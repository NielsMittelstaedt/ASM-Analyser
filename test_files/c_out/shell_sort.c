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

reg r3, r6, r0, r4, r1, r2, r5, r8, r7;

int32_t LC0, LC1, LC2, LC3, notation;

int counters[32] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[32] = {3,4,4,2,3,5,7,2,5,3,4,4,4,2,1,5,2,7,1,8,3,1,4,1,4,3,4,2,4,4,6,4};


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

    int32_t malloc_total = (int32_t) ((uint8_t*) malloc(124) - malloc_0);
    LC0 = malloc_total;
    strcpy(malloc_0+LC0, "%3d \000");

    LC1 = malloc_total + 10;
    strcpy(malloc_0+LC1, "Data Sorted\000");

    LC2 = malloc_total + 27;
    strcpy(malloc_0+LC2, "Time spent sorting: %.4g ms\012\000");

    LC3 = malloc_total + 64;
    strcpy(malloc_0+LC3, "Shell Sort Big O Notation:\011\011\011\011\011\011\012");

    notation = malloc_total + 120;
    int32_t arraynotation[] = {.LC3};
    for(int i=0; i<1; i++) str(&arraynotation[i], &notation, i*4, 4, false, false, false);

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "shell_sort.c";

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

void show_data();
void swap();
void shellSort();
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
void srand_help()
{
    srand(r0.i);
}
void rand_help()
{
    r0.i = rand();
}
void i2d()
{
    double result = (double) r0.i;
    int64_t result_int64 = *(int64_t *)&result;
    r1.i = (int32_t) (result_int64 >> 32);
    r0.i = (int32_t) result_int64;
}
void time_help()
{
    r0.i = time(NULL);
}
void dmul()
{
    int64_t op1 = ((int64_t) r1.i) << 32 | ((int64_t) r0.i);
    int64_t op2 = ((int64_t) r3.i) << 32 | ((int64_t) r2.i);
    double result = *(double *)&op1 * *(double *)&op2;
    int64_t result_int64 = *(int64_t *)&result;
    r1.i = (int32_t) (result_int64 >> 32);
    r0.i = (int32_t) result_int64;
}
void smull(int32_t *dest_lo, int32_t *dest_hi, int32_t *op1, int32_t *op2)
{
    uint64_t res = (uint64_t) (*op1) * (*op2);
    *dest_lo = (uint32_t) res;
    *dest_hi = (uint32_t) (res >> 32);
}

void show_data()
{
    counters[0] ++;
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
        goto L2;
    }
    counters[1] ++;
    r6.i = (LC0 & 0xffff);
    r5.i = r0.i + ((uint32_t)r5.i << 2);
    r6.i = r6.i | (((uint32_t)LC0 >> 16) << 16);
    r4.i = r0.i;
L3:
    counters[2] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 4, 4, false, true, false);
    r1.i = r6.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[3] ++;
    tmp = r5.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r4.i);
    v = (r5.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (!z)
    {
        goto L3;
    }
L2:
    counters[4] ++;
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

void swap()
{
    counters[5] ++;
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

void shellSort()
{
    counters[6] ++;
    tmp = r1.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 1);
    v = (r1.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    store_counter ++;
    sp.i -= 24;
    str(&r4.i, &sp.i, 0*4, 4, false, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false, false);
    str(&r7.i, &sp.i, 3*4, 4, false, false, false);
    str(&r8.i, &sp.i, 4*4, 4, false, false, false);
    str(&lr.i, &sp.i, 5*4, 4, false, false, false);
    lr.i = r1.i + ((uint32_t)r1.i >> 31);
    load_counter ++;
    if (z || n != v)
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
    lr.i = lr.i >> 1;
    r7.i = r1.i;
    r8.i = r0.i;
L9:
    counters[7] ++;
    tmp = r7.i - lr.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r7.i) >= ((uint32_t) lr.i);
    v = (r7.i&0x80000000) != (lr.i&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
    if (z || n != v)
    {
        goto L13;
    }
    counters[8] ++;
    ip.i = (uint32_t)lr.i << 2;
    r6.i = r7.i - lr.i;
    r5.i = r8.i + ip.i;
    ip.i = 0 - ip.i;
    r4.i = 0;
L12:
    counters[9] ++;
    r2.i = r4.i;
    r3.i = r5.i;
    goto L11;
L15:
    counters[10] ++;
    r2.i = r2.i - lr.i;
    z = r2.i == 0;
    n = r2.i & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) lr.i);
    v = (r2.i&0x80000000) != (lr.i&0x80000000) && (r2.i&0x80000000) != (r2.i&0x80000000);
    store_counter ++;
    str(&r1.i, &r3.i, ip.i, 4, false, false, false);
    store_counter ++;
    str(&r0.i, &r3.i, ip.i, 4, false, true, false);
    if (n)
    {
        goto L14;
    }
L11:
    counters[11] ++;
    load_counter ++;
    ldr(&r0.i, &r3.i, ip.i, 4, false, false, false);
    load_counter ++;
    ldr(&r1.i, &r3.i, 0, 4, false, true, false);
    tmp = r0.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) r1.i);
    v = (r0.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z && n == v)
    {
        goto L15;
    }
