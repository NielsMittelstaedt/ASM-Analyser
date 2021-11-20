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

reg r3, r4, r1, r0, r2, r5;

int32_t LC1, LC0;

int counters[11] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[11] = {2,2,9,2,2,11,7,4,1,4,3};


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

    LC1 = (int32_t) ((uint8_t*) malloc(22) - malloc_0);
    strcpy(malloc_0+LC1, "Ergebnis: %d\012\000");

    LC0 = (int32_t) ((uint8_t*) malloc(5*sizeof(int32_t)) - malloc_0);
    int32_t arrayLC0[] = {2,3,4,10,40};
    for(int i=0; i<5; i++) str(&arrayLC0[i], &LC0, i*4, 4, false, false);
}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "binary_search.c";

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


void binarySearch()
{
    counters[0] ++;
    tmp = r1.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r2.i);
    v = (r1.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!z && n == v)
    {
        goto L13;
    }
    counters[1] ++;
    store_counter ++;
    str(&lr.i, &sp.i, -4, 4, true, false);
    lr.i = r0.i;
L2:
    counters[2] ++;
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
    if (!z && n == v)
    {
        r2.i = r0.i - 1;
    }
    if (z || n != v)
    {
        r1.i = r0.i + 1;
    }
    tmp = r2.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r1.i);
    v = (r2.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n == v)
    {
        goto L2;
    }
    counters[3] ++;
    r0.i = ~0;
    load_counter ++;
    ldr(&pc.i, &sp.i, 4, 4, false, true);
L13:
    counters[4] ++;
    r0.i = ~0;
    return;

}

void main()
{
    malloc_start();
    counters[5] ++;
    store_counter ++;
    sp.i -= 12;
    str(&r4.i, &sp.i, 0*4, 4, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false);
    str(&lr.i, &sp.i, 2*4, 4, false, false);
    r4.i = (LC0 & 0xffff);
    r4.i = r4.i | (((uint32_t)LC0 >> 16) << 16);
    sp.i = sp.i - 28;
    r5.i = sp.i + 4;
    ip.i = 0;
    load_counter ++;
    ldr(&r0.i, &r4.i, 0*4, 4, false, false);
    ldr(&r1.i, &r4.i, 1*4, 4, false, false);
    ldr(&r2.i, &r4.i, 2*4, 4, false, false);
    ldr(&r3.i, &r4.i, 3*4, 4, false, false);
    r4.i += 16;
    lr.i = 4;
    load_counter ++;
    ldr(&r4.i, &r4.i, 0, 4, false, true);
    store_counter ++;
    str(&r0.i, &r5.i, 0*4, 4, false, false);
    str(&r1.i, &r5.i, 1*4, 4, false, false);
    str(&r2.i, &r5.i, 2*4, 4, false, false);
    str(&r3.i, &r5.i, 3*4, 4, false, false);
    r5.i += 16;
    store_counter ++;
    str(&r4.i, &r5.i, 0, 4, false, true);
L15:
    counters[6] ++;
    r2.i = lr.i - ip.i;
    r3.i = sp.i + 24;
    r2.i = ip.i + (r2.i >> 1);
    r3.i = r3.i + ((uint32_t)r2.i << 2);
    load_counter ++;
    ldr(&r3.i, &r3.i, -20, 4, false, false);
    tmp = r3.i - 40;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 40);
    v = (r3.i&0x80000000) != (40&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L16;
    }
    counters[7] ++;
    if (!z && n == v)
    {
        lr.i = r2.i - 1;
    }
    if (z || n != v)
    {
        ip.i = r2.i + 1;
    }
    tmp = ip.i - lr.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) lr.i);
    v = (ip.i&0x80000000) != (lr.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (z || n != v)
    {
        goto L15;
    }
    counters[8] ++;
    r2.i = ~0;
L16:
    counters[9] ++;
    r1.i = (LC1 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC1 >> 16) << 16);
    printf(malloc_0+r1.i, r2.i);
    counters[10] ++;
    r0.i = 0;
    sp.i = sp.i + 28;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false);
    ldr(&pc.i, &sp.i, 2*4, 4, false, false);
    sp.i += 12;
    counter_summary();
    return;

}

