import re

long_instructions = ['pop', 'push', 'pople']

def translate(opcode: str, *args):
    '''Translates an arm instruction to C using a dictionary.

    Parameters
    ----------
    opcode : str
        Name of the instruction
    args : tuple(str)
        Operands for the instruction

    Returns
    -------
    str
        The translated C code
    '''
    new_args = [*args]
    translation = ''

    # add suffix for the reg union in C
    if not re.match('(^ldr.*)|(^str.*)|(^bl.*)|(^push.*)|(^pop.*)', opcode):
        for i, op in enumerate(args):
            if not re.match('^-?\d+$', op):
                new_args[i] = f'{args[i]}.i'

    
    # ldr, str, ldrb, strb will be handled separately
    if re.match('(^ldr.*)|(^str.*)', opcode):
        # parameters
        byte, update, post_index = 'false', 'false', 'false'
        op = 'ldr' if 'ldr' in opcode else 'str'
        
        # look for byte str or ldr
        if opcode[3] == 'b':
            byte = 'true'

        # look for index update 
        if opcode[-2] == '1':
            update = 'true'

        # look for post-indexed addressing
        if opcode[-1] == '1':
            post_index = 'true'

        translation = f'{op}(&{new_args[0]}.i, &{new_args[1]}.i, {new_args[2]}, {byte}, {update}, {post_index});\n'
    else:
        # translate longer instructions
        if opcode in long_instructions:
            if opcode == 'pop':
                for i in range(len(new_args)):
                    translation += f'ldr(&{new_args[i]}.i, &sp.i, {i}*4, false, false, false);\n'
                    #translation += f'{new_args[i]} = 0;\nfor(int i=0;i<4;i++){new_args[i]}+=(stack[sp+({i}*4)+i] << 8*i) & 0xff;\n'
                translation += f'sp.i += {len(new_args)*4};\n'
            elif opcode == 'push':
                translation += f'sp.i -= {len(new_args)*4};\n'
                for i in range(len(new_args)):
                    translation += f'str(&{new_args[i]}.i, &sp.i, {i}*4, false, false, false);\n'
                    #translation += f'for(int i=0;i<4;i++)stack[sp+({i}*4)+i] = ({new_args[i]} >> (8*i)) & 0xff;\n'

            # TODO
            elif opcode == 'pople':
                translation += f'if (cond_reg <= 0){{\n'
                for i in range(len(new_args)):
                    translation += f'{new_args[i]} = stack[sp+{i}];\n'
                translation += f'sp += {len(new_args)};\n'
                translation += f'}}\n'

        # translate all other instructions  
        else:
            translation = translations[opcode].format(*new_args)

    return translation

translations = {
    'add': '{0} = {1} + {2};\n',
    'sub': '{0} = {1} - {2};\n',
    #'str1': '{1} += {2};\nfor(int i=0;i<4;i++)stack[{1}+i] = ({0}>>(8*i)) & 0xff;\n',
    #'str2': 'for(int i=0;i<4;i++)stack[{1}+({2})+i] = ({0}>>(8*i)) & 0xff;\n',
    #'str3': 'for(int i=0;i<4;i++)*(malloc_0+{1}+i) = ({0}>>(8*i)) & 0xff;\n',
    #'ldr_stack1': 'ldr_stack(&{0}, {1});\n{1} += {2};\n',
    #'ldr_stack2': 'ldr_stack(&{0}, {1}+({2}));\n',
    #'ldr1': '',
    #'ldr2': '',
    #'ldr1': '{0} = 0;\nfor(int i=0;i<4;i++){0} += (stack[{1}+i] << 8*i) & 0xff;\n{1} += {2};\n',
    #'ldr2': '{0} = 0;\nfor(int i=0;i<4;i++){0} += (stack[{1}+({2})+i] << 8*i) & 0xff;\n',
    #'ldr3': '{0} = 0;\nfor(int i=0;i<4;i++){0} += (*(malloc_0+{1}+i) << 8*i) & 0xff;\n',
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
    #'ldrb1': '{0} = stack[{1}+({2})] & 0xff;\n',
    #'ldrb2': '{0} = *(malloc_0+{1}) & 0xff;\n',
    #'ldrb3': '{0} = *(malloc_0+{1}+{2}) & 0xff;\n',
    #'strb1': 'stack[{1}+({2})] = {0} & 0xff;\n',
    #'strb2': '*(malloc_0+{1}) = {0} & 0xff;\n',
    #'strb3': '*(malloc_0+{1}+{2}) = {0} & 0xff;\n'
}