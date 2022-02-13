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

reg r10, r3, r1, r4, r2, r8, r6, r9, r0, r5, r7;

int32_t LC1, LC2, LC0;

int load_counter = 0, store_counter = 0;
int counters[18] = { 0 };
int block_sizes[18] = {2,3,4,13,6,5,2,5,2,6,3,1,3,17,4,4,2,3};

uint8_t branch_bits[8] = {0};
int cond_branches[8] = {0};
int mispredictions[8] = {0};

void ldr4000(int32_t *target, int32_t *address, int32_t offset)
{
    *target = *((uint32_t*)(malloc_0+*address+offset));
    load_counter ++;
}
void ldr4100(int32_t *target, int32_t *address, int32_t offset)
{
    *target = *((uint32_t*)(malloc_0+*address+offset));
    *address += offset;
    load_counter ++;
}
void stm0(int32_t *address, int num, ...)
{
    va_list args;
    va_start(args, num);
    int32_t tmp = *address;
    for (int i=0; i < num; i++)
    {
        int32_t *cur_arg = va_arg(args, int32_t *);
        *((uint32_t*) (malloc_0 + tmp)) = *cur_arg;
        tmp += 4;
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
void str4000(int32_t *target, int32_t *address, int32_t offset)
{
    *((uint32_t*)(malloc_0+*address+offset)) = *target;
    store_counter ++;
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
void ldr4010(int32_t *target, int32_t *address, int32_t offset)
{
    *target = *((uint32_t*)(malloc_0+*address));
    *address += offset;
    load_counter ++;
}
void ldm0(int32_t *address, int num, ...)
{
    va_list args;
    va_start(args, num);
    int32_t tmp = *address;
    for (int i=0; i < num; i++)
    {
        int32_t *cur_arg = va_arg(args, int32_t *);
        *cur_arg = *((uint32_t*) (malloc_0 + tmp));
        tmp += 4;
        load_counter ++;
    }
    va_end(args);
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
    malloc_0 = (uint8_t*) malloc(20069);
    sp.i = 19996;
    fp = sp;
    LC1 = 20000;
    strcpy(malloc_0+LC1, "Order of Sorted elements: \000");

    LC2 = 20032;
    strcpy(malloc_0+LC2, " %d\000");

    LC0 = 20041;
    int32_t arrayLC0[] = {0,1,2,3,4,5,6};
    for(int i=0; i<7; i++) *((uint32_t*)(malloc_0+LC0+i*4)) = arrayLC0[i];

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

void quicksort();
void main();

void quicksort()
{
    counters[0] ++;
    tmp = r1.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r2.i);
    v = (r1.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (n == v)
    {
        cond_branches[0]++;
        if(branch_bits[0] == 0)
        {
            mispredictions[0]++;
            branch_bits[0] = 1;
        }
        return;
    }
    cond_branches[0]++;
    if(branch_bits[0] == 1)
    {
        mispredictions[0]++;
        branch_bits[0] = 0;
    }
    counters[1] ++;
    push(8, &r4.i, &r5.i, &r6.i, &r7.i, &r8.i, &r9.i, &r10.i, &lr.i);
    r6.i = r2.i;
    r7.i = r0.i;
L10:
    counters[2] ++;
    r8.i = (uint32_t)r1.i << 2;
    r4.i = r6.i;
    r2.i = r7.i + (r8.i);
    ip.i = r1.i;
L3:
    counters[3] ++;
    tmp = r6.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) ip.i);
    v = (r6.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    ldr4000(&r5.i, &r7.i, ((uint32_t)ip.i << 2));
    ldr4000(&lr.i, &r2.i, 0);
    r3.i = (uint32_t)ip.i << 2;
    if (!z && n == v)
    {
        r9.i = 1;
    }
    if (z || n != v)
    {
        r9.i = 0;
    }
    tmp = r5.i - lr.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) lr.i);
    v = (r5.i&0x80000000) != (lr.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    r0.i = r7.i + (r3.i);
    if (!z && n == v)
    {
        r9.i = 0;
    }
    tmp = r9.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r9.i) >= ((uint32_t) 0);
    v = (r9.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r9.i&0x80000000);
    if (!z)
    {
        r3.i = r3.i + (4);
    }
    if (!z)
    {
        r3.i = r7.i + (r3.i);
    }
    if (z)
    {
        cond_branches[1]++;
        if(branch_bits[1] == 0)
        {
            mispredictions[1]++;
            branch_bits[1] = 1;
        }
        goto L9;
    }
    cond_branches[1]++;
    if(branch_bits[1] == 1)
    {
        mispredictions[1]++;
        branch_bits[1] = 0;
    }
L4:
    counters[4] ++;
    r0.i = r3.i;
    ldr4010(&r5.i, &r3.i, 4);
    ip.i = ip.i + (1);
    tmp = r5.i - lr.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) lr.i);
    v = (r5.i&0x80000000) != (lr.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (z || n != v)
    {
        tmp = ip.i - r6.i;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) ip.i) >= ((uint32_t) r6.i);
        v = (ip.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    }
    if (n != v)
    {
        cond_branches[2]++;
        if(branch_bits[2] == 0)
        {
            mispredictions[2]++;
            branch_bits[2] = 1;
        }
        goto L4;
    }
    cond_branches[2]++;
    if(branch_bits[2] == 1)
    {
        mispredictions[2]++;
        branch_bits[2] = 0;
    }
