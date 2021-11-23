from asm_analyser.blocks.code_block import CodeBlock

function_dict = {
    '__aeabi_fadd':     'void fadd()\n' \
                        '{\n' \
                        'r0.f = r0.f + r1.f;\n' \
                        '}\n',
    '__aeabi_fsub':     'void fsub()\n' \
                        '{\n' \
                        'r0.f = r0.f - r1.f;\n' \
                        '}\n',
    '__aeabi_fmul':     'void fmul()\n' \
                        '{\n' \
                        'r0.f = r0.f * r1.f;\n' \
                        '}\n',
    '__aeabi_fdiv':     'void fdiv()\n' \
                        '{\n' \
                        'r0.f = r0.f / r1.f;\n' \
                        '}\n',
    '__aeabi_f2d':      'void f2d()\n' \
                        '{\n' \
                        'double double_val = (double) r0.f;\n' \
                        'int64_t int64_t_val = *(int64_t *)&double_val;\n' \
                        'r1.i = (int32_t) (int64_t_val >> 32);\n' \
                        'r0.i = (int32_t) int64_t_val;\n' \
                        '}\n',
    '__aeabi_d2f':      'void d2f()\n' \
                        '{\n' \
                        'int64_t int64_t_val = ((int64_t) r1.i) << 32 | ((int64_t) r0.i);\n' \
                        'double double_val = *(double *)&int64_t_val;\n' \
                        'r0.f = (float) double_val;\n' \
                        '}\n',
    '__aeabi_dadd':     'void dadd()\n' \
                        '{\n' \
                        'int64_t op1 = ((int64_t) r1.i) << 32 | ((int64_t) r0.i);\n' \
                        'int64_t op2 = ((int64_t) r3.i) << 32 | ((int64_t) r2.i);\n' \
                        'double result = *(double *)&op1 + *(double *)&op2;\n' \
                        'int64_t result_int64 = *(int64_t *)&result;\n' \
                        'r1.i = (int32_t) (result_int64 >> 32);\n' \
                        'r0.i = (int32_t) result_int64;\n' \
                        '}\n',
    '__aeabi_dsub':     'void dsub()\n' \
                        '{\n' \
                        'int64_t op1 = ((int64_t) r1.i) << 32 | ((int64_t) r0.i);\n' \
                        'int64_t op2 = ((int64_t) r3.i) << 32 | ((int64_t) r2.i);\n' \
                        'double result = *(double *)&op1 - *(double *)&op2;\n' \
                        'int64_t result_int64 = *(int64_t *)&result;\n' \
                        'r1.i = (int32_t) (result_int64 >> 32);\n' \
                        'r0.i = (int32_t) result_int64;\n' \
                        '}\n',
    '__aeabi_dmul':     'void dmul()\n' \
                        '{\n' \
                        'int64_t op1 = ((int64_t) r1.i) << 32 | ((int64_t) r0.i);\n' \
                        'int64_t op2 = ((int64_t) r3.i) << 32 | ((int64_t) r2.i);\n' \
                        'double result = *(double *)&op1 * *(double *)&op2;\n' \
                        'int64_t result_int64 = *(int64_t *)&result;\n' \
                        'r1.i = (int32_t) (result_int64 >> 32);\n' \
                        'r0.i = (int32_t) result_int64;\n' \
                        '}\n',
    '__aeabi_ddiv':     'void ddiv()\n' \
                        '{\n' \
                        'int64_t op1 = ((int64_t) r1.i) << 32 | ((int64_t) r0.i);\n' \
                        'int64_t op2 = ((int64_t) r3.i) << 32 | ((int64_t) r2.i);\n' \
                        'double result = *(double *)&op1 / *(double *)&op2;\n' \
                        'int64_t result_int64 = *(int64_t *)&result;\n' \
                        'r1.i = (int32_t) (result_int64 >> 32);\n' \
                        'r0.i = (int32_t) result_int64;\n' \
                        '}\n',
    '__aeabi_dcmplt':   'void dcmplt()\n' \
                        '{\n' \
                        'int64_t op1 = ((int64_t) r1.i) << 32 | ((int64_t) r0.i);\n' \
                        'int64_t op2 = ((int64_t) r3.i) << 32 | ((int64_t) r2.i);\n' \
                        'r0.i = *(double *)&op1 < *(double *)&op2;\n' \
                        '}\n',
    '__aeabi_dcmpeq':   'void dcmpeq()\n' \
                        '{\n' \
                        'int64_t op1 = ((int64_t) r1.i) << 32 | ((int64_t) r0.i);\n' \
                        'int64_t op2 = ((int64_t) r3.i) << 32 | ((int64_t) r2.i);\n' \
                        'r0.i = *(double *)&op1 == *(double *)&op2;\n' \
                        '}\n',
    '__aeabi_dcmple':   'void dcmple()\n' \
                        '{\n' \
                        'int64_t op1 = ((int64_t) r1.i) << 32 | ((int64_t) r0.i);\n' \
                        'int64_t op2 = ((int64_t) r3.i) << 32 | ((int64_t) r2.i);\n' \
                        'r0.i = *(double *)&op1 <= *(double *)&op2;\n' \
                        '}\n',
    '__aeabi_dcmpge':   'void dcmpge()\n' \
                        '{\n' \
                        'int64_t op1 = ((int64_t) r1.i) << 32 | ((int64_t) r0.i);\n' \
                        'int64_t op2 = ((int64_t) r3.i) << 32 | ((int64_t) r2.i);\n' \
                        'r0.i = *(double *)&op1 >= *(double *)&op2;\n' \
                        '}\n',
    '__aeabi_dcmpgt':   'void dcmpgt()\n' \
                        '{\n' \
                        'int64_t op1 = ((int64_t) r1.i) << 32 | ((int64_t) r0.i);\n' \
                        'int64_t op2 = ((int64_t) r3.i) << 32 | ((int64_t) r2.i);\n' \
                        'r0.i = *(double *)&op1 > *(double *)&op2;\n' \
                        '}\n',
    '__aeabi_d2iz':     'void d2iz()\n' \
                        '{\n' \
                        'int64_t op_int = ((int64_t) r1.i) << 32 | ((int64_t) r0.i);\n' \
                        'r0.i = (int32_t) *(double *)&op_int;\n' \
                        '}\n',
    '__aeabi_idivmod':  'void idivmod()\n' \
                        '{\n' \
                        'int32_t quot = r0.i / r1.i;\n' \
                        'int32_t rem = r0.i % r1.i;\n' \
                        'r0.i = quot;\n' \
                        'r1.i = rem;\n' \
                        '}\n',
    '__aeabi_i2d':      'void i2d()\n' \
                        '{\n' \
                        'double result = (double) r0.i;\n' \
                        'int64_t result_int64 = *(int64_t *)&result;\n' \
                        'r1.i = (int32_t) (result_int64 >> 32);\n' \
                        'r0.i = (int32_t) result_int64;\n' \
                        '}\n',
    'malloc':           'void malloc_help()\n' \
                        '{\n' \
                        'uint8_t* ptr = (uint8_t*) malloc(r0.i);\n' \
                        'r0.i = (int32_t) (ptr - malloc_0);\n' \
                        '}\n',
    'free':             'void free_help()\n' \
                        '{\n' \
                        'free(malloc_0+r0.i);\n' \
                        '}\n',
    'calloc':           'void calloc_help()\n' \
                        '{\n' \
                        'uint8_t* ptr = (uint8_t*) calloc(r0.i, r1.i);\n' \
                        'r0.i = (int32_t) (ptr - malloc_0);\n' \
                        '}\n',
    'memcpy':           'void memcpy_help()\n' \
                        '{\n' \
                        'memcpy(malloc_0+r0.i, malloc_0+r1.i, r2.i);\n' \
                        '}\n',
    'memset':           'void memset_help()\n' \
                        '{\n' \
                        'memset(malloc_0+r0.i, r1.i, r2.i);\n' \
                        '}\n',
    'strlen':           'void strlen_help()\n' \
                        '{\n' \
                        'r0.i = (int32_t) strlen(malloc_0+r0.i);\n' \
                        '}\n',
    'rand':             'void rand_help()\n' \
                        '{\n' \
                        'r0.i = rand();\n' \
                        '}\n',
    'srand':            'void srand_help()\n' \
                        '{\n' \
                        'srand(r0.i);\n' \
                        '}\n',
    'time':             'void time_help()\n' \
                        '{\n' \
                        'r0.i = time(NULL);' \
                        '}\n',
    'puts':             '',
    'putchar':          '',
    'nl':               '',
    'printf':           '',
    '__printf_chk':     '',
    '__assert_fail':    'void assert_help()\n' \
                        '{\n' \
                        '__assert_fail(malloc_0+r0.i, malloc_0+r1.i, r2.i, malloc_0+r3.i);\n' \
                        '}\n',
    '__isoc99_scanf':   'void scanf_help()\n' \
                        '{\n' \
                        'scanf(malloc_0+r0.i, malloc_0+r1.i);\n' \
                        '}\n',
    'umull':            'void umull(int32_t *dest_lo, int32_t *dest_hi, int32_t *op1, int32_t *op2)\n' \
                        '{\n' \
                        'uint64_t res = (uint64_t) ((uint32_t) *op1) * ((uint32_t) *op2);\n' \
                        '*dest_lo = (uint32_t) res;\n' \
                        '*dest_hi = (uint32_t) (res >> 32);\n' \
                        '}\n',
    'smull':            'void smull(int32_t *dest_lo, int32_t *dest_hi, int32_t *op1, int32_t *op2)\n' \
                        '{\n' \
                        'uint64_t res = (uint64_t) (*op1) * (*op2);\n' \
                        '*dest_lo = (uint32_t) res;\n' \
                        '*dest_hi = (uint32_t) (res >> 32);\n' \
                        '}\n'
}

