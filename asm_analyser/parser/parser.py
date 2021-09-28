from abc import abstractmethod
from function import Function

class Parser:
    '''Converts the input into a suitable format.

    Parser class, responsible for reading the assembler input file.
    Transforms the lines into blocks of functions.
    '''

    def __init__(self, file_name: str) -> None:
        self.file_name = file_name

    @abstractmethod
    def read_file(self) -> None:
        '''Reads the input file and throws away unnecessary lines.'''
        pass

    @abstractmethod
    def create_functions(self) -> list[Function]:
        '''Splits the instructions into a list of functions.

        Returns
        -------
        list[Function]
            List of functions with a name and a set of instructions
            for each function.
        '''
        pass


#class FileError(Exception):
#    '''Raised when creating the output file goes wrong
#    or when there is no file name
#    '''
#
#    def __init__(self, message: str) -> None:
#        super().__init__()
#        self.message = message
#