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

    # some instructions are handled differently
    if re.match(exception_re, opcode):# translate ldrd and strd to two instructions
        if re.match('(^ldrd.*)|(^strd.*)', opcode):
            opcode = opcode[:3]+opcode[4:]
            reg1 = re.sub(r'[0-9]+$',
                          lambda x: f"{str(int(x.group())+1).zfill(len(x.group()))}",
                          args[0])
            if reg1 == 'r11':
                reg1 = 'fp'
            args1 = [reg1, *args[1:-1],
                     re.sub(r'-?[0-9]+$',
                            lambda x: f"{str(int(x.group())+4).zfill(len(x.group()))}",
                            args[-1])]
            translation += _translate_exceptions(opcode, args)
            return translation + _translate_exceptions(opcode, args1)
        return translation + _translate_exceptions(opcode, args)

    # separate the condition code and status flag from the opcode
    opcode, status, condition = _match_instruction(opcode)

    if not opcode:
        print('opcode missing')
        _save_missing(opcode+status+condition, args)
        return ''

    translation += translations[opcode].format(*args)

    if status:
        translation += _translate_status(opcode, args)

    if condition:
        return cond_translations[condition]+translation+'}\n'

    return translation

def _match_instruction(opcode: str) -> tuple[str, str, str]:
    '''TODO
    '''
    # in this case we do not have a condition code
    if len(opcode) == 1 or opcode[-2:] not in cond_translations:
        if opcode in translations:
            return opcode, '', ''
        elif opcode[-1] == 's' and opcode[:-1] in translations:
            return opcode[:-1], 's', ''
        else:
            return '', '', ''
    # in this case the condition code matches (this could be false positive)
    else:
        if opcode[:-2] in translations:
            return opcode[:-2], '', opcode[-2:]
        elif (len(opcode) > 3 and opcode[-3] == 's' and
              opcode[:-3] in translations):
            return opcode[:-3], 's', opcode[-2:]
        elif opcode in translations:
            return opcode, '', ''
        elif opcode[-1] == 's' and opcode[:-1] in translations:
            return opcode[:-1], 's', ''
        else:
            return '', '', ''

def _translate_exceptions(opcode: str, args: list[str]) -> str:
    '''TODO
    load and store instructions will be handled separately
    '''
    translation = ''

    if re.match('(^ldr.*)|(^str.*)', opcode):
        # parameters
        bytes, update, post_index, signed = '4', 'false', 'false', 'false'
        op = 'ldr' if 'ldr' in opcode else 'str'

        # look for byte str or ldr
        if opcode[3] == 'b' or opcode[3:5] == 'sb':
            bytes = '1'
            signed = 'true' if opcode[3:5] == 'sb' else 'false'
        elif opcode[3] == 'h' or opcode[3:5] == 'sh':
            bytes = '2'
            signed = 'true' if opcode[3:5] == 'sh' else 'false'

        # look for index update
        if opcode[-2] == '1':
            update = 'true'

        # look for post-indexed addressing
        if opcode[-1] == '1':
            post_index = 'true'

        if re.match('^L(C|\d).*', args[1]):
            translation += f'{op}(&{args[0]}.i, &{args[1]}, {args[2]}, {bytes}, {update}, {post_index}, {signed});\n'
        else:
            translation += f'{op}(&{args[0]}.i, &{args[1]}.i, {args[2]}, {bytes}, {update}, {post_index}, {signed});\n'

        #translation += f'{op}(&{args[0]}.i, &{args[1]}.i, {args[2]}, {bytes}, {update}, {post_index}, {signed});\n'
    # TODO: support other instructions than only ldmia and look for exclamation mark
    elif re.match('(^ldm.*)|(^stm.*)|(^push.*)|(^pop.*)', opcode):
        translation += _translate_stm_ldm(opcode, args)

    if re.match('(^ldr.*)|(^ldm.*)|(^pop.*)', opcode) and 'pc' in args:
        translation += 'return;\n'

    if opcode[-4:-2] in cond_translations:
        return cond_translations[opcode[-4:-2]] + translation + '}\n'
    elif (re.match('(^push.*)|(^pop.*)', opcode) and
            opcode[-2:] in cond_translations):
        return cond_translations[opcode[-2:]] + translation + '}\n'
    
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

