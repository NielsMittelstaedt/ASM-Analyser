from os import terminal_size
import sys
sys.path.append("..")
import re
from code_block import CodeBlock
from parser.parser import Parser

class ArmParser(Parser):
    def __init__(self, file_name: str) -> None:
        super().__init__(file_name)
        self.filter_re = ('(^\t@ .*)|(.*\.(arch|eabi_attribute|file|text|'
                          'global|align|syntax|arm|fpu|size|ident|section).*)')
        self.file_name = file_name
        self.line_columns = []

    def create_blocks(self) -> list[CodeBlock]:
        blocks = []
        self._read_file()

        for i, line in enumerate(self.line_columns):
            # detect the blocks by the labels
            if re.match('^\.?.+:$', line[0]):
                block = CodeBlock()
                block.name = line[0].replace('.', '').replace(':','')
                
                # check if the block represents a function
                if (self.line_columns[i-1][0] == '.type' and 
                        self.line_columns[i-1][2] == '%function'):
                    block.is_function = True
                # check if the block represents a constant
                if re.match('^LC\d*$', block.name):
                    block.is_code = False

                blocks.append(block)
                continue

            # add the instructions or constant definitions
            if re.match('^\.(word|ascii)$', line[0]):
                blocks[-1].instructions.append((line[0],
                                                [' '.join(line[1:])]))
            elif line[0][0] != '.':
                if len(line) > 1:
                    blocks[-1].instructions.append((line[0], line[1:]))
                elif len(line) == 1:
                    blocks[-1].instructions.append((line[0], []))

        return blocks

    def _read_file(self) -> None:
        f = open(f'../examples/asm/{self.file_name}.s', 'r')

        lines = [ re.sub('[#{}]', '', l).replace(',',' ')  for l in f.readlines()]

        for line in lines:
            # remove unneccesary lines
            if bool(re.match(self.filter_re, line)):
                continue

            columns = line.split()

            self.line_columns.append(columns)