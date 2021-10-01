import util
import counter
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

    functions = parser.create_functions()

    counter.insert_counters(functions)

    # maybe remove some instructions
    '''left out optimizations:
    - str rx ... at the beginning of a function
    - instructions that work on sp or fp, e.g. str fp ...
    - consecutive str and ldr, e.g. str r0 ... and ldr r0 ...
    '''

    functions = util.create_IR(functions)
    
    output_str = util.translate_blocks(functions)
    # zwischenstep einbauen, der ldr und str je nach parametern in andere instruktionen übersetzt
    # hier vllt mit regex's arbeiten für das pattern matching

    util.write_C_file(file_name, output_str)

    util.format_C(file_name)


def main():
    run_analysis('int_incr', False, ArmParser('int_incr'))

if __name__ == '__main__':
    main()
