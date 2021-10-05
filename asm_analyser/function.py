import re

Instruction = tuple[str, list[str]]


class Function:
    '''Represents a code section that corresponds to a function.

    Contains the list of instructions belonging to that function.
    '''

    def __init__(self) -> None:
        self.name = ''
        self.instructions = []
        self.return_exludes = ['bx', 'ctr', 'str1', 'str2']
        self.param_exludes = ['bx', 'ctr', 'str1', 'str2']

    def get_return_type(self) -> str:
        '''Determines the return type of the function.

        Goes through the instructions backwards and determines the 
        return type by looking at the instructions where r0 was used.

        Returns
        -------
        str
            Return type of the function (currently: int, float or void).
        '''
        reg_to_search = 'r0'

        for instr in reversed(self.instructions):
            if instr[0] in self.return_exludes:
                continue

            # case for branching
            if instr[0] == 'bl':
                if reg_to_search == 'r0':
                    if instr[1][0] == '__aeabi_fadd':
                        return 'float'

                continue

            # case for normal instructions
            if reg_to_search in instr[1][0]:
                if instr[0] == 'add':
                    return 'int'

                if instr[0] == 'mov':
                    if 'r' in instr[1][1]:
                        reg_to_search = instr[1][1]

                    if re.match('^\d+$', instr[1][1]):
                        return 'int'
                    continue

        return 'void'

    def get_params(self) -> str:
        '''Determines paramters of the function.

        Returns
        -------
        str
            Comma separated function parameters in C.
        '''
        params = []
        registers = []

        # without optimization, the parameters will be loaded from the stack

        used_registers = set()

        for i, instruction in enumerate(self.instructions):
            if ('ldr' in instruction[0] and 'r' in instruction[1][0] and
                    instruction[1][0] not in used_registers):
                if 'float' in instruction[1]:
                    params.append(f'float {instruction[1][0]}')
                else:
                    param_type = self._get_param_type(i, instruction[1][0])
                    params.append(f'{param_type} {instruction[1][0]}')
                continue

            if 'r' in instruction[1][0] and 'str' not in instruction[0]:
                used_registers.add(instruction[1][0])

            # break if calculations start

        # with optimization, the parameters can already be in register r0-r3

        return ', '.join(params)

    def _get_param_type(self, search_idx, register: list[Instruction]) -> str:
        '''TODO
        '''
        for instr in self.instructions[search_idx+1:]:
            if instr[0] in self.return_exludes:
                continue

            # case for branching
            if instr[0] == 'bl':
                if register == 'r0':
                    if instr[1][0] == '__aeabi_fadd':
                        return 'float'

                continue

            # case for normal instructions
            if register in instr[1][0]:
                if instr[0] == 'add':
                    return 'int'

                if instr[0] == 'mov':
                    if 'r' in instr[1][1]:
                        register = instr[1][1]
                    # TODO: search regex for integer number
                    if instr[1][1] == '0':
                        return 'int'
                    continue
