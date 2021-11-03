import os

def compile_asm(file_name: str, optimization: str) -> None:
    '''Compiles the selected C file to assembler.

    Parameters
    ----------
    file_name : str
        Name of the file.
    optimization: str
        Specifies the optimization level that should be used.
    '''
    if optimization:
        os.system(
            f'arm-linux-gnueabi-gcc -S -march=armv7-a -marm -fno-stack-protector {optimization} ../examples/c_in/{file_name}.c -o ../examples/asm/{file_name}.s')
    else:
        os.system(
            f'arm-linux-gnueabi-gcc -S -march=armv7-a -marm -fno-stack-protector ../examples/c_in/{file_name}.c -o ../examples/asm/{file_name}.s')


def format_C(file_name: str) -> None:
    '''Formats the given C file using astyle for better readability.

    Parameters
    ----------
    file_name : str
        Name of the file to be formatted.
    '''
    os.system(
        f'../astyle --style=allman --suffix=none ../examples/c_out/{file_name}.c')

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