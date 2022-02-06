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

int32_t LC1, LC0;

int load_counter = 0, store_counter = 0;
int counters[27] = { 0 };
int block_sizes[27] = {8,3,7,2,4,2,3,2,3,5,5,2,6,3,7,2,7,2,5,2,3,2,1,16,4,2,3};

int cond_branches = 0, mispredictions = 0;
uint8_t branch_bits[12] = {0};

void memcpy_help()
{
    memcpy(malloc_0+r0.i, malloc_0+r1.i, r2.i);
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
void malloc_help()
{
    uint8_t* ptr = (uint8_t*) malloc(r0.i);
    r0.i = (int32_t) (ptr - malloc_0);
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
void free_help()
{
    free(malloc_0+r0.i);
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
    malloc_0 = (uint8_t*) malloc(20033);
    sp.i = 19996;
    fp = sp;
    LC1 = 20000;
    strcpy(malloc_0+LC1, "%d \000");

    LC0 = 20009;
    int32_t arrayLC0[] = {5,3,0,2,6,1};
    for(int i=0; i<6; i++) *((uint32_t*)(malloc_0+LC0+i*4)) = arrayLC0[i];

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

void mergeSortpart0();
void mergeSort();
void main();

void mergeSortpart0()
{
    counters[0] ++;
    push(10, &r3.i, &r4.i, &r5.i, &r6.i, &r7.i, &r8.i, &r9.i, &r10.i, &fp.i, &lr.i);
    r8.i = (uint32_t)r1.i >> 1;
    fp.i = r0.i;
    r7.i = r1.i - (((uint32_t)r1.i >> 1));
    r4.i = (uint32_t)r8.i << 2;
    r5.i = (uint32_t)r7.i << 2;
    r0.i = r4.i;
    malloc_help();
    counters[1] ++;
    r9.i = r0.i;
    r0.i = r5.i;
    malloc_help();
    counters[2] ++;
    tmp = r8.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) 0);
    v = (r8.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    r1.i = fp.i;
    if (!z && n == v)
    {
        r2.i = r4.i;
    }
    if (z || n != v)
    {
        r2.i = 4;
    }
    r10.i = r0.i;
    r0.i = r9.i;
    memcpy_help();
    counters[3] ++;
    tmp = r7.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r7.i) >= ((uint32_t) 0);
    v = (r7.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
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
        goto L5;
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
    r1.i = fp.i + (r4.i);
    r2.i = r5.i;
    r0.i = r10.i;
    memcpy_help();
L5:
    counters[5] ++;
    tmp = r8.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) 1);
    v = (r8.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
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
    counters[6] ++;
    r1.i = r8.i;
    r0.i = r9.i;
    mergeSortpart0();
L3:
    counters[7] ++;
    tmp = r7.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r7.i) >= ((uint32_t) 1);
    v = (r7.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
    if (!c || z)
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
        goto L6;
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
    counters[8] ++;
    r1.i = r7.i;
    r0.i = r10.i;
    mergeSortpart0();
L6:
    counters[9] ++;
    tmp = r7.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r7.i) >= ((uint32_t) 0);
    v = (r7.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
    if (z || n != v)
    {
        r4.i = 0;
    }
    if (z || n != v)
    {
        r5.i = r4.i;
    }
    if (z || n != v)
    {
        r6.i = r4.i;
    }
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
    counters[10] ++;
    ldr4000(&r2.i, &r9.i, 0);
    r4.i = 0;
    ldr4000(&r3.i, &r10.i, 0);
    r6.i = r4.i;
    r5.i = r4.i;
L7:
    counters[11] ++;
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (c && !z)
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
        goto L10;
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
L26:
    counters[12] ++;
    r5.i = r5.i + (1);
    str4000(&r2.i, &fp.i, ((uint32_t)r4.i << 2));
    tmp = r8.i - r5.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) r5.i);
    v = (r8.i&0x80000000) != (r5.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    if (!z && n == v)
    {
        tmp = r7.i - r6.i;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r7.i) >= ((uint32_t) r6.i);
        v = (r7.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
    }
    r4.i = r4.i + (1);
    if (z || n != v)
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
        goto L12;
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
    ldr4000(&r2.i, &r9.i, ((uint32_t)r5.i << 2));
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!c || z)
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
        goto L26;
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
L10:
    counters[14] ++;
    r6.i = r6.i + (1);
    str4000(&r3.i, &fp.i, ((uint32_t)r4.i << 2));
    tmp = r8.i - r5.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) r5.i);
    v = (r8.i&0x80000000) != (r5.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    if (!z && n == v)
    {
        tmp = r7.i - r6.i;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r7.i) >= ((uint32_t) r6.i);
        v = (r7.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
    }
    r4.i = r4.i + (1);
    if (!z && n == v)
    {
        ldr4000(&r3.i, &r10.i, ((uint32_t)r6.i << 2));
    }
    if (!z && n == v)
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
        goto L7;
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
L12:
    counters[15] ++;
    tmp = r8.i - r5.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) r5.i);
    v = (r8.i&0x80000000) != (r5.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
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
        goto L9;
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
L8:
    counters[16] ++;
    r2.i = r8.i - (r5.i);
    r0.i = fp.i + (((uint32_t)r4.i << 2));
    r1.i = r9.i + (((uint32_t)r5.i << 2));
    r4.i = r8.i + (r4.i);
    r2.i = (uint32_t)r2.i << 2;
    r4.i = r4.i - (r5.i);
    memcpy_help();
L9:
    counters[17] ++;
    tmp = r7.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r7.i) >= ((uint32_t) r6.i);
    v = (r7.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
    if (z || n != v)
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
        goto L14;
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
    counters[18] ++;
    r2.i = r7.i - (r6.i);
    r1.i = r10.i + (((uint32_t)r6.i << 2));
    r0.i = fp.i + (((uint32_t)r4.i << 2));
    r2.i = (uint32_t)r2.i << 2;
    memcpy_help();
L14:
    counters[19] ++;
    r0.i = r9.i;
    free_help();
    counters[20] ++;
    r0.i = r10.i;
    pop(10, &lr.i, &fp.i, &r10.i, &r9.i, &r8.i, &r7.i, &r6.i, &r5.i, &r4.i, &r3.i);
    free_help();
    return;

}

