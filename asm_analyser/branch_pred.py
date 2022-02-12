# bei conditional b, bx, (pop, load mit pc)
# muss die branch prediction eingebaut werden.

# Wir brauchen zwei globale variablen für die Anzahl conditional branches
# und die Anzahl Misspredictions

# Bei einem conditional branch wird je nach if auswertung dann
# die branch pred bits erhöht oder verringert und die misprediction gezählt
import re

from asm_analyser.blocks.code_block import CodeBlock

def one_bit(c_code: str) -> str:
    '''Branch prediction using one bit (saturating counter).

    Parameters
    ----------
    c_code : str
        The C code containing placeholders for the branch predictions.

    Returns
    -------
    str
        C code containing all necessary elements for this branch predictor.
    '''
    result = ''
    branch_count = 0
    branch_index = 0
    
    for line in c_code.splitlines():
        if '//BRANCHTAKEN' in line:
            branch_count += 1

    for line in c_code.splitlines():
        if '//BRANCHPRED' in line:
            if branch_count > 0:
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

def two_bit1(c_code: str) -> str:
    '''Branch prediction using two bits (saturating counter).

    Parameters
    ----------
    c_code : str
        The C code containing placeholders for the branch predictions.

    Returns
    -------
    str
        C code containing all necessary elements for this branch predictor.
    '''
    result = ''
    branch_count = 0
    branch_index = 0
    
    for line in c_code.splitlines():
        if '//BRANCHTAKEN' in line:
            branch_count += 1

    for line in c_code.splitlines():
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
                f'}}\n'
            )
        elif '//BRANCHNOTTAKEN' in line:
            result += (
                f'cond_branches[{branch_index}]++;\n'
                f'if(branch_bits[{branch_index}] == 2 || branch_bits[{branch_index}] == 3) {{\n'
                f'mispredictions[{branch_index}]++;\n'
                f'branch_bits[{branch_index}]--;\n'
                f'}}\n'
                f'else if(branch_bits[{branch_index}] == 1) {{\n'
                f'branch_bits[{branch_index}]--;\n'
                f'}}\n'
            )
            branch_index += 1
        else:
            result += f'{line}\n'

    return result[:-2]

def two_bit2(c_code: str) -> str:
    '''Another Branch prediction using two bits (bimodal predictor).

    Parameters
    ----------
    c_code : str
        The C code containing placeholders for the branch predictions.

    Returns
    -------
    str
        C code containing all necessary elements for this branch predictor.
    '''
    result = ''
    branch_count = 0
    branch_index = 0
    
    for line in c_code.splitlines():
        if '//BRANCHTAKEN' in line:
            branch_count += 1

    for line in c_code.splitlines():
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

def insert_branch_pred(c_code: str, method_name: str) -> str:
    '''Inserts the everything necessary for the desired branch
    prediction strategy.

    Parameters
    ----------
    c_code : str
        The C code containing placeholders for the branch predictions.
    method_name : str
        Name of the branch prediction strategy that should be used.

    Returns
    -------
    str
        C code containing all necessary elements to simulate branch predictions.
    '''
    if method_name == 'one_bit':
        return one_bit(c_code)
    elif method_name == 'two_bit1':
        return two_bit1(c_code)
    elif method_name == 'two_bit2':
        return two_bit2(c_code)

def is_branch_instr(opcode: str, *args) -> bool:
    '''Checks whether the given instruction is a branch instruction.

    Parameters
    ----------
    opcode : str
        Name of the instruction
    args : tuple(str)
        Operands for the instruction

    Returns
    -------
    bool
        Determines whether the instructions is a branch instruction.
    '''
    if re.match('(^b(?!ic$).*)|(^ldr.*)|(^ldm.*)|(^pop.*)', opcode):
        cond = False

        if re.match('(^ldr.*)|(^ldm.*)', opcode):
            digit_idx = re.search('\d', opcode).start()
            if opcode[digit_idx-2:digit_idx] in cond_codes:
                cond = True

        elif opcode[-2:] in cond_codes:
            cond = True

        return cond
        
    return False

def write_rates(file_path: str, blocks: list[CodeBlock],
                branch_rates: list[float], branch_map: dict[int, int]) -> None:
    asm_lines = []
    line_index = 0

    with open(file_path, 'r') as f:
        asm_lines = f.readlines()

    with open(file_path, 'w') as f:
        for block in blocks:
            for instr in block.instructions:
                if instr[0] != -1:

                    while line_index < instr[0]:
                        f.write(f'1.00 {asm_lines[line_index]}')
                        print(f'1.00 {asm_lines[line_index]}')
                        line_index += 1

                    if instr[0] in branch_map:
                        branch_rate = branch_rates[branch_map[instr[0]]]
                        branch_str = '{:.2f}'.format(branch_rate)
                        f.write(f'{branch_str} {asm_lines[line_index]}')
                        print(f'{branch_str} {asm_lines[line_index]}')
                    else:
                        f.write(f'1.00 {asm_lines[line_index]}')
                        print(f'1.00 {asm_lines[line_index]}')
                    
                    line_index += 1
        
        
    # with open(file_path, 'w') as f:
    #     for i, block in enumerate(blocks):
    #         for instr in block.instructions:
    #             while line_index < instr[0]:
    #                 f.write(f'0 {asm_lines[line_index]}')
    #                 line_index += 1
    #             f.write(f'{block_counts[i]} {asm_lines[line_index]}')
    #             line_index += 1
        
    

methods = ['one_bit', 'two_bit1', 'two_bit2']
cond_codes = ['eq', 'ne', 'ge', 'gt', 'le', 'lt', 'ls', 'cs',
              'cc', 'hi', 'mi', 'pl', 'al', 'nv', 'vs', 'vc']