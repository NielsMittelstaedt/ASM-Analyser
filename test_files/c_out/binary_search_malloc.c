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

reg r5, r3, r1, r0, r6, r4, r2;


int counters[15] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[15] = {4,6,3,2,3,1,3,10,5,1,3,1,2,3,1};

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
    char filename[] = "binary_search_malloc.c";

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

void free_help()
{
    free(malloc_0+r0.i);
}
void malloc_help()
{
    uint8_t* ptr = (uint8_t*) malloc(r0.i);
    r0.i = (int32_t) (ptr - malloc_0);
}

void binarySearch()
{
    counters[0] ++;
    tmp = r1.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r2.i);
    v = (r1.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    store_counter ++;
    str(&lr.i, &sp.i, -4, 4, true, false);
    lr.i = r0.i;
    if (!z && n == v)
    {
        goto L8;
    }
L2:
    counters[1] ++;
    r0.i = r2.i - r1.i;
    r0.i = r1.i + (r0.i >> 1);
    load_counter ++;
    ldr(&ip.i, &lr.i, ((uint32_t)r0.i << 2), 4, false, false);
    tmp = ip.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r3.i);
    v = (ip.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    load_counter ++;
    if (z)
    {
        ldr(&pc.i, &sp.i, 4, 4, false, true);
    }
    if (z || n != v)
    {
        goto L4;
    }
    counters[2] ++;
    r2.i = r0.i - 1;
    tmp = r2.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r1.i);
    v = (r2.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n == v)
    {
        goto L2;
    }
L8:
    counters[3] ++;
    r0.i = ~0;
    load_counter ++;
    ldr(&pc.i, &sp.i, 4, 4, false, true);
L4:
    counters[4] ++;
    r1.i = r0.i + 1;
    tmp = r1.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r2.i);
    v = (r1.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (z || n != v)
    {
        goto L2;
    }
    counters[5] ++;
    goto L8;
    return;
}

void main()
{
    malloc_start();
    counters[6] ++;
    store_counter ++;
    sp.i -= 16;
    str(&r4.i, &sp.i, 0*4, 4, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false);
    str(&lr.i, &sp.i, 3*4, 4, false, false);
    r0.i = 20;
    malloc_help();
    counters[7] ++;
    r2.i = 0;
    r1.i = 4;
    r4.i = 2;
    r5.i = 3;
    r3.i = 40;
    store_counter ++;
    str(&r4.i, &r0.i, 0, 8, false, true);
    r4.i = 4;
    r5.i = 10;
    store_counter ++;
    str(&r3.i, &r0.i, 16, 4, false, false);
    store_counter ++;
    str(&r4.i, &r0.i, 8, 8, false, false);
L11:
    counters[8] ++;
    r3.i = r1.i - r2.i;
    r3.i = r2.i + (r3.i >> 1);
    load_counter ++;
    ldr(&ip.i, &r0.i, ((uint32_t)r3.i << 2), 4, false, false);
    tmp = ip.i - 10;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) 10);
    v = (ip.i&0x80000000) != (10&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (z)
    {
        goto L12;
    }
    counters[9] ++;
    if (z || n != v)
    {
        goto L13;
    }
    counters[10] ++;
    r1.i = r3.i - 1;
    tmp = r1.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r2.i);
    v = (r1.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (n == v)
    {
        goto L11;
    }
L12:
    counters[11] ++;
    free_help();
    counters[12] ++;
    r0.i = 0;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false);
    ldr(&pc.i, &sp.i, 3*4, 4, false, false);
    sp.i += 16;
    return;
L13:
    counters[13] ++;
    r2.i = r3.i + 1;
    tmp = r2.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r1.i);
    v = (r2.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (z || n != v)
    {
        goto L11;
    }
    counters[14] ++;
    goto L12;
    counter_summary();
    return;
}

