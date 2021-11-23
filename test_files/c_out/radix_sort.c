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

reg r1, r2, r3, r0;

int32_t LC0, LC1, LC2;

int counters[44] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[44] = {11,8,6,3,4,5,12,5,1,11,3,3,3,9,3,3,8,44,4,5,3,20,8,3,3,7,9,3,4,2,3,4,4,8,11,4,4,3,3,9,3,4,2,4};


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

    int32_t malloc_total = (int32_t) ((uint8_t*) malloc(72) - malloc_0);
    LC0 = malloc_total;
    strcpy(malloc_0+LC0, "The large element %d\012\000");

    LC1 = malloc_total + 30;
    strcpy(malloc_0+LC1, "%d \000");

    LC2 = malloc_total + 39;
    strcpy(malloc_0+LC2, "The sorted elements are :: \000");

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "radix_sort.c";

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

void largest();
void RadixSort();
void main();

void smull(int32_t *dest_lo, int32_t *dest_hi, int32_t *op1, int32_t *op2)
{
    uint64_t res = (uint64_t) (*op1) * (*op2);
    *dest_lo = (uint32_t) res;
    *dest_hi = (uint32_t) (res >> 32);
}

void largest()
{
    counters[0] ++;
    store_counter ++;
    str(&fp.i, &sp.i, -4, 4, true, false, false);
    fp.i = sp.i + 0;
    sp.i = sp.i - 20;
    store_counter ++;
    str(&r0.i, &fp.i, -16, 4, false, false, false);
    store_counter ++;
    str(&r1.i, &fp.i, -20, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, true, false);
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = 1;
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false, false);
    goto L2;
L4:
    counters[1] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -16, 4, false, false, false);
    r3.i = r2.i + r3.i;
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, true, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -8, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n == v)
    {
        goto L3;
    }
    counters[2] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -16, 4, false, false, false);
    r3.i = r2.i + r3.i;
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, true, false);
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
L3:
    counters[3] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false, false);
    r3.i = r3.i + 1;
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false, false);
L2:
    counters[4] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -12, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n != v)
    {
        goto L4;
    }
    counters[5] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r0.i = r3.i;
    sp.i = fp.i + 0;
    load_counter ++;
    ldr(&fp.i, &sp.i, 4, 4, false, true, false);
    return;

}

void RadixSort()
{
    counters[6] ++;
    store_counter ++;
    sp.i -= 8;
    str(&fp.i, &sp.i, 0*4, 4, false, false, false);
    str(&lr.i, &sp.i, 1*4, 4, false, false, false);
    fp.i = sp.i + 4;
    sp.i = sp.i - 480;
    store_counter ++;
    str(&r0.i, &fp.i, -480, 4, false, false, false);
    store_counter ++;
    str(&r1.i, &fp.i, -484, 4, false, false, false);
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -20, 4, false, false, false);
    r3.i = 1;
    store_counter ++;
    str(&r3.i, &fp.i, -24, 4, false, false, false);
    load_counter ++;
    ldr(&r1.i, &fp.i, -484, 4, false, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, -480, 4, false, false, false);
    largest();
    counters[7] ++;
    store_counter ++;
    str(&r0.i, &fp.i, -28, 4, false, false, false);
    load_counter ++;
    ldr(&r1.i, &fp.i, -28, 4, false, false, false);
    r0.i = (LC0 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC0 >> 16) << 16);
    printf(malloc_0+r0.i, r1.i);
    counters[8] ++;
    goto L7;
L8:
    counters[9] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false, false);
    r3.i = r3.i + 1;
    store_counter ++;
    str(&r3.i, &fp.i, -20, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -28, 4, false, false, false);
    r3.i = 26215;
    r3.i = r3.i | (26214 << 16);
    smull(&r1.i, &r3.i, &r3.i, &r2.i);
    r1.i = r3.i >> 2;
    r3.i = r2.i >> 31;
    r3.i = r1.i - r3.i;
    store_counter ++;
    str(&r3.i, &fp.i, -28, 4, false, false, false);
L7:
    counters[10] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -28, 4, false, false, false);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z && n == v)
    {
        goto L8;
    }
    counters[11] ++;
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -32, 4, false, false, false);
    goto L9;
L20:
    counters[12] ++;
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
    goto L10;
L11:
    counters[13] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    r2.i = fp.i - 4;
    r3.i = r2.i + r3.i;
    r2.i = 0;
    store_counter ++;
    str(&r2.i, &r3.i, -472, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = r3.i + 1;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
L10:
    counters[14] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    tmp = r3.i - 9;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 9);
    v = (r3.i&0x80000000) != (9&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L11;
    }
    counters[15] ++;
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
    goto L12;
