# bei conditional b, bx, (pop, load mit pc)
# muss die branch prediction eingebaut werden.

# Wir brauchen zwei globale variablen für die Anzahl conditional branches
# und die Anzahl Misspredictions

# Bei einem conditional branch wird je nach if auswertung dann
# die branch pred bits erhöht oder verringert und die misprediction gezählt

def one_bit(c_code: str):
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
            result += f'uint8_t branch_bits[{branch_count}] = {{0}};\n'
        elif '//BRANCHTAKEN' in line:
            result += (
                f'cond_branches ++;\n'
                f'if(branch_bits[{branch_index}] == 0) {{\n'
                f'mispredictions++;\n'
                f'branch_bits[{branch_index}] = 1;\n'
                f'}}\n'
            )
        elif '//BRANCHNOTTAKEN' in line:
            result += (
                f'cond_branches ++;\n'
                f'if(branch_bits[{branch_index}] == 1) {{\n'
                f'mispredictions++;\n'
                f'branch_bits[{branch_index}] = 0;\n'
                f'}}\n'
            )
            branch_index += 1
        else:
            result += f'{line}\n'

    return result[:-2]

def two_bit(c_code: str):
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
            result += f'uint8_t branch_bits[{branch_count}] = {{0}};\n'
        elif '//BRANCHTAKEN' in line:
            result += (
                f'cond_branches ++;\n'
                f'if(branch_bits[{branch_index}] == 0 || branch_bits[{branch_index}] == 1) {{\n'
                f'mispredictions++;\n'
                f'branch_bits[{branch_index}]++;\n'
                f'}}\n'
                f'else if(branch_bits[{branch_index}] == 2) {{\n'
                f'branch_bits[{branch_index}]++;\n'
                f'}}\n'
            )
        elif '//BRANCHNOTTAKEN' in line:
            result += (
                f'cond_branches ++;\n'
                f'if(branch_bits[{branch_index}] == 2 || branch_bits[{branch_index}] == 3) {{\n'
                f'mispredictions++;\n'
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