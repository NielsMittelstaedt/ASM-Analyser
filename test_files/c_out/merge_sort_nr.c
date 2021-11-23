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

int32_t LC0, LC1, LC2;

int counters[35] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[35] = {2,12,3,9,5,3,9,4,9,2,1,2,7,3,2,8,4,7,2,4,2,3,2,2,3,4,4,2,4,14,3,4,4,2,3};


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

    int32_t malloc_total = (int32_t) ((uint8_t*) malloc(50) - malloc_0);
    LC0 = malloc_total;
    strcpy(malloc_0+LC0, "%d \000");

    LC1 = malloc_total + 9;
    strcpy(malloc_0+LC1, "\012\000");

    LC2 = malloc_total + 19;
    strcpy(malloc_0+LC2, "Sorted array is as shown:\000");

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "merge_sort_nr.c";

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

void mergesort();
void show();
void main();

void memcpy_help()
{
    memcpy(malloc_0+r0.i, malloc_0+r1.i, r2.i);
}

void mergesort()
{
    counters[0] ++;
    tmp = r1.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 1);
    v = (r1.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (z || n != v)
    {
        return;
    }
    counters[1] ++;
    store_counter ++;
    sp.i -= 36;
    str(&r4.i, &sp.i, 0*4, 4, false, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false, false);
    str(&r7.i, &sp.i, 3*4, 4, false, false, false);
    str(&r8.i, &sp.i, 4*4, 4, false, false, false);
    str(&r9.i, &sp.i, 5*4, 4, false, false, false);
    str(&r10.i, &sp.i, 6*4, 4, false, false, false);
    str(&fp.i, &sp.i, 7*4, 4, false, false, false);
    str(&lr.i, &sp.i, 8*4, 4, false, false, false);
    sp.i = sp.i - 220;
    r10.i = r1.i;
    r8.i = r0.i;
    fp.i = 1;
    r2.i = r0.i + ((uint32_t)r1.i << 2);
    r3.i = (LC0 & 0xffff);
    store_counter ++;
    str(&r2.i, &sp.i, 8, 4, false, false, false);
    r3.i = r3.i | (((uint32_t)LC0 >> 16) << 16);
    store_counter ++;
    str(&r3.i, &sp.i, 12, 4, false, false, false);
    r3.i = r1.i - 1;
    store_counter ++;
    str(&r3.i, &sp.i, 4, 4, false, false, false);
L18:
    counters[2] ++;
    r4.i = 0;
    r3.i = fp.i;
    r5.i = r4.i;
L13:
    counters[3] ++;
    ip.i = r3.i - 1;
    r7.i = ip.i + fp.i;
    tmp = r7.i - r10.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r7.i) >= ((uint32_t) r10.i);
    v = (r7.i&0x80000000) != (r10.i&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
    if (n != v)
    {
        r9.i = r7.i + 1;
    }
    load_counter ++;
    if (n == v)
    {
        ldr(&r7.i, &sp.i, 4, 4, false, false, false);
    }
    if (n == v)
    {
        r9.i = r10.i;
    }
    tmp = r7.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r7.i) >= ((uint32_t) r3.i);
    v = (r7.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
    if (n == v)
    {
        tmp = ip.i - r4.i;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) ip.i) >= ((uint32_t) r4.i);
        v = (ip.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    }
    if (n != v)
    {
        goto L16;
    }
    counters[4] ++;
    r2.i = sp.i + 16;
    load_counter ++;
    ldr(&r0.i, &r8.i, ((uint32_t)r4.i << 2), 4, false, false, false);
    load_counter ++;
    ldr(&r1.i, &r8.i, ((uint32_t)r3.i << 2), 4, false, false, false);
    r2.i = r2.i + ((uint32_t)r5.i << 2);
    r6.i = r3.i;
