'''Provides methods for further processing of parsed ARM assembly.
'''
import re
import copy
from typing import List
from asm_analyser import processor
from asm_analyser.blocks.code_block import CodeBlock
from asm_analyser.blocks.basic_block import BasicBlock

COND_CODES = {
    'eq', 'ne', 'ge', 'gt', 'le', 'lt', 'ls', 'cs',
    'cc', 'hi', 'mi', 'pl', 'al', 'nv', 'vs', 'vc'
}


class ArmProcessor(processor.Processor):
    '''Implements the Processor Class for ARM assembly.
    '''

    @staticmethod
    def create_ir(blocks: List[CodeBlock]) -> List[CodeBlock]:
        new_blocks = []

        for block in blocks:
            new_block = copy.deepcopy(block)
            new_block.instructions = []

            for instr in block.instructions:
                if re.match('(^ldr.*)|(^str.*)', instr[1]):
                    byte_amount = '4'
                    update = ''
                    post_index = ''
                    signed = '0'

                    # unify argument length to 3
                    if len(instr[2]) == 2:
                        instr = (*instr[:2], [*instr[2], '0'])

                    # look for index updates (exclamation mark)
                    if '!' in instr[2][2]:
                        update = '1'
                    else:
                        update = '0'

                    # look for post-indexed addressing
                    if re.match(
                            r'\[(.*?)\]',
                            instr[2][1]) and instr[2][2] != '0':
                        post_index = '1'
                    else:
                        post_index = '0'

                    opcode = instr[1]

                    if opcode[-2:] in COND_CODES:
                        opcode = opcode[:-2]

                    if 'ldrb' in opcode and opcode[-2:] not in COND_CODES:
                        byte_amount = '1'
                        instr = (
                            instr[0], instr[1].replace(
                                'ldrb', 'ldr'), instr[2])
                    elif 'ldrsb' in opcode and opcode[-2:] not in COND_CODES:
                        byte_amount = '1'
                        signed = '1'
                        instr = (
                            instr[0], instr[1].replace(
                                'ldrsb', 'ldr'), instr[2])
                    elif 'ldrh' in opcode and opcode[-2:] not in COND_CODES:
                        byte_amount = '2'
                        instr = (
                            instr[0], instr[1].replace(
                                'ldrh', 'ldr'), instr[2])
                    elif 'ldrsh' in opcode and opcode[-2:] not in COND_CODES:
                        byte_amount = '2'
                        signed = '1'
                        instr = (
                            instr[0], instr[1].replace(
                                'ldrsh', 'ldr'), instr[2])
                    elif 'ldrd' in opcode and opcode[-2:] not in COND_CODES:
                        byte_amount = '8'
                        instr = (
                            instr[0], instr[1].replace(
                                'ldrd', 'ldr'), instr[2])
                    elif 'strb' in opcode and opcode[-2:] not in COND_CODES:
                        byte_amount = '1'
                        instr = (
                            instr[0], instr[1].replace(
                                'strb', 'str'), instr[2])
                    elif 'strh' in opcode and opcode[-2:] not in COND_CODES:
                        byte_amount = '2'
                        instr = (
                            instr[0], instr[1].replace(
                                'strh', 'str'), instr[2])
                    elif 'strd' in opcode and opcode[-2:] not in COND_CODES:
                        byte_amount = '8'
                        instr = (
                            instr[0], instr[1].replace(
                                'strd', 'str'), instr[2])

                    instr = (
                        instr[0],
                        f'{instr[1]}{byte_amount}{update}{post_index}{signed}',
                        instr[2])

                elif re.match('(^ldm.*)|(^stm.*)', instr[1]):
                    if 'ldmia' in instr[1]:
                        instr = (
                            instr[0], instr[1].replace(
                                'ldmia', 'ldm'), instr[2])
                    elif 'stmia' in instr[1]:
                        instr = (
                            instr[0], instr[1].replace(
                                'stmia', 'stm'), instr[2])

                    if '!' in instr[2][0]:
                        instr = (instr[0], instr[1] + '1', instr[2])
                    else:
                        instr = (instr[0], instr[1] + '0', instr[2])

                # remove square brackets and exclamation mark
                if not re.match(r'^\.(word|ascii)$', instr[1]):
                    for j in range(len(instr[2])):
                        instr[2][j] = re.sub(r'[\\[\\]!\.]', '', instr[2][j])

                # replace specifiers like :lower16: and :upper16: and LANCHOR
                for i, op in enumerate(instr[2]):
                    if 'LANCHOR' in op:
                        instr[2][i] = instr[2][i].replace(
                            'ANCHOR', 'C').replace('.', '')
                    if ':lower16:' in op:
                        val = instr[2][i].replace(':lower16:', '')
                        instr[2][i] = f'({val} & 0xffff)'
                    if ':upper16:' in op:
                        val = instr[2][i].replace(':upper16:', '')
                        instr[2][i] = f'((uint32_t){val} >> 16)'

                new_block.instructions.append(instr)

            if new_block.instructions:
                new_blocks.append(new_block)

        return new_blocks

    @staticmethod
    def get_basic_blocks(blocks: List[CodeBlock]) -> List[BasicBlock]:
        basic_blocks = []

        # create one or more basic blocks for each code block
        for code_block in blocks:
            if code_block.is_code:

                basic_block = BasicBlock()
                basic_block.parent_block = code_block.name

                # loop over the instructions and look for separating
                # instructions
                for i, instr in enumerate(code_block.instructions):
                    basic_block.instructions.append(instr)

                    # add basic block to list if branch instruction or end of
                    # block occurs
                    if (i == len(code_block.instructions)-1
                            or re.match(
                                r'^((b)|(bl)|(bx))(?:eq|ne|cs|hs|cc|lo|mi|pl|vs|vc|hi|ls|ge|lt|gt|le|al)*$',
                                instr[1])
                            or (re.match(
                                '(^ldr.*)|(^ldm.*)|(^pop.*)',
                                instr[1]) and 'pc' in instr[2])):
                        basic_blocks.append(basic_block)
                        basic_block = BasicBlock()
                        basic_block.parent_block = code_block.name

        return basic_blocks
