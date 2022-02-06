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

reg r3, r8, r6, r2, r4, r10, r7, r9, r5, r1, r0;

int32_t LC1, LC2, LC3, LC4, LC5, LC6, LC7, LC8, LC0;

int load_counter = 0, store_counter = 0;
int counters[131] = { 0 };
int block_sizes[131] = {8,3,5,1,2,3,4,1,1,3,3,3,3,2,2,1,3,4,1,4,1,1,3,3,3,3,2,2,6,1,3,1,2,2,1,1,2,2,1,3,1,5,2,2,4,1,1,3,3,3,2,2,4,2,4,1,1,3,3,3,2,2,2,2,2,1,2,5,2,4,3,2,5,5,2,4,2,1,4,4,1,3,2,2,2,8,2,1,4,6,5,4,2,8,8,4,2,7,3,3,3,13,10,2,5,7,5,3,6,2,5,3,3,1,3,3,3,2,2,3,2,5,5,3,5,1,2,5,3,5,1};

int cond_branches = 0, mispredictions = 0;
uint8_t branch_bits[52] = {0};

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
void rand_help()
{
    r0.i = rand();
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
void ldr4000(int32_t *target, int32_t *address, int32_t offset)
{
    *target = *((uint32_t*)(malloc_0+*address+offset));
    load_counter ++;
}
void smull(int32_t *dest_lo, int32_t *dest_hi, int32_t *op1, int32_t *op2)
{
    uint64_t res = (uint64_t) (*op1) * (*op2);
    *dest_lo = (uint32_t) res;
    *dest_hi = (uint32_t) (res >> 32);
}
void str4000(int32_t *target, int32_t *address, int32_t offset)
{
    *((uint32_t*)(malloc_0+*address+offset)) = *target;
    store_counter ++;
}
void idiv()
{
    r0.i = r0.i / r1.i;
}
void ldr4100(int32_t *target, int32_t *address, int32_t offset)
{
    *target = *((uint32_t*)(malloc_0+*address+offset));
    *address += offset;
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
void idivmod()
{
    int32_t quot = r0.i / r1.i;
    int32_t rem = r0.i % r1.i;
    r0.i = quot;
    r1.i = rem;
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
    malloc_0 = (uint8_t*) malloc(20194);
    sp.i = 19996;
    fp = sp;
    LC1 = 20000;
    strcpy(malloc_0+LC1, "array[%d]: \000");

    LC2 = 20017;
    strcpy(malloc_0+LC2, "%d\012\000");

    LC3 = 20029;
    strcpy(malloc_0+LC3, "tmp: %d\012\000");

    LC4 = 20046;
    strcpy(malloc_0+LC4, "crossSum: %d\012\000");

    LC5 = 20068;
    strcpy(malloc_0+LC5, "tmp2: %d\012\000");

    LC6 = 20086;
    strcpy(malloc_0+LC6, "%d is prime\012\000");

    LC7 = 20107;
    strcpy(malloc_0+LC7, "%d is not prime\012\000");

    LC8 = 20132;
    strcpy(malloc_0+LC8, "Ergebnis: %d\012\000");

    LC0 = 20154;
    int32_t arrayLC0[] = {1,34,6,2,6,2,7,2,17,7};
    for(int i=0; i<10; i++) *((uint32_t*)(malloc_0+LC0+i*4)) = arrayLC0[i];

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

void Millerpart0();
void mulmod();
void modulo();
void Miller();
void swap();
void heapify();
void heapSort();
void test();
void fib();
void main();

void Millerpart0()
{
    counters[0] ++;
    push(9, &r4.i, &r5.i, &r6.i, &r7.i, &r8.i, &r9.i, &r10.i, &fp.i, &lr.i);
    tmp = r0.i & 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    sp.i = sp.i - (12);
    r8.i = r0.i - (1);
    fp.i = r0.i;
    r9.i = r8.i;
    str4000(&r1.i, &sp.i, 4);
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
        goto L2;
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
L3:
    counters[1] ++;
    r9.i = r9.i >> 1;
    tmp = r9.i & 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    if (z)
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
        goto L3;
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
L2:
    counters[2] ++;
    ldr4000(&r3.i, &sp.i, 4);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z && n == v)
    {
        r3.i = 0;
    }
    if (!z && n == v)
    {
        str4000(&r3.i, &sp.i, 0);
    }
    if (z || n != v)
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
        goto L14;
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
L4:
    counters[3] ++;
    rand_help();
    counters[4] ++;
    r1.i = r8.i;
    idivmod();
    counters[5] ++;
    r6.i = r9.i;
    r5.i = 1;
    r4.i = r1.i + (1);
L7:
    counters[6] ++;
    tmp = r6.i & 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    r1.i = fp.i;
    r0.i = (r4.i) * (r5.i);
    if (z)
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
        goto L6;
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
    idivmod();
    counters[8] ++;
    r5.i = r1.i;
L6:
    counters[9] ++;
    r0.i = (r4.i) * (r4.i);
    r1.i = fp.i;
    idivmod();
    counters[10] ++;
    r6.i = r6.i >> 1;
    z = r6.i == 0;
    n = r6.i & 0x80000000;
    c = r6.i & (1 << 1 - 1);
    r4.i = r1.i;
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
    counters[11] ++;
    r0.i = r5.i;
    r1.i = fp.i;
    idivmod();
    counters[12] ++;
    tmp = r8.i - r9.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) r9.i);
    v = (r8.i&0x80000000) != (r9.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    r10.i = r1.i;
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
        goto L18;
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
    counters[13] ++;
    tmp = r1.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 1);
    v = (r1.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (z)
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
        goto L19;
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
    counters[14] ++;
    tmp = r8.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) r1.i);
    v = (r8.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    if (z)
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
        goto L9;
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
    counters[15] ++;
    r7.i = r9.i;
L13:
    counters[16] ++;
    r1.i = fp.i;
    r0.i = r10.i;
    idivmod();
    counters[17] ++;
    tmp = r10.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r10.i) >= ((uint32_t) 0);
    v = (r10.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r10.i&0x80000000);
    r7.i = (uint32_t)r7.i << 1;
    r4.i = r1.i;
    if (z || n != v)
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
        goto L10;
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
    counters[18] ++;
    r5.i = 0;
