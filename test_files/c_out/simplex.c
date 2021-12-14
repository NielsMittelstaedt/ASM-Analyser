#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <regex.h>

typedef union
{
    int32_t i;
    float f;
} reg;

int32_t tmp;
reg sp, fp, lr, pc, ip;
bool z, n, c, v;
uint8_t* malloc_0 = 0;

reg r3, r9, r8, r1, r0, r5, r2, r6, r7, r4;

int32_t SimplexTable, TempState, LC1, LC2, LC3, LC4, LC5, LC6, LC0;

int load_counter = 0, store_counter = 0;
int counters[119] = { 0 };
int block_sizes[119] = {3,1,1,1,3,10,10,6,3,9,13,18,3,2,7,2,3,3,2,1,9,13,18,3,2,7,2,3,3,2,3,12,13,18,3,2,7,2,3,3,2,3,8,3,15,3,17,3,3,3,3,12,4,4,4,3,19,9,8,13,3,5,16,9,8,13,3,5,15,6,3,1,5,7,3,8,25,6,24,5,18,3,1,25,6,24,5,18,3,3,8,5,24,3,9,5,22,3,8,4,10,3,3,14,3,3,2,3,3,4,10,3,3,25,3,3,3,2,3};

void str8000(int32_t *target1, int32_t *target2, int32_t *address, int32_t offset)
{
    *((uint32_t*)(malloc_0+*address+offset)) = *target1;
    *((uint32_t*)(malloc_0+*address+offset+4)) = *target2;
    store_counter += 2;
}
void dmul()
{
    uint64_t op1 = ((uint64_t)(uint32_t) r1.i) << 32 | ((uint64_t)(uint32_t) r0.i);
    uint64_t op2 = ((uint64_t)(uint32_t) r3.i) << 32 | ((uint64_t)(uint32_t) r2.i);
    double result = *(double *)&op1 * *(double *)&op2;
    uint64_t result_uint64 = *(uint64_t *)&result;
    r1.i = (uint32_t) (result_uint64 >> 32);
    r0.i = (uint32_t) result_uint64;
}
void ldr2001(int32_t *target, int32_t *address, int32_t offset)
{
    *target = (*((uint16_t*)(malloc_0+*address+offset)) & 0xffff) << 16 >> 16;
    load_counter ++;
}
void ldr8000(int32_t *target1, int32_t *target2, int32_t *address, int32_t offset)
{
    *target1 = *((uint32_t*)(malloc_0+*address+offset));
    *target2 = *((uint32_t*)(malloc_0+*address+offset+4));
    load_counter += 2;
}
void dcmpeq()
{
    uint64_t op1 = ((uint64_t)(uint32_t) r1.i) << 32 | ((uint64_t)(uint32_t) r0.i);
    uint64_t op2 = ((uint64_t)(uint32_t) r3.i) << 32 | ((uint64_t)(uint32_t) r2.i);
    r0.i = *(double *)&op1 == *(double *)&op2;
}
void pop(int num, ...)
{
    va_list args;
    va_start(args, num);
    for (int i=0; i < num; i++)
    {
        int32_t *cur_arg = va_arg(args, int32_t *);
        *cur_arg = *((uint32_t*) (malloc_0 + sp.i));
        sp.i += 4;
        load_counter ++;
    }
    va_end(args);
}
void memcpy_help()
{
    memcpy(malloc_0+r0.i, malloc_0+r1.i, r2.i);
}
void push(int num, ...)
{
    va_list args;
    va_start(args, num);
    for (int i=0; i < num; i++)
    {
        int32_t *cur_arg = va_arg(args, int32_t *);
        sp.i -= 4;
        *((uint32_t*) (malloc_0 + sp.i)) = *cur_arg;
        store_counter ++;
    }
    va_end(args);
}
void ldr4000(int32_t *target, int32_t *address, int32_t offset)
{
    *target = *((uint32_t*)(malloc_0+*address+offset));
    load_counter ++;
}
void str2000(int32_t *target, int32_t *address, int32_t offset)
{
    *((uint16_t*)(malloc_0+*address+offset)) = *target & 0xffff;
    store_counter ++;
}
void dsub()
{
    uint64_t op1 = ((uint64_t)(uint32_t) r1.i) << 32 | ((uint64_t)(uint32_t) r0.i);
    uint64_t op2 = ((uint64_t)(uint32_t) r3.i) << 32 | ((uint64_t)(uint32_t) r2.i);
    double result = *(double *)&op1 - *(double *)&op2;
    uint64_t result_uint64 = *(uint64_t *)&result;
    r1.i = (uint32_t) (result_uint64 >> 32);
    r0.i = (uint32_t) result_uint64;
}
void dadd()
{
    uint64_t op1 = ((uint64_t)(uint32_t) r1.i) << 32 | ((uint64_t)(uint32_t) r0.i);
    uint64_t op2 = ((uint64_t)(uint32_t) r3.i) << 32 | ((uint64_t)(uint32_t) r2.i);
    double result = *(double *)&op1 + *(double *)&op2;
    uint64_t result_uint64 = *(uint64_t *)&result;
    r1.i = (uint32_t) (result_uint64 >> 32);
    r0.i = (uint32_t) result_uint64;
}
void dcmplt()
{
    uint64_t op1 = ((uint64_t)(uint32_t) r1.i) << 32 | ((uint64_t)(uint32_t) r0.i);
    uint64_t op2 = ((uint64_t)(uint32_t) r3.i) << 32 | ((uint64_t)(uint32_t) r2.i);
    r0.i = *(double *)&op1 < *(double *)&op2;
}
void str4000(int32_t *target, int32_t *address, int32_t offset)
{
    *((uint32_t*)(malloc_0+*address+offset)) = *target;
    store_counter ++;
}
void ddiv()
{
    uint64_t op1 = ((uint64_t)(uint32_t) r1.i) << 32 | ((uint64_t)(uint32_t) r0.i);
    uint64_t op2 = ((uint64_t)(uint32_t) r3.i) << 32 | ((uint64_t)(uint32_t) r2.i);
    double result = *(double *)&op1 / *(double *)&op2;
    uint64_t result_uint64 = *(uint64_t *)&result;
    r1.i = (uint32_t) (result_uint64 >> 32);
    r0.i = (uint32_t) result_uint64;
}

