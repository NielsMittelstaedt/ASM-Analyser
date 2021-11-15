import subprocess
import os
from parser.arm_parser import ArmParser
import main

IN_PATH = '../examples/c_in/'
OUT_PATH = '../examples/c_out/'

def run_tests() -> None:
    '''TODO
    '''

    errors = []

    for filename in os.listdir(IN_PATH):
        
        if filename != 'output':
            filename = filename[:-2]

            for optimization in ['', '-O1', '-O2', '-O3']:
                res_c_in, res_c_out = _run_test(filename, optimization)

                if res_c_in != res_c_out:
                    errors.append((filename, optimization))

    for error in errors:
        print(f'Error in {error[0]} at optimization {error[1]}.')
        res_in, res_out = _run_test(*error)
        print(f'input result:\n {res_in} \n')
        print(f'output result:\n {res_out} \n')


def _run_test(filename: str, optimization: str) -> tuple[str, str]:
    '''TODO
    '''
    main.run_analysis(filename, optimization, ArmParser(filename))
                
    os.system(f'gcc {IN_PATH}{filename}.c -o {IN_PATH}output')
    os.system(f'gcc {OUT_PATH}{filename}.c -o {OUT_PATH}output')

    res_c_in = subprocess.run([f'{IN_PATH}output'],
                            stdout=subprocess.PIPE).stdout.decode('utf-8')
    res_c_out = subprocess.run([f'{OUT_PATH}output'],
                            stdout=subprocess.PIPE).stdout.decode('utf-8')

    # remove the counting results from the output
    count_idx = res_c_out.find('COUNTING RESULTS')
    res_c_out = res_c_out[:count_idx] if count_idx != -1 else res_c_out

    res_c_in = res_c_in.strip()
    res_c_out = res_c_out.strip()

    return res_c_in, res_c_out

run_tests()
