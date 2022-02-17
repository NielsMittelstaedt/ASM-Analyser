'''Provides some utility functions.
'''

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


def format_c(filepath: str) -> None:
    '''Formats the given C file using astyle for better readability.

    Parameters
    ----------
    filename : str
        Name of the file to be formatted.
    '''
    os.system(
        f'../astyle --quiet --style=allman --suffix=none {filepath}')


def write_c_file(filepath: str, contents: str) -> None:
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


def parse_output(test_path: str,
                 filename: str) -> tuple[list[int], list[int], str]:
    '''Parses and processes the output from the C-file.

    Any important information that is used in other features
    (e.g. branch prediction) will be returned in this function.

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
    list[int]
        Branch prediction success rate of each branch instruction.
    str
        Outputs that will be logged to the console.
    '''
    result = ''

    compile_out = subprocess.run(
        [
            'gcc',
            '-O3',
            f'{test_path}/c_out/{filename}.c',
            '-o',
            f'{test_path}/c_out/output'
        ],
        stderr=subprocess.PIPE
    ).stderr.decode('utf-8')

    if compile_out:
        print(compile_out)

    if compile_out.find('[-Waggressive-loop-optimizations]') != -1:
        os.system(
            f'gcc -O1 {test_path}/c_out/{filename}.c -o {test_path}/c_out/output')

    res = subprocess.run([f'{test_path}/c_out/output'],
                         stdout=subprocess.PIPE).stdout.decode('utf-8')

    result += '\nPROGRAM OUTPUT\n--------------\n'

    line_counter = -1
    block_count = 0
    block_sizes = []
    block_counts = []
    load_count = 0
    store_count = 0
    instr_total = 0
    branch_rate = 0.0
    cond_branches = []
    mispredictions = []
    branch_rates = []

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
                cond_branches = [int(x) for x in line.split()]
            elif line_counter == 6:
                mispredictions = [int(x) for x in line.split()]

            line_counter += 1
        else:
            if '__count_start__' not in line:
                result += f'{line}\n'
            else:
                line_counter = 0

    # calculate total number of instructions
    for i in range(block_count):
        instr_total += block_sizes[i] * block_counts[i]

    # calculate total misprediction rates
    t = 0
    for i, b in enumerate(cond_branches):
        if b > 0:
            branch_rate += mispredictions[i]
            t += b
            branch_rates.append(1 - mispredictions[i] / cond_branches[i])
        else:
            branch_rates.append(1.0)

    if t == 0:
        branch_rate = '1.00'
    else:
        branch_rate = 1 - branch_rate / t
        branch_rate = '{:.2f}'.format(branch_rate)

    result += f'\n\nCOUNTING RESULTS of {filename}.s\n' + '-' * 71 + '\n'
    result += '{:<40} {:>30}'.format('Number of basic blocks:',
                                     block_count) + '\n'
    result += '{:<40} {:>30}'.format(
        'Total instructions executed:',
        instr_total) + '\n'
    result += '{:<40} {:>30}'.format(
        'Total load instructions executed:',
        load_count) + '\n'
    result += '{:<40} {:>30}'.format(
        'Total store instructions executed:',
        store_count) + '\n'
    result += '{:<40} {:>30}'.format(
        'Branch prediction success rate:',
        branch_rate) + '\n'

    return block_counts, branch_rates, result