L12:
    counters[19] ++;
    tmp = r10.i & 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    r0.i = r5.i + (r4.i);
    r1.i = fp.i;
    if (z)
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
        goto L11;
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
    counters[20] ++;
    idivmod();
    counters[21] ++;
    r5.i = r1.i;
L11:
    counters[22] ++;
    r0.i = (uint32_t)r4.i << 1;
    r1.i = fp.i;
    idivmod();
    counters[23] ++;
    r10.i = r10.i >> 1;
    z = r10.i == 0;
    n = r10.i & 0x80000000;
    c = r10.i & (1 << 1 - 1);
    r4.i = r1.i;
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
        goto L12;
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
    counters[24] ++;
    r0.i = r5.i;
    r1.i = fp.i;
    idivmod();
    counters[25] ++;
    tmp = r8.i - r7.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) r7.i);
    v = (r8.i&0x80000000) != (r7.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    r10.i = r1.i;
    if (z)
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
        goto L8;
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
    counters[26] ++;
    tmp = r1.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 1);
    v = (r1.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
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
        goto L8;
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
    counters[27] ++;
    tmp = r8.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) r1.i);
    v = (r8.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
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
        goto L13;
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
L9:
    counters[28] ++;
    ldr4000(&r3.i, &sp.i, 0);
    ldr4000(&r2.i, &sp.i, 4);
    r3.i = r3.i + (1);
    str4000(&r3.i, &sp.i, 0);
    tmp = r3.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r2.i);
    v = (r3.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
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
        goto L4;
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
L14:
    counters[29] ++;
    r6.i = 1;
L1:
    counters[30] ++;
    r0.i = r6.i;
    sp.i = sp.i + (12);
    pop(9, &pc.i, &fp.i, &r10.i, &r9.i, &r8.i, &r7.i, &r6.i, &r5.i, &r4.i);
    return;
L41:
    counters[31] ++;
    r7.i = (uint32_t)r7.i << 1;
L10:
    counters[32] ++;
    tmp = r8.i - r7.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) r7.i);
    v = (r8.i&0x80000000) != (r7.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
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
        goto L41;
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
    counters[33] ++;
    tmp = r7.i & 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
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
        goto L9;
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
    counters[34] ++;
    goto L1;
L19:
    counters[35] ++;
    r7.i = r9.i;
L8:
    counters[36] ++;
    tmp = r8.i - r10.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) r10.i);
    v = (r8.i&0x80000000) != (r10.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    if (z)
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
        goto L9;
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
L42:
    counters[37] ++;
    tmp = r7.i & 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
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
        goto L9;
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
    counters[38] ++;
    goto L1;
L18:
    counters[39] ++;
    tmp = r8.i - r10.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) r10.i);
    v = (r8.i&0x80000000) != (r10.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    r7.i = r8.i;
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
        goto L42;
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
    counters[40] ++;
    goto L9;
    return;
}