L9:
    counters[5] ++;
    ldr4000(&r10.i, &r7.i, ((uint32_t)r4.i << 2));
    r3.i = (uint32_t)r4.i << 2;
    r9.i = r7.i + (r3.i);
    tmp = r10.i - lr.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r10.i) >= ((uint32_t) lr.i);
    v = (r10.i&0x80000000) != (lr.i&0x80000000) && (tmp&0x80000000) != (r10.i&0x80000000);
    if (z || n != v)
    {
        cond_branches[3]++;
        if(branch_bits[3] == 0)
        {
            mispredictions[3]++;
            branch_bits[3] = 1;
        }
        goto L5;
    }
    cond_branches[3]++;
    if(branch_bits[3] == 1)
    {
        mispredictions[3]++;
        branch_bits[3] = 0;
    }
    counters[6] ++;
    r3.i = r3.i - (4);
    r3.i = r7.i + (r3.i);
L6:
    counters[7] ++;
    r9.i = r3.i;
    ldr4010(&r10.i, &r3.i, -4);
    r4.i = r4.i - (1);
    tmp = r10.i - lr.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r10.i) >= ((uint32_t) lr.i);
    v = (r10.i&0x80000000) != (lr.i&0x80000000) && (tmp&0x80000000) != (r10.i&0x80000000);
    if (!z && n == v)
    {
        cond_branches[4]++;
        if(branch_bits[4] == 0)
        {
            mispredictions[4]++;
            branch_bits[4] = 1;
        }
        goto L6;
    }
    cond_branches[4]++;
    if(branch_bits[4] == 1)
    {
        mispredictions[4]++;
        branch_bits[4] = 0;
    }
L5:
    counters[8] ++;
    tmp = ip.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r4.i);
    v = (ip.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (n != v)
    {
        cond_branches[5]++;
        if(branch_bits[5] == 0)
        {
            mispredictions[5]++;
            branch_bits[5] = 1;
        }
        goto L19;
    }
    cond_branches[5]++;
    if(branch_bits[5] == 1)
    {
        mispredictions[5]++;
        branch_bits[5] = 0;
    }
    counters[9] ++;
    ldr4000(&r3.i, &r9.i, 0);
    r2.i = r4.i - (1);
    r0.i = r7.i;
    str4000(&r3.i, &r7.i, r8.i);
    str4000(&lr.i, &r9.i, 0);
    quicksort();
    counters[10] ++;
    r1.i = r4.i + (1);
    tmp = r1.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r6.i);
    v = (r1.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (n != v)
    {
        cond_branches[6]++;
        if(branch_bits[6] == 0)
        {
            mispredictions[6]++;
            branch_bits[6] = 1;
        }
        goto L10;
    }
    cond_branches[6]++;
    if(branch_bits[6] == 1)
    {
        mispredictions[6]++;
        branch_bits[6] = 0;
    }
    counters[11] ++;
    pop(8, &pc.i, &r10.i, &r9.i, &r8.i, &r7.i, &r6.i, &r5.i, &r4.i);
    return;
L19:
    counters[12] ++;
    str4000(&r10.i, &r0.i, 0);
    str4000(&r5.i, &r9.i, 0);
    goto L3;
    return;
}

void main()
{
    malloc_start();
    counters[13] ++;
    ip.i = (LC0 & 0xffff);
    ip.i = ip.i | (((uint32_t)LC0 >> 16) << 16);
    push(4, &r4.i, &r5.i, &r6.i, &lr.i);
    sp.i = sp.i - (32);
    ldm1(&ip.i, 4, &r0.i, &r1.i, &r2.i, &r3.i);
    lr.i = sp.i + (4);
    r5.i = (LC2 & 0xffff);
    r6.i = sp.i + (28);
    r5.i = r5.i | (((uint32_t)LC2 >> 16) << 16);
    r4.i = sp.i;
    stm1(&lr.i, 4, &r0.i, &r1.i, &r2.i, &r3.i);
    ldm0(&ip.i, 3, &r0.i, &r1.i, &r2.i);
    stm0(&lr.i, 3, &r0.i, &r1.i, &r2.i);
    r0.i = sp.i + (4);
    r1.i = 0;
    r2.i = 6;
    quicksort();
    counters[14] ++;
    r1.i = (LC1 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC1 >> 16) << 16);
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
L21:
    counters[15] ++;
    ldr4100(&r2.i, &r4.i, 4);
    r1.i = r5.i;
    r0.i = 1;
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[16] ++;
    tmp = r4.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r6.i);
    v = (r4.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        cond_branches[7]++;
        if(branch_bits[7] == 0)
        {
            mispredictions[7]++;
            branch_bits[7] = 1;
        }
        goto L21;
    }
    cond_branches[7]++;
    if(branch_bits[7] == 1)
    {
        mispredictions[7]++;
        branch_bits[7] = 0;
    }
    counters[17] ++;
    r0.i = 0;
    sp.i = sp.i + (32);
    pop(4, &pc.i, &r6.i, &r5.i, &r4.i);
    counter_summary();
    return;

}