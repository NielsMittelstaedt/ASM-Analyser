'''Implements everything required (including different strategies) for
branch prediction simulation with ARM assembly.
'''
import re
from typing import List, Dict
from asm_analyser import branch_pred
from asm_analyser.blocks.code_block import CodeBlock


class ArmBranchPredictor(branch_pred.BranchPredictor):
    '''Implements the BranchPredictor class for ARM assembly.
    '''


    def one_bit(self) -> str:
        '''Branch prediction using one bit (saturating counter).

        Returns
        -------
        str
            C code containing all necessary elements for this branch predictor.
        '''
        result = ''
        branch_count = 0
        branch_index = 0

        for line in self.c_code.splitlines():
            if '//BRANCHTAKEN' in line:
                branch_count += 1

        for line in self.c_code.splitlines():
            if '//BPDEFS' in line:
                result += f'uint8_t branch_bits[{branch_count}];\n'
                result += f'int cond_branches[{branch_count}];\n'
                result += f'int mispredictions[{branch_count}];\n'
            elif '//BPINIT' in line:
                if branch_count > 0:
                    result += '.branch_bits = {0}, .cond_branches = {0}, '
                    result += '.mispredictions = {0}\n'
            elif '//BRANCHTAKEN' in line:
                result += (
                    f'_asm_analysis_.cond_branches[{branch_index}]++;\n'
                    f'if(_asm_analysis_.branch_bits[{branch_index}] == 0) {{\n'
                    f'_asm_analysis_.mispredictions[{branch_index}]++;\n'
                    f'_asm_analysis_.branch_bits[{branch_index}] = 1;\n'
                    f'}}\n'
                )
            elif '//BRANCHNOTTAKEN' in line:
                result += (
                    f'_asm_analysis_.cond_branches[{branch_index}]++;\n'
                    f'if(_asm_analysis_.branch_bits[{branch_index}] == 1) {{\n'
                    f'_asm_analysis_.mispredictions[{branch_index}]++;\n'
                    f'_asm_analysis_.branch_bits[{branch_index}] = 0;\n'
                    f'}}\n'
                )
                branch_index += 1
            elif 'BPSTART' in line:
                pass
            elif 'BPEND' in line:
                pass
            else:
                result += f'{line}\n'

        return result[:-2]

    def two_bit1(self) -> str:
        '''Branch prediction using two bits (saturating counter).

        Returns
        -------
        str
            C code containing all necessary elements for this branch predictor.
        '''
        result = ''
        branch_count = 0
        branch_index = 0

        for line in self.c_code.splitlines():
            if '//BRANCHTAKEN' in line:
                branch_count += 1

        for line in self.c_code.splitlines():
            if '//BPDEFS' in line:
                result += f'uint8_t branch_bits[{branch_count}];\n'
                result += f'int cond_branches[{branch_count}];\n'
                result += f'int mispredictions[{branch_count}];\n'
            elif '//BPINIT' in line:
                if branch_count > 0:
                    result += '.branch_bits = {0}, .cond_branches = {0}, '
                    result += '.mispredictions = {0}\n'
            elif '//BRANCHTAKEN' in line:
                result += (
                    f'_asm_analysis_.cond_branches[{branch_index}]++;\n'
                    f'if(_asm_analysis_.branch_bits[{branch_index}] == 0 || _asm_analysis_.branch_bits[{branch_index}] == 1) {{\n'
                    f'_asm_analysis_.mispredictions[{branch_index}]++;\n'
                    f'_asm_analysis_.branch_bits[{branch_index}]++;\n'
                    f'}}\n'
                    f'else if(_asm_analysis_.branch_bits[{branch_index}] == 2) {{\n'
                    f'_asm_analysis_.branch_bits[{branch_index}]++;\n'
                    f'}}\n')
            elif '//BRANCHNOTTAKEN' in line:
                result += (
                    f'_asm_analysis_.cond_branches[{branch_index}]++;\n'
                    f'if(_asm_analysis_.branch_bits[{branch_index}] == 2 || _asm_analysis_.branch_bits[{branch_index}] == 3) {{\n'
                    f'_asm_analysis_.mispredictions[{branch_index}]++;\n'
                    f'_asm_analysis_.branch_bits[{branch_index}]--;\n'
                    f'}}\n'
                    f'else if(_asm_analysis_.branch_bits[{branch_index}] == 1) {{\n'
                    f'_asm_analysis_.branch_bits[{branch_index}]--;\n'
                    f'}}\n')
                branch_index += 1
            elif 'BPSTART' in line:
                pass
            elif 'BPEND' in line:
                pass
            else:
                result += f'{line}\n'

        return result[:-2]

    def two_bit2(self) -> str:
        '''Another Branch prediction using two bits (bimodal predictor).

        Returns
        -------
        str
            C code containing all necessary elements for this branch predictor.
        '''
        result = ''
        branch_count = 0
        branch_index = 0

        for line in self.c_code.splitlines():
            if '//BRANCHTAKEN' in line:
                branch_count += 1

        for line in self.c_code.splitlines():
            if '//BPDEFS' in line:
                result += f'uint8_t branch_bits[{branch_count}];\n'
                result += f'int cond_branches[{branch_count}];\n'
                result += f'int mispredictions[{branch_count}];\n'
            elif '//BPINIT' in line:
                if branch_count > 0:
                    result += '.branch_bits = {0}, .cond_branches = {0}, '
                    result += '.mispredictions = {0}\n'
            elif '//BRANCHTAKEN' in line:
                result += (
                    f'_asm_analysis_.cond_branches[{branch_index}]++;\n'
                    f'if(_asm_analysis_.branch_bits[{branch_index}] == 0){{\n'
                    f'_asm_analysis_.mispredictions[{branch_index}]++;\n'
                    f'_asm_analysis_.branch_bits[{branch_index}]++;\n'
                    f'}}\n'
                    f'else if(_asm_analysis_.branch_bits[{branch_index}] == 1) {{\n'
                    f'_asm_analysis_.mispredictions[{branch_index}]++;\n'
                    f'_asm_analysis_.branch_bits[{branch_index}] += 2;\n'
                    f'}}\n'
                    f'else if(_asm_analysis_.branch_bits[{branch_index}] == 2) {{\n'
                    f'_asm_analysis_.branch_bits[{branch_index}]++;\n'
                    f'}}\n'
                )
            elif '//BRANCHNOTTAKEN' in line:
                result += (
                    f'_asm_analysis_.cond_branches[{branch_index}]++;\n'
                    f'if(_asm_analysis_.branch_bits[{branch_index}] == 3){{\n'
                    f'_asm_analysis_.mispredictions[{branch_index}]++;\n'
                    f'_asm_analysis_.branch_bits[{branch_index}]--;\n'
                    f'}}\n'
                    f'else if(_asm_analysis_.branch_bits[{branch_index}] == 2) {{\n'
                    f'_asm_analysis_.mispredictions[{branch_index}]++;\n'
                    f'_asm_analysis_.branch_bits[{branch_index}] = 0;\n'
                    f'}}\n'
                    f'else if(_asm_analysis_.branch_bits[{branch_index}] == 1) {{\n'
                    f'_asm_analysis_.branch_bits[{branch_index}]--;\n'
                    f'}}\n'
                )
                branch_index += 1
            elif 'BPSTART' in line:
                pass
            elif 'BPEND' in line:
                pass
            else:
                result += f'{line}\n'

        return result[:-2]

    def insert_branch_pred(self, method_name: str) -> str:
        '''Calls the desired branch prediction method.

        Parameters
        ----------
        method_name : str
            Name of the desired branch prediction method.

        Returns
        -------
        str
            C-code containing the necessary instructions for the branch
            prediction simulation.
        '''
        if method_name == 'one_bit':
            return self.one_bit()
        elif method_name == 'two_bit1':
            return self.two_bit1()
        elif method_name == 'two_bit2':
            return self.two_bit2()
        else:
            return self.c_code

    @staticmethod
    def is_branch_instr(opcode: str, *args) -> bool:
        if (re.match('^b(?!ic$).*', opcode) or
           (re.match('(^ldr.*)|(^ldm.*)|(^pop.*)', opcode) and 'pc' in args)):
            cond = False

            if re.match('(^ldr.*)|(^ldm.*)', opcode):
                digit_idx = re.search('\d', opcode).start()
                if opcode[digit_idx - 2:digit_idx] in COND_CODES:
                    cond = True

            elif opcode[-2:] in COND_CODES:
                cond = True

            return cond

        return False

    @staticmethod
    def write_rates(file_path: str,
                    blocks: List[CodeBlock],
                    branch_rates: List[float],
                    branch_map: Dict[int, int]) -> None:
        asm_lines = []
        line_index = 0

        with open(file_path, 'r') as f:
            asm_lines = f.readlines()

        # Write back every asm line but add the branch prediction rate.
        with open(file_path, 'w') as f:
            for block in blocks:
                for instr in block.instructions:
                    if instr[0] != -1:
                        while line_index < instr[0]:
                            f.write(f'1.00 {asm_lines[line_index]}')
                            line_index += 1

                        if instr[0] in branch_map:
                            branch_rate = branch_rates[branch_map[instr[0]]]
                            branch_str = '{:.2f}'.format(branch_rate)
                            f.write(f'{branch_str} {asm_lines[line_index]}')
                        else:
                            f.write(f'1.00 {asm_lines[line_index]}')

                        line_index += 1

            while line_index < len(asm_lines):
                f.write(f'1.00 {asm_lines[line_index]}')
                line_index += 1


BP_METHODS = ['one_bit', 'two_bit1', 'two_bit2']
COND_CODES = ['eq', 'ne', 'ge', 'gt', 'le', 'lt', 'ls', 'cs',
              'cc', 'hi', 'mi', 'pl', 'al', 'nv', 'vs', 'vc']
