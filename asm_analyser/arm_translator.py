import re


def translate(opcode: str, *args) -> str:
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
    exception_re = '(^ldr.*)|(^str.*)|(^push.*)|(^pop.*)|(^b$)|(^bl.+)|(^b[^li].*)'

    # add suffix for the reg union in C
    if not re.match(exception_re, opcode) and opcode != 'bl':
        for i, op in enumerate(args):
            if not re.match('^-?\d+$', op):
                new_args[i] = f'{args[i]}.i'

    if re.match(exception_re, opcode):
        return _translate_exceptions(opcode, new_args)

    return translations[opcode].format(*new_args)


def _translate_exceptions(opcode: str, args: list[str]) -> str:
    '''TODO
    ldr, str, ldrb, strb, push, pop, bx will be handled separately
    '''
    translation = ''

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

        translation = f'{op}(&{args[0]}.i, &{args[1]}.i, {args[2]}, {byte}, {update}, {post_index});\n'
    elif re.match('(^push.*)|(^pop.*)', opcode):
        cond = cond_translations[opcode[-2:]
                                 ] if opcode[-2:] in cond_translations else ''

        if cond:
            translation += cond

        if 'pop' in opcode:
            for i in range(len(args)):
                translation += f'ldr(&{args[i]}.i, &sp.i, {i}*4, false, false, false);\n'
            translation += f'sp.i += {len(args)*4};\n'
            if 'pc' in args:
                translation += 'return r0;'
        elif 'push' in opcode:
            translation += f'sp.i -= {len(args)*4};\n'
            for i in range(len(args)):
                translation += f'str(&{args[i]}.i, &sp.i, {i}*4, false, false, false);\n'

        if cond:
            translation += '}\n'
    elif re.match('^bx.*', opcode):
        cond = cond_translations[opcode[-2:]
                                 ] if opcode[-2:] in cond_translations else ''

        if cond:
            translation += cond

        translation += 'return r0;\n'

        if cond:
            translation += '}\n'
    elif re.match('^b.*', opcode):
        cond = cond_translations[opcode[-2:]
                                 ] if opcode[-2:] in cond_translations else ''
        
        if cond:
            translation += cond

        translation += f'goto {args[0][1:]};\n'

        if cond:
            translation += '}\n'

    return translation


translations = {
    'add': '{0} = {1} + {2};\n',
    'sub': '{0} = {1} - {2};\n',
    'mov': '{0} = {1};\n',
    'movt': '{0} = ({1} << 16) | {0};\n',
    'movw': '{0} = {0} | {1};\n',
    'mvn': '{0} = ~{1};\n',
    'nop': '',
    'bx': 'return r0;\n',
    'bl': 'r0.i = {0}(r0).i;\n',
    'ctr': 'counter{0} ++;\n',
    'cmp': 'cond_reg = {0} > {1} ? 1 : ({0} < {1} ? -1 : 0);\n',
    'and': '{0} = {1} & {2};\n',
    'rsblt': '{0} = {1} < {2} ? {2} - {1} : {0};\n',
    'bic': '{0} = {1} & ~{2};\n'
}

cond_translations = {
    'eq': 'if (cond_reg == 0){\n',
    'ne': 'if (cond_reg != 0){\n',
    'ge': 'if (cond_reg >= 0){\n',
    'gt': 'if (cond_reg > 0){\n',
    'le': 'if (cond_reg <= 0){\n',
    'lt': 'if (cond_reg < 0){\n'
}
