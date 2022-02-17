from architectures.arm.parser import ArmParser
from architectures.arm.processor import ArmProcessor
from architectures.arm.counter import ArmCounter
from architectures.arm.translator import ArmTranslator
from architectures.arm.branch_pred import ArmBranchPredictor, bp_methods
import os
import re
import sys
import util


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
        Specifies the optimization level for the compiler
        ('', '-O1', '-O2' or '-O3').
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
    code_blocks = processor.create_ir(code_blocks)
    basic_blocks = processor.get_basic_blocks(code_blocks)

    # insert counters
    code_blocks = counter.insert_counters(code_blocks, basic_blocks)

    # translate to C
    translator = ArmTranslator(code_blocks, basic_blocks, counter)
    translated_str = translator.translate()
    predictor = ArmBranchPredictor(translated_str)
    output_str = predictor.insert_branch_pred(bp_method)

    # write to file and format
    util.write_C_file(f'{test_path}/c_out/{filename}.c', output_str)
    util.format_C(f'{test_path}/c_out/{filename}.c')

    # execute output C file, and parse the results
    block_counts, branch_rates, logs = util.parse_output(test_path, filename)
    print(logs)

    # write the instruction counts in front of each asm instruction
    counter.write_instr_counts(f'{test_path}/asm/{filename}.s', basic_blocks,
                               block_counts)
    # write the branch prediction success rates to the asm file
    predictor.write_rates(f'{test_path}/asm/{filename}.s', code_blocks,
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
        print('Usage: python main.py -n=PROGRAM_NAME '
              '-o=OPTIMIZATION -b=BRANCH_PRED')
        return

    # read the passed arguments
    for i in range(1, len(sys.argv)):
        if len(sys.argv[i]) >= 4:
            if sys.argv[i].startswith('-n='):
                filename = sys.argv[i][3:]
            elif sys.argv[i].startswith('-o='):
                optimization = sys.argv[i][3:]
            elif sys.argv[i].startswith('-b='):
                bp_method = sys.argv[i][3:]

    # check if optimization level is correct
    if optimization != '' and not re.match('^-O[123]$', optimization):
        print('Optimization level can only be empty, -O1, -O2 or -O3.')
        return

    # check if branch prediction method is correct
    if bp_method not in bp_methods:
        print('The branch prediction method should be one of the following:')
        print(', '.join(bp_methods))
        return

    if filename.endswith('.s'):
        compile_asm = False
    elif filename.endswith('.c'):
        filename = filename[:-2]

    run_analysis(os.path.abspath(rel_path), filename,
                 optimization, compile_asm, bp_method)


if __name__ == '__main__':
    main()
