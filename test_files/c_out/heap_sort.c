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

reg r2, r8, r1, r0, r3, r5, r4, r6, r7;

int32_t LC0, LC1;

int counters[43] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[43] = {5,2,3,6,6,6,2,3,2,10,2,3,5,4,5,8,1,2,7,5,1,4,6,6,3,1,4,1,15,4,3,2,4,18,3,2,5,3,4,2,4,2,3};


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

void print_stack(int32_t start)
{
    int32_t size = (10028-start)/4;
    int32_t cur_val = 0;

    for(int32_t i=0; i<size; i++)
    {
        ldr(&cur_val, &start, i*4, 4, false, false, false);
        printf("%d: %d\n", start+i*4, cur_val);
    }
}

void malloc_start()
{
    malloc_0 = (uint8_t*) malloc(1);
    uint8_t* stack_ptr = (uint8_t*) malloc(10000);
    sp.i = (int32_t) (stack_ptr - malloc_0) + 9996;
    fp = sp;

    int32_t malloc_total = (int32_t) ((uint8_t*) malloc(31) - malloc_0);
    LC0 = malloc_total;
    strcpy(malloc_0+LC0, "Sorted Output\000");

    LC1 = malloc_total + 19;
    strcpy(malloc_0+LC1, "%d\012\000");

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

void max_heapify();
void heapsort();
void build_maxheap();
void main();


void max_heapify()
{
    counters[0] ++;
    tmp = r2.i - ((uint32_t)r1.i << 1);
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) ((uint32_t)r1.i << 1));
    v = (r2.i&0x80000000) != (((uint32_t)r1.i << 1)&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r4.i, &sp.i, 0, 4, false, false, false);
    r4.i = r0.i + (((uint32_t)r1.i << 2));
    load_counter ++;
    ldr(&r5.i, &r0.i, ((uint32_t)r1.i << 2), 4, false, false, false);
    if (n != v)
    {
        goto L2;
    }
    counters[1] ++;
    r3.i = (uint32_t)r1.i << 1;
    goto L4;
L9:
    counters[2] ++;
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    store_counter ++;
    str(&lr.i, &r0.i, ((uint32_t)r1.i << 2), 4, false, false, false);
    if (n != v)
    {
        goto L8;
    }
L4:
    counters[3] ++;
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    r1.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&lr.i, &r0.i, ((uint32_t)r3.i << 2), 4, false, false, false);
    r4.i = r1.i + (4);
    ip.i = r0.i + (r1.i);
    if (z || n != v)
    {
        goto L3;
    }
    counters[4] ++;
    load_counter ++;
    ldr(&r1.i, &r0.i, r4.i, 4, false, false, false);
    r4.i = r0.i + (r4.i);
    tmp = r1.i - lr.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) lr.i);
    v = (r1.i&0x80000000) != (lr.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!z && n == v)
    {
        r3.i = r3.i + (1);
    }
    if (!z && n == v)
    {
        lr.i = r1.i;
    }
    if (!z && n == v)
    {
        ip.i = r4.i;
    }
L3:
    counters[5] ++;
    r1.i = r3.i + (((uint32_t)r3.i >> 31));
    tmp = r5.i - lr.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) lr.i);
    v = (r5.i&0x80000000) != (lr.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    r3.i = (uint32_t)r3.i << 1;
    r1.i = r1.i >> 1;
    r4.i = r0.i + (((uint32_t)r1.i << 2));
    if (z || n != v)
    {
        goto L9;
    }
L2:
    counters[6] ++;
    store_counter ++;
    str(&r5.i, &r4.i, 0, 4, false, true, false);
    load_counter ++;
    ldr(&r4.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;
L8:
    counters[7] ++;
    r4.i = ip.i;
    store_counter ++;
    str(&r5.i, &r4.i, 0, 4, false, true, false);
    load_counter ++;
    ldr(&r4.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;

}

void heapsort()
{
    counters[8] ++;
    tmp = r1.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 1);
    v = (r1.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (z || n != v)
    {
        return;
    }
    counters[9] ++;
    load_counter ++;
    ldr(&r3.i, &r0.i, 4, 4, false, false, false);
    tmp = r1.i - 2;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 2);
    v = (r1.i&0x80000000) != (2&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r6.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r4.i, &sp.i, 0, 4, false, false, false);
    ip.i = r1.i - (1);
    load_counter ++;
    ldr(&lr.i, &r0.i, ((uint32_t)r1.i << 2), 4, false, false, false);
    r4.i = r0.i + (((uint32_t)r1.i << 2));
    store_counter ++;
    str(&r3.i, &r0.i, ((uint32_t)r1.i << 2), 4, false, false, false);
    store_counter ++;
    str(&lr.i, &r0.i, 4, 4, false, false, false);
    load_counter ++;
    if (z)
    {
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
    r6.i = r0.i + (8);
L15:
    counters[10] ++;
    r3.i = 2;
    goto L14;
L26:
    counters[11] ++;
    tmp = r3.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) ip.i);
    v = (r3.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    store_counter ++;
    str(&r2.i, &r0.i, ((uint32_t)r1.i << 2), 4, false, false, false);
    if (!z && n == v)
    {
        goto L25;
    }
L14:
    counters[12] ++;
    tmp = r3.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) ip.i);
    v = (r3.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    r1.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &r0.i, ((uint32_t)r3.i << 2), 4, false, false, false);
    r1.i = r0.i + (r1.i);
    if (n == v)
    {
        goto L12;
    }
    counters[13] ++;
    load_counter ++;
    ldr(&r1.i, &r1.i, 4, 4, false, false, false);
    tmp = r1.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r2.i);
    v = (r1.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!z && n == v)
    {
        r3.i = r3.i + (1);
    }
    if (!z && n == v)
    {
        r2.i = r1.i;
    }
