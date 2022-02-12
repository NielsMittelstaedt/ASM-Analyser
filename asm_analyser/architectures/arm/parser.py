from asm_analyser.blocks.code_block import CodeBlock
from asm_analyser import parser
import re
import sys
sys.path.append('..')


class ArmParser(parser.Parser):
    def __init__(self, input_path: str, filename: str) -> None:
        super().__init__(input_path, filename)
        self.filter_re = ('(^\t@ .*)|(.*\.(arch|eabi_attribute|file|text|'
                          'global|align|syntax|arm|fpu|size|ident|section).*)')
        self.line_columns = []

    def create_blocks(self) -> list[CodeBlock]:
        blocks = []
        self._parse_file()

        last_parent_block = ''

        for i, el in enumerate(self.line_columns):
            (num, line) = el

            # detect the blocks by the labels
            if re.match('^\.?.+:$', line[0]):
                block = CodeBlock()
                block.name = line[0].replace('.', '').replace(':', '')

                # check if the block represents a function
                if (self.line_columns[i - 1][1][0] == '.type' and
                        self.line_columns[i - 1][1][2] == '%function'):
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
                blocks[-1].instructions.append((num, line[0], line[1:]))
            # common symbols are handled like constant definitions
            elif line[0] == '.comm':
                block = CodeBlock()
                block.name = line[1].replace('.', '').replace(':', '')
                block.is_code = False
                block.instructions.append((num, line[0], line[1:]))
                blocks.append(block)
            elif line[0] == '.inst':
                blocks[-1].instructions.append((num, 'nop', []))
            elif line[0][0] != '.':
                if len(line) > 1:
                    blocks[-1].instructions.append((num, line[0], line[1:]))
                elif len(line) == 1:
                    blocks[-1].instructions.append((num, line[0], []))

        return self._set_last_blocks(blocks)

    def _parse_file(self) -> None:
        with open(f'{self.input_path}/{self.filename}.s', 'r') as f:
            lines = []

            for i, l in enumerate(f.readlines()):
                # filter out empty lines
                if l.replace(' ', '').replace('\t', '') != '\n':
                    if '.ascii' not in l:
                        lines.append(
                            (i, re.sub(
                                '[#{}]', '', l).replace(
                                ',', ' ')))
                    else:
                        lines.append((i, l))

            for i, line in lines:
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
                    columns[1] = columns[1][:columns[1].rfind('"') + 1]

                self.line_columns.append((i, columns))

    def _set_last_blocks(self, blocks: list[CodeBlock]) -> list[CodeBlock]:
        '''Marks the last labeled code block in the main function.


        Parameters
        ----------
        blocks : list[CodeBlock]
            List of the labeled code blocks with their instructions.

        Returns
        -------
        list[CodeBlocks]
            List of code blocks in which the last one is marked.
        '''
        last_idx = len(blocks) - 1

        while(last_idx >= 0):
            if (blocks[last_idx].parent_name == 'main' and
                    blocks[last_idx].is_code):
                blocks[last_idx].is_last = True
            last_idx -= 1

        return blocks