void mulmod()
{
    counters[41] ++;
    push(6, &r4.i, &r5.i, &r6.i, &r7.i, &r8.i, &lr.i);
    r5.i = r1.i;
    r1.i = r2.i;
    r7.i = r2.i;
    idivmod();
    counters[42] ++;
    tmp = r5.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) 0);
    v = (r5.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (z || n != v)
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
        goto L47;
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
    counters[43] ++;
    r4.i = r1.i;
    r6.i = 0;
L46:
    counters[44] ++;
    tmp = r5.i & 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    r0.i = r6.i + (r4.i);
    r1.i = r7.i;
    if (z)
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
        goto L45;
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
    counters[45] ++;
    idivmod();
    counters[46] ++;
    r6.i = r1.i;
L45:
    counters[47] ++;
    r0.i = (uint32_t)r4.i << 1;
    r1.i = r7.i;
    idivmod();
    counters[48] ++;
    r5.i = r5.i >> 1;
    z = r5.i == 0;
    n = r5.i & 0x80000000;
    c = r5.i & (1 << 1 - 1);
    r4.i = r1.i;
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
        goto L46;
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
    counters[49] ++;
    r1.i = r7.i;
    r0.i = r6.i;
    idivmod();
    counters[50] ++;
    r0.i = r1.i;
    pop(6, &pc.i, &r8.i, &r7.i, &r6.i, &r5.i, &r4.i);
    return;
L47:
    counters[51] ++;
    r0.i = 0;
    pop(6, &pc.i, &r8.i, &r7.i, &r6.i, &r5.i, &r4.i);
    return;

}

void modulo()
{
    counters[52] ++;
    push(6, &r4.i, &r5.i, &r6.i, &r7.i, &r8.i, &lr.i);
    r5.i = r1.i - (0);
    z = r5.i == 0;
    n = r5.i & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 0);
    v = (r1.i&0x80000000) != (0&0x80000000) && (r5.i&0x80000000) != (r1.i&0x80000000);
    r7.i = r2.i;
    if (z || n != v)
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
        goto L57;
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
    counters[53] ++;
    r4.i = r0.i;
    r6.i = 1;
L56:
    counters[54] ++;
    tmp = r5.i & 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    r1.i = r7.i;
    r0.i = (r4.i) * (r6.i);
    if (z)
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
        goto L55;
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
    counters[55] ++;
    idivmod();
    counters[56] ++;
    r6.i = r1.i;
L55:
    counters[57] ++;
    r0.i = (r4.i) * (r4.i);
    r1.i = r7.i;
    idivmod();
    counters[58] ++;
    r5.i = r5.i >> 1;
    z = r5.i == 0;
    n = r5.i & 0x80000000;
    c = r5.i & (1 << 1 - 1);
    r4.i = r1.i;
    if (!z)
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
        goto L56;
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
L54:
    counters[59] ++;
    r1.i = r7.i;
    r0.i = r6.i;
    idivmod();
    counters[60] ++;
    r0.i = r1.i;
    pop(6, &pc.i, &r8.i, &r7.i, &r6.i, &r5.i, &r4.i);
    return;
L57:
    counters[61] ++;
    r6.i = 1;
    goto L54;
    return;
}

void Miller()
{
    counters[62] ++;
    tmp = r0.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 1);
    v = (r0.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (z || n != v)
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
        goto L63;
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
    counters[63] ++;
    tmp = r0.i - 2;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 2);
    v = (r0.i&0x80000000) != (2&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (z)
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
        goto L65;
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
    counters[64] ++;
    tmp = r0.i & 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    if (z)
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
        goto L63;
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
L65:
    counters[65] ++;
    Millerpart0();
    return;
L63:
    counters[66] ++;
    r0.i = 0;
    return;

}

void swap()
{
    counters[67] ++;
    ldr4000(&r3.i, &r0.i, ((uint32_t)r1.i << 2));
    ldr4000(&ip.i, &r0.i, ((uint32_t)r2.i << 2));
    str4000(&ip.i, &r0.i, ((uint32_t)r1.i << 2));
    str4000(&r3.i, &r0.i, ((uint32_t)r2.i << 2));
    return;

}

