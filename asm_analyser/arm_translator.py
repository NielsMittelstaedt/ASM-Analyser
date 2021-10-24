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
    if instruction != 'bl':
        for i, op in enumerate(args):
            if not re.match('^-?\d+$', op) and op != 'sp' and op != 'fp':
                new_args[i] = f'{args[i]}.i'

    translation = ''

    if instruction in long_instructions:
        if instruction == 'pop':
            for i in range(len(new_args)):
                translation += f'{new_args[i]} = 0;\nfor(int i=0;i<4;i++){new_args[i]}+=(stack[sp+({i}*4)+i] << 8*i) & 0xff;\n'
            translation += f'sp += {len(new_args)*4};\n'

        elif instruction == 'push':
            translation += f'sp -= {len(new_args)*4};\n'
            for i in range(len(new_args)):
                translation += f'for(int i=0;i<4;i++)stack[sp+({i}*4)+i] = ({new_args[i]} >> (8*i)) & 0xff;\n'

        # TODO
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
    'sub': '{0} = {1} - {2};\n',
    'str1': '{1} += {2};\nfor(int i=0;i<4;i++)stack[{1}+i] = ({0}>>(8*i)) & 0xff;\n',
    'str2': 'for(int i=0;i<4;i++)stack[{1}+({2})+i] = ({0}>>(8*i)) & 0xff;\n',
    #'ldr1': '({0} = stack[{1}] & 0xff) + ((stack[{1}+1] << 8) & 0xff) + ((stack[{1}+2] << 16) & 0xff) + ((stack[{1}+3] << 24) & 0xff);\n{1} += {2};\n',
    #'ldr2': '({0} = stack[{1}+({2})] & 0xff) + ((stack[{1}+({2})+1] << 8) & 0xff) + ((stack[{1}+({2})+2] << 16) & 0xff) + ((stack[{1}+({2})+3] << 24) & 0xff);\n',
    'ldr1': '{0} = 0;\nfor(int i=0;i<4;i++){0} += (stack[{1}+i] << 8*i) & 0xff;\n{1} += {2};\n',
    'ldr2': '{0} = 0;\nfor(int i=0;i<4;i++){0} += (stack[{1}+({2})+i] << 8*i) & 0xff;\n',
    'mov': '{0} = {1};\n',
    'movt': '{0} = ({1} << 16) | {0};\n',
    'movw': '{0} = {0} | {1};\n',
    'nop': '',
    'bx': 'return r0;\n',
    'bl': 'r0.i = {0}(r0).i;\n',
    'ctr': 'counter{0} ++;\n',
    'cmp': 'cond_reg = {0} > {1} ? 1 : ({0} < {1} ? -1 : 0);\n',
    'and': '{0} = {1} & {2};\n',
    'rsblt': '{0} = {1} < {2} ? {2} - {1} : {0};\n',
    'bgt': 'if (cond_reg == 1){{\n',
    'b': '',
    'ldrb1': '{0} = stack[{1}+({2})] & 0xff;\n',
    'ldrb2': '{0} = *(malloc_0+{1}) & 0xff;\n',
    'ldrb3': '{0} = *(malloc_0+{1}+{2}) & 0xff;\n',
    'strb1': 'stack[{1}+({2})] = {0} & 0xff;\n',
    'strb2': '*(malloc_0+{1}) = {0} & 0xff;\n',
    'strb3': '*(malloc_0+{1}+{2}) = {0} & 0xff;\n'
}