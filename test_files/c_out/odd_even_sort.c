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

reg r3, r6, r0, r4, r1, r2, r5, r7;

int32_t LC4, LC5, LC6, LC7, L30, LC0, LC1, LC2, LC3, __PRETTY_FUNCTION__5675;

int counters[34] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[34] = {5,7,2,5,5,2,1,9,2,4,1,2,2,1,30,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,3,3,7,7};


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

    int32_t malloc_total = (int32_t) ((uint8_t*) malloc(250) - malloc_0);
    LC4 = malloc_total;
    strcpy(malloc_0+LC4, "../test_files/c_in/odd_even_sort.c\000");

    LC5 = malloc_total + 40;
    strcpy(malloc_0+LC5, "arr1[i] == arr1Soln[i]\000");

    LC6 = malloc_total + 68;
    strcpy(malloc_0+LC6, "arr2[i] == arr2Soln[i]\000");

    LC7 = malloc_total + 96;
    strcpy(malloc_0+LC7, "All tests have passed!\000");

    L30 = malloc_total + 124;
    int32_t arrayL30[] = {LC0+112};
    for(int i=0; i<1; i++) str(&arrayL30[i], &L30, i*4, 4, false, false, false);

    LC0 = malloc_total + 128;
    int32_t arrayLC0[] = {-9,2,3,1};
    for(int i=0; i<4; i++) str(&arrayLC0[i], &LC0, i*4, 4, false, false, false);

    LC1 = malloc_total + 144;
    int32_t arrayLC1[] = {-9,1,2,3};
    for(int i=0; i<4; i++) str(&arrayLC1[i], &LC1, i*4, 4, false, false, false);

    LC2 = malloc_total + 160;
    int32_t arrayLC2[] = {9,7,5,3,8,2,1,4,0,6};
    for(int i=0; i<10; i++) str(&arrayLC2[i], &LC2, i*4, 4, false, false, false);

    LC3 = malloc_total + 200;
    int32_t arrayLC3[] = {0,1,2,3,4,5,6,7,8,9};
    for(int i=0; i<10; i++) str(&arrayLC3[i], &LC3, i*4, 4, false, false, false);

    __PRETTY_FUNCTION__5675 = malloc_total + 240;
    strcpy(malloc_0+__PRETTY_FUNCTION__5675, "test\000");

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "odd_even_sort.c";

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
void oddEvenSort();
void main();

