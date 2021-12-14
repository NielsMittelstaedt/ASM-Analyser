from architectures.arm.parser import Parser as ArmParser
from architectures.arm.processor import Processor as ArmProcessor
from architectures.arm.counter import Counter as ArmCounter
from architectures.arm.translator import Translator as ArmTranslator
import os
import util

def run_analysis(test_path: str, filename: str, optimization: str) -> None:
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
    output_str = translator.translate()

    # write to file and format
    util.write_C_file(f'{test_path}/c_out/{filename}.c', output_str)
    util.format_C(f'{test_path}/c_out/{filename}.c')

    # execute output C file and process the count results
    block_counts = util.parse_output(test_path, filename)
    counter.write_instr_counts(f'{test_path}/asm/{filename}.s', basic_blocks,
                               block_counts)


def main():
    rel_path = os.path.join(os.getcwd(), '../test_files')
    run_analysis(os.path.abspath(rel_path) ,'simplex', '')

if __name__ == '__main__':
    main()