L14:
    counters[12] ++;
    r4.i = r4.i + 1;
    r5.i = r5.i + 4;
    tmp = r4.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r6.i);
    v = (r4.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        goto L12;
    }
L13:
    counters[13] ++;
    lr.i = lr.i >> 1;
    z = lr.i == 0;
    n = lr.i & 0x80000000;
    c = lr.i & (1 << 1 - 1);
    if (!z)
    {
        goto L9;
    }
    counters[14] ++;
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
    counters[15] ++;
    store_counter ++;
    sp.i -= 24;
    str(&r4.i, &sp.i, 0*4, 4, false, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false, false);
    str(&r7.i, &sp.i, 3*4, 4, false, false, false);
    str(&r8.i, &sp.i, 4*4, 4, false, false, false);
    str(&lr.i, &sp.i, 5*4, 4, false, false, false);
    sp.i = sp.i - 79872;
    sp.i = sp.i - 128;
    r0.i = 0;
    time_help();
    counters[16] ++;
    r5.i = 19923;
    srand_help();
    counters[17] ++;
    r3.i = sp.i + 128;
    r4.i = r3.i + 78848;
    r5.i = r5.i | (4194 << 16);
    r7.i = r3.i - 128;
    r4.i = r4.i + 1020;
    r8.i = r3.i - 132;
    r6.i = 500;
L26:
    counters[18] ++;
    rand_help();
    counters[19] ++;
    smull(&r3.i, &r2.i, &r5.i, &r0.i);
    r3.i = r0.i >> 31;
    r3.i = (r2.i >> 5) - r3.i;
    r0.i = r0.i - (r6.i * r3.i);
    z = r0.i == 0;
    n = r0.i & 0x80000000;
    r0.i = r0.i + 1;
    store_counter ++;
    str(&r0.i, &r8.i, 4, 4, true, false, false);
    tmp = r8.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) r4.i);
    v = (r8.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    if (!z)
    {
        goto L26;
    }
    counters[20] ++;
    r1.i = 20000;
    r0.i = r7.i;
    show_data();
    counters[21] ++;
    clock();
    counters[22] ++;
    r1.i = 20000;
    r4.i = r0.i;
    r0.i = r7.i;
    shellSort();
    counters[23] ++;
    clock();
    counters[24] ++;
    r5.i = r0.i;
    r0.i = (LC1 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC1 >> 16) << 16);
    printf("%s\n", malloc_0+r0.i);
    counters[25] ++;
    r0.i = r7.i;
    r1.i = 20000;
    show_data();
    counters[26] ++;
    r3.i = (LC0 & 0xffff);
    r3.i = r3.i | (((uint32_t)LC0 >> 16) << 16);
    load_counter ++;
    ldr(&r0.i, &r3.i, 0, 4, false, true, false);
    printf("%s\n", malloc_0+r0.i);
    counters[27] ++;
    r0.i = r5.i - r4.i;
    i2d();
    counters[28] ++;
    r2.i = 0;
    r3.i = 33920;
    r3.i = r3.i | (16686 << 16);
    ddiv();
    counters[29] ++;
    r2.i = 0;
    r3.i = 16384;
    r3.i = r3.i | (16527 << 16);
    dmul();
    counters[30] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = 1;
    r1.i = (LC2 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC2 >> 16) << 16);
    printf(malloc_0+r1.i, r2.i);
    counters[31] ++;
    r0.i = 0;
    sp.i = sp.i + 79872;
    sp.i = sp.i + 128;
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

