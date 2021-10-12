from basic_block import BasicBlock
from basic_block import Instruction
import arm_translator
import re

FUNC_TEMPLATE = '{return_type} {func_name}(){{\n' \
                '{body}\n' \
                '}}'

instructions_to_filter = ['bx']
branch_instructions = ['bgt', 'blt', 'b']
float_functions = ['__aeabi_fadd']
return_excludes = ['bx', 'ctr', 'str1', 'str2']

def get_return_types(blocks: list[BasicBlock]) -> list[BasicBlock]:
    '''Determines the return types of all functions.
    
    Parameters
    ----------
    blocks : list[BasicBlock]
        The basic blocks with all their instructions.

    Returns
    -------
    list[BasicBlock]
        Same basic blocks, but the functions now have a return type assigned.
    '''
    for i, block in enumerate(blocks):
        if block.is_function:
            _, blocks[i].return_type = _get_return_type(block, blocks, 'r0')

    return blocks

def create_IR(blocks: list[BasicBlock]) -> list[BasicBlock]:
    '''Creates a the indermediate representation of the instructions.

    Parameters
    ----------
    blocks : list[BasicBlock]
        The basic blocks with all their instructions.

    Returns
    -------
    list[BasicBlock]
        List of basic blocks with the instrucitons.
    '''
    new_blocks = []

    # TODO: vielleicht noch die len(instruction) prüfen
    for block in blocks:
        new_block = BasicBlock()
        new_block.name = block.name
        new_block.is_function = block.is_function

        for instr in block.instructions:
            new_instr = instr

            # change representation of ldr, str, push, pop
            if new_instr[0] == 'ldr':
                if re.match('\[(.*?)\]', new_instr[1][1]):
                    new_instr = ('ldr1', new_instr[1][:])
                elif ']' not in new_instr[1][1]:
                    new_instr = ('ldr2', new_instr[1][:])

            if new_instr[0] == 'str':
                if '!' in new_instr[1][2]:
                    new_instr = ('str1', new_instr[1][:])
                else:
                    new_instr = ('str2', new_instr[1][:])

            if new_instr[0] == 'push' or new_instr[0] == 'pop':
                new_instr = (f'{new_instr[0]}{len(new_instr[1])}',
                             new_instr[1][:])

            # change representation float operation
            if new_instr[0] == 'bl' and new_instr[1][0] in float_functions:
                if new_instr[1][0] == '__aeabi_fadd':
                    new_instr = ('fadd', ['r0', 'r0', 'r1'])

            for j in range(len(new_instr[1])):
                new_instr[1][j] = re.sub('[\\[\\]!]', '', new_instr[1][j])

            # divide the pointer increments/decrements by 4
            if 'sp' in new_instr[1] or 'fp' in new_instr[1]:
                for j in range(len(new_instr[1])):
                    if re.match('^-?\d+$', new_instr[1][j]):
                        new_instr[1][j] = str(int(new_instr[1][j])//4)

            if new_instr[0] not in instructions_to_filter:
                new_block.instructions.append(new_instr)

        new_blocks.append(new_block)

    return new_blocks

def translate_blocks(blocks: list[BasicBlock]) -> str:
    '''Generates the C code by translating all the blocks.

    Parameters
    ----------
    blocks : list[BasicBlock]
        The functions and labeled blocks with all their instructions.

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
              'int32_t counter = 0;\n' \
              'reg lr, pc, cond_reg;\n\n'

    # add the necessary registers as globals
    result += _get_needed_vars(blocks)

    # add the function definitions
    result += _translate_functions(blocks)

    return result

def _get_return_type(function: BasicBlock, blocks: list[BasicBlock],
                     return_reg) -> str:
    '''Determines the return type of a function.

    Parameters
    ----------
    function : BasicBlock
        The function with all its instructions.
    blocks : list[BasicBlock]
        The basic blocks with all their instructions.
    return_reg : str
        Name of the register that contains the return value.

    Returns
    -------
    str
        The return type of the function.
    '''
    return return_reg, 'reg'
    return_type = ''

    for instr in reversed(function.instructions):
        if instr[0] in return_excludes:
            continue

        # check the operand values
        if return_reg in instr[1][0]:
            if instr[0] == 'add':
                return return_reg, 'int32_t'
            if instr[0] == 'rsblt':
                return return_reg, 'int32_t'
            if instr[0] == 'and':
                return return_reg, 'int32_t'
            if instr[0] == 'fadd':
                return return_reg, 'float'
            if instr[0] == 'mov':
                # value moves from one register to another
                if re.match('^\[?r\d{1}\]?$', instr[1][1]):
                    return_reg = instr[1][1]
                # integer is moved into that register
                if re.match('^-?\d+$', instr[1][1]):
                    return return_reg, 'int32_t'
                # detects float values (e.g. -2.5)
                if re.match('[+-]?([0-9]*[.])?[0-9]+', instr[1][1]):
                    return return_reg, 'float'

        # check sub-blocks
        if instr[0] in branch_instructions:
            sub_block = next(
                (x for x in blocks if x.name == instr[1][0]
                .replace('.','')), None)
            
            if sub_block == None:
                raise ValueError('TODO: ändern')
            
            return_reg, return_type = _get_return_type(sub_block, blocks,
                                                       return_reg)

    return return_reg, return_type

def _translate_functions(blocks: list[BasicBlock]) -> str:
    '''TODO
    '''
    result = ''

    for block in blocks:
        if block.is_function:
            body = _translate_function(block, blocks)

            if block.return_type != 'void':
                body += 'return r0;'
            
            result += FUNC_TEMPLATE.format(
                return_type=block.return_type,
                func_name=block.name,
                body=body
            )
            result += '\n\n'

    return result

def _translate_function(block: BasicBlock, blocks: list[BasicBlock]) -> str:
    '''TODO
    '''
    body = ''
    skip_next = 0

    for i, instr in enumerate(block.instructions):
        if skip_next > 0:
            skip_next -= 1
            continue

        body += _translate_instruction(instr)

        if instr[0] in branch_instructions:
            branch_block = next((x for x in blocks if x.name == instr[1][0]
                                .replace('.','')), None)
            
            if branch_block == None:
                raise ValueError('TODO: ändern')    

            body += _translate_function(branch_block, blocks)

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
            
            if else_ctr > 0:
                tmp_block = BasicBlock()
                tmp_block.instructions = block.instructions[i+1:i+else_ctr+1]
                skip_next = else_ctr

                body += 'else{\n'
                body += _translate_function(tmp_block, blocks)
                body += '}\n'

    return body

def _get_needed_vars(blocks: list[BasicBlock]) -> str:
    '''Determines the global variables that need to be created.

    Parameters
    ----------
    blocks : list[BasicBlock]
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
    op1 = instruction[1][0]

    try:
        op2 = instruction[1][1]
    except IndexError:
        op2 = ''

    try:
        op3 = instruction[1][2]
    except IndexError:
        op3 = ''

    return arm_translator.translate(instruction[0], op1, op2, op3)