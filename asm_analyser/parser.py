'''
Provides the basis for a Parser.
'''

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
    def create_blocks(self) -> list[CodeBlock]:
        '''Splits the instructions into a list of code blocks.

        Returns
        -------
        list[CodeBlock]
            List of code blocks with a name and a set of instructions
            for each block.
        '''

    @abstractmethod
    def _parse_file(self) -> None:
        '''Splits the input lines and throws away unnecessary lines.

        Every line is numbered to identify it later for counting.
        '''
