from code_block import CodeBlock
from basic_block import BasicBlock
import re

branch_instructions = ['bgt', 'blt', 'b', 'bl']

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

    for block in blocks:
        new_block = CodeBlock()
        new_block.name = block.name
        new_block.is_function = block.is_function
        new_block.is_code = block.is_code

        for instr in block.instructions:
            # translate ldr,str,ldrb,strb
            if re.match('(^ldr.*)|(^str.*)', instr[0]):
                # unify argument length to 3
                if len(instr[1]) == 2:
                    instr[1][1].replace('[','').replace(']','')
                    instr = (instr[0], [*instr[1], '0'])
                
                # look for index updates (exclamation mark)
                if '!' in instr[1][2]:
                    instr = (instr[0]+'1', instr[1])
                else:
                    instr = (instr[0]+'0', instr[1])
                
                # look for post-indexed addressing
                if re.match('\[(.*?)\]', instr[1][1]):
                    instr = (instr[0]+'1', instr[1])
                else:
                    instr = (instr[0]+'0', instr[1])
                
            # remove square brackets and exclamation mark
            if not re.match('^\.(word|ascii)$', instr[0]):
                for j in range(len(instr[1])):
                    instr[1][j] = re.sub('[\\[\\]!\.]', '', instr[1][j])

            # replace specifiers like :lower16: and :upper16: and LANCHOR
            for i, op in enumerate(instr[1]):
                if 'LANCHOR' in op:
                    instr[1][i] = instr[1][i].replace('ANCHOR', 'C')
                if ':lower16:' in op:
                    val = instr[1][i].replace(':lower16:', '')
                    instr[1][i] = f'({val} & 0xffff)'
                if ':upper16:' in op:
                    val = instr[1][i].replace(':upper16:', '')
                    instr[1][i] = f'((uint32_t){val} >> 16)'

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
            blocks[i].return_type = 'void'

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