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

        for i, instr in enumerate(block.instructions):
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
    '''TODO
    '''
    # add the header (e.g. global variables)
    result = '#include <stdio.h>\n' \
              '#include <stdint.h>\n' \
              'int32_t stack[200];\n' \
              'int32_t sp = 199, fp = 199;\n' \
              'int32_t lr, pc, cond_reg;\n' \
              'int32_t counter = 0;\n\n'
    
    # add the necessary registers as globals
    result += _get_needed_vars(blocks)

    # add the function definitions
    result += _translate_functions(blocks)

    return result

# TODO: code standards
def _get_return_type(function: BasicBlock, blocks: list[BasicBlock], reg_to_search) -> str:
    '''Determines the return type of a function.

    Parameters
    ----------
    function : BasicBlock
        The function with all its instructions.
    blocks : list[BasicBlock]
        The basic blocks with all their instructions.

    Returns
    TODO
    -------
    str
        The return type of the function.
    '''
    return_type = ''

    for instr in reversed(function.instructions):
        if instr[0] in return_excludes:
            continue

        # check the operand values
        if reg_to_search in instr[1][0]:
            if instr[0] == 'add':
                return reg_to_search, 'int32_t'
            if instr[0] == 'rsblt':
                return reg_to_search, 'int32_t'
            if instr[0] == 'and':
                return reg_to_search, 'int32_t'
            if instr[0] == 'fadd':
                return reg_to_search, 'float'
            if instr[0] == 'mov':
                # value moves from one register to another
                if re.match('^\[?r\d{1}\]?$', instr[1][1]):
                    reg_to_search = instr[1][1]
                # integer is moved into that register
                if re.match('^-?\d+$', instr[1][1]):
                    return reg_to_search, 'int32_t'
                # detects float values (e.g. -2.5)
                if re.match('[+-]?([0-9]*[.])?[0-9]+', instr[1][1]):
                    return reg_to_search, 'float'

        # check sub-blocks
        if instr[0] in branch_instructions:
            sub_block = next(
                (x for x in blocks if x.name == instr[1][0]
                .replace('.','')), None)
            
            if sub_block == None:
                raise ValueError('TODO: ändern')
            
            reg_to_search, return_type = _get_return_type(sub_block, blocks, reg_to_search)

    return reg_to_search, return_type

def _translate_functions(blocks: list[BasicBlock]) -> str:
    '''TODO
    '''
    result = ''

    for block in blocks:
        if block.is_function:
            body = ''
            # translate the instructions in the function body
            for instr in block.instructions:
                body += _translate_instruction(instr)
                if instr[0] in branch_instructions:
                    branch_block = next(
                        (x for x in blocks if x.name == instr[1][0]
                        .replace('.','')), None)

                    if branch_block == None:
                        raise ValueError('TODO: ändern')
                    
                    for instr in branch_block.instructions:
                        body += _translate_instruction(instr)
                    
                    body += '}\n'

            return_type = block.return_type

            if return_type != 'void':
                body += 'return r0;'

            result += FUNC_TEMPLATE.format(
                return_type=return_type,
                func_name=block.name,
                body=body
            )
            result += '\n\n'

    return result

def _get_needed_vars(blocks: list[BasicBlock]) -> str:
    '''TODO
    '''
    needed_vars = set()
    result = ''
    for block in blocks:
        for instr in block.instructions:
            for j, op in enumerate(instr[1]):
                if re.match('^\[?r\d{1}\]?$', op):
                    needed_vars.add(instr[1][j])
    
    for var in needed_vars:
        result += f'int32_t {var};\n'
    
    return result+'\n'

def _translate_instruction(instruction: Instruction) -> str:
    '''TODO
    '''
    operand1 = instruction[1][0]

    try:
        operand2 = instruction[1][1]
    except IndexError:
        operand2 = ''

    try:
        operand3 = instruction[1][2]
    except IndexError:
        operand3 = ''

    return arm_translator.translate(
        instruction[0], operand1, operand2, operand3)