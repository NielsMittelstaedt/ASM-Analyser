'''Provides the basis for a branch prediction simulation.
'''

from abc import ABC, abstractmethod
from typing import List, Dict
from asm_analyser.blocks.code_block import CodeBlock


class BranchPredictor(ABC):
    '''Responsible for branch prediction simulation.
    '''

    def __init__(self, c_code) -> None:
        super().__init__()
        self.c_code = c_code

    @abstractmethod
    def insert_branch_pred(self, method_name: str) -> str:
        '''Inserts the everything necessary for the desired branch
        prediction strategy.

        Parameters
        ----------
        c_code : str
            The C code containing placeholders for the branch predictions.
        method_name : str
            Name of the branch prediction strategy that should be used.

        Returns
        -------
        str
            C code containing all necessary elements to simulate branch predictions.
        '''

    @staticmethod
    @abstractmethod
    def is_branch_instr(opcode: str, *args) -> bool:
        '''Checks whether the given instruction is a branch instruction.

        Parameters
        ----------
        opcode : str
            Name of the instruction
        args : tuple(str)
            Operands for the instruction

        Returns
        -------
        bool
            Determines whether the instructions is a branch instruction.
        '''

    @staticmethod
    @abstractmethod
    def write_rates(file_path: str,
                    blocks: List[CodeBlock],
                    branch_rates: List[float],
                    branch_map: Dict[int, int]) -> None:
        '''Writes the number of executions next to each assembly instruction.

        Parameters
        ----------
        file_path : str
            File path of the assembly file.
        blocks : list[BasicBlock]
            The basic blocks with all their instructions.
        branch_rates : list[float]
            Branch prediction success rate for each branch instruction.
        branch_map : dict[int, int]
            Maps the instruction index to the branch index.
        '''
