from function import Function
from function import Instruction
import arm_translator
import os
import re

FUNC_TEMPLATE = '{return_type} {func_name}(){{\n' \
                '{body}\n' \
                '}}'

float_functions = ['__aeabi_fadd']

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


def create_IR(functions: list[Function]) -> list[Function]:
    '''Creates a the indermediate representation of the instructions.

    Translates some instructions like str and ldr to distringuish them better.

    Parameters
    ----------
    functions : list[Function]
        The functions with all its instructions.

    Returns
    -------
    list[Function]
        List of functions with the instrucitons.
    '''
    new_functions = []

    # TODO: vielleicht noch die len(instruction) prüfen
    for function in functions:
        new_func = Function()
        new_func.name = function.name

        for i, instruction in enumerate(function.instructions):
            new_instr = instruction

            # look for constant float values
            if (new_instr[0] == 'mov' and
                    (function.instructions[i+1][1][0] in float_functions or
                    function.instructions[i+2][1][0] in float_functions)):
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

            new_func.instructions.append(new_instr)

        new_functions.append(new_func)

    return new_functions


def translate_functions(functions: list[Function]) -> str:
    '''TODO'''
    result = ''

    # add the header (e.g. global variables)
    result += '#include <stdio.h>\n' \
              '#include <stdint.h>\n' \
              'int32_t stack[200];\n' \
              'int32_t sp = 199, fp = 199;\n' \
              'int32_t counter = 0;\n\n'

    # add the necessary registers as globals
    result += _get_needed_vars(functions)

    # add the function definitions
    for function in functions:
        body = _translate_instructions(function.instructions)
        return_type = function.get_return_type()

        if return_type != 'void':
            body += 'return r0;'

        result += FUNC_TEMPLATE.format(
            return_type=return_type,
            func_name=function.name,
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

def _get_needed_vars(functions: list[Function]) -> str:
    '''TODO
    '''
    needed_vars = set()
    result = ''
    for function in functions:
        for instr in function.instructions:
            for j, op in enumerate(instr[1]):
                if re.match('^\[?r\d{1}\]?$', op):
                    needed_vars.add(instr[1][j])
    
    for var in needed_vars:
        result += f'int32_t {var};\n'
    
    return result+'\n'

def _translate_instructions(instructions: list[Instruction]) -> str:
    '''TODO
    '''
    translations = []

    for instruction in instructions:
        if 'bx' in instruction[0]:
            continue

        operand1 = instruction[1][0]

        try:
            operand2 = instruction[1][1]
        except IndexError:
            operand2 = ''

        try:
            operand3 = instruction[1][2]
        except IndexError:
            operand3 = ''

        translations.append(arm_translator.translate(
            instruction[0], operand1, operand2, operand3))

    return ''.join(translations)

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