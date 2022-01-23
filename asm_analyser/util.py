import os
import subprocess

def compile_asm(test_path: str, filename: str, optimization: str) -> None:
    '''Compiles the selected C file to assembler.

    Parameters
    ----------
    test_path : str
        Path to the test files.
    filename : str
        Name of the file.
    optimization: str
        Specifies the optimization level that should be used.
    '''
    if optimization:
        os.system(
            f'arm-linux-gnueabi-gcc -S -march=armv7-a -marm -fno-stack-protector {optimization} {test_path}/c_in/{filename}.c -o {test_path}/asm/{filename}.s')
    else:
        os.system(
            f'arm-linux-gnueabi-gcc -S -march=armv7-a -marm -fno-stack-protector {test_path}/c_in/{filename}.c -o {test_path}/asm/{filename}.s')


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

def parse_output(test_path: str, filename: str) -> list[int]:
    '''Parses and displays the output from the C-file

    Parameters
    ----------
    test_path : str
        Path to the test files.
    filename : str
        Name of the file.
    
    Returns
    -------
    list[int]
        Number of executions of each basic block.
    '''
    os.system(f'gcc {test_path}/c_out/{filename}.c -o {test_path}/c_out/output')

    res = subprocess.run([f'{test_path}/c_out/output'],
                         stdout= subprocess.PIPE).stdout.decode('utf-8')

    print('\n\nPROGRAM OUTPUT\n--------------')

    line_counter = -1
    block_count = 0
    block_sizes = []
    block_counts = []
    load_count = 0
    store_count = 0
    cond_branches = 0
    mispredictions = 0

    for line in res.splitlines():
        if line_counter >= 0:
            if line_counter == 0:
                block_count = int(line)
            elif line_counter == 1:
                block_sizes = [int(x) for x in line.split()]
            elif line_counter == 2:
                block_counts = [int(x) for x in line.split()]
            elif line_counter == 3:
                load_count = int(line)
            elif line_counter == 4:
                store_count = int(line)
            elif line_counter == 5:
                cond_branches = int(line)
            elif line_counter == 6:
                mispredictions = int(line)

            line_counter += 1
        else:
            if '__count_start__' not in line:
                print(line)
            else:
                line_counter = 0

    total = 0
    for i in range(block_count):
        total += block_sizes[i] * block_counts[i]

    print(f'\n\nCOUNTING RESULTS of {filename}.s\n'+'-'*71)
    print('{:<40} {:>30}'.format('Number of basic blocks:', block_count))
    print('{:<40} {:>30}'.format('Total instructions executed:', total))
    print('{:<40} {:>30}'.format('Total load instructions executed:', load_count))
    print('{:<40} {:>30}'.format('Total store instructions executed:', store_count))
    print('{:<40} {:>30}'.format('Branch prediction success rate:', 1-mispredictions/cond_branches))
    
    return block_counts