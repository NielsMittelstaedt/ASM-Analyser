'''
Implements everything required (including different strategies) for
branch prediction simulation with ARM assembly.
'''
import re
from asm_analyser import branch_pred
from asm_analyser.blocks.code_block import CodeBlock


class ArmBranchPredictor(branch_pred.BranchPredictor):
    '''
    Implements the BranchPredictor class for ARM assembly.
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
            if '//BRANCHPRED' in line:
                if branch_count == 0:
                    result += 'int cond_branches[0];\n'
                    result += 'int mispredictions[0];\n'
                else:
                    result += f'uint8_t branch_bits[{branch_count}] = {{0}};\n'
                    result += f'int cond_branches[{branch_count}] = {{0}};\n'
                    result += f'int mispredictions[{branch_count}] = {{0}};\n'
            elif '//BRANCHTAKEN' in line:
                result += (
                    f'cond_branches[{branch_index}]++;\n'
                    f'if(branch_bits[{branch_index}] == 0) {{\n'
                    f'mispredictions[{branch_index}]++;\n'
                    f'branch_bits[{branch_index}] = 1;\n'
                    f'}}\n'
                )
            elif '//BRANCHNOTTAKEN' in line:
                result += (
                    f'cond_branches[{branch_index}]++;\n'
                    f'if(branch_bits[{branch_index}] == 1) {{\n'
                    f'mispredictions[{branch_index}]++;\n'
                    f'branch_bits[{branch_index}] = 0;\n'
                    f'}}\n'
                )
                branch_index += 1
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
            if '//BRANCHPRED' in line:
                if branch_count > 0:
                    result += f'uint8_t branch_bits[{branch_count}] = {{0}};\n'
                    result += f'int cond_branches[{branch_count}] = {{0}};\n'
                    result += f'int mispredictions[{branch_count}] = {{0}};\n'
            elif '//BRANCHTAKEN' in line:
                result += (
                    f'cond_branches[{branch_index}]++;\n'
                    f'if(branch_bits[{branch_index}] == 0 || branch_bits[{branch_index}] == 1) {{\n'
                    f'mispredictions[{branch_index}]++;\n'
                    f'branch_bits[{branch_index}]++;\n'
                    f'}}\n'
                    f'else if(branch_bits[{branch_index}] == 2) {{\n'
                    f'branch_bits[{branch_index}]++;\n'
                    f'}}\n')
            elif '//BRANCHNOTTAKEN' in line:
                result += (
                    f'cond_branches[{branch_index}]++;\n'
                    f'if(branch_bits[{branch_index}] == 2 || branch_bits[{branch_index}] == 3) {{\n'
                    f'mispredictions[{branch_index}]++;\n'
                    f'branch_bits[{branch_index}]--;\n'
                    f'}}\n'
                    f'else if(branch_bits[{branch_index}] == 1) {{\n'
                    f'branch_bits[{branch_index}]--;\n'
                    f'}}\n')
                branch_index += 1
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
            if '//BRANCHPRED' in line:
                if branch_count > 0:
                    result += f'uint8_t branch_bits[{branch_count}] = {{0}};\n'
                    result += f'int cond_branches[{branch_count}] = {{0}};\n'
                    result += f'int mispredictions[{branch_count}] = {{0}};\n'
            elif '//BRANCHTAKEN' in line:
                result += (
                    f'cond_branches[{branch_index}]++;\n'
                    f'if(branch_bits[{branch_index}] == 0){{\n'
                    f'mispredictions[{branch_index}]++;\n'
                    f'branch_bits[{branch_index}]++;\n'
                    f'}}\n'
                    f'else if(branch_bits[{branch_index}] == 1) {{\n'
                    f'mispredictions[{branch_index}]++;\n'
                    f'branch_bits[{branch_index}] += 2;\n'
                    f'}}\n'
                    f'else if(branch_bits[{branch_index}] == 2) {{\n'
                    f'branch_bits[{branch_index}]++;\n'
                    f'}}\n'
                )
            elif '//BRANCHNOTTAKEN' in line:
                result += (
                    f'cond_branches[{branch_index}]++;\n'
                    f'if(branch_bits[{branch_index}] == 3){{\n'
                    f'mispredictions[{branch_index}]++;\n'
                    f'branch_bits[{branch_index}]--;\n'
                    f'}}\n'
                    f'else if(branch_bits[{branch_index}] == 2) {{\n'
                    f'mispredictions[{branch_index}]++;\n'
                    f'branch_bits[{branch_index}] = 0;\n'
                    f'}}\n'
                    f'else if(branch_bits[{branch_index}] == 1) {{\n'
                    f'branch_bits[{branch_index}]--;\n'
                    f'}}\n'
                )
                branch_index += 1
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
        if (re.match(r'^b(?!ic$).*', opcode) or
           (re.match(r'(^ldr.*)|(^ldm.*)|(^pop.*)', opcode) and 'pc' in args)):
            cond = False

            if re.match(r'(^ldr.*)|(^ldm.*)', opcode):
                digit_idx = re.search(r'\d', opcode).start()
                if opcode[digit_idx - 2:digit_idx] in COND_CODES:
                    cond = True

            elif opcode[-2:] in COND_CODES:
                cond = True

            return cond

        return False

    @staticmethod
    def write_rates(file_path: str,
                    blocks: list[CodeBlock],
                    branch_rates: list[float],
                    branch_map: dict[int,
                                     int]) -> None:
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
