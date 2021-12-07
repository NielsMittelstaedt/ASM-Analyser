import os

def compile_asm(filename: str, optimization: str) -> None:
    '''Compiles the selected C file to assembler.

    Parameters
    ----------
    filename : str
        Name of the file.
    optimization: str
        Specifies the optimization level that should be used.
    '''
    if optimization:
        os.system(
            f'arm-linux-gnueabi-gcc -S -march=armv7-a -marm -fno-stack-protector {optimization} ../test_files/c_in/{filename}.c -o ../test_files/asm/{filename}.s')
    else:
        os.system(
            f'arm-linux-gnueabi-gcc -S -march=armv7-a -marm -fno-stack-protector ../test_files/c_in/{filename}.c -o ../test_files/asm/{filename}.s')


def format_C(filepath: str) -> None:
    '''Formats the given C file using astyle for better readability.

    Parameters
    ----------
    filename : str
        Name of the file to be formatted.
    '''
    os.system(
        f'../astyle --quiet --style=allman --suffix=none {filepath}')

def write_C_file(filepath: str, contents: str) -> None:
    '''Writes all the code into a C-file

    Parameters
    ----------
    filename : str
        Name of the C-file.
    contents: str
        Contents to be written to the file.
    '''
    with open(filepath, 'w') as fs:
        fs.write(contents)