
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

    return translations[instruction].format(*args)


translations = {
    # ldr 1 mit [sp]
    'add': '{0} = {1} + {2};\n',
    'sub': '{0} = {1} - {2};\n',
    'str1': '{1} += {2};\n*{1} = {0};\n',
    'str2': '*({1}+({2})) = {0};\n',
    'ldr1': '{0} = *{1};\n{1} += {2};\n',
    'ldr2': '{0} = *({1}+({2}));\n',
    'push1': 'sp -= 4;\n*sp = {0};\n',
    'push2': 'sp -= 8;\n*sp = {0};\n*(sp+4) = {1};\n',
    'pop1': '{0} = *sp;\nsp += 4;\n',
    'pop2': '{0} = *sp;\n{1} = *(sp + 4);\nsp += 8;\n',
    'mov': '{0} = {1};\n',
    'nop': '',
    'bx': 'return r0;\n',
    'bl': 'r0 = {0}(r0);\n',
    'ctr': 'counter += {0};\n'
}
