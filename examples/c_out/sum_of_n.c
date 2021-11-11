#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

typedef union
{
    int32_t i;
    float f;
} reg;

reg sp, fp, lr, pc, ip;
int32_t cond_reg;
char* malloc_0 = 0;

reg r3, r0, r1, r2;


int counters[6] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[6] = {9,7,4,5,4,3};

void ldr(int32_t *target, int32_t *address, int32_t offset, bool byte, bool update, bool post_index)
{
    int bytes = 1;
    char *ptr;
    ptr = malloc_0 + *address;
    *target = 0;

    if (!post_index)
        ptr += offset;

    if (!byte)
        bytes = 4;

    for(int j=0; j<bytes; j++)
        *target += (*(ptr+j) << 8*j) & (0xff << 8*j);

    if (update || post_index)
        *address += offset;
}

void str(int32_t *target, int32_t *address, int32_t offset, bool byte, bool update, bool post_index)
{
    int bytes = 1;
    char *ptr;
    ptr = malloc_0 + *address;

    if (!post_index)
        ptr += offset;

    if (!byte)
        bytes = 4;

    for(int j=0; j<bytes; j++)
        *(ptr+j) = (*target >> (8*j)) & 0xff;

    if(update || post_index)
        *address += offset;
}

void malloc_start()
{
    malloc_0 = (char*) malloc(1);
    char* stack_ptr = (char*) malloc(1000);
    sp.i = (int32_t) (stack_ptr - malloc_0) + 999;
    fp = sp;

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "sum_of_n.c";

    for (int i = 0; i < basic_blocks; i++)
        total += counters[i] * block_sizes[i];

    printf("\n\nCOUNTING RESULTS of '%s'\n", filename);
    printf("------------------------------------------\n");
    printf("%-40s %8d\n", "Number of basic blocks: ", basic_blocks);
    printf("%-40s %8d\n", "Total instructions executed: ", total);
    printf("%-40s %8d\n", "Total load instructions executed: ", load_counter);
    printf("%-40s %8d\n", "Total store instructions executed: ", store_counter);
    printf("------------------------------------------\n");
}


void f()
{
    counters[0] ++;
    store_counter ++;
    str(&fp.i, &sp.i, -4, false, true, false);
    fp.i = sp.i + 0;
    sp.i = sp.i - 20;
    store_counter ++;
    str(&r0.i, &fp.i, -16, false, false, false);
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -8, false, false, false);
    r3.i = 1;
    store_counter ++;
    str(&r3.i, &fp.i, -12, false, false, false);
    goto L2;
L3:
    counters[1] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -8, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, false, false, false);
    r3.i = r2.i + r3.i;
    store_counter ++;
    str(&r3.i, &fp.i, -8, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, false, false, false);
    r3.i = r3.i + 1;
    store_counter ++;
    str(&r3.i, &fp.i, -12, false, false, false);
L2:
    counters[2] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -12, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, false, false, false);
    cond_reg = r2.i > r3.i ? 1 : (r2.i < r3.i ? -1 : 0);
    if (cond_reg <= 0)
    {
        goto L3;
    }
    counters[3] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, false, false, false);
    r0.i = r3.i;
    sp.i = fp.i + 0;
    load_counter ++;
    ldr(&fp.i, &sp.i, 4, false, false, true);
    return;

}

void main()
{
    malloc_start();
    counters[4] ++;
    store_counter ++;
    sp.i -= 8;
    str(&fp.i, &sp.i, 0*4, false, false, false);
    str(&lr.i, &sp.i, 1*4, false, false, false);
    fp.i = sp.i + 4;
    r0.i = 9;
    f();
    counters[5] ++;
    r3.i = 0;
    r0.i = r3.i;
    load_counter ++;
    ldr(&fp.i, &sp.i, 0*4, false, false, false);
    ldr(&pc.i, &sp.i, 1*4, false, false, false);
    sp.i += 8;
    counter_summary();
    return;

}

