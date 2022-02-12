import re
from asm_analyser import counter
from asm_analyser.blocks.code_block import CodeBlock
from asm_analyser.blocks.basic_block import BasicBlock

class ArmCounter(counter.Counter):

    @staticmethod
    def insert_counters(code_blocks: list[CodeBlock],
                        basic_blocks: list[BasicBlock]) -> list[CodeBlock]:
        last_block_name = ''
        instr_index = 0

        # add count instruction to the beginning of every basic block
        for i, block in enumerate(basic_blocks):
            if block.parent_block != last_block_name:
                instr_index = 0
            last_block_name = block.parent_block

            code_index = next((i for i, item in enumerate(code_blocks)
                            if item.name == last_block_name), -1)
            if code_index == -1:
                raise ValueError('TODO: ändern')

            code_blocks[code_index].instructions.insert(instr_index, (-1, 'ctr', [str(i)]))
            instr_index += 1

            instr_index += len(block.instructions)

        return code_blocks

    @staticmethod
    def get_counter_vars(blocks: list[BasicBlock]) -> str:
        if len(blocks) <= 0:
            return ''
    
        # array with an entry for each basic block
        result = f'int counters[{len(blocks)}] = {{ 0 }};\n'

        # array with size of each basic block
        result += f'int block_sizes[{len(blocks)}] = {{'
        block_lengths = [str(len(block.instructions)) for block in blocks]
        result += ','.join(block_lengths)
        result += '};\n'

        return result

    @staticmethod
    def write_instr_counts(file_path: str, blocks: list[BasicBlock],
                           block_counts: list[int]) -> None:
        asm_lines = []

        with open(file_path, 'r') as f:
            asm_lines = f.readlines()

        line_index = 0
        with open(file_path, 'w') as f:
            for i, block in enumerate(blocks):
                for instr in block.instructions:
                    while line_index < instr[0]:
                        f.write(f'0 {asm_lines[line_index]}')
                        line_index += 1
                    f.write(f'{block_counts[i]} {asm_lines[line_index]}')
                    line_index += 1

            while line_index < len(asm_lines):
                f.write(f'0 {asm_lines[line_index]}')
                line_index += 1