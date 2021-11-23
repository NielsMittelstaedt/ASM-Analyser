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

reg r3, r6, r10, r0, r4, r1, r2, r5, r8, r7, r9;

int32_t LC0;

int counters[31] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[31] = {5,6,9,2,4,2,10,2,2,5,3,7,3,2,7,1,2,2,3,7,8,5,6,6,3,18,1,4,2,2,2};


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
    int32_t size = (1028-start)/4;
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

    int32_t malloc_total = (int32_t) ((uint8_t*) malloc(9) - malloc_0);
    LC0 = malloc_total;
    strcpy(malloc_0+LC0, " %d\000");

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "merge_sort.c";

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

void swap();
void merge();
void merge_sort();
void main();

void free_help()
{
    free(malloc_0+r0.i);
}
void memcpy_help()
{
    memcpy(malloc_0+r0.i, malloc_0+r1.i, r2.i);
}
void malloc_help()
{
    uint8_t* ptr = (uint8_t*) malloc(r0.i);
    r0.i = (int32_t) (ptr - malloc_0);
}

void swap()
{
    counters[0] ++;
    load_counter ++;
    ldr(&r3.i, &r0.i, 0, 4, false, true, false);
    load_counter ++;
    ldr(&r2.i, &r1.i, 0, 4, false, true, false);
    store_counter ++;
    str(&r2.i, &r0.i, 0, 4, false, true, false);
    store_counter ++;
    str(&r3.i, &r1.i, 0, 4, false, true, false);
    return;

}

void merge()
{
    counters[1] ++;
    store_counter ++;
    sp.i -= 32;
    str(&r4.i, &sp.i, 0*4, 4, false, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false, false);
    str(&r7.i, &sp.i, 3*4, 4, false, false, false);
    str(&r8.i, &sp.i, 4*4, 4, false, false, false);
    str(&r9.i, &sp.i, 5*4, 4, false, false, false);
    str(&r10.i, &sp.i, 6*4, 4, false, false, false);
    str(&lr.i, &sp.i, 7*4, 4, false, false, false);
    r5.i = r0.i;
    r0.i = (uint32_t)r3.i << 2;
    r8.i = r1.i;
    r4.i = r2.i;
    malloc_help();
    counters[2] ++;
    r2.i = r8.i + r4.i;
    r2.i = r2.i + ((uint32_t)r2.i >> 31);
    r2.i = r2.i >> 1;
    r10.i = r2.i + 1;
    tmp = r2.i - r8.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r8.i);
    v = (r2.i&0x80000000) != (r8.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    r3.i = r10.i;
    r9.i = r0.i;
    r0.i = r4.i + 1;
    if (n != v)
    {
        goto L16;
    }
    counters[3] ++;
    tmp = r4.i - r10.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r10.i);
    v = (r4.i&0x80000000) != (r10.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (n != v)
    {
        goto L5;
    }
    counters[4] ++;
    r1.i = r9.i - 4;
    lr.i = r8.i;
    ip.i = r8.i;
    goto L8;
L23:
    counters[5] ++;
    tmp = r3.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r4.i);
    v = (r3.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z && n == v)
    {
        goto L22;
    }
L8:
    counters[6] ++;
    load_counter ++;
    ldr(&r7.i, &r5.i, ((uint32_t)lr.i << 2), 4, false, false, false);
    ip.i = ip.i + 1;
    load_counter ++;
    ldr(&r6.i, &r5.i, ((uint32_t)r3.i << 2), 4, false, false, false);
    tmp = r7.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r7.i) >= ((uint32_t) r6.i);
    v = (r7.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
    store_counter ++;
    if (z || n != v)
    {
        str(&r7.i, &r1.i, ((uint32_t)ip.i << 2), 4, false, false, false);
    }
    if (z || n != v)
    {
        lr.i = lr.i + 1;
    }
    if (!z && n == v)
    {
        r3.i = r3.i + 1;
    }
    store_counter ++;
    if (!z && n == v)
    {
        str(&r6.i, &r1.i, ((uint32_t)ip.i << 2), 4, false, false, false);
    }
    tmp = r2.i - lr.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) lr.i);
    v = (r2.i&0x80000000) != (lr.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n == v)
    {
        goto L23;
    }
