'''
Provides a datastructure representing a basic block.
'''
class BasicBlock:
    '''
    Represents a basic block with all its instructions.
    '''

    def __init__(self) -> None:
        self.instructions = []
        self.parent_block = ''
