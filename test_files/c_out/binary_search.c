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

reg r0, r4, r1, r2, r3;

int32_t LC1, LC0;

int load_counter = 0, store_counter = 0;
int counters[13] = { 0 };
int block_sizes[13] = {11,18,2,8,6,2,6,2,1,3,21,5,4};

uint8_t branch_bits[3] = {0};
int cond_branches[3] = {0};
int mispredictions[3] = {0};

void stm1(int32_t *address, int num, ...)
{
    va_list args;
    va_start(args, num);
    for (int i=0; i < num; i++)
    {
        int32_t *cur_arg = va_arg(args, int32_t *);
        *((uint32_t*) (malloc_0 + *address)) = *cur_arg;
        *address += 4;
        store_counter ++;
    }
    va_end(args);
}
void ldr4000(int32_t *target, int32_t *address, int32_t offset)
{
    *target = *((uint32_t*)(malloc_0+*address+offset));
    load_counter ++;
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
void ldm1(int32_t *address, int num, ...)
{
    va_list args;
    va_start(args, num);
    for (int i=0; i < num; i++)
    {
        int32_t *cur_arg = va_arg(args, int32_t *);
        *cur_arg = *((uint32_t*) (malloc_0 + *address));
        *address += 4;
        load_counter ++;
    }
    va_end(args);
}
void str4000(int32_t *target, int32_t *address, int32_t offset)
{
    *((uint32_t*)(malloc_0+*address+offset)) = *target;
    store_counter ++;
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
    malloc_0 = (uint8_t*) malloc(20040);
    sp.i = 19996;
    fp = sp;
    LC1 = 20000;
    strcpy(malloc_0+LC1, "Result: %d\012\000");

    LC0 = 20020;
    int32_t arrayLC0[] = {2,3,4,10,40};
    for(int i=0; i<5; i++) *((uint32_t*)(malloc_0+LC0+i*4)) = arrayLC0[i];

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int branch_count = sizeof(cond_branches)/sizeof(cond_branches[0]);

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
    for (int i=0; i < branch_count; i++)
    {
        printf("%d ", cond_branches[i]);
    }
    printf("\n");
    for (int i=0; i < branch_count; i++)
    {
        printf("%d ", mispredictions[i]);
    }
    printf("\n");
}

void binarySearch();
void main();

void binarySearch()
{
    counters[0] ++;
    push(2, &fp.i, &lr.i);
    fp.i = sp.i + (4);
    sp.i = sp.i - (24);
    str4000(&r0.i, &fp.i, -16);
    str4000(&r1.i, &fp.i, -20);
    str4000(&r2.i, &fp.i, -24);
    str4000(&r3.i, &fp.i, -28);
    ldr4000(&r2.i, &fp.i, -24);
    ldr4000(&r3.i, &fp.i, -20);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n != v)
    {
        cond_branches[0]++;
        if(branch_bits[0] == 0)
        {
            mispredictions[0]++;
            branch_bits[0] = 1;
        }
        goto L2;
    }
    cond_branches[0]++;
    if(branch_bits[0] == 1)
    {
        mispredictions[0]++;
        branch_bits[0] = 0;
    }
    counters[1] ++;
    ldr4000(&r2.i, &fp.i, -24);
    ldr4000(&r3.i, &fp.i, -20);
    r3.i = r2.i - (r3.i);
    r2.i = (uint32_t)r3.i >> 31;
    r3.i = r2.i + (r3.i);
    r3.i = r3.i >> 1;
    r2.i = r3.i;
    ldr4000(&r3.i, &fp.i, -20);
    r3.i = r3.i + (r2.i);
    str4000(&r3.i, &fp.i, -8);
    ldr4000(&r3.i, &fp.i, -8);
    r3.i = (uint32_t)r3.i << 2;
    ldr4000(&r2.i, &fp.i, -16);
    r3.i = r2.i + (r3.i);
    ldr4000(&r3.i, &r3.i, 0);
    ldr4000(&r2.i, &fp.i, -28);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z)
    {
        cond_branches[1]++;
        if(branch_bits[1] == 0)
        {
            mispredictions[1]++;
            branch_bits[1] = 1;
        }
        goto L3;
    }
    cond_branches[1]++;
    if(branch_bits[1] == 1)
    {
        mispredictions[1]++;
        branch_bits[1] = 0;
    }
    counters[2] ++;
    ldr4000(&r3.i, &fp.i, -8);
    goto L4;
L3:
    counters[3] ++;
    ldr4000(&r3.i, &fp.i, -8);
    r3.i = (uint32_t)r3.i << 2;
    ldr4000(&r2.i, &fp.i, -16);
    r3.i = r2.i + (r3.i);
    ldr4000(&r3.i, &r3.i, 0);
    ldr4000(&r2.i, &fp.i, -28);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n == v)
    {
        cond_branches[2]++;
        if(branch_bits[2] == 0)
        {
            mispredictions[2]++;
            branch_bits[2] = 1;
        }
        goto L5;
    }
    cond_branches[2]++;
    if(branch_bits[2] == 1)
    {
        mispredictions[2]++;
        branch_bits[2] = 0;
    }
    counters[4] ++;
    ldr4000(&r3.i, &fp.i, -8);
    r2.i = r3.i - (1);
    ldr4000(&r3.i, &fp.i, -28);
    ldr4000(&r1.i, &fp.i, -20);
    ldr4000(&r0.i, &fp.i, -16);
    binarySearch();
    counters[5] ++;
    r3.i = r0.i;
    goto L4;
L5:
    counters[6] ++;
    ldr4000(&r3.i, &fp.i, -8);
    r1.i = r3.i + (1);
    ldr4000(&r3.i, &fp.i, -28);
    ldr4000(&r2.i, &fp.i, -24);
    ldr4000(&r0.i, &fp.i, -16);
    binarySearch();
    counters[7] ++;
    r3.i = r0.i;
    goto L4;
L2:
    counters[8] ++;
    r3.i = ~0;
L4:
    counters[9] ++;
    r0.i = r3.i;
    sp.i = fp.i - (4);
    pop(2, &pc.i, &fp.i);
    return;

}

void main()
{
    malloc_start();
    counters[10] ++;
    push(2, &fp.i, &lr.i);
    fp.i = sp.i + (4);
    sp.i = sp.i - (32);
    r3.i = (LC0 & 0xffff);
    r3.i = r3.i | (((uint32_t)LC0 >> 16) << 16);
    ip.i = fp.i - (32);
    lr.i = r3.i;
    ldm1(&lr.i, 4, &r0.i, &r1.i, &r2.i, &r3.i);
    stm1(&ip.i, 4, &r0.i, &r1.i, &r2.i, &r3.i);
    ldr4000(&r3.i, &lr.i, 0);
    str4000(&r3.i, &ip.i, 0);
    r3.i = 6;
    str4000(&r3.i, &fp.i, -8);
    r3.i = 40;
    str4000(&r3.i, &fp.i, -12);
    ldr4000(&r3.i, &fp.i, -8);
    r2.i = r3.i - (1);
    r0.i = fp.i - (32);
    ldr4000(&r3.i, &fp.i, -12);
    r1.i = 0;
    binarySearch();
    counters[11] ++;
    r3.i = r0.i;
    r1.i = r3.i;
    r0.i = (LC1 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC1 >> 16) << 16);
    printf_help(malloc_0+r0.i, r1.i, r2.i, r3.i);
    counters[12] ++;
    r3.i = 0;
    r0.i = r3.i;
    sp.i = fp.i - (4);
    pop(2, &pc.i, &fp.i);
    counter_summary();
    return;

}