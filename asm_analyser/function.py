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

        return self._get_param_type_rev(reg_to_search)

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

        for i, instr in enumerate(self.instructions):
            if ('ldr' in instr[0] and re.match('^\[?r\d{1}\]?$', instr[1][0])
                    and instr[1][0] not in used_registers):
                if 'float' in instr[1]:
                    params.append(f'float {instr[1][0]}')
                else:
                    param_type = self._get_param_type(i, instr[1][0])
                    params.append(f'{param_type} {instr[1][0]}')
                continue

            if (re.match('^\[?r\d{1}\]?$', instr[1][0]) and
                    'str' not in instr[0]):
                used_registers.add(instr[1][0])

            # break if calculations start

        # with optimization, the parameters can already be in register r0-r3

        return ', '.join(params)

    def get_needed_vars(self, params: str) -> str:
        '''TODO
        '''
        params = params.split(',')
        param_registers = [param.split()[-1] for param in params
                           if len(param) > 0]
        needed_vars = set()
        result = ''
        
        # find all variables needed by looking at the used registers
        for instr in self.instructions:
            for j, op in enumerate(instr[1]):
                if (re.match('^\[?r\d{1}\]?$', op) and
                        instr[1][j] not in param_registers):
                    needed_vars.add(instr[1][j])

        for var in needed_vars:
            result += f'{self._get_param_type_rev(var)} {var};\n'

        return result

    def _get_param_type_rev(self, register: str) -> str:
        '''TODO
        '''
        for instr in reversed(self.instructions):
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

                    if re.match('^\d+$', instr[1][1]):
                        return 'int'
                    continue

        return 'void'

    def _get_param_type(self, search_idx: int, register: str) -> str:
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
                    if re.match('^\[?r\d{1}\]?$', instr[1][1]):
                        register = instr[1][1]
                    # TODO: search regex for integer number
                    if instr[1][1] == '0':
                        return 'int'
                    continue

        return ''
