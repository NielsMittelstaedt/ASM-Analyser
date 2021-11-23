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

reg r1, r5, r2, r6, r3, r4, r0;

int32_t LC1, LC0;

int counters[24] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[24] = {5,2,4,2,2,2,5,6,8,1,3,1,4,1,3,2,4,8,2,1,16,4,2,3};


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

    LC1 = (int32_t) ((uint8_t*) malloc(9) - malloc_0);
    strcpy(malloc_0+LC1, "%d \000");

    LC0 = (int32_t) ((uint8_t*) malloc(6*sizeof(int32_t)) - malloc_0);
    int32_t arrayLC0[] = {5,3,9,2,6,1};
    for(int i=0; i<6; i++) str(&arrayLC0[i], &LC0, i*4, 4, false, false);
}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "heap_sort.c";

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


void swap()
{
    counters[0] ++;
    load_counter ++;
    ldr(&r3.i, &r0.i, ((uint32_t)r1.i << 2), 4, false, false);
    load_counter ++;
    ldr(&ip.i, &r0.i, ((uint32_t)r2.i << 2), 4, false, false);
    store_counter ++;
    str(&ip.i, &r0.i, ((uint32_t)r1.i << 2), 4, false, false);
    store_counter ++;
    str(&r3.i, &r0.i, ((uint32_t)r2.i << 2), 4, false, false);
    return;

}

void heapify()
{
    counters[1] ++;
    store_counter ++;
    sp.i -= 12;
    str(&r4.i, &sp.i, 0*4, 4, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false);
    str(&lr.i, &sp.i, 2*4, 4, false, false);
    goto L7;
L12:
    counters[2] ++;
    load_counter ++;
    ldr(&r4.i, &r0.i, ((uint32_t)lr.i << 2), 4, false, false);
    load_counter ++;
    ldr(&r5.i, &r0.i, ((uint32_t)r2.i << 2), 4, false, false);
    tmp = r5.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r4.i);
    v = (r5.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (c)
    {
        goto L4;
    }
    counters[3] ++;
    tmp = r1.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r3.i);
    v = (r1.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (c && !z)
    {
        goto L11;
    }
L9:
    counters[4] ++;
    ip.i = lr.i;
    r3.i = lr.i;
L5:
    counters[5] ++;
    tmp = r3.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r2.i);
    v = (r3.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    load_counter ++;
    if (z)
    {
        ldr(&r4.i, &sp.i, 0*4, 4, false, false);
        ldr(&r5.i, &sp.i, 1*4, 4, false, false);
        ldr(&pc.i, &sp.i, 2*4, 4, false, false);
        sp.i += 12;
        return;
    }
L13:
    counters[6] ++;
    load_counter ++;
    ldr(&r4.i, &r0.i, ((uint32_t)r2.i << 2), 4, false, false);
    load_counter ++;
    ldr(&lr.i, &r0.i, ((uint32_t)ip.i << 2), 4, false, false);
    store_counter ++;
    str(&r4.i, &r0.i, ((uint32_t)ip.i << 2), 4, false, false);
    store_counter ++;
    str(&lr.i, &r0.i, ((uint32_t)r2.i << 2), 4, false, false);
    r2.i = r3.i;
L7:
    counters[7] ++;
    r3.i = (uint32_t)r2.i << 1;
    lr.i = r3.i + 1;
    r3.i = r3.i + 2;
    tmp = lr.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) r1.i);
    v = (lr.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    ip.i = r3.i;
    if (!c)
    {
        goto L12;
    }
L4:
    counters[8] ++;
    tmp = r1.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r3.i);
    v = (r1.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    load_counter ++;
    if (!c || z)
    {
        ldr(&r4.i, &sp.i, 0*4, 4, false, false);
        ldr(&r5.i, &sp.i, 1*4, 4, false, false);
        ldr(&pc.i, &sp.i, 2*4, 4, false, false);
        sp.i += 12;
        return;
    }
    load_counter ++;
    ldr(&r4.i, &r0.i, ((uint32_t)r2.i << 2), 4, false, false);
    load_counter ++;
    ldr(&lr.i, &r0.i, ((uint32_t)r3.i << 2), 4, false, false);
    tmp = r4.i - lr.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) lr.i);
    v = (r4.i&0x80000000) != (lr.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    load_counter ++;
    if (c)
    {
        ldr(&r4.i, &sp.i, 0*4, 4, false, false);
        ldr(&r5.i, &sp.i, 1*4, 4, false, false);
        ldr(&pc.i, &sp.i, 2*4, 4, false, false);
        sp.i += 12;
        return;
    }
    tmp = r3.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r2.i);
    v = (r3.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L13;
    }
    counters[9] ++;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false);
    ldr(&pc.i, &sp.i, 2*4, 4, false, false);
    sp.i += 12;
    return;
