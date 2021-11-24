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

reg r1, r0, r3, r2;

int32_t LC1, LC2, LC0;

int counters[18] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[18] = {8,2,5,5,5,14,26,3,6,3,4,17,3,3,9,3,4,4};


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

    int32_t malloc_total = (int32_t) ((uint8_t*) malloc(53) - malloc_0);
    LC1 = malloc_total;
    strcpy(malloc_0+LC1, "Sorted array: \000");

    LC2 = malloc_total + 20;
    strcpy(malloc_0+LC2, "%d \000");

    LC0 = malloc_total + 29;
    int32_t arrayLC0[] = {6,5,4,3,2,1};
    for(int i=0; i<6; i++) str(&arrayLC0[i], &LC0, i*4, 4, false, false, false);

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "comb_sort.c";

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

void sort();
void main();

void d2iz()
{
    int64_t op_int = ((int64_t) r1.i) << 32 | ((int64_t) r0.i);
    r0.i = (int32_t) *(double *)&op_int;
}
void ddiv()
{
    int64_t op1 = ((int64_t) r1.i) << 32 | ((int64_t) r0.i);
    int64_t op2 = ((int64_t) r3.i) << 32 | ((int64_t) r2.i);
    double result = *(double *)&op1 / *(double *)&op2;
    int64_t result_int64 = *(int64_t *)&result;
    r1.i = (int32_t) (result_int64 >> 32);
    r0.i = (int32_t) result_int64;
}
void i2d()
{
    double result = (double) r0.i;
    int64_t result_int64 = *(int64_t *)&result;
    r1.i = (int32_t) (result_int64 >> 32);
    r0.i = (int32_t) result_int64;
}

void sort()
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
    str(&r0.i, &fp.i, -24, 4, false, false, false);
    store_counter ++;
    str(&r1.i, &fp.i, -28, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -28, 4, false, false, false);
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
    goto L2;
L6:
    counters[1] ++;
    load_counter ++;
    ldr(&r0.i, &fp.i, -8, 4, false, false, false);
    i2d();
    counters[2] ++;
    r2.i = 52429;
    r2.i = r2.i | (52428 << 16);
    r3.i = 52428;
    r3.i = r3.i | (16372 << 16);
    ddiv();
    counters[3] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r2.i;
    r1.i = r3.i;
    d2iz();
    counters[4] ++;
    r3.i = r0.i;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false, false);
    goto L3;
L5:
    counters[5] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -24, 4, false, false, false);
    r3.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r2.i, &r3.i, 0, 4, false, true, false);
    load_counter ++;
    ldr(&r1.i, &fp.i, -12, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = r1.i + (r3.i);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r1.i, &fp.i, -24, 4, false, false, false);
    r3.i = r1.i + (r3.i);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, true, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (z || n != v)
    {
        goto L4;
    }
    counters[6] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -24, 4, false, false, false);
    r3.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, true, false);
    store_counter ++;
    str(&r3.i, &fp.i, -16, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -12, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = r2.i + (r3.i);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -24, 4, false, false, false);
    r2.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r1.i, &fp.i, -24, 4, false, false, false);
    r3.i = r1.i + (r3.i);
    load_counter ++;
    ldr(&r2.i, &r2.i, 0, 4, false, true, false);
    store_counter ++;
    str(&r2.i, &r3.i, 0, 4, false, true, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -12, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = r2.i + (r3.i);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -24, 4, false, false, false);
    r3.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r2.i, &fp.i, -16, 4, false, false, false);
    store_counter ++;
    str(&r2.i, &r3.i, 0, 4, false, true, false);
L4:
    counters[7] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false, false);
    r3.i = r3.i + (1);
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false, false);
L3:
    counters[8] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -12, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r2.i, &fp.i, -28, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z && n == v)
    {
        goto L5;
    }
L2:
    counters[9] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    tmp = r3.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 1);
    v = (r3.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z && n == v)
    {
        goto L6;
    }
    counters[10] ++;
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
    counters[11] ++;
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
    tmp = lr.i;
    ldr(&r0.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    ldr(&r1.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    lr.i = tmp;
    store_counter ++;
    tmp = ip.i;
    str(&r0.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    str(&r1.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    ip.i = tmp;
    r3.i = 6;
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false, false);
    r3.i = fp.i - (36);
    load_counter ++;
    ldr(&r1.i, &fp.i, -12, 4, false, false, false);
    r0.i = r3.i;
    sort();
    counters[12] ++;
    r0.i = (LC1 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC1 >> 16) << 16);
    printf(malloc_0+r0.i, r1.i);
    counters[13] ++;
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
    goto L8;
L9:
    counters[14] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    r2.i = fp.i - (4);
    r3.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r3.i, &r3.i, -32, 4, false, false, false);
    r1.i = r3.i;
    r0.i = (LC2 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC2 >> 16) << 16);
    printf(malloc_0+r0.i, r1.i);
    counters[15] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = r3.i + (1);
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
L8:
    counters[16] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -8, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n != v)
    {
        goto L9;
    }
    counters[17] ++;
    r3.i = 0;
    r0.i = r3.i;
    sp.i = fp.i - (4);
    load_counter ++;
    ldr(&fp.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    counter_summary();
    return;

}

