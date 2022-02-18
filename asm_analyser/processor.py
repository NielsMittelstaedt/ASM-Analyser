'''Provides the basis for processing code blocks further.
'''

from abc import ABC, abstractmethod
from typing import List
from blocks.code_block import CodeBlock
from blocks.basic_block import BasicBlock


class Processor(ABC):
    '''Processes the instructions.
    '''

    @staticmethod
    @abstractmethod
    def create_ir(blocks: List[CodeBlock]) -> List[CodeBlock]:
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

    @staticmethod
    @abstractmethod
    def get_basic_blocks(blocks: List[CodeBlock]) -> List[BasicBlock]:
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
