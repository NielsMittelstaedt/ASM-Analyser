import util
import translation
import processing
import counting
from parser.parser import Parser
from parser.arm_parser import ArmParser


def run_analysis(file_name: str, optimization: bool, parser: Parser) -> None:
    '''Core part of the application, controls the whole data flow.

    This function contains the whole process from start to finish.

    Parameters
    ----------
    file_name : str
        Name of the file to be analysed.
    optimization : bool
        Specifies whether the compiler should optimize.
    parser : Parser
        Instance of the parser that should be used.
    '''
    util.compile_asm(file_name, optimization)

    code_blocks = parser.create_blocks()

    # maybe remove some instructions
    '''left out optimizations:
    - str rx ... at the beginning of a function
    - instructions that work on sp or fp, e.g. str fp ...
    - consecutive str and ldr, e.g. str r0 ... and ldr r0 ...
    '''
    code_blocks = processing.create_IR(code_blocks)

    code_blocks = processing.get_return_types(code_blocks)
    
    basic_blocks = processing.get_basic_blocks(code_blocks)

    #code_blocks = counting.insert_counters(code_blocks, basic_blocks)

    output_str = translation.translate_blocks(code_blocks, basic_blocks)
    # TODO zwischenstep einbauen, der ldr und str je nach parametern in andere instruktionen übersetzt
    # hier vllt mit regex's arbeiten für das pattern matching

    util.write_C_file(file_name, output_str)

    util.format_C(file_name)


def main():
    run_analysis('float_incr', '', ArmParser('float_incr'))

if __name__ == '__main__':
    main()
