from basic_block import BasicBlock

def insert_counters(blocks: list[BasicBlock]) -> list[BasicBlock]:
    for i, block in enumerate(blocks):
        cur_block_ctr = 0
        for instruction in block.instructions:
            cur_block_ctr += 1

            # if there is a block inside the function, count the instructions for that block and put a counter at the end

        blocks[i].instructions.append(('ctr', [str(cur_block_ctr)]))
