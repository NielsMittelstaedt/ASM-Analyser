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

reg r2, r8, r1, r0, r3, r9, r10, r5, r4, r6, r7;

int32_t LC0, LC1, LC2;

int counters[31] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[31] = {5,6,4,3,1,5,5,2,4,4,4,3,1,6,4,2,4,3,4,4,2,3,7,1,8,3,3,4,3,3,3};


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

    int32_t malloc_total = (int32_t) ((uint8_t*) malloc(42) - malloc_0);
    LC0 = malloc_total;
    strcpy(malloc_0+LC0, "%d \000");

    LC1 = malloc_total + 9;
    strcpy(malloc_0+LC1, "Array: \000");

    LC2 = malloc_total + 22;
    strcpy(malloc_0+LC2, "Sorted Array: \000");

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "partition_sort.c";

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
void partition();
void partitionSort();
void printArray();
void main();

void smull(int32_t *dest_lo, int32_t *dest_hi, int32_t *op1, int32_t *op2)
{
    uint64_t res = (uint64_t) (*op1) * (*op2);
    *dest_lo = (uint32_t) res;
    *dest_hi = (uint32_t) (res >> 32);
}
void rand_help()
{
    r0.i = rand();
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

void partition()
{
    counters[1] ++;
    load_counter ++;
    ldr(&ip.i, &r0.i, ((uint32_t)r1.i << 2), 4, false, false, false);
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r7.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r6.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r4.i, &sp.i, 0, 4, false, false, false);
    r5.i = r1.i - (1);
    lr.i = r2.i + (1);
    r4.i = r0.i + (((uint32_t)r1.i << 2));
    r7.i = r0.i;
L4:
    counters[2] ++;
    load_counter ++;
    ldr(&r6.i, &r4.i, 4, 4, false, true, false);
    r5.i = r5.i + (1);
    tmp = r6.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) ip.i);
    v = (r6.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    if (n != v)
    {
        goto L4;
    }
    counters[3] ++;
    r0.i = lr.i - (1);
    r3.i = r7.i + (((uint32_t)r0.i << 2));
    goto L6;
L12:
    counters[4] ++;
    r0.i = r0.i - (1);
L6:
    counters[5] ++;
    r1.i = r3.i;
    load_counter ++;
    ldr(&r2.i, &r3.i, -4, 4, false, true, false);
    lr.i = r0.i;
    tmp = r2.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) ip.i);
    v = (r2.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z && n == v)
    {
        goto L12;
    }
    counters[6] ++;
    tmp = r5.i - r0.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r0.i);
    v = (r5.i&0x80000000) != (r0.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    load_counter ++;
    if (n == v)
    {
        ldr(&r4.i, &sp.i, 0, 4, false, false, false);
        sp.i += 4;
        ldr(&r5.i, &sp.i, 0, 4, false, false, false);
        sp.i += 4;
        ldr(&r6.i, &sp.i, 0, 4, false, false, false);
        sp.i += 4;
        ldr(&r7.i, &sp.i, 0, 4, false, false, false);
        sp.i += 4;
        ldr(&pc.i, &sp.i, 0, 4, false, false, false);
        sp.i += 4;
        return;
    }
    store_counter ++;
    str(&r2.i, &r4.i, -4, 4, false, false, false);
    store_counter ++;
    str(&r6.i, &r1.i, 0, 4, false, true, false);
    goto L4;
    return;
}

void partitionSort()
{
    counters[7] ++;
    tmp = r1.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r2.i);
    v = (r1.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (n == v)
    {
        return;
    }
    counters[8] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&fp.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r10.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r9.i, &sp.i, 0, 4, false, false, false);
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
    sp.i -= 4;
    str(&r3.i, &sp.i, 0, 4, false, false, false);
    r6.i = r2.i + (1);
    r5.i = r2.i;
    r4.i = r0.i;
L19:
    counters[9] ++;
    load_counter ++;
    ldr(&r10.i, &r4.i, ((uint32_t)r1.i << 2), 4, false, false, false);
    lr.i = r1.i - (1);
    ip.i = r4.i + (((uint32_t)r1.i << 2));
    r0.i = r6.i;
L15:
    counters[10] ++;
    load_counter ++;
    ldr(&r8.i, &ip.i, 4, 4, false, true, false);
    lr.i = lr.i + (1);
    tmp = r10.i - r8.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r10.i) >= ((uint32_t) r8.i);
    v = (r10.i&0x80000000) != (r8.i&0x80000000) && (tmp&0x80000000) != (r10.i&0x80000000);
    if (!z && n == v)
    {
        goto L15;
    }
    counters[11] ++;
    r2.i = r0.i - (1);
    r3.i = r4.i + (((uint32_t)r2.i << 2));
    goto L17;
