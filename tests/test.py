import os

def run_test(file_name:str) -> None:
    '''TODO'''
    os.system(f'make output file=../examples/c_out/{file_name}')
    os.system(f'make output file=../examples/c_in/{file_name}')

run_test('int_incr')