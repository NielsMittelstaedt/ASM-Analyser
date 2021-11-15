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
char* malloc_0 = 0;

reg r1, r2, r3, r0;

int32_t LC1, LC0;

int counters[13] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[13] = {11,18,2,8,6,2,6,2,1,3,21,5,4};

void ldr(int32_t *target, int32_t *address, int32_t offset, int bytes, bool update, bool post_index)
{
    char *ptr;
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
    char *ptr;
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
    malloc_0 = (char*) malloc(1);
    char* stack_ptr = (char*) malloc(1000);
    sp.i = (int32_t) (stack_ptr - malloc_0) + 999;
    fp = sp;

    LC1 = (int32_t) ((char*) malloc(22) - malloc_0);
    strcpy(malloc_0+LC1, "Ergebnis: %d\012\000");

    LC0 = (int32_t) ((char*) malloc(5*sizeof(int32_t)) - malloc_0);
    int32_t arrayLC0[] = {2,3,4,10,40};
    for(int i=0; i<5; i++) str(&arrayLC0[i], &LC0, i*4, false, false, false);
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
    store_counter ++;
    sp.i -= 8;
    str(&fp.i, &sp.i, 0*4, 4, false, false);
    str(&lr.i, &sp.i, 1*4, 4, false, false);
    fp.i = sp.i + 4;
    sp.i = sp.i - 24;
    store_counter ++;
    str(&r0.i, &fp.i, -16, 4, false, false);
    store_counter ++;
    str(&r1.i, &fp.i, -20, 4, false, false);
    store_counter ++;
    str(&r2.i, &fp.i, -24, 4, false, false);
    store_counter ++;
    str(&r3.i, &fp.i, -28, 4, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -24, 4, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n != v)
    {
        goto L2;
    }
    counters[1] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -24, 4, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false);
    r3.i = r2.i - r3.i;
    r2.i = (uint32_t)r3.i >> 31;
    r3.i = r2.i + r3.i;
    r3.i = r3.i >> 1;
    r2.i = r3.i;
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false);
    r3.i = r3.i + r2.i;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -16, 4, false, false);
    r3.i = r2.i + r3.i;
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -28, 4, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z)
    {
        goto L3;
    }
    counters[2] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false);
    goto L4;
L3:
    counters[3] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -16, 4, false, false);
    r3.i = r2.i + r3.i;
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, true);
    load_counter ++;
    ldr(&r2.i, &fp.i, -28, 4, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n == v)
    {
        goto L5;
    }
    counters[4] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false);
    r2.i = r3.i - 1;
    load_counter ++;
    ldr(&r3.i, &fp.i, -28, 4, false, false);
    load_counter ++;
    ldr(&r1.i, &fp.i, -20, 4, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, -16, 4, false, false);
    binarySearch();
    counters[5] ++;
    r3.i = r0.i;
    goto L4;
L5:
    counters[6] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false);
    r1.i = r3.i + 1;
    load_counter ++;
    ldr(&r3.i, &fp.i, -28, 4, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -24, 4, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, -16, 4, false, false);
    binarySearch();
    counters[7] ++;
    r3.i = r0.i;
    goto L4;
L2:
    counters[8] ++;
    r3.i = ~0;
L4:
    counters[9] ++;
    r0.i = r3.i;
    sp.i = fp.i - 4;
    load_counter ++;
    ldr(&fp.i, &sp.i, 0*4, 4, false, false);
    ldr(&pc.i, &sp.i, 1*4, 4, false, false);
    sp.i += 8;
    return;

}

void main()
{
    malloc_start();
    counters[10] ++;
    store_counter ++;
    sp.i -= 8;
    str(&fp.i, &sp.i, 0*4, 4, false, false);
    str(&lr.i, &sp.i, 1*4, 4, false, false);
    fp.i = sp.i + 4;
    sp.i = sp.i - 32;
    r3.i = (LC0 & 0xffff);
    r3.i = r3.i | (((uint32_t)LC0 >> 16) << 16);
    ip.i = fp.i - 36;
    lr.i = r3.i;
    load_counter ++;
    ldr(&r0.i, &lr.i, 0*4, 4, false, false);
    ldr(&r1.i, &lr.i, 1*4, 4, false, false);
    ldr(&r2.i, &lr.i, 2*4, 4, false, false);
    ldr(&r3.i, &lr.i, 3*4, 4, false, false);
    lr.i += 16;
    store_counter ++;
    str(&r0.i, &ip.i, 0*4, 4, false, false);
    str(&r1.i, &ip.i, 1*4, 4, false, false);
    str(&r2.i, &ip.i, 2*4, 4, false, false);
    str(&r3.i, &ip.i, 3*4, 4, false, false);
    ip.i += 16;
    load_counter ++;
    ldr(&r3.i, &lr.i, 0, 4, false, true);
    store_counter ++;
    str(&r3.i, &ip.i, 0, 4, false, true);
    r3.i = 5;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false);
    r3.i = 40;
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false);
    r2.i = r3.i - 1;
    r0.i = fp.i - 36;
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false);
    r1.i = 0;
    binarySearch();
    counters[11] ++;
    store_counter ++;
    str(&r0.i, &fp.i, -16, 4, false, false);
    load_counter ++;
    ldr(&r1.i, &fp.i, -16, 4, false, false);
    r0.i = (LC1 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC1 >> 16) << 16);
    printf(malloc_0+r0.i, r1.i);
    counters[12] ++;
    r3.i = 0;
    r0.i = r3.i;
    sp.i = fp.i - 4;
    load_counter ++;
    ldr(&fp.i, &sp.i, 0*4, 4, false, false);
    ldr(&pc.i, &sp.i, 1*4, 4, false, false);
    sp.i += 8;
    counter_summary();
    return;

}

