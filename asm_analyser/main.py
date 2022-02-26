from architectures.arm.parser import ArmParser
from architectures.arm.processor import ArmProcessor
from architectures.arm.counter import ArmCounter
from architectures.arm.translator import ArmTranslator
from architectures.arm.branch_pred import ArmBranchPredictor, BP_METHODS
import os
import re
import util
import argparse


def run_analysis(filepath: str, optimization: str,
                 compile_asm: bool, bp_method: str) -> str:
    '''Core part of the application; controls the whole data flow.

    Parameters
    ----------
    filepath : str
        Patht of the input file to be analysed.
    optimization : str
        Specifies the optimization level for the compiler
        ('', 'O1', 'O2' or 'O3').
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
    parser = ArmParser(f'{filepath}.s')
    processor = ArmProcessor()
    counter = ArmCounter()

    # clean any old files
    util.cleanup(filepath)

    # compile the c file if necessary
    if compile_asm:
        util.compile_asm(f'{filepath}.c', optimization)

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
    util.write_c_file(f'{filepath}_out.c', output_str)
    util.format_c(f'{filepath}_out.c')

    # execute output C file, and parse the results
    block_counts, branch_rates, logs = util.parse_output(f'{filepath}_out.c')
    print(logs)

    # write the instruction counts in front of each asm instruction
    counter.write_instr_counts(f'{filepath}.s', basic_blocks, block_counts)
    # write the branch prediction success rates to the asm file
    predictor.write_rates(f'{filepath}.s', code_blocks,
                          branch_rates, translator.branch_map)

    return logs


def main():
    # initializing the configuration values
    #rel_path = os.path.join(os.getcwd(), '../test_files')
    filepath = ''
    optimization = ''
    compile_asm = True
    bp_method = 'one_bit'

    parser = argparse.ArgumentParser()

    parser.add_argument(
        '-f',
        '--file',
        help='input file in assembly or C',
        type=str,
        required=True)

    parser.add_argument(
        '-o',
        '--opt',
        help='optimization level to be used (O1, O2, O3), '
        'leave out for no optimization',
        type=str,
        required=False)

    parser.add_argument(
        '-b',
        '--bp',
        help=f'branch prediction method to be used',
        type=str,
        required=False
    )

    # parse and save args
    args = parser.parse_args()
    filepath = args.file
    if args.opt:
        optimization = args.opt
    if args.bp:
        bp_method = args.bp

    # check if file is valid and exists
    if not re.match('^.*\.[cs]$', filepath) or not os.path.exists(filepath):
        print('Input file invalid or does not exist.')
        return

    # check if optimization level is correct
    if optimization != '' and not re.match('^O[123]$', optimization):
        print('Optimization level can only be empty, O1, O2 or O3.')
        return

    # check if branch prediction method is correct
    if bp_method not in BP_METHODS:
        print('The branch prediction method should be one of the following:')
        print(', '.join(BP_METHODS))
        return

    # start analysis
    filepath = filepath[:-2]

    run_analysis(filepath, optimization, compile_asm, bp_method)


if __name__ == '__main__':
    main()
