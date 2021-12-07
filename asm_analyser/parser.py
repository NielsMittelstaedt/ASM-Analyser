from abc import ABC, abstractmethod
from blocks.code_block import CodeBlock

class Parser(ABC):
    '''Converts the input into a suitable format.

    Parser class, responsible for reading the assembler input file.
    Transforms the lines into code blocks.
    '''
    
    def __init__(self, input_path: str, filename: str) -> None:
        super().__init__()
        self.input_path = input_path
        self.filename = filename

    @abstractmethod
    def create_blocks(self, filename: str) -> list[CodeBlock]:
        '''Splits the instructions into a list of code blocks.

        Parameters
        ----------
        filename : str
            Name of the assembly file to be read.

        Returns
        -------
        list[CodeBlock]
            List of code blocks with a name and a set of instructions
            for each block.
        '''
        pass

    @abstractmethod
    def _read_file(self) -> None:
        '''Reads the input file and throws away unnecessary lines.'''
        pass