void printf_help(const char *format, int32_t arg1, int32_t arg2, int32_t arg3)
{
    regex_t reg;
    if (regcomp(&reg, "(%([0-9]*)lf)|(%f)", REG_EXTENDED | REG_NOSUB) != 0) return;
    if (regexec(&reg, format, 0, 0, 0) == 0)
    {
        uint64_t arg = ((uint64_t)(uint32_t) arg3) << 32 | ((uint64_t)(uint32_t) arg2);
        double d_arg = *(double *)&arg;
        printf(format, d_arg);
        return;
    }
    else if(strstr(format, "%s"))
    {
        printf(format, malloc_0+arg1);
    }
    else if(strstr(format, "%c"))
    {
        printf(format, arg1);
    }
    else
    {
        printf(format, arg1);
    }
    regfree(&reg);
}

// TODO clz nur laden wenn gebraucht
void clz(int32_t *dest, int32_t *op)
{
    int msb = 1 << (32 - 1);
    int count = 0;
    uint32_t num = (uint32_t)*op;

    for(int i=0; i<32; i++)
    {
        if((num << i) & msb)
            break;
        count++;
    }

    *dest = count;
}

// Debugging purposes
/*void print_stack(int32_t start, int32_t bytes)
{
    int32_t size = bytes/4;
    int32_t cur_val = 0;

    for(int32_t i=0; i<size; i++){
        ldr4000(&cur_val, &start, i*4);
        printf("%d: %d\n", start+i*4, cur_val);
    }
}*/

void malloc_start()
{
    malloc_0 = (uint8_t*) malloc(20422);
    sp.i = 19996;
    fp = sp;
    SimplexTable = 20000;
    TempState = 20120;
    LC1 = 20160;
    strcpy(malloc_0+LC1, "\012***** Result *****\000");

    LC2 = 20188;
    strcpy(malloc_0+LC2, "x1 = %lf, \000");

    LC3 = 20204;
    strcpy(malloc_0+LC3, "x2 = %lf, \000");

    LC4 = 20220;
    strcpy(malloc_0+LC4, "f = %lf\012\000");

    LC5 = 20237;
    strcpy(malloc_0+LC5, "\012------------------Simplex Table Step = %d------");

    LC6 = 20290;
    strcpy(malloc_0+LC6, "%10lf \000");

    LC0 = 20302;
    int32_t arrayLC0[] = {0,1077739520,0,1078362112,0,0,0,0,0,0,0,1073741824,0,1075838976,0,1072693248,0,0,0,1078853632,0,1074790400,0,1074790400,0,0,0,1072693248,0,1078853632};
    for(int i=0; i<30; i++) *((uint32_t*)(malloc_0+LC0+i*4)) = arrayLC0[i];

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);

    printf("__count_start__\n");
    printf("%d\n", basic_blocks);

    for (int i=0; i < basic_blocks; i++)
    {
        printf("%d ", block_sizes[i]);
    }
    printf("\n");

    for (int i=0; i < basic_blocks; i++)
    {
        printf("%d ", counters[i]);
    }
    printf("\n");
    printf("%d\n", load_counter);
    printf("%d\n", store_counter);
}

void main();
void X2Calc();
void X1Calc();
void Result();
void Maxim();
void GaussCalc();
void Exchange();
void ShowTable();
void Input();

void main()
{
    malloc_start();
    counters[0] ++;
    push(2, &fp.i, &lr.i);
    fp.i = sp.i + (4);
    Input();
    counters[1] ++;
    X2Calc();
    counters[2] ++;
    X1Calc();
    counters[3] ++;
    Result();
    counters[4] ++;
    r3.i = 0;
    r0.i = r3.i;
    pop(2, &pc.i, &fp.i);
    counter_summary();
    return;

}

void X2Calc()
{
    counters[5] ++;
    push(2, &fp.i, &lr.i);
    fp.i = sp.i + (4);
    sp.i = sp.i - (56);
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    ldr8000(&r0.i, &r1.i, &r3.i, 72);
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    ldr8000(&r2.i, &r3.i, &r3.i, 48);
    ddiv();
    counters[6] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    str8000(&r2.i, &r3.i, &fp.i, -20);
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    ldr8000(&r0.i, &r1.i, &r3.i, 112);
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    ldr8000(&r2.i, &r3.i, &r3.i, 88);
    ddiv();
    counters[7] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    str8000(&r2.i, &r3.i, &fp.i, -28);
    ldr8000(&r2.i, &r3.i, &fp.i, -28);
    ldr8000(&r0.i, &r1.i, &fp.i, -20);
    dcmplt();
    counters[8] ++;
    r3.i = r0.i;
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L12;
    }
    counters[9] ++;
    r3.i = 1;
    str4000(&r3.i, &fp.i, -32);
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    ldr8000(&r2.i, &r3.i, &r3.i, 48);
    str8000(&r2.i, &r3.i, &fp.i, -60);
    r3.i = 0;
    str4000(&r3.i, &fp.i, -8);
    goto L6;
