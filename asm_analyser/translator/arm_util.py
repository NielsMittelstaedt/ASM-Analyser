import re
from asm_analyser.blocks.code_block import CodeBlock, Instruction


def get_needed_regs(blocks: list[CodeBlock]) -> str:
    '''Determines the global variables that need to be created as registers.

    Parameters
    ----------
    blocks : list[CodeBlock]
        All the labeled code blocks with their instructions.

    Returns
    -------
    str
        Variable declarations in C.
    '''
    needed_vars = {'r0', 'r1'}

    for block in blocks:
        for instr in block.instructions:
            for j, op in enumerate(instr[1]):
                if re.match('^\[?r\d{1,2}\]?$', op):
                    needed_vars.add(instr[1][j])

    if len(needed_vars) == 0:
        return ''

    result = 'reg '
    result += ', '.join(needed_vars)

    return result+';\n'

def get_part_vars(blocks: list[CodeBlock]) -> str:
    '''Creates the global variables needed for translating divided functions.

    The GCC compiler sometimes splits functions into multiple parts
    as an optimization.
    (see https://github.com/gcc-mirror/gcc/blob/master/gcc/ipa-split.c)

    Returns
    -------
    str
        Variable declarations in C.
    '''
    parts = {re.sub('\d+$', '', block.name)
             for block in blocks if block.is_part}
    
    if len(parts) <= 0:
        return ''

    result = 'int '
    result += ', '.join(parts)
    return result + ';\n'

def get_needed_consts(blocks: list[CodeBlock]) -> str:
    '''Creates the global variables needed for constants.

    These constants variables are used to store pointers to memory
    containing the constants (e.g. array, string,...)

    Returns
    -------
    str
        Variable declarations in C.
    '''
    contants = [block.name for block in blocks if not block.is_code]

    if len(contants) <= 0:
        return ''

    result = 'int32_t '
    result += ', '.join(contants)
    return result + ';\n'

def get_constant_defs(blocks: list[CodeBlock]) -> str:
    '''Fills the constants from "get_needed_consts".

    This is done by allocating memory with malloc in C and then
    saving the values to that memory.
    The pointer to that memory is stored in a global variable.

    Returns
    -------
    str
        C code that defines the arm constants.
    '''
    blocks = [block for block in blocks if not block.is_code]

    if len(blocks) <= 0:
        return ''

    block_order = {}
    block_count = 0

    for block in blocks:
        if block.parent_name not in block_order:
            block_order[block.parent_name] = block_count
            block_count += 1

    # sort the blocks in each section so that 'LCx' definitions come first
    blocks = sorted(blocks, key = lambda b: (block_order[b.parent_name],
                                             'LC' not in b.name))

    result = ''
    bytes = []

    # calculate and allocate the necessary memory
    for block in blocks:
        if block.instructions[0][0] == '.ascii':
            bytes.append(len(block.instructions[0][1][0]))
        elif block.instructions[0][0] == '.word':
            bytes.append(len(block.instructions)*4)
        elif block.instructions[0][0] == '.comm':
            bytes.append(int(block.instructions[0][1][1]))
        elif block.instructions[0][0] == '.space':
            bytes.append(int(block.instructions[0][1][0]))

    result += f'int32_t malloc_total = (int32_t) ((uint8_t*) malloc({sum(bytes)}) - malloc_0);\n'

    # define the constants
    for i, block in enumerate(blocks):
        if i == 0:
            result += f'{block.name} = malloc_total;\n'
        else:
            result += f'{block.name} = malloc_total + {sum(bytes[:i])};\n'        

        if block.instructions[0][0] == '.ascii':
            result += f'strcpy(malloc_0+{block.name}, {block.instructions[0][1][0]});\n\n'
        elif block.instructions[0][0] == '.word':
            arr = [instr[1][0] for instr in block.instructions]
            result += f'int32_t array{block.name}[] = {{{",".join(arr)}}};\n'
            result += f'for(int i=0; i<{len(arr)}; i++) str(&array{block.name}[i], &{block.name}, i*4, 4, false, false, false);\n\n'
        elif block.instructions[0][0] == '.comm':
            length = block.instructions[0][1][1] 
            result += f'{block.name} = (int32_t) ((uint8_t*) malloc({length}*sizeof(int8_t)) - malloc_0);\n\n'
        elif block.instructions[0][0] == '.space':
            length = block.instructions[0][1][0]
            result += f'{block.name} = (int32_t) ((uint8_t*) calloc({length}, sizeof(int8_t)) - malloc_0);\n\n'

    return result

def get_function_decls(blocks: list[CodeBlock]) -> str:
    '''Creates the functions declarations in C for every arm function.

    Returns
    -------
    str
        C code containing the function declarations.
    '''
    funcs = [block.name for block in blocks if block.is_function and
             not block.is_part]

    if len(funcs) <= 0:
        return ''

    result = 'void '
    result += '();\nvoid '.join(funcs)
    return result + '();\n'