void heapify()
{
    counters[68] ++;
    push(2, &r4.i, &lr.i);
    goto L77;
L82:
    counters[69] ++;
    ldr4000(&lr.i, &r0.i, ((uint32_t)ip.i << 2));
    ldr4000(&r4.i, &r0.i, ((uint32_t)r2.i << 2));
    tmp = r4.i - lr.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) lr.i);
    v = (r4.i&0x80000000) != (lr.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (c)
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
        goto L74;
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
    counters[70] ++;
    tmp = r1.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r3.i);
    v = (r1.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!c || z)
    {
        r3.i = ip.i;
    }
    if (c && !z)
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
        goto L81;
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
L75:
    counters[71] ++;
    tmp = r3.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r2.i);
    v = (r3.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        pop(2, &pc.i, &r4.i);
        cond_branches ++;
        if(branch_bits[31] == 0 || branch_bits[31] == 1)
        {
            mispredictions++;
            branch_bits[31]++;
        }
        else if(branch_bits[31] == 2)
        {
            branch_bits[31]++;
        }
        return;
    }
    cond_branches ++;
    if(branch_bits[31] == 2 || branch_bits[31] == 3)
    {
        mispredictions++;
        branch_bits[31]--;
    }
    else if(branch_bits[31] == 1)
    {
        branch_bits[31]--;
    }
L83:
    counters[72] ++;
    ldr4000(&lr.i, &r0.i, ((uint32_t)r2.i << 2));
    ldr4000(&ip.i, &r0.i, ((uint32_t)r3.i << 2));
    str4000(&lr.i, &r0.i, ((uint32_t)r3.i << 2));
    str4000(&ip.i, &r0.i, ((uint32_t)r2.i << 2));
    r2.i = r3.i;
L77:
    counters[73] ++;
    r3.i = (uint32_t)r2.i << 1;
    ip.i = r3.i + (1);
    r3.i = r3.i + (2);
    tmp = ip.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r1.i);
    v = (ip.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (!c)
    {
        cond_branches ++;
        if(branch_bits[32] == 0 || branch_bits[32] == 1)
        {
            mispredictions++;
            branch_bits[32]++;
        }
        else if(branch_bits[32] == 2)
        {
            branch_bits[32]++;
        }
        goto L82;
    }
    cond_branches ++;
    if(branch_bits[32] == 2 || branch_bits[32] == 3)
    {
        mispredictions++;
        branch_bits[32]--;
    }
    else if(branch_bits[32] == 1)
    {
        branch_bits[32]--;
    }
L74:
    counters[74] ++;
    tmp = r1.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r3.i);
    v = (r1.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!c || z)
    {
        pop(2, &pc.i, &r4.i);
        cond_branches ++;
        if(branch_bits[33] == 0 || branch_bits[33] == 1)
        {
            mispredictions++;
            branch_bits[33]++;
        }
        else if(branch_bits[33] == 2)
        {
            branch_bits[33]++;
        }
        return;
    }
    cond_branches ++;
    if(branch_bits[33] == 2 || branch_bits[33] == 3)
    {
        mispredictions++;
        branch_bits[33]--;
    }
    else if(branch_bits[33] == 1)
    {
        branch_bits[33]--;
    }
    counters[75] ++;
    ldr4000(&lr.i, &r0.i, ((uint32_t)r2.i << 2));
    ldr4000(&ip.i, &r0.i, ((uint32_t)r3.i << 2));
    tmp = lr.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) ip.i);
    v = (lr.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    if (c)
    {
        pop(2, &pc.i, &r4.i);
        cond_branches ++;
        if(branch_bits[34] == 0 || branch_bits[34] == 1)
        {
            mispredictions++;
            branch_bits[34]++;
        }
        else if(branch_bits[34] == 2)
        {
            branch_bits[34]++;
        }
        return;
    }
    cond_branches ++;
    if(branch_bits[34] == 2 || branch_bits[34] == 3)
    {
        mispredictions++;
        branch_bits[34]--;
    }
    else if(branch_bits[34] == 1)
    {
        branch_bits[34]--;
    }
    counters[76] ++;
    tmp = r3.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r2.i);
    v = (r3.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        cond_branches ++;
        if(branch_bits[35] == 0 || branch_bits[35] == 1)
        {
            mispredictions++;
            branch_bits[35]++;
        }
        else if(branch_bits[35] == 2)
        {
            branch_bits[35]++;
        }
        goto L83;
    }
    cond_branches ++;
    if(branch_bits[35] == 2 || branch_bits[35] == 3)
    {
        mispredictions++;
        branch_bits[35]--;
    }
    else if(branch_bits[35] == 1)
    {
        branch_bits[35]--;
    }
    counters[77] ++;
    pop(2, &pc.i, &r4.i);
    return;
L81:
    counters[78] ++;
    ldr4000(&r4.i, &r0.i, ((uint32_t)r3.i << 2));
    tmp = lr.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) r4.i);
    v = (lr.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    if (c)
    {
        r3.i = ip.i;
    }
    goto L75;
    return;
}