L7:
    counters[10] ++;
    r2.i = (SimplexTable & 0xffff);
    r2.i = r2.i | (((uint32_t)SimplexTable >> 16) << 16);
    ldr4000(&r1.i, &fp.i, -32);
    r3.i = r1.i;
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r3.i + (r1.i);
    ldr4000(&r1.i, &fp.i, -8);
    r3.i = r3.i + (r1.i);
    r3.i = (uint32_t)r3.i << 3;
    r3.i = r2.i + (r3.i);
    ldr8000(&r0.i, &r1.i, &r3.i, 0);
    ldr8000(&r2.i, &r3.i, &fp.i, -60);
    ddiv();
    counters[11] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r2.i;
    r1.i = r3.i;
    r2.i = (SimplexTable & 0xffff);
    r2.i = r2.i | (((uint32_t)SimplexTable >> 16) << 16);
    ldr4000(&ip.i, &fp.i, -32);
    r3.i = ip.i;
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r3.i + (ip.i);
    ldr4000(&ip.i, &fp.i, -8);
    r3.i = r3.i + (ip.i);
    r3.i = (uint32_t)r3.i << 3;
    r3.i = r2.i + (r3.i);
    str8000(&r0.i, &r1.i, &r3.i, 0);
    ldr4000(&r3.i, &fp.i, -8);
    r3.i = r3.i + (1);
    str4000(&r3.i, &fp.i, -8);
L6:
    counters[12] ++;
    ldr4000(&r3.i, &fp.i, -8);
    tmp = r3.i - 4;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 4);
    v = (r3.i&0x80000000) != (4&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L7;
    }
    counters[13] ++;
    r0.i = 1;
    ShowTable();
    counters[14] ++;
    r3.i = 1;
    str4000(&r3.i, &fp.i, -48);
    r3.i = 1;
    str4000(&r3.i, &fp.i, -52);
    ldr4000(&r1.i, &fp.i, -52);
    ldr4000(&r0.i, &fp.i, -48);
    GaussCalc();
    counters[15] ++;
    r0.i = 2;
    ShowTable();
    counters[16] ++;
    ldr4000(&r1.i, &fp.i, -52);
    ldr4000(&r0.i, &fp.i, -48);
    Exchange();
    counters[17] ++;
    ldr4000(&r1.i, &fp.i, -52);
    ldr4000(&r0.i, &fp.i, -48);
    Maxim();
    counters[18] ++;
    r0.i = 3;
    ShowTable();
    counters[19] ++;
    goto L13;
L12:
    counters[20] ++;
    r3.i = 2;
    str4000(&r3.i, &fp.i, -32);
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    ldr8000(&r2.i, &r3.i, &r3.i, 88);
    str8000(&r2.i, &r3.i, &fp.i, -44);
    r3.i = 0;
    str4000(&r3.i, &fp.i, -8);
    goto L9;
L10:
    counters[21] ++;
    r2.i = (SimplexTable & 0xffff);
    r2.i = r2.i | (((uint32_t)SimplexTable >> 16) << 16);
    ldr4000(&r1.i, &fp.i, -32);
    r3.i = r1.i;
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r3.i + (r1.i);
    ldr4000(&r1.i, &fp.i, -8);
    r3.i = r3.i + (r1.i);
    r3.i = (uint32_t)r3.i << 3;
    r3.i = r2.i + (r3.i);
    ldr8000(&r0.i, &r1.i, &r3.i, 0);
    ldr8000(&r2.i, &r3.i, &fp.i, -44);
    ddiv();
    counters[22] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r2.i;
    r1.i = r3.i;
    r2.i = (SimplexTable & 0xffff);
    r2.i = r2.i | (((uint32_t)SimplexTable >> 16) << 16);
    ldr4000(&ip.i, &fp.i, -32);
    r3.i = ip.i;
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r3.i + (ip.i);
    ldr4000(&ip.i, &fp.i, -8);
    r3.i = r3.i + (ip.i);
    r3.i = (uint32_t)r3.i << 3;
    r3.i = r2.i + (r3.i);
    str8000(&r0.i, &r1.i, &r3.i, 0);
    ldr4000(&r3.i, &fp.i, -8);
    r3.i = r3.i + (1);
    str4000(&r3.i, &fp.i, -8);
L9:
    counters[23] ++;
    ldr4000(&r3.i, &fp.i, -8);
    tmp = r3.i - 4;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 4);
    v = (r3.i&0x80000000) != (4&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L10;
    }
    counters[24] ++;
    r0.i = 1;
    ShowTable();
    counters[25] ++;
    r3.i = 2;
    str4000(&r3.i, &fp.i, -48);
    r3.i = 1;
    str4000(&r3.i, &fp.i, -52);
    ldr4000(&r1.i, &fp.i, -52);
    ldr4000(&r0.i, &fp.i, -48);
    GaussCalc();
    counters[26] ++;
    r0.i = 2;
    ShowTable();
    counters[27] ++;
    ldr4000(&r1.i, &fp.i, -52);
    ldr4000(&r0.i, &fp.i, -48);
    Exchange();
    counters[28] ++;
    ldr4000(&r1.i, &fp.i, -52);
    ldr4000(&r0.i, &fp.i, -48);
    Maxim();
    counters[29] ++;
    r0.i = 3;
    ShowTable();
L13:
    counters[30] ++;
    sp.i = fp.i - (4);
    pop(2, &pc.i, &fp.i);
    return;

}

