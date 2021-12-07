#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <assert.h>

typedef union
{
    int32_t i;
    float f;
} reg;

int32_t tmp;
reg sp, fp, lr, pc, ip;
bool z, n, c, v;
uint8_t* malloc_0 = 0;

reg r2, r4, r8, r9, r3, r7, r10, r0, r5, r6, r1;

int32_t LC1, LC2, LC0;

int counters[18] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[18] = {2,3,4,13,6,5,2,5,2,5,3,1,3,17,4,4,2,3};


void ldr(int32_t *target, int32_t *address, int32_t offset, int bytes, bool update, bool post_index, bool is_signed)
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

void str(int32_t *target, int32_t *address, int32_t offset, int bytes, bool update, bool post_index, bool is_signed)
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

void print_stack(int32_t start, int32_t bytes)
{
    int32_t size = bytes/4;
    int32_t cur_val = 0;

    for(int32_t i=0; i<size; i++)
    {
        ldr(&cur_val, &start, i*4, 4, false, false, false);
        printf("%d: %d\n", start+i*4, cur_val);
    }
}

void malloc_start()
{
    malloc_0 = (uint8_t*) malloc(20069);
    sp.i = 19996;
    fp = sp;
    LC1 = 20000;
    strcpy(malloc_0+LC1, "Order of Sorted elements: \000");

    LC2 = 20032;
    strcpy(malloc_0+LC2, " %d\000");

    LC0 = 20041;
    int32_t arrayLC0[] = {0,1,2,3,4,5,6};
    for(int i=0; i<7; i++) str(&arrayLC0[i], &LC0, i*4, 4, false, false, false);

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "quicksort.c";

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

void quicksort();
void main();


void quicksort()
{
    counters[0] ++;
    tmp = r1.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r2.i);
    v = (r1.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (n == v)
    {
        return;
    }
    counters[1] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r10.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r9.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r8.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r7.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r6.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r4.i, &sp.i, 0, 4, false, false, false);
    r5.i = r2.i;
    r6.i = r0.i;
L10:
    counters[2] ++;
    r7.i = (uint32_t)r1.i << 2;
    r4.i = r5.i;
    r0.i = r6.i + (r7.i);
    ip.i = r1.i;
L3:
    counters[3] ++;
    tmp = r5.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) ip.i);
    v = (r5.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    load_counter ++;
    ldr(&r2.i, &r6.i, ((uint32_t)ip.i << 2), 4, false, false, false);
    load_counter ++;
    ldr(&lr.i, &r0.i, 0, 4, false, false, false);
    r3.i = (uint32_t)ip.i << 2;
    if (!z && n == v)
    {
        r9.i = 1;
    }
    if (z || n != v)
    {
        r9.i = 0;
    }
    tmp = r2.i - lr.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) lr.i);
    v = (r2.i&0x80000000) != (lr.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    r8.i = r6.i + (r3.i);
    if (!z && n == v)
    {
        r9.i = 0;
    }
    tmp = r9.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r9.i) >= ((uint32_t) 0);
    v = (r9.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r9.i&0x80000000);
    if (!z)
    {
        r3.i = r3.i + (4);
    }
    if (!z)
    {
        r3.i = r6.i + (r3.i);
    }
    if (z)
    {
        goto L9;
    }
L4:
    counters[4] ++;
    r8.i = r3.i;
    load_counter ++;
    ldr(&r2.i, &r3.i, 4, 4, false, true, false);
    ip.i = ip.i + (1);
    tmp = r2.i - lr.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) lr.i);
    v = (r2.i&0x80000000) != (lr.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (z || n != v)
    {
        tmp = ip.i - r5.i;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) ip.i) >= ((uint32_t) r5.i);
        v = (ip.i&0x80000000) != (r5.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    }
    if (n != v)
    {
        goto L4;
    }
L9:
    counters[5] ++;
    load_counter ++;
    ldr(&r10.i, &r6.i, ((uint32_t)r4.i << 2), 4, false, false, false);
    r3.i = (uint32_t)r4.i << 2;
    r9.i = r6.i + (r3.i);
    tmp = r10.i - lr.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r10.i) >= ((uint32_t) lr.i);
    v = (r10.i&0x80000000) != (lr.i&0x80000000) && (tmp&0x80000000) != (r10.i&0x80000000);
    if (z || n != v)
    {
        goto L5;
    }
    counters[6] ++;
    r3.i = r3.i - (4);
    r3.i = r6.i + (r3.i);
L6:
    counters[7] ++;
    r9.i = r3.i;
    load_counter ++;
    ldr(&r10.i, &r3.i, -4, 4, false, true, false);
    r4.i = r4.i - (1);
    tmp = r10.i - lr.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r10.i) >= ((uint32_t) lr.i);
    v = (r10.i&0x80000000) != (lr.i&0x80000000) && (tmp&0x80000000) != (r10.i&0x80000000);
    if (!z && n == v)
    {
        goto L6;
    }
L5:
    counters[8] ++;
    tmp = ip.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r4.i);
    v = (ip.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (n != v)
    {
        goto L19;
    }
    counters[9] ++;
    store_counter ++;
    str(&r10.i, &r6.i, r7.i, 4, false, false, false);
    r2.i = r4.i - (1);
    r0.i = r6.i;
    store_counter ++;
    str(&lr.i, &r9.i, 0, 4, false, false, false);
    quicksort();
    counters[10] ++;
    r1.i = r4.i + (1);
    tmp = r1.i - r5.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r5.i);
    v = (r1.i&0x80000000) != (r5.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (n != v)
    {
        goto L10;
    }
    counters[11] ++;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&r6.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&r7.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&r8.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&r9.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&r10.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;
L19:
    counters[12] ++;
    store_counter ++;
    str(&r10.i, &r8.i, 0, 4, false, false, false);
    store_counter ++;
    str(&r2.i, &r9.i, 0, 4, false, false, false);
    goto L3;
    return;
}

void main()
{
    malloc_start();
    counters[13] ++;
    ip.i = (LC0 & 0xffff);
    ip.i = ip.i | (((uint32_t)LC0 >> 16) << 16);
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r6.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r4.i, &sp.i, 0, 4, false, false, false);
    sp.i = sp.i - (32);
    load_counter ++;
    ldr(&r0.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    ldr(&r1.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    ldr(&r2.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    ldr(&r3.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    lr.i = sp.i + (4);
    r5.i = (LC2 & 0xffff);
    r6.i = sp.i + (28);
    r5.i = r5.i | (((uint32_t)LC2 >> 16) << 16);
    r4.i = sp.i;
    store_counter ++;
    str(&r0.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    str(&r1.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    str(&r2.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    str(&r3.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    load_counter ++;
    tmp = ip.i;
    ldr(&r0.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    ldr(&r1.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    ldr(&r2.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    ip.i = tmp;
    store_counter ++;
    tmp = lr.i;
    str(&r0.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    str(&r1.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    str(&r2.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    lr.i = tmp;
    r0.i = sp.i + (4);
    r1.i = 0;
    r2.i = 6;
    quicksort();
    counters[14] ++;
    r1.i = (LC1 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC1 >> 16) << 16);
    printf(malloc_0+r1.i, r2.i);
L21:
    counters[15] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 4, 4, true, false, false);
    r1.i = r5.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[16] ++;
    tmp = r4.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r6.i);
    v = (r4.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        goto L21;
    }
    counters[17] ++;
    r0.i = 0;
    sp.i = sp.i + (32);
    load_counter ++;
    ldr(&r4.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&r6.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;

}