void assert_help()
{
    __assert_fail(malloc_0+r0.i, malloc_0+r1.i, r2.i, malloc_0+r3.i);
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

void oddEvenSort()
{
    counters[1] ++;
    store_counter ++;
    sp.i -= 16;
    str(&r4.i, &sp.i, 0*4, 4, false, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false, false);
    str(&lr.i, &sp.i, 3*4, 4, false, false, false);
    r2.i = r0.i + 4;
    lr.i = r1.i - 1;
    r6.i = r0.i - 8;
    r5.i = r0.i - 4;
    r3.i = 0;
    r4.i = 1;
L4:
    counters[2] ++;
    tmp = lr.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) r3.i);
    v = (lr.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    if (z || n != v)
    {
        goto L23;
    }
L5:
    counters[3] ++;
    load_counter ++;
    ldr(&r1.i, &r0.i, ((uint32_t)r3.i << 2), 4, false, false, false);
    load_counter ++;
    ldr(&ip.i, &r2.i, ((uint32_t)r3.i << 2), 4, false, false, false);
    r3.i = r3.i + 2;
    tmp = r1.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) ip.i);
    v = (r1.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (z || n != v)
    {
        goto L4;
    }
    counters[4] ++;
    tmp = lr.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) r3.i);
    v = (lr.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    store_counter ++;
    str(&ip.i, &r6.i, ((uint32_t)r3.i << 2), 4, false, false, false);
    r4.i = 0;
    store_counter ++;
    str(&r1.i, &r5.i, ((uint32_t)r3.i << 2), 4, false, false, false);
    if (!z && n == v)
    {
        goto L5;
    }
    counters[5] ++;
    tmp = lr.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) 1);
    v = (lr.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    if (z || n != v)
    {
        goto L12;
    }
L6:
    counters[6] ++;
    r3.i = 1;
L11:
    counters[7] ++;
    load_counter ++;
    ldr(&r1.i, &r0.i, ((uint32_t)r3.i << 2), 4, false, false, false);
    load_counter ++;
    ldr(&ip.i, &r2.i, ((uint32_t)r3.i << 2), 4, false, false, false);
    tmp = r1.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) ip.i);
    v = (r1.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    store_counter ++;
    if (!z && n == v)
    {
        str(&ip.i, &r0.i, ((uint32_t)r3.i << 2), 4, false, false, false);
    }
    store_counter ++;
    if (!z && n == v)
    {
        str(&r1.i, &r2.i, ((uint32_t)r3.i << 2), 4, false, false, false);
    }
    r3.i = r3.i + 2;
    if (!z && n == v)
    {
        r4.i = 0;
    }
    tmp = lr.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) r3.i);
    v = (lr.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    if (!z && n == v)
    {
        goto L11;
    }
    counters[8] ++;
    tmp = r4.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 0);
    v = (r4.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    load_counter ++;
    if (!z)
    {
        ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
        ldr(&r5.i, &sp.i, 1*4, 4, false, false, false);
        ldr(&r6.i, &sp.i, 2*4, 4, false, false, false);
        ldr(&pc.i, &sp.i, 3*4, 4, false, false, false);
        sp.i += 16;
        return;
    }
L12:
    counters[9] ++;
    tmp = lr.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) 0);
    v = (lr.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    r4.i = 1;
    r3.i = 0;
    if (!z && n == v)
    {
        goto L5;
    }
    counters[10] ++;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false, false);
    ldr(&pc.i, &sp.i, 3*4, 4, false, false, false);
    sp.i += 16;
    return;
L23:
    counters[11] ++;
    tmp = lr.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) 1);
    v = (lr.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    if (!z && n == v)
    {
        goto L6;
    }
    counters[12] ++;
    tmp = r4.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 0);
    v = (r4.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (z)
    {
        goto L12;
    }
    counters[13] ++;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false, false);
    ldr(&pc.i, &sp.i, 3*4, 4, false, false, false);
    sp.i += 16;
    return;

}

