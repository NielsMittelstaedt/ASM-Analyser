import re
import sys
sys.path.append('..')
from asm_analyser import parser
from asm_analyser.blocks.code_block import CodeBlock

class Parser(parser.Parser):
    def __init__(self, input_path: str, filename: str) -> None:
        super().__init__(input_path, filename)
        self.filter_re = ('(^\t@ .*)|(.*\.(arch|eabi_attribute|file|text|'
                          'global|align|syntax|arm|fpu|size|ident|section).*)')
        self.line_columns = []
        

    def create_blocks(self) -> list[CodeBlock]:
        blocks = []
        self._read_file()

        last_parent_block = ''

        for i, line in enumerate(self.line_columns):
            # detect the blocks by the labels
            if re.match('^\.?.+:$', line[0]):
                block = CodeBlock()
                block.name = line[0].replace('.', '').replace(':','')
                
                # check if the block represents a function
                if (self.line_columns[i-1][0] == '.type' and 
                        self.line_columns[i-1][2] == '%function'):
                    block.is_function = True

                # set name of the parent block
                if block.is_function:
                    block.parent_name = block.name
                    last_parent_block = block.name
                else:
                    block.parent_name = last_parent_block

                blocks.append(block)
                continue

            # add the instructions or constant definitions
            if re.match('^\.(word|ascii|space)$', line[0]):
                blocks[-1].is_code = False
                if '.word' in line[0]:
                    line[1] = line[1].replace('.LC', 'LC')
                    if line[1].find('+') != -1:
                        line[1] = line[1][:line[1].find('+')]
                blocks[-1].instructions.append((line[0], line[1:]))
            # common symbols are handled like constant definitions
            elif line[0] == '.comm':
                block = CodeBlock()
                block.name = line[1].replace('.', '').replace(':','')
                block.is_code = False
                block.instructions.append((line[0], line[1:]))
                blocks.append(block)

            elif line[0][0] != '.':
                if len(line) > 1:
                    blocks[-1].instructions.append((line[0], line[1:]))
                elif len(line) == 1:
                    blocks[-1].instructions.append((line[0], []))

        return self._set_last_block(blocks)

    def _read_file(self) -> None:
        f = open(f'{self.input_path}/{self.filename}.s', 'r')

        lines = []

        for l in f.readlines():
            if '.ascii' not in l:
                lines.append(re.sub('[#{}]', '', l).replace(',',' '))
            else:
                lines.append(l)

        for line in lines:
            # remove unneccesary lines
            if bool(re.match(self.filter_re, line)):
                continue

            # remove comments within a line
            comment_idx = line.find('@')
            if comment_idx != -1:
                line = line[:comment_idx]

            if '.ascii' not in line:
                columns = line.split(None)
            else:
                columns = line.split(None, 1)
                columns[1] = columns[1][:columns[1].rfind('"')+1]

            self.line_columns.append(columns)

    def _set_last_block(self, blocks: list[CodeBlock]) -> list[CodeBlock]:
        '''TODO
        '''
        last_idx = len(blocks)-1

        while(last_idx >= 0):
            if blocks[last_idx].parent_name == 'main':
                break
            last_idx -= 1
        
        blocks[last_idx].is_last = True

        return blocks