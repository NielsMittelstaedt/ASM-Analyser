from function import Function
import arm_translator
import os

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

        print('test')
    return ''.join(translations)


def _translate_function(function: Function) -> str:

    body = ''

    # filter out instructions that aren't import for the translation
    filtered = []

    only_str_ldr = True

    for instruction in function.instructions:
        # if ('sp' in instruction[1][0] or 'fp' in instruction[1][0]):
        #    continue

        # if (only_str_ldr and 'r' in instruction[1][0]):
        #    continue

        #only_str_ldr = False

        filtered.append(instruction)

    return ''
