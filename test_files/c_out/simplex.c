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

reg r7, r2, r5, r8, r6, r1, r0, r10, r3, r9, r4;

int32_t LC1, LC2, L40, L59, LC3, LC4, LC5, LC6, L121, TempState, SimplexTable, LC0;

int load_counter = 0, store_counter = 0;
int counters[234] = { 0 };
int block_sizes[234] = {9,7,6,2,5,9,5,5,9,1,4,2,3,3,11,4,4,8,4,7,4,7,4,7,4,8,1,4,2,3,3,37,8,6,8,3,7,2,5,2,1,4,2,3,3,2,5,7,5,5,12,1,4,2,3,3,11,4,4,8,4,7,4,7,4,7,4,8,1,4,2,3,3,38,8,6,8,3,7,2,5,2,1,4,2,3,3,2,4,2,4,2,11,5,5,5,6,8,2,1,4,2,3,3,9,7,5,9,4,6,4,6,4,6,4,8,1,4,2,3,3,38,8,6,8,3,7,2,4,1,5,2,1,4,2,3,3,2,9,4,5,5,5,5,5,5,8,2,5,6,5,5,5,5,5,5,8,5,7,5,5,7,5,12,4,5,7,6,7,5,4,6,2,4,1,2,4,6,5,5,7,5,5,7,9,7,4,7,4,7,4,7,4,7,4,2,5,4,4,7,4,7,4,7,4,7,4,2,7,16,7,17,7,3,1,4,2,3,2,1,7,40,1,1,4,2,3,2,2,2,1,1,1,2};

int cond_branches = 0, mispredictions = 0;
uint8_t branch_bits[31] = {0};

