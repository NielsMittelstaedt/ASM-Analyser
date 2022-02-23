'''Provides methods for translating an ARM assembly file.
'''
import os
from typing import List
import asm_analyser.architectures.arm.arm_util as arm_util
import asm_analyser.architectures.arm.instr_translator as instr_translator
import asm_analyser.architectures.arm.auxiliary_functions as auxiliary_functions
from asm_analyser.architectures.arm.branch_pred import ArmBranchPredictor
from asm_analyser.blocks.basic_block import BasicBlock
from asm_analyser.blocks.code_block import CodeBlock
from asm_analyser.counter import Counter
from asm_analyser import translator

file_dir = os.path.dirname(os.path.abspath(__file__))

class ArmTranslator(translator.Translator):
    '''Implements the Translator class for ARM assembly.
    '''

    def __init__(self,
                 code_blocks: List[CodeBlock],
                 basic_blocks: List[BasicBlock],
                 counter: Counter):
        super().__init__(code_blocks, basic_blocks, counter)
        self.func_template = 'void {func_name}(){{\n' \
                             '{body}\n' \
                             '}}'

    def translate(self) -> str:
        # fill the template file with the variable parts
        result = ''

        with open(os.path.join(file_dir, 'template.c'), 'r') as f:
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
                elif 'AUXFUNCTIONS' in line:
                    # add the necessary auxiliary functions
                    result += auxiliary_functions.get_auxiliary_functions(
                        self.code_blocks)
                elif 'MALLOCSTART' in line:
                    # allocate stack and heap and
                    # assign values to the arm local constants
                    result += arm_util.get_malloc_start(self.code_blocks)
                    result += arm_util.get_constant_defs(self.code_blocks)
                elif 'FUNCTIONDECLS' in line:
                    # add the declarations for the translated functions
                    result += arm_util.get_function_decls(self.code_blocks)
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
                j = i + 1
                while (j < len(self.code_blocks) and
                       not self.code_blocks[j].is_function and
                       self.code_blocks[j].is_code):
                    body += self.code_blocks[j].name + ':\n'
                    body += self._translate_block(self.code_blocks[j])
                    j += 1

                if 'return' not in body[-20:]:
                    body += 'return;'

                # fill the function template
                result += self.func_template.format(
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
            # mapping between instruction number and branch instruction
            if ArmBranchPredictor.is_branch_instr(instr[1], *instr[2]):
                self.branch_map[instr[0]] = self.branch_count
                self.branch_count += 1
            body += instr_translator.translate(self.code_blocks, instr[1],
                                               *instr[2])

        # add output of results to main method
        if block.is_last:
            # insert it before the return statement
            last_row_idx = body.rfind('\n', 0, body.rfind('\n'))
            if 'return;\n' in body[last_row_idx:]:
                body = (body[:last_row_idx + 1] + 'counter_summary();\n' +
                        body[last_row_idx + 1:])

        return body
