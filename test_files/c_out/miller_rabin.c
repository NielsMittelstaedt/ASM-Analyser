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

int32_t LC0, LC1;

int load_counter = 0, store_counter = 0;
int counters[70] = { 0 };
int block_sizes[70] = {8,3,5,1,2,3,4,1,1,3,3,3,3,2,2,1,3,4,1,4,1,1,3,3,3,3,2,2,6,1,3,1,2,2,1,1,2,2,1,3,1,5,2,2,4,1,1,3,3,3,2,2,4,2,4,1,1,3,3,3,2,2,2,2,2,1,2,5,10,2};

int cond_branches = 0, mispredictions = 0;
uint8_t branch_bits[29] = {0};

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
void idivmod()
{
    int32_t quot = r0.i / r1.i;
    int32_t rem = r0.i % r1.i;
    r0.i = quot;
    r1.i = rem;
}
void rand_help()
{
    r0.i = rand();
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
    malloc_0 = (uint8_t*) malloc(20054);
    sp.i = 19996;
    fp = sp;
    LC0 = 20000;
    strcpy(malloc_0+LC0, "\012%d is prime\012\000");

    LC1 = 20025;
    strcpy(malloc_0+LC1, "\012%d is not prime\012\000");

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

void main()
{
    malloc_start();
    counters[67] ++;
    r1.i = 50000;
    r0.i = 6167;
    push(2, &r4.i, &lr.i);
    r0.i = r0.i | (525 << 16);
    Millerpart0();
    counters[68] ++;
    r2.i = 6167;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    r0.i = 1;
    if (!z)
    {
        r2.i = r2.i | (525 << 16);
    }
    if (z)
    {
        r2.i = r2.i | (525 << 16);
    }
    if (!z)
    {
        r1.i = (LC0 & 0xffff);
    }
    if (z)
    {
        r1.i = (LC1 & 0xffff);
    }
    if (!z)
    {
        r1.i = r1.i | (((uint32_t)LC0 >> 16) << 16);
    }
    if (z)
    {
        r1.i = r1.i | (((uint32_t)LC1 >> 16) << 16);
    }
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[69] ++;
    r0.i = 0;
    pop(2, &pc.i, &r4.i);
    counter_summary();
    return;

}