L11:
    counters[10] ++;
    load_counter ++;
    ldr(&r5.i, &r0.i, ((uint32_t)r3.i << 2), 4, false, false);
    tmp = r4.i - r5.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r5.i);
    v = (r4.i&0x80000000) != (r5.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (c)
    {
        goto L9;
    }
    counters[11] ++;
    goto L5;
    return;
}

void heapSort()
{
    counters[12] ++;
    store_counter ++;
    sp.i -= 16;
    str(&r4.i, &sp.i, 0*4, 4, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false);
    str(&lr.i, &sp.i, 3*4, 4, false, false);
    r4.i = (uint32_t)r1.i >> 1;
    tmp = r4.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 0);
    v = (r4.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (z)
    {
        goto L15;
    }
    counters[13] ++;
    r4.i = r4.i - 1;
L16:
    counters[14] ++;
    r2.i = r4.i;
    r4.i = r4.i - 1;
    heapify();
    counters[15] ++;
    tmp = r4.i + 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) tmp) < ((uint32_t) r4.i);
    v = (r4.i&0x80000000) == (1&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        goto L16;
    }
L15:
    counters[16] ++;
    r5.i = r1.i - 1;
    z = r5.i == 0;
    n = r5.i & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 1);
    v = (r1.i&0x80000000) != (1&0x80000000) && (r5.i&0x80000000) != (r1.i&0x80000000);
    load_counter ++;
    if (z)
    {
        ldr(&r4.i, &sp.i, 0*4, 4, false, false);
        ldr(&r5.i, &sp.i, 1*4, 4, false, false);
        ldr(&r6.i, &sp.i, 2*4, 4, false, false);
        ldr(&pc.i, &sp.i, 3*4, 4, false, false);
        sp.i += 16;
        return;
    }
    r4.i = r0.i + ((uint32_t)r1.i << 2);
    r6.i = r0.i + 4;
L18:
    counters[17] ++;
    load_counter ++;
    ldr(&ip.i, &r4.i, -4, 4, true, false);
    r1.i = r5.i;
    load_counter ++;
    ldr(&r3.i, &r0.i, 0, 4, false, true);
    r2.i = 0;
    r5.i = r5.i - 1;
    store_counter ++;
    str(&ip.i, &r0.i, 0, 4, false, true);
    store_counter ++;
    str(&r3.i, &r4.i, 0, 4, false, true);
    heapify();
    counters[18] ++;
    tmp = r6.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) r4.i);
    v = (r6.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    if (!z)
    {
        goto L18;
    }
    counters[19] ++;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false);
    ldr(&pc.i, &sp.i, 3*4, 4, false, false);
    sp.i += 16;
    return;

}

void main()
{
    malloc_start();
    counters[20] ++;
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
    lr.i = sp.i;
    r5.i = (LC1 & 0xffff);
    r6.i = sp.i + 24;
    r5.i = r5.i | (((uint32_t)LC1 >> 16) << 16);
    r4.i = sp.i;
    store_counter ++;
    str(&r0.i, &lr.i, 0*4, 4, false, false);
    str(&r1.i, &lr.i, 1*4, 4, false, false);
    str(&r2.i, &lr.i, 2*4, 4, false, false);
    str(&r3.i, &lr.i, 3*4, 4, false, false);
    lr.i += 16;
    load_counter ++;
    ldr(&r0.i, &ip.i, 0*4, 4, false, false);
    ldr(&r1.i, &ip.i, 1*4, 4, false, false);
    store_counter ++;
    str(&r0.i, &lr.i, 0*4, 4, false, false);
    str(&r1.i, &lr.i, 1*4, 4, false, false);
    r0.i = sp.i;
    r1.i = 6;
    heapSort();
L29:
    counters[21] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 4, 4, false, true);
    r1.i = r5.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[22] ++;
    tmp = r4.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r6.i);
    v = (r4.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        goto L29;
    }
    counters[23] ++;
    r0.i = 0;
    sp.i = sp.i + 24;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false);
    ldr(&pc.i, &sp.i, 3*4, 4, false, false);
    sp.i += 16;
    counter_summary();
    return;

}

