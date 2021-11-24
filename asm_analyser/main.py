import util
import processing
import counting
from parser.parser import Parser
from parser.arm_parser import ArmParser
from translator.arm_translator import ArmTranslator


def run_analysis(file_name: str, optimization: str, parser: Parser) -> None:
    '''Core part of the application, controls the whole data flow.

    This function contains the whole process from start to finish.

    Parameters
    ----------
    file_name : str
        Name of the file to be analysed.
    optimization : str
        Specifies the optimization level for the compiler.
    parser : Parser
        Instance of the parser that should be used.
    '''
    util.compile_asm(file_name, optimization)

    code_blocks = parser.create_blocks()

    # process the parsed instructions
    code_blocks = processing.create_IR(code_blocks)
    basic_blocks = processing.get_basic_blocks(code_blocks)
    code_blocks = processing.set_last_block(code_blocks)
    part_functions = processing.get_part_functions(code_blocks)

    # insert counters
    code_blocks = counting.insert_counters(code_blocks, basic_blocks)

    # translate to C
    translator = ArmTranslator(code_blocks, basic_blocks,
                               file_name, part_functions)
    output_str = translator.translate()

    # write to file and format
    util.write_C_file(file_name, output_str)
    util.format_C(file_name)


def main():
    run_analysis('radix_sort_2', '-O3', ArmParser('radix_sort_2'))

if __name__ == '__main__':
    main()
