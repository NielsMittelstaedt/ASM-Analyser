from abc import ABC, abstractmethod
from blocks.code_block import CodeBlock, Instruction
from blocks.basic_block import BasicBlock
from counter import Counter

class Translator(ABC):
    '''Translates all the assembly instructions to C.
    '''

    def __init__(self,
                 code_blocks: list[CodeBlock],
                 basic_blocks: list[BasicBlock],
                 file_name: str,
                 counter: Counter):
        super().__init__()
        self.code_blocks = code_blocks
        self.basic_blocks = basic_blocks
        self.file_name = file_name
        self.counter = counter

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
    def _translate_instruction(self, instruction: Instruction) -> str:
        '''Translates one assembly instruction to C using a dictionary.

        Parameters
        ----------
        instruction : Instruction
            The instruction (opcode with parameters) to translate.

        Returns
        -------
        str
            The translated instruction in C.
        '''
        pass