L12:
    counters[14] ++;
    r1.i = r3.i >> 1;
    tmp = lr.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) r2.i);
    v = (lr.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    r3.i = (uint32_t)r3.i << 1;
    r5.i = r0.i + (((uint32_t)r1.i << 2));
    if (z || n != v)
    {
        goto L26;
    }
L13:
    counters[15] ++;
    store_counter ++;
    str(&lr.i, &r5.i, 0, 4, false, true, false);
    ip.i = ip.i - (1);
    load_counter ++;
    ldr(&lr.i, &r4.i, -4, 4, true, false, false);
    load_counter ++;
    ldr(&r3.i, &r0.i, 4, 4, false, false, false);
    tmp = r6.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) r4.i);
    v = (r6.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    store_counter ++;
    str(&r3.i, &r4.i, 0, 4, false, true, false);
    store_counter ++;
    str(&lr.i, &r0.i, 4, 4, false, false, false);
    if (!z)
    {
        goto L15;
    }
    counters[16] ++;
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
L25:
    counters[17] ++;
    r5.i = r0.i + (((uint32_t)r3.i << 1));
    goto L13;
    return;
}

void build_maxheap()
{
    counters[18] ++;
    tmp = r1.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 1);
    v = (r1.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
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
    r5.i = r1.i + (((uint32_t)r1.i >> 31));
    load_counter ++;
    if (z || n != v)
    {
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
        ldr(&pc.i, &sp.i, 0, 4, false, false, false);
        sp.i += 4;
        return;
    }
    r5.i = r5.i >> 1;
    r8.i = r0.i + (((uint32_t)r5.i << 2));
    r4.i = (uint32_t)r5.i << 1;
L33:
    counters[19] ++;
    tmp = r1.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r4.i);
    v = (r1.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    r2.i = r8.i;
    r3.i = r4.i;
    load_counter ++;
    ldr(&r7.i, &r8.i, -4, 4, false, true, false);
    if (n == v)
    {
        goto L32;
    }
    counters[20] ++;
    goto L29;
L31:
    counters[21] ++;
    r3.i = (uint32_t)r3.i << 1;
    store_counter ++;
    str(&ip.i, &r0.i, ((uint32_t)lr.i << 2), 4, false, false, false);
    tmp = r1.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r3.i);
    v = (r1.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (n != v)
    {
        goto L29;
    }
L32:
    counters[22] ++;
    tmp = r1.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r3.i);
    v = (r1.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    r2.i = (uint32_t)r3.i << 2;
    lr.i = r2.i + (4);
    load_counter ++;
    ldr(&ip.i, &r0.i, ((uint32_t)r3.i << 2), 4, false, false, false);
    r2.i = r0.i + (r2.i);
    if (z || n != v)
    {
        goto L30;
    }
    counters[23] ++;
    load_counter ++;
    ldr(&r6.i, &r0.i, lr.i, 4, false, false, false);
    lr.i = r0.i + (lr.i);
    tmp = r6.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) ip.i);
    v = (r6.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    if (!z && n == v)
    {
        r3.i = r3.i + (1);
    }
    if (!z && n == v)
    {
        ip.i = r6.i;
    }
    if (!z && n == v)
    {
        r2.i = lr.i;
    }
L30:
    counters[24] ++;
    tmp = r7.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r7.i) >= ((uint32_t) ip.i);
    v = (r7.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
    lr.i = r3.i >> 1;
    if (z || n != v)
    {
        goto L31;
    }
    counters[25] ++;
    r2.i = r0.i + (((uint32_t)lr.i << 2));
L29:
    counters[26] ++;
    r5.i = r5.i - (1);
    z = r5.i == 0;
    n = r5.i & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) 1);
    v = (r5.i&0x80000000) != (1&0x80000000) && (r5.i&0x80000000) != (r5.i&0x80000000);
    r4.i = r4.i - (2);
    store_counter ++;
    str(&r7.i, &r2.i, 0, 4, false, true, false);
    if (!z)
    {
        goto L33;
    }
    counters[27] ++;
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
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;

}

