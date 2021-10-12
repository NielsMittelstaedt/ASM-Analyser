import re


def translate(instruction: str, *args):
    '''Translates an arm instruction to C using a dictionary.

    Parameters
    ----------
    instruction : str
        Name of the instruction
    operand1 : str
        First operand
    operand2 : str
        Second operand
    operand3 : str
        Third operand

    Returns
    -------
    str
        The translated C code
    '''
    new_args = [*args]
    instr_suffix = 'f' if instruction[0] == 'f' else 'i'

    if instruction != 'bl':
        for i, op in enumerate(args):
            if not re.match('^-?\d+$', op) and op != 'sp' and op != 'fp':
                new_args[i] = f'{args[i]}.{instr_suffix}'

    return translations[instruction].format(*new_args)

# TODO: generalize push and pop for arbitrarly length
translations = {
    'add': '{0} = {1} + {2};\n',
    'fadd': '{0} = {1} + {2};\n',
    'sub': '{0} = {1} - {2};\n',
    'str1': '{1} += {2};\nstack[{1}] = {0};\n',
    'str2': 'stack[{1}+({2})] = {0};\n',
    'ldr1': '{0} = stack[{1}];\n{1} += {2};\n',
    'ldr2': '{0} = stack[{1}+({2})];\n',
    'push1': 'sp -= 1;\nstack[sp] = {0};\n',
    'push2': 'sp -= 2;\nstack[sp] = {0};\nstack[sp+1] = {1};\n',
    'push3': 'sp -= 3;\nstack[sp] = {0};\nstack[sp+1] = {1};\nstack[sp+2] = {2};\n',
    'pop1': '{0} = stack[sp];\nsp += 1;\n',
    'pop2': '{0} = stack[sp];\n{1} = stack[sp + 1];\nsp += 2;\n',
    'pop3': '{0} = stack[sp];\n{1} = stack[sp + 1];\n{2} = stack[sp + 2];\nsp += 3;\n',
    'mov': '{0} = {1};\n',
    'movt': '{0} = ({1} << 16) | {0};\n',
    'nop': '',
    'bx': 'return r0;\n',
    'bl': 'r0.i = {0}(r0).i;\n',
    'ctr': 'counter += {0};\n',
    'cmp': 'cond_reg = {0} > {1} ? 1 : ({0} < {1} ? -1 : 0);\n',
    'and': '{0} = {1} & {2};\n',
    'rsblt': '{0} = {1} < {2} ? {2} - {1} : {0};\n',
    'bgt': 'if (cond_reg == 1){{\n',
    'b': '',
}