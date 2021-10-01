
class Function:
    '''Represents a code section that corresponds to a function.

    Contains the list of instructions belonging to that function.
    '''

    def __init__(self) -> None:
        self.name = ''
        self.instructions = []

    def get_return_type(self) -> str:
        '''Determines the return type of the function.

        Returns
        -------
        str
            Return type of the function (currently: int, float or void).
        '''
        
        # The return value is stored in r0
        return 'int'

    def get_params(self) -> str:
        '''Determines paramters of the function.

        Returns
        -------
        str
            Comma separated function parameters in C.
        '''
        params = []

        # without optimization, the parameters will be loaded from the stack
        
        used_registers = set()

        for instruction in self.instructions:
            if (instruction[0] == 'ldr' and 'r' in instruction[1][0] and
                  instruction[1][0] not in used_registers):
                params.append(f'int {instruction[1][0]}')
                continue

            if 'r' in instruction[1][0]:
                used_registers.add(instruction[1][0])

            # break if calculations start

        return ', '.join(params)