void X1Calc()
{
    counters[31] ++;
    push(2, &fp.i, &lr.i);
    fp.i = sp.i + (4);
    sp.i = sp.i - (24);
    r3.i = 2;
    str4000(&r3.i, &fp.i, -12);
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    ldr8000(&r2.i, &r3.i, &r3.i, 80);
    str8000(&r2.i, &r3.i, &fp.i, -20);
    r3.i = 0;
    str4000(&r3.i, &fp.i, -8);
    goto L15;
L16:
    counters[32] ++;
    r2.i = (SimplexTable & 0xffff);
    r2.i = r2.i | (((uint32_t)SimplexTable >> 16) << 16);
    ldr4000(&r1.i, &fp.i, -12);
    r3.i = r1.i;
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r3.i + (r1.i);
    ldr4000(&r1.i, &fp.i, -8);
    r3.i = r3.i + (r1.i);
    r3.i = (uint32_t)r3.i << 3;
    r3.i = r2.i + (r3.i);
    ldr8000(&r0.i, &r1.i, &r3.i, 0);
    ldr8000(&r2.i, &r3.i, &fp.i, -20);
    ddiv();
    counters[33] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r2.i;
    r1.i = r3.i;
    r2.i = (SimplexTable & 0xffff);
    r2.i = r2.i | (((uint32_t)SimplexTable >> 16) << 16);
    ldr4000(&ip.i, &fp.i, -12);
    r3.i = ip.i;
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r3.i + (ip.i);
    ldr4000(&ip.i, &fp.i, -8);
    r3.i = r3.i + (ip.i);
    r3.i = (uint32_t)r3.i << 3;
    r3.i = r2.i + (r3.i);
    str8000(&r0.i, &r1.i, &r3.i, 0);
    ldr4000(&r3.i, &fp.i, -8);
    r3.i = r3.i + (1);
    str4000(&r3.i, &fp.i, -8);
L15:
    counters[34] ++;
    ldr4000(&r3.i, &fp.i, -8);
    tmp = r3.i - 4;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 4);
    v = (r3.i&0x80000000) != (4&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L16;
    }
    counters[35] ++;
    r0.i = 4;
    ShowTable();
    counters[36] ++;
    r3.i = 2;
    str4000(&r3.i, &fp.i, -24);
    r3.i = 0;
    str4000(&r3.i, &fp.i, -28);
    ldr4000(&r1.i, &fp.i, -28);
    ldr4000(&r0.i, &fp.i, -24);
    GaussCalc();
    counters[37] ++;
    r0.i = 5;
    ShowTable();
    counters[38] ++;
    ldr4000(&r1.i, &fp.i, -28);
    ldr4000(&r0.i, &fp.i, -24);
    Exchange();
    counters[39] ++;
    ldr4000(&r1.i, &fp.i, -28);
    ldr4000(&r0.i, &fp.i, -24);
    Maxim();
    counters[40] ++;
    r0.i = 6;
    ShowTable();
    counters[41] ++;
    sp.i = fp.i - (4);
    pop(2, &pc.i, &fp.i);
    return;

}

void Result()
{
    counters[42] ++;
    push(2, &fp.i, &lr.i);
    fp.i = sp.i + (4);
    sp.i = sp.i - (40);
    r3.i = 0;
    str4000(&r3.i, &fp.i, -16);
    r3.i = 1;
    str4000(&r3.i, &fp.i, -8);
    goto L18;
L23:
    counters[43] ++;
    r3.i = 0;
    str4000(&r3.i, &fp.i, -12);
    goto L19;
L22:
    counters[44] ++;
    r2.i = (SimplexTable & 0xffff);
    r2.i = r2.i | (((uint32_t)SimplexTable >> 16) << 16);
    ldr4000(&r1.i, &fp.i, -8);
    r3.i = r1.i;
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r3.i + (r1.i);
    ldr4000(&r1.i, &fp.i, -12);
    r3.i = r3.i + (r1.i);
    r3.i = (uint32_t)r3.i << 3;
    r3.i = r2.i + (r3.i);
    ldr8000(&r0.i, &r1.i, &r3.i, 0);
    r2.i = 0;
    r3.i = 0;
    r3.i = r3.i | (16368 << 16);
    dcmpeq();
    counters[45] ++;
    r3.i = r0.i;
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L20;
    }
    counters[46] ++;
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    ldr4000(&r2.i, &fp.i, -8);
    r1.i = 40;
    r2.i = (r1.i) * (r2.i);
    r3.i = r3.i + (r2.i);
    r3.i = r3.i + (32);
    ldr8000(&r2.i, &r3.i, &r3.i, 0);
    ldr4000(&r1.i, &fp.i, -16);
    r1.i = (uint32_t)r1.i << 3;
    r0.i = fp.i - (4);
    r1.i = r0.i + (r1.i);
    r1.i = r1.i - (40);
    str8000(&r2.i, &r3.i, &r1.i, 0);
    ldr4000(&r3.i, &fp.i, -16);
    r3.i = r3.i + (1);
    str4000(&r3.i, &fp.i, -16);
L20:
    counters[47] ++;
    ldr4000(&r3.i, &fp.i, -12);
    r3.i = r3.i + (1);
    str4000(&r3.i, &fp.i, -12);
L19:
    counters[48] ++;
    ldr4000(&r3.i, &fp.i, -12);
    tmp = r3.i - 4;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 4);
    v = (r3.i&0x80000000) != (4&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L22;
    }
    counters[49] ++;
    ldr4000(&r3.i, &fp.i, -8);
    r3.i = r3.i + (1);
    str4000(&r3.i, &fp.i, -8);
L18:
    counters[50] ++;
    ldr4000(&r3.i, &fp.i, -8);
    tmp = r3.i - 2;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 2);
    v = (r3.i&0x80000000) != (2&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L23;
    }
    counters[51] ++;
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    ldr8000(&r2.i, &r3.i, &r3.i, 32);
    ldr4000(&r1.i, &fp.i, -16);
    r1.i = (uint32_t)r1.i << 3;
    r0.i = fp.i - (4);
    r1.i = r0.i + (r1.i);
    r1.i = r1.i - (40);
    str8000(&r2.i, &r3.i, &r1.i, 0);
    r0.i = (LC1 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC1 >> 16) << 16);
    printf_help("%s\n", r0.i, r1.i, r2.i);
    counters[52] ++;
    ldr8000(&r2.i, &r3.i, &fp.i, -44);
    r0.i = (LC2 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC2 >> 16) << 16);
    printf_help(malloc_0+r0.i, r1.i, r2.i, r3.i);
    counters[53] ++;
    ldr8000(&r2.i, &r3.i, &fp.i, -36);
    r0.i = (LC3 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC3 >> 16) << 16);
    printf_help(malloc_0+r0.i, r1.i, r2.i, r3.i);
    counters[54] ++;
    ldr8000(&r2.i, &r3.i, &fp.i, -28);
    r0.i = (LC4 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC4 >> 16) << 16);
    printf_help(malloc_0+r0.i, r1.i, r2.i, r3.i);
    counters[55] ++;
    sp.i = fp.i - (4);
    pop(2, &pc.i, &fp.i);
    return;

}

