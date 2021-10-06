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

    def _get_param_type_rev(self, register: str) -> str:
        '''Determines the type of a variable/register.

        Determines the type of the given variable by iterating backwards
        through the instructions of this function.

        Parameters
        ----------
        register : str
            Name of the variable.

        Returns
        -------
        str
            Type of the variable in C.
        '''
        for instr in reversed(self.instructions):
            if instr[0] in self.return_exludes:
                continue

            # check the operand values
            if register in instr[1][0]:
                if instr[0] == 'add':
                    return 'int32_t'

                if instr[0] == 'fadd':
                    return 'float'

                if instr[0] == 'mov':
                    if re.match('^\[?r\d{1}\]?$', instr[1][1]):
                        register = instr[1][1]

                    if re.match('^-?\d+$', instr[1][1]):
                        return 'int32_t'

                    if re.match('[+-]?([0-9]*[.])?[0-9]+', instr[1][1]):
                        return 'float'
                    continue

        return 'void'

    def _get_param_type(self, search_idx: int, register: str) -> str:
        '''Determines the type of a variable/register.

        Determines the type of the given variable or function parameter
        by iterating through the instructions of this function.

        Parameters
        ----------
        search_idx : int
            Index of the instruction where the search should start.
        register : str
            Name of the variable.

        Returns
        -------
        str
            Type of the variable in C.
        '''
        for instr in self.instructions[search_idx+1:]:
            if instr[0] in self.return_exludes:
                continue

            # check the operand values
            if register in instr[1][0]:
                if instr[0] == 'add':
                    return 'int32_t'

                if instr[0] == 'fadd':
                    return 'float'

                if instr[0] == 'mov':
                    if re.match('^\[?r\d{1}\]?$', instr[1][1]):
                        register = instr[1][1]

                    if re.match('^-?\d+$', instr[1][1]):
                        return 'int32_t'

                    if re.match('[+-]?([0-9]*[.])?[0-9]+', instr[1][1]):
                        return 'float'
                    continue

        return ''
