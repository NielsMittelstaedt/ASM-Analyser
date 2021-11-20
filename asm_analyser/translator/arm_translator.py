from asm_analyser.blocks.code_block import CodeBlock, Instruction
from asm_analyser.blocks.basic_block import BasicBlock
from translator.translator import Translator
import asm_analyser.counting as counting
import translator.auxiliary_functions as auxiliary_functions
import translator.instr_translator as instr_translator
import translator.arm_util as arm_util
import re


class ArmTranslator(Translator):
    def __init__(self,
                 code_blocks: list[CodeBlock],
                 basic_blocks: list[BasicBlock],
                 file_name: str,
                 part_functions: set[str]):
        self.FUNC_TEMPLATE = 'void {func_name}(){{\n' \
                             '{body}\n' \
                             '}}'
        super().__init__(code_blocks, basic_blocks, file_name, part_functions)

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
                    result += counting.get_counter_vars(self.basic_blocks)
                elif 'PARTS' in line:
                    # add the boolean variables for divided functions
                    result += arm_util.get_part_vars(self.code_blocks)
                elif 'LOCALCONSTANTS' in line:
                    # assign values to the arm local constants
                    result += arm_util.get_constant_defs(self.code_blocks)
                elif 'FILENAME' in line:
                    # add the name of the file to print it in the summary
                    result += f'char filename[] = "{self.file_name}.c";\n'
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
            
            if block.is_function and not block.is_part:
                body = ''

                # add the condition if function is divided
                if any(re.match(block.name+'part\d+$', x.name)
                       for x in self.code_blocks):
                    body += f'if ({block.name}part == -1) {{\n'

                body += self._translate_block(block)

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
            body += self._translate_instruction(instr, block.name)

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

    def _translate_part(self, index: int) -> str:
        '''TODO
        '''
        part_name = re.sub('\d+$', '', self.code_blocks[index].name)
        part_number = re.search(r'\d+', self.code_blocks[index].name[::-1]).group()[::-1]

        result = f'goto {self.code_blocks[index].name};\n}}\n'
        result += f'if ({part_name} == {part_number}) {{\n{self.code_blocks[index].name}:\n'
        result += self._translate_block(self.code_blocks[index])

        # check for other labels or divided functions
        j = index + 1
        while (j < len(self.code_blocks) and
               not self.code_blocks[j].is_function and
               self.code_blocks[j].is_code):
            result += self.code_blocks[j].name+':\n'
            result += self._translate_block(self.code_blocks[j])
            j += 1

        result += '}\n'

        return result

    def _translate_branching(self, instruction: Instruction,
                             parent_name: str) -> str:
        '''TODO
        '''
        # todo translate b ...part0 only with translate_part once
        
        # translate library calls in auxiliary functions
        if instruction[1][0] in auxiliary_functions.call_dict:
            if instruction[0] == 'b':
                return (auxiliary_functions.call_dict[instruction[1][0]] +
                        'return;\n')
            else:
                return auxiliary_functions.call_dict[instruction[1][0]]
        
        if re.match('.*part\d+$', instruction[1][0]):
            func_name = re.sub('part\d+$', '', instruction[1][0])

            if instruction[0] == 'b':
                if func_name == parent_name:
                    part_idx = next((i for i, item in enumerate(self.code_blocks)
                                    if item.name == instruction[1][0]), None)
                    return self._translate_part(part_idx)
                
                return f'goto {instruction[1][0]};\n'

            elif instruction[0] == 'bl':
                part_number = re.search(r'\d+',
                                        instruction[1][0][::-1]).group()[::-1]
                return f'{func_name}part = {part_number};\n{func_name}();\n'

        if instruction[0] == 'bl' and instruction[1][0] in self.part_functions:
            return f'{instruction[1][0]}part = -1;\n{instruction[1][0]}();\n'

        return instr_translator.translate(instruction[0], *instruction[1])

    def _translate_instruction(self, instruction: Instruction,
                               parent_name: str) -> str:
        # branch instructions are handled differently
        if instruction[0] == 'bl' or instruction[0] == 'b':
            return self._translate_branching(instruction, parent_name)

        return instr_translator.translate(instruction[0], *instruction[1])
        