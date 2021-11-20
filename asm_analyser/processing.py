from blocks.code_block import CodeBlock
from blocks.basic_block import BasicBlock
import re
import copy

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
        new_block = copy.deepcopy(block)
        new_block.instructions = []

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

def get_basic_blocks(blocks: list[CodeBlock]) -> list[BasicBlock]:
    '''TODO
    '''
    basic_blocks = []

    # create one or more basic blocks for each code block
    for code_block in blocks:
        if code_block.is_code:

            basic_block = BasicBlock()
            basic_block.parent_block = code_block.name

            # loop over the instructions and look for separating instructions
            for i, instr in enumerate(code_block.instructions):
                basic_block.instructions.append(instr)

                # add basic block to list if branch instruction or end of block occurs
                if (i == len(code_block.instructions)-1 or
                        re.match('^((b)|(bl)|(bx))(?:eq|ne|cs|hs|cc|lo|mi|pl|vs|vc|hi|ls|ge|lt|gt|le|al)*$', instr[0])):
                    basic_blocks.append(basic_block)
                    basic_block = BasicBlock()
                    basic_block.parent_block = code_block.name

    return basic_blocks

def set_last_block(blocks: list[CodeBlock]) -> list[CodeBlock]:
    '''TODO
    '''
    last_idx = next((i for i, item in enumerate(blocks)
                     if item.name == 'main'), -1)

    for i in range(last_idx+1, len(blocks)):
        if not blocks[i].is_function and blocks[i].is_code:
            last_idx = i
    
    blocks[last_idx].is_last = True

    return blocks

def get_part_functions(blocks: list[CodeBlock]) -> set[str]:
    '''TODO
    '''
    part_functions = set()
    for block in blocks:
        func_name = re.sub('part\d+$', '', block.name)
        if func_name != block.name:
            part_functions.add(func_name)

    return part_functions