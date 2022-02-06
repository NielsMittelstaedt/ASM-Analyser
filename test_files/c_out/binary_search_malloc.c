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


int load_counter = 0, store_counter = 0;
int counters[16] = { 0 };
int block_sizes[16] = {4,5,1,3,2,3,1,3,10,5,1,3,1,2,3,1};

int cond_branches = 0, mispredictions = 0;
uint8_t branch_bits[9] = {0};

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
void str8000(int32_t *target1, int32_t *target2, int32_t *address, int32_t offset)
{
    *((uint32_t*)(malloc_0+*address+offset)) = *target1;
    *((uint32_t*)(malloc_0+*address+offset+4)) = *target2;
    store_counter += 2;
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
void str4100(int32_t *target, int32_t *address, int32_t offset)
{
    *((uint32_t*)(malloc_0+*address+offset)) = *target;
    *address += offset;
    store_counter ++;
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
    malloc_0 = (uint8_t*) malloc(20000);
    sp.i = 19996;
    fp = sp;
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
        return;
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
    counters[2] ++;
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
    counters[3] ++;
    r2.i = r0.i - (1);
    tmp = r2.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r1.i);
    v = (r2.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n == v)
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
        goto L2;
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
        goto L2;
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
    counters[6] ++;
    goto L8;
    return;
}

void main()
{
    malloc_start();
    counters[7] ++;
    push(4, &r4.i, &r5.i, &r6.i, &lr.i);
    r0.i = 20;
    malloc_help();
    counters[8] ++;
    r2.i = 0;
    r1.i = 4;
    r4.i = 2;
    r5.i = 3;
    r3.i = 40;
    str8000(&r4.i, &r5.i, &r0.i, 0);
    r4.i = 4;
    r5.i = 10;
    str4000(&r3.i, &r0.i, 16);
    str8000(&r4.i, &r5.i, &r0.i, 8);
L11:
    counters[9] ++;
    r3.i = r1.i - (r2.i);
    r3.i = r2.i + ((r3.i >> 1));
    ldr4000(&ip.i, &r0.i, ((uint32_t)r3.i << 2));
    tmp = ip.i - 10;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) 10);
    v = (ip.i&0x80000000) != (10&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
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
    counters[10] ++;
    if (z || n != v)
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
    counters[11] ++;
    r1.i = r3.i - (1);
    tmp = r1.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r2.i);
    v = (r1.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (n == v)
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
        goto L11;
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
    counters[12] ++;
    free_help();
    counters[13] ++;
    r0.i = 0;
    pop(4, &pc.i, &r6.i, &r5.i, &r4.i);
    counter_summary();
    return;
L13:
    counters[14] ++;
    r2.i = r3.i + (1);
    tmp = r2.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r1.i);
    v = (r2.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
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
        goto L11;
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
    counters[15] ++;
    goto L12;
    return;
}