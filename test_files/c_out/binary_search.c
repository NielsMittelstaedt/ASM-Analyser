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

reg r5, r0, r3, r1, r2, r4;

int32_t LC1, LC0;

int load_counter = 0, store_counter = 0;
int counters[16] = { 0 };
int block_sizes[16] = {4,5,1,3,2,3,1,11,7,1,3,1,4,3,3,1};

uint8_t branch_bits[9] = {0};
int cond_branches[9] = {0};
int mispredictions[9] = {0};

void ldr4010(int32_t *target, int32_t *address, int32_t offset)
{
    *target = *((uint32_t*)(malloc_0+*address));
    *address += offset;
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
void str4000(int32_t *target, int32_t *address, int32_t offset)
{
    *((uint32_t*)(malloc_0+*address+offset)) = *target;
    store_counter ++;
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
void str4100(int32_t *target, int32_t *address, int32_t offset)
{
    *((uint32_t*)(malloc_0+*address+offset)) = *target;
    *address += offset;
    store_counter ++;
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
void ldr4000(int32_t *target, int32_t *address, int32_t offset)
{
    *target = *((uint32_t*)(malloc_0+*address+offset));
    load_counter ++;
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
    tmp = r1.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r2.i);
    v = (r1.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    str4100(&lr.i, &sp.i, -4);
    lr.i = r0.i;
    if (!z && n == v)
    {
        cond_branches[0]++;
        if(branch_bits[0] == 0)
        {
            mispredictions[0]++;
            branch_bits[0]++;
        }
        else if(branch_bits[0] == 1)
        {
            mispredictions[0]++;
            branch_bits[0] += 2;
        }
        else if(branch_bits[0] == 2)
        {
            branch_bits[0]++;
        }
        goto L8;
    }
    cond_branches[0]++;
    if(branch_bits[0] == 3)
    {
        mispredictions[0]++;
        branch_bits[0]--;
    }
    else if(branch_bits[0] == 2)
    {
        mispredictions[0]++;
        branch_bits[0] = 0;
    }
    else if(branch_bits[0] == 1)
    {
        branch_bits[0]--;
    }
L2:
    counters[1] ++;
    r0.i = r2.i - (r1.i);
    r0.i = r1.i + ((r0.i >> 1));
    ldr4000(&ip.i, &lr.i, ((uint32_t)r0.i << 2));
    tmp = ip.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r3.i);
    v = (ip.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (z)
    {
        ldr4010(&pc.i, &sp.i, 4);
        cond_branches[1]++;
        if(branch_bits[1] == 0)
        {
            mispredictions[1]++;
            branch_bits[1]++;
        }
        else if(branch_bits[1] == 1)
        {
            mispredictions[1]++;
            branch_bits[1] += 2;
        }
        else if(branch_bits[1] == 2)
        {
            branch_bits[1]++;
        }
        return;
    }
    cond_branches[1]++;
    if(branch_bits[1] == 3)
    {
        mispredictions[1]++;
        branch_bits[1]--;
    }
    else if(branch_bits[1] == 2)
    {
        mispredictions[1]++;
        branch_bits[1] = 0;
    }
    else if(branch_bits[1] == 1)
    {
        branch_bits[1]--;
    }
    counters[2] ++;
    if (z || n != v)
    {
        cond_branches[2]++;
        if(branch_bits[2] == 0)
        {
            mispredictions[2]++;
            branch_bits[2]++;
        }
        else if(branch_bits[2] == 1)
        {
            mispredictions[2]++;
            branch_bits[2] += 2;
        }
        else if(branch_bits[2] == 2)
        {
            branch_bits[2]++;
        }
        goto L4;
    }
    cond_branches[2]++;
    if(branch_bits[2] == 3)
    {
        mispredictions[2]++;
        branch_bits[2]--;
    }
    else if(branch_bits[2] == 2)
    {
        mispredictions[2]++;
        branch_bits[2] = 0;
    }
    else if(branch_bits[2] == 1)
    {
        branch_bits[2]--;
    }
    counters[3] ++;
    r2.i = r0.i - (1);
    tmp = r2.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r1.i);
    v = (r2.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n == v)
    {
        cond_branches[3]++;
        if(branch_bits[3] == 0)
        {
            mispredictions[3]++;
            branch_bits[3]++;
        }
        else if(branch_bits[3] == 1)
        {
            mispredictions[3]++;
            branch_bits[3] += 2;
        }
        else if(branch_bits[3] == 2)
        {
            branch_bits[3]++;
        }
        goto L2;
    }
    cond_branches[3]++;
    if(branch_bits[3] == 3)
    {
        mispredictions[3]++;
        branch_bits[3]--;
    }
    else if(branch_bits[3] == 2)
    {
        mispredictions[3]++;
        branch_bits[3] = 0;
    }
    else if(branch_bits[3] == 1)
    {
        branch_bits[3]--;
    }
L8:
    counters[4] ++;
    r0.i = ~0;
    ldr4010(&pc.i, &sp.i, 4);
    return;
L4:
    counters[5] ++;
    r1.i = r0.i + (1);
    tmp = r1.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r2.i);
    v = (r1.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (z || n != v)
    {
        cond_branches[4]++;
        if(branch_bits[4] == 0)
        {
            mispredictions[4]++;
            branch_bits[4]++;
        }
        else if(branch_bits[4] == 1)
        {
            mispredictions[4]++;
            branch_bits[4] += 2;
        }
        else if(branch_bits[4] == 2)
        {
            branch_bits[4]++;
        }
        goto L2;
    }
    cond_branches[4]++;
    if(branch_bits[4] == 3)
    {
        mispredictions[4]++;
        branch_bits[4]--;
    }
    else if(branch_bits[4] == 2)
    {
        mispredictions[4]++;
        branch_bits[4] = 0;
    }
    else if(branch_bits[4] == 1)
    {
        branch_bits[4]--;
    }
    counters[6] ++;
    goto L8;
    return;
}

void main()
{
    malloc_start();
    counters[7] ++;
    push(3, &r4.i, &r5.i, &lr.i);
    r4.i = (LC0 & 0xffff);
    r4.i = r4.i | (((uint32_t)LC0 >> 16) << 16);
    sp.i = sp.i - (28);
    r5.i = sp.i + (4);
    ip.i = 0;
    ldm1(&r4.i, 4, &r0.i, &r1.i, &r2.i, &r3.i);
    lr.i = 5;
    ldr4000(&r4.i, &r4.i, 0);
    stm1(&r5.i, 4, &r0.i, &r1.i, &r2.i, &r3.i);
    str4000(&r4.i, &r5.i, 0);
L11:
    counters[8] ++;
    r2.i = lr.i - (ip.i);
    r3.i = sp.i + (24);
    r2.i = ip.i + ((r2.i >> 1));
    r3.i = r3.i + (((uint32_t)r2.i << 2));
    ldr4000(&r3.i, &r3.i, -20);
    tmp = r3.i - 40;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 40);
    v = (r3.i&0x80000000) != (40&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        cond_branches[5]++;
        if(branch_bits[5] == 0)
        {
            mispredictions[5]++;
            branch_bits[5]++;
        }
        else if(branch_bits[5] == 1)
        {
            mispredictions[5]++;
            branch_bits[5] += 2;
        }
        else if(branch_bits[5] == 2)
        {
            branch_bits[5]++;
        }
        goto L12;
    }
    cond_branches[5]++;
    if(branch_bits[5] == 3)
    {
        mispredictions[5]++;
        branch_bits[5]--;
    }
    else if(branch_bits[5] == 2)
    {
        mispredictions[5]++;
        branch_bits[5] = 0;
    }
    else if(branch_bits[5] == 1)
    {
        branch_bits[5]--;
    }
    counters[9] ++;
    if (z || n != v)
    {
        cond_branches[6]++;
        if(branch_bits[6] == 0)
        {
            mispredictions[6]++;
            branch_bits[6]++;
        }
        else if(branch_bits[6] == 1)
        {
            mispredictions[6]++;
            branch_bits[6] += 2;
        }
        else if(branch_bits[6] == 2)
        {
            branch_bits[6]++;
        }
        goto L13;
    }
    cond_branches[6]++;
    if(branch_bits[6] == 3)
    {
        mispredictions[6]++;
        branch_bits[6]--;
    }
    else if(branch_bits[6] == 2)
    {
        mispredictions[6]++;
        branch_bits[6] = 0;
    }
    else if(branch_bits[6] == 1)
    {
        branch_bits[6]--;
    }
    counters[10] ++;
    lr.i = r2.i - (1);
    tmp = lr.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) ip.i);
    v = (lr.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    if (n == v)
    {
        cond_branches[7]++;
        if(branch_bits[7] == 0)
        {
            mispredictions[7]++;
            branch_bits[7]++;
        }
        else if(branch_bits[7] == 1)
        {
            mispredictions[7]++;
            branch_bits[7] += 2;
        }
        else if(branch_bits[7] == 2)
        {
            branch_bits[7]++;
        }
        goto L11;
    }
    cond_branches[7]++;
    if(branch_bits[7] == 3)
    {
        mispredictions[7]++;
        branch_bits[7]--;
    }
    else if(branch_bits[7] == 2)
    {
        mispredictions[7]++;
        branch_bits[7] = 0;
    }
    else if(branch_bits[7] == 1)
    {
        branch_bits[7]--;
    }
L19:
    counters[11] ++;
    r2.i = ~0;
L12:
    counters[12] ++;
    r1.i = (LC1 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC1 >> 16) << 16);
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[13] ++;
    r0.i = 0;
    sp.i = sp.i + (28);
    pop(3, &pc.i, &r5.i, &r4.i);
    counter_summary();
    return;
L13:
    counters[14] ++;
    ip.i = r2.i + (1);
    tmp = ip.i - lr.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) lr.i);
    v = (ip.i&0x80000000) != (lr.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (z || n != v)
    {
        cond_branches[8]++;
        if(branch_bits[8] == 0)
        {
            mispredictions[8]++;
            branch_bits[8]++;
        }
        else if(branch_bits[8] == 1)
        {
            mispredictions[8]++;
            branch_bits[8] += 2;
        }
        else if(branch_bits[8] == 2)
        {
            branch_bits[8]++;
        }
        goto L11;
    }
    cond_branches[8]++;
    if(branch_bits[8] == 3)
    {
        mispredictions[8]++;
        branch_bits[8]--;
    }
    else if(branch_bits[8] == 2)
    {
        mispredictions[8]++;
        branch_bits[8] = 0;
    }
    else if(branch_bits[8] == 1)
    {
        branch_bits[8]--;
    }
    counters[15] ++;
    goto L19;
    return;
}