void memcpy_help()
{
    memcpy(malloc_0+r0.i, malloc_0+r1.i, r2.i);
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
void dcmpeq()
{
    uint64_t op1 = ((uint64_t)(uint32_t) r1.i) << 32 | ((uint64_t)(uint32_t) r0.i);
    uint64_t op2 = ((uint64_t)(uint32_t) r3.i) << 32 | ((uint64_t)(uint32_t) r2.i);
    r0.i = *(double *)&op1 == *(double *)&op2;
}
void ldr4000(int32_t *target, int32_t *address, int32_t offset)
{
    *target = *((uint32_t*)(malloc_0+*address+offset));
    load_counter ++;
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
void str8000(int32_t *target1, int32_t *target2, int32_t *address, int32_t offset)
{
    *((uint32_t*)(malloc_0+*address+offset)) = *target1;
    *((uint32_t*)(malloc_0+*address+offset+4)) = *target2;
    store_counter += 2;
}
void ldr8010(int32_t *target1, int32_t *target2, int32_t *address, int32_t offset)
{
    *target1 = *((uint32_t*)(malloc_0+*address));
    *target2 = *((uint32_t*)(malloc_0+*address+4));
    *address += offset;
    load_counter += 2;
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
void ldr8000(int32_t *target1, int32_t *target2, int32_t *address, int32_t offset)
{
    *target1 = *((uint32_t*)(malloc_0+*address+offset));
    *target2 = *((uint32_t*)(malloc_0+*address+offset+4));
    load_counter += 2;
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
void dmul()
{
    uint64_t op1 = ((uint64_t)(uint32_t) r1.i) << 32 | ((uint64_t)(uint32_t) r0.i);
    uint64_t op2 = ((uint64_t)(uint32_t) r3.i) << 32 | ((uint64_t)(uint32_t) r2.i);
    double result = *(double *)&op1 * *(double *)&op2;
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

// Debugging purposes
/*
void print_stack(int32_t start, int32_t bytes)
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
    malloc_0 = (uint8_t*) malloc(20434);
    sp.i = 19996;
    fp = sp;
    LC1 = 20000;
    strcpy(malloc_0+LC1, "\012------------------Simplex Table Step = %d------");

    LC2 = 20053;
    strcpy(malloc_0+LC2, "%10lf \000");

    TempState = 20065;
    SimplexTable = 20105;
    L40 = 20225;
    int32_t arrayL40[] = {SimplexTable+160};
    for(int i=0; i<1; i++) *((uint32_t*)(malloc_0+L40+i*4)) = arrayL40[i];

    LC3 = 20229;
    strcpy(malloc_0+LC3, "\012***** Result *****\000");

    LC4 = 20257;
    strcpy(malloc_0+LC4, "x1 = %lf, \000");

    LC5 = 20273;
    strcpy(malloc_0+LC5, "x2 = %lf, \000");

    LC6 = 20289;
    strcpy(malloc_0+LC6, "f = %lf\012\000");

    L59 = 20306;
    int32_t arrayL59[] = {SimplexTable+160};
    for(int i=0; i<1; i++) *((uint32_t*)(malloc_0+L59+i*4)) = arrayL59[i];

    L121 = 20310;
    int32_t arrayL121[] = {SimplexTable+40};
    for(int i=0; i<1; i++) *((uint32_t*)(malloc_0+L121+i*4)) = arrayL121[i];

    LC0 = 20314;
    int32_t arrayLC0[] = {0,1077739520,0,1078362112,0,0,0,0,0,0,0,1073741824,0,1075838976,0,1072693248,0,0,0,1078853632,0,1074790400,0,1074790400,0,0,0,1072693248,0,1078853632};
    for(int i=0; i<30; i++) *((uint32_t*)(malloc_0+LC0+i*4)) = arrayLC0[i];

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);

    printf("\n__count_start__\n");
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
    printf("%d\n", cond_branches);
    printf("%d\n", mispredictions);
}

void X2Calc();
void X1Calc();
void Result();
void Maxim();
void GaussCalc();
void Exchange();
void ShowTable();
void Input();
void main();

void X2Calc()
{
    counters[0] ++;
    push(9, &r4.i, &r5.i, &r6.i, &r7.i, &r8.i, &r9.i, &r10.i, &fp.i, &lr.i);
    fp.i = (SimplexTable & 0xffff);
    fp.i = fp.i | (((uint32_t)SimplexTable >> 16) << 16);
    sp.i = sp.i - (28);
    ldr8000(&r8.i, &r9.i, &fp.i, 48);
    ldr8000(&r0.i, &r1.i, &fp.i, 72);
    r2.i = r8.i;
    r3.i = r9.i;
    ddiv();
    counters[1] ++;
    ldr8000(&r6.i, &r7.i, &fp.i, 88);
    r2.i = r6.i;
    r3.i = r7.i;
    r4.i = r0.i;
    r5.i = r1.i;
    ldr8000(&r0.i, &r1.i, &fp.i, 112);
    ddiv();
    counters[2] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r4.i;
    r1.i = r5.i;
    str8000(&r2.i, &r3.i, &sp.i, 0);
    dcmplt();
    counters[3] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (z)
    {
        cond_branches ++;
        if(branch_bits[0] == 0 || branch_bits[0] == 1)
        {
            mispredictions++;
            branch_bits[0]++;
        }
        else if(branch_bits[0] == 2)
        {
            branch_bits[0]++;
        }
        goto L34;
    }
    cond_branches ++;
    if(branch_bits[0] == 2 || branch_bits[0] == 3)
    {
        mispredictions++;
        branch_bits[0]--;
    }
    else if(branch_bits[0] == 1)
    {
        branch_bits[0]--;
    }
    counters[4] ++;
    r2.i = r8.i;
    r3.i = r9.i;
    ldr8000(&r0.i, &r1.i, &fp.i, 40);
    r10.i = fp.i + (40);
    ddiv();
    counters[5] ++;
    r2.i = r8.i;
    r3.i = r9.i;
    r7.i = (LC2 & 0xffff);
    r6.i = r10.i;
    r7.i = r7.i | (((uint32_t)LC2 >> 16) << 16);
    str8000(&r0.i, &r1.i, &fp.i, 40);
    r0.i = r8.i;
    r1.i = r9.i;
    ddiv();
    counters[6] ++;
    r2.i = r8.i;
    r3.i = r9.i;
    str8000(&r0.i, &r1.i, &fp.i, 48);
    ldr8000(&r0.i, &r1.i, &fp.i, 56);
    ddiv();
    counters[7] ++;
    r2.i = r8.i;
    r3.i = r9.i;
    str8000(&r0.i, &r1.i, &fp.i, 56);
    ldr8000(&r0.i, &r1.i, &fp.i, 64);
    ddiv();
    counters[8] ++;
    r2.i = 1;
    str8000(&r4.i, &r5.i, &fp.i, 72);
    r8.i = r0.i;
    r9.i = r1.i;
    r0.i = r2.i;
    r1.i = (LC1 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC1 >> 16) << 16);
    str8000(&r8.i, &r9.i, &fp.i, 64);
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
L4:
    counters[9] ++;
    r4.i = r6.i - (40);
L5:
    counters[10] ++;
    ldr8010(&r2.i, &r3.i, &r4.i, 8);
    r1.i = r7.i;
    r0.i = 1;
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[11] ++;
    tmp = r4.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r6.i);
    v = (r4.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        cond_branches ++;
        if(branch_bits[1] == 0 || branch_bits[1] == 1)
        {
            mispredictions++;
            branch_bits[1]++;
        }
        else if(branch_bits[1] == 2)
        {
            branch_bits[1]++;
        }
        goto L5;
    }
    cond_branches ++;
    if(branch_bits[1] == 2 || branch_bits[1] == 3)
    {
        mispredictions++;
        branch_bits[1]--;
    }
    else if(branch_bits[1] == 1)
    {
        branch_bits[1]--;
    }
    counters[12] ++;
    r0.i = 10;
    r6.i = r4.i + (40);
    printf_help("%c", r0.i, r1.i, r2.i);
    counters[13] ++;
    ldr4000(&r3.i, &L40, 0);
    tmp = r3.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r6.i);
    v = (r3.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        cond_branches ++;
        if(branch_bits[2] == 0 || branch_bits[2] == 1)
        {
            mispredictions++;
            branch_bits[2]++;
        }
        else if(branch_bits[2] == 2)
        {
            branch_bits[2]++;
        }
        goto L4;
    }
    cond_branches ++;
    if(branch_bits[2] == 2 || branch_bits[2] == 3)
    {
        mispredictions++;
        branch_bits[2]--;
    }
    else if(branch_bits[2] == 1)
    {
        branch_bits[2]--;
    }
    counters[14] ++;
    ldr8000(&r2.i, &r3.i, &fp.i, 88);
    r5.i = (LC2 & 0xffff);
    ldr8000(&r6.i, &r7.i, &fp.i, 48);
    r5.i = r5.i | (((uint32_t)LC2 >> 16) << 16);
    r4.i = r10.i;
    str8000(&r2.i, &r3.i, &sp.i, 0);
    r0.i = r2.i;
    r1.i = r3.i;
    r2.i = r6.i;
    r3.i = r7.i;
    ddiv();
    counters[15] ++;
    ldr8000(&r2.i, &r3.i, &fp.i, 40);
    r8.i = r0.i;
    r9.i = r1.i;
    dmul();
    counters[16] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    ldr8000(&r0.i, &r1.i, &fp.i, 80);
    dsub();
    counters[17] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r6.i;
    str8000(&r2.i, &r3.i, &fp.i, 80);
    r1.i = r7.i;
    r2.i = r8.i;
    r3.i = r9.i;
    dmul();
    counters[18] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    ldr8000(&r0.i, &r1.i, &sp.i, 0);
    dsub();
    counters[19] ++;
    ldr8000(&r2.i, &r3.i, &fp.i, 56);
    r6.i = r0.i;
    r7.i = r1.i;
    r0.i = r8.i;
    str8000(&r6.i, &r7.i, &fp.i, 88);
    r1.i = r9.i;
    dmul();
    counters[20] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    ldr8000(&r0.i, &r1.i, &fp.i, 96);
    dsub();
    counters[21] ++;
    ldr8000(&r2.i, &r3.i, &fp.i, 64);
    r6.i = r0.i;
    r7.i = r1.i;
    r0.i = r8.i;
    str8000(&r6.i, &r7.i, &fp.i, 96);
    r1.i = r9.i;
    dmul();
    counters[22] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    ldr8000(&r0.i, &r1.i, &fp.i, 104);
    dsub();
    counters[23] ++;
    ldr8000(&r2.i, &r3.i, &fp.i, 72);
    r6.i = r0.i;
    r7.i = r1.i;
    r0.i = r8.i;
    str8000(&r6.i, &r7.i, &fp.i, 104);
    r1.i = r9.i;
    dmul();
    counters[24] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    ldr8000(&r0.i, &r1.i, &fp.i, 112);
    dsub();
    counters[25] ++;
    r2.i = 2;
    r6.i = r0.i;
    r7.i = r1.i;
    r0.i = 1;
    r1.i = (LC1 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC1 >> 16) << 16);
    str8000(&r6.i, &r7.i, &fp.i, 112);
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
L7:
    counters[26] ++;
    r6.i = r4.i - (40);
L8:
    counters[27] ++;
    ldr8010(&r2.i, &r3.i, &r6.i, 8);
    r1.i = r5.i;
    r0.i = 1;
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[28] ++;
    tmp = r6.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) r4.i);
    v = (r6.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    if (!z)
    {
        cond_branches ++;
        if(branch_bits[3] == 0 || branch_bits[3] == 1)
        {
            mispredictions++;
            branch_bits[3]++;
        }
        else if(branch_bits[3] == 2)
        {
            branch_bits[3]++;
        }
        goto L8;
    }
    cond_branches ++;
    if(branch_bits[3] == 2 || branch_bits[3] == 3)
    {
        mispredictions++;
        branch_bits[3]--;
    }
    else if(branch_bits[3] == 1)
    {
        branch_bits[3]--;
    }
    counters[29] ++;
    r0.i = 10;
    r4.i = r6.i + (40);
    printf_help("%c", r0.i, r1.i, r2.i);
    counters[30] ++;
    ldr4000(&r3.i, &L40, 0);
    tmp = r3.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r4.i);
    v = (r3.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        cond_branches ++;
        if(branch_bits[4] == 0 || branch_bits[4] == 1)
        {
            mispredictions++;
            branch_bits[4]++;
        }
        else if(branch_bits[4] == 2)
        {
            branch_bits[4]++;
        }
        goto L7;
    }
    cond_branches ++;
    if(branch_bits[4] == 2 || branch_bits[4] == 3)
    {
        mispredictions++;
        branch_bits[4]--;
    }
    else if(branch_bits[4] == 1)
    {
        branch_bits[4]--;
    }
    counters[31] ++;
    ldr4000(&r3.i, &fp.i, 44);
    ip.i = (TempState & 0xffff);
    ldr4000(&r5.i, &fp.i, 40);
    ip.i = ip.i | (((uint32_t)TempState >> 16) << 16);
    r3.i = r3.i + (-2147483648);
    str4000(&r3.i, &sp.i, 12);
    ldr4000(&r3.i, &sp.i, 12);
    ldr4000(&r1.i, &fp.i, 60);
    r2.i = r5.i;
    ldr4000(&r0.i, &fp.i, 56);
    str8000(&r2.i, &r3.i, &ip.i, 0);
    lr.i = r1.i + (-2147483648);
    ldr8000(&r2.i, &r3.i, &fp.i, 72);
    ldr4000(&r1.i, &fp.i, 64);
    r7.i = lr.i;
    r6.i = r0.i;
    ldr4000(&r4.i, &fp.i, 68);
    str8000(&r2.i, &r3.i, &sp.i, 0);
    r3.i = lr.i;
    ldr4000(&lr.i, &fp.i, 48);
    r2.i = r6.i;
    str4000(&r1.i, &sp.i, 16);
    r4.i = r4.i + (-2147483648);
    ldr8000(&r8.i, &r9.i, &fp.i, 8);
    str8000(&r6.i, &r7.i, &ip.i, 16);
    r1.i = r4.i;
    ldr4000(&r0.i, &sp.i, 16);
    ldr8000(&r6.i, &r7.i, &sp.i, 0);
    str4000(&lr.i, &ip.i, 8);
    ldr4000(&lr.i, &fp.i, 52);
    str8000(&r0.i, &r1.i, &ip.i, 24);
    r0.i = r8.i;
    lr.i = lr.i + (-2147483648);
    str8000(&r6.i, &r7.i, &ip.i, 32);
    str4000(&lr.i, &ip.i, 12);
    r1.i = r9.i;
    dmul();
    counters[32] ++;
    ldr8000(&r6.i, &r7.i, &fp.i, 32);
    ldr4000(&r2.i, &sp.i, 16);
    r3.i = r4.i;
    str8000(&r6.i, &r7.i, &sp.i, 16);
    str8000(&r0.i, &r1.i, &fp.i, 16);
    r0.i = r8.i;
    r1.i = r9.i;
    dmul();
    counters[33] ++;
    ldr8000(&r2.i, &r3.i, &sp.i, 0);
    ldr8000(&r6.i, &r7.i, &fp.i, 0);
    str8000(&r0.i, &r1.i, &fp.i, 24);
    r0.i = r8.i;
    r1.i = r9.i;
    dmul();
    counters[34] ++;
    r2.i = r5.i;
    ldr4000(&r3.i, &sp.i, 12);
    r4.i = r0.i;
    r5.i = r1.i;
    r0.i = r8.i;
    r1.i = r9.i;
    str8000(&r4.i, &r5.i, &fp.i, 32);
    dmul();
    counters[35] ++;
    r2.i = r6.i;
    r3.i = r7.i;
    dadd();
    counters[36] ++;
    r2.i = 0;
    r3.i = 0;
    str8000(&r2.i, &r3.i, &fp.i, 8);
    str8000(&r0.i, &r1.i, &fp.i, 0);
    r0.i = r4.i;
    r1.i = r5.i;
    dcmpeq();
    counters[37] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (z)
    {
        cond_branches ++;
        if(branch_bits[5] == 0 || branch_bits[5] == 1)
        {
            mispredictions++;
            branch_bits[5]++;
        }
        else if(branch_bits[5] == 2)
        {
            branch_bits[5]++;
        }
        goto L38;
    }
    cond_branches ++;
    if(branch_bits[5] == 2 || branch_bits[5] == 3)
    {
        mispredictions++;
        branch_bits[5]--;
    }
    else if(branch_bits[5] == 1)
    {
        branch_bits[5]--;
    }
L10:
    counters[38] ++;
    r1.i = (LC1 & 0xffff);
    r2.i = 3;
    r1.i = r1.i | (((uint32_t)LC1 >> 16) << 16);
    r0.i = 1;
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[39] ++;
    r5.i = (LC2 & 0xffff);
    r5.i = r5.i | (((uint32_t)LC2 >> 16) << 16);
L12:
    counters[40] ++;
    r4.i = r10.i - (40);
L13:
    counters[41] ++;
    ldr8010(&r2.i, &r3.i, &r4.i, 8);
    r1.i = r5.i;
    r0.i = 1;
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[42] ++;
    tmp = r10.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r10.i) >= ((uint32_t) r4.i);
    v = (r10.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r10.i&0x80000000);
    if (!z)
    {
        cond_branches ++;
        if(branch_bits[6] == 0 || branch_bits[6] == 1)
        {
            mispredictions++;
            branch_bits[6]++;
        }
        else if(branch_bits[6] == 2)
        {
            branch_bits[6]++;
        }
        goto L13;
    }
    cond_branches ++;
    if(branch_bits[6] == 2 || branch_bits[6] == 3)
    {
        mispredictions++;
        branch_bits[6]--;
    }
    else if(branch_bits[6] == 1)
    {
        branch_bits[6]--;
    }
    counters[43] ++;
    r0.i = 10;
    r10.i = r10.i + (40);
    printf_help("%c", r0.i, r1.i, r2.i);
    counters[44] ++;
    ldr4000(&r3.i, &L40, 0);
    tmp = r3.i - r10.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r10.i);
    v = (r3.i&0x80000000) != (r10.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        cond_branches ++;
        if(branch_bits[7] == 0 || branch_bits[7] == 1)
        {
            mispredictions++;
            branch_bits[7]++;
        }
        else if(branch_bits[7] == 2)
        {
            branch_bits[7]++;
        }
        goto L12;
    }
    cond_branches ++;
    if(branch_bits[7] == 2 || branch_bits[7] == 3)
    {
        mispredictions++;
        branch_bits[7]--;
    }
    else if(branch_bits[7] == 1)
    {
        branch_bits[7]--;
    }
    counters[45] ++;
    sp.i = sp.i + (28);
    pop(9, &pc.i, &fp.i, &r10.i, &r9.i, &r8.i, &r7.i, &r6.i, &r5.i, &r4.i);
    return;
L34:
    counters[46] ++;
    r2.i = r6.i;
    r3.i = r7.i;
    ldr8000(&r0.i, &r1.i, &fp.i, 80);
    r10.i = fp.i + (40);
    ddiv();
    counters[47] ++;
    r2.i = r6.i;
    r3.i = r7.i;
    r5.i = r10.i;
    str8000(&r0.i, &r1.i, &fp.i, 80);
    r0.i = r6.i;
    r1.i = r7.i;
    ddiv();
    counters[48] ++;
    r2.i = r6.i;
    r3.i = r7.i;
    str8000(&r0.i, &r1.i, &fp.i, 88);
    ldr8000(&r0.i, &r1.i, &fp.i, 96);
    ddiv();
    counters[49] ++;
    r2.i = r6.i;
    r3.i = r7.i;
    str8000(&r0.i, &r1.i, &fp.i, 96);
    ldr8000(&r0.i, &r1.i, &fp.i, 104);
    ddiv();
    counters[50] ++;
    ldr8000(&r8.i, &r9.i, &sp.i, 0);
    r2.i = 1;
    str8000(&r8.i, &r9.i, &fp.i, 112);
    r6.i = r0.i;
    r7.i = r1.i;
    r0.i = r2.i;
    r1.i = (LC1 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC1 >> 16) << 16);
    str8000(&r6.i, &r7.i, &fp.i, 104);
    r6.i = (LC2 & 0xffff);
    r6.i = r6.i | (((uint32_t)LC2 >> 16) << 16);
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
L15:
    counters[51] ++;
    r4.i = r5.i - (40);
L16:
    counters[52] ++;
    ldr8010(&r2.i, &r3.i, &r4.i, 8);
    r1.i = r6.i;
    r0.i = 1;
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[53] ++;
    tmp = r5.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r4.i);
    v = (r5.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (!z)
    {
        cond_branches ++;
        if(branch_bits[8] == 0 || branch_bits[8] == 1)
        {
            mispredictions++;
            branch_bits[8]++;
        }
        else if(branch_bits[8] == 2)
        {
            branch_bits[8]++;
        }
        goto L16;
    }
    cond_branches ++;
    if(branch_bits[8] == 2 || branch_bits[8] == 3)
    {
        mispredictions++;
        branch_bits[8]--;
    }
    else if(branch_bits[8] == 1)
    {
        branch_bits[8]--;
    }
    counters[54] ++;
    r0.i = 10;
    r5.i = r5.i + (40);
    printf_help("%c", r0.i, r1.i, r2.i);
    counters[55] ++;
    ldr4000(&r3.i, &L40, 0);
    tmp = r5.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r3.i);
    v = (r5.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (!z)
    {
        cond_branches ++;
        if(branch_bits[9] == 0 || branch_bits[9] == 1)
        {
            mispredictions++;
            branch_bits[9]++;
        }
        else if(branch_bits[9] == 2)
        {
            branch_bits[9]++;
        }
        goto L15;
    }
    cond_branches ++;
    if(branch_bits[9] == 2 || branch_bits[9] == 3)
    {
        mispredictions++;
        branch_bits[9]--;
    }
    else if(branch_bits[9] == 1)
    {
        branch_bits[9]--;
    }
    counters[56] ++;
    ldr8000(&r2.i, &r3.i, &fp.i, 48);
    r5.i = (LC2 & 0xffff);
    ldr8000(&r6.i, &r7.i, &fp.i, 88);
    r5.i = r5.i | (((uint32_t)LC2 >> 16) << 16);
    r4.i = r10.i;
    str8000(&r2.i, &r3.i, &sp.i, 0);
    r0.i = r2.i;
    r1.i = r3.i;
    r2.i = r6.i;
    r3.i = r7.i;
    ddiv();
    counters[57] ++;
    ldr8000(&r2.i, &r3.i, &fp.i, 80);
    r8.i = r0.i;
    r9.i = r1.i;
    dmul();
    counters[58] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    ldr8000(&r0.i, &r1.i, &fp.i, 40);
    dsub();
    counters[59] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r6.i;
    str8000(&r2.i, &r3.i, &fp.i, 40);
    r1.i = r7.i;
    r2.i = r8.i;
    r3.i = r9.i;
    dmul();
    counters[60] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    ldr8000(&r0.i, &r1.i, &sp.i, 0);
    dsub();
    counters[61] ++;
    ldr8000(&r2.i, &r3.i, &fp.i, 96);
    r6.i = r0.i;
    r7.i = r1.i;
    r0.i = r8.i;
    str8000(&r6.i, &r7.i, &fp.i, 48);
    r1.i = r9.i;
    dmul();
    counters[62] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    ldr8000(&r0.i, &r1.i, &fp.i, 56);
    dsub();
    counters[63] ++;
    ldr8000(&r2.i, &r3.i, &fp.i, 104);
    r6.i = r0.i;
    r7.i = r1.i;
    r0.i = r8.i;
    str8000(&r6.i, &r7.i, &fp.i, 56);
    r1.i = r9.i;
    dmul();
    counters[64] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    ldr8000(&r0.i, &r1.i, &fp.i, 64);
    dsub();
    counters[65] ++;
    ldr8000(&r2.i, &r3.i, &fp.i, 112);
    r6.i = r0.i;
    r7.i = r1.i;
    r0.i = r8.i;
    str8000(&r6.i, &r7.i, &fp.i, 64);
    r1.i = r9.i;
    dmul();
    counters[66] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    ldr8000(&r0.i, &r1.i, &fp.i, 72);
    dsub();
    counters[67] ++;
    r2.i = 2;
    r6.i = r0.i;
    r7.i = r1.i;
    r0.i = 1;
    r1.i = (LC1 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC1 >> 16) << 16);
    str8000(&r6.i, &r7.i, &fp.i, 72);
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
L18:
    counters[68] ++;
    r6.i = r4.i - (40);
L19:
    counters[69] ++;
    ldr8010(&r2.i, &r3.i, &r6.i, 8);
    r1.i = r5.i;
    r0.i = 1;
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[70] ++;
    tmp = r6.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) r4.i);
    v = (r6.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    if (!z)
    {
        cond_branches ++;
        if(branch_bits[10] == 0 || branch_bits[10] == 1)
        {
            mispredictions++;
            branch_bits[10]++;
        }
        else if(branch_bits[10] == 2)
        {
            branch_bits[10]++;
        }
        goto L19;
    }
    cond_branches ++;
    if(branch_bits[10] == 2 || branch_bits[10] == 3)
    {
        mispredictions++;
        branch_bits[10]--;
    }
    else if(branch_bits[10] == 1)
    {
        branch_bits[10]--;
    }
    counters[71] ++;
    r0.i = 10;
    r4.i = r6.i + (40);
    printf_help("%c", r0.i, r1.i, r2.i);
    counters[72] ++;
    ldr4000(&r3.i, &L40, 0);
    tmp = r4.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r3.i);
    v = (r4.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        cond_branches ++;
        if(branch_bits[11] == 0 || branch_bits[11] == 1)
        {
            mispredictions++;
            branch_bits[11]++;
        }
        else if(branch_bits[11] == 2)
        {
            branch_bits[11]++;
        }
        goto L18;
    }
    cond_branches ++;
    if(branch_bits[11] == 2 || branch_bits[11] == 3)
    {
        mispredictions++;
        branch_bits[11]--;
    }
    else if(branch_bits[11] == 1)
    {
        branch_bits[11]--;
    }
    counters[73] ++;
    ldr4000(&lr.i, &fp.i, 84);
    ip.i = (TempState & 0xffff);
    ldr4000(&r5.i, &fp.i, 80);
    ip.i = ip.i | (((uint32_t)TempState >> 16) << 16);
    ldr4000(&r6.i, &fp.i, 104);
    lr.i = lr.i + (-2147483648);
    ldr4000(&r3.i, &fp.i, 100);
    r0.i = r5.i;
    r1.i = lr.i;
    r3.i = r3.i + (-2147483648);
    str8000(&r0.i, &r1.i, &ip.i, 0);
    str4000(&r3.i, &sp.i, 12);
    r2.i = r5.i;
    ldr8000(&r0.i, &r1.i, &fp.i, 112);
    r3.i = lr.i;
    str4000(&r6.i, &sp.i, 16);
    ldr4000(&r5.i, &fp.i, 96);
    ldr4000(&r6.i, &sp.i, 16);
    ldr4000(&r9.i, &sp.i, 12);
    str8000(&r0.i, &r1.i, &sp.i, 0);
    r8.i = r5.i;
    ldr4000(&r4.i, &fp.i, 108);
    r0.i = r6.i;
    str8000(&r8.i, &r9.i, &ip.i, 16);
    ldr4000(&r1.i, &fp.i, 88);
    r4.i = r4.i + (-2147483648);
    ldr8000(&r8.i, &r9.i, &fp.i, 8);
    ldr8000(&r6.i, &r7.i, &sp.i, 0);
    ldr4000(&lr.i, &fp.i, 92);
    str4000(&r1.i, &ip.i, 8);
    r1.i = r4.i;
    lr.i = lr.i + (-2147483648);
    str8000(&r0.i, &r1.i, &ip.i, 24);
    str8000(&r6.i, &r7.i, &ip.i, 32);
    r0.i = r8.i;
    str4000(&lr.i, &ip.i, 12);
    r1.i = r9.i;
    dmul();
    counters[74] ++;
    ldr8000(&r6.i, &r7.i, &fp.i, 32);
    ldr4000(&r2.i, &sp.i, 16);
    r3.i = r4.i;
    str8000(&r6.i, &r7.i, &sp.i, 16);
    str8000(&r0.i, &r1.i, &fp.i, 0);
    r0.i = r8.i;
    r1.i = r9.i;
    dmul();
    counters[75] ++;
    ldr8000(&r2.i, &r3.i, &sp.i, 0);
    ldr8000(&r6.i, &r7.i, &fp.i, 16);
    str8000(&r0.i, &r1.i, &fp.i, 24);
    r0.i = r8.i;
    r1.i = r9.i;
    dmul();
    counters[76] ++;
    r2.i = r5.i;
    ldr4000(&r3.i, &sp.i, 12);
    r4.i = r0.i;
    r5.i = r1.i;
    r0.i = r8.i;
    r1.i = r9.i;
    str8000(&r4.i, &r5.i, &fp.i, 32);
    dmul();
    counters[77] ++;
    r2.i = r6.i;
    r3.i = r7.i;
    dadd();
    counters[78] ++;
    r2.i = 0;
    r3.i = 0;
    str8000(&r2.i, &r3.i, &fp.i, 8);
    str8000(&r0.i, &r1.i, &fp.i, 16);
    r0.i = r4.i;
    r1.i = r5.i;
    dcmpeq();
    counters[79] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (z)
    {
        cond_branches ++;
        if(branch_bits[12] == 0 || branch_bits[12] == 1)
        {
            mispredictions++;
            branch_bits[12]++;
        }
        else if(branch_bits[12] == 2)
        {
            branch_bits[12]++;
        }
        goto L39;
    }
    cond_branches ++;
    if(branch_bits[12] == 2 || branch_bits[12] == 3)
    {
        mispredictions++;
        branch_bits[12]--;
    }
    else if(branch_bits[12] == 1)
    {
        branch_bits[12]--;
    }
L21:
    counters[80] ++;
    r1.i = (LC1 & 0xffff);
    r2.i = 3;
    r1.i = r1.i | (((uint32_t)LC1 >> 16) << 16);
    r0.i = 1;
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[81] ++;
    r5.i = (LC2 & 0xffff);
    r5.i = r5.i | (((uint32_t)LC2 >> 16) << 16);
L23:
    counters[82] ++;
    r4.i = r10.i - (40);
L24:
    counters[83] ++;
    ldr8010(&r2.i, &r3.i, &r4.i, 8);
    r1.i = r5.i;
    r0.i = 1;
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[84] ++;
    tmp = r4.i - r10.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r10.i);
    v = (r4.i&0x80000000) != (r10.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        cond_branches ++;
        if(branch_bits[13] == 0 || branch_bits[13] == 1)
        {
            mispredictions++;
            branch_bits[13]++;
        }
        else if(branch_bits[13] == 2)
        {
            branch_bits[13]++;
        }
        goto L24;
    }
    cond_branches ++;
    if(branch_bits[13] == 2 || branch_bits[13] == 3)
    {
        mispredictions++;
        branch_bits[13]--;
    }
    else if(branch_bits[13] == 1)
    {
        branch_bits[13]--;
    }
    counters[85] ++;
    r0.i = 10;
    r10.i = r10.i + (40);
    printf_help("%c", r0.i, r1.i, r2.i);
    counters[86] ++;
    ldr4000(&r3.i, &L40, 0);
    tmp = r10.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r10.i) >= ((uint32_t) r3.i);
    v = (r10.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r10.i&0x80000000);
    if (!z)
    {
        cond_branches ++;
        if(branch_bits[14] == 0 || branch_bits[14] == 1)
        {
            mispredictions++;
            branch_bits[14]++;
        }
        else if(branch_bits[14] == 2)
        {
            branch_bits[14]++;
        }
        goto L23;
    }
    cond_branches ++;
    if(branch_bits[14] == 2 || branch_bits[14] == 3)
    {
        mispredictions++;
        branch_bits[14]--;
    }
    else if(branch_bits[14] == 1)
    {
        branch_bits[14]--;
    }
    counters[87] ++;
    sp.i = sp.i + (28);
    pop(9, &pc.i, &fp.i, &r10.i, &r9.i, &r8.i, &r7.i, &r6.i, &r5.i, &r4.i);
    return;
L39:
    counters[88] ++;
    ldr8000(&r0.i, &r1.i, &sp.i, 16);
    r2.i = r4.i;
    r3.i = r5.i;
    dadd();
    counters[89] ++;
    str8000(&r0.i, &r1.i, &fp.i, 32);
    goto L21;
L38:
    counters[90] ++;
    ldr8000(&r0.i, &r1.i, &sp.i, 16);
    r2.i = r4.i;
    r3.i = r5.i;
    dadd();
    counters[91] ++;
    str8000(&r0.i, &r1.i, &fp.i, 32);
    goto L10;
    return;
}

void X1Calc()
{
    counters[92] ++;
    push(9, &r4.i, &r5.i, &r6.i, &r7.i, &r8.i, &r9.i, &r10.i, &fp.i, &lr.i);
    fp.i = (SimplexTable & 0xffff);
    fp.i = fp.i | (((uint32_t)SimplexTable >> 16) << 16);
    sp.i = sp.i - (28);
    r10.i = fp.i + (40);
    ldr8000(&r4.i, &r5.i, &fp.i, 80);
    r3.i = r5.i;
    r2.i = r4.i;
    r1.i = r5.i;
    r0.i = r4.i;
    ddiv();
    counters[93] ++;
    r3.i = r5.i;
    r2.i = r4.i;
    str8000(&r0.i, &r1.i, &fp.i, 80);
    ldr8000(&r0.i, &r1.i, &fp.i, 88);
    ddiv();
    counters[94] ++;
    r3.i = r5.i;
    r2.i = r4.i;
    str8000(&r0.i, &r1.i, &fp.i, 88);
    ldr8000(&r0.i, &r1.i, &fp.i, 96);
    ddiv();
    counters[95] ++;
    r3.i = r5.i;
    r2.i = r4.i;
    str8000(&r0.i, &r1.i, &fp.i, 96);
    ldr8000(&r0.i, &r1.i, &fp.i, 104);
    ddiv();
    counters[96] ++;
    r3.i = r5.i;
    r2.i = r4.i;
    r5.i = r10.i;
    str8000(&r0.i, &r1.i, &fp.i, 104);
    ldr8000(&r0.i, &r1.i, &fp.i, 112);
    ddiv();
    counters[97] ++;
    r2.i = 4;
    r6.i = r0.i;
    r7.i = r1.i;
    r0.i = 1;
    r1.i = (LC1 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC1 >> 16) << 16);
    str8000(&r6.i, &r7.i, &fp.i, 112);
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[98] ++;
    r6.i = (LC2 & 0xffff);
    r6.i = r6.i | (((uint32_t)LC2 >> 16) << 16);
L43:
    counters[99] ++;
    r4.i = r5.i - (40);
L44:
    counters[100] ++;
    ldr8010(&r2.i, &r3.i, &r4.i, 8);
    r1.i = r6.i;
    r0.i = 1;
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[101] ++;
    tmp = r4.i - r5.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r5.i);
    v = (r4.i&0x80000000) != (r5.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        cond_branches ++;
        if(branch_bits[15] == 0 || branch_bits[15] == 1)
        {
            mispredictions++;
            branch_bits[15]++;
        }
        else if(branch_bits[15] == 2)
        {
            branch_bits[15]++;
        }
        goto L44;
    }
    cond_branches ++;
    if(branch_bits[15] == 2 || branch_bits[15] == 3)
    {
        mispredictions++;
        branch_bits[15]--;
    }
    else if(branch_bits[15] == 1)
    {
        branch_bits[15]--;
    }
    counters[102] ++;
    r0.i = 10;
    r5.i = r4.i + (40);
    printf_help("%c", r0.i, r1.i, r2.i);
    counters[103] ++;
    ldr4000(&r3.i, &L59, 0);
    tmp = r5.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r3.i);
    v = (r5.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (!z)
    {
        cond_branches ++;
        if(branch_bits[16] == 0 || branch_bits[16] == 1)
        {
            mispredictions++;
            branch_bits[16]++;
        }
        else if(branch_bits[16] == 2)
        {
            branch_bits[16]++;
        }
        goto L43;
    }
    cond_branches ++;
    if(branch_bits[16] == 2 || branch_bits[16] == 3)
    {
        mispredictions++;
        branch_bits[16]--;
    }
    else if(branch_bits[16] == 1)
    {
        branch_bits[16]--;
    }
    counters[104] ++;
    ldr8000(&r4.i, &r5.i, &fp.i, 40);
    r6.i = (LC2 & 0xffff);
    ldr8000(&r8.i, &r9.i, &fp.i, 80);
    r6.i = r6.i | (((uint32_t)LC2 >> 16) << 16);
    r0.i = r4.i;
    r1.i = r5.i;
    r2.i = r8.i;
    r3.i = r9.i;
    ddiv();
    counters[105] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r8.i;
    r1.i = r9.i;
    r8.i = r2.i;
    r9.i = r3.i;
    dmul();
    counters[106] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r4.i;
    r1.i = r5.i;
    dsub();
    counters[107] ++;
    ldr8000(&r2.i, &r3.i, &fp.i, 88);
    str8000(&r8.i, &r9.i, &sp.i, 0);
    r4.i = r0.i;
    r5.i = r1.i;
    r0.i = r8.i;
    r1.i = r9.i;
    str8000(&r4.i, &r5.i, &fp.i, 40);
    r4.i = r10.i;
    dmul();
    counters[108] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    ldr8000(&r0.i, &r1.i, &fp.i, 48);
    dsub();
    counters[109] ++;
    ldr8000(&r2.i, &r3.i, &fp.i, 96);
    r8.i = r0.i;
    r9.i = r1.i;
    ldr8000(&r0.i, &r1.i, &sp.i, 0);
    str8000(&r8.i, &r9.i, &fp.i, 48);
    dmul();
    counters[110] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    ldr8000(&r0.i, &r1.i, &fp.i, 56);
    dsub();
    counters[111] ++;
    ldr8000(&r2.i, &r3.i, &fp.i, 104);
    r8.i = r0.i;
    r9.i = r1.i;
    ldr8000(&r0.i, &r1.i, &sp.i, 0);
    str8000(&r8.i, &r9.i, &fp.i, 56);
    dmul();
    counters[112] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    ldr8000(&r0.i, &r1.i, &fp.i, 64);
    dsub();
    counters[113] ++;
    ldr8000(&r2.i, &r3.i, &fp.i, 112);
    r8.i = r0.i;
    r9.i = r1.i;
    ldr8000(&r0.i, &r1.i, &sp.i, 0);
    str8000(&r8.i, &r9.i, &fp.i, 64);
    dmul();
    counters[114] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    ldr8000(&r0.i, &r1.i, &fp.i, 72);
    dsub();
    counters[115] ++;
    r2.i = 5;
    r8.i = r0.i;
    r9.i = r1.i;
    r0.i = 1;
    r1.i = (LC1 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC1 >> 16) << 16);
    str8000(&r8.i, &r9.i, &fp.i, 72);
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
L46:
    counters[116] ++;
    r5.i = r4.i - (40);
L47:
    counters[117] ++;
    ldr8010(&r2.i, &r3.i, &r5.i, 8);
    r1.i = r6.i;
    r0.i = 1;
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[118] ++;
    tmp = r5.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r4.i);
    v = (r5.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (!z)
    {
        cond_branches ++;
        if(branch_bits[17] == 0 || branch_bits[17] == 1)
        {
            mispredictions++;
            branch_bits[17]++;
        }
        else if(branch_bits[17] == 2)
        {
            branch_bits[17]++;
        }
        goto L47;
    }
    cond_branches ++;
    if(branch_bits[17] == 2 || branch_bits[17] == 3)
    {
        mispredictions++;
        branch_bits[17]--;
    }
    else if(branch_bits[17] == 1)
    {
        branch_bits[17]--;
    }
    counters[119] ++;
    r0.i = 10;
    r4.i = r5.i + (40);
    printf_help("%c", r0.i, r1.i, r2.i);
    counters[120] ++;
    ldr4000(&r3.i, &L59, 0);
    tmp = r4.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r3.i);
    v = (r4.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        cond_branches ++;
        if(branch_bits[18] == 0 || branch_bits[18] == 1)
        {
            mispredictions++;
            branch_bits[18]++;
        }
        else if(branch_bits[18] == 2)
        {
            branch_bits[18]++;
        }
        goto L46;
    }
    cond_branches ++;
    if(branch_bits[18] == 2 || branch_bits[18] == 3)
    {
        mispredictions++;
        branch_bits[18]--;
    }
    else if(branch_bits[18] == 1)
    {
        branch_bits[18]--;
    }
    counters[121] ++;
    ldr4000(&lr.i, &fp.i, 92);
    ip.i = (TempState & 0xffff);
    ldr4000(&r5.i, &fp.i, 88);
    ip.i = ip.i | (((uint32_t)TempState >> 16) << 16);
    ldr4000(&r6.i, &fp.i, 104);
    lr.i = lr.i + (-2147483648);
    ldr4000(&r3.i, &fp.i, 100);
    r0.i = r5.i;
    r1.i = lr.i;
    r3.i = r3.i + (-2147483648);
    str8000(&r0.i, &r1.i, &ip.i, 8);
    str4000(&r3.i, &sp.i, 12);
    r2.i = r5.i;
    ldr8000(&r0.i, &r1.i, &fp.i, 112);
    r3.i = lr.i;
    str4000(&r6.i, &sp.i, 16);
    ldr4000(&r5.i, &fp.i, 96);
    ldr4000(&r6.i, &sp.i, 16);
    ldr4000(&r9.i, &sp.i, 12);
    str8000(&r0.i, &r1.i, &sp.i, 0);
    r8.i = r5.i;
    ldr4000(&r4.i, &fp.i, 108);
    r0.i = r6.i;
    str8000(&r8.i, &r9.i, &ip.i, 16);
    ldr4000(&r1.i, &fp.i, 80);
    r4.i = r4.i + (-2147483648);
    ldr8000(&r8.i, &r9.i, &fp.i, 0);
    ldr8000(&r6.i, &r7.i, &sp.i, 0);
    ldr4000(&lr.i, &fp.i, 84);
    str4000(&r1.i, &ip.i, 0);
    r1.i = r4.i;
    lr.i = lr.i + (-2147483648);
    str8000(&r0.i, &r1.i, &ip.i, 24);
    str8000(&r6.i, &r7.i, &ip.i, 32);
    r0.i = r8.i;
    str4000(&lr.i, &ip.i, 4);
    r1.i = r9.i;
    dmul();
    counters[122] ++;
    ldr8000(&r6.i, &r7.i, &fp.i, 32);
    ldr4000(&r2.i, &sp.i, 16);
    r3.i = r4.i;
    str8000(&r6.i, &r7.i, &sp.i, 16);
    str8000(&r0.i, &r1.i, &fp.i, 8);
    r0.i = r8.i;
    r1.i = r9.i;
    dmul();
    counters[123] ++;
    ldr8000(&r2.i, &r3.i, &sp.i, 0);
    ldr8000(&r6.i, &r7.i, &fp.i, 16);
    str8000(&r0.i, &r1.i, &fp.i, 24);
    r0.i = r8.i;
    r1.i = r9.i;
    dmul();
    counters[124] ++;
    r2.i = r5.i;
    ldr4000(&r3.i, &sp.i, 12);
    r4.i = r0.i;
    r5.i = r1.i;
    r0.i = r8.i;
    r1.i = r9.i;
    str8000(&r4.i, &r5.i, &fp.i, 32);
    dmul();
    counters[125] ++;
    r2.i = r6.i;
    r3.i = r7.i;
    dadd();
    counters[126] ++;
    r2.i = 0;
    r3.i = 0;
    str8000(&r2.i, &r3.i, &fp.i, 0);
    str8000(&r0.i, &r1.i, &fp.i, 16);
    r0.i = r4.i;
    r1.i = r5.i;
    dcmpeq();
    counters[127] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        cond_branches ++;
        if(branch_bits[19] == 0 || branch_bits[19] == 1)
        {
            mispredictions++;
            branch_bits[19]++;
        }
        else if(branch_bits[19] == 2)
        {
            branch_bits[19]++;
        }
        goto L49;
    }
    cond_branches ++;
    if(branch_bits[19] == 2 || branch_bits[19] == 3)
    {
        mispredictions++;
        branch_bits[19]--;
    }
    else if(branch_bits[19] == 1)
    {
        branch_bits[19]--;
    }
    counters[128] ++;
    ldr8000(&r0.i, &r1.i, &sp.i, 16);
    r2.i = r4.i;
    r3.i = r5.i;
    dadd();
    counters[129] ++;
    str8000(&r0.i, &r1.i, &fp.i, 32);
L49:
    counters[130] ++;
    r1.i = (LC1 & 0xffff);
    r2.i = 6;
    r1.i = r1.i | (((uint32_t)LC1 >> 16) << 16);
    r0.i = 1;
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[131] ++;
    r5.i = (LC2 & 0xffff);
    r5.i = r5.i | (((uint32_t)LC2 >> 16) << 16);
L51:
    counters[132] ++;
    r4.i = r10.i - (40);
L52:
    counters[133] ++;
    ldr8010(&r2.i, &r3.i, &r4.i, 8);
    r1.i = r5.i;
    r0.i = 1;
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[134] ++;
    tmp = r10.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r10.i) >= ((uint32_t) r4.i);
    v = (r10.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r10.i&0x80000000);
    if (!z)
    {
        cond_branches ++;
        if(branch_bits[20] == 0 || branch_bits[20] == 1)
        {
            mispredictions++;
            branch_bits[20]++;
        }
        else if(branch_bits[20] == 2)
        {
            branch_bits[20]++;
        }
        goto L52;
    }
    cond_branches ++;
    if(branch_bits[20] == 2 || branch_bits[20] == 3)
    {
        mispredictions++;
        branch_bits[20]--;
    }
    else if(branch_bits[20] == 1)
    {
        branch_bits[20]--;
    }
    counters[135] ++;
    r0.i = 10;
    r10.i = r10.i + (40);
    printf_help("%c", r0.i, r1.i, r2.i);
    counters[136] ++;
    ldr4000(&r3.i, &L59, 0);
    tmp = r10.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r10.i) >= ((uint32_t) r3.i);
    v = (r10.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r10.i&0x80000000);
    if (!z)
    {
        cond_branches ++;
        if(branch_bits[21] == 0 || branch_bits[21] == 1)
        {
            mispredictions++;
            branch_bits[21]++;
        }
        else if(branch_bits[21] == 2)
        {
            branch_bits[21]++;
        }
        goto L51;
    }
    cond_branches ++;
    if(branch_bits[21] == 2 || branch_bits[21] == 3)
    {
        mispredictions++;
        branch_bits[21]--;
    }
    else if(branch_bits[21] == 1)
    {
        branch_bits[21]--;
    }
    counters[137] ++;
    sp.i = sp.i + (28);
    pop(9, &pc.i, &fp.i, &r10.i, &r9.i, &r8.i, &r7.i, &r6.i, &r5.i, &r4.i);
    return;

}

void Result()
{
    counters[138] ++;
    push(7, &r4.i, &r5.i, &r6.i, &r7.i, &r8.i, &r9.i, &lr.i);
    r5.i = (SimplexTable & 0xffff);
    r5.i = r5.i | (((uint32_t)SimplexTable >> 16) << 16);
    sp.i = sp.i - (28);
    r2.i = 0;
    r3.i = 0;
    ldr8000(&r0.i, &r1.i, &r5.i, 40);
    r3.i = r3.i | (16368 << 16);
    dcmpeq();
    counters[139] ++;
    ldr8000(&r6.i, &r7.i, &r5.i, 72);
    r4.i = r0.i - (0);
    z = r4.i == 0;
    n = r4.i & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (r4.i&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        r4.i = 1;
    }
    if (!z)
    {
        str8000(&r6.i, &r7.i, &sp.i, 0);
    }
L62:
    counters[140] ++;
    ldr8000(&r0.i, &r1.i, &r5.i, 48);
    r2.i = 0;
    r3.i = 0;
    r3.i = r3.i | (16368 << 16);
    dcmpeq();
    counters[141] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        r3.i = sp.i + (24);
    }
    if (!z)
    {
        r3.i = r3.i + (((uint32_t)r4.i << 3));
    }
    if (!z)
    {
        r4.i = r4.i + (1);
    }
    if (!z)
    {
        str8000(&r6.i, &r7.i, &r3.i, -24);
    }
L64:
    counters[142] ++;
    ldr8000(&r0.i, &r1.i, &r5.i, 56);
    r2.i = 0;
    r3.i = 0;
    r3.i = r3.i | (16368 << 16);
    dcmpeq();
    counters[143] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        r3.i = sp.i + (24);
    }
    if (!z)
    {
        r3.i = r3.i + (((uint32_t)r4.i << 3));
    }
    if (!z)
    {
        r4.i = r4.i + (1);
    }
    if (!z)
    {
        str8000(&r6.i, &r7.i, &r3.i, -24);
    }
L66:
    counters[144] ++;
    ldr8000(&r0.i, &r1.i, &r5.i, 64);
    r2.i = 0;
    r3.i = 0;
    r3.i = r3.i | (16368 << 16);
    dcmpeq();
    counters[145] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        r3.i = sp.i + (24);
    }
    if (!z)
    {
        r3.i = r3.i + (((uint32_t)r4.i << 3));
    }
    if (!z)
    {
        r4.i = r4.i + (1);
    }
    if (!z)
    {
        str8000(&r6.i, &r7.i, &r3.i, -24);
    }
L68:
    counters[146] ++;
    r9.i = 0;
    r9.i = r9.i | (16368 << 16);
    r8.i = 0;
    r0.i = r6.i;
    r1.i = r7.i;
    r2.i = r8.i;
    r3.i = r9.i;
    dcmpeq();
    counters[147] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        cond_branches ++;
        if(branch_bits[22] == 0 || branch_bits[22] == 1)
        {
            mispredictions++;
            branch_bits[22]++;
        }
        else if(branch_bits[22] == 2)
        {
            branch_bits[22]++;
        }
        goto L95;
    }
    cond_branches ++;
    if(branch_bits[22] == 2 || branch_bits[22] == 3)
    {
        mispredictions++;
        branch_bits[22]--;
    }
    else if(branch_bits[22] == 1)
    {
        branch_bits[22]--;
    }
L70:
    counters[148] ++;
    ldr8000(&r0.i, &r1.i, &r5.i, 80);
    r2.i = 0;
    r3.i = 0;
    r3.i = r3.i | (16368 << 16);
    dcmpeq();
    counters[149] ++;
    ldr8000(&r6.i, &r7.i, &r5.i, 112);
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        r3.i = sp.i + (24);
    }
    if (!z)
    {
        r3.i = r3.i + (((uint32_t)r4.i << 3));
    }
    if (!z)
    {
        r4.i = r4.i + (1);
    }
    if (!z)
    {
        str8000(&r6.i, &r7.i, &r3.i, -24);
    }
L72:
    counters[150] ++;
    ldr8000(&r0.i, &r1.i, &r5.i, 88);
    r2.i = 0;
    r3.i = 0;
    r3.i = r3.i | (16368 << 16);
    dcmpeq();
    counters[151] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        r3.i = sp.i + (24);
    }
    if (!z)
    {
        r3.i = r3.i + (((uint32_t)r4.i << 3));
    }
    if (!z)
    {
        r4.i = r4.i + (1);
    }
    if (!z)
    {
        str8000(&r6.i, &r7.i, &r3.i, -24);
    }
L74:
    counters[152] ++;
    ldr8000(&r0.i, &r1.i, &r5.i, 96);
    r2.i = 0;
    r3.i = 0;
    r3.i = r3.i | (16368 << 16);
    dcmpeq();
    counters[153] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        r3.i = sp.i + (24);
    }
    if (!z)
    {
        r3.i = r3.i + (((uint32_t)r4.i << 3));
    }
    if (!z)
    {
        r4.i = r4.i + (1);
    }
    if (!z)
    {
        str8000(&r6.i, &r7.i, &r3.i, -24);
    }
L76:
    counters[154] ++;
    ldr8000(&r0.i, &r1.i, &r5.i, 104);
    r2.i = 0;
    r3.i = 0;
    r3.i = r3.i | (16368 << 16);
    dcmpeq();
    counters[155] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        r3.i = sp.i + (24);
    }
    if (!z)
    {
        r3.i = r3.i + (((uint32_t)r4.i << 3));
    }
    if (!z)
    {
        r4.i = r4.i + (1);
    }
    if (!z)
    {
        str8000(&r6.i, &r7.i, &r3.i, -24);
    }
L78:
    counters[156] ++;
    r9.i = 0;
    r9.i = r9.i | (16368 << 16);
    r8.i = 0;
    r0.i = r6.i;
    r1.i = r7.i;
    r2.i = r8.i;
    r3.i = r9.i;
    dcmpeq();
    counters[157] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        r3.i = sp.i + (24);
    }
    if (!z)
    {
        r3.i = r3.i + (((uint32_t)r4.i << 3));
    }
    if (!z)
    {
        r4.i = r4.i + (1);
    }
    if (!z)
    {
        str8000(&r8.i, &r9.i, &r3.i, -24);
    }
L80:
    counters[158] ++;
    ldr8000(&r2.i, &r3.i, &r5.i, 32);
    r1.i = sp.i + (24);
    r4.i = r1.i + (((uint32_t)r4.i << 3));
    r0.i = (LC3 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC3 >> 16) << 16);
    str8000(&r2.i, &r3.i, &r4.i, -24);
    printf_help("%s\n", r0.i, r1.i, r2.i);
    counters[159] ++;
    ldr8000(&r2.i, &r3.i, &sp.i, 0);
    r1.i = (LC4 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC4 >> 16) << 16);
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[160] ++;
    ldr8000(&r2.i, &r3.i, &sp.i, 8);
    r1.i = (LC5 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC5 >> 16) << 16);
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[161] ++;
    ldr8000(&r2.i, &r3.i, &sp.i, 16);
    r1.i = (LC6 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC6 >> 16) << 16);
    sp.i = sp.i + (28);
    pop(7, &lr.i, &r9.i, &r8.i, &r7.i, &r6.i, &r5.i, &r4.i);
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    return;
L95:
    counters[162] ++;
    r3.i = sp.i + (24);
    r3.i = r3.i + (((uint32_t)r4.i << 3));
    r4.i = r4.i + (1);
    str8000(&r8.i, &r9.i, &r3.i, -24);
    goto L70;
    return;
}

void Maxim()
{
    counters[163] ++;
    push(8, &r4.i, &r5.i, &r6.i, &r7.i, &r8.i, &r9.i, &r10.i, &lr.i);
    r4.i = (SimplexTable & 0xffff);
    r4.i = r4.i | (((uint32_t)SimplexTable >> 16) << 16);
    sp.i = sp.i - (16);
    r10.i = (uint32_t)r1.i << 3;
    tmp = r0.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 1);
    v = (r0.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    ldr8000(&r2.i, &r3.i, &r4.i, 32);
    r5.i = (TempState & 0xffff);
    ldr8000(&r6.i, &r7.i, &r4.i, r10.i);
    r5.i = r5.i | (((uint32_t)TempState >> 16) << 16);
    str8000(&r2.i, &r3.i, &sp.i, 0);
    if (z)
    {
        cond_branches ++;
        if(branch_bits[23] == 0 || branch_bits[23] == 1)
        {
            mispredictions++;
            branch_bits[23]++;
        }
        else if(branch_bits[23] == 2)
        {
            branch_bits[23]++;
        }
        goto L103;
    }
    cond_branches ++;
    if(branch_bits[23] == 2 || branch_bits[23] == 3)
    {
        mispredictions++;
        branch_bits[23]--;
    }
    else if(branch_bits[23] == 1)
    {
        branch_bits[23]--;
    }
    counters[164] ++;
    r2.i = r6.i;
    r3.i = r7.i;
    ldr8000(&r0.i, &r1.i, &r5.i, 0);
    dmul();
    counters[165] ++;
    r2.i = r6.i;
    r3.i = r7.i;
    str8000(&r0.i, &r1.i, &r4.i, 0);
    ldr8000(&r0.i, &r1.i, &r5.i, 8);
    dmul();
    counters[166] ++;
    ldr8000(&r2.i, &r3.i, &r5.i, 16);
    r8.i = r0.i;
    r9.i = r1.i;
    r0.i = r6.i;
    str8000(&r8.i, &r9.i, &r4.i, 8);
    r1.i = r7.i;
    dmul();
    counters[167] ++;
    r2.i = r6.i;
    r3.i = r7.i;
    r8.i = r0.i;
    r9.i = r1.i;
    ldr8000(&r0.i, &r1.i, &r5.i, 24);
    dmul();
    counters[168] ++;
    ldr8000(&r2.i, &r3.i, &r4.i, 16);
    str8000(&r2.i, &r3.i, &sp.i, 8);
    r2.i = r6.i;
    r3.i = r7.i;
    str8000(&r0.i, &r1.i, &r4.i, 24);
    ldr8000(&r0.i, &r1.i, &r5.i, 32);
    dmul();
    counters[169] ++;
    r2.i = r8.i;
    r3.i = r9.i;
    str8000(&r0.i, &r1.i, &r4.i, 32);
    ldr8000(&r0.i, &r1.i, &sp.i, 8);
    dadd();
    counters[170] ++;
    r2.i = 0;
    r3.i = 0;
    str8000(&r0.i, &r1.i, &r4.i, 16);
    str8000(&r2.i, &r3.i, &r4.i, r10.i);
L98:
    counters[171] ++;
    ldr8000(&r6.i, &r7.i, &r4.i, 32);
    r2.i = 0;
    r3.i = 0;
    r0.i = r6.i;
    r1.i = r7.i;
    dcmpeq();
    counters[172] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        cond_branches ++;
        if(branch_bits[24] == 0 || branch_bits[24] == 1)
        {
            mispredictions++;
            branch_bits[24]++;
        }
        else if(branch_bits[24] == 2)
        {
            branch_bits[24]++;
        }
        goto L96;
    }
    cond_branches ++;
    if(branch_bits[24] == 2 || branch_bits[24] == 3)
    {
        mispredictions++;
        branch_bits[24]--;
    }
    else if(branch_bits[24] == 1)
    {
        branch_bits[24]--;
    }
    counters[173] ++;
    ldr8000(&r2.i, &r3.i, &sp.i, 0);
    r0.i = r6.i;
    r1.i = r7.i;
    dadd();
    counters[174] ++;
    str8000(&r0.i, &r1.i, &r4.i, 32);
L96:
    counters[175] ++;
    sp.i = sp.i + (16);
    pop(8, &pc.i, &r10.i, &r9.i, &r8.i, &r7.i, &r6.i, &r5.i, &r4.i);
    return;
L103:
    counters[176] ++;
    ldr8000(&r2.i, &r3.i, &r5.i, 0);
    r0.i = r6.i;
    r1.i = r7.i;
    dmul();
    counters[177] ++;
    r2.i = r6.i;
    r3.i = r7.i;
    r8.i = r0.i;
    r9.i = r1.i;
    ldr8000(&r0.i, &r1.i, &r5.i, 8);
    dmul();
    counters[178] ++;
    r2.i = r6.i;
    r3.i = r7.i;
    str8000(&r0.i, &r1.i, &r4.i, 8);
    ldr8000(&r0.i, &r1.i, &r5.i, 16);
    dmul();
    counters[179] ++;
    r2.i = r6.i;
    r3.i = r7.i;
    str8000(&r0.i, &r1.i, &r4.i, 16);
    ldr8000(&r0.i, &r1.i, &r5.i, 24);
    dmul();
    counters[180] ++;
    ldr8000(&r2.i, &r3.i, &r4.i, 0);
    str8000(&r2.i, &r3.i, &sp.i, 8);
    r2.i = r6.i;
    r3.i = r7.i;
    str8000(&r0.i, &r1.i, &r4.i, 24);
    ldr8000(&r0.i, &r1.i, &r5.i, 32);
    dmul();
    counters[181] ++;
    r2.i = r8.i;
    r3.i = r9.i;
    str8000(&r0.i, &r1.i, &r4.i, 32);
    ldr8000(&r0.i, &r1.i, &sp.i, 8);
    dadd();
    counters[182] ++;
    r2.i = 0;
    r3.i = 0;
    str8000(&r0.i, &r1.i, &r4.i, 0);
    str8000(&r2.i, &r3.i, &r4.i, r10.i);
    goto L98;
    return;
}

void GaussCalc()
{
    counters[183] ++;
    push(8, &r4.i, &r5.i, &r6.i, &r7.i, &r8.i, &r9.i, &r10.i, &lr.i);
    r4.i = (SimplexTable & 0xffff);
    r4.i = r4.i | (((uint32_t)SimplexTable >> 16) << 16);
    tmp = r0.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 1);
    v = (r0.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    r2.i = r4.i + (((uint32_t)r1.i << 3));
    ldr8000(&r6.i, &r7.i, &r2.i, 40);
    if (z)
    {
        cond_branches ++;
        if(branch_bits[25] == 0 || branch_bits[25] == 1)
        {
            mispredictions++;
            branch_bits[25]++;
        }
        else if(branch_bits[25] == 2)
        {
            branch_bits[25]++;
        }
        goto L108;
    }
    cond_branches ++;
    if(branch_bits[25] == 2 || branch_bits[25] == 3)
    {
        mispredictions++;
        branch_bits[25]--;
    }
    else if(branch_bits[25] == 1)
    {
        branch_bits[25]--;
    }
    counters[184] ++;
    ip.i = r0.i + (((uint32_t)r0.i << 2));
    r3.i = r1.i;
    r3.i = ip.i + (r3.i);
    r5.i = r0.i;
    r1.i = r7.i;
    r0.i = r6.i;
    r3.i = (uint32_t)r3.i << 3;
    ldr8000(&r2.i, &r3.i, &r3.i, r4.i);
    ddiv();
    counters[185] ++;
    r3.i = 40;
    r5.i = (r3.i) * (r5.i);
    r8.i = r4.i + (r5.i);
    ldr8000(&r2.i, &r3.i, &r4.i, r5.i);
    r6.i = r0.i;
    r7.i = r1.i;
    dmul();
    counters[186] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    ldr8000(&r0.i, &r1.i, &r4.i, 40);
    dsub();
    counters[187] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r6.i;
    str8000(&r2.i, &r3.i, &r4.i, 40);
    r1.i = r7.i;
    ldr8000(&r2.i, &r3.i, &r8.i, 8);
    dmul();
    counters[188] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    ldr8000(&r0.i, &r1.i, &r4.i, 48);
    dsub();
    counters[189] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r6.i;
    str8000(&r2.i, &r3.i, &r4.i, 48);
    r1.i = r7.i;
    ldr8000(&r2.i, &r3.i, &r8.i, 16);
    dmul();
    counters[190] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    ldr8000(&r0.i, &r1.i, &r4.i, 56);
    dsub();
    counters[191] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r6.i;
    str8000(&r2.i, &r3.i, &r4.i, 56);
    r1.i = r7.i;
    ldr8000(&r2.i, &r3.i, &r8.i, 24);
    dmul();
    counters[192] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    ldr8000(&r0.i, &r1.i, &r4.i, 64);
    dsub();
    counters[193] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r6.i;
    str8000(&r2.i, &r3.i, &r4.i, 64);
    r1.i = r7.i;
    ldr8000(&r2.i, &r3.i, &r8.i, 32);
    dmul();
    counters[194] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    ldr8000(&r0.i, &r1.i, &r4.i, 72);
    dsub();
    counters[195] ++;
    str8000(&r0.i, &r1.i, &r4.i, 72);
    pop(8, &pc.i, &r10.i, &r9.i, &r8.i, &r7.i, &r6.i, &r5.i, &r4.i);
    return;
L108:
    counters[196] ++;
    r1.i = r2.i;
    r3.i = r7.i;
    ldr8000(&r0.i, &r1.i, &r1.i, 80);
    r2.i = r6.i;
    ddiv();
    counters[197] ++;
    ldr8000(&r2.i, &r3.i, &r4.i, 40);
    r6.i = r0.i;
    r7.i = r1.i;
    dmul();
    counters[198] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    ldr8000(&r0.i, &r1.i, &r4.i, 80);
    dsub();
    counters[199] ++;
    ldr8000(&r2.i, &r3.i, &r4.i, 48);
    r8.i = r0.i;
    r9.i = r1.i;
    r0.i = r6.i;
    str8000(&r8.i, &r9.i, &r4.i, 80);
    r1.i = r7.i;
    dmul();
    counters[200] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    ldr8000(&r0.i, &r1.i, &r4.i, 88);
    dsub();
    counters[201] ++;
    ldr8000(&r2.i, &r3.i, &r4.i, 56);
    r8.i = r0.i;
    r9.i = r1.i;
    r0.i = r6.i;
    str8000(&r8.i, &r9.i, &r4.i, 88);
    r1.i = r7.i;
    dmul();
    counters[202] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    ldr8000(&r0.i, &r1.i, &r4.i, 96);
    dsub();
    counters[203] ++;
    ldr8000(&r2.i, &r3.i, &r4.i, 64);
    r8.i = r0.i;
    r9.i = r1.i;
    r0.i = r6.i;
    str8000(&r8.i, &r9.i, &r4.i, 96);
    r1.i = r7.i;
    dmul();
    counters[204] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    ldr8000(&r0.i, &r1.i, &r4.i, 104);
    dsub();
    counters[205] ++;
    ldr8000(&r2.i, &r3.i, &r4.i, 72);
    r8.i = r0.i;
    r9.i = r1.i;
    r0.i = r6.i;
    r1.i = r7.i;
    str8000(&r8.i, &r9.i, &r4.i, 104);
    dmul();
    counters[206] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    ldr8000(&r0.i, &r1.i, &r4.i, 112);
    dsub();
    counters[207] ++;
    str8000(&r0.i, &r1.i, &r4.i, 112);
    pop(8, &pc.i, &r10.i, &r9.i, &r8.i, &r7.i, &r6.i, &r5.i, &r4.i);
    return;

}

void Exchange()
{
    counters[208] ++;
    tmp = r0.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 1);
    v = (r0.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    r2.i = (SimplexTable & 0xffff);
    r3.i = (TempState & 0xffff);
    r2.i = r2.i | (((uint32_t)SimplexTable >> 16) << 16);
    r3.i = r3.i | (((uint32_t)TempState >> 16) << 16);
    push(3, &r4.i, &r5.i, &lr.i);
    if (z)
    {
        cond_branches ++;
        if(branch_bits[26] == 0 || branch_bits[26] == 1)
        {
            mispredictions++;
            branch_bits[26]++;
        }
        else if(branch_bits[26] == 2)
        {
            branch_bits[26]++;
        }
        goto L114;
    }
    cond_branches ++;
    if(branch_bits[26] == 2 || branch_bits[26] == 3)
    {
        mispredictions++;
        branch_bits[26]--;
    }
    else if(branch_bits[26] == 1)
    {
        branch_bits[26]--;
    }
    counters[209] ++;
    ldr4000(&r0.i, &r2.i, 88);
    ldr4000(&r4.i, &r2.i, 80);
    ldr4000(&r1.i, &r2.i, 84);
    str4000(&r0.i, &r3.i, 8);
    ldr4000(&r0.i, &r2.i, 92);
    r1.i = r1.i + (-2147483648);
    ldr4000(&lr.i, &r2.i, 96);
    ldr4000(&ip.i, &r2.i, 104);
    r0.i = r0.i + (-2147483648);
    str4000(&r4.i, &r3.i, 0);
    str4000(&r1.i, &r3.i, 4);
    ldr8000(&r4.i, &r5.i, &r2.i, 112);
    ldr4000(&r1.i, &r2.i, 100);
    ldr4000(&r2.i, &r2.i, 108);
    str4000(&lr.i, &r3.i, 16);
    str4000(&ip.i, &r3.i, 24);
L113:
    counters[210] ++;
    r1.i = r1.i + (-2147483648);
    r2.i = r2.i + (-2147483648);
    str4000(&r0.i, &r3.i, 12);
    str4000(&r1.i, &r3.i, 20);
    str4000(&r2.i, &r3.i, 28);
    str8000(&r4.i, &r5.i, &r3.i, 32);
    pop(3, &pc.i, &r5.i, &r4.i);
    return;
L114:
    counters[211] ++;
    ldr4000(&r0.i, &r2.i, 48);
    ldr4000(&r4.i, &r2.i, 40);
    ldr4000(&lr.i, &r2.i, 56);
    ldr4000(&ip.i, &r2.i, 64);
    ldr4000(&r1.i, &r2.i, 44);
    str4000(&r0.i, &r3.i, 8);
    ldr4000(&r0.i, &r2.i, 52);
    r1.i = r1.i + (-2147483648);
    str4000(&r4.i, &r3.i, 0);
    str4000(&r1.i, &r3.i, 4);
    r0.i = r0.i + (-2147483648);
    ldr8000(&r4.i, &r5.i, &r2.i, 72);
    ldr4000(&r1.i, &r2.i, 60);
    str4000(&lr.i, &r3.i, 16);
    ldr4000(&r2.i, &r2.i, 68);
    str4000(&ip.i, &r3.i, 24);
    goto L113;
    return;
}

void ShowTable()
{
    counters[212] ++;
    push(6, &r4.i, &r5.i, &r6.i, &r7.i, &r8.i, &lr.i);
    r2.i = r0.i;
    r1.i = (LC1 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC1 >> 16) << 16);
    ldr4000(&r5.i, &L121, 0);
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[213] ++;
    r6.i = (LC2 & 0xffff);
    r7.i = r5.i + (120);
    r6.i = r6.i | (((uint32_t)LC2 >> 16) << 16);
L116:
    counters[214] ++;
    r4.i = r5.i - (40);
L117:
    counters[215] ++;
    ldr8010(&r2.i, &r3.i, &r4.i, 8);
    r1.i = r6.i;
    r0.i = 1;
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[216] ++;
    tmp = r4.i - r5.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r5.i);
    v = (r4.i&0x80000000) != (r5.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        cond_branches ++;
        if(branch_bits[27] == 0 || branch_bits[27] == 1)
        {
            mispredictions++;
            branch_bits[27]++;
        }
        else if(branch_bits[27] == 2)
        {
            branch_bits[27]++;
        }
        goto L117;
    }
    cond_branches ++;
    if(branch_bits[27] == 2 || branch_bits[27] == 3)
    {
        mispredictions++;
        branch_bits[27]--;
    }
    else if(branch_bits[27] == 1)
    {
        branch_bits[27]--;
    }
    counters[217] ++;
    r5.i = r4.i + (40);
    r0.i = 10;
    printf_help("%c", r0.i, r1.i, r2.i);
    counters[218] ++;
    tmp = r5.i - r7.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r7.i);
    v = (r5.i&0x80000000) != (r7.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (!z)
    {
        cond_branches ++;
        if(branch_bits[28] == 0 || branch_bits[28] == 1)
        {
            mispredictions++;
            branch_bits[28]++;
        }
        else if(branch_bits[28] == 2)
        {
            branch_bits[28]++;
        }
        goto L116;
    }
    cond_branches ++;
    if(branch_bits[28] == 2 || branch_bits[28] == 3)
    {
        mispredictions++;
        branch_bits[28]--;
    }
    else if(branch_bits[28] == 1)
    {
        branch_bits[28]--;
    }
    counters[219] ++;
    pop(6, &pc.i, &r8.i, &r7.i, &r6.i, &r5.i, &r4.i);
    return;

}

void Input()
{
    counters[220] ++;
    push(7, &r4.i, &r5.i, &r6.i, &r7.i, &r8.i, &r9.i, &lr.i);
    sp.i = sp.i - (124);
    r2.i = 120;
    r1.i = (LC0 & 0xffff);
    r0.i = sp.i;
    r1.i = r1.i | (((uint32_t)LC0 >> 16) << 16);
    memcpy_help();
    counters[221] ++;
    ldr8000(&r4.i, &r5.i, &sp.i, 16);
    ip.i = (SimplexTable & 0xffff);
    ip.i = ip.i | (((uint32_t)SimplexTable >> 16) << 16);
    ldr8000(&r6.i, &r7.i, &sp.i, 24);
    r8.i = ip.i + (40);
    str8000(&r4.i, &r5.i, &ip.i, 16);
    r9.i = ip.i + (160);
    ldr8000(&r4.i, &r5.i, &sp.i, 32);
    str8000(&r6.i, &r7.i, &ip.i, 24);
    ldr8000(&r6.i, &r7.i, &sp.i, 48);
    str8000(&r4.i, &r5.i, &ip.i, 32);
    ldr8000(&r4.i, &r5.i, &sp.i, 40);
    str8000(&r6.i, &r7.i, &ip.i, 48);
    ldr8000(&r6.i, &r7.i, &sp.i, 64);
    str8000(&r4.i, &r5.i, &ip.i, 40);
    ldr8000(&r4.i, &r5.i, &sp.i, 56);
    str8000(&r6.i, &r7.i, &ip.i, 64);
    ldr8000(&r6.i, &r7.i, &sp.i, 80);
    str8000(&r4.i, &r5.i, &ip.i, 56);
    ldr8000(&r4.i, &r5.i, &sp.i, 72);
    str8000(&r6.i, &r7.i, &ip.i, 80);
    ldr8000(&r6.i, &r7.i, &sp.i, 96);
    str8000(&r4.i, &r5.i, &ip.i, 72);
    ldr8000(&r4.i, &r5.i, &sp.i, 88);
    ldr8000(&r0.i, &r1.i, &sp.i, 0);
    ldr8000(&r2.i, &r3.i, &sp.i, 8);
    str8000(&r4.i, &r5.i, &ip.i, 88);
    str8000(&r6.i, &r7.i, &ip.i, 96);
    ldr8000(&r4.i, &r5.i, &sp.i, 104);
    ldr8000(&r6.i, &r7.i, &sp.i, 112);
    str8000(&r0.i, &r1.i, &ip.i, 0);
    r1.i = (LC1 & 0xffff);
    str8000(&r2.i, &r3.i, &ip.i, 8);
    r1.i = r1.i | (((uint32_t)LC1 >> 16) << 16);
    r2.i = 0;
    r0.i = 1;
    str8000(&r4.i, &r5.i, &ip.i, 104);
    r5.i = (LC2 & 0xffff);
    str8000(&r6.i, &r7.i, &ip.i, 112);
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[222] ++;
    r5.i = r5.i | (((uint32_t)LC2 >> 16) << 16);
L124:
    counters[223] ++;
    r4.i = r8.i - (40);
L125:
    counters[224] ++;
    ldr8010(&r2.i, &r3.i, &r4.i, 8);
    r1.i = r5.i;
    r0.i = 1;
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[225] ++;
    tmp = r4.i - r8.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r8.i);
    v = (r4.i&0x80000000) != (r8.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        cond_branches ++;
        if(branch_bits[29] == 0 || branch_bits[29] == 1)
        {
            mispredictions++;
            branch_bits[29]++;
        }
        else if(branch_bits[29] == 2)
        {
            branch_bits[29]++;
        }
        goto L125;
    }
    cond_branches ++;
    if(branch_bits[29] == 2 || branch_bits[29] == 3)
    {
        mispredictions++;
        branch_bits[29]--;
    }
    else if(branch_bits[29] == 1)
    {
        branch_bits[29]--;
    }
    counters[226] ++;
    r8.i = r4.i + (40);
    r0.i = 10;
    printf_help("%c", r0.i, r1.i, r2.i);
    counters[227] ++;
    tmp = r8.i - r9.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) r9.i);
    v = (r8.i&0x80000000) != (r9.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    if (!z)
    {
        cond_branches ++;
        if(branch_bits[30] == 0 || branch_bits[30] == 1)
        {
            mispredictions++;
            branch_bits[30]++;
        }
        else if(branch_bits[30] == 2)
        {
            branch_bits[30]++;
        }
        goto L124;
    }
    cond_branches ++;
    if(branch_bits[30] == 2 || branch_bits[30] == 3)
    {
        mispredictions++;
        branch_bits[30]--;
    }
    else if(branch_bits[30] == 1)
    {
        branch_bits[30]--;
    }
    counters[228] ++;
    sp.i = sp.i + (124);
    pop(7, &pc.i, &r9.i, &r8.i, &r7.i, &r6.i, &r5.i, &r4.i);
    return;

}

void main()
{
    malloc_start();
    counters[229] ++;
    push(2, &r4.i, &lr.i);
    Input();
    counters[230] ++;
    X2Calc();
    counters[231] ++;
    X1Calc();
    counters[232] ++;
    Result();
    counters[233] ++;
    r0.i = 0;
    pop(2, &pc.i, &r4.i);
    counter_summary();
    return;

}