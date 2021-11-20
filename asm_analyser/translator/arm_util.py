import re
from asm_analyser.blocks.code_block import CodeBlock


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
    result = ''

    for block in blocks:
        # distinguish between string and array
        if block.instructions[0][0] == '.ascii':
            const = block.name
            string = block.instructions[0][1][0]
            result += f'{const} = (int32_t) ((uint8_t*) malloc({len(string)}) - malloc_0);\n'
            result += f'strcpy(malloc_0+{const}, {block.instructions[0][1][0]});\n\n'
        elif block.instructions[0][0] == '.word':
            const = block.name
            arr = [instr[1][0] for instr in block.instructions]
            result += f'{const} = (int32_t) ((uint8_t*) malloc({len(arr)}*sizeof(int32_t)) - malloc_0);\n'
            result += f'int32_t array{const}[] = {{{",".join(arr)}}};\n'
            result += f'for(int i=0; i<{len(arr)}; i++) str(&array{const}[i], &{const}, i*4, 4, false, false);\n'

    return result