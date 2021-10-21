import re

Instruction = tuple[str, list[str]]


class CodeBlock:
    '''Represents a code section that corresponds to a function or label.

    Contains the list of instructions belonging to that block.
    '''

    def __init__(self) -> None:
        self.name = ''
        self.instructions = []
        self.is_function = False
        self.return_type = ''
        self.return_exludes = ['bx', 'ctr', 'str1', 'str2']
        self.param_exludes = ['bx', 'ctr', 'str1', 'str2']


    def _get_var_type(self, search_idx: int, register: str) -> str:
        '''Determines the type of a variable/register.

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
