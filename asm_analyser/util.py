from typing import Container
from basic_block import BasicBlock
from basic_block import Instruction
import arm_translator
import os
import re

FUNC_TEMPLATE = '{return_type} {func_name}(){{\n' \
                '{body}\n' \
                '}}'

float_functions = ['__aeabi_fadd']

instructions_to_filter = ['bx']
branch_instructions = ['bgt', 'blt', 'b']

def compile_asm(file_name: str, optimization: bool) -> None:
    '''Compiles the selected C file to assembler.

    Parameters
    ----------
    file_name : str
        Name of the file.
    optimization: bool
        Specifies whether optimizations should be used.
    '''
    if optimization:
        os.system(
            f'arm-linux-gnueabi-gcc -S -march=armv7ve -marm -O3 ../examples/c_in/{file_name}.c -o ../examples/asm/{file_name}.s')
    else:
        os.system(
            f'arm-linux-gnueabi-gcc -S -march=armv7ve -marm ../examples/c_in/{file_name}.c -o ../examples/asm/{file_name}.s')


def format_C(file_name: str) -> None:
    '''Formats the given C file using astyle for better readability.

    Parameters
    ----------
    file_name : str
        Name of the file to be formatted.
    '''
    os.system(
        f'../astyle --style=allman --suffix=none ../examples/c_out/{file_name}.c')


def create_IR(blocks: list[BasicBlock]) -> list[BasicBlock]:
    '''Creates a the indermediate representation of the instructions.

    Translates some instructions like str and ldr to distringuish them better.

    Parameters
    ----------
    functions : list[BasicBlock]
        The basic block with all its instructions.

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

            # look for constant float values
            if (new_instr[0] == 'mov' and
                    (block.instructions[i+1][1][0] in float_functions or
                    block.instructions[i+2][1][0] in float_functions)):
                if re.match('^-?\d+$', new_instr[1][0]):
                    new_instr[1][0] = _convert_to_float(new_instr[1][0])
                if re.match('^-?\d+$', new_instr[1][1]):
                    new_instr[1][1] = _convert_to_float(new_instr[1][1])

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
                if 'lr' in new_instr[1]:
                    new_instr[1].remove('lr')
                if 'pc' in new_instr[1]:
                    new_instr[1].remove('pc')

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
              'int32_t counter = 0;\n' \
              'int32_t cond_reg;\n\n'
    
    # add the necessary registers as globals
    result += _get_needed_vars(blocks)

    # add the function definitions
    result += _translate_functions(blocks)

    return result

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

            return_type = block.get_return_type()

            if return_type != 'void':
                body += 'return r0;'

            result += FUNC_TEMPLATE.format(
                return_type=return_type,
                func_name=block.name,
                body=body
            )
            result += '\n\n'

    return result

def write_C_file(file_name: str, contents: str) -> None:
    '''Writes all the code into a C-file

    Parameters
    ----------
    file_name : str
        Name of the C-file.
    contents: str
        Contents to be written to the file.
    '''
    with open(f'../examples/c_out/{file_name}.c', 'w') as fs:
        fs.write(contents)

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

def _convert_to_int(mantissa_str: str) -> int:
    '''TODO
    '''
    power_count = -1
    mantissa_int = 0

    for i in mantissa_str:
        mantissa_int += (int(i) * pow(2, power_count))
        power_count -= 1
         
    return (mantissa_int + 1)
    
def _convert_to_float(int_number: str) -> str:
    '''TODO
    '''
    ieee_32 = '{0:032b}'.format(int(int_number))
    sign_bit = int(ieee_32[0])
    exponent_bias = int(ieee_32[1:9], 2)
    exponent_unbias = exponent_bias - 127
    mantissa_str = ieee_32[10:]
    
    mantissa_int = _convert_to_int(mantissa_str)
    return str(pow(-1, sign_bit) * mantissa_int * pow(2, exponent_unbias))