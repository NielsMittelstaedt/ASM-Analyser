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

reg r1, r3, r0, r2;

int32_t LC1, LC2, LC3, LC4, LC5, LC6, LC7, LC0, __PRETTY_FUNCTION__4635;

int counters[42] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[42] = {11,18,2,8,6,2,6,2,1,3,18,4,3,2,8,4,3,10,8,1,4,16,8,4,8,3,6,4,8,3,3,8,4,8,3,6,4,8,3,3,3,3};


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

    int32_t malloc_total = (int32_t) ((uint8_t*) malloc(190) - malloc_0);
    LC1 = malloc_total;
    strcpy(malloc_0+LC1, "Test 1.... \000");

    LC2 = malloc_total + 17;
    strcpy(malloc_0+LC2, "../test_files/c_in/binary_search.c\000");

    LC3 = malloc_total + 57;
    strcpy(malloc_0+LC3, "result == 3\000");

    LC4 = malloc_total + 74;
    strcpy(malloc_0+LC4, "passed recursive... \000");

    LC5 = malloc_total + 100;
    strcpy(malloc_0+LC5, "passed iterative...\000");

    LC6 = malloc_total + 125;
    strcpy(malloc_0+LC6, "Test 2.... \000");

    LC7 = malloc_total + 142;
    strcpy(malloc_0+LC7, "result == -1\000");

    LC0 = malloc_total + 160;
    int32_t arrayLC0[] = {2,3,4,10,40};
    for(int i=0; i<5; i++) str(&arrayLC0[i], &LC0, i*4, 4, false, false, false);

    __PRETTY_FUNCTION__4635 = malloc_total + 180;
    strcpy(malloc_0+__PRETTY_FUNCTION__4635, "test\000");

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

void binarysearch1();
void binarysearch2();
void test();
void main();

void assert_help()
{
    __assert_fail(malloc_0+r0.i, malloc_0+r1.i, r2.i, malloc_0+r3.i);
}

void binarysearch1()
{
    counters[0] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&fp.i, &sp.i, 0, 4, false, false, false);
    fp.i = sp.i + (4);
    sp.i = sp.i - (24);
    store_counter ++;
    str(&r0.i, &fp.i, -16, 4, false, false, false);
    store_counter ++;
    str(&r1.i, &fp.i, -20, 4, false, false, false);
    store_counter ++;
    str(&r2.i, &fp.i, -24, 4, false, false, false);
    store_counter ++;
    str(&r3.i, &fp.i, -28, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -24, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false, false);
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
    ldr(&r2.i, &fp.i, -24, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false, false);
    r3.i = r2.i - (r3.i);
    r2.i = (uint32_t)r3.i >> 31;
    r3.i = r2.i + (r3.i);
    r3.i = r3.i >> 1;
    r2.i = r3.i;
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false, false);
    r3.i = r3.i + (r2.i);
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -16, 4, false, false, false);
    r3.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -28, 4, false, false, false);
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
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    goto L4;
L3:
    counters[3] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -16, 4, false, false, false);
    r3.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -28, 4, false, false, false);
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
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r2.i = r3.i - (1);
    load_counter ++;
    ldr(&r3.i, &fp.i, -28, 4, false, false, false);
    load_counter ++;
    ldr(&r1.i, &fp.i, -20, 4, false, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, -16, 4, false, false, false);
    binarysearch1();
    counters[5] ++;
    r3.i = r0.i;
    goto L4;
L5:
    counters[6] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r1.i = r3.i + (1);
    load_counter ++;
    ldr(&r3.i, &fp.i, -28, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -24, 4, false, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, -16, 4, false, false, false);
    binarysearch1();
    counters[7] ++;
    r3.i = r0.i;
    goto L4;
L2:
    counters[8] ++;
    r3.i = ~0;
L4:
    counters[9] ++;
    r0.i = r3.i;
    sp.i = fp.i - (4);
    load_counter ++;
    ldr(&fp.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;

}

void binarysearch2()
{
    counters[10] ++;
    store_counter ++;
    str(&fp.i, &sp.i, -4, 4, true, false, false);
    fp.i = sp.i + (0);
    sp.i = sp.i - (28);
    store_counter ++;
    str(&r0.i, &fp.i, -16, 4, false, false, false);
    store_counter ++;
    str(&r1.i, &fp.i, -20, 4, false, false, false);
    store_counter ++;
    str(&r2.i, &fp.i, -24, 4, false, false, false);
    store_counter ++;
    str(&r3.i, &fp.i, -28, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -24, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false, false);
    r3.i = r2.i - (r3.i);
    r2.i = (uint32_t)r3.i >> 31;
    r3.i = r2.i + (r3.i);
    r3.i = r3.i >> 1;
    r2.i = r3.i;
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false, false);
    r3.i = r3.i + (r2.i);
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
    goto L7;
L13:
    counters[11] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -24, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (z || n != v)
    {
        goto L8;
    }
    counters[12] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -24, 4, false, false, false);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (n == v)
    {
        goto L9;
    }
L8:
    counters[13] ++;
    r3.i = ~0;
    goto L10;
L9:
    counters[14] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -16, 4, false, false, false);
    r3.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -28, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n == v)
    {
        goto L11;
    }
    counters[15] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = r3.i - (1);
    store_counter ++;
    str(&r3.i, &fp.i, -24, 4, false, false, false);
    goto L12;
L11:
    counters[16] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = r3.i + (1);
    store_counter ++;
    str(&r3.i, &fp.i, -20, 4, false, false, false);