void main()
{
    malloc_start();
    counters[28] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
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
    sp.i = sp.i - (80);
    r0.i = 5;
    r1.i = 4;
    r6.i = sp.i + (16);
    store_counter ++;
    str(&r0.i, &sp.i, 4, 4, false, false, false);
    str(&r1.i, &sp.i, 8, 4, false, false, false);
    r5.i = sp.i + (24);
    r0.i = 3;
    r1.i = 2;
    lr.i = 6;
    store_counter ++;
    str(&r0.i, &sp.i, 12, 4, false, false, false);
    str(&r1.i, &sp.i, 16, 4, false, false, false);
    r0.i = 1;
    r1.i = 0;
    store_counter ++;
    str(&r0.i, &sp.i, 20, 4, false, false, false);
    str(&r1.i, &sp.i, 24, 4, false, false, false);
    goto L46;
L56:
    counters[29] ++;
    load_counter ++;
    ldr(&r3.i, &sp.i, 24, 4, false, false, false);
    r0.i = sp.i + (12);
    tmp = ip.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r3.i);
    v = (ip.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (z || n != v)
    {
        goto L54;
    }
L45:
    counters[30] ++;
    lr.i = lr.i - (2);
    z = lr.i == 0;
    n = lr.i & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) 2);
    v = (lr.i&0x80000000) != (2&0x80000000) && (lr.i&0x80000000) != (lr.i&0x80000000);
    store_counter ++;
    str(&ip.i, &r0.i, 0, 4, false, true, false);
    if (z)
    {
        goto L55;
    }
L46:
    counters[31] ++;
    load_counter ++;
    ldr(&ip.i, &r6.i, -4, 4, true, false, false);
    r2.i = lr.i;
L44:
    counters[32] ++;
    r4.i = r2.i + (1);
    tmp = r2.i - 6;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) 6);
    v = (r2.i&0x80000000) != (6&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    r0.i = (uint32_t)r4.i << 2;
    if (z)
    {
        goto L56;
    }
    counters[33] ++;
    r8.i = sp.i + (80);
    r1.i = r0.i - (4);
    r8.i = r8.i + (r0.i);
    r7.i = sp.i + (r1.i);
    load_counter ++;
    ldr(&r1.i, &sp.i, r1.i, 4, false, false, false);
    r3.i = r2.i >> 1;
    load_counter ++;
    ldr(&r8.i, &r8.i, -80, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    tmp = r8.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) r1.i);
    v = (r8.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    if (!z && n == v)
    {
        r7.i = sp.i + (r0.i);
    }
    if (!z && n == v)
    {
        r2.i = r4.i;
    }
    if (!z && n == v)
    {
        r3.i = r2.i >> 1;
    }
    load_counter ++;
    if (!z && n == v)
    {
        ldr(&r1.i, &sp.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    }
    r2.i = (uint32_t)r2.i << 1;
    if (!z && n == v)
    {
        r3.i = (uint32_t)r3.i << 2;
    }
    tmp = ip.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r1.i);
    v = (ip.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    r0.i = sp.i + (r3.i);
    if (!z && n == v)
    {
        goto L45;
    }
    counters[34] ++;
    tmp = r2.i - 6;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) 6);
    v = (r2.i&0x80000000) != (6&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    store_counter ++;
    str(&r1.i, &sp.i, r3.i, 4, false, false, false);
    if (z || n != v)
    {
        goto L44;
    }
    counters[35] ++;
    r0.i = r7.i;
    goto L45;
L54:
    counters[36] ++;
    lr.i = lr.i - (2);
    z = lr.i == 0;
    n = lr.i & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) 2);
    v = (lr.i&0x80000000) != (2&0x80000000) && (lr.i&0x80000000) != (lr.i&0x80000000);
    r0.i = r5.i;
    store_counter ++;
    str(&r3.i, &sp.i, 12, 4, false, false, false);
    store_counter ++;
    str(&ip.i, &r0.i, 0, 4, false, true, false);
    if (!z)
    {
        goto L46;
    }
L55:
    counters[37] ++;
    r1.i = 6;
    r0.i = sp.i;
    heapsort();
    counters[38] ++;
    r0.i = (LC0 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC0 >> 16) << 16);
    r6.i = (LC1 & 0xffff);
    printf("%s\n", malloc_0+r0.i);
    counters[39] ++;
    r6.i = r6.i | (((uint32_t)LC1 >> 16) << 16);
    r4.i = sp.i;
L47:
    counters[40] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 4, 4, true, false, false);
    r1.i = r6.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[41] ++;
    tmp = r5.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r4.i);
    v = (r5.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (!z)
    {
        goto L47;
    }
    counters[42] ++;
    r0.i = 0;
    sp.i = sp.i + (80);
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
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    counter_summary();
    return;

}

