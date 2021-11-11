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
    translation, args = _translate_shift(opcode, args)

    # translate the suffix condition codes
    has_cond, tmp, opcode = _translate_conds(opcode)
    translation += tmp

    # some instructions are handled differently
    if re.match(exception_re, opcode):
        translation += _translate_exceptions(opcode, args)
    else:
        # look for suffix 's'
        if re.match('^.*s$', opcode):
            if opcode[:-1] not in translations:
                _save_missing(opcode[:-1], args)
                return ''
            translation += translations[opcode[:-1]].format(*args)
        else:
            if opcode not in translations:
                _save_missing(opcode, args)
                return ''
            translation += translations[opcode].format(*args)

    # update the status bits if necessary
    tmp, opcode = _translate_status(opcode, args)
    translation += tmp

    if has_cond:
        translation += '}\n'

    return translation

def _translate_exceptions(opcode: str, args: list[str]) -> str:
    '''TODO
    ldr, str, ldm, stm, ldrb, strb, push, pop, will be handled separately
    '''
    translation = ''

    if re.match('(^ldr.*)|(^str.*)', opcode):
        # parameters
        bytes, update, post_index = '4', 'false', 'false'
        op = 'ldr' if 'ldr' in opcode else 'str'

        # look for byte str or ldr
        if opcode[3] == 'b':
            bytes = '1'
        elif opcode[3] == 'd':
            bytes = '8'

        # look for index update
        if opcode[-2] == '1':
            update = 'true'

        # look for post-indexed addressing
        if opcode[-1] == '1':
            post_index = 'true'

        translation += f'{op}(&{args[0]}.i, &{args[1]}.i, {args[2]}, {bytes}, {update}, {post_index});\n'
    # TODO: support other instructions than only ldmia and look for exclamation mark
    elif opcode == 'ldmia':
        for i in range(1, len(args)):
            translation += f'ldr(&{args[i]}.i, &{args[0]}.i, {i-1}*4, 4, false, false);\n'
        translation += f'{args[0]}.i += {(len(args)-1)*4};\n'
    elif opcode == 'ldmdb':
        translation += f'{args[0]}.i -= {(len(args)-1)*4};\n'
        for i in range(1, len(args)):
            translation += f'ldr(&{args[i]}.i, &{args[0]}.i, {i-1}*4, 4, false, false);\n'
    elif opcode == 'ldm':
        for i in range(1, len(args)):
            translation += f'ldr(&{args[i]}.i, &{args[0]}.i, {i-1}*4, 4, false, false);\n'
    elif opcode == 'stmdb':
        translation += f'{args[0]}.i -= {(len(args)-1)*4};\n'
        for i in range(1, len(args)):
                translation += f'str(&{args[i]}.i, &{args[0]}.i, {i-1}*4, 4, false, false);\n'
    elif opcode == 'stm':
        for i in range(1, len(args)):
            translation += f'str(&{args[i]}.i, &{args[0]}.i, {i-1}*4, 4, false, false);\n'
    elif opcode == 'stmia':
        for i in range(1, len(args)):
                translation += f'str(&{args[i]}.i, &{args[0]}.i, {i-1}*4, 4, false, false);\n'
        translation += f'{args[0]}.i += {(len(args)-1)*4};\n'

    elif re.match('(^push.*)|(^pop.*)', opcode):
        if 'pop' in opcode:
            for i in range(len(args)):
                translation += f'ldr(&{args[i]}.i, &sp.i, {i}*4, 4, false, false);\n'
            translation += f'sp.i += {len(args)*4};\n'
            if 'pc' in args:
                translation += 'return;\n'
        elif 'push' in opcode:
            translation += f'sp.i -= {len(args)*4};\n'
            for i in range(len(args)):
                translation += f'str(&{args[i]}.i, &sp.i, {i}*4, 4, false, false);\n'

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

def _translate_shift(opcode: str, args: list[str]) -> tuple[str, list[str]]:
    '''TODO
    '''
    translation = ''
    if len(args) > 2 and args[-2] in shift_translations:
        # for some opcodes, we need to update the carry flag
        if re.match('(^movs.*)|(^mvns.*)|(^ands.*)|(^orrs.*)|(^orns.*)|(^eors.*)|(^bics.*)|(^teq.*)|(^tst.*)', opcode):
            if 'ror' in args[-2] or 'lsr' in args[-2] or 'asr' in args[-2]:
                translation = f'c = {args[-3]} & (1 << {args[-1]} - 1);\n'
            elif 'lsl' in args[-2]:
                translation = f'c = {args[-3]} & ((uint32_t) 0x80000000 >> {args[-1]} - 1);\n'
                    
        return translation, [*args[:-3],
                shift_translations[args[-2]].format(args[-3], args[-1])]
    else:
        return translation, args

def _translate_conds(opcode: str) -> tuple[bool, str, str]:
    '''TODO
    returns has_cond, translation, new_opcode
    '''
    if re.match('(^ldr.*)|(^str.*)', opcode):
        if opcode[-4:-2] in cond_translations:
            return (True, cond_translations[opcode[-4:-2]],
                    opcode[:-4]+opcode[-2:])
    else:
        # prevent false translations
        if len(opcode) == 4 and opcode[:3] in translations:
            return False, '', opcode
        if opcode[-2:] in cond_translations:
            return True, cond_translations[opcode[-2:]], opcode[:-2]
    
    return False, '', opcode

