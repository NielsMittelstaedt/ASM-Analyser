
'''
Provides a datastructure representing a code block or section.
'''

Instruction = tuple[int, str, list[str]]


class CodeBlock:
    '''
    Represents a code section that corresponds to a function or label.
    Contains the list of instructions belonging to that block.
    '''

    def __init__(self) -> None:
        self.name = ''
        self.parent_name = ''
        self.instructions = []
        self.is_function = False
        self.is_code = True
        self.is_last = False
