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

int32_t LC0, LC1;

int counters[11] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[11] = {8,16,5,1,15,4,3,4,2,2,3};


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

    int32_t malloc_total = (int32_t) ((uint8_t*) malloc(30) - malloc_0);
    LC0 = malloc_total;
    strcpy(malloc_0+LC0, "Sorted array : \000");

    LC1 = malloc_total + 21;
    strcpy(malloc_0+LC1, "%d \000");

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "stooge_sort.c";

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

void stoogesort();
void main();

void smull(int32_t *dest_lo, int32_t *dest_hi, int32_t *op1, int32_t *op2)
{
    uint64_t res = (uint64_t) (*op1) * (*op2);
    *dest_lo = (uint32_t) res;
    *dest_hi = (uint32_t) (res >> 32);
}

void stoogesort()
{
    counters[0] ++;
    store_counter ++;
    sp.i -= 40;
    str(&r3.i, &sp.i, 0*4, 4, false, false, false);
    str(&r4.i, &sp.i, 1*4, 4, false, false, false);
    str(&r5.i, &sp.i, 2*4, 4, false, false, false);
    str(&r6.i, &sp.i, 3*4, 4, false, false, false);
    str(&r7.i, &sp.i, 4*4, 4, false, false, false);
    str(&r8.i, &sp.i, 5*4, 4, false, false, false);
    str(&r9.i, &sp.i, 6*4, 4, false, false, false);
    str(&r10.i, &sp.i, 7*4, 4, false, false, false);
    str(&fp.i, &sp.i, 8*4, 4, false, false, false);
    str(&lr.i, &sp.i, 9*4, 4, false, false, false);
    r9.i = 21846;
    r7.i = r0.i + ((uint32_t)r1.i << 2);
    r8.i = r1.i + 1;
    r9.i = r9.i | (21845 << 16);
    r6.i = r1.i;
    r5.i = r0.i;
    r4.i = r2.i;
L4:
    counters[1] ++;
    r3.i = r4.i - r6.i;
    load_counter ++;
    ldr(&r2.i, &r7.i, 0, 4, false, true, false);
    r3.i = r3.i + 1;
    load_counter ++;
    ldr(&ip.i, &r5.i, ((uint32_t)r4.i << 2), 4, false, false, false);
    r1.i = r6.i;
    r0.i = r5.i;
    smull(&lr.i, &r10.i, &r9.i, &r3.i);
    tmp = r2.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) ip.i);
    v = (r2.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    store_counter ++;
    if (!z && n == v)
    {
        str(&ip.i, &r7.i, 0, 4, false, true, false);
    }
    r10.i = r10.i - (r3.i >> 31);
    store_counter ++;
    if (!z && n == v)
    {
        str(&r2.i, &r5.i, ((uint32_t)r4.i << 2), 4, false, false, false);
    }
    fp.i = r4.i - r10.i;
    tmp = r4.i - r8.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r8.i);
    v = (r4.i&0x80000000) != (r8.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    r2.i = fp.i;
    load_counter ++;
    if (z || n != v)
    {
        ldr(&r3.i, &sp.i, 0*4, 4, false, false, false);
        ldr(&r4.i, &sp.i, 1*4, 4, false, false, false);
        ldr(&r5.i, &sp.i, 2*4, 4, false, false, false);
        ldr(&r6.i, &sp.i, 3*4, 4, false, false, false);
        ldr(&r7.i, &sp.i, 4*4, 4, false, false, false);
        ldr(&r8.i, &sp.i, 5*4, 4, false, false, false);
        ldr(&r9.i, &sp.i, 6*4, 4, false, false, false);
        ldr(&r10.i, &sp.i, 7*4, 4, false, false, false);
        ldr(&fp.i, &sp.i, 8*4, 4, false, false, false);
        ldr(&pc.i, &sp.i, 9*4, 4, false, false, false);
        sp.i += 40;
        return;
    }
    stoogesort();
    counters[2] ++;
    r2.i = r4.i;
    r1.i = r6.i + r10.i;
    r0.i = r5.i;
    r4.i = fp.i;
    stoogesort();
    counters[3] ++;
    goto L4;
    return;
}

void main()
{
    malloc_start();
    counters[4] ++;
    store_counter ++;
    sp.i -= 16;
    str(&r4.i, &sp.i, 0*4, 4, false, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false, false);
    str(&lr.i, &sp.i, 3*4, 4, false, false, false);
    sp.i = sp.i - 400;
    r2.i = 5;
    r1.i = 0;
    r0.i = sp.i;
    r4.i = 6;
    r5.i = 5;
    store_counter ++;
    str(&r4.i, &sp.i, 0, 4, false, true, false);
    str(&r5.i, &sp.i, 4, 4, false, true, false);
    r4.i = 4;
    r5.i = 3;
    store_counter ++;
    str(&r4.i, &sp.i, 8, 4, false, false, false);
    str(&r5.i, &sp.i, 12, 4, false, false, false);
    r4.i = 2;
    r5.i = 1;
    store_counter ++;
    str(&r4.i, &sp.i, 16, 4, false, false, false);
    str(&r5.i, &sp.i, 20, 4, false, false, false);
    stoogesort();
    counters[5] ++;
    r0.i = (LC0 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC0 >> 16) << 16);
    r5.i = (LC1 & 0xffff);
    printf("%s\n", malloc_0+r0.i);
    counters[6] ++;
    r5.i = r5.i | (((uint32_t)LC1 >> 16) << 16);
    r6.i = sp.i + 24;
    r4.i = sp.i;
L9:
    counters[7] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 4, 4, false, true, false);
    r1.i = r5.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[8] ++;
    tmp = r6.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) r4.i);
    v = (r6.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    if (!z)
    {
        goto L9;
    }
    counters[9] ++;
    r0.i = 10;
    printf("%c", (char)r0.i);
    counters[10] ++;
    r0.i = 0;
    sp.i = sp.i + 400;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false, false);
    ldr(&pc.i, &sp.i, 3*4, 4, false, false, false);
    sp.i += 16;
    counter_summary();
    return;

}

