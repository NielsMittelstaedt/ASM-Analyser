from abc import ABC, abstractmethod
from asm_analyser.blocks.code_block import CodeBlock, Instruction
from asm_analyser.blocks.basic_block import BasicBlock


class Translator(ABC):
    '''Translates all the assembly instructions to C.'''

    def __init__(self,
                 code_blocks: list[CodeBlock],
                 basic_blocks: list[BasicBlock],
                 file_name: str,
                 part_functions: set[str]):
        self.code_blocks = code_blocks
        self.basic_blocks = basic_blocks
        self.file_name = file_name
        self.part_functions = part_functions
        super().__init__()

    @abstractmethod
    def translate(self) -> str:
        '''Main translation, translates the whole asm file.

        Returns
        -------
        str
            The complete translated C file.
        '''
        pass

    @abstractmethod
    def _translate_blocks(self) -> str:
        '''Translates the code blocks (i.e. functions, labels) one by one.

        Returns
        -------
        str
            The translated C code containing all the code blocks.
        '''
        pass

    @abstractmethod
    def _translate_block(self, block: CodeBlock) -> str:
        '''Translates one code block (function) with all its labels.

        Parameters
        ----------
        block : CodeBlock
            The code block to be translated.

        Returns
        -------
        str
            The translated C function or code sequence.
        '''
        pass

    @abstractmethod
    def _translate_instruction(self, instruction: Instruction,
                               parent_name: str) -> str:
        '''Translates one assembly instruction to C using a dictionary.

        Parameters
        ----------
        instruction : Instruction
            The instruction (opcode with parameters) to translate.
        parent_name : str
            The name of the block to which the instruction belongs.

        Returns
        -------
        str
            The translated instruction in C.
        '''
        pass