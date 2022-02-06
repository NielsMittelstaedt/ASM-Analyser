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

int32_t LC0;

int load_counter = 0, store_counter = 0;
int counters[11] = { 0 };
int block_sizes[11] = {10,1,2,5,5,6,8,1,3,6,2};

int cond_branches = 0, mispredictions = 0;
uint8_t branch_bits[2] = {0};

void dadd()
{
    uint64_t op1 = ((uint64_t)(uint32_t) r1.i) << 32 | ((uint64_t)(uint32_t) r0.i);
    uint64_t op2 = ((uint64_t)(uint32_t) r3.i) << 32 | ((uint64_t)(uint32_t) r2.i);
    double result = *(double *)&op1 + *(double *)&op2;
    uint64_t result_uint64 = *(uint64_t *)&result;
    r1.i = (uint32_t) (result_uint64 >> 32);
    r0.i = (uint32_t) result_uint64;
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
    malloc_0 = (uint8_t*) malloc(20009);
    sp.i = 19996;
    fp = sp;
    LC0 = 20000;
    strcpy(malloc_0+LC0, "%lf\000");

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

void main();

void main()
{
    malloc_start();
    counters[0] ++;
    push(10, &r3.i, &r4.i, &r5.i, &r6.i, &r7.i, &r8.i, &r9.i, &r10.i, &fp.i, &lr.i);
    fp.i = 33920;
    r5.i = 0;
    fp.i = fp.i | (30 << 16);
    r5.i = r5.i | (16368 << 16);
    r6.i = 0;
    r7.i = 0;
    r4.i = 0;
    r10.i = 1;
    goto L4;
L9:
    counters[1] ++;
    dadd();
    counters[2] ++;
    r6.i = r0.i;
    r7.i = r1.i;
L3:
    counters[3] ++;
    r0.i = r4.i;
    r1.i = r5.i;
    r2.i = 0;
    r3.i = 1073741824;
    dadd();
    counters[4] ++;
    r10.i = r10.i + (1);
    tmp = r10.i - fp.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r10.i) >= ((uint32_t) fp.i);
    v = (r10.i&0x80000000) != (fp.i&0x80000000) && (tmp&0x80000000) != (r10.i&0x80000000);
    r4.i = r0.i;
    r5.i = r1.i;
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
        goto L8;
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
L4:
    counters[5] ++;
    r2.i = r4.i;
    r3.i = r5.i;
    r0.i = 0;
    r1.i = 0;
    r1.i = r1.i | (16400 << 16);
    ddiv();
    counters[6] ++;
    tmp = r10.i & 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    r8.i = r0.i;
    r9.i = r1.i;
    r0.i = r6.i;
    r1.i = r7.i;
    r2.i = r8.i;
    r3.i = r9.i;
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
        goto L9;
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
    counters[7] ++;
    dsub();
    counters[8] ++;
    r6.i = r0.i;
    r7.i = r1.i;
    goto L3;
L8:
    counters[9] ++;
    r2.i = r6.i;
    r3.i = r7.i;
    r1.i = (LC0 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC0 >> 16) << 16);
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[10] ++;
    r0.i = 0;
    pop(10, &pc.i, &fp.i, &r10.i, &r9.i, &r8.i, &r7.i, &r6.i, &r5.i, &r4.i, &r3.i);
    counter_summary();
    return;

}