import architectures.arm.arm_util as arm_util
import architectures.arm.instr_translator as instr_translator
import architectures.arm.auxiliary_functions as auxiliary_functions
from asm_analyser.counter import Counter
from asm_analyser.blocks.basic_block import BasicBlock
from asm_analyser.blocks.code_block import CodeBlock, Instruction
from asm_analyser import translator


class Translator(translator.Translator):
    def __init__(self,
                 code_blocks: list[CodeBlock],
                 basic_blocks: list[BasicBlock],
                 file_name: str,
                 counter: Counter):
        super().__init__(code_blocks, basic_blocks, file_name, counter)
        self.FUNC_TEMPLATE = 'void {func_name}(){{\n' \
                             '{body}\n' \
                             '}}'

    def translate(self) -> str:
        # fill the template file with the variable parts
        result = ''

        with open('template.c', 'r') as f:
            for line in f.readlines():
                if 'REGISTERS' in line:
                    # add the necessary registers as globals
                    result += arm_util.get_needed_regs(self.code_blocks)
                elif 'LOCALDEFS' in line:
                    # add the variables for the arm local constants
                    result += arm_util.get_needed_consts(self.code_blocks)
                elif 'COUNTERS' in line:
                    # add the counter variables
                    result += self.counter.get_counter_vars(self.basic_blocks)
                elif 'MALLOCSTART' in line:
                    # allocate stack and heap and
                    # assign values to the arm local constants
                    result += arm_util.get_malloc_start(self.code_blocks)
                    result += arm_util.get_constant_defs(self.code_blocks)
                elif 'FILENAME' in line:
                    # add the name of the file to print it in the summary
                    result += f'char filename[] = "{self.file_name}.c";\n'
                elif 'FUNCTIONDECLS' in line:
                    # add the declarations for the translated functions
                    result += arm_util.get_function_decls(self.code_blocks)
                elif 'AUXFUNCTIONS' in line:
                    # add the necessary auxiliary functions
                    result += auxiliary_functions.get_auxiliary_functions(self.code_blocks)
                elif 'TRANSLATIONS' in line:
                    # add the function definitions
                    result += self._translate_blocks()
                else:
                    result += line

        return result

    def _translate_blocks(self) -> str:
        result = ''
        i = 0

        while i < len(self.code_blocks):
            block = self.code_blocks[i]
            
            if block.is_function:
                body = self._translate_block(block)

                # check for other labels or divided functions
                j = i+1
                while (j < len(self.code_blocks) and
                       not self.code_blocks[j].is_function and
                       self.code_blocks[j].is_code):
                    body += self.code_blocks[j].name+':\n'
                    body += self._translate_block(self.code_blocks[j])
                    j += 1

                if 'return' not in body[-20:]:
                    body += 'return;'

                # fill the function template
                result += self.FUNC_TEMPLATE.format(
                    func_name=block.name,
                    body=body
                )
                result += '\n\n'
        
            i += 1

        return result

    def _translate_block(self, block: CodeBlock) -> str:
        body = ''

        # add stack initialization to main method
        if block.name == 'main':
            body += 'malloc_start();\n'

        # translate each instruction of the block
        for instr in block.instructions:
            body += self._translate_instruction(instr)

        # add output of results to main method
        if block.is_last:
            # insert it before the return statement
            last_row_idx = body.rfind('\n', 0, body.rfind('\n'))
            if 'return;\n' in body[last_row_idx:]:
                body = (body[:last_row_idx+1] + 'counter_summary();\n' +
                        body[last_row_idx+1:])
            else:
                body += 'counter_summary();\n'

        return body

    def _translate_instruction(self, instruction: Instruction) -> str:
        # branch instructions are handled differently
        if instruction[0] == 'bl' or instruction[0] == 'b':
            return self._translate_branching(instruction)

        return instr_translator.translate(instruction[0], *instruction[1])

    def _translate_branching(self, instruction: Instruction) -> str:
        '''Translates branch instructions as they are handled differently.

        Parameters
        ----------
        instruction : Instruction
            The branch instruction (b or bl) to be translated.

        Returns
        -------
        str
            The translated C code for this instruction.
        '''
        # translate library calls in auxiliary functions
        if instruction[1][0] in auxiliary_functions.call_dict:
            if instruction[0] == 'b':
                return (auxiliary_functions.call_dict[instruction[1][0]] +
                        'return;\n')
            else:
                return auxiliary_functions.call_dict[instruction[1][0]]

        # we cannot use goto for functions
        if instruction[0] == 'b':
            function =  next((item for item in self.code_blocks
                                   if item.name == instruction[1][0] and
                                      item.is_function), None)
            if function is not None:
                return f'{instruction[1][0]}();\nreturn;\n'

        return instr_translator.translate(instruction[0], *instruction[1])