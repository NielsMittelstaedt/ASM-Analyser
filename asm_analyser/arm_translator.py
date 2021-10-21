import re

long_instructions = ['pop', 'push', 'pople']

def translate(instruction: str, *args):
    '''Translates an arm instruction to C using a dictionary.

    Parameters
    ----------
    instruction : str
        Name of the instruction
    args : tuple(str)
        Operands for the instruction

    Returns
    -------
    str
        The translated C code
    '''
    # append suffix for the reg union
    new_args = [*args]
    instr_suffix = 'f' if instruction[0] == 'f' else 'i'
    if instruction != 'bl':
        for i, op in enumerate(args):
            if not re.match('^-?\d+$', op) and op != 'sp' and op != 'fp':
                new_args[i] = f'{args[i]}.{instr_suffix}'

    translation = ''

    if instruction in long_instructions:
        if instruction == 'pop':
            for i in range(len(new_args)):
                translation += f'{new_args[i]} = stack[sp+{i}];\n'
            translation += f'sp += {len(new_args)};\n'

        elif instruction == 'push':
            translation += f'sp -= {len(new_args)};\n'
            for i in range(len(new_args)):
                translation += f'stack[sp+{i}] = {new_args[i]};\n'

        elif instruction == 'pople':
            translation += f'if (cond_reg <= 0){{\n'
            for i in range(len(new_args)):
                translation += f'{new_args[i]} = stack[sp+{i}];\n'
            translation += f'sp += {len(new_args)};\n'
            translation += f'}}\n'
        
    else:
        translation = translations[instruction].format(*new_args)

    # translate instruction
    return translation

translations = {
    'add': '{0} = {1} + {2};\n',
    'fadd': '{0} = {1} + {2};\n',
    'fsub': '{0} = {1} - {2};\n',
    'fmul': '{0} = {1} * {2};\n',
    'fdiv': '{0} = {1} / {2};\n',
    'sub': '{0} = {1} - {2};\n',
    'str1': '{1} += {2};\nstack[{1}] = {0};\n',
    'str2': 'stack[{1}+({2})] = {0};\n',
    'ldr1': '{0} = stack[{1}];\n{1} += {2};\n',
    'ldr2': '{0} = stack[{1}+({2})];\n',
    'mov': '{0} = {1};\n',
    'movt': '{0} = ({1} << 16) | {0};\n',
    'nop': '',
    'bx': 'return r0;\n',
    'bl': 'r0.i = {0}(r0).i;\n',
    'ctr': 'counter{0} ++;\n',
    'cmp': 'cond_reg = {0} > {1} ? 1 : ({0} < {1} ? -1 : 0);\n',
    'and': '{0} = {1} & {2};\n',
    'rsblt': '{0} = {1} < {2} ? {2} - {1} : {0};\n',
    'bgt': 'if (cond_reg == 1){{\n',
    'b': '',
}