void Maxim()
{
    counters[56] ++;
    push(2, &fp.i, &lr.i);
    fp.i = sp.i + (4);
    sp.i = sp.i - (56);
    str4000(&r0.i, &fp.i, -56);
    str4000(&r1.i, &fp.i, -60);
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    ldr4000(&r2.i, &fp.i, -60);
    r2.i = (uint32_t)r2.i << 3;
    r3.i = r3.i + (r2.i);
    ldr8000(&r2.i, &r3.i, &r3.i, 0);
    str8000(&r2.i, &r3.i, &fp.i, -20);
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    ldr8000(&r2.i, &r3.i, &r3.i, 32);
    str8000(&r2.i, &r3.i, &fp.i, -28);
    ldr4000(&r3.i, &fp.i, -56);
    tmp = r3.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 1);
    v = (r3.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L26;
    }
    counters[57] ++;
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    ldr8000(&r2.i, &r3.i, &r3.i, 0);
    str8000(&r2.i, &r3.i, &fp.i, -52);
    r3.i = 1;
    str4000(&r3.i, &fp.i, -40);
    r3.i = 0;
    str4000(&r3.i, &fp.i, -8);
    goto L27;
L28:
    counters[58] ++;
    r3.i = (TempState & 0xffff);
    r3.i = r3.i | (((uint32_t)TempState >> 16) << 16);
    ldr4000(&r2.i, &fp.i, -8);
    r2.i = (uint32_t)r2.i << 3;
    r3.i = r3.i + (r2.i);
    ldr8000(&r0.i, &r1.i, &r3.i, 0);
    ldr8000(&r2.i, &r3.i, &fp.i, -20);
    dmul();
    counters[59] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r2.i;
    r1.i = r3.i;
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    ldr4000(&r2.i, &fp.i, -8);
    r2.i = (uint32_t)r2.i << 3;
    r3.i = r3.i + (r2.i);
    str8000(&r0.i, &r1.i, &r3.i, 0);
    ldr4000(&r3.i, &fp.i, -8);
    r3.i = r3.i + (1);
    str4000(&r3.i, &fp.i, -8);
L27:
    counters[60] ++;
    ldr4000(&r3.i, &fp.i, -8);
    tmp = r3.i - 4;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 4);
    v = (r3.i&0x80000000) != (4&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L28;
    }
    counters[61] ++;
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    ldr8000(&r0.i, &r1.i, &r3.i, 0);
    ldr8000(&r2.i, &r3.i, &fp.i, -52);
    dadd();
    counters[62] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r2.i;
    r1.i = r3.i;
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    str8000(&r0.i, &r1.i, &r3.i, 0);
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    ldr4000(&r2.i, &fp.i, -60);
    r2.i = (uint32_t)r2.i << 3;
    r1.i = r3.i + (r2.i);
    r2.i = 0;
    r3.i = 0;
    str8000(&r2.i, &r3.i, &r1.i, 0);
    goto L29;
L26:
    counters[63] ++;
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    ldr8000(&r2.i, &r3.i, &r3.i, 16);
    str8000(&r2.i, &r3.i, &fp.i, -36);
    r3.i = 2;
    str4000(&r3.i, &fp.i, -40);
    r3.i = 0;
    str4000(&r3.i, &fp.i, -8);
    goto L30;
L31:
    counters[64] ++;
    r3.i = (TempState & 0xffff);
    r3.i = r3.i | (((uint32_t)TempState >> 16) << 16);
    ldr4000(&r2.i, &fp.i, -8);
    r2.i = (uint32_t)r2.i << 3;
    r3.i = r3.i + (r2.i);
    ldr8000(&r0.i, &r1.i, &r3.i, 0);
    ldr8000(&r2.i, &r3.i, &fp.i, -20);
    dmul();
    counters[65] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r2.i;
    r1.i = r3.i;
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    ldr4000(&r2.i, &fp.i, -8);
    r2.i = (uint32_t)r2.i << 3;
    r3.i = r3.i + (r2.i);
    str8000(&r0.i, &r1.i, &r3.i, 0);
    ldr4000(&r3.i, &fp.i, -8);
    r3.i = r3.i + (1);
    str4000(&r3.i, &fp.i, -8);
L30:
    counters[66] ++;
    ldr4000(&r3.i, &fp.i, -8);
    tmp = r3.i - 4;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 4);
    v = (r3.i&0x80000000) != (4&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L31;
    }
    counters[67] ++;
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    ldr8000(&r0.i, &r1.i, &r3.i, 16);
    ldr8000(&r2.i, &r3.i, &fp.i, -36);
    dadd();
    counters[68] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r2.i;
    r1.i = r3.i;
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    str8000(&r0.i, &r1.i, &r3.i, 16);
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    ldr4000(&r2.i, &fp.i, -60);
    r2.i = (uint32_t)r2.i << 3;
    r1.i = r3.i + (r2.i);
    r2.i = 0;
    r3.i = 0;
    str8000(&r2.i, &r3.i, &r1.i, 0);
L29:
    counters[69] ++;
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    ldr8000(&r0.i, &r1.i, &r3.i, 32);
    r2.i = 0;
    r3.i = 0;
    dcmpeq();
    counters[70] ++;
    r3.i = r0.i;
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L34;
    }
    counters[71] ++;
    goto L35;
L34:
    counters[72] ++;
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    ldr8000(&r0.i, &r1.i, &r3.i, 32);
    ldr8000(&r2.i, &r3.i, &fp.i, -28);
    dadd();
    counters[73] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r2.i;
    r1.i = r3.i;
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    str8000(&r0.i, &r1.i, &r3.i, 32);
L35:
    counters[74] ++;
    sp.i = fp.i - (4);
    pop(2, &pc.i, &fp.i);
    return;

}