def _translate_status(opcode: str, args: list[str]) -> tuple[str, str]:
    '''TODO (explain suffix s)
    '''
    result = ''

    if re.match('^.*s$', opcode):
        result += f'z = {args[0]} == 0;\n'
        result += f'n = {args[0]} & 0x80000000;\n'

        # update the carry flag depending on the operation
        if re.match('^ad.*', opcode):
            result += f'c = ((uint32_t) {args[0]}) < ((uint32_t) {args[1]});\n'
            result += f'v = ({args[1]}&0x80000000) == ({args[2]}&0x80000000) && ({args[0]}&0x80000000) != ({args[1]}&0x80000000);\n'
        elif re.match('(^sub.*)|(^rsb.*)|(^sbc.*)', opcode):
            result += f'c = ((uint32_t) {args[1]}) >= ((uint32_t) {args[2]});\n'
            result += f'v = ({args[1]}&0x80000000) != ({args[2]}&0x80000000) && ({args[0]}&0x80000000) != ({args[1]}&0x80000000);\n' 
        elif re.match('(^ror.*)|(^lsr.*)|(^asr.*)', opcode):
            result += f'c = {args[1]} & (1 << {args[2]} - 1);\n'
        elif re.match('^lsl.*', opcode):
            result += f'c = {args[1]} & ((uint32_t) 0x80000000 >> {args[2]} - 1);\n'
        
        opcode = opcode[:-1]

    return result, opcode

def _save_missing(opcode: str, args) -> None:
    '''TODO
    '''
    print('opcode is missing in translations')
    file = open('missing_translations.txt', 'a')
    file.write(f'{opcode} {" ".join(args)}\n')
    file.close()

translations = {
    'ctr': 'counters[{0}] ++;\n',
    'memctr0': 'load_counter ++;\n',
    'memctr1': 'store_counter ++;\n',
    'add': '{0} = {1} + {2};\n',
    'adc': '{0} = {1} + {2} + c;\n',
    'sub': '{0} = {1} - {2};\n',
    'sbc': '{0} = {1} - {2} - !c;\n',
    'mul': '{0} = {1} * {2};\n',
    'mla': '{0} = ({1} * {2}) + {3};\n',
    'mov': '{0} = {1};\n',
    'movt': '{0} = {0} | ({1} << 16);\n',
    'movw': '{0} = {1};\n',
    'mvn': '{0} = ~{1};\n',
    'nop': '',
    'b': 'goto {0};\n',
    'bx': 'return;\n',
    'bl': '{0}();\n',
    'cmp': 'tmp = {0} - {1};\nz = tmp == 0;\nn = tmp & 0x80000000;\nc = ((uint32_t) {0}) >= ((uint32_t) {1});\nv = ({0}&0x80000000) != ({1}&0x80000000) && (tmp&0x80000000) != ({0}&0x80000000);\n',
    'cmn': 'tmp = {0} + {1};\nz = tmp == 0;\nn = tmp & 0x80000000;\nc = ((uint32_t) tmp) < ((uint32_t) {0});\nv = ({0}&0x80000000) == ({1}&0x80000000) && (tmp&0x80000000) != ({0}&0x80000000);\n',
    'and': '{0} = {1} & {2};\n',
    'bic': '{0} = {1} & ~{2};\n',
    'rsb': '{0} = {2} - {1};\n',
    'ror': '{0} = ((uint32_t){1} >> {2}) | ((uint32_t){1} << (32-{2}));\n',
    'lsr': '{0} = (uint32_t){1} >> {2};\n',
    'asr': '{0} = {1} >> {2};\n',
    'lsl': '{0} = (uint32_t){1} << {2};\n',
    'eor': '{0} = {1} ^ {2};\n',
    'orr': '{0} = {1} | {2};\n'
}

cond_translations = {
    'eq': 'if (z){\n',
    'ne': 'if (!z){\n',
    'ge': 'if (n == v){\n',
    'gt': 'if (!z && n == v){\n',
    'le': 'if (z || n != v){\n',
    'lt': 'if (n != v){\n',
    'ls': 'if (!c || z){\n', #TODO: ls testen, da unterschiedliche infos online
    'cs': 'if (c){\n',
    'cc': 'if (!c){\n',
    'hi': 'if (c && !z){\n',
    'mi': 'if (n){\n',
    'pl': 'if (!n){\n',
    'al': 'if (true){\n',
    'nv': 'if (false){\n',
    'vs': 'if (v){\n',
    'vc': 'if (!v){\n'
}

shift_translations = {
    'lsr': '((uint32_t){0} >> {1})',
    'asr': '({0} >> {1})',
    'lsl': '((uint32_t){0} << {1})',
    'ror': '(((uint32_t){0} >> {1}) | ((uint32_t){0} << (32-{1})))'
}