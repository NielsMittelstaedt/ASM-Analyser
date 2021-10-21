from basic_block import BasicBlock
from code_block import CodeBlock
from code_block import Instruction
import counting
import arm_translator
import re

FUNC_TEMPLATE = '{return_type} {func_name}(){{\n' \
                '{body}\n' \
                '}}'

instructions_to_filter = ['bx']
branch_instructions = ['bgt', 'blt', 'b']
float_functions = ['__aeabi_fadd']
return_excludes = ['bx', 'ctr', 'str1', 'str2']


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
    # add the header (e.g. global variables)
    result = '#include <stdio.h>\n' \
             '#include <stdint.h>\n\n' \
             'typedef union {\n' \
             'int32_t i;\n' \
             'float f;\n' \
             '} reg;\n\n' \
             'int32_t stack[200];\n' \
             'int32_t sp = 199, fp = 199;\n' \
             'int32_t cond_reg;\n' \
             'reg lr, pc;\n\n' \

    # add the necessary registers as globals
    result += _get_needed_vars(code_blocks)

    # add the counter variables
    result += counting.get_counter_vars(basic_blocks)

    # add the function definitions
    result += _translate_functions(code_blocks, basic_blocks)

    return result

def _translate_functions(code_blocks: list[CodeBlock],
                         basic_blocks: list[BasicBlock]) -> str:
    '''TODO
    '''
    result = ''

    for block in code_blocks:
        if block.is_function:
            body = _translate_function(block, code_blocks, basic_blocks)

            if block.return_type != 'void':
                body += 'return r0;'
            
            result += FUNC_TEMPLATE.format(
                return_type=block.return_type,
                func_name=block.name,
                body=body
            )
            result += '\n\n'

    return result

def _translate_function(block: CodeBlock, code_blocks: list[CodeBlock],
                    basic_blocks: list[BasicBlock]) -> str:
    '''TODO
    '''
    body = ''
    i = 0

    while i < len(block.instructions):
        instr = block.instructions[i]

        if instr[0] not in branch_instructions: 
            body += _translate_instruction(instr)
        else:
            if (i < len(block.instructions)-1 and
                    block.instructions[i+1][0] == 'ctr'):
                body += _translate_instruction(block.instructions[i+1])
                block.instructions.pop(i+1)
            
            body += _translate_instruction(instr)
            
            branch_block = next((x for x in code_blocks if x.name == instr[1][0]
                                .replace('.','')), None)

            if branch_block == None:
                raise ValueError('TODO: ändern')

            body += _translate_function(branch_block, code_blocks, basic_blocks)

            if instr[0] != 'b':
                body += '}\n'

            # look for the else part
            else_ctr = 0
            for j in range(i+1, len(block.instructions)):
                if block.instructions[j][0] in branch_instructions:
                    break
                if j == len(block.instructions) - 1:
                    else_ctr = 0
                else_ctr += 1
            
            if else_ctr == 1 and block.instructions[i+1][0] == 'ctr':
                continue

            if else_ctr > 0:
                tmp_block = CodeBlock()
                tmp_block.instructions = block.instructions[i+1:i+else_ctr+1]
                i += else_ctr

                body += 'else{\n'
                body += _translate_function(tmp_block, code_blocks, basic_blocks)
                body += '}\n'

        i += 1

    return body


#def _translate_function(block: CodeBlock, code_blocks: list[CodeBlock],
#                        basic_blocks: list[BasicBlock]) -> str:
#    '''TODO
#    '''
#    body = ''
#    skip_next = 0
#
#    for i, instr in enumerate(block.instructions):
#        if skip_next > 0:
#            skip_next -= 1
#            continue
#        
#        if instr[0] not in branch_instructions:
#            body += _translate_instruction(instr)
#        else:
#            if block.instructions[i+1][0] == 'ctr':
#                body += _translate_instruction(block.instructions[i+1])
#                skip_next += 1
#            body += _translate_instruction(instr)
#
#            branch_block = next((x for x in code_blocks if x.name == instr[1][0]
#                                .replace('.','')), None)
#            
#            if branch_block == None:
#                raise ValueError('TODO: ändern')    
#
#            body += _translate_function(branch_block, code_blocks, basic_blocks)
#
#            if instr[0] != 'b':
#                body += '}\n'
#
#            # look for the else part
#            else_ctr = 0
#            for j in range(i+1, len(block.instructions)):
#                if block.instructions[j][0] in branch_instructions:
#                    break
#                if j == len(block.instructions) - 1:
#                    else_ctr = 0
#                else_ctr += 1
#            
#            if else_ctr == 1 and block.instructions[i+1][0] == 'ctr':
#                continue
#
#            if else_ctr > 0:
#                tmp_block = CodeBlock()
#                tmp_block.instructions = block.instructions[i+1:i+else_ctr+1]
#                skip_next += else_ctr
#
#                body += 'else{\n'
#                body += _translate_function(tmp_block, code_blocks, basic_blocks)
#                body += '}\n'
#
#    return body
#
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
    needed_vars = set()
    result = ''
    for block in blocks:
        for instr in block.instructions:
            for j, op in enumerate(instr[1]):
                if re.match('^\[?r\d{1}\]?$', op):
                    needed_vars.add(instr[1][j])
    
    for var in needed_vars:
        result += f'reg {var};\n'
    
    return result+'\n'

def _translate_instruction(instruction: Instruction) -> str:
    '''TODO
    '''

    return arm_translator.translate(instruction[0], *instruction[1])