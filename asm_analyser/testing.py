'''Provides a method for testing multiple programs.
'''

import subprocess
import os
from architectures.arm.parser import ArmParser
import main

TEST_PATH = os.path.abspath(os.path.join(os.getcwd(), '../test_files'))
IN_PATH = f'{TEST_PATH}/c_in'
OUT_PATH = f'{TEST_PATH}/c_out'


def run_tests() -> None:
    '''Runs the tool on every example C-file in the 'test_files' folder.
    '''

    errors = []

    for filename in os.listdir(IN_PATH):
        if filename != 'output':
            filename = filename[:-2]
            print(filename)
            print('----------------')

            # test every optimization level
            for optimization in ['', '-O1', '-O2', '-O3']:
                if optimization:
                    print(optimization)
                else:
                    print('Without optimization')

                # compare the outputs of the two C programs
                res_c_in, res_c_out = _run_test(filename, optimization)

                if res_c_in != res_c_out:
                    errors.append((filename, optimization))
                    print(f'error at: {optimization}:')
                    print('c_in:')
                    print(res_c_in[:100])
                    print('c_out:')
                    print(res_c_out[:100])
                    print()

    # print the errors
    for error in errors:
        print(f'Error in {error[0]} at optimization {error[1]}.')
        res_in, res_out = _run_test(*error)
        print(f'input result:\n {res_in} \n')
        print(f'output result:\n {res_out} \n')


def _run_test(filename: str, optimization: str) -> tuple[str, str]:
    '''Tests one C-file at the given optimization level and compares it
    to the input C program.

    Parameters
    ----------
    filename : str
        Name of the program/file to be tested.
    optimization : str
        Optimization level that should be used
        ('', '-O1', '-O2' or '-O3').
    '''
    res_c_out = main.run_analysis(TEST_PATH, filename, optimization)

    os.system(f'gcc -O3 {IN_PATH}/{filename}.c -o {IN_PATH}/output')

    res_c_in = subprocess.run([f'{IN_PATH}/output'],
                              stdout=subprocess.PIPE).stdout.decode('utf-8')

    # remove the counting results from the output
    title_idx = res_c_out.find('PROGRAM OUTPUT') + 29
    count_idx = res_c_out.find('COUNTING RESULTS')
    res_c_out = res_c_out[title_idx:count_idx] if count_idx != - 1 \
        else res_c_out[title_idx:]

    res_c_in = res_c_in.strip()
    res_c_out = res_c_out.strip()

    return res_c_in, res_c_out


run_tests()