void GaussCalc()
{
    counters[75] ++;
    push(4, &r4.i, &r5.i, &fp.i, &lr.i);
    fp.i = sp.i + (12);
    sp.i = sp.i - (32);
    str4000(&r0.i, &fp.i, -40);
    str4000(&r1.i, &fp.i, -44);
    ldr4000(&r3.i, &fp.i, -40);
    tmp = r3.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 1);
    v = (r3.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L37;
    }
    counters[76] ++;
    r3.i = 2;
    str4000(&r3.i, &fp.i, -20);
    r2.i = (SimplexTable & 0xffff);
    r2.i = r2.i | (((uint32_t)SimplexTable >> 16) << 16);
    ldr4000(&r1.i, &fp.i, -20);
    r3.i = r1.i;
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r3.i + (r1.i);
    ldr4000(&r1.i, &fp.i, -44);
    r3.i = r3.i + (r1.i);
    r3.i = (uint32_t)r3.i << 3;
    r3.i = r2.i + (r3.i);
    ldr8000(&r0.i, &r1.i, &r3.i, 0);
    r2.i = (SimplexTable & 0xffff);
    r2.i = r2.i | (((uint32_t)SimplexTable >> 16) << 16);
    ldr4000(&ip.i, &fp.i, -40);
    r3.i = ip.i;
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r3.i + (ip.i);
    ldr4000(&ip.i, &fp.i, -44);
    r3.i = r3.i + (ip.i);
    r3.i = (uint32_t)r3.i << 3;
    r3.i = r2.i + (r3.i);
    ldr8000(&r2.i, &r3.i, &r3.i, 0);
    ddiv();
    counters[77] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    str8000(&r2.i, &r3.i, &fp.i, -36);
    r3.i = 0;
    str4000(&r3.i, &fp.i, -16);
    goto L38;
L39:
    counters[78] ++;
    r2.i = (SimplexTable & 0xffff);
    r2.i = r2.i | (((uint32_t)SimplexTable >> 16) << 16);
    ldr4000(&r1.i, &fp.i, -20);
    r3.i = r1.i;
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r3.i + (r1.i);
    ldr4000(&r1.i, &fp.i, -16);
    r3.i = r3.i + (r1.i);
    r3.i = (uint32_t)r3.i << 3;
    r3.i = r2.i + (r3.i);
    ldr8000(&r4.i, &r5.i, &r3.i, 0);
    r2.i = (SimplexTable & 0xffff);
    r2.i = r2.i | (((uint32_t)SimplexTable >> 16) << 16);
    ldr4000(&r1.i, &fp.i, -40);
    r3.i = r1.i;
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r3.i + (r1.i);
    ldr4000(&r1.i, &fp.i, -16);
    r3.i = r3.i + (r1.i);
    r3.i = (uint32_t)r3.i << 3;
    r3.i = r2.i + (r3.i);
    ldr8000(&r0.i, &r1.i, &r3.i, 0);
    ldr8000(&r2.i, &r3.i, &fp.i, -36);
    dmul();
    counters[79] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r4.i;
    r1.i = r5.i;
    dsub();
    counters[80] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r2.i;
    r1.i = r3.i;
    r2.i = (SimplexTable & 0xffff);
    r2.i = r2.i | (((uint32_t)SimplexTable >> 16) << 16);
    ldr4000(&ip.i, &fp.i, -20);
    r3.i = ip.i;
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r3.i + (ip.i);
    ldr4000(&ip.i, &fp.i, -16);
    r3.i = r3.i + (ip.i);
    r3.i = (uint32_t)r3.i << 3;
    r3.i = r2.i + (r3.i);
    str8000(&r0.i, &r1.i, &r3.i, 0);
    ldr4000(&r3.i, &fp.i, -16);
    r3.i = r3.i + (1);
    str4000(&r3.i, &fp.i, -16);
L38:
    counters[81] ++;
    ldr4000(&r3.i, &fp.i, -16);
    tmp = r3.i - 4;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 4);
    v = (r3.i&0x80000000) != (4&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L39;
    }
    counters[82] ++;
    goto L43;
L37:
    counters[83] ++;
    r3.i = 1;
    str4000(&r3.i, &fp.i, -20);
    r2.i = (SimplexTable & 0xffff);
    r2.i = r2.i | (((uint32_t)SimplexTable >> 16) << 16);
    ldr4000(&r1.i, &fp.i, -20);
    r3.i = r1.i;
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r3.i + (r1.i);
    ldr4000(&r1.i, &fp.i, -44);
    r3.i = r3.i + (r1.i);
    r3.i = (uint32_t)r3.i << 3;
    r3.i = r2.i + (r3.i);
    ldr8000(&r0.i, &r1.i, &r3.i, 0);
    r2.i = (SimplexTable & 0xffff);
    r2.i = r2.i | (((uint32_t)SimplexTable >> 16) << 16);
    ldr4000(&ip.i, &fp.i, -40);
    r3.i = ip.i;
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r3.i + (ip.i);
    ldr4000(&ip.i, &fp.i, -44);
    r3.i = r3.i + (ip.i);
    r3.i = (uint32_t)r3.i << 3;
    r3.i = r2.i + (r3.i);
    ldr8000(&r2.i, &r3.i, &r3.i, 0);
    ddiv();
    counters[84] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    str8000(&r2.i, &r3.i, &fp.i, -28);
    r3.i = 0;
    str4000(&r3.i, &fp.i, -16);
    goto L41;
