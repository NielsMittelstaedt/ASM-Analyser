from asm_analyser.blocks.code_block import CodeBlock
import re

function_dict = {
    'ldr4000':          'void ldr4000(int32_t *target, int32_t *address, int32_t offset)\n' \
                        '{\n' \
                        '*target = *((uint32_t*)(malloc_0+*address+offset));\n' \
                        '}\n',
    'ldr4010':          'void ldr4010(int32_t *target, int32_t *address, int32_t offset)\n' \
                        '{\n' \
                        '*target = *((uint32_t*)(malloc_0+*address));\n' \
                        '*address += offset;\n' \
                        '}\n',
    'ldr4100':          'void ldr4100(int32_t *target, int32_t *address, int32_t offset)\n' \
                        '{\n' \
                        '*target = *((uint32_t*)(malloc_0+*address+offset));\n' \
                        '*address += offset;\n' \
                        '}\n',
    'ldr2000':          'void ldr2000(int32_t *target, int32_t *address, int32_t offset)\n' \
                        '{\n' \
                        '*target = *((uint16_t*)(malloc_0)+*address+offset) & 0xffff;\n' \
                        '}\n',
    'ldr2001':          'void ldr2001(int32_t *target, int32_t *address, int32_t offset)\n' \
                        '{\n' \
                        '*target = (*((uint16_t*)(malloc_0)+*address+offset) & 0xffff) << 16 >> 16;\n' \
                        '}\n',
    'ldr2010':          'void ldr2010(int32_t *target, int32_t *address, int32_t offset)\n' \
                        '{\n' \
                        '*target = *((uint16_t*)(malloc_0)+*address) & 0xffff;\n' \
                        '*address += offset;\n' \
                        '}\n',
    'ldr2011':          'void ldr2011(int32_t *target, int32_t *address, int32_t offset)\n' \
                        '{\n' \
                        '*target = (*((uint16_t*)(malloc_0)+*address) & 0xffff) << 16 >> 16;\n' \
                        '*address += offset;\n' \
                        '}\n',
    'ldr2100':          'void ldr2100(int32_t *target, int32_t *address, int32_t offset)\n' \
                        '{\n' \
                        '*target = *((uint16_t*)(malloc_0)+*address+offset) & 0xffff;\n' \
                        '*address += offset;\n' \
                        '}\n',
    'ldr2101':          'void ldr2101(int32_t *target, int32_t *address, int32_t offset)\n' \
                        '{\n' \
                        '*target = (*((uint16_t*)(malloc_0)+*address+offset) & 0xffff) << 16 >> 16;\n' \
                        '*address += offset;\n' \
                        '}\n',
    'ldr1000':          'void ldr1000(int32_t *target, int32_t *address, int32_t offset)\n' \
                        '{\n' \
                        '*target = *((uint8_t*)(malloc_0)+*address+offset) & 0xff;\n' \
                        '}\n',
    'ldr1001':          'void ldr1001(int32_t *target, int32_t *address, int32_t offset)\n' \
                        '{\n' \
                        '*target = (*((uint8_t*)(malloc_0)+*address+offset) & 0xff) << 24 >> 24;\n' \
                        '}\n',
    'ldr1010':          'void ldr1010(int32_t *target, int32_t *address, int32_t offset)\n' \
                        '{\n' \
                        '*target = *((uint8_t*)(malloc_0)+*address) & 0xff;\n' \
                        '*address += offset;\n' \
                        '}\n',
    'ldr1011':          'void ldr1011(int32_t *target, int32_t *address, int32_t offset)\n' \
                        '{\n' \
                        '*target = (*((uint8_t*)(malloc_0)+*address) & 0xff) << 24 >> 24;\n' \
                        '*address += offset;\n' \
                        '}\n',
    'ldr1100':          'void ldr1100(int32_t *target, int32_t *address, int32_t offset)\n' \
                        '{\n' \
                        '*target = *((uint8_t*)(malloc_0)+*address+offset) & 0xff;\n' \
                        '*address += offset;\n' \
                        '}\n',
    'ldr1101':          'void ldr1101(int32_t *target, int32_t *address, int32_t offset)\n' \
                        '{\n' \
                        '*target = (*((uint8_t*)(malloc_0)+*address+offset) & 0xff) << 24 >> 24;\n' \
                        '*address += offset;\n' \
                        '}\n',
    'str4000':          'void str4000(int32_t *target, int32_t *address, int32_t offset)\n' \
                        '{\n' \
                        '*((uint32_t*)(malloc_0+*address+offset)) = *target;\n' \
                        '}\n',
    'str4010':          'void str4010(int32_t *target, int32_t *address, int32_t offset)\n' \
                        '{\n' \
                        '*((uint32_t*)(malloc_0+*address)) = *target;\n' \
                        '*address += offset;\n' \
                        '}\n',
    'str4100':          'void str4100(int32_t *target, int32_t *address, int32_t offset)\n' \
                        '{\n' \
                        '*((uint32_t*)(malloc_0+*address+offset)) = *target;\n' \
                        '*address += offset;\n' \
                        '}\n',
    'str2000':          'void str2000(int32_t *target, int32_t *address, int32_t offset)\n' \
                        '{\n' \
                        '*((uint16_t*)(malloc_0+*address+offset)) = *target & 0xffff;\n' \
                        '}\n',
    'str2010':          'void str2010(int32_t *target, int32_t *address, int32_t offset)\n' \
                        '{\n' \
                        '*((uint16_t*)(malloc_0+*address)) = *target & 0xffff;\n' \
                        '*address += offset;\n' \
                        '}\n',
    'str2100':          'void str2100(int32_t *target, int32_t *address, int32_t offset)\n' \
                        '{\n' \
                        '*((uint16_t*)(malloc_0+*address+offset)) = *target & 0xffff;\n' \
                        '*address += offset;\n' \
                        '}\n',
    'str1000':          'void str1000(int32_t *target, int32_t *address, int32_t offset)\n' \
                        '{\n' \
                        '*(malloc_0+*address+offset) = *target & 0xff;\n' \
                        '}\n',
    'str1010':          'void str1010(int32_t *target, int32_t *address, int32_t offset)\n' \
                        '{\n' \
                        '*(malloc_0+*address) = *target & 0xff;\n' \
                        '*address += offset;\n' \
                        '}\n',
    'str1100':          'void str1100(int32_t *target, int32_t *address, int32_t offset)\n' \
                        '{\n' \
                        '*(malloc_0+*address+offset) = *target & 0xff;\n' \
                        '*address += offset;\n' \
                        '}\n',
    'ldr8000':          'void ldr8000(int32_t *target1, int32_t *target2, int32_t *address, int32_t offset)\n' \
                        '{\n' \
                        '*target1 = *((uint32_t*)(malloc_0+*address+offset));\n' \
                        '*target2 = *((uint32_t*)(malloc_0+*address+offset+4));\n' \
                        '}\n',
    'ldr8010':          'void ldr8010(int32_t *target1, int32_t *target2, int32_t *address, int32_t offset)\n' \
                        '{\n' \
                        '*target1 = *((uint32_t*)(malloc_0+*address));\n' \
                        '*target2 = *((uint32_t*)(malloc_0+*address+4));\n' \
                        '*address += offset;\n' \
                        '}\n',
    'ldr8100':          'void ldr8100(int32_t *target1, int32_t *target2, int32_t *address, int32_t offset)\n' \
                        '{\n' \
                        '*target1 = *((uint32_t*)(malloc_0+*address+offset));\n' \
                        '*target2 = *((uint32_t*)(malloc_0+*address+offset+4));\n' \
                        '*address += offset;\n' \
                        '}\n',
    'str8000':          'void str8000(int32_t *target1, int32_t *target2, int32_t *address, int32_t offset)\n' \
                        '{\n' \
                        '*((uint32_t*)(malloc_0+*address+offset)) = *target1;\n' \
                        '*((uint32_t*)(malloc_0+*address+offset+4)) = *target2;\n' \
                        '}\n',
    'str8010':          'void str8010(int32_t *target1, int32_t *target2, int32_t *address, int32_t offset)\n' \
                        '{\n' \
                        '*((uint32_t*)(malloc_0+*address)) = *target1;\n' \
                        '*((uint32_t*)(malloc_0+*address+4)) = *target2;\n' \
                        '*address += offset;\n' \
                        '}\n',
    'str8100':          'void str8100(int32_t *target1, int32_t *target2, int32_t *address, int32_t offset)\n' \
                        '{\n' \
                        '*((uint32_t*)(malloc_0+*address+offset)) = *target1;\n' \
                        '*((uint32_t*)(malloc_0+*address+offset+4)) = *target2;\n' \
                        '*address += offset;\n' \
                        '}\n',
    'push':             'void push(int num, ...)\n' \
                        '{\n' \
                        'va_list args;\n' \
                        'va_start(args, num);\n' \
                        'for (int i=0; i < num; i++)\n' \
                        '{\n' \
                        'int32_t *cur_arg = va_arg(args, int32_t *);\n' \
                        'sp.i -= 4;\n' \
                        '*((uint32_t*) (malloc_0 + sp.i)) = *cur_arg;\n' \
                        '}\n' \
                        'va_end(args);\n' \
                        '}\n',
    'pop':              'void pop(int num, ...)\n' \
                        '{\n' \
                        'va_list args;\n' \
                        'va_start(args, num);\n' \
                        'for (int i=0; i < num; i++)\n' \
                        '{\n' \
                        'int32_t *cur_arg = va_arg(args, int32_t *);\n' \
                        '*cur_arg = *((uint32_t*) (malloc_0 + sp.i));\n' \
                        'sp.i += 4;\n' \
                        '}\n' \
                        'va_end(args);\n' \
                        '}\n',
    'ldm0':             'void ldm0(int32_t *address, int num, ...)\n' \
                        '{\n' \
                        'va_list args;\n' \
                        'va_start(args, num);\n' \
                        'int32_t tmp = *address;\n' \
                        'for (int i=0; i < num; i++)\n' \
                        '{\n' \
                        'int32_t *cur_arg = va_arg(args, int32_t *);\n' \
                        '*cur_arg = *((uint32_t*) (malloc_0 + tmp));\n' \
                        'tmp += 4;\n' \
                        '}\n' \
                        'va_end(args);\n' \
                        '}\n',
    'ldm1':             'void ldm1(int32_t *address, int num, ...)\n' \
                        '{\n' \
                        'va_list args;\n' \
                        'va_start(args, num);\n' \
                        'for (int i=0; i < num; i++)\n' \
                        '{\n' \
                        'int32_t *cur_arg = va_arg(args, int32_t *);\n' \
                        '*cur_arg = *((uint32_t*) (malloc_0 + *address));\n' \
                        '*address += 4;\n' \
                        '}\n' \
                        'va_end(args);\n' \
                        '}\n',
    'ldmib0':           'void ldmib0(int32_t *address, int num, ...)\n' \
                        '{\n' \
                        'va_list args;\n' \
                        'va_start(args, num);\n' \
                        'int32_t tmp = *address;\n' \
                        'for (int i=0; i < num; i++)\n' \
                        '{\n' \
                        'int32_t *cur_arg = va_arg(args, int32_t *);\n' \
                        'tmp += 4;\n' \
                        '*cur_arg = *((uint32_t*) (malloc_0 + tmp));\n' \
                        '}\n' \
                        'va_end(args);\n' \
                        '}\n',
    'ldmib1':           'void ldmib1(int32_t *address, int num, ...)\n' \
                        '{\n' \
                        'va_list args;\n' \
                        'va_start(args, num);\n' \
                        'for (int i=0; i < num; i++)\n' \
                        '{\n' \
                        'int32_t *cur_arg = va_arg(args, int32_t *);\n' \
                        '*address += 4;\n' \
                        '*cur_arg = *((uint32_t*) (malloc_0 + *address));\n' \
                        '}\n' \
                        'va_end(args);\n' \
                        '}\n',
    'ldmda0':           'void ldmda0(int32_t *address, int num, ...)\n' \
                        '{\n' \
                        'va_list args;\n' \
                        'va_start(args, num);\n' \
                        'int32_t tmp = *address;\n' \
                        'for (int i=0; i < num; i++)\n' \
                        '{\n' \
                        'int32_t *cur_arg = va_arg(args, int32_t *);\n' \
                        '*cur_arg = *((uint32_t*) (malloc_0 + tmp));\n' \
                        'tmp -= 4;\n' \
                        '}\n' \
                        'va_end(args);\n' \
                        '}\n',
    'ldmda1':           'void ldmda1(int32_t *address, int num, ...)\n' \
                        '{\n' \
                        'va_list args;\n' \
                        'va_start(args, num);\n' \
                        'for (int i=0; i < num; i++)\n' \
                        '{\n' \
                        'int32_t *cur_arg = va_arg(args, int32_t *);\n' \
                        '*cur_arg = *((uint32_t*) (malloc_0 + *address));\n' \
                        '*address -= 4;\n' \
                        '}\n' \
                        'va_end(args);\n' \
                        '}\n',
    'ldmdb0':           'void ldmdb0(int32_t *address, int num, ...)\n' \
                        '{\n' \
                        'va_list args;\n' \
                        'va_start(args, num);\n' \
                        'int32_t tmp = *address;\n' \
                        'for (int i=0; i < num; i++)\n' \
                        '{\n' \
                        'int32_t *cur_arg = va_arg(args, int32_t *);\n' \
                        'tmp -= 4;\n' \
                        '*cur_arg = *((uint32_t*) (malloc_0 + tmp));\n' \
                        '}\n' \
                        'va_end(args);\n' \
                        '}\n',
    'ldmdb1':           'void ldmdb1(int32_t *address, int num, ...)\n' \
                        '{\n' \
                        'va_list args;\n' \
                        'va_start(args, num);\n' \
                        'for (int i=0; i < num; i++)\n' \
                        '{\n' \
                        'int32_t *cur_arg = va_arg(args, int32_t *);\n' \
                        '*address -= 4;\n' \
                        '*cur_arg = *((uint32_t*) (malloc_0 + *address));\n' \
                        '}\n' \
                        'va_end(args);\n' \
                        '}\n',
    'stm0':             'void stm0(int32_t *address, int num, ...)\n' \
                        '{\n' \
                        'va_list args;\n' \
                        'va_start(args, num);\n' \
                        'int32_t tmp = *address;\n' \
                        'for (int i=0; i < num; i++)\n' \
                        '{\n' \
                        'int32_t *cur_arg = va_arg(args, int32_t *);\n' \
                        '*((uint32_t*) (malloc_0 + tmp)) = *cur_arg;\n' \
                        'tmp += 4;\n' \
                        '}\n' \
                        'va_end(args);\n' \
                        '}\n',
    'stm1':             'void stm1(int32_t *address, int num, ...)\n' \
                        '{\n' \
                        'va_list args;\n' \
                        'va_start(args, num);\n' \
                        'for (int i=0; i < num; i++)\n' \
                        '{\n' \
                        'int32_t *cur_arg = va_arg(args, int32_t *);\n' \
                        '*((uint32_t*) (malloc_0 + *address)) = *cur_arg;\n' \
                        '*address += 4;\n' \
                        '}\n' \
                        'va_end(args);\n' \
                        '}\n',
    'stmib0':           'void stmib0(int32_t *address, int num, ...)\n' \
                        '{\n' \
                        'va_list args;\n' \
                        'va_start(args, num);\n' \
                        'int32_t tmp = *address;\n' \
                        'for (int i=0; i < num; i++)\n' \
                        '{\n' \
                        'int32_t *cur_arg = va_arg(args, int32_t *);\n' \
                        'tmp += 4;\n' \
                        '*((uint32_t*) (malloc_0 + tmp)) = *cur_arg;\n' \
                        '}\n' \
                        'va_end(args);\n' \
                        '}\n',
    'stmib1':           'void stmib1(int32_t *address, int num, ...)\n' \
                        '{\n' \
                        'va_list args;\n' \
                        'va_start(args, num);\n' \
                        'for (int i=0; i < num; i++)\n' \
                        '{\n' \
                        'int32_t *cur_arg = va_arg(args, int32_t *);\n' \
                        '*address += 4;\n' \
                        '*((uint32_t*) (malloc_0 + *address)) = *cur_arg;\n' \
                        '}\n' \
                        'va_end(args);\n' \
                        '}\n',
    'stmda0':           'void stmda0(int32_t *address, int num, ...)\n' \
                        '{\n' \
                        'va_list args;\n' \
                        'va_start(args, num);\n' \
                        'int32_t tmp = *address;\n' \
                        'for (int i=0; i < num; i++)\n' \
                        '{\n' \
                        'int32_t *cur_arg = va_arg(args, int32_t *);\n' \
                        '*((uint32_t*) (malloc_0 + tmp)) = *cur_arg;\n' \
                        'tmp -= 4;\n' \
                        '}\n' \
                        'va_end(args);\n' \
                        '}\n',
    'stmda1':           'void stmda1(int32_t *address, int num, ...)\n' \
                        '{\n' \
                        'va_list args;\n' \
                        'va_start(args, num);\n' \
                        'for (int i=0; i < num; i++)\n' \
                        '{\n' \
                        'int32_t *cur_arg = va_arg(args, int32_t *);\n' \
                        '*((uint32_t*) (malloc_0 + *address)) = *cur_arg;\n' \
                        '*address -= 4;\n' \
                        '}\n' \
                        'va_end(args);\n' \
                        '}\n',
    'stmdb0':           'void stmdb0(int32_t *address, int num, ...)\n' \
                        '{\n' \
                        'va_list args;\n' \
                        'va_start(args, num);\n' \
                        'int32_t tmp = *address;\n' \
                        'for (int i=0; i < num; i++)\n' \
                        '{\n' \
                        'int32_t *cur_arg = va_arg(args, int32_t *);\n' \
                        'tmp -= 4;\n' \
                        '*((uint32_t*) (malloc_0 + tmp)) = *cur_arg;\n' \
                        '}\n' \
                        'va_end(args);\n' \
                        '}\n',
    'stmdb1':           'void stmdb1(int32_t *address, int num, ...)\n' \
                        '{\n' \
                        'va_list args;\n' \
                        'va_start(args, num);\n' \
                        'for (int i=0; i < num; i++)\n' \
                        '{\n' \
                        'int32_t *cur_arg = va_arg(args, int32_t *);\n' \
                        '*address -= 4;\n' \
                        '*((uint32_t*) (malloc_0 + *address)) = *cur_arg;\n' \
                        '}\n' \
                        'va_end(args);\n' \
                        '}\n',
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
                        'uint64_t uint64_t_val = *(uint64_t *)&double_val;\n' \
                        'r1.i = (uint32_t) (uint64_t_val >> 32);\n' \
                        'r0.i = (uint32_t) uint64_t_val;\n' \
                        '}\n',
    '__aeabi_d2f':      'void d2f()\n' \
                        '{\n' \
                        'uint64_t uint64_t_val = ((uint64_t)(uint32_t) r1.i) << 32 | ((uint64_t)(uint32_t) r0.i);\n' \
                        'double double_val = *(double *)&uint64_t_val;\n' \
                        'r0.f = (float) double_val;\n' \
                        '}\n',
    '__aeabi_dadd':     'void dadd()\n' \
                        '{\n' \
                        'uint64_t op1 = ((uint64_t)(uint32_t) r1.i) << 32 | ((uint64_t)(uint32_t) r0.i);\n' \
                        'uint64_t op2 = ((uint64_t)(uint32_t) r3.i) << 32 | ((uint64_t)(uint32_t) r2.i);\n' \
                        'double result = *(double *)&op1 + *(double *)&op2;\n' \
                        'uint64_t result_uint64 = *(uint64_t *)&result;\n' \
                        'r1.i = (uint32_t) (result_uint64 >> 32);\n' \
                        'r0.i = (uint32_t) result_uint64;\n' \
                        '}\n',
    '__aeabi_dsub':     'void dsub()\n' \
                        '{\n' \
                        'uint64_t op1 = ((uint64_t)(uint32_t) r1.i) << 32 | ((uint64_t)(uint32_t) r0.i);\n' \
                        'uint64_t op2 = ((uint64_t)(uint32_t) r3.i) << 32 | ((uint64_t)(uint32_t) r2.i);\n' \
                        'double result = *(double *)&op1 - *(double *)&op2;\n' \
                        'uint64_t result_uint64 = *(uint64_t *)&result;\n' \
                        'r1.i = (uint32_t) (result_uint64 >> 32);\n' \
                        'r0.i = (uint32_t) result_uint64;\n' \
                        '}\n',
    '__aeabi_dmul':     'void dmul()\n' \
                        '{\n' \
                        'uint64_t op1 = ((uint64_t)(uint32_t) r1.i) << 32 | ((uint64_t)(uint32_t) r0.i);\n' \
                        'uint64_t op2 = ((uint64_t)(uint32_t) r3.i) << 32 | ((uint64_t)(uint32_t) r2.i);\n' \
                        'double result = *(double *)&op1 * *(double *)&op2;\n' \
                        'uint64_t result_uint64 = *(uint64_t *)&result;\n' \
                        'r1.i = (uint32_t) (result_uint64 >> 32);\n' \
                        'r0.i = (uint32_t) result_uint64;\n' \
                        '}\n',
    '__aeabi_ddiv':     'void ddiv()\n' \
                        '{\n' \
                        'uint64_t op1 = ((uint64_t)(uint32_t) r1.i) << 32 | ((uint64_t)(uint32_t) r0.i);\n' \
                        'uint64_t op2 = ((uint64_t)(uint32_t) r3.i) << 32 | ((uint64_t)(uint32_t) r2.i);\n' \
                        'double result = *(double *)&op1 / *(double *)&op2;\n' \
                        'uint64_t result_uint64 = *(uint64_t *)&result;\n' \
                        'r1.i = (uint32_t) (result_uint64 >> 32);\n' \
                        'r0.i = (uint32_t) result_uint64;\n' \
                        '}\n',
    '__aeabi_dcmplt':   'void dcmplt()\n' \
                        '{\n' \
                        'uint64_t op1 = ((uint64_t)(uint32_t) r1.i) << 32 | ((uint64_t)(uint32_t) r0.i);\n' \
                        'uint64_t op2 = ((uint64_t)(uint32_t) r3.i) << 32 | ((uint64_t)(uint32_t) r2.i);\n' \
                        'r0.i = *(double *)&op1 < *(double *)&op2;\n' \
                        '}\n',
    '__aeabi_dcmpeq':   'void dcmpeq()\n' \
                        '{\n' \
                        'uint64_t op1 = ((uint64_t)(uint32_t) r1.i) << 32 | ((uint64_t)(uint32_t) r0.i);\n' \
                        'uint64_t op2 = ((uint64_t)(uint32_t) r3.i) << 32 | ((uint64_t)(uint32_t) r2.i);\n' \
                        'r0.i = *(double *)&op1 == *(double *)&op2;\n' \
                        '}\n',
    '__aeabi_dcmple':   'void dcmple()\n' \
                        '{\n' \
                        'uint64_t op1 = ((uint64_t)(uint32_t) r1.i) << 32 | ((uint64_t)(uint32_t) r0.i);\n' \
                        'uint64_t op2 = ((uint64_t)(uint32_t) r3.i) << 32 | ((uint64_t)(uint32_t) r2.i);\n' \
                        'r0.i = *(double *)&op1 <= *(double *)&op2;\n' \
                        '}\n',
    '__aeabi_dcmpge':   'void dcmpge()\n' \
                        '{\n' \
                        'uint64_t op1 = ((uint64_t)(uint32_t) r1.i) << 32 | ((uint64_t)(uint32_t) r0.i);\n' \
                        'uint64_t op2 = ((uint64_t)(uint32_t) r3.i) << 32 | ((uint64_t)(uint32_t) r2.i);\n' \
                        'r0.i = *(double *)&op1 >= *(double *)&op2;\n' \
                        '}\n',
    '__aeabi_dcmpgt':   'void dcmpgt()\n' \
                        '{\n' \
                        'uint64_t op1 = ((uint64_t)(uint32_t) r1.i) << 32 | ((uint64_t)(uint32_t) r0.i);\n' \
                        'uint64_t op2 = ((uint64_t)(uint32_t) r3.i) << 32 | ((uint64_t)(uint32_t) r2.i);\n' \
                        'r0.i = *(double *)&op1 > *(double *)&op2;\n' \
                        '}\n',
    '__aeabi_d2iz':     'void d2iz()\n' \
                        '{\n' \
                        'uint64_t op_int = ((uint64_t)(uint32_t) r1.i) << 32 | ((uint64_t)(uint32_t) r0.i);\n' \
                        'r0.i = (int32_t) *(double *)&op_int;\n' \
                        '}\n',
    '__aeabi_idivmod':  'void idivmod()\n' \
                        '{\n' \
                        'int32_t quot = r0.i / r1.i;\n' \
                        'int32_t rem = r0.i % r1.i;\n' \
                        'r0.i = quot;\n' \
                        'r1.i = rem;\n' \
                        '}\n',
    '__aeabi_idiv':     'void idiv()\n' \
                        '{\n' \
                        'r0.i = r0.i / r1.i;\n' \
                        '}\n',
    '__aeabi_i2d':      'void i2d()\n' \
                        '{\n' \
                        'double result = (double) r0.i;\n' \
                        'uint64_t result_uint64 = *(uint64_t *)&result;\n' \
                        'r1.i = (uint32_t) (result_uint64 >> 32);\n' \
                        'r0.i = (uint32_t) result_uint64;\n' \
                        '}\n',
    '__aeabi_ui2d':     'void ui2d()\n' \
                        '{\n' \
                        'double result = (double)(uint32_t) r0.i;\n' \
                        'uint64_t result_uint64 = *(uint64_t *)&result;\n' \
                        'r1.i = (uint32_t) (result_uint64 >> 32);\n' \
                        'r0.i = (uint32_t) result_uint64;\n' \
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
    'clock':            'void clock_help()\n' \
                        '{\n' \
                        'r0.i = clock();' \
                        '}\n',
    'puts':             '',
    'putchar':          '',
    'putc':             '',
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
    '__aeabi_idiv':     'idiv();\n',
    '__aeabi_i2d':      'i2d();\n',
    '__aeabi_ui2d':     'ui2d();\n',
    'malloc':           'malloc_help();\n',
    'free':             'free_help();\n',
    'calloc':           'calloc_help();\n',
    'memcpy':           'memcpy_help();\n',
    'memset':           'memset_help();\n',
    'strlen':           'strlen_help();\n',
    'rand':             'rand_help();\n',
    'srand':            'srand_help();\n',
    'time':             'time_help();\n',
    'clock':            'clock_help();\n',
    'puts':             'printf_help("%s\\n", r0.i, r1.i, r2.i);\n',
    'putchar':          'printf_help("%c", (char)r0.i, r1.i, r2.i);\n',
    'putc':             'printf_help("%c", (char)r0.i, r1.i, r2.i);\n',
    'nl':               'printf_help("\\n", r0.i, r1.i, r2.i);\n',
    'printf':           'printf_help(malloc_0+r0.i, r1.i, r2.i, r3.i);\n',
    '__printf_chk':     'printf_help(malloc_0+r1.i, r2.i, r3.i, r4.i);\n',
    '__assert_fail':    'assert_help();\n',
    '__isoc99_scanf':   'scanf_help();\n',
    'umull':            '',
    'smull':            ''
}

