from code_block import CodeBlock
from basic_block import BasicBlock


def insert_counters(code_blocks: list[CodeBlock],
                    basic_blocks: list[BasicBlock]) -> list[CodeBlock]:
    '''TODO
    '''
    last_block_name = ''
    instr_index = 0

    for i, block in enumerate(basic_blocks):
        if block.parent_block != last_block_name:
            instr_index = 0
        last_block_name = block.parent_block

        instr_index += len(block.instructions)

        code_index = next((i for i, item in enumerate(code_blocks)
                           if item.name == last_block_name), -1)
        if code_index == -1:
            raise ValueError('TODO: ändern')

        code_blocks[code_index].instructions.insert(instr_index, ('ctr', [str(i)]))
        instr_index += 1

    return code_blocks


def get_counter_vars(blocks: list[BasicBlock]) -> str:
    '''TODO
    '''
    if len(blocks) <= 0:
        return ''
    
    counters = [f'counter{i}' for i,_ in enumerate(blocks)]
    result = 'int '
    result += ', '.join(counters)
    
    return result + ';\n\n'