L12:
    counters[17] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -24, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false, false);
    r3.i = r2.i - (r3.i);
    r2.i = (uint32_t)r3.i >> 31;
    r3.i = r2.i + (r3.i);
    r3.i = r3.i >> 1;
    r2.i = r3.i;
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false, false);
    r3.i = r3.i + (r2.i);
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
L7:
    counters[18] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -16, 4, false, false, false);
    r3.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -28, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z)
    {
        goto L13;
    }
    counters[19] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
L10:
    counters[20] ++;
    r0.i = r3.i;
    sp.i = fp.i + (0);
    load_counter ++;
    ldr(&fp.i, &sp.i, 4, 4, false, true, false);
    return;

}

void test()
{
    counters[21] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&fp.i, &sp.i, 0, 4, false, false, false);
    fp.i = sp.i + (4);
    sp.i = sp.i - (32);
    r3.i = (LC0 & 0xffff);
    r3.i = r3.i | (((uint32_t)LC0 >> 16) << 16);
    ip.i = fp.i - (36);
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
    ldr(&r3.i, &lr.i, 0, 4, false, false, false);
    store_counter ++;
    str(&r3.i, &ip.i, 0, 4, false, false, false);
    r3.i = 5;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
    r0.i = (LC1 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC1 >> 16) << 16);
    printf(malloc_0+r0.i, r1.i);
    counters[22] ++;
    r3.i = 10;
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r2.i = r3.i - (1);
    r0.i = fp.i - (36);
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false, false);
    r1.i = 0;
    binarysearch1();
    counters[23] ++;
    store_counter ++;
    str(&r0.i, &fp.i, -16, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false, false);
    tmp = r3.i - 3;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 3);
    v = (r3.i&0x80000000) != (3&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L15;
    }
    counters[24] ++;
    r3.i = (__PRETTY_FUNCTION__4635 & 0xffff);
    r3.i = r3.i | (((uint32_t)__PRETTY_FUNCTION__4635 >> 16) << 16);
    r2.i = 87;
    r1.i = (LC2 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC2 >> 16) << 16);
    r0.i = (LC3 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC3 >> 16) << 16);
    assert_help();
L15:
    counters[25] ++;
    r0.i = (LC4 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC4 >> 16) << 16);
    printf(malloc_0+r0.i, r1.i);
    counters[26] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r2.i = r3.i - (1);
    r0.i = fp.i - (36);
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false, false);
    r1.i = 0;
    binarysearch2();
    counters[27] ++;
    store_counter ++;
    str(&r0.i, &fp.i, -16, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false, false);
    tmp = r3.i - 3;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 3);
    v = (r3.i&0x80000000) != (3&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L16;
    }
    counters[28] ++;
    r3.i = (__PRETTY_FUNCTION__4635 & 0xffff);
    r3.i = r3.i | (((uint32_t)__PRETTY_FUNCTION__4635 >> 16) << 16);
    r2.i = 90;
    r1.i = (LC2 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC2 >> 16) << 16);
    r0.i = (LC3 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC3 >> 16) << 16);
    assert_help();
L16:
    counters[29] ++;
    r0.i = (LC5 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC5 >> 16) << 16);
    printf("%s\n", malloc_0+r0.i);
    counters[30] ++;
    r0.i = (LC6 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC6 >> 16) << 16);
    printf(malloc_0+r0.i, r1.i);
    counters[31] ++;
    r3.i = 5;
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r2.i = r3.i - (1);
    r0.i = fp.i - (36);
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false, false);
    r1.i = 0;
    binarysearch1();
    counters[32] ++;
    store_counter ++;
    str(&r0.i, &fp.i, -16, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false, false);
    tmp = r3.i + 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) tmp) < ((uint32_t) r3.i);
    v = (r3.i&0x80000000) == (1&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L17;
    }
    counters[33] ++;
    r3.i = (__PRETTY_FUNCTION__4635 & 0xffff);
    r3.i = r3.i | (((uint32_t)__PRETTY_FUNCTION__4635 >> 16) << 16);
    r2.i = 97;
    r1.i = (LC2 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC2 >> 16) << 16);
    r0.i = (LC7 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC7 >> 16) << 16);
    assert_help();
L17:
    counters[34] ++;
    r0.i = (LC4 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC4 >> 16) << 16);
    printf(malloc_0+r0.i, r1.i);
    counters[35] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r2.i = r3.i - (1);
    r0.i = fp.i - (36);
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false, false);
    r1.i = 0;
    binarysearch2();
    counters[36] ++;
    store_counter ++;
    str(&r0.i, &fp.i, -16, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false, false);
    tmp = r3.i + 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) tmp) < ((uint32_t) r3.i);
    v = (r3.i&0x80000000) == (1&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L18;
    }
    counters[37] ++;
    r3.i = (__PRETTY_FUNCTION__4635 & 0xffff);
    r3.i = r3.i | (((uint32_t)__PRETTY_FUNCTION__4635 >> 16) << 16);
    r2.i = 100;
    r1.i = (LC2 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC2 >> 16) << 16);
    r0.i = (LC7 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC7 >> 16) << 16);
    assert_help();
L18:
    counters[38] ++;
    r0.i = (LC5 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC5 >> 16) << 16);
    printf("%s\n", malloc_0+r0.i);
    counters[39] ++;
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
    counters[40] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&fp.i, &sp.i, 0, 4, false, false, false);
    fp.i = sp.i + (4);
    test();
    counters[41] ++;
    r3.i = 0;
    r0.i = r3.i;
    load_counter ++;
    ldr(&fp.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;

}

