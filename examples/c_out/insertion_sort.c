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

reg r4, r3, r0, r5, r6, r2, r1;

int32_t LC1, LC2, LC0;

int counters[17] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[17] = {16,3,5,2,5,3,2,5,2,5,16,3,4,2,3,6,5};

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

    LC1 = (int32_t) ((char*) malloc(19) - malloc_0);
    strcpy(malloc_0+LC1, "Sorted array:\000");

    LC2 = (int32_t) ((char*) malloc(9) - malloc_0);
    strcpy(malloc_0+LC2, " %d\000");

    LC0 = (int32_t) ((char*) malloc(5*sizeof(int32_t)) - malloc_0);
    int32_t arrayLC0[] = {9,1,3,7,2};
    for(int i=0; i<5; i++) str(&arrayLC0[i], &LC0, i*4, false, false, false);
}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "insertion_sort.c";

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


void main()
{
    malloc_start();
    counters[0] ++;
    ip.i = (LC0 & 0xffff);
    ip.i = ip.i | (((uint32_t)LC0 >> 16) << 16);
    store_counter ++;
    sp.i -= 16;
    str(&r4.i, &sp.i, 0*4, 4, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false);
    str(&lr.i, &sp.i, 3*4, 4, false, false);
    sp.i = sp.i - 24;
    load_counter ++;
    ldr(&r0.i, &ip.i, 0*4, 4, false, false);
    ldr(&r1.i, &ip.i, 1*4, 4, false, false);
    ldr(&r2.i, &ip.i, 2*4, 4, false, false);
    ldr(&r3.i, &ip.i, 3*4, 4, false, false);
    ip.i += 16;
    lr.i = sp.i + 4;
    store_counter ++;
    str(&r0.i, &lr.i, 0*4, 4, false, false);
    str(&r1.i, &lr.i, 1*4, 4, false, false);
    str(&r2.i, &lr.i, 2*4, 4, false, false);
    str(&r3.i, &lr.i, 3*4, 4, false, false);
    lr.i += 16;
    r1.i = r0.i;
    load_counter ++;
    ldr(&r3.i, &sp.i, 8, 4, false, false);
    load_counter ++;
    ldr(&r2.i, &ip.i, 0, 4, false, true);
    tmp = r0.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) r3.i);
    v = (r0.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    store_counter ++;
    str(&r2.i, &lr.i, 0, 4, false, true);
    if (!z && n == v)
    {
        r1.i = r3.i;
    }
    store_counter ++;
    if (!z && n == v)
    {
        str(&r3.i, &sp.i, 4, 4, false, false);
    }
    if (!z && n == v)
    {
        r3.i = r0.i;
    }
    store_counter ++;
    if (!z && n == v)
    {
        str(&r0.i, &sp.i, 8, 4, false, false);
    }
L5:
    counters[1] ++;
    load_counter ++;
    ldr(&r2.i, &sp.i, 12, 4, false, false);
    tmp = r3.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r2.i);
    v = (r3.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L4;
    }
    counters[2] ++;
    r0.i = r3.i;
    store_counter ++;
    str(&r3.i, &sp.i, 12, 4, false, false);
    store_counter ++;
    str(&r2.i, &sp.i, 8, 4, false, false);
    r3.i = r2.i;
    r2.i = r0.i;
L4:
    counters[3] ++;
    tmp = r1.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r3.i);
    v = (r1.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (z || n != v)
    {
        goto L9;
    }
    counters[4] ++;
    r0.i = r1.i;
    store_counter ++;
    str(&r1.i, &sp.i, 8, 4, false, false);
    store_counter ++;
    str(&r3.i, &sp.i, 4, 4, false, false);
    r1.i = r3.i;
    r3.i = r0.i;
L9:
    counters[5] ++;
    load_counter ++;
    ldr(&r0.i, &sp.i, 16, 4, false, false);
    tmp = r2.i - r0.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r0.i);
    v = (r2.i&0x80000000) != (r0.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z && n == v)
    {
        goto L7;
    }
L8:
    counters[6] ++;
    tmp = r3.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r2.i);
    v = (r3.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L15;
    }
    counters[7] ++;
    ip.i = r3.i;
    store_counter ++;
    str(&r3.i, &sp.i, 12, 4, false, false);
    store_counter ++;
    str(&r2.i, &sp.i, 8, 4, false, false);
    r3.i = r2.i;
    r2.i = ip.i;
L15:
    counters[8] ++;
    tmp = r1.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r3.i);
    v = (r1.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!z && n == v)
    {
        goto L11;
    }
L14:
    counters[9] ++;
    load_counter ++;
    ldr(&ip.i, &sp.i, 20, 4, false, false);
    tmp = r0.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) ip.i);
    v = (r0.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    store_counter ++;
    if (!z && n == v)
    {
        str(&r0.i, &sp.i, 20, 4, false, false);
    }
    if (!z && n == v)
    {
        r0.i = ip.i;
    }
    store_counter ++;
    if (!z && n == v)
    {
        str(&ip.i, &sp.i, 16, 4, false, false);
    }
L13:
    counters[10] ++;
    tmp = r2.i - r0.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r0.i);
    v = (r2.i&0x80000000) != (r0.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    store_counter ++;
    if (!z && n == v)
    {
        str(&r0.i, &sp.i, 12, 4, false, false);
    }
    store_counter ++;
    if (!z && n == v)
    {
        str(&r2.i, &sp.i, 16, 4, false, false);
    }
    r5.i = (LC2 & 0xffff);
    if (!z && n == v)
    {
        r2.i = r0.i;
    }
    tmp = r3.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r2.i);
    v = (r3.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    r0.i = 1;
    store_counter ++;
    if (!z && n == v)
    {
        str(&r3.i, &sp.i, 12, 4, false, false);
    }
    store_counter ++;
    if (!z && n == v)
    {
        str(&r2.i, &sp.i, 8, 4, false, false);
    }
    if (!z && n == v)
    {
        r3.i = r2.i;
    }
    tmp = r1.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r3.i);
    v = (r1.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    store_counter ++;
    if (!z && n == v)
    {
        str(&r1.i, &sp.i, 8, 4, false, false);
    }
    r1.i = (LC1 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC1 >> 16) << 16);
    store_counter ++;
    if (!z && n == v)
    {
        str(&r3.i, &sp.i, 4, 4, false, false);
    }
    printf(malloc_0+r1.i, r2.i);
    counters[11] ++;
    r5.i = r5.i | (((uint32_t)LC2 >> 16) << 16);
    r4.i = sp.i + 4;
    r6.i = sp.i + 24;
L19:
    counters[12] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 4, 4, false, true);
    r1.i = r5.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[13] ++;
    tmp = r4.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r6.i);
    v = (r4.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        goto L19;
    }
    counters[14] ++;
    r0.i = 0;
    sp.i = sp.i + 24;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false);
    ldr(&pc.i, &sp.i, 3*4, 4, false, false);
    sp.i += 16;
    return;
L7:
    counters[15] ++;
    ip.i = r2.i;
    store_counter ++;
    str(&r2.i, &sp.i, 16, 4, false, false);
    store_counter ++;
    str(&r0.i, &sp.i, 12, 4, false, false);
    r2.i = r0.i;
    r0.i = ip.i;
    goto L8;
L11:
    counters[16] ++;
    ip.i = r1.i;
    r1.i = r3.i;
    store_counter ++;
    r3.i = ip.i;
    goto L14;
    counter_summary();
    return;
}