void heapSort()
{
    counters[79] ++;
    push(4, &r4.i, &r5.i, &r6.i, &lr.i);
    r4.i = (uint32_t)r1.i >> 1;
    tmp = r4.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 0);
    v = (r4.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (z)
    {
        cond_branches ++;
        if(branch_bits[36] == 0 || branch_bits[36] == 1)
        {
            mispredictions++;
            branch_bits[36]++;
        }
        else if(branch_bits[36] == 2)
        {
            branch_bits[36]++;
        }
        goto L85;
    }
    cond_branches ++;
    if(branch_bits[36] == 2 || branch_bits[36] == 3)
    {
        mispredictions++;
        branch_bits[36]--;
    }
    else if(branch_bits[36] == 1)
    {
        branch_bits[36]--;
    }
    counters[80] ++;
    r4.i = r4.i - (1);
L86:
    counters[81] ++;
    r2.i = r4.i;
    r4.i = r4.i - (1);
    heapify();
    counters[82] ++;
    tmp = r4.i + 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) tmp) < ((uint32_t) r4.i);
    v = (r4.i&0x80000000) == (1&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        cond_branches ++;
        if(branch_bits[37] == 0 || branch_bits[37] == 1)
        {
            mispredictions++;
            branch_bits[37]++;
        }
        else if(branch_bits[37] == 2)
        {
            branch_bits[37]++;
        }
        goto L86;
    }
    cond_branches ++;
    if(branch_bits[37] == 2 || branch_bits[37] == 3)
    {
        mispredictions++;
        branch_bits[37]--;
    }
    else if(branch_bits[37] == 1)
    {
        branch_bits[37]--;
    }
L85:
    counters[83] ++;
    r5.i = r1.i - (1);
    z = r5.i == 0;
    n = r5.i & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 1);
    v = (r1.i&0x80000000) != (1&0x80000000) && (r5.i&0x80000000) != (r1.i&0x80000000);
    if (z)
    {
        pop(4, &pc.i, &r6.i, &r5.i, &r4.i);
        cond_branches ++;
        if(branch_bits[38] == 0 || branch_bits[38] == 1)
        {
            mispredictions++;
            branch_bits[38]++;
        }
        else if(branch_bits[38] == 2)
        {
            branch_bits[38]++;
        }
        return;
    }
    cond_branches ++;
    if(branch_bits[38] == 2 || branch_bits[38] == 3)
    {
        mispredictions++;
        branch_bits[38]--;
    }
    else if(branch_bits[38] == 1)
    {
        branch_bits[38]--;
    }
    counters[84] ++;
    r4.i = r0.i + (((uint32_t)r1.i << 2));
    r6.i = r0.i + (4);
L88:
    counters[85] ++;
    ldr4100(&ip.i, &r4.i, -4);
    r1.i = r5.i;
    ldr4000(&r3.i, &r0.i, 0);
    r2.i = 0;
    r5.i = r5.i - (1);
    str4000(&ip.i, &r0.i, 0);
    str4000(&r3.i, &r4.i, 0);
    heapify();
    counters[86] ++;
    tmp = r6.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) r4.i);
    v = (r6.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    if (!z)
    {
        cond_branches ++;
        if(branch_bits[39] == 0 || branch_bits[39] == 1)
        {
            mispredictions++;
            branch_bits[39]++;
        }
        else if(branch_bits[39] == 2)
        {
            branch_bits[39]++;
        }
        goto L88;
    }
    cond_branches ++;
    if(branch_bits[39] == 2 || branch_bits[39] == 3)
    {
        mispredictions++;
        branch_bits[39]--;
    }
    else if(branch_bits[39] == 1)
    {
        branch_bits[39]--;
    }
    counters[87] ++;
    pop(4, &pc.i, &r6.i, &r5.i, &r4.i);
    return;

}