L7:
    counters[5] ++;
    tmp = r0.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) r1.i);
    v = (r0.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    r5.i = r5.i + 1;
    if (n == v)
    {
        goto L8;
    }
L30:
    counters[6] ++;
    tmp = r7.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r7.i) >= ((uint32_t) r6.i);
    v = (r7.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
    r4.i = r4.i + 1;
    store_counter ++;
    str(&r0.i, &r2.i, 4, 4, false, true, false);
    if (n != v)
    {
        r0.i = 0;
    }
    if (n == v)
    {
        r0.i = 1;
    }
    tmp = r4.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) ip.i);
    v = (r4.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z && n == v)
    {
        r0.i = 0;
    }
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (z)
    {
        goto L6;
    }
    counters[7] ++;
    load_counter ++;
    ldr(&r0.i, &r8.i, ((uint32_t)r4.i << 2), 4, false, false, false);
    r5.i = r5.i + 1;
    tmp = r0.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) r1.i);
    v = (r0.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (n != v)
    {
        goto L30;
    }
L8:
    counters[8] ++;
    r6.i = r6.i + 1;
    store_counter ++;
    str(&r1.i, &r2.i, 4, 4, false, true, false);
    tmp = r6.i - r7.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) r7.i);
    v = (r6.i&0x80000000) != (r7.i&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    if (!z && n == v)
    {
        r1.i = 0;
    }
    if (z || n != v)
    {
        r1.i = 1;
    }
    tmp = ip.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r4.i);
    v = (ip.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (n != v)
    {
        r1.i = 0;
    }
    tmp = r1.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 0);
    v = (r1.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (z)
    {
        goto L6;
    }
    counters[9] ++;
    load_counter ++;
    ldr(&r1.i, &r8.i, ((uint32_t)r6.i << 2), 4, false, false, false);
    goto L7;
L16:
    counters[10] ++;
    r6.i = r3.i;
L6:
    counters[11] ++;
    tmp = ip.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r4.i);
    v = (ip.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (n != v)
    {
        goto L11;
    }
    counters[12] ++;
    r2.i = r3.i - r4.i;
    store_counter ++;
    str(&r3.i, &sp.i, 0, 4, false, true, false);
    r3.i = sp.i + 16;
    r1.i = r8.i + ((uint32_t)r4.i << 2);
    r0.i = r3.i + ((uint32_t)r5.i << 2);
    r2.i = (uint32_t)r2.i << 2;
    memcpy_help();
    counters[13] ++;
    load_counter ++;
    ldr(&r3.i, &sp.i, 0, 4, false, true, false);
    r5.i = r5.i + r3.i;
    r5.i = r5.i - r4.i;
L11:
    counters[14] ++;
    tmp = r7.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r7.i) >= ((uint32_t) r6.i);
    v = (r7.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
    if (n != v)
    {
        goto L12;
    }
    counters[15] ++;
    r2.i = r7.i + 1;
    r3.i = sp.i + 16;
    r2.i = r2.i - r6.i;
    r0.i = r3.i + ((uint32_t)r5.i << 2);
    r1.i = r8.i + ((uint32_t)r6.i << 2);
    r5.i = r5.i + r2.i;
    r2.i = (uint32_t)r2.i << 2;
    memcpy_help();
L12:
    counters[16] ++;
    r3.i = fp.i + r9.i;
    tmp = r3.i - r10.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r10.i);
    v = (r3.i&0x80000000) != (r10.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (n != v)
    {
        r4.i = r9.i;
    }
    if (n != v)
    {
        goto L13;
    }
L31:
    counters[17] ++;
    r2.i = r7.i + 1;
    r1.i = sp.i + 16;
    r0.i = r8.i;
    fp.i = (uint32_t)fp.i << 1;
    r2.i = (uint32_t)r2.i << 2;
    r4.i = r8.i;
    memcpy_help();
    counters[18] ++;
    load_counter ++;
    ldr(&r5.i, &sp.i, 8, 4, false, false, false);
    load_counter ++;
    ldr(&r6.i, &sp.i, 12, 4, false, false, false);
L15:
    counters[19] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 4, 4, false, true, false);
    r1.i = r6.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[20] ++;
    tmp = r5.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r4.i);
    v = (r5.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (!z)
    {
        goto L15;
    }
    counters[21] ++;
    r0.i = (LC1 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC1 >> 16) << 16);
    printf("%s\n", malloc_0+r0.i);
    counters[22] ++;
    tmp = r10.i - fp.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r10.i) >= ((uint32_t) fp.i);
    v = (r10.i&0x80000000) != (fp.i&0x80000000) && (tmp&0x80000000) != (r10.i&0x80000000);
    if (!z && n == v)
    {
        goto L18;
    }
    counters[23] ++;
    sp.i = sp.i + 220;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false, false);
    ldr(&r7.i, &sp.i, 3*4, 4, false, false, false);
    ldr(&r8.i, &sp.i, 4*4, 4, false, false, false);
    ldr(&r9.i, &sp.i, 5*4, 4, false, false, false);
    ldr(&r10.i, &sp.i, 6*4, 4, false, false, false);
    ldr(&fp.i, &sp.i, 7*4, 4, false, false, false);
    ldr(&pc.i, &sp.i, 8*4, 4, false, false, false);
    sp.i += 36;
    return;

}

