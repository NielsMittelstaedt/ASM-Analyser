from code_block import CodeBlock
from basic_block import BasicBlock
import re

instructions_to_filter = ['bx']
branch_instructions = ['bgt', 'blt', 'b', 'bl']
float_translations = {
    '__aeabi_fadd': 'fadd',
    '__aeabi_fsub': 'fsub',
    '__aeabi_fmul': 'fmul',
    '__aeabi_fdiv': 'fdiv'
}

def create_IR(blocks: list[CodeBlock]) -> list[CodeBlock]:
    '''Creates a the indermediate representation of the instructions.

    Parameters
    ----------
    blocks : list[CodeBlock]
        The code blocks with all their instructions.

    Returns
    -------
    list[CodeBlock]
        List of code blocks with the instrucitons.
    '''
    new_blocks = []

    # TODO: vielleicht noch die len(instruction) prüfen
    for block in blocks:
        new_block = CodeBlock()
        new_block.name = block.name
        new_block.is_function = block.is_function

        for instr in block.instructions:
            # change representation of ldr, str, push, pop
            if instr[0] == 'ldr':
                if re.match('\[(.*?)\]', instr[1][1]):
                    instr = ('ldr1', instr[1][:])
                elif ']' not in instr[1][1]:
                    instr = ('ldr2', instr[1][:])

            if instr[0] == 'str':
                if '!' in instr[1][2]:
                    instr = ('str1', instr[1][:])
                else:
                    instr = ('str2', instr[1][:])

            # change representation float operations
            if instr[0] == 'bl' and instr[1][0] in float_translations:
                instr = (float_translations[instr[1][0]], ['r0', 'r0', 'r1'])

            for j in range(len(instr[1])):
                instr[1][j] = re.sub('[\\[\\]!]', '', instr[1][j])

            # divide the pointer increments/decrements by 4
            if 'sp' in instr[1] or 'fp' in instr[1]:
                for j in range(len(instr[1])):
                    if re.match('^-?\d+$', instr[1][j]):
                        instr[1][j] = str(int(instr[1][j])//4)

            if instr[0] not in instructions_to_filter:
                new_block.instructions.append(instr)

        new_blocks.append(new_block)

    return new_blocks


def get_return_types(blocks: list[CodeBlock]) -> list[CodeBlock]:
    '''Determines the return types of all functions.

    Parameters
    ----------
    blocks : list[CodeBlock]
        The code blocks with all their instructions.

    Returns
    -------
    list[CodeBlock]
        Same code blocks, but the functions now have a return type assigned.
    '''
    for i, block in enumerate(blocks):
        if block.is_function:
            _, blocks[i].return_type = _get_return_type(block, blocks, 'r0')

    return blocks


def get_basic_blocks(blocks: list[CodeBlock]) -> list[BasicBlock]:
    '''TODO
    '''
    basic_blocks = []

    # create one or more basic blocks for each code block
    for code_block in blocks:
        basic_block = BasicBlock()
        basic_block.parent_block = code_block.name
        skip_next = 0

        # loop over the instructions and look for separating instructions
        for i, instr in enumerate(code_block.instructions):
            if skip_next > 0:
                skip_next -= 1
                continue

            basic_block.instructions.append(instr)

            # add basic block to list if branch instruction or end of block occurs
            if (i == len(code_block.instructions)-1 or
                    instr[0] in branch_instructions):
                basic_blocks.append(basic_block)
                basic_block = BasicBlock()
                basic_block.parent_block = code_block.name

                # create another basic block for the else part
                if instr[0] in branch_instructions and instr[0] != 'bl':
                    else_ctr = 0
                    for j in range(i+1, len(code_block.instructions)):
                        if code_block.instructions[j][0] in branch_instructions:
                            break
                        if j == len(code_block.instructions)-1:
                            else_ctr = 0
                        else_ctr += 1
                    if else_ctr > 0:
                        basic_block.instructions = code_block.instructions[i+1:i+else_ctr+1]
                        basic_blocks.append(basic_block)
                        basic_block = BasicBlock()
                        basic_block.parent_block = code_block.name
                        skip_next = else_ctr

    return basic_blocks


def _get_return_type(function: CodeBlock, blocks: list[CodeBlock],
                     return_reg) -> str:
    '''Determines the return type of a function.

    Parameters
    ----------
    function : CodeBlock
        The function with all its instructions.
    blocks : list[CodeBlock]
        The code blocks with all their instructions.
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
                 .replace('.', '')), None)

            if sub_block == None:
                raise ValueError('TODO: ändern')

            return_reg, return_type = _get_return_type(sub_block, blocks,
                                                       return_reg)

    return return_reg, return_type