def get_auxiliary_functions(blocks: list[CodeBlock]) -> str:
    '''Determines the needed auxiliary functions for the translation.

    Parameters
    ----------
    blocks : list[CodeBlock]
        The code blocks with all their instructions.

    Returns
    -------
    str
        The C code containing all the necessary function definitions.
    '''
    result = ''
    function_calls = set()

    # get the necessary auxiliary functions for the translation
    for block in blocks:
        for instr in block.instructions:
            if ((instr[1] == 'bl' or instr[1] == 'b') and
                    instr[2][0] in call_dict):
                function_calls.add(instr[2][0])

            if instr[1] in call_dict:
                function_calls.add(instr[1])

            if re.match('(^ld.*)|(^st.*)|(^push.*)|(^pop.*)', instr[1]):
                opcode = instr[1]
                if 'push' not in opcode and 'pop' not in opcode:
                    digit_idx = re.search('\d', opcode).start()

                    if opcode[digit_idx-2:digit_idx] in cond_codes:
                        opcode = opcode[:digit_idx-2]+opcode[digit_idx:]
                else:
                    if opcode[-2:] in cond_codes:
                        opcode = opcode[:-2]

                function_calls.add(opcode)

    
    added_defs = set()

    for call in function_calls:
        if function_dict[call] not in added_defs:
            result += function_dict[call]
            added_defs.add(function_dict[call])

    return result

cond_codes = {
    'eq','ne','ge','gt','le','lt','ls',
    'cs','cc','hi','mi','pl','al','nv','vs','vc'
}