void show()
{
    counters[24] ++;
    store_counter ++;
    sp.i -= 16;
    str(&r4.i, &sp.i, 0*4, 4, false, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false, false);
    str(&lr.i, &sp.i, 3*4, 4, false, false, false);
    r5.i = r1.i - 0;
    z = r5.i == 0;
    n = r5.i & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 0);
    v = (r1.i&0x80000000) != (0&0x80000000) && (r5.i&0x80000000) != (r1.i&0x80000000);
    if (z || n != v)
    {
        goto L33;
    }
    counters[25] ++;
    r6.i = (LC0 & 0xffff);
    r5.i = r0.i + ((uint32_t)r5.i << 2);
    r6.i = r6.i | (((uint32_t)LC0 >> 16) << 16);
    r4.i = r0.i;
L34:
    counters[26] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 4, 4, false, true, false);
    r1.i = r6.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[27] ++;
    tmp = r5.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r4.i);
    v = (r5.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (!z)
    {
        goto L34;
    }
L33:
    counters[28] ++;
    r0.i = (LC1 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC1 >> 16) << 16);
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false, false);
    ldr(&lr.i, &sp.i, 3*4, 4, false, false, false);
    sp.i += 16;
    printf("%s\n", malloc_0+r0.i);
    return;

}

void main()
{
    malloc_start();
    counters[29] ++;
    store_counter ++;
    sp.i -= 16;
    str(&r4.i, &sp.i, 0*4, 4, false, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false, false);
    str(&lr.i, &sp.i, 3*4, 4, false, false, false);
    sp.i = sp.i - 80;
    r1.i = 6;
    r2.i = 6;
    r0.i = sp.i;
    r3.i = 5;
    store_counter ++;
    str(&r2.i, &sp.i, 0, 4, false, true, false);
    str(&r3.i, &sp.i, 4, 4, false, true, false);
    r2.i = 4;
    r3.i = 3;
    store_counter ++;
    str(&r2.i, &sp.i, 8, 4, false, false, false);
    str(&r3.i, &sp.i, 12, 4, false, false, false);
    r2.i = 2;
    r3.i = 1;
    store_counter ++;
    str(&r2.i, &sp.i, 16, 4, false, false, false);
    str(&r3.i, &sp.i, 20, 4, false, false, false);
    mergesort();
    counters[30] ++;
    r0.i = (LC2 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC2 >> 16) << 16);
    printf("%s\n", malloc_0+r0.i);
    counters[31] ++;
    r5.i = (LC0 & 0xffff);
    r6.i = sp.i + 24;
    r5.i = r5.i | (((uint32_t)LC0 >> 16) << 16);
    r4.i = sp.i;
L38:
    counters[32] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 4, 4, false, true, false);
    r1.i = r5.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[33] ++;
    tmp = r6.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) r4.i);
    v = (r6.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    if (!z)
    {
        goto L38;
    }
    counters[34] ++;
    r0.i = 0;
    sp.i = sp.i + 80;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false, false);
    ldr(&pc.i, &sp.i, 3*4, 4, false, false, false);
    sp.i += 16;
    counter_summary();
    return;

}

