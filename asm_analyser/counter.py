from function import Function

def insert_counters(functions: list[Function]) -> list[Function]:
    for i, function in enumerate(functions):
        cur_block_ctr = 0
        for instruction in function.instructions:
            cur_block_ctr += 1

            # if there is a block inside the function, count the instructions for that block and put a counter at the end

        functions[i].instructions.append(('ctr', [str(cur_block_ctr)]))