void test()
{
    counters[88] ++;
    push(6, &r4.i, &r5.i, &r6.i, &r7.i, &r8.i, &lr.i);
    r1.i = 10;
    r5.i = r0.i;
    heapSort();
    counters[89] ++;
    r8.i = (LC1 & 0xffff);
    r7.i = (LC2 & 0xffff);
    r8.i = r8.i | (((uint32_t)LC1 >> 16) << 16);
    r7.i = r7.i | (((uint32_t)LC2 >> 16) << 16);
    r4.i = 0;
    r6.i = r0.i - (4);
L99:
    counters[90] ++;
    r2.i = r4.i;
    r1.i = r8.i;
    r0.i = 1;
    r4.i = r4.i + (r0.i);
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[91] ++;
    ldr4100(&r2.i, &r6.i, 4);
    r1.i = r7.i;
    r0.i = 1;
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[92] ++;
    tmp = r4.i - 10;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 10);
    v = (r4.i&0x80000000) != (10&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        cond_branches ++;
        if(branch_bits[40] == 0 || branch_bits[40] == 1)
        {
            mispredictions++;
            branch_bits[40]++;
        }
        else if(branch_bits[40] == 2)
        {
            branch_bits[40]++;
        }
        goto L99;
    }
    cond_branches ++;
    if(branch_bits[40] == 2 || branch_bits[40] == 3)
    {
        mispredictions++;
        branch_bits[40]--;
    }
    else if(branch_bits[40] == 1)
    {
        branch_bits[40]--;
    }
    counters[93] ++;
    ldr4000(&r1.i, &r5.i, 0);
    r3.i = 0;
    lr.i = 43691;
    r4.i = 21845;
    lr.i = lr.i | (43690 << 16);
    r4.i = r4.i | (21845 << 16);
    r0.i = r3.i;
    r2.i = r5.i;
L100:
    counters[94] ++;
    tmp = r3.i & 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    r3.i = r3.i + (1);
    if (!z)
    {
        r0.i = r0.i - (r1.i);
    }
    if (z)
    {
        ldr4000(&r1.i, &r2.i, 0);
    }
    ip.i = (lr.i) * (r3.i);
    if (z)
    {
        r0.i = r0.i + (r1.i);
    }
    tmp = r3.i - 10;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 10);
    v = (r3.i&0x80000000) != (10&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        pop(6, &pc.i, &r8.i, &r7.i, &r6.i, &r5.i, &r4.i);
        cond_branches ++;
        if(branch_bits[41] == 0 || branch_bits[41] == 1)
        {
            mispredictions++;
            branch_bits[41]++;
        }
        else if(branch_bits[41] == 2)
        {
            branch_bits[41]++;
        }
        return;
    }
    cond_branches ++;
    if(branch_bits[41] == 2 || branch_bits[41] == 3)
    {
        mispredictions++;
        branch_bits[41]--;
    }
    else if(branch_bits[41] == 1)
    {
        branch_bits[41]--;
    }
    counters[95] ++;
    ldr4100(&r1.i, &r2.i, 4);
    tmp = ip.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r4.i);
    v = (ip.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (c && !z)
    {
        r0.i = (r1.i) * (r0.i);
    }
    goto L100;
    return;
}

void fib()
{
    counters[96] ++;
    tmp = r0.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 1);
    v = (r0.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (z || n != v)
    {
        cond_branches ++;
        if(branch_bits[42] == 0 || branch_bits[42] == 1)
        {
            mispredictions++;
            branch_bits[42]++;
        }
        else if(branch_bits[42] == 2)
        {
            branch_bits[42]++;
        }
        return;
    }
    cond_branches ++;
    if(branch_bits[42] == 2 || branch_bits[42] == 3)
    {
        mispredictions++;
        branch_bits[42]--;
    }
    else if(branch_bits[42] == 1)
    {
        branch_bits[42]--;
    }
    counters[97] ++;
    push(6, &r4.i, &r5.i, &r6.i, &r7.i, &r8.i, &lr.i);
    r7.i = r0.i - (2);
    r6.i = r0.i - (3);
    r3.i = r7.i & ~1;
    r5.i = r0.i - (1);
    r6.i = r6.i - (r3.i);
    r4.i = 0;
L110:
    counters[98] ++;
    r0.i = r5.i;
    r5.i = r5.i - (2);
    fib();
    counters[99] ++;
    tmp = r5.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r6.i);
    v = (r5.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    r4.i = r4.i + (r0.i);
    if (!z)
    {
        cond_branches ++;
        if(branch_bits[43] == 0 || branch_bits[43] == 1)
        {
            mispredictions++;
            branch_bits[43]++;
        }
        else if(branch_bits[43] == 2)
        {
            branch_bits[43]++;
        }
        goto L110;
    }
    cond_branches ++;
    if(branch_bits[43] == 2 || branch_bits[43] == 3)
    {
        mispredictions++;
        branch_bits[43]--;
    }
    else if(branch_bits[43] == 1)
    {
        branch_bits[43]--;
    }
    counters[100] ++;
    r0.i = r7.i & 1;
    r0.i = r0.i + (r4.i);
    pop(6, &pc.i, &r8.i, &r7.i, &r6.i, &r5.i, &r4.i);
    return;

}

