'''Responsible for translating the ARM instructions.
'''
import re
from typing import List, Tuple
from asm_analyser.architectures.arm import auxiliary_functions
from asm_analyser.blocks.code_block import CodeBlock


def translate(code_blocks: List[CodeBlock], opcode: str, *args) -> str:
    '''Translates an arm instruction to C using a dictionary.

    Parameters
    ----------
    code_blocks: list[CodeBlock]
        The code blocks containing all the instructions
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
    input_args = args.copy()
    args = _add_pre_suffix(opcode, args)
    translation, args = _translate_shift(opcode, args)

    # memory instructions (loading and storing) are handled differently
    if re.match('(^ld.*)|(^st.*)|(^push.*)|(^pop.*)', opcode):
        return translation + _translate_mem_acc(opcode, args)
    # branch instructions aswell
    elif re.match('^b(?!ic$).*', opcode):
        return translation + _translate_branch(opcode, args, code_blocks)

    # separate the condition code and status flag from the opcode
    complete_opcode = opcode
    opcode, status, condition = _match_instruction(opcode)

    if not opcode:
        print('Opcode is missing in translations:')
        print(f'{complete_opcode} {" ".join(input_args)}\n')
        return ''

    translation += TRANSLATIONS[opcode].format(*args)

    if status:
        translation += _translate_status(opcode, args)

    if condition:
        return COND_TRANSLATIONS[condition] + translation + '}\n'

    return translation


def _match_instruction(opcode: str) -> Tuple[str, str, str]:
    '''Divides the opcode into the opcode itself, the status bit and the
    condition code.

    Parameters
    ----------
    opcode : str
        Complete opcode in ARM assembly.

    Returns
    -------
    str
        Opcode without suffix.
    str
        Status bit if used.
    str
        Condition code if used.
    '''
    # in this case we do not have a condition code
    if len(opcode) == 1 or opcode[-2:] not in COND_TRANSLATIONS:
        if opcode in TRANSLATIONS:
            return opcode, '', ''
        elif opcode[-1] == 's' and opcode[:-1] in TRANSLATIONS:
            return opcode[:-1], 's', ''
        else:
            return '', '', ''
    # in this case the condition code matches (this could be false positive)
    else:
        if opcode[:-2] in TRANSLATIONS:
            return opcode[:-2], '', opcode[-2:]
        elif (len(opcode) > 3 and opcode[-3] == 's' and
              opcode[:-3] in TRANSLATIONS):
            return opcode[:-3], 's', opcode[-2:]
        elif opcode in TRANSLATIONS:
            return opcode, '', ''
        elif opcode[-1] == 's' and opcode[:-1] in TRANSLATIONS:
            return opcode[:-1], 's', ''
        else:
            return '', '', ''


def _translate_mem_acc(opcode: str, args: List[str]) -> str:
    '''Translates instructions that load from or store into memory.

    These instructions are handled differently as there are a few
    variations for each of these opcode.

    Parameters
    ----------
    opcode : str
        Opcode in ARM assembly.
    args : list[str]
        Arguments passed to the opcode.

    Returns
    -------
    str
        C translation of the ARM instruction.
    '''
    translation = ''
    cond_code = ''

    # split condition code from opcode
    if 'push' not in opcode and 'pop' not in opcode:
        digit_idx = re.search('\d', opcode).start()

        if opcode[digit_idx - 2:digit_idx] in COND_TRANSLATIONS:
            opcode_cpy = opcode
            opcode = opcode_cpy[:digit_idx - 2] + opcode_cpy[digit_idx:]
            cond_code = opcode_cpy[digit_idx - 2:digit_idx]
    else:
        if opcode[-2:] in COND_TRANSLATIONS:
            cond_code = opcode[-2:]
            opcode = opcode[:-2]

    # translate ldr and str instructions for 1, 2, 4 and 8 bytes
    if re.match('(^ldr.*)|(^str.*)', opcode):
        if opcode[3] == '8':
            reg1 = re.sub('[0-9]+$',
                          lambda x: f"{str(int(x.group())+1)}",
                          args[0])
            if reg1 == 'r11':
                reg1 = 'fp'

            if re.match('^L(C|\d).*', args[1]):
                translation = f'{opcode}(&_asm_analysis_.{args[0]}.i, &_asm_analysis_.{reg1}.i, &{args[1]}, {args[2]});\n'
            else:
                translation = f'{opcode}(&_asm_analysis_.{args[0]}.i, &_asm_analysis_.{reg1}.i, &_asm_analysis_.{args[1]}.i, {args[2]});\n'
        else:
            if re.match('^L(C|\d).*', args[1]):
                translation = f'{opcode}(&_asm_analysis_.{args[0]}.i, &{args[1]}, {args[2]});\n'
            else:
                translation = f'{opcode}(&_asm_analysis_.{args[0]}.i, &_asm_analysis_.{args[1]}.i, {args[2]});\n'

    # translate ldm and stm
    elif re.match('(^ldm.*)|(^stm.*)', opcode):
        registers = ''

        if len(opcode) > 4 and (opcode[3:5] == 'da' or opcode[3:5] == 'db'):
            registers = '.i, &_asm_analysis_.'.join(reversed(args[1:]))
        else:
            registers = '.i, &_asm_analysis_.'.join(args[1:])

        registers = f'&_asm_analysis_.{registers}.i'

        translation = f'{opcode}(&_asm_analysis_.{args[0]}.i, {len(args)-1}, {registers});\n'

    # translate push and pop
    elif re.match('(^push.*)|(^pop.*)', opcode):
        registers = ''

        if 'pop' in opcode:
            registers = '.i, &_asm_analysis_.'.join(reversed(args))
        else:
            registers = '.i, &_asm_analysis_.'.join(args)

        registers = f'&_asm_analysis_.{registers}.i'

        translation = f'{opcode}({len(args)}, {registers});\n'

    if re.match('(^ldr.*)|(^ldm.*)|(^pop.*)', opcode) and 'pc' in args:
        if cond_code:
            translation += '//BRANCHTAKEN\n'
            return f'{COND_TRANSLATIONS[cond_code]}{translation}return;\n}}\n//BRANCHNOTTAKEN\n'

        translation += 'return;\n'

    if cond_code:
        return COND_TRANSLATIONS[cond_code] + translation + '}\n'
    else:
        return translation


def _translate_branch(opcode: str, args: List[str],
                      code_blocks: List[CodeBlock]) -> str:
    '''Translates branch instruction like b or bl.

    Parameters
    ----------
    opcode : str
        Opcode in ARM assembly.
    args : list[str]
        Arguments passed to the opcode.
    code_blocks : list[CodeBlock]
        List containing the labeled code blocks with their instructions.

    Returns
    -------
    str
        C translation of the ARM instruction.
    '''
    translation = ''
    cond_code = ''

    if opcode[-2:] in COND_TRANSLATIONS:
        cond_code = opcode[-2:]
        opcode = opcode[:-2]

    # translate library calls using auxiliary functions
    if args[0] in auxiliary_functions.CALL_DICT:
        if opcode == 'b':
            translation = auxiliary_functions.CALL_DICT[args[0]] + 'return;\n'
        else:
            translation = auxiliary_functions.CALL_DICT[args[0]]

    # we cannot use goto for functions
    if opcode == 'b':
        function = next((item for item in code_blocks
                         if item.name == args[0] and
                         item.is_function), None)
        if function is not None:
            translation = f'{args[0]}();\nreturn;\n'

    if not translation:
        translation = TRANSLATIONS[opcode].format(*args)

    if cond_code:
        return f'{COND_TRANSLATIONS[cond_code]}//BRANCHTAKEN\n{translation}}}\n//BRANCHNOTTAKEN\n'

    return translation


def _add_pre_suffix(opcode: str, args: List[str]) -> List[str]:
    '''This function is responsible for adding the .i or .f suffix to
    the registers of the union type in C. It also adds the prefix for
    the struct that is used in the template.

    Parameters
    ----------
    opcode : str
        Opcode in ARM assembly.
    args : list[str]
        Arguments passed to the opcode.

    Returns
    -------
    list[str]
        Arguments in which the registers now have the correct suffix and
        prefix for C.
    '''
    suffix_re = '(^ld.*)|(^st.*)|(^push.*)|(^pop.*)|(^b$)|(^b[^i].*)'
    reg_re = '(^r[0-9]{1,2}$)|(^sp$)|(^fp$)|(^lr$)|(^pc$)|(^ip$)'

    if not re.match(suffix_re, opcode) and opcode != 'bl':
        for i, op in enumerate(args):
            if re.match(reg_re, op):
                args[i] = f'_asm_analysis_.{args[i]}.i'
    elif (re.match('(^ldr.*)|(^str.*)', opcode) and
          re.match(reg_re, args[2])):
        args[2] = f'_asm_analysis_.{args[2]}.i'

    return args


def _translate_shift(opcode: str, args: List[str]) -> Tuple[str, List[str]]:
    '''Translates bit shifts which can be used within other instructions
    in ARM assembly.

    Parameters
    ----------
    opcode : str
        Opcode in ARM assembly.
    args : list[str]
        Arguments passed to the opcode.

    Returns
    -------
    str
        C code to update the carry bit if necessary.
    list[str]
        The partially translated parameters of the instruction.
    '''
    translation = ''
    if len(args) > 2 and args[-2] in SHIFT_TRANSLATIONS:
        # for some opcodes, we need to update the carry flag
        if re.match(
            '(^movs.*)|(^mvns.*)|(^ands.*)|(^orrs.*)|(^orns.*)|(^eors.*)|(^bics.*)|(^teq.*)|(^tst.*)',
                opcode):
            if 'ror' in args[-2] or 'lsr' in args[-2] or 'asr' in args[-2]:
                translation = f'_asm_analysis_.c = {args[-3]} & (1 << {args[-1]} - 1);\n'
            elif 'lsl' in args[-2]:
                translation = f'_asm_analysis_.c = {args[-3]} & ((uint32_t) 0x80000000 >> {args[-1]} - 1);\n'

        return translation, [
            *args[:-3], SHIFT_TRANSLATIONS[args[-2]].format(args[-3], args[-1])]
    else:
        return translation, args


def _translate_status(opcode: str, args: List[str]) -> str:
    '''Translates the use of the suffix bit s in ARM assembly.

    Sometimes the suffix 's' is append in ARM assembly which induces an
    update of the status bits (N, V, C, Z).

    Parameters
    ----------
    opcode : str
        Opcode in ARM assembly.
    args : list[str]
        Arguments passed to the opcode.

    Returns
    -------
    str
        C translation that performs the update of the status bits.
    '''
    result = ''

    result += f'_asm_analysis_.z = {args[0]} == 0;\n'
    result += f'_asm_analysis_.n = {args[0]} & 0x80000000;\n'

    # update the carry flag depending on the operation
    if re.match('^ad.*', opcode):
        result += f'_asm_analysis_.c = ((uint32_t) {args[0]}) < ((uint32_t) {args[1]});\n'
        result += f'_asm_analysis_.v = ({args[1]}&0x80000000) == ({args[2]}&0x80000000) '
        result += f'&& ({args[0]}&0x80000000) != ({args[1]}&0x80000000);\n'
    elif re.match('(^sub.*)|(^rsb.*)|(^sbc.*)', opcode):
        result += f'_asm_analysis_.c = ((uint32_t) {args[1]}) >= ((uint32_t) {args[2]});\n'
        result += f'_asm_analysis_.v = ({args[1]}&0x80000000) != ({args[2]}&0x80000000) '
        result += f'&& ({args[0]}&0x80000000) != ({args[1]}&0x80000000);\n'
    elif re.match('(^ror.*)|(^lsr.*)|(^asr.*)', opcode):
        result += f'_asm_analysis_.c = {args[1]} & (1 << {args[2]} - 1);\n'
    elif re.match('^lsl.*', opcode):
        result += f'_asm_analysis_.c = {args[1]} & ((uint32_t) 0x80000000 >> {args[2]} - 1);\n'

    return result


TRANSLATIONS = {
    'ctr': '_asm_analysis_.counters[{0}] ++;\n',
    'memctr0': '_asm_analysis_.load_counter ++;\n',
    'memctr1': '_asm_analysis_.store_counter ++;\n',
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
    'cmp': '_asm_analysis_.tmp = {0} - {1};\n_asm_analysis_.z = _asm_analysis_.tmp == 0;\n_asm_analysis_.n = _asm_analysis_.tmp & 0x80000000;\n_asm_analysis_.c = ((uint32_t) {0}) >= ((uint32_t) {1});\n_asm_analysis_.v = ({0}&0x80000000) != ({1}&0x80000000) && (_asm_analysis_.tmp&0x80000000) != ({0}&0x80000000);\n',
    'cmn': '_asm_analysis_.tmp = {0} + {1};\n_asm_analysis_.z = _asm_analysis_.tmp == 0;\n_asm_analysis_.n = _asm_analysis_.tmp & 0x80000000;\n_asm_analysis_.c = ((uint32_t) _asm_analysis_.tmp) < ((uint32_t) {0});\n_asm_analysis_.v = ({0}&0x80000000) == ({1}&0x80000000) && (_asm_analysis_.tmp&0x80000000) != ({0}&0x80000000);\n',
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
    'tst': '_asm_analysis_.tmp = {0} & {1};\n_asm_analysis_.z = _asm_analysis_.tmp == 0;\n_asm_analysis_.n = _asm_analysis_.tmp & 0x80000000;\n',
    'teq': '_asm_analysis_.tmp = {1} ^ {2};\n_asm_analysis_.z = _asm_analysis_.tmp == 0;\n_asm_analysis_.n = _asm_analysis_.tmp & 0x80000000;\n',
    'uxtb': '{0} = 0xff & (uint8_t){1};\n',
    'uxth': '{0} = 0xffff & (uint16_t){1};\n',
    'uxtab': '{0} = (0xff & (uint8_t){2}) + {1};\n',
    'uxtah': '{0} = (0xffff & (uint16_t){2}) + {1};\n',
    'sxtb': '{0} = (0xff & {1}) << 24 >> 24;\n',
    'sxth': '{0} = (0xffff & {1}) << 16 >> 16;\n',
    'sxtab': '{0} = ((0xff & {2}) << 24 >> 24) + {1};\n',
    'sxtah': '{0} = ((0xffff & {2}) << 16 >> 16) + {1};\n',
    'ubfx': '{0} = ({1} >> {2}) & ((1 << {3}) - 1);\n',
    'clz': 'clz(&{0}, &{1});\n'}

COND_TRANSLATIONS = {
    'eq': 'if (_asm_analysis_.z){\n',
    'ne': 'if (!_asm_analysis_.z){\n',
    'ge': 'if (_asm_analysis_.n == _asm_analysis_.v){\n',
    'gt': 'if (!_asm_analysis_.z && _asm_analysis_.n == _asm_analysis_.v){\n',
    'le': 'if (_asm_analysis_.z || _asm_analysis_.n != _asm_analysis_.v){\n',
    'lt': 'if (_asm_analysis_.n != _asm_analysis_.v){\n',
    'ls': 'if (!_asm_analysis_.c || _asm_analysis_.z){\n',
    'cs': 'if (_asm_analysis_.c){\n',
    'cc': 'if (!_asm_analysis_.c){\n',
    'hi': 'if (_asm_analysis_.c && !_asm_analysis_.z){\n',
    'mi': 'if (_asm_analysis_.n){\n',
    'pl': 'if (!_asm_analysis_.n){\n',
    'al': 'if (true){\n',
    'nv': 'if (false){\n',
    'vs': 'if (_asm_analysis_.v){\n',
    'vc': 'if (!_asm_analysis_.v){\n'
}

SHIFT_TRANSLATIONS = {
    'lsr': '((uint32_t){0} >> {1})',
    'asr': '({0} >> {1})',
    'lsl': '((uint32_t){0} << {1})',
    'ror': '(((uint32_t){0} >> {1}) | ((uint32_t){0} << (32-{1})))'
}
