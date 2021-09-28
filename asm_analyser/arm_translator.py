
def translate(instruction: str, operand1: str,
              operand2: str = '', operand3: str = ''):
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
    operand1.replace('#', '')
    operand2.replace('#', '')
    operand3.replace('#', '')

    return translations[instruction].format(
        operand1=operand1, operand2=operand2, operand3=operand3)


translations = {
    "add": "{operand1} = {operand2} + {operand3};",
    "sub": "{operand1} = {operand2} - {operand3};",
    "ldr": "",
    "mov": "{operand1} = {operand2}{operand3};"
}
