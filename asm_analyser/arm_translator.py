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
    args = [*args]
    exception_re = '(^ld.*)|(^st.*)|(^push.*)|(^pop.*)'

    args = _append_suffix(opcode, args)
    args = _translate_shift(args)

    if re.match(exception_re, opcode):
        return _translate_exceptions(opcode, args)
    else:
        # check if instruction uses condition codes
        if opcode[-2:] in cond_translations:
            translation = cond_translations[opcode[-2:]]
            translation += translations[opcode[:-2]].format(*args)
            return translation + '}\n'
        else:
            # add missing opcodes to list
            if opcode not in translations:
                print('opcode is missing in translations')
                file = open('missing_translations.txt', 'a')
                file.write(f'{opcode} {" ".join(args)}\n')
                file.close()
                return ''
            else:
                return translations[opcode].format(*args)

def _translate_exceptions(opcode: str, args: list[str]) -> str:
    '''TODO
    ldr, str, ldrb, strb, push, pop, will be handled separately
    '''
    translation = ''
    # check for conditional suffix
    if re.match('(^ldr.*)|(^str.*)', opcode):
        if opcode[-4:-2] in cond_translations:
            translation += cond_translations[opcode[-4:-2]]
            opcode = opcode[:-4]+opcode[-2:]
    else:
        if opcode[-2:] in cond_translations:
            translation += cond_translations[opcode[-2:]]
            opcode = opcode[:-2]

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

        translation += f'{op}(&{args[0]}.i, &{args[1]}.i, {args[2]}, {byte}, {update}, {post_index});\n'
    # TODO: support other instructions than only ldmia and look for exclamation mark
    elif opcode == 'ldmia':
        for i in range(1, len(args)):
            translation += f'ldr(&{args[i]}.i, &{args[0]}.i, {i-1}*4, false, false, false);\n'
        translation += f'{args[0]}.i += {(len(args)-1)*4};\n'
    elif opcode == 'ldmdb':
        translation += f'{args[0]}.i -= {(len(args)-1)*4};\n'
        for i in range(1, len(args)):
            translation += f'ldr(&{args[i]}.i, &{args[0]}.i, {i-1}*4, false, false, false);\n'
    elif opcode == 'ldm':
        for i in range(1, len(args)):
            translation += f'ldr(&{args[i]}.i, &{args[0]}.i, {i-1}*4, false, false, false);\n'
    elif opcode == 'stmdb':
        translation += f'{args[0]}.i -= {(len(args)-1)*4};\n'
        for i in range(1, len(args)):
                translation += f'str(&{args[i]}.i, &{args[0]}.i, {i-1}*4, false, false, false);\n'
    elif opcode == 'stm':
        for i in range(1, len(args)):
            translation += f'str(&{args[i]}.i, &{args[0]}.i, {i-1}*4, false, false, false);\n'
    elif opcode == 'stmia':
        for i in range(1, len(args)):
                translation += f'str(&{args[i]}.i, &{args[0]}.i, {i-1}*4, false, false, false);\n'
        translation += f'{args[0]}.i += {(len(args)-1)*4};\n'

    elif re.match('(^push.*)|(^pop.*)', opcode):
        if 'pop' in opcode:
            for i in range(len(args)):
                translation += f'ldr(&{args[i]}.i, &sp.i, {i}*4, false, false, false);\n'
            translation += f'sp.i += {len(args)*4};\n'
            if 'pc' in args:
                translation += 'return;'
        elif 'push' in opcode:
            translation += f'sp.i -= {len(args)*4};\n'
            for i in range(len(args)):
                translation += f'str(&{args[i]}.i, &sp.i, {i}*4, false, false, false);\n'

    if 'cond_reg' in translation[:15]:
            translation += '}\n'

    return translation

def _append_suffix(opcode: str, args: list[str]) -> list[str]:
    '''TODO
    add suffix for the reg union in C
    '''
    suffix_re = '(^ld.*)|(^st.*)|(^push.*)|(^pop.*)|(^b$)|(^b[^i].*)'
    reg_re = '(^r[0-9]{1,2}$)|(^sp$)|(^fp$)|(^lr$)|(^pc$)|(^ip$)'

    if not re.match(suffix_re, opcode) and opcode != 'bl':
        for i, op in enumerate(args):
            if re.match(reg_re, op):
                args[i] = f'{args[i]}.i'
    elif (re.match('(^ldr.*)|(^str.*)', opcode) and
          re.match(reg_re, args[2])):
        args[2] = f'{args[2]}.i'

    return args

def _translate_shift(args: list[str]) -> list[str]:
    '''TODO
    '''
    if len(args) > 2 and args[-2] in shift_translations:
        return [*args[:-3],
                shift_translations[args[-2]].format(args[-3], args[-1])]
    else:
        return args


translations = {
    'ctr': 'counter{0} ++;\n',
    'add': '{0} = {1} + {2};\n',
    'sub': '{0} = {1} - {2};\n',
    'mov': '{0} = {1};\n',
    'movt': '{0} = {0} | ({1} << 16);\n',
    'movw': '{0} = {1};\n',
    'mvn': '{0} = ~{1};\n',
    'nop': '',
    'b': 'goto {0};\n',
    'bx': 'return;\n',
    'bl': '{0}();\n',
    'cmp': 'cond_reg = {0} > {1} ? 1 : ({0} < {1} ? -1 : 0);\n',
    'cmn': 'cond_reg = {0} > -({1}) ? 1 : ({0} < -({1}) ? -1 : 0);\n',
    'and': '{0} = {1} & {2};\n',
    'bic': '{0} = {1} & ~{2};\n',
    'rsb': '{0} = {2} - {1};\n',
    'ror': '{0} = ((uint32_t){1} >> {2}) | ((uint32_t){1} << (32-{2}));\n',
    'lsr': '{0} = (uint32_t){1} >> {2};\n',
    'asr': '{0} = {1} >> {2};\n',
    'lsl': '{0} = (uint32_t){1} << {2};\n',
    'eors': '{0} = {1} ^ {2};\n'
}

cond_translations = {
    'eq': 'if (cond_reg == 0){\n',
    'ne': 'if (cond_reg != 0){\n',
    'ge': 'if (cond_reg >= 0){\n',
    'gt': 'if (cond_reg > 0){\n',
    'le': 'if (cond_reg <= 0){\n',
    'lt': 'if (cond_reg < 0){\n'
}

shift_translations = {
    'lsr': '((uint32_t){0} >> {1})',
    'asr': '({0} >> {1})',
    'lsl': '((uint32_t){0} << {1})',
    'ror': '(((uint32_t){0} >> {1}) | ((uint32_t){0} << (32-{1})))'
}