void main()
{
    malloc_start();
    counters[14] ++;
    ip.i = (LC0 & 0xffff);
    ip.i = ip.i | (((uint32_t)LC0 >> 16) << 16);
    store_counter ++;
    sp.i -= 20;
    str(&r4.i, &sp.i, 0*4, 4, false, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false, false);
    str(&r7.i, &sp.i, 3*4, 4, false, false, false);
    str(&lr.i, &sp.i, 4*4, 4, false, false, false);
    sp.i = sp.i - 116;
    load_counter ++;
    ldr(&r0.i, &ip.i, 0*4, 4, false, false, false);
    ldr(&r1.i, &ip.i, 1*4, 4, false, false, false);
    ldr(&r2.i, &ip.i, 2*4, 4, false, false, false);
    ldr(&r3.i, &ip.i, 3*4, 4, false, false, false);
    lr.i = ip.i + 16;
    r6.i = sp.i;
    r5.i = ip.i + 32;
    r7.i = sp.i + 16;
    r4.i = sp.i + 32;
    ip.i = ip.i + 72;
    store_counter ++;
    str(&r0.i, &r6.i, 0*4, 4, false, false, false);
    str(&r1.i, &r6.i, 1*4, 4, false, false, false);
    str(&r2.i, &r6.i, 2*4, 4, false, false, false);
    str(&r3.i, &r6.i, 3*4, 4, false, false, false);
    load_counter ++;
    ldr(&r0.i, &lr.i, 0*4, 4, false, false, false);
    ldr(&r1.i, &lr.i, 1*4, 4, false, false, false);
    ldr(&r2.i, &lr.i, 2*4, 4, false, false, false);
    ldr(&r3.i, &lr.i, 3*4, 4, false, false, false);
    lr.i = sp.i + 72;
    store_counter ++;
    str(&r0.i, &r7.i, 0*4, 4, false, false, false);
    str(&r1.i, &r7.i, 1*4, 4, false, false, false);
    str(&r2.i, &r7.i, 2*4, 4, false, false, false);
    str(&r3.i, &r7.i, 3*4, 4, false, false, false);
    load_counter ++;
    ldr(&r0.i, &r5.i, 0*4, 4, false, false, false);
    ldr(&r1.i, &r5.i, 1*4, 4, false, false, false);
    ldr(&r2.i, &r5.i, 2*4, 4, false, false, false);
    ldr(&r3.i, &r5.i, 3*4, 4, false, false, false);
    r5.i += 16;
    store_counter ++;
    str(&r0.i, &r4.i, 0*4, 4, false, false, false);
    str(&r1.i, &r4.i, 1*4, 4, false, false, false);
    str(&r2.i, &r4.i, 2*4, 4, false, false, false);
    str(&r3.i, &r4.i, 3*4, 4, false, false, false);
    r4.i += 16;
    load_counter ++;
    ldr(&r0.i, &r5.i, 0*4, 4, false, false, false);
    ldr(&r1.i, &r5.i, 1*4, 4, false, false, false);
    ldr(&r2.i, &r5.i, 2*4, 4, false, false, false);
    ldr(&r3.i, &r5.i, 3*4, 4, false, false, false);
    r5.i += 16;
    store_counter ++;
    str(&r0.i, &r4.i, 0*4, 4, false, false, false);
    str(&r1.i, &r4.i, 1*4, 4, false, false, false);
    str(&r2.i, &r4.i, 2*4, 4, false, false, false);
    str(&r3.i, &r4.i, 3*4, 4, false, false, false);
    r4.i += 16;
    load_counter ++;
    ldr(&r0.i, &r5.i, 0*4, 4, false, false, false);
    ldr(&r1.i, &r5.i, 1*4, 4, false, false, false);
    store_counter ++;
    str(&r0.i, &r4.i, 0*4, 4, false, false, false);
    str(&r1.i, &r4.i, 1*4, 4, false, false, false);
    load_counter ++;
    ldr(&r0.i, &ip.i, 0*4, 4, false, false, false);
    ldr(&r1.i, &ip.i, 1*4, 4, false, false, false);
    ldr(&r2.i, &ip.i, 2*4, 4, false, false, false);
    ldr(&r3.i, &ip.i, 3*4, 4, false, false, false);
    ip.i += 16;
    store_counter ++;
    str(&r0.i, &lr.i, 0*4, 4, false, false, false);
    str(&r1.i, &lr.i, 1*4, 4, false, false, false);
    str(&r2.i, &lr.i, 2*4, 4, false, false, false);
    str(&r3.i, &lr.i, 3*4, 4, false, false, false);
    lr.i += 16;
    load_counter ++;
    ldr(&r0.i, &ip.i, 0*4, 4, false, false, false);
    ldr(&r1.i, &ip.i, 1*4, 4, false, false, false);
    ldr(&r2.i, &ip.i, 2*4, 4, false, false, false);
    ldr(&r3.i, &ip.i, 3*4, 4, false, false, false);
    ip.i += 16;
    store_counter ++;
    str(&r0.i, &lr.i, 0*4, 4, false, false, false);
    str(&r1.i, &lr.i, 1*4, 4, false, false, false);
    str(&r2.i, &lr.i, 2*4, 4, false, false, false);
    str(&r3.i, &lr.i, 3*4, 4, false, false, false);
    lr.i += 16;
    load_counter ++;
    ldr(&r0.i, &ip.i, 0*4, 4, false, false, false);
    ldr(&r1.i, &ip.i, 1*4, 4, false, false, false);
    store_counter ++;
    str(&r0.i, &lr.i, 0*4, 4, false, false, false);
    str(&r1.i, &lr.i, 1*4, 4, false, false, false);
    r0.i = r6.i;
    r1.i = 4;
    oddEvenSort();
    counters[15] ++;
    r0.i = sp.i + 32;
    r1.i = 10;
    oddEvenSort();
    counters[16] ++;
    load_counter ++;
    ldr(&r2.i, &sp.i, 0, 4, false, true, false);
    load_counter ++;
    ldr(&r3.i, &sp.i, 16, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z)
    {
        goto L25;
    }
    counters[17] ++;
    load_counter ++;
    ldr(&r2.i, &sp.i, 4, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &sp.i, 20, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z)
    {
        goto L25;
    }
    counters[18] ++;
    load_counter ++;
    ldr(&r2.i, &sp.i, 8, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &sp.i, 24, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z)
    {
        goto L25;
    }
    counters[19] ++;
    load_counter ++;
    ldr(&r2.i, &sp.i, 12, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &sp.i, 28, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z)
    {
        goto L25;
    }
    counters[20] ++;
    load_counter ++;
    ldr(&r2.i, &sp.i, 32, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &sp.i, 72, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z)
    {
        goto L27;
    }
    counters[21] ++;
    load_counter ++;
    ldr(&r2.i, &sp.i, 36, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &sp.i, 76, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z)
    {
        goto L27;
    }
    counters[22] ++;
    load_counter ++;
    ldr(&r2.i, &sp.i, 40, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &sp.i, 80, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z)
    {
        goto L27;
    }
    counters[23] ++;
    load_counter ++;
    ldr(&r2.i, &sp.i, 44, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &sp.i, 84, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z)
    {
        goto L27;
    }
    counters[24] ++;
    load_counter ++;
    ldr(&r2.i, &sp.i, 48, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &sp.i, 88, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z)
    {
        goto L27;
    }
    counters[25] ++;
    load_counter ++;
    ldr(&r2.i, &sp.i, 52, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &sp.i, 92, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z)
    {
        goto L27;
    }
    counters[26] ++;
    load_counter ++;
    ldr(&r2.i, &sp.i, 56, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &sp.i, 96, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z)
    {
        goto L27;
    }
    counters[27] ++;
    load_counter ++;
    ldr(&r2.i, &sp.i, 60, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &sp.i, 100, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z)
    {
        goto L27;
    }
    counters[28] ++;
    load_counter ++;
    ldr(&r2.i, &sp.i, 64, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &sp.i, 104, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z)
    {
        goto L27;
    }
    counters[29] ++;
    load_counter ++;
    ldr(&r2.i, &sp.i, 68, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &sp.i, 108, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z)
    {
        goto L27;
    }
    counters[30] ++;
    r0.i = (LC7 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC7 >> 16) << 16);
    printf("%s\n", malloc_0+r0.i);
    counters[31] ++;
    r0.i = 0;
    sp.i = sp.i + 116;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false, false);
    ldr(&r7.i, &sp.i, 3*4, 4, false, false, false);
    ldr(&pc.i, &sp.i, 4*4, 4, false, false, false);
    sp.i += 20;
    return;
L27:
    counters[32] ++;
    r1.i = (LC4 & 0xffff);
    r0.i = (LC6 & 0xffff);
    load_counter ++;
    ldr(&r3.i, &L30.i, 0, 4, false, false, false);
    r1.i = r1.i | (((uint32_t)LC4 >> 16) << 16);
    r0.i = r0.i | (((uint32_t)LC6 >> 16) << 16);
    r2.i = 107;
    assert_help();
L25:
    counters[33] ++;
    r1.i = (LC4 & 0xffff);
    r0.i = (LC5 & 0xffff);
    load_counter ++;
    ldr(&r3.i, &L30.i, 0, 4, false, false, false);
    r1.i = r1.i | (((uint32_t)LC4 >> 16) << 16);
    r0.i = r0.i | (((uint32_t)LC5 >> 16) << 16);
    r2.i = 102;
    assert_help();
L31:
    counter_summary();
    return;
}