L42:
    counters[85] ++;
    r2.i = (SimplexTable & 0xffff);
    r2.i = r2.i | (((uint32_t)SimplexTable >> 16) << 16);
    ldr4000(&r1.i, &fp.i, -20);
    r3.i = r1.i;
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r3.i + (r1.i);
    ldr4000(&r1.i, &fp.i, -16);
    r3.i = r3.i + (r1.i);
    r3.i = (uint32_t)r3.i << 3;
    r3.i = r2.i + (r3.i);
    ldr8000(&r4.i, &r5.i, &r3.i, 0);
    r2.i = (SimplexTable & 0xffff);
    r2.i = r2.i | (((uint32_t)SimplexTable >> 16) << 16);
    ldr4000(&r1.i, &fp.i, -40);
    r3.i = r1.i;
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r3.i + (r1.i);
    ldr4000(&r1.i, &fp.i, -16);
    r3.i = r3.i + (r1.i);
    r3.i = (uint32_t)r3.i << 3;
    r3.i = r2.i + (r3.i);
    ldr8000(&r0.i, &r1.i, &r3.i, 0);
    ldr8000(&r2.i, &r3.i, &fp.i, -28);
    dmul();
    counters[86] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r4.i;
    r1.i = r5.i;
    dsub();
    counters[87] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r2.i;
    r1.i = r3.i;
    r2.i = (SimplexTable & 0xffff);
    r2.i = r2.i | (((uint32_t)SimplexTable >> 16) << 16);
    ldr4000(&ip.i, &fp.i, -20);
    r3.i = ip.i;
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r3.i + (ip.i);
    ldr4000(&ip.i, &fp.i, -16);
    r3.i = r3.i + (ip.i);
    r3.i = (uint32_t)r3.i << 3;
    r3.i = r2.i + (r3.i);
    str8000(&r0.i, &r1.i, &r3.i, 0);
    ldr4000(&r3.i, &fp.i, -16);
    r3.i = r3.i + (1);
    str4000(&r3.i, &fp.i, -16);
L41:
    counters[88] ++;
    ldr4000(&r3.i, &fp.i, -16);
    tmp = r3.i - 4;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 4);
    v = (r3.i&0x80000000) != (4&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L42;
    }
L43:
    counters[89] ++;
    sp.i = fp.i - (12);
    pop(4, &pc.i, &fp.i, &r5.i, &r4.i);
    return;

}

void Exchange()
{
    counters[90] ++;
    push(7, &r4.i, &r5.i, &r6.i, &r7.i, &r8.i, &r9.i, &fp.i);
    fp.i = sp.i + (24);
    sp.i = sp.i - (28);
    str4000(&r0.i, &fp.i, -40);
    str4000(&r1.i, &fp.i, -44);
    ldr4000(&r3.i, &fp.i, -40);
    tmp = r3.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 1);
    v = (r3.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L45;
    }
    counters[91] ++;
    r3.i = 1;
    str4000(&r3.i, &fp.i, -36);
    r3.i = 0;
    str4000(&r3.i, &fp.i, -32);
    goto L46;
L47:
    counters[92] ++;
    r2.i = (SimplexTable & 0xffff);
    r2.i = r2.i | (((uint32_t)SimplexTable >> 16) << 16);
    ldr4000(&r1.i, &fp.i, -36);
    r3.i = r1.i;
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r3.i + (r1.i);
    ldr4000(&r1.i, &fp.i, -32);
    r3.i = r3.i + (r1.i);
    r3.i = (uint32_t)r3.i << 3;
    r3.i = r2.i + (r3.i);
    ldr8000(&r2.i, &r3.i, &r3.i, 0);
    str4000(&r2.i, &fp.i, -52);
    r3.i = r3.i ^ -2147483648;
    str4000(&r3.i, &fp.i, -48);
    r3.i = (TempState & 0xffff);
    r3.i = r3.i | (((uint32_t)TempState >> 16) << 16);
    ldr4000(&r2.i, &fp.i, -32);
    r2.i = (uint32_t)r2.i << 3;
    r3.i = r3.i + (r2.i);
    ldr8000(&r0.i, &r1.i, &fp.i, -52);
    str8000(&r0.i, &r1.i, &r3.i, 0);
    ldr4000(&r3.i, &fp.i, -32);
    r3.i = r3.i + (1);
    str4000(&r3.i, &fp.i, -32);
L46:
    counters[93] ++;
    ldr4000(&r3.i, &fp.i, -32);
    tmp = r3.i - 4;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 4);
    v = (r3.i&0x80000000) != (4&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L47;
    }
    counters[94] ++;
    r3.i = (TempState & 0xffff);
    r3.i = r3.i | (((uint32_t)TempState >> 16) << 16);
    ldr8000(&r2.i, &r3.i, &r3.i, 32);
    r8.i = r2.i;
    r9.i = r3.i ^ -2147483648;
    r3.i = (TempState & 0xffff);
    r3.i = r3.i | (((uint32_t)TempState >> 16) << 16);
    str8000(&r8.i, &r9.i, &r3.i, 32);
    goto L51;
L45:
    counters[95] ++;
    r3.i = 2;
    str4000(&r3.i, &fp.i, -36);
    r3.i = 0;
    str4000(&r3.i, &fp.i, -32);
    goto L49;
L50:
    counters[96] ++;
    r2.i = (SimplexTable & 0xffff);
    r2.i = r2.i | (((uint32_t)SimplexTable >> 16) << 16);
    ldr4000(&r1.i, &fp.i, -36);
    r3.i = r1.i;
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r3.i + (r1.i);
    ldr4000(&r1.i, &fp.i, -32);
    r3.i = r3.i + (r1.i);
    r3.i = (uint32_t)r3.i << 3;
    r3.i = r2.i + (r3.i);
    ldr8000(&r2.i, &r3.i, &r3.i, 0);
    r6.i = r2.i;
    r7.i = r3.i ^ -2147483648;
    r3.i = (TempState & 0xffff);
    r3.i = r3.i | (((uint32_t)TempState >> 16) << 16);
    ldr4000(&r2.i, &fp.i, -32);
    r2.i = (uint32_t)r2.i << 3;
    r3.i = r3.i + (r2.i);
    str8000(&r6.i, &r7.i, &r3.i, 0);
    ldr4000(&r3.i, &fp.i, -32);
    r3.i = r3.i + (1);
    str4000(&r3.i, &fp.i, -32);
