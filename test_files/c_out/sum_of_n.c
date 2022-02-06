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

reg r3, r2, r1, r0, r4;


int load_counter = 0, store_counter = 0;
int counters[6] = { 0 };
int block_sizes[6] = {2,3,4,1,2,2};

int cond_branches = 0, mispredictions = 0;
uint8_t branch_bits[2] = {0};


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

void f();
void main();

void f()
{
    counters[0] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
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
    counters[1] ++;
    r2.i = r0.i + (1);
    r3.i = 1;
    r0.i = 0;
L3:
    counters[2] ++;
    r0.i = r0.i + (r3.i);
    r3.i = r3.i + (1);
    tmp = r3.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r2.i);
    v = (r3.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
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
    counters[3] ++;
    return;
L4:
    counters[4] ++;
    r0.i = 0;
    return;

}

void main()
{
    malloc_start();
    counters[5] ++;
    r0.i = 0;
    counter_summary();
    return;

}