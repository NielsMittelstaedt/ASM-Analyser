import re
from asm_analyser.blocks.code_block import CodeBlock

# Stack size in bytes
STACK_SIZE = 20000

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
    needed_vars = {'r0', 'r1', 'r2', 'r3', 'r4'}

    for block in blocks:
        for instr in block.instructions:
            for j, op in enumerate(instr[2]):
                if re.match('^\[?r\d{1,2}\]?$', op):
                    needed_vars.add(instr[2][j])

    if len(needed_vars) == 0:
        return ''

    result = 'reg '
    result += ', '.join(needed_vars)

    return result+';\n'

def get_malloc_start(blocks: list[CodeBlock]) -> str:
    '''TODO
    '''
    blocks = [block for block in blocks if not block.is_code]
    bytes = []

    # calculate and allocate the necessary memory
    for block in blocks:
        if block.instructions[0][1] == '.ascii':
            bytes.append(len(block.instructions[0][2][0]))
        elif block.instructions[0][1] == '.word':
            bytes.append(len(block.instructions)*4)
        elif block.instructions[0][1] == '.comm':
            bytes.append(int(block.instructions[0][2][1]))
        elif block.instructions[0][1] == '.space':
            bytes.append(int(block.instructions[0][2][0]))

    total_length = sum(bytes)+STACK_SIZE

    result  = f'malloc_0 = (uint8_t*) malloc({total_length});\n'
    result += f'sp.i = {STACK_SIZE-4};\n'
    result += f'fp = sp;\n'

    return result

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
        if block.instructions[0][1] == '.ascii':
            bytes.append(len(block.instructions[0][2][0]))
        elif block.instructions[0][1] == '.word':
            bytes.append(len(block.instructions)*4)
        elif block.instructions[0][1] == '.comm':
            bytes.append(int(block.instructions[0][2][1]))
        elif block.instructions[0][1] == '.space':
            bytes.append(int(block.instructions[0][2][0]))

    # define the constants
    for i, block in enumerate(blocks):
        if i == 0:
            result += f'{block.name} = {STACK_SIZE};\n'
        else:
            result += f'{block.name} = {STACK_SIZE+sum(bytes[:i])};\n'        

        if block.instructions[0][1] == '.ascii':
            result += f'strcpy(malloc_0+{block.name}, {block.instructions[0][2][0]});\n\n'
        elif block.instructions[0][1] == '.word':
            arr = [instr[2][0] for instr in block.instructions]
            result += f'int32_t array{block.name}[] = {{{",".join(arr)}}};\n'
            result += f'for(int i=0; i<{len(arr)}; i++) str4000(&array{block.name}[i], &{block.name}, i*4);\n\n'
        elif block.instructions[0][1] == '.comm':
            pass
        elif block.instructions[0][1] == '.space':
            pass

    return result

def get_function_decls(blocks: list[CodeBlock]) -> str:
    '''Creates the functions declarations in C for every arm function.

    Returns
    -------
    str
        C code containing the function declarations.
    '''
    funcs = [block.name for block in blocks if block.is_function]

    if len(funcs) <= 0:
        return ''

    result = 'void '
    result += '();\nvoid '.join(funcs)
    return result + '();\n'