L28:
    counters[12] ++;
    r2.i = r2.i - (1);
L17:
    counters[13] ++;
    fp.i = r3.i;
    load_counter ++;
    ldr(&r9.i, &r3.i, -4, 4, false, true, false);
    r7.i = r0.i;
    r0.i = r2.i;
    tmp = r10.i - r9.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r10.i) >= ((uint32_t) r9.i);
    v = (r10.i&0x80000000) != (r9.i&0x80000000) && (tmp&0x80000000) != (r10.i&0x80000000);
    if (n != v)
    {
        goto L28;
    }
    counters[14] ++;
    tmp = lr.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) r2.i);
    v = (lr.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    store_counter ++;
    if (n != v)
    {
        str(&r9.i, &ip.i, -4, 4, false, false, false);
    }
    store_counter ++;
    if (n != v)
    {
        str(&r8.i, &fp.i, 0, 4, false, true, false);
    }
    if (n != v)
    {
        goto L15;
    }
L29:
    counters[15] ++;
    r0.i = r4.i;
    partitionSort();
    counters[16] ++;
    tmp = r5.i - r7.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r7.i);
    v = (r5.i&0x80000000) != (r7.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    load_counter ++;
    if (z || n != v)
    {
        ldr(&r3.i, &sp.i, 0, 4, false, false, false);
        sp.i += 4;
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
        ldr(&r9.i, &sp.i, 0, 4, false, false, false);
        sp.i += 4;
        ldr(&r10.i, &sp.i, 0, 4, false, false, false);
        sp.i += 4;
        ldr(&fp.i, &sp.i, 0, 4, false, false, false);
        sp.i += 4;
        ldr(&pc.i, &sp.i, 0, 4, false, false, false);
        sp.i += 4;
        return;
    }
    r1.i = r7.i;
    goto L19;
    return;
}

void printArray()
{
    counters[17] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r6.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r4.i, &sp.i, 0, 4, false, false, false);
    r5.i = r1.i - (0);
    z = r5.i == 0;
    n = r5.i & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 0);
    v = (r1.i&0x80000000) != (0&0x80000000) && (r5.i&0x80000000) != (r1.i&0x80000000);
    if (z || n != v)
    {
        goto L31;
    }
    counters[18] ++;
    r6.i = (LC0 & 0xffff);
    r5.i = r0.i + (((uint32_t)r5.i << 2));
    r6.i = r6.i | (((uint32_t)LC0 >> 16) << 16);
    r4.i = r0.i;
L32:
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
        goto L32;
    }
L31:
    counters[21] ++;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&r6.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    r0.i = 10;
    printf("%c", (char)r0.i);
    return;

}

void main()
{
    malloc_start();
    counters[22] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r7.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r6.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r4.i, &sp.i, 0, 4, false, false, false);
    sp.i = sp.i - (84);
    r4.i = 34079;
    r7.i = sp.i - (4);
    r4.i = r4.i | (20971 << 16);
    r6.i = sp.i + (76);
    r5.i = 100;
L36:
    counters[23] ++;
    rand_help();
    counters[24] ++;
    smull(&r3.i, &r2.i, &r4.i, &r0.i);
    r3.i = r0.i >> 31;
    r3.i = (r2.i >> 5) - r3.i;
    r0.i = r0.i - ((r5.i) * (r3.i));
    z = r0.i == 0;
    n = r0.i & 0x80000000;
    r0.i = r0.i + (1);
    store_counter ++;
    str(&r0.i, &r7.i, 4, 4, true, false, false);
    tmp = r7.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r7.i) >= ((uint32_t) r6.i);
    v = (r7.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
    if (!z)
    {
        goto L36;
    }
    counters[25] ++;
    r0.i = (LC1 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC1 >> 16) << 16);
    printf("%s\n", malloc_0+r0.i);
    counters[26] ++;
    r0.i = sp.i;
    r1.i = 20;
    printArray();
    counters[27] ++;
    r2.i = 19;
    r0.i = sp.i;
    r1.i = 0;
    partitionSort();
    counters[28] ++;
    r0.i = (LC2 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC2 >> 16) << 16);
    printf("%s\n", malloc_0+r0.i);
    counters[29] ++;
    r0.i = sp.i;
    r1.i = 20;
    printArray();
    counters[30] ++;
    r0.i = 0;
    sp.i = sp.i + (84);
    load_counter ++;
    ldr(&r4.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&r6.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&r7.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    counter_summary();
    return;

}