void main()
{
    malloc_start();
    counters[101] ++;
    ip.i = (LC0 & 0xffff);
    ip.i = ip.i | (((uint32_t)LC0 >> 16) << 16);
    push(5, &r4.i, &r5.i, &r6.i, &r7.i, &lr.i);
    sp.i = sp.i - (44);
    ldm1(&ip.i, 4, &r0.i, &r1.i, &r2.i, &r3.i);
    lr.i = sp.i;
    stm1(&lr.i, 4, &r0.i, &r1.i, &r2.i, &r3.i);
    ldm1(&ip.i, 4, &r0.i, &r1.i, &r2.i, &r3.i);
    stm1(&lr.i, 4, &r0.i, &r1.i, &r2.i, &r3.i);
    ldm0(&ip.i, 2, &r0.i, &r1.i);
    stm0(&lr.i, 2, &r0.i, &r1.i);
    r0.i = sp.i;
    test();
    counters[102] ++;
    r1.i = (LC3 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC3 >> 16) << 16);
    r6.i = (r0.i) * (r0.i);
    r3.i = r0.i;
    r0.i = 1;
    r6.i = (r6.i) * (r3.i);
    r6.i = (r6.i) * (r6.i);
    r6.i = (r3.i) * (r6.i);
    r2.i = r6.i;
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[103] ++;
    tmp = r6.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) 0);
    v = (r6.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    if (z)
    {
        cond_branches ++;
        if(branch_bits[44] == 0 || branch_bits[44] == 1)
        {
            mispredictions++;
            branch_bits[44]++;
        }
        else if(branch_bits[44] == 2)
        {
            branch_bits[44]++;
        }
        goto L118;
    }
    cond_branches ++;
    if(branch_bits[44] == 2 || branch_bits[44] == 3)
    {
        mispredictions++;
        branch_bits[44]--;
    }
    else if(branch_bits[44] == 1)
    {
        branch_bits[44]--;
    }
    counters[104] ++;
    r1.i = 26215;
    r1.i = r1.i | (26214 << 16);
    r4.i = r6.i;
    r5.i = 0;
    r0.i = 10;
L119:
    counters[105] ++;
    smull(&r3.i, &r2.i, &r1.i, &r4.i);
    r3.i = r4.i >> 31;
    r3.i = (r2.i >> 2) - r3.i;
    r2.i = r4.i - ((r0.i) * (r3.i));
    r4.i = r3.i - (0);
    z = r4.i == 0;
    n = r4.i & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (r4.i&0x80000000) != (r3.i&0x80000000);
    r5.i = r5.i + (r2.i);
    if (!z)
    {
        cond_branches ++;
        if(branch_bits[45] == 0 || branch_bits[45] == 1)
        {
            mispredictions++;
            branch_bits[45]++;
        }
        else if(branch_bits[45] == 2)
        {
            branch_bits[45]++;
        }
        goto L119;
    }
    cond_branches ++;
    if(branch_bits[45] == 2 || branch_bits[45] == 3)
    {
        mispredictions++;
        branch_bits[45]--;
    }
    else if(branch_bits[45] == 1)
    {
        branch_bits[45]--;
    }
    counters[106] ++;
    r2.i = r5.i;
    r1.i = (LC4 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC4 >> 16) << 16);
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[107] ++;
    r1.i = (r5.i) * (r5.i);
    r0.i = r6.i;
    idiv();
    counters[108] ++;
    r1.i = (LC5 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC5 >> 16) << 16);
    r2.i = r0.i;
    r6.i = r0.i;
    r0.i = 1;
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[109] ++;
    tmp = r5.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) 1);
    v = (r5.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (z || n != v)
    {
        cond_branches ++;
        if(branch_bits[46] == 0 || branch_bits[46] == 1)
        {
            mispredictions++;
            branch_bits[46]++;
        }
        else if(branch_bits[46] == 2)
        {
            branch_bits[46]++;
        }
        goto L141;
    }
    cond_branches ++;
    if(branch_bits[46] == 2 || branch_bits[46] == 3)
    {
        mispredictions++;
        branch_bits[46]--;
    }
    else if(branch_bits[46] == 1)
    {
        branch_bits[46]--;
    }
    counters[110] ++;
    r7.i = r5.i - (2);
    r1.i = r5.i - (3);
    r3.i = r7.i & ~1;
    r2.i = r5.i - (1);
    r1.i = r1.i - (r3.i);
L123:
    counters[111] ++;
    r0.i = r2.i;
    r2.i = r2.i - (2);
    fib();
    counters[112] ++;
    tmp = r2.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r1.i);
    v = (r2.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    r4.i = r4.i + (r0.i);
    if (!z)
    {
        cond_branches ++;
        if(branch_bits[47] == 0 || branch_bits[47] == 1)
        {
            mispredictions++;
            branch_bits[47]++;
        }
        else if(branch_bits[47] == 2)
        {
            branch_bits[47]++;
        }
        goto L123;
    }
    cond_branches ++;
    if(branch_bits[47] == 2 || branch_bits[47] == 3)
    {
        mispredictions++;
        branch_bits[47]--;
    }
    else if(branch_bits[47] == 1)
    {
        branch_bits[47]--;
    }
    counters[113] ++;
    r0.i = r7.i & 1;
L124:
    counters[114] ++;
    r0.i = r4.i + (r0.i);
    r1.i = r5.i;
    idiv();
    counters[115] ++;
    r1.i = r0.i;
    r0.i = r6.i;
    idiv();
    counters[116] ++;
    tmp = r0.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 1);
    v = (r0.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    r4.i = r0.i;
    if (z || n != v)
    {
        cond_branches ++;
        if(branch_bits[48] == 0 || branch_bits[48] == 1)
        {
            mispredictions++;
            branch_bits[48]++;
        }
        else if(branch_bits[48] == 2)
        {
            branch_bits[48]++;
        }
        goto L121;
    }
    cond_branches ++;
    if(branch_bits[48] == 2 || branch_bits[48] == 3)
    {
        mispredictions++;
        branch_bits[48]--;
    }
    else if(branch_bits[48] == 1)
    {
        branch_bits[48]--;
    }
    counters[117] ++;
    tmp = r0.i - 2;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 2);
    v = (r0.i&0x80000000) != (2&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (z)
    {
        cond_branches ++;
        if(branch_bits[49] == 0 || branch_bits[49] == 1)
        {
            mispredictions++;
            branch_bits[49]++;
        }
        else if(branch_bits[49] == 2)
        {
            branch_bits[49]++;
        }
        goto L125;
    }
    cond_branches ++;
    if(branch_bits[49] == 2 || branch_bits[49] == 3)
    {
        mispredictions++;
        branch_bits[49]--;
    }
    else if(branch_bits[49] == 1)
    {
        branch_bits[49]--;
    }
    counters[118] ++;
    tmp = r0.i & 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    if (z)
    {
        cond_branches ++;
        if(branch_bits[50] == 0 || branch_bits[50] == 1)
        {
            mispredictions++;
            branch_bits[50]++;
        }
        else if(branch_bits[50] == 2)
        {
            branch_bits[50]++;
        }
        goto L121;
    }
    cond_branches ++;
    if(branch_bits[50] == 2 || branch_bits[50] == 3)
    {
        mispredictions++;
        branch_bits[50]--;
    }
    else if(branch_bits[50] == 1)
    {
        branch_bits[50]--;
    }
L125:
    counters[119] ++;
    r1.i = 10;
    r0.i = r4.i;
    Millerpart0();
    counters[120] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        cond_branches ++;
        if(branch_bits[51] == 0 || branch_bits[51] == 1)
        {
            mispredictions++;
            branch_bits[51]++;
        }
        else if(branch_bits[51] == 2)
        {
            branch_bits[51]++;
        }
        goto L142;
    }
    cond_branches ++;
    if(branch_bits[51] == 2 || branch_bits[51] == 3)
    {
        mispredictions++;
        branch_bits[51]--;
    }
    else if(branch_bits[51] == 1)
    {
        branch_bits[51]--;
    }
