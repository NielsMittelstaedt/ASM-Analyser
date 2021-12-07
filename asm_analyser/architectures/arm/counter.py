import re
from asm_analyser import counter
from asm_analyser.blocks.code_block import CodeBlock
from asm_analyser.blocks.basic_block import BasicBlock

class Counter(counter.Counter):

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

            code_blocks[code_index].instructions.insert(instr_index, ('ctr', [str(i)]))
            instr_index += 1

            instr_index += len(block.instructions)

        # add count instruction to each memory access instruction
        for i, block in enumerate(code_blocks):
            j = 0
            while j < len(block.instructions):
                if re.match('^(ldr|ldm|pop).*$', block.instructions[j][0]):
                    code_blocks[i].instructions.insert(j, ('memctr0', ['0']))
                    j += 1
                if re.match('^(str|stm|push).*$', block.instructions[j][0]):
                    code_blocks[i].instructions.insert(j, ('memctr1', ['0']))
                    j += 1
                j += 1

        return code_blocks

    @staticmethod
    def get_counter_vars(blocks: list[BasicBlock]) -> str:
        if len(blocks) <= 0:
            return ''
    
        # array with an entry for each basic block
        result = f'int counters[{len(blocks)}] = {{ 0 }};\n'

        # counter variables for memory access
        result += 'int load_counter = 0, store_counter = 0;\n'

        # array with size of each basic block
        result += f'int block_sizes[{len(blocks)}] = {{'
        block_lengths = [str(len(block.instructions)) for block in blocks]
        result += ','.join(block_lengths)
        result += '};\n'

        return result