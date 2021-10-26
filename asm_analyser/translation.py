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
            result += _get_needed_vars(code_blocks)
        elif 'COUNTERS' in line:
            # add the counter variables
            result += counting.get_counter_vars(basic_blocks)
        elif 'AUXFUNCTIONS' in line:
            # add the necessary auxiliary functions
            result += auxiliary_functions.get_auxiliary_functions(code_blocks)
        elif 'TRANSLATIONS' in line:
            # add the function definitions
            result += _translate_functions(code_blocks, basic_blocks)
        else:
            result += line

    return result

def _translate_functions(code_blocks: list[CodeBlock],
                         basic_blocks: list[BasicBlock]) -> str:
    '''TODO
    '''
    result = ''
    i = 0

    while i < len(code_blocks):
        block = code_blocks[i]
        if block.is_function:
            body = _translate_function(block,code_blocks, basic_blocks)
            
            # check for other labels
            j = i+1
            while (j < len(code_blocks) and not code_blocks[j].is_function):
                body += code_blocks[j].name+':\n'
                body += _translate_function(code_blocks[j], code_blocks,
                                            basic_blocks)
                j += 1

            if block.return_type != 'void' and 'return' not in body[-20:]:
                body += 'return r0;'

            # fill the function template
            result += FUNC_TEMPLATE.format(
                return_type=block.return_type,
                func_name=block.name,
                body=body
            )
            result += '\n\n'
        
        i += 1
    
    return result

def _translate_function(block: CodeBlock, code_blocks: list[CodeBlock],
                    basic_blocks: list[BasicBlock]) -> str:
    '''TODO
    '''
    body = ''
    i = 0

    # add stack initialization to main method
    if block.name == 'main':
        body += 'malloc_start();\n'

    for instr in block.instructions:
        body += _translate_instruction(instr)

    return body

def _get_needed_vars(blocks: list[CodeBlock]) -> str:
    '''Determines the global variables that need to be created.

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
                if re.match('^\[?r\d{1}\]?$', op):
                    needed_vars.add(instr[1][j])
    
    if len(needed_vars) == 0:
        return ''

    result = 'reg '
    result += ', '.join(needed_vars)
    
    return result+';\n'

def _translate_instruction(instruction: Instruction) -> str:
    '''TODO
    '''
    if (instruction[0] == 'bl' and instruction[1][0] in
            auxiliary_functions.call_dict):
        return auxiliary_functions.call_dict[instruction[1][0]]
    return arm_translator.translate(instruction[0], *instruction[1])

