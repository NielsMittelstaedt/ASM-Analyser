from basic_block import BasicBlock
from code_block import CodeBlock
from code_block import Instruction
import counting
import auxiliary_functions
import arm_translator
import re

FUNC_TEMPLATE = '{return_type} {func_name}(){{\n' \
                '{body}\n' \
                '}}'

def translate_blocks(code_blocks: list[CodeBlock],
                     basic_blocks: list[BasicBlock]) -> str:
    '''Generates the C code by translating all the blocks.

    Parameters
    ----------
    code_blocks : list[CodeBlock]
        The functions and labeled blocks with all their instructions.
    basic_blocks: list[BasicBlock]
        The code_blocks that are split into basic blocks.

    Returns
    -------
    str
        The resulting C code.
    '''
    # fill the template file with the variable parts
    result = ''

    f = open('template.c', 'r')

    for line in f.readlines():
        if 'REGISTERS' in line:
            # add the necessary registers as globals
            result += _get_needed_regs(code_blocks)
        elif 'LOCALDEFS' in line:
            # add the variables for the arm local constants
            result += _get_needed_consts(code_blocks)
        elif 'COUNTERS' in line:
            # add the counter variables
            result += counting.get_counter_vars(basic_blocks)
        elif 'LOCALCONSTANTS' in line:
            # assign values to the arm local constants
            result += _get_constant_defs(code_blocks)
        elif 'AUXFUNCTIONS' in line:
            # add the necessary auxiliary functions
            result += auxiliary_functions.get_auxiliary_functions(code_blocks)
        elif 'TRANSLATIONS' in line:
            # add the translations of the code blocks
            result += _translate_blocks(code_blocks)
        else:
            result += line

    return result

def _translate_blocks(blocks: list[CodeBlock]) -> str:
    '''TODO
    '''
    result = ''

    main_block = next((x for x in blocks if x.name == 'main'), None)

    if main_block == None:
        raise ValueError('TODO: ändern')

    result += main_block.name+':\n'
    result += _translate_block(main_block, blocks)

    for block in blocks:
        if block.is_code and block.name != 'main':
            result += block.name+':\n'
            result += _translate_block(block, blocks)

    return result

def _translate_block(block: CodeBlock, blocks: list[CodeBlock]) -> str:
    '''TODO
    '''
    result = ''

    for instr in block.instructions:
        result += _translate_instruction(instr, blocks)

    return result

def _get_needed_regs(blocks: list[CodeBlock]) -> str:
    '''Determines the global variables that need to be created as registers.

    Parameters
    ----------
    blocks : list[CodeBlock]
        All the labeled blocks with their instructions.
    
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

def _get_needed_consts(blocks: list[CodeBlock]) -> str:
    '''TODO
    '''
    contants = [block.name for block in blocks if not block.is_code]

    if len(contants) <= 0:
        return ''
    
    result = 'int32_t '
    result += ', '.join(contants)
    return result + ';\n'

def _get_constant_defs(blocks: list[CodeBlock]) -> str:
    '''TODO
    '''
    blocks = [block for block in blocks if not block.is_code]
    result = ''

    for block in blocks:
        # distinguish between string and array
        if block.instructions[0][0] == '.ascii':
            const = block.name
            string = block.instructions[0][1][0]
            result += f'{const} = (int32_t) ((char*) malloc({len(string)}) - malloc_0);\n'
            result += f'strcpy(malloc_0+{const}, {block.instructions[0][1][0]});\n\n'
        elif block.instructions[0][0] == '.word':
            const = block.name
            arr = [instr[1][0] for instr in block.instructions]
            result += f'{const} = (int32_t) ((char*) malloc({len(arr)}*sizeof(int32_t)) - malloc_0);\n'
            result += f'int32_t array{const}[] = {{{",".join(arr)}}};\n'
            result += f'for(int i=0; i<{len(arr)}; i++) str(&array{const}[i], &{const}, i*4, false, false, false);\n'

    return result

def _translate_instruction(instruction: Instruction,
                           blocks: list[CodeBlock]) -> str:
    '''TODO
    '''
    if instruction[1][0] in auxiliary_functions.call_dict:
        if instruction[0] == 'bl' or instruction[0] == 'b':
            return auxiliary_functions.call_dict[instruction[1][0]]
    else:
        if instruction[0] == 'bl':
            pass

    return arm_translator.translate(instruction[0], *instruction[1])