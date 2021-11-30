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

reg r0, r3, r2, r1;

int32_t LC1, LC2, LC3, LC4, LC0, __PRETTY_FUNCTION__4682;

int counters[17] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[17] = {8,2,6,20,4,12,4,1,4,20,4,4,8,3,3,3,3};


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
    malloc_0 = (uint8_t*) malloc(1);
    uint8_t* stack_ptr = (uint8_t*) malloc(20000);
    sp.i = (int32_t) (stack_ptr - malloc_0) + 19996;
    fp = sp;

    int32_t malloc_total = (int32_t) ((uint8_t*) malloc(169) - malloc_0);
    LC1 = malloc_total;
    strcpy(malloc_0+LC1, "1st test... \000");

    LC2 = malloc_total + 18;
    strcpy(malloc_0+LC2, "../test_files/c_in/floyd_cycle_detection_algorithm.");

    LC3 = malloc_total + 71;
    strcpy(malloc_0+LC3, "index == 1\000");

    LC4 = malloc_total + 87;
    strcpy(malloc_0+LC4, "passed\000");

    LC0 = malloc_total + 99;
    int32_t arrayLC0[] = {1,1,2,3,5,8,13,21,34,55,89,144,233,377,610};
    for(int i=0; i<15; i++) str(&arrayLC0[i], &LC0, i*4, 4, false, false, false);

    __PRETTY_FUNCTION__4682 = malloc_total + 159;
    strcpy(malloc_0+__PRETTY_FUNCTION__4682, "test\000");

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "floyd_cycle_detection_algorithm.c";

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

void duplicateNumber();
void test();
void main();

void assert_help()
{
    __assert_fail(malloc_0+r0.i, malloc_0+r1.i, r2.i, malloc_0+r3.i);
}

void duplicateNumber()
{
    counters[0] ++;
    store_counter ++;
    str(&fp.i, &sp.i, -4, 4, true, false, false);
    fp.i = sp.i + (0);
    sp.i = sp.i - (20);
    store_counter ++;
    str(&r0.i, &fp.i, -16, 4, false, false, false);
    store_counter ++;
    str(&r1.i, &fp.i, -20, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false, false);
    tmp = r3.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 1);
    v = (r3.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (c && !z)
    {
        goto L2;
    }
    counters[1] ++;
    r3.i = ~0;
    goto L3;
L2:
    counters[2] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, false, false);
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, false, false);
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false, false);
L4:
    counters[3] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -16, 4, false, false, false);
    r3.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, false, false);
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -16, 4, false, false, false);
    r3.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -16, 4, false, false, false);
    r3.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, false, false);
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -8, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z)
    {
        goto L4;
    }
    counters[4] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, false, false);
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
    goto L5;
L6:
    counters[5] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -16, 4, false, false, false);
    r3.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, false, false);
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -16, 4, false, false, false);
    r3.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, false, false);
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false, false);
L5:
    counters[6] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -8, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z)
    {
        goto L6;
    }
    counters[7] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
L3:
    counters[8] ++;
    r0.i = r3.i;
    sp.i = fp.i + (0);
    load_counter ++;
    ldr(&fp.i, &sp.i, 4, 4, false, true, false);
    return;

}

void test()
{
    counters[9] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&fp.i, &sp.i, 0, 4, false, false, false);
    fp.i = sp.i + (4);
    sp.i = sp.i - (72);
    r3.i = (LC0 & 0xffff);
    r3.i = r3.i | (((uint32_t)LC0 >> 16) << 16);
    ip.i = fp.i - (72);
    lr.i = r3.i;
    load_counter ++;
    ldr(&r0.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    ldr(&r1.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    ldr(&r2.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    ldr(&r3.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    store_counter ++;
    str(&r0.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    str(&r1.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    str(&r2.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    str(&r3.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    load_counter ++;
    ldr(&r0.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    ldr(&r1.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    ldr(&r2.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    ldr(&r3.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    store_counter ++;
    str(&r0.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    str(&r1.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    str(&r2.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    str(&r3.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    load_counter ++;
    ldr(&r0.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    ldr(&r1.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    ldr(&r2.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    ldr(&r3.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    store_counter ++;
    str(&r0.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    str(&r1.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    str(&r2.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    str(&r3.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    load_counter ++;
    tmp = lr.i;
    ldr(&r0.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    ldr(&r1.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    ldr(&r2.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    lr.i = tmp;
    store_counter ++;
    tmp = ip.i;
    str(&r0.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    str(&r1.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    str(&r2.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    ip.i = tmp;
    r3.i = 15;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
    r0.i = (LC1 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC1 >> 16) << 16);
    printf(malloc_0+r0.i, r1.i);
    counters[10] ++;
    r3.i = fp.i - (72);
    load_counter ++;
    ldr(&r1.i, &fp.i, -8, 4, false, false, false);
    r0.i = r3.i;
    duplicateNumber();
    counters[11] ++;
    store_counter ++;
    str(&r0.i, &fp.i, -12, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false, false);
    tmp = r3.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 1);
    v = (r3.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L8;
    }
    counters[12] ++;
    r3.i = (__PRETTY_FUNCTION__4682 & 0xffff);
    r3.i = r3.i | (((uint32_t)__PRETTY_FUNCTION__4682 >> 16) << 16);
    r2.i = 56;
    r1.i = (LC2 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC2 >> 16) << 16);
    r0.i = (LC3 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC3 >> 16) << 16);
    assert_help();
L8:
    counters[13] ++;
    r0.i = (LC4 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC4 >> 16) << 16);
    printf("%s\n", malloc_0+r0.i);
    counters[14] ++;
    sp.i = fp.i - (4);
    load_counter ++;
    ldr(&fp.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;

}

void main()
{
    malloc_start();
    counters[15] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&fp.i, &sp.i, 0, 4, false, false, false);
    fp.i = sp.i + (4);
    test();
    counters[16] ++;
    r3.i = 0;
    r0.i = r3.i;
    load_counter ++;
    ldr(&fp.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;

}

