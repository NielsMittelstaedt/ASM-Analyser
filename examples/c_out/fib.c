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

reg r7, r3, r8, r5, r0, r6, r1, r4;


int counters[12] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[12] = {2,7,3,3,3,3,2,2,2,2,2,2};

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
    char filename[] = "fib.c";

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


void fib()
{
    counters[0] ++;
    tmp = r0.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 1);
    v = (r0.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (z || n != v)
    {
        return;
    }
    counters[1] ++;
    store_counter ++;
    sp.i -= 24;
    str(&r4.i, &sp.i, 0*4, 4, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false);
    str(&r7.i, &sp.i, 3*4, 4, false, false);
    str(&r8.i, &sp.i, 4*4, 4, false, false);
    str(&lr.i, &sp.i, 5*4, 4, false, false);
    r7.i = r0.i - 2;
    r6.i = r0.i - 3;
    r3.i = r7.i & ~1;
    r5.i = r0.i - 1;
    r6.i = r6.i - r3.i;
    r4.i = 0;
L3:
    counters[2] ++;
    r0.i = r5.i;
    r5.i = r5.i - 2;
    fib();
    counters[3] ++;
    tmp = r5.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r6.i);
    v = (r5.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    r4.i = r4.i + r0.i;
    if (!z)
    {
        goto L3;
    }
    counters[4] ++;
    r0.i = r7.i & 1;
    r0.i = r0.i + r4.i;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false);
    ldr(&r7.i, &sp.i, 3*4, 4, false, false);
    ldr(&r8.i, &sp.i, 4*4, 4, false, false);
    ldr(&pc.i, &sp.i, 5*4, 4, false, false);
    sp.i += 24;
    return;

}

void main()
{
    malloc_start();
    counters[5] ++;
    store_counter ++;
    sp.i -= 8;
    str(&r4.i, &sp.i, 0*4, 4, false, false);
    str(&lr.i, &sp.i, 1*4, 4, false, false);
    r0.i = 5;
    fib();
    counters[6] ++;
    r0.i = 3;
    fib();
    counters[7] ++;
    r0.i = 1;
    fib();
    counters[8] ++;
    r0.i = 3;
    fib();
    counters[9] ++;
    r0.i = 1;
    fib();
    counters[10] ++;
    r0.i = 1;
    fib();
    counters[11] ++;
    r0.i = 0;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false);
    ldr(&pc.i, &sp.i, 1*4, 4, false, false);
    sp.i += 8;
    counter_summary();
    return;

}

