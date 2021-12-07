import re
import copy
from asm_analyser import processor
from asm_analyser.blocks.code_block import CodeBlock
from asm_analyser.blocks.basic_block import BasicBlock

class Processor(processor.Processor):

    @staticmethod
    def create_IR(blocks: list[CodeBlock]) -> list[CodeBlock]:
        new_blocks = []

        for block in blocks:
            new_block = copy.deepcopy(block)
            new_block.instructions = []

            for instr in block.instructions:
                # translate ldr,str,ldrb,strb
                if re.match('(^ldr.*)|(^str.*)', instr[1]):
                    # unify argument length to 3
                    if len(instr[2]) == 2:
                        instr = (*instr[:2], [*instr[2], '0'])
                    
                    # look for index updates (exclamation mark)
                    if '!' in instr[2][2]:
                        instr = (instr[0], instr[1]+'1', instr[2])
                    else:
                        instr = (instr[0], instr[1]+'0', instr[2])
                    
                    # look for post-indexed addressing
                    if re.match('\[(.*?)\]', instr[2][1]) and instr[2][2] != '0':
                        instr = (instr[0], instr[1]+'1', instr[2])
                    else:
                        instr = (instr[0], instr[1]+'0', instr[2])

                if re.match('(^ldm.*)|(^stm.*)', instr[1]):
                    if '!' in instr[2][0]:
                        instr = (instr[0], instr[1]+'01', instr[2])
                    else:
                        instr = (instr[0], instr[1]+'00', instr[2])
                    
                # remove square brackets and exclamation mark
                if not re.match('^\.(word|ascii)$', instr[1]):
                    for j in range(len(instr[2])):
                        instr[2][j] = re.sub('[\\[\\]!\.]', '', instr[2][j])

                # replace specifiers like :lower16: and :upper16: and LANCHOR
                for i, op in enumerate(instr[2]):
                    if 'LANCHOR' in op:
                        instr[2][i] = instr[2][i].replace('ANCHOR', 'C').replace('.','')
                    if ':lower16:' in op:
                        val = instr[2][i].replace(':lower16:', '')
                        instr[2][i] = f'({val} & 0xffff)'
                    if ':upper16:' in op:
                        val = instr[2][i].replace(':upper16:', '')
                        instr[2][i] = f'((uint32_t){val} >> 16)'

                new_block.instructions.append(instr)

            if len(new_block.instructions):
                new_blocks.append(new_block)

        return new_blocks

    @staticmethod
    def get_basic_blocks(blocks: list[CodeBlock]) -> list[BasicBlock]:
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
                            re.match('^((b)|(bl)|(bx))(?:eq|ne|cs|hs|cc|lo|mi|pl|vs|vc|hi|ls|ge|lt|gt|le|al)*$', instr[1])):
                        basic_blocks.append(basic_block)
                        basic_block = BasicBlock()
                        basic_block.parent_block = code_block.name

        return basic_blocks