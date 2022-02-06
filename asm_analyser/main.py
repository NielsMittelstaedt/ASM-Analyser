from architectures.arm.parser import ArmParser
from architectures.arm.processor import ArmProcessor
from architectures.arm.counter import ArmCounter
from architectures.arm.translator import ArmTranslator
import os
import re
import sys
import util
import branch_pred

def run_analysis(test_path: str, filename: str, optimization: str) -> str:
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

    Returns
    -------
    str
        Output that is also printed to the console.
    '''
    parser = ArmParser(f'{test_path}/asm', filename)
    processor = ArmProcessor()
    counter = ArmCounter()

    # compile the c file if necessary
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
    output_str = branch_pred.two_bit1(translated_str)

    # write to file and format
    util.write_C_file(f'{test_path}/c_out/{filename}.c', output_str)
    util.format_C(f'{test_path}/c_out/{filename}.c')

    # execute output C file, process and display the results
    block_counts, logs = util.parse_output(test_path, filename)
    print(logs)

    #counter.write_instr_counts(f'{test_path}/asm/{filename}.s', basic_blocks,
    #                           block_counts)

    return logs

def main():
    rel_path = os.path.join(os.getcwd(), '../test_files')

    if len(sys.argv) < 2:
        print("Usage: python main.py <TESTPROGRAM> <OPTIMIZATION>")
        return

    elif len(sys.argv) == 2:
        run_analysis(os.path.abspath(rel_path), sys.argv[1], '')

    else:
        if not re.match('^-O[123]$', sys.argv[2]):
            print("Optimization level can only be empty, -O1, -O2 or -O3.")
            return

        run_analysis(os.path.abspath(rel_path), sys.argv[1], sys.argv[2])

if __name__ == '__main__':
    main()