from abc import ABC, abstractmethod
from blocks.code_block import CodeBlock
from blocks.basic_block import BasicBlock


class Processor(ABC):
    '''TODO
    '''

    @staticmethod
    @abstractmethod
    def create_IR(blocks: list[CodeBlock]) -> list[CodeBlock]:
        '''Creates a the indermediate representation of the instructions.

        Parameters
        ----------
        blocks : list[CodeBlock]
            The code blocks with all their instructions.

        Returns
        -------
        list[CodeBlock]
            List of code blocks with the instrucitons.
        '''
        pass

    @staticmethod
    @abstractmethod
    def get_basic_blocks(blocks: list[CodeBlock]) -> list[BasicBlock]:
        '''Divides the code blocks into basic blocks by looking at branching.

        Parameters
        ----------
        blocks : list[CodeBlock]
            The code blocks with all their instructions.

        Returns
        -------
        list[BasicBlock]
            List of basic blocks for all the code blocks.
        '''
        pass
