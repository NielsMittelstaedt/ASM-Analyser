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

int32_t LC0, LC1, LC2, LC3;

int counters[24] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[24] = {2,10,1,3,1,2,2,7,2,1,3,4,4,2,3,3,8,13,3,3,4,3,2,2};


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

    int32_t malloc_total = (int32_t) ((uint8_t*) malloc(88) - malloc_0);
    LC0 = malloc_total;
    strcpy(malloc_0+LC0, "%d \000");

    LC1 = malloc_total + 9;
    strcpy(malloc_0+LC1, "Insert %d unsorted numbers: \012\000");

    LC2 = malloc_total + 47;
    strcpy(malloc_0+LC2, "Initial array: \000");

    LC3 = malloc_total + 68;
    strcpy(malloc_0+LC3, "Sorted array: \000");

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
void display();
void main();

void ddiv()
{
    int64_t op1 = ((int64_t) r1.i) << 32 | ((int64_t) r0.i);
    int64_t op2 = ((int64_t) r3.i) << 32 | ((int64_t) r2.i);
    double result = *(double *)&op1 / *(double *)&op2;
    int64_t result_int64 = *(int64_t *)&result;
    r1.i = (int32_t) (result_int64 >> 32);
    r0.i = (int32_t) result_int64;
}
void d2iz()
{
    int64_t op_int = ((int64_t) r1.i) << 32 | ((int64_t) r0.i);
    r0.i = (int32_t) *(double *)&op_int;
}
void malloc_help()
{
    uint8_t* ptr = (uint8_t*) malloc(r0.i);
    r0.i = (int32_t) (ptr - malloc_0);
}
void free_help()
{
    free(malloc_0+r0.i);
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
    sp.i -= 32;
    str(&r4.i, &sp.i, 0*4, 4, false, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false, false);
    str(&r7.i, &sp.i, 3*4, 4, false, false, false);
    str(&r8.i, &sp.i, 4*4, 4, false, false, false);
    str(&r9.i, &sp.i, 5*4, 4, false, false, false);
    str(&r10.i, &sp.i, 6*4, 4, false, false, false);
    str(&lr.i, &sp.i, 7*4, 4, false, false, false);
    r6.i = 52429;
    r7.i = 52428;
    r6.i = r6.i | (52428 << 16);
    r7.i = r7.i | (16372 << 16);
    r4.i = r0.i + ((uint32_t)r1.i << 2);
    r9.i = r0.i - 4;
    r8.i = r0.i;
    r5.i = r1.i;
    r0.i = r1.i;
L6:
    counters[2] ++;
    i2d();
    counters[3] ++;
    r2.i = r6.i;
    r3.i = r7.i;
    ddiv();
    counters[4] ++;
    d2iz();
    counters[5] ++;
    tmp = r5.i - r0.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r0.i);
    v = (r5.i&0x80000000) != (r0.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (z || n != v)
    {
        goto L6;
    }
    counters[6] ++;
    r3.i = r8.i + ((uint32_t)r0.i << 2);
    r2.i = r9.i;
L5:
    counters[7] ++;
    load_counter ++;
    ldr(&ip.i, &r3.i, 4, 4, false, true, false);
    load_counter ++;
    ldr(&r1.i, &r2.i, 4, 4, true, false, false);
    tmp = r1.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) ip.i);
    v = (r1.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    store_counter ++;
    if (!z && n == v)
    {
        str(&ip.i, &r2.i, 0, 4, false, true, false);
    }
    store_counter ++;
    if (!z && n == v)
    {
        str(&r1.i, &r3.i, -4, 4, false, false, false);
    }
    tmp = r4.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r3.i);
    v = (r4.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        goto L5;
    }
    counters[8] ++;
    tmp = r0.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 1);
    v = (r0.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z && n == v)
    {
        goto L6;
    }
    counters[9] ++;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false, false);
    ldr(&r7.i, &sp.i, 3*4, 4, false, false, false);
    ldr(&r8.i, &sp.i, 4*4, 4, false, false, false);
    ldr(&r9.i, &sp.i, 5*4, 4, false, false, false);
    ldr(&r10.i, &sp.i, 6*4, 4, false, false, false);
    ldr(&pc.i, &sp.i, 7*4, 4, false, false, false);
    sp.i += 32;
    return;

}

void display()
{
    counters[10] ++;
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
        goto L14;
    }
    counters[11] ++;
    r6.i = (LC0 & 0xffff);
    r5.i = r0.i + ((uint32_t)r5.i << 2);
    r6.i = r6.i | (((uint32_t)LC0 >> 16) << 16);
    r4.i = r0.i;
L15:
    counters[12] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 4, 4, false, true, false);
    r1.i = r6.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[13] ++;
    tmp = r5.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r4.i);
    v = (r5.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (!z)
    {
        goto L15;
    }
L14:
    counters[14] ++;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false, false);
    ldr(&lr.i, &sp.i, 3*4, 4, false, false, false);
    sp.i += 16;
    r0.i = 10;
    printf("%c", (char)r0.i);
    return;

}

void main()
{
    malloc_start();
    counters[15] ++;
    store_counter ++;
    sp.i -= 16;
    str(&r4.i, &sp.i, 0*4, 4, false, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false, false);
    str(&lr.i, &sp.i, 3*4, 4, false, false, false);
    r0.i = 24;
    malloc_help();
    counters[16] ++;
    r6.i = 1;
    r2.i = 6;
    r1.i = (LC1 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC1 >> 16) << 16);
    r5.i = 6;
    r4.i = r0.i;
    r0.i = r6.i;
    printf(malloc_0+r1.i, r2.i);
    counters[17] ++;
    r2.i = 3;
    r0.i = r6.i;
    r3.i = 5;
    store_counter ++;
    str(&r5.i, &r4.i, 0, 4, false, true, false);
    r1.i = (LC2 & 0xffff);
    store_counter ++;
    str(&r3.i, &r4.i, 4, 4, false, false, false);
    r1.i = r1.i | (((uint32_t)LC2 >> 16) << 16);
    r3.i = 4;
    store_counter ++;
    str(&r6.i, &r4.i, 20, 4, false, false, false);
    store_counter ++;
    str(&r3.i, &r4.i, 8, 4, false, false, false);
    r3.i = 2;
    store_counter ++;
    str(&r2.i, &r4.i, 12, 4, false, false, false);
    str(&r3.i, &r4.i, 16, 4, false, false, false);
    printf(malloc_0+r1.i, r2.i);
    counters[18] ++;
    r1.i = r5.i;
    r0.i = r4.i;
    display();
    counters[19] ++;
    r1.i = r5.i;
    r0.i = r4.i;
    sort();
    counters[20] ++;
    r0.i = r6.i;
    r1.i = (LC3 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC3 >> 16) << 16);
    printf(malloc_0+r1.i, r2.i);
    counters[21] ++;
    r1.i = r5.i;
    r0.i = r4.i;
    display();
    counters[22] ++;
    r0.i = r4.i;
    free_help();
    counters[23] ++;
    r0.i = 0;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false, false);
    ldr(&pc.i, &sp.i, 3*4, 4, false, false, false);
    sp.i += 16;
    counter_summary();
    return;

}