L121:
    counters[121] ++;
    r1.i = (LC7 & 0xffff);
    r2.i = r4.i;
    r1.i = r1.i | (((uint32_t)LC7 >> 16) << 16);
    r0.i = 1;
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
L126:
    counters[122] ++;
    r2.i = r4.i;
    r1.i = (LC8 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC8 >> 16) << 16);
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[123] ++;
    r0.i = 0;
    sp.i = sp.i + (44);
    pop(5, &pc.i, &r7.i, &r6.i, &r5.i, &r4.i);
    counter_summary();
    return;
L142:
    counters[124] ++;
    r1.i = (LC6 & 0xffff);
    r2.i = r4.i;
    r1.i = r1.i | (((uint32_t)LC6 >> 16) << 16);
    r0.i = 1;
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[125] ++;
    goto L126;
L141:
    counters[126] ++;
    r0.i = r5.i;
    goto L124;
L118:
    counters[127] ++;
    r2.i = r6.i;
    r1.i = (LC4 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC4 >> 16) << 16);
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[128] ++;
    r1.i = r6.i;
    r0.i = r6.i;
    idiv();
    counters[129] ++;
    r1.i = (LC5 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC5 >> 16) << 16);
    r2.i = r0.i;
    r0.i = 1;
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[130] ++;
    return;
}