call_dict = {
    '__aeabi_fadd':     'fadd();\n',
    '__aeabi_fsub':     'fsub();\n',
    '__aeabi_fmul':     'fmul();\n',
    '__aeabi_fdiv':     'fdiv();\n',
    '__aeabi_f2d':      'f2d();\n',
    '__aeabi_d2f':      'd2f();\n',
    '__aeabi_dadd':     'dadd();\n',
    '__aeabi_dsub':     'dsub();\n',
    '__aeabi_dmul':     'dmul();\n',
    '__aeabi_ddiv':     'ddiv();\n',
    '__aeabi_dcmplt':   'dcmplt();\n',
    '__aeabi_dcmpeq':   'dcmpeq();\n',
    '__aeabi_dcmple':   'dcmple();\n',
    '__aeabi_dcmpge':   'dcmpge();\n',
    '__aeabi_dcmpgt':   'dcmpgt();\n',
    '__aeabi_d2iz':     'd2iz();\n',
    '__aeabi_idivmod':  'idivmod();\n',
    '__aeabi_i2d':      'i2d();\n',
    'malloc':           'malloc_help();\n',
    'free':             'free_help();\n',
    'calloc':           'calloc_help();\n',
    'memcpy':           'memcpy_help();\n',
    'memset':           'memset_help();\n',
    'strlen':           'strlen_help();\n',
    'rand':             'rand_help();\n',
    'srand':            'srand_help();\n',
    'time':             'time_help();\n',
    'puts':             'printf("%s\\n", malloc_0+r0.i);\n',
    'putchar':          'printf("%c", (char)r0.i);\n',
    'nl':               'printf("\\n");\n',
    'printf':           'printf(malloc_0+r0.i, r1.i);\n',
    '__printf_chk':     'printf(malloc_0+r1.i, r2.i);\n',
    '__assert_fail':    'assert_help();\n',
    '__isoc99_scanf':   'scanf_help();\n',
    'umull':            '',
    'smull':            ''
}

def get_auxiliary_functions(blocks: list[CodeBlock]) -> str:
    '''TODO
    '''
    result = ''
    function_calls = set()

    # get the necessary auxiliary functions for the translation
    for block in blocks:
        for instr in block.instructions:
            if ((instr[0] == 'bl' or instr[0] == 'b') and
                    instr[1][0] in call_dict):
                function_calls.add(instr[1][0])

            if instr[0] in call_dict:
                function_calls.add(instr[0])
    
    for call in function_calls:
        result += function_dict[call]

    return result