L13:
    counters[16] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -480, 4, false, false, false);
    r3.i = r2.i + r3.i;
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, true, false);
    load_counter ++;
    ldr(&r1.i, &fp.i, -24, 4, false, false, false);
    r0.i = r3.i;
    __aeabi_idiv();
    counters[17] ++;
    r3.i = r0.i;
    r2.i = r3.i;
    r3.i = 26215;
    r3.i = r3.i | (26214 << 16);
    smull(&r1.i, &r3.i, &r3.i, &r2.i);
    r1.i = r3.i >> 2;
    r3.i = r2.i >> 31;
    r3.i = r1.i - r3.i;
    r1.i = 10;
    r3.i = r1.i * r3.i;
    r3.i = r2.i - r3.i;
    store_counter ++;
    str(&r3.i, &fp.i, -36, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -480, 4, false, false, false);
    r2.i = r2.i + r3.i;
    load_counter ++;
    ldr(&r3.i, &fp.i, -36, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    r1.i = fp.i - 4;
    r3.i = r1.i + r3.i;
    load_counter ++;
    ldr(&r3.i, &r3.i, -472, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &r2.i, 0, 4, false, true, false);
    load_counter ++;
    ldr(&r1.i, &fp.i, -36, 4, false, false, false);
    r0.i = 10;
    r1.i = r0.i * r1.i;
    r3.i = r1.i + r3.i;
    r3.i = (uint32_t)r3.i << 2;
    r1.i = fp.i - 4;
    r3.i = r1.i + r3.i;
    store_counter ++;
    str(&r2.i, &r3.i, -432, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -36, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    r2.i = fp.i - 4;
    r3.i = r2.i + r3.i;
    load_counter ++;
    ldr(&r3.i, &r3.i, -472, 4, false, false, false);
    r2.i = r3.i + 1;
    load_counter ++;
    ldr(&r3.i, &fp.i, -36, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    r1.i = fp.i - 4;
    r3.i = r1.i + r3.i;
    store_counter ++;
    str(&r2.i, &r3.i, -472, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = r3.i + 1;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
L12:
    counters[18] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -8, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -484, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n != v)
    {
        goto L13;
    }
    counters[19] ++;
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -16, 4, false, false, false);
    goto L14;
L17:
    counters[20] ++;
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false, false);
    goto L15;
L16:
    counters[21] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -480, 4, false, false, false);
    r2.i = r2.i + r3.i;
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false, false);
    r1.i = 10;
    r1.i = r1.i * r3.i;
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false, false);
    r3.i = r1.i + r3.i;
    r3.i = (uint32_t)r3.i << 2;
    r1.i = fp.i - 4;
    r3.i = r1.i + r3.i;
    load_counter ++;
    ldr(&r3.i, &r3.i, -432, 4, false, false, false);
    store_counter ++;
    str(&r3.i, &r2.i, 0, 4, false, true, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = r3.i + 1;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false, false);
    r3.i = r3.i + 1;
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false, false);
L15:
    counters[22] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    r2.i = fp.i - 4;
    r3.i = r2.i + r3.i;
    load_counter ++;
    ldr(&r3.i, &r3.i, -472, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -12, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n != v)
    {
        goto L16;
    }
    counters[23] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false, false);
    r3.i = r3.i + 1;
    store_counter ++;
    str(&r3.i, &fp.i, -16, 4, false, false, false);
L14:
    counters[24] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false, false);
    tmp = r3.i - 9;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 9);
    v = (r3.i&0x80000000) != (9&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L17;
    }
    counters[25] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -24, 4, false, false, false);
    r2.i = 10;
    r3.i = r2.i * r3.i;
    store_counter ++;
    str(&r3.i, &fp.i, -24, 4, false, false, false);
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
    goto L18;
L19:
    counters[26] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -480, 4, false, false, false);
    r3.i = r2.i + r3.i;
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, true, false);
    r1.i = r3.i;
    r0.i = (LC1 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC1 >> 16) << 16);
    printf(malloc_0+r0.i, r1.i);
    counters[27] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = r3.i + 1;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
L18:
    counters[28] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -8, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -484, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n != v)
    {
        goto L19;
    }
    counters[29] ++;
    r0.i = 10;
    printf("%c", (char)r0.i);
    counters[30] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -32, 4, false, false, false);
    r3.i = r3.i + 1;
    store_counter ++;
    str(&r3.i, &fp.i, -32, 4, false, false, false);
L9:
    counters[31] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -32, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n != v)
    {
        goto L20;
    }
    counters[32] ++;
    sp.i = fp.i - 4;
    load_counter ++;
    ldr(&fp.i, &sp.i, 0*4, 4, false, false, false);
    ldr(&pc.i, &sp.i, 1*4, 4, false, false, false);
    sp.i += 8;
    return;

}

void main()
{
    malloc_start();
    counters[33] ++;
    store_counter ++;
    sp.i -= 8;
    str(&fp.i, &sp.i, 0*4, 4, false, false, false);
    str(&lr.i, &sp.i, 1*4, 4, false, false, false);
    fp.i = sp.i + 4;
    sp.i = sp.i - 48;
    r3.i = 6;
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false, false);
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
    goto L22;
L23:
    counters[34] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -12, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r2.i = r2.i - r3.i;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    r1.i = fp.i - 4;
    r3.i = r1.i + r3.i;
    store_counter ++;
    str(&r2.i, &r3.i, -48, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = r3.i + 1;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
L22:
    counters[35] ++;
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
        goto L23;
    }
    counters[36] ++;
    r3.i = fp.i - 52;
    load_counter ++;
    ldr(&r1.i, &fp.i, -12, 4, false, false, false);
    r0.i = r3.i;
    RadixSort();
    counters[37] ++;
    r0.i = (LC2 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC2 >> 16) << 16);
    printf(malloc_0+r0.i, r1.i);
    counters[38] ++;
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
    goto L24;
L25:
    counters[39] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    r2.i = fp.i - 4;
    r3.i = r2.i + r3.i;
    load_counter ++;
    ldr(&r3.i, &r3.i, -48, 4, false, false, false);
    r1.i = r3.i;
    r0.i = (LC1 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC1 >> 16) << 16);
    printf(malloc_0+r0.i, r1.i);
    counters[40] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = r3.i + 1;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
L24:
    counters[41] ++;
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
        goto L25;
    }
    counters[42] ++;
    r0.i = 10;
    printf("%c", (char)r0.i);
    counters[43] ++;
    r3.i = 0;
    r0.i = r3.i;
    sp.i = fp.i - 4;
    load_counter ++;
    ldr(&fp.i, &sp.i, 0*4, 4, false, false, false);
    ldr(&pc.i, &sp.i, 1*4, 4, false, false, false);
    sp.i += 8;
    counter_summary();
    return;

}