L4:
    counters[7] ++;
    tmp = r3.i - r0.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r0.i);
    v = (r3.i&0x80000000) != (r0.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L13;
    }
    counters[8] ++;
    tmp = r4.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r3.i);
    v = (r4.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (n != v)
    {
        goto L13;
    }
    counters[9] ++;
    r2.i = r0.i - r3.i;
    r1.i = r5.i + ((uint32_t)r3.i << 2);
    r0.i = r9.i + ((uint32_t)ip.i << 2);
    r2.i = (uint32_t)r2.i << 2;
    memcpy_help();
L13:
    counters[10] ++;
    r4.i = r4.i - r8.i;
    tmp = r8.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) r4.i);
    v = (r8.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    if (!z && n == v)
    {
        goto L12;
    }
    counters[11] ++;
    r4.i = r4.i - r8.i;
    r1.i = (uint32_t)r8.i << 2;
    r2.i = r4.i + 1;
    r0.i = r5.i + r1.i;
    r1.i = r9.i + r1.i;
    r2.i = (uint32_t)r2.i << 2;
    memcpy_help();
L12:
    counters[12] ++;
    r0.i = r9.i;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false, false);
    ldr(&r7.i, &sp.i, 3*4, 4, false, false, false);
    ldr(&r8.i, &sp.i, 4*4, 4, false, false, false);
    ldr(&r9.i, &sp.i, 5*4, 4, false, false, false);
    ldr(&r10.i, &sp.i, 6*4, 4, false, false, false);
    ldr(&lr.i, &sp.i, 7*4, 4, false, false, false);
    sp.i += 32;
    free_help();
    return;
L22:
    counters[13] ++;
    tmp = r3.i - r0.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r0.i);
    v = (r3.i&0x80000000) != (r0.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L13;
    }
L15:
    counters[14] ++;
    tmp = r2.i - lr.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) lr.i);
    v = (r2.i&0x80000000) != (lr.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    r10.i = r10.i - lr.i;
    r0.i = r9.i + ((uint32_t)ip.i << 2);
    r1.i = r5.i + ((uint32_t)lr.i << 2);
    if (n == v)
    {
        r2.i = (uint32_t)r10.i << 2;
    }
    if (n != v)
    {
        r2.i = 4;
    }
    memcpy_help();
    counters[15] ++;
    goto L13;
L16:
    counters[16] ++;
    ip.i = r8.i;
    goto L4;
L5:
    counters[17] ++;
    tmp = r2.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r4.i);
    v = (r2.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z)
    {
        goto L13;
    }
    counters[18] ++;
    lr.i = r8.i;
    ip.i = r8.i;
    goto L15;
    return;
}

void merge_sort()
{
    counters[19] ++;
    store_counter ++;
    sp.i -= 24;
    str(&r4.i, &sp.i, 0*4, 4, false, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false, false);
    str(&r7.i, &sp.i, 3*4, 4, false, false, false);
    str(&r8.i, &sp.i, 4*4, 4, false, false, false);
    str(&lr.i, &sp.i, 5*4, 4, false, false, false);
    r4.i = r3.i;
    r3.i = r3.i - r2.i;
    r5.i = r2.i;
    tmp = r3.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 1);
    v = (r3.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    r6.i = r0.i;
    if (z)
    {
        goto L28;
    }
    counters[20] ++;
    tmp = r4.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r2.i);
    v = (r4.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    load_counter ++;
    if (z)
    {
        ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
        ldr(&r5.i, &sp.i, 1*4, 4, false, false, false);
        ldr(&r6.i, &sp.i, 2*4, 4, false, false, false);
        ldr(&r7.i, &sp.i, 3*4, 4, false, false, false);
        ldr(&r8.i, &sp.i, 4*4, 4, false, false, false);
        ldr(&pc.i, &sp.i, 5*4, 4, false, false, false);
        sp.i += 24;
        return;
    }
    r8.i = r4.i + r2.i;
    r7.i = r1.i;
    r8.i = r8.i + ((uint32_t)r8.i >> 31);
    r8.i = r8.i >> 1;
    r3.i = r8.i;
    merge_sort();
    counters[21] ++;
    r2.i = r8.i + 1;
    r3.i = r4.i;
    r1.i = r7.i;
    r0.i = r6.i;
    merge_sort();
    counters[22] ++;
    r3.i = r7.i;
    r2.i = r4.i;
    r1.i = r5.i;
    r0.i = r6.i;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false, false);
    ldr(&r7.i, &sp.i, 3*4, 4, false, false, false);
    ldr(&r8.i, &sp.i, 4*4, 4, false, false, false);
    ldr(&lr.i, &sp.i, 5*4, 4, false, false, false);
    sp.i += 24;
    merge();
    return;
