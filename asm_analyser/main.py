from architectures.arm.parser import ArmParser
from architectures.arm.processor import ArmProcessor
from architectures.arm.counter import ArmCounter
from architectures.arm.translator import ArmTranslator
import os
import re
import sys
import util
import branch_pred


def run_analysis(test_path: str, filename: str, optimization: str,
                 compile_asm: bool, bp_method: str) -> str:
    '''Core part of the application; controls the whole data flow.

    Parameters
    ----------
    test_path : str
        Absolute path to the test directory
        for the input, asm and output files.
    filename : str
        Name of the file to be analysed.
    optimization : str
        Specifies the optimization level for the compiler.
    compile_asm : bool
        Specifies whether the asm file needs
        to be compiled or already exists.
    bp_method : str
        Name of the branch prediction method that should be used.

    Returns
    -------
    str
        Output that is also printed to the console.
    '''
    parser = ArmParser(f'{test_path}/asm', filename)
    processor = ArmProcessor()
    counter = ArmCounter()

    # compile the c file if necessary
    if compile_asm:
        util.compile_asm(test_path, filename, optimization)

    # parse the assembly input file
    code_blocks = parser.create_blocks()

    # process the parsed instructions further
    code_blocks = processor.create_IR(code_blocks)
    basic_blocks = processor.get_basic_blocks(code_blocks)

    # insert counters
    code_blocks = counter.insert_counters(code_blocks, basic_blocks)

    # translate to C
    translator = ArmTranslator(code_blocks, basic_blocks, counter)
    translated_str = translator.translate()
    output_str = branch_pred.insert_branch_pred(translated_str, bp_method)

    # write to file and format
    util.write_C_file(f'{test_path}/c_out/{filename}.c', output_str)
    util.format_C(f'{test_path}/c_out/{filename}.c')

    # execute output C file, process and display the results
    block_counts, branch_rates, logs = util.parse_output(test_path, filename)
    print(logs)

    counter.write_instr_counts(f'{test_path}/asm/{filename}.s', basic_blocks,
                               block_counts)
    branch_pred.write_rates(f'{test_path}/asm/{filename}.s', code_blocks,
                            branch_rates, translator.branch_map)

    return logs


def main():
    # initializing the configuration values
    rel_path = os.path.join(os.getcwd(), '../test_files')
    filename = ''
    optimization = ''
    compile_asm = True
    bp_method = 'one_bit'

    # check if enough arguments are passed
    if len(sys.argv) < 2:
        print('Usage: python main.py <TESTPROGRAM> <OPTIMIZATION> <BRANCH_PRED>')
        return

    filename = sys.argv[1]

    # check if optimization level is correct
    if len(sys.argv) >= 3:
        if not re.match('^-O[123]$', sys.argv[2]):
            print('Optimization level can only be empty, -O1, -O2 or -O3.')
            return

        optimization = sys.argv[2]

    # check if branch prediction method is correct
    if len(sys.argv) >= 4:
        if sys.argv[3] not in branch_pred.methods:
            print('The branch prediction method should be one of the following:')
            print(', '.join(branch_pred.methods.keys()))
            return

        bp_method = sys.argv[3]

    if filename.endswith('.s'):
        compile_asm = False

    run_analysis(os.path.abspath(rel_path), filename,
                 optimization, compile_asm, bp_method)


if __name__ == '__main__':
    main()
