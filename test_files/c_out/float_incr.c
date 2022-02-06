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
int counters[5] = { 0 };
int block_sizes[5] = {2,5,1,1,2};

int cond_branches = 0, mispredictions = 0;

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
void d2f()
{
    uint64_t uint64_t_val = ((uint64_t)(uint32_t) r1.i) << 32 | ((uint64_t)(uint32_t) r0.i);
    double double_val = *(double *)&uint64_t_val;
    r0.f = (float) double_val;
}
void f2d()
{
    double double_val = (double) r0.f;
    uint64_t uint64_t_val = *(uint64_t *)&double_val;
    r1.i = (uint32_t) (uint64_t_val >> 32);
    r0.i = (uint32_t) uint64_t_val;
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
    push(2, &r4.i, &lr.i);
    f2d();
    counters[1] ++;
    r2.i = 3626;
    r3.i = 4829;
    r2.i = r2.i | (21078 << 16);
    r3.i = r3.i | (16385 << 16);
    dadd();
    counters[2] ++;
    d2f();
    counters[3] ++;
    pop(2, &pc.i, &r4.i);
    return;

}

void main()
{
    malloc_start();
    counters[4] ++;
    r0.i = 0;
    counter_summary();
    return;

}