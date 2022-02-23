'''Provides some utility functions.
'''

import os
import subprocess
from typing import List, Tuple

def test():
    print("hilfe")

def cleanup(filepath: str) -> None:
    '''Cleans the compiled files for the current program. That way we
    can assure new files are generated.

    Parameters
    ----------
    filepath : str
        Path of the input file without the file ending.
    '''
    try:
        os.remove(f'{filepath}_out.c')
        os.remove(os.path.join(os.path.dirname(filepath), 'output'))
    except:
        print("Cleanup: nothing to clean here.")


def compile_asm(filepath: str, optimization: str) -> None:
    '''Compiles the selected C file to assembler.

    Parameters
    ----------
    filepath : str
        Path of the input C file.
    optimization: str
        Specifies the optimization level that should be used.
    '''
    if optimization:
        os.system(
            f'arm-linux-gnueabi-gcc -S -march=armv7-a -marm -fno-stack-protector {optimization} {filepath} -o {filepath[:-2]}.s')
    else:
        os.system(
            f'arm-linux-gnueabi-gcc -S -march=armv7-a -marm -fno-stack-protector {filepath} -o {filepath[:-2]}.s')


def format_c(out_path: str) -> None:
    '''Formats the given C file using astyle for better readability.

    Parameters
    ----------
    out_path : str
        Name of the file to be formatted.
    '''
    os.system(
        f'../astyle --quiet --style=allman --suffix=none {out_path}')


def write_c_file(out_path: str, contents: str) -> None:
    '''Writes all the code into a C-file

    Parameters
    ----------
    out_path : str
        Name of the output C-file.
    contents: str
        Contents to be written to the file.
    '''
    with open(out_path, 'w') as fs:
        fs.write(contents)


def parse_output(out_path: str) -> Tuple[List[int], List[int], str]:
    '''Parses and processes the output from the C-file.

    Any important information that is used in other features
    (e.g. branch prediction) will be returned in this function.

    Parameters
    ----------
    filepath : str
        Path of the output C file.

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
    asm_name = f'{os.path.basename(out_path)[:-6]}.s'
    binary_path = ''
    out_dir = os.path.dirname(out_path)

    if not out_dir:
        binary_path = f'./output'
    else:
        binary_path = os.path.join(out_dir, 'output')

    compile_out = subprocess.run(
        [
            'gcc',
            '-O3',
            out_path,
            '-o',
            binary_path
        ],
        stderr=subprocess.PIPE
    ).stderr.decode('utf-8')

    if compile_out:
        print(compile_out)

    if compile_out.find('[-Waggressive-loop-optimizations]') != -1:
        os.system(
            f'gcc -O1 {out_path} -o {binary_path}')

    res = subprocess.run([f'./{binary_path}'],
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

    result += f'\n\nCOUNTING RESULTS of {asm_name}\n' + '-' * 71 + '\n'
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
