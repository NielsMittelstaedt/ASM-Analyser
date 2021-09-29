
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
    args = list(args)
    if instruction == 'str':
        if len(args) > 2 and args[2][-1] == '!':
            instruction = 'str1'
            args[2] = args[2][:-1]
        else:
            instruction = 'str2'

    return translations[instruction].format(*args)


translations = {
    'add': '{0} = {1} + {2};\n',
    'sub': '{0} = {1} - {2};\n',
    'str1': '{1} += {2};\n*{1} = {0};\n',
    'str2': '*({1}+({2})) = {0};\n',
    'ldr': '',
    'mov': '{0} = {1};\n',
    'nop': '',
    'bx': 'return r0;\n',
    'bl': 'r0 = {0}(r0);'
}
