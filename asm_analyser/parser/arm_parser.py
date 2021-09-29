import sys
sys.path.append("..")
import re
from function import Function
from parser.parser import Parser

class ArmParser(Parser):
    def __init__(self, file_name: str) -> None:
        super().__init__(file_name)
        self.filter_re = ('(^\t@ .*)|(.*\.(arch|eabi_attribute|file|text|'
                          'global|align|syntax|arm|fpu|size|ident|section).*)')
        self.file_name = file_name
        self.line_columns = []

    def create_functions(self) -> list[Function]:
        functions = []
        self._read_file()

        for line in self.line_columns:
            
            # check if line contains function definition
            if line[0] == '.type' and line[2] == '%function':
                functions.append(Function())
                continue

            if len(line) == 1 and line[0][-1] == ':':
                functions[-1].name = line[0][:-1]
                continue

            # check if line is an instruction
            if len(line) > 1:
                functions[-1].instructions.append((line[0], line[1:]))
            elif len(line) == 1:
                functions[-1].instructions.append((line[0], []))

        return functions

    def _read_file(self) -> None:
        f = open(f'../examples/asm/{self.file_name}.s', 'r')

        lines = [ re.sub('[,#\\[\\]{}]', '', l)  for l in f.readlines()]

        for line in lines:

            #remove unneccesary lines
            if bool(re.match(self.filter_re, line)):
                continue

            columns = line.split()

            self.line_columns.append(columns)