L28:
    counters[23] ++;
    load_counter ++;
    ldr(&r3.i, &r0.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &r0.i, ((uint32_t)r4.i << 2), 4, false, false, false);
    tmp = r3.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r2.i);
    v = (r3.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    store_counter ++;
    if (!z && n == v)
    {
        str(&r2.i, &r0.i, ((uint32_t)r5.i << 2), 4, false, false, false);
    }
    store_counter ++;
    if (!z && n == v)
    {
        str(&r3.i, &r0.i, ((uint32_t)r4.i << 2), 4, false, false, false);
    }
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false, false);
    ldr(&r7.i, &sp.i, 3*4, 4, false, false, false);
    ldr(&r8.i, &sp.i, 4*4, 4, false, false, false);
    ldr(&pc.i, &sp.i, 5*4, 4, false, false, false);
    sp.i += 24;
    return;

}

void main()
{
    malloc_start();
    counters[24] ++;
    store_counter ++;
    sp.i -= 24;
    str(&r4.i, &sp.i, 0*4, 4, false, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false, false);
    str(&r7.i, &sp.i, 3*4, 4, false, false, false);
    str(&r8.i, &sp.i, 4*4, 4, false, false, false);
    str(&lr.i, &sp.i, 5*4, 4, false, false, false);
    r0.i = 24;
    malloc_help();
    counters[25] ++;
    r1.i = 6;
    r3.i = 5;
    r2.i = 4;
    r6.i = (LC0 & 0xffff);
    r6.i = r6.i | (((uint32_t)LC0 >> 16) << 16);
    store_counter ++;
    str(&r2.i, &r0.i, 8, 4, false, false, false);
    r2.i = 3;
    store_counter ++;
    str(&r1.i, &r0.i, 0, 4, false, true, false);
    r5.i = r0.i;
    store_counter ++;
    str(&r2.i, &r0.i, 12, 4, false, false, false);
    r2.i = 2;
    store_counter ++;
    str(&r3.i, &r0.i, 4, 4, false, false, false);
    r4.i = r5.i - 4;
    store_counter ++;
    str(&r2.i, &r0.i, 16, 4, false, false, false);
    r2.i = 1;
    store_counter ++;
    str(&r2.i, &r0.i, 20, 4, false, false, false);
    r2.i = 0;
    merge_sort();
    counters[26] ++;
    r7.i = r5.i + 20;
L30:
    counters[27] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 4, 4, true, false, false);
    r1.i = r6.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[28] ++;
    tmp = r7.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r7.i) >= ((uint32_t) r4.i);
    v = (r7.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
    if (!z)
    {
        goto L30;
    }
    counters[29] ++;
    r0.i = r5.i;
    free_help();
    counters[30] ++;
    r0.i = 0;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false, false);
    ldr(&r7.i, &sp.i, 3*4, 4, false, false, false);
    ldr(&r8.i, &sp.i, 4*4, 4, false, false, false);
    ldr(&pc.i, &sp.i, 5*4, 4, false, false, false);
    sp.i += 24;
    counter_summary();
    return;

}

