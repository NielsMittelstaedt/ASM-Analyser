from abc import abstractmethod
from code_block import CodeBlock

class Parser:
    '''Converts the input into a suitable format.

    Parser class, responsible for reading the assembler input file.
    Transforms the lines into code blocks.
    '''

    def __init__(self, file_name: str) -> None:
        self.file_name = file_name

    @abstractmethod
    def read_file(self) -> None:
        '''Reads the input file and throws away unnecessary lines.'''
        pass

    @abstractmethod
    def create_blocks(self) -> list[CodeBlock]:
        '''Splits the instructions into a list of code blocks.

        Returns
        -------
        list[CodeBlock]
            List of code blocks with a name and a set of instructions
            for each block.
        '''
        pass