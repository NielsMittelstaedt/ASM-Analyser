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

reg r3, r2, r5, r6, r1, r0, r4;

int32_t LC1, LC2, LC0;

int load_counter = 0, store_counter = 0;
int counters[17] = { 0 };
int block_sizes[17] = {16,3,5,2,5,3,2,5,2,5,16,3,4,2,3,6,5};

int cond_branches = 0, mispredictions = 0;
uint8_t branch_bits[6] = {0};

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
void ldr4010(int32_t *target, int32_t *address, int32_t offset)
{
    *target = *((uint32_t*)(malloc_0+*address));
    *address += offset;
    load_counter ++;
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
void stmib0(int32_t *address, int num, ...)
{
    va_list args;
    va_start(args, num);
    int32_t tmp = *address;
    for (int i=0; i < num; i++)
    {
        int32_t *cur_arg = va_arg(args, int32_t *);
        tmp += 4;
        *((uint32_t*) (malloc_0 + tmp)) = *cur_arg;
        store_counter ++;
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
    malloc_0 = (uint8_t*) malloc(20048);
    sp.i = 19996;
    fp = sp;
    LC1 = 20000;
    strcpy(malloc_0+LC1, "Sorted array:\000");

    LC2 = 20019;
    strcpy(malloc_0+LC2, " %d\000");

    LC0 = 20028;
    int32_t arrayLC0[] = {9,1,3,7,2};
    for(int i=0; i<5; i++) *((uint32_t*)(malloc_0+LC0+i*4)) = arrayLC0[i];

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
    ip.i = (LC0 & 0xffff);
    ip.i = ip.i | (((uint32_t)LC0 >> 16) << 16);
    push(4, &r4.i, &r5.i, &r6.i, &lr.i);
    sp.i = sp.i - (24);
    ldm1(&ip.i, 4, &r0.i, &r1.i, &r2.i, &r3.i);
    lr.i = sp.i + (4);
    stm1(&lr.i, 4, &r0.i, &r1.i, &r2.i, &r3.i);
    r1.i = r0.i;
    ldr4000(&r3.i, &sp.i, 8);
    ldr4000(&r2.i, &ip.i, 0);
    tmp = r0.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) r3.i);
    v = (r0.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    str4000(&r2.i, &lr.i, 0);
    if (!z && n == v)
    {
        r1.i = r3.i;
    }
    if (!z && n == v)
    {
        str4000(&r3.i, &sp.i, 4);
    }
    if (!z && n == v)
    {
        r3.i = r0.i;
    }
    if (!z && n == v)
    {
        str4000(&r0.i, &sp.i, 8);
    }
L5:
    counters[1] ++;
    ldr4000(&r2.i, &sp.i, 12);
    tmp = r3.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r2.i);
    v = (r3.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
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
        goto L4;
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
    counters[2] ++;
    r0.i = r3.i;
    str4000(&r3.i, &sp.i, 12);
    str4000(&r2.i, &sp.i, 8);
    r3.i = r2.i;
    r2.i = r0.i;
L4:
    counters[3] ++;
    tmp = r1.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r3.i);
    v = (r1.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (z || n != v)
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
    counters[4] ++;
    r0.i = r1.i;
    str4000(&r1.i, &sp.i, 8);
    str4000(&r3.i, &sp.i, 4);
    r1.i = r3.i;
    r3.i = r0.i;
L9:
    counters[5] ++;
    ldr4000(&r0.i, &sp.i, 16);
    tmp = r2.i - r0.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r0.i);
    v = (r2.i&0x80000000) != (r0.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z && n == v)
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
        goto L7;
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
L8:
    counters[6] ++;
    tmp = r3.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r2.i);
    v = (r3.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
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
        goto L15;
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
    counters[7] ++;
    ip.i = r3.i;
    str4000(&r3.i, &sp.i, 12);
    str4000(&r2.i, &sp.i, 8);
    r3.i = r2.i;
    r2.i = ip.i;
L15:
    counters[8] ++;
    tmp = r1.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r3.i);
    v = (r1.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!z && n == v)
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
        goto L11;
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
L14:
    counters[9] ++;
    ldr4000(&ip.i, &sp.i, 20);
    tmp = r0.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) ip.i);
    v = (r0.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z && n == v)
    {
        str4000(&r0.i, &sp.i, 20);
    }
    if (!z && n == v)
    {
        r0.i = ip.i;
    }
    if (!z && n == v)
    {
        str4000(&ip.i, &sp.i, 16);
    }
L13:
    counters[10] ++;
    tmp = r2.i - r0.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r0.i);
    v = (r2.i&0x80000000) != (r0.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z && n == v)
    {
        str4000(&r0.i, &sp.i, 12);
    }
    if (!z && n == v)
    {
        str4000(&r2.i, &sp.i, 16);
    }
    r5.i = (LC2 & 0xffff);
    if (!z && n == v)
    {
        r2.i = r0.i;
    }
    tmp = r3.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r2.i);
    v = (r3.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    r0.i = 1;
    if (!z && n == v)
    {
        str4000(&r3.i, &sp.i, 12);
    }
    if (!z && n == v)
    {
        str4000(&r2.i, &sp.i, 8);
    }
    if (!z && n == v)
    {
        r3.i = r2.i;
    }
    tmp = r1.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r3.i);
    v = (r1.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!z && n == v)
    {
        str4000(&r1.i, &sp.i, 8);
    }
    r1.i = (LC1 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC1 >> 16) << 16);
    if (!z && n == v)
    {
        str4000(&r3.i, &sp.i, 4);
    }
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[11] ++;
    r5.i = r5.i | (((uint32_t)LC2 >> 16) << 16);
    r4.i = sp.i + (4);
    r6.i = sp.i + (24);
L19:
    counters[12] ++;
    ldr4010(&r2.i, &r4.i, 4);
    r1.i = r5.i;
    r0.i = 1;
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[13] ++;
    tmp = r4.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r6.i);
    v = (r4.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
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
        goto L19;
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
    counters[14] ++;
    r0.i = 0;
    sp.i = sp.i + (24);
    pop(4, &pc.i, &r6.i, &r5.i, &r4.i);
    counter_summary();
    return;
L7:
    counters[15] ++;
    ip.i = r2.i;
    str4000(&r2.i, &sp.i, 16);
    str4000(&r0.i, &sp.i, 12);
    r2.i = r0.i;
    r0.i = ip.i;
    goto L8;
L11:
    counters[16] ++;
    ip.i = r1.i;
    r1.i = r3.i;
    stmib0(&sp.i, 2, &r3.i, &ip.i);
    r3.i = ip.i;
    goto L14;
    return;
}