L49:
    counters[97] ++;
    ldr4000(&r3.i, &fp.i, -32);
    tmp = r3.i - 4;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 4);
    v = (r3.i&0x80000000) != (4&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L50;
    }
    counters[98] ++;
    r3.i = (TempState & 0xffff);
    r3.i = r3.i | (((uint32_t)TempState >> 16) << 16);
    ldr8000(&r2.i, &r3.i, &r3.i, 32);
    r4.i = r2.i;
    r5.i = r3.i ^ -2147483648;
    r3.i = (TempState & 0xffff);
    r3.i = r3.i | (((uint32_t)TempState >> 16) << 16);
    str8000(&r4.i, &r5.i, &r3.i, 32);
L51:
    counters[99] ++;
    sp.i = fp.i - (24);
    pop(7, &fp.i, &r9.i, &r8.i, &r7.i, &r6.i, &r5.i, &r4.i);
    return;

}

void ShowTable()
{
    counters[100] ++;
    push(2, &fp.i, &lr.i);
    fp.i = sp.i + (4);
    sp.i = sp.i - (16);
    r3.i = r0.i;
    str2000(&r3.i, &fp.i, -14);
    ldr2001(&r3.i, &fp.i, -14);
    r1.i = r3.i;
    r0.i = (LC5 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC5 >> 16) << 16);
    printf_help(malloc_0+r0.i, r1.i, r2.i, r3.i);
    counters[101] ++;
    r3.i = 0;
    str4000(&r3.i, &fp.i, -8);
    goto L53;
L56:
    counters[102] ++;
    r3.i = 0;
    str4000(&r3.i, &fp.i, -12);
    goto L54;
L55:
    counters[103] ++;
    r2.i = (SimplexTable & 0xffff);
    r2.i = r2.i | (((uint32_t)SimplexTable >> 16) << 16);
    ldr4000(&r1.i, &fp.i, -8);
    r3.i = r1.i;
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r3.i + (r1.i);
    ldr4000(&r1.i, &fp.i, -12);
    r3.i = r3.i + (r1.i);
    r3.i = (uint32_t)r3.i << 3;
    r3.i = r2.i + (r3.i);
    ldr8000(&r2.i, &r3.i, &r3.i, 0);
    r0.i = (LC6 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC6 >> 16) << 16);
    printf_help(malloc_0+r0.i, r1.i, r2.i, r3.i);
    counters[104] ++;
    ldr4000(&r3.i, &fp.i, -12);
    r3.i = r3.i + (1);
    str4000(&r3.i, &fp.i, -12);
L54:
    counters[105] ++;
    ldr4000(&r3.i, &fp.i, -12);
    tmp = r3.i - 4;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 4);
    v = (r3.i&0x80000000) != (4&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L55;
    }
    counters[106] ++;
    r0.i = 10;
    printf_help("%c", r0.i, r1.i, r2.i);
    counters[107] ++;
    ldr4000(&r3.i, &fp.i, -8);
    r3.i = r3.i + (1);
    str4000(&r3.i, &fp.i, -8);
L53:
    counters[108] ++;
    ldr4000(&r3.i, &fp.i, -8);
    tmp = r3.i - 2;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 2);
    v = (r3.i&0x80000000) != (2&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L56;
    }
    counters[109] ++;
    sp.i = fp.i - (4);
    pop(2, &pc.i, &fp.i);
    return;

}

void Input()
{
    counters[110] ++;
    push(2, &fp.i, &lr.i);
    fp.i = sp.i + (4);
    sp.i = sp.i - (128);
    r3.i = (LC0 & 0xffff);
    r3.i = r3.i | (((uint32_t)LC0 >> 16) << 16);
    r0.i = fp.i - (132);
    r1.i = r3.i;
    r3.i = 120;
    r2.i = r3.i;
    memcpy_help();
    counters[111] ++;
    r3.i = 0;
    str4000(&r3.i, &fp.i, -8);
    goto L58;
L61:
    counters[112] ++;
    r3.i = 0;
    str4000(&r3.i, &fp.i, -12);
    goto L59;
L60:
    counters[113] ++;
    ldr4000(&r2.i, &fp.i, -8);
    r3.i = r2.i;
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r3.i + (r2.i);
    ldr4000(&r2.i, &fp.i, -12);
    r3.i = r3.i + (r2.i);
    r3.i = (uint32_t)r3.i << 3;
    r2.i = fp.i - (4);
    r3.i = r2.i + (r3.i);
    r3.i = r3.i - (128);
    ldr8000(&r0.i, &r1.i, &r3.i, 0);
    r2.i = (SimplexTable & 0xffff);
    r2.i = r2.i | (((uint32_t)SimplexTable >> 16) << 16);
    ldr4000(&ip.i, &fp.i, -8);
    r3.i = ip.i;
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r3.i + (ip.i);
    ldr4000(&ip.i, &fp.i, -12);
    r3.i = r3.i + (ip.i);
    r3.i = (uint32_t)r3.i << 3;
    r3.i = r2.i + (r3.i);
    str8000(&r0.i, &r1.i, &r3.i, 0);
    ldr4000(&r3.i, &fp.i, -12);
    r3.i = r3.i + (1);
    str4000(&r3.i, &fp.i, -12);
L59:
    counters[114] ++;
    ldr4000(&r3.i, &fp.i, -12);
    tmp = r3.i - 4;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 4);
    v = (r3.i&0x80000000) != (4&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L60;
    }
    counters[115] ++;
    ldr4000(&r3.i, &fp.i, -8);
    r3.i = r3.i + (1);
    str4000(&r3.i, &fp.i, -8);
L58:
    counters[116] ++;
    ldr4000(&r3.i, &fp.i, -8);
    tmp = r3.i - 2;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 2);
    v = (r3.i&0x80000000) != (2&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L61;
    }
    counters[117] ++;
    r0.i = 0;
    ShowTable();
    counters[118] ++;
    sp.i = fp.i - (4);
    pop(2, &pc.i, &fp.i);
    return;

}

