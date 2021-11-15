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

int32_t tmp;
reg sp, fp, lr, pc, ip;
bool z, n, c, v;
uint8_t* malloc_0 = 0;

reg r3, r0, r1, r2;


int counters[6] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[6] = {2,3,4,1,2,2};

void ldr(int32_t *target, int32_t *address, int32_t offset, int bytes, bool update, bool post_index)
{
    uint8_t *ptr;
    ptr = malloc_0 + *address;
    *target = 0;

    if (!post_index)
        ptr += offset;

    for(int j=0; j<bytes; j++)
        *target += (*(ptr+j) << 8*j) & (0xff << 8*j);

    if (update || post_index)
        *address += offset;
}

void str(int32_t *target, int32_t *address, int32_t offset, int bytes, bool update, bool post_index)
{
    uint8_t *ptr;
    ptr = malloc_0 + *address;

    if (!post_index)
        ptr += offset;

    for(int j=0; j<bytes; j++)
        *(ptr+j) = (*target >> (8*j)) & 0xff;

    if(update || post_index)
        *address += offset;
}

void malloc_start()
{
    malloc_0 = (uint8_t*) malloc(1);
    uint8_t* stack_ptr = (uint8_t*) malloc(1000);
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
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (z || n != v)
    {
        goto L4;
    }
    counters[1] ++;
    r2.i = r0.i + 1;
    r3.i = 1;
    r0.i = 0;
L3:
    counters[2] ++;
    r0.i = r0.i + r3.i;
    r3.i = r3.i + 1;
    tmp = r3.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r2.i);
    v = (r3.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L3;
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