void mergeSort()
{
    counters[21] ++;
    tmp = r1.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 1);
    v = (r1.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!c || z)
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
        return;
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
    counters[22] ++;
    mergeSortpart0();
    return;

}

void main()
{
    malloc_start();
    counters[23] ++;
    ip.i = (LC0 & 0xffff);
    ip.i = ip.i | (((uint32_t)LC0 >> 16) << 16);
    push(4, &r4.i, &r5.i, &r6.i, &lr.i);
    sp.i = sp.i - (24);
    ldm1(&ip.i, 4, &r0.i, &r1.i, &r2.i, &r3.i);
    lr.i = sp.i;
    r5.i = (LC1 & 0xffff);
    r6.i = sp.i + (24);
    r5.i = r5.i | (((uint32_t)LC1 >> 16) << 16);
    r4.i = sp.i;
    stm1(&lr.i, 4, &r0.i, &r1.i, &r2.i, &r3.i);
    ldm0(&ip.i, 2, &r0.i, &r1.i);
    stm0(&lr.i, 2, &r0.i, &r1.i);
    r0.i = sp.i;
    r1.i = 6;
    mergeSortpart0();
L30:
    counters[24] ++;
    ldr4010(&r2.i, &r4.i, 4);
    r1.i = r5.i;
    r0.i = 1;
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[25] ++;
    tmp = r4.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r6.i);
    v = (r4.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
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
        goto L30;
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
    r0.i = 0;
    sp.i = sp.i + (24);
    pop(4, &pc.i, &r6.i, &r5.i, &r4.i);
    counter_summary();
    return;

}