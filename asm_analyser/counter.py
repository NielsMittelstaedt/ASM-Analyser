'''
Provides the basis for instruction counting.
'''

from abc import ABC, abstractmethod
from blocks.code_block import CodeBlock
from blocks.basic_block import BasicBlock


class Counter(ABC):
    '''Responsible for counting the instructions.
    '''

    @staticmethod
    @abstractmethod
    def insert_counters(code_blocks: list[CodeBlock],
                        basic_blocks: list[BasicBlock]) -> list[CodeBlock]:
        '''Inserts the counter variables.

        Inserts the counter variables by adding instructions
        to the codeblocks which will be later translated to C.

        Parameters
        ----------
        code_blocks : list[CodeBlock]
            The code blocks with all their instructions.
        basic_blocks : list[BasicBlock]
            The basic blocks with all their instructions.

        Returns
        -------
        list[CodeBlock]
            The code blocks which now contain the instructions for counting.
        '''

    @staticmethod
    @abstractmethod
    def get_counter_vars(blocks: list[BasicBlock]) -> str:
        '''Returns the C code to define the necessary variables for counting.

        Parameters
        ----------
        blocks : list[BasicBlock]
            The basic blocks with all their instructions.

        Returns
        -------
        str
            The C code containing the definitions
            for all the counter variables.
        '''

    @staticmethod
    @abstractmethod
    def write_instr_counts(file_path: str, blocks: list[BasicBlock],
                           block_counts: list[int]) -> None:
        '''Writes the number of executions next to each assembly instruction.

        Parameters
        ----------
        file_path : str
            File path of the assembly file.
        blocks : list[BasicBlock]
            The basic blocks with all their instructions.
        block_counts : list[int]
            Number of times each basic block was executed.
        '''
