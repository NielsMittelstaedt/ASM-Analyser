from function import Function
import arm_translator
import os
import re

Instruction = tuple[str, list[str]]

FUNC_TEMPLATE = '{return_type} {func_name}({params}){{\n' \
                '    {body}\n' \
                '}}'


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
    os.system(f'../astyle --style=allman --suffix=none ../examples/c_out/{file_name}.c')

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

    #TODO: vielleicht noch die len(instructiojn) prüfen
    for function in functions:
        new_func = Function()
        new_func.name = function.name

        for instruction in function.instructions:
            new_instr = instruction

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

            for i in range(len(new_instr[1])):
                new_instr[1][i] = re.sub('[\\[\\]!]', '', new_instr[1][i])

            new_func.instructions.append(new_instr)
        
        new_functions.append(new_func)

    return new_functions


def translate_blocks(functions: list[Function]) -> str:
    '''TODO'''
    result = ''

    for function in functions:
        body = _translate_instructions(function.instructions)

        result += FUNC_TEMPLATE.format(
            return_type=function.get_return_type(),
            func_name=function.name,
            params=function.get_params(),
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


def _translate_instructions(instructions: list[Instruction]) -> str:
    '''TODO'''
    translations = []

    for i, instruction in enumerate(instructions):
        
        #return statement
        if (instruction[0] == 'mov' and instruction[1][0] == 'r0' and 
              instructions[i+1][0] == 'bx'):
            translations.append(f'return {instruction[1][1]};')
            continue

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