def _translate_status(opcode: str, args: list[str]) -> str:
    '''TODO (explain suffix s)
    '''
    result = ''

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

    return result

def _translate_stm_ldm(opcode: str, args: list[str]) -> str:
    '''TODO
    '''
    translation = ''

    # translate push and pop to stmdb and ldmia
    if re.match('^push.*', opcode):
        opcode = opcode.replace('push', 'stmdb') + '01'
        args = ['sp', *args]
    elif re.match('^pop.*', opcode):
        opcode = opcode.replace('pop', 'ldmia') + '01'
        args = ['sp', *args]

    op = 'ldr' if 'ldm' in opcode else 'str'
    change_addr = True if opcode[-1] == '1' else False

    opcode = opcode[:-2]
    opcode = re.sub('(^ldm)|(^stm)', '', opcode)
    if opcode[-2:] in cond_translations:
        opcode = opcode[:-2]

    if not change_addr:
        translation += f'tmp = {args[0]}.i;\n'

    if opcode == '' or opcode == 'ia':
        for i in range(1, len(args)):
            translation += f'{op}(&{args[i]}.i, &{args[0]}.i, 0, 4, false, false, false);\n'
            translation += f'{args[0]}.i += 4;\n'

    elif opcode == 'ib':
        for i in range(1, len(args)):
            translation += f'{args[0]}.i += 4;\n'
            translation += f'{op}(&{args[i]}.i, &{args[0]}.i, 0, 4, false, false, false);\n'

    elif opcode == 'da':
        for i in reversed(range(1, len(args))):
            translation += f'{op}(&{args[i]}.i, &{args[0]}.i, 0, 4, false, false, false);\n'
            translation += f'{args[0]}.i -= 4;\n'

    elif opcode == 'db':
        for i in reversed(range(1, len(args))):
            translation += f'{args[0]}.i -= 4;\n'
            translation += f'{op}(&{args[i]}.i, &{args[0]}.i, 0, 4, false, false, false);\n'

    if not change_addr:
        translation += f'{args[0]}.i = tmp;\n'

    return translation


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
    'add': '{0} = {1} + ({2});\n',
    'adc': '{0} = {1} + ({2}) + c;\n',
    'sub': '{0} = {1} - ({2});\n',
    'sbc': '{0} = {1} - ({2}) - !c;\n',
    'mul': '{0} = ({1}) * ({2});\n',
    'mla': '{0} = (({1}) * ({2})) + ({3});\n',
    'mls': '{0} = {3} - (({1}) * ({2}));\n',
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
    'orr': '{0} = {1} | {2};\n',
    'umull': 'umull(&{0}, &{1}, &{2}, &{3});\n',
    'smull': 'smull(&{0}, &{1}, &{2}, &{3});\n',
    'tst': 'tmp = {0} & {1};\nz = tmp == 0;\nn = tmp & 0x80000000;\n',
    'teq': 'tmp = {1} ^ {2};\nz = tmp == 0;\nn = tmp & 0x80000000;\n',
    'uxtb': '{0} = 0xff & (uint8_t){1};\n',
    'uxth': '{0} = 0xffff & (uint16_t){1};\n',
    'uxtab': '{0} = (0xff & (uint8_t){2}) + {1};\n',
    'uxtah': '{0} = (0xffff & (uint16_t){2}) + {1};\n',
    'sxtb': '{0} = (0xff & {1}) << 24 >> 24;\n',
    'sxth': '{0} = (0xffff & {1}) << 16 >> 16;\n',
    'sxtab': '{0} = ((0xff & {2}) << 24 >> 24) + {1};\n',
    'sxtah': '{0} = ((0xffff & {2}) << 16 >> 16) + {1};\n',
    'ubfx': '{0} = ({1} >> {2}) & ((1 << {3}) - 1);\n'
}

cond_translations = {
    'eq': 'if (z){\n',
    'ne': 'if (!z){\n',
    'ge': 'if (n == v){\n',
    'gt': 'if (!z && n == v){\n',
    'le': 'if (z || n != v){\n',
    'lt': 'if (n != v){\n',
    # TODO: ls testen, da unterschiedliche infos online
    'ls': 'if (!c || z){\n',
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
