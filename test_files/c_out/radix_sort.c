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

int counters[34] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[34] = {4,2,5,1,7,2,5,5,2,3,5,10,12,4,15,3,6,1,1,4,4,3,4,2,6,3,2,14,5,3,4,2,2,3};


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
void idiv()
{
    r0.i = r0.i / r1.i;
}
void umull(int32_t *dest_lo, int32_t *dest_hi, int32_t *op1, int32_t *op2)
{
    uint64_t res = (uint64_t) ((uint32_t) *op1) * ((uint32_t) *op2);
    *dest_lo = (uint32_t) res;
    *dest_hi = (uint32_t) (res >> 32);
}
void memcpy_help()
{
    memcpy(malloc_0+r0.i, malloc_0+r1.i, r2.i);
}

void largest()
{
    counters[0] ++;
    tmp = r1.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 1);
    v = (r1.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    r3.i = r0.i;
    load_counter ++;
    ldr(&r0.i, &r0.i, 0, 4, false, true, false);
    if (z || n != v)
    {
        return;
    }
    counters[1] ++;
    r1.i = r3.i + (((uint32_t)r1.i << 2));
    r3.i = r3.i + (4);
L3:
    counters[2] ++;
    load_counter ++;
    ldr(&r2.i, &r3.i, 4, 4, false, true, false);
    tmp = r0.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) r2.i);
    v = (r0.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (n != v)
    {
        r0.i = r2.i;
    }
    tmp = r1.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r3.i);
    v = (r1.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!z)
    {
        goto L3;
    }
    counters[3] ++;
    return;

}

void RadixSort()
{
    counters[4] ++;
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
    tmp = r1.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 1);
    v = (r1.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    sp.i = sp.i - (460);
    load_counter ++;
    ldr(&r4.i, &r0.i, 0, 4, false, true, false);
    r9.i = r0.i;
    store_counter ++;
    str(&r1.i, &sp.i, 0, 4, false, true, false);
    if (z || n != v)
    {
        goto L7;
    }
    counters[5] ++;
    r3.i = r0.i + (4);
    r1.i = r0.i + (((uint32_t)r1.i << 2));
L8:
    counters[6] ++;
    load_counter ++;
    ldr(&r2.i, &r3.i, 4, 4, false, true, false);
    tmp = r4.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r2.i);
    v = (r4.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (n != v)
    {
        r4.i = r2.i;
    }
    tmp = r3.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r1.i);
    v = (r3.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L8;
    }
L7:
    counters[7] ++;
    r1.i = (LC0 & 0xffff);
    r2.i = r4.i;
    r1.i = r1.i | (((uint32_t)LC0 >> 16) << 16);
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[8] ++;
    tmp = r4.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 0);
    v = (r4.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (z || n != v)
    {
        goto L6;
    }
    counters[9] ++;
    r1.i = 52429;
    r1.i = r1.i | (52428 << 16);
    r3.i = 0;
L10:
    counters[10] ++;
    umull(&r0.i, &r2.i, &r1.i, &r4.i);
    tmp = r4.i - 9;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 9);
    v = (r4.i&0x80000000) != (9&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    r3.i = r3.i + (1);
    r4.i = (uint32_t)r2.i >> 3;
    if (!z && n == v)
    {
        goto L10;
    }
    counters[11] ++;
    load_counter ++;
    ldr(&r2.i, &sp.i, 0, 4, false, true, false);
    fp.i = 1;
    r7.i = 10;
    store_counter ++;
    str(&r3.i, &sp.i, 8, 4, false, false, false);
    r3.i = 26215;
    r3.i = r3.i | (26214 << 16);
    r8.i = r9.i + (((uint32_t)r2.i << 2));
    store_counter ++;
    str(&r3.i, &sp.i, 12, 4, false, false, false);
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &sp.i, 4, 4, false, false, false);
L11:
    counters[12] ++;
    load_counter ++;
    ldr(&r3.i, &sp.i, 0, 4, false, true, false);
    r2.i = 0;
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    r3.i = 0;
    store_counter ++;
    str(&r2.i, &sp.i, 16, 4, false, false, false);
    str(&r3.i, &sp.i, 20, 4, false, false, false);
    load_counter ++;
    if (!z && n == v)
    {
        ldr(&r5.i, &sp.i, 12, 4, false, false, false);
    }
    if (!z && n == v)
    {
        r4.i = r9.i;
    }
    store_counter ++;
    str(&r2.i, &sp.i, 24, 4, false, false, false);
    str(&r3.i, &sp.i, 28, 4, false, false, false);
    store_counter ++;
    str(&r2.i, &sp.i, 32, 4, false, false, false);
    str(&r3.i, &sp.i, 36, 4, false, false, false);
    store_counter ++;
    str(&r2.i, &sp.i, 40, 4, false, false, false);
    str(&r3.i, &sp.i, 44, 4, false, false, false);
    store_counter ++;
    str(&r2.i, &sp.i, 48, 4, false, false, false);
    str(&r3.i, &sp.i, 52, 4, false, false, false);
    if (z || n != v)
    {
        goto L19;
    }
L12:
    counters[13] ++;
    load_counter ++;
    ldr(&r6.i, &r4.i, 4, 4, false, true, false);
    r1.i = fp.i;
    r0.i = r6.i;
    idiv();
    counters[14] ++;
    tmp = r8.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) r4.i);
    v = (r8.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    smull(&r3.i, &r2.i, &r5.i, &r0.i);
    r3.i = r0.i >> 31;
    r3.i = (r2.i >> 2) - r3.i;
    r2.i = sp.i + (456);
    r3.i = r0.i - ((r7.i) * (r3.i));
    z = r3.i == 0;
    n = r3.i & 0x80000000;
    r1.i = r2.i + (((uint32_t)r3.i << 2));
    load_counter ++;
    ldr(&r2.i, &r1.i, -440, 4, false, false, false);
    r0.i = r2.i + (1);
    store_counter ++;
    str(&r0.i, &r1.i, -440, 4, false, false, false);
    r3.i = ((r7.i) * (r3.i)) + (r2.i);
    r2.i = sp.i + (456);
    r3.i = r2.i + (((uint32_t)r3.i << 2));
    store_counter ++;
    str(&r6.i, &r3.i, -400, 4, false, false, false);
    if (!z)
    {
        goto L12;
    }
L19:
    counters[15] ++;
    r10.i = sp.i + (16);
    r4.i = sp.i + (56);
    r6.i = 0;
L13:
    counters[16] ++;
    load_counter ++;
    ldr(&r5.i, &r10.i, 4, 4, false, true, false);
    r0.i = r9.i + (((uint32_t)r6.i << 2));
    r1.i = r4.i;
    tmp = r5.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) 0);
    v = (r5.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    r2.i = (uint32_t)r5.i << 2;
    if (z || n != v)
    {
        goto L16;
    }
    counters[17] ++;
    memcpy_help();
    counters[18] ++;
    r6.i = r6.i + (r5.i);
L16:
    counters[19] ++;
    r4.i = r4.i + (40);
    r3.i = sp.i + (456);
    tmp = r3.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r4.i);
    v = (r3.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L13;
    }
    counters[20] ++;
    load_counter ++;
    ldr(&r3.i, &sp.i, 0, 4, false, true, false);
    fp.i = (r7.i) * (fp.i);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L17;
    }
    counters[21] ++;
    r5.i = (LC1 & 0xffff);
    r5.i = r5.i | (((uint32_t)LC1 >> 16) << 16);
    r4.i = r9.i;
L18:
    counters[22] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 4, 4, false, true, false);
    r1.i = r5.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[23] ++;
    tmp = r8.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) r4.i);
    v = (r8.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    if (!z)
    {
        goto L18;
    }
L17:
    counters[24] ++;
    load_counter ++;
    ldr(&r3.i, &sp.i, 4, 4, false, false, false);
    r0.i = 10;
    r3.i = r3.i + (1);
    store_counter ++;
    str(&r3.i, &sp.i, 4, 4, false, false, false);
    r4.i = r3.i;
    printf("%c", (char)r0.i);
    counters[25] ++;
    load_counter ++;
    ldr(&r2.i, &sp.i, 8, 4, false, false, false);
    tmp = r2.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r4.i);
    v = (r2.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z)
    {
        goto L11;
    }
L6:
    counters[26] ++;
    sp.i = sp.i + (460);
    load_counter ++;
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

void main()
{
    malloc_start();
    counters[27] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r6.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r4.i, &sp.i, 0, 4, false, false, false);
    sp.i = sp.i - (40);
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
    RadixSort();
    counters[28] ++;
    r1.i = (LC2 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC2 >> 16) << 16);
    r5.i = (LC1 & 0xffff);
    printf(malloc_0+r1.i, r2.i);
    counters[29] ++;
    r5.i = r5.i | (((uint32_t)LC1 >> 16) << 16);
    r6.i = sp.i + (24);
    r4.i = sp.i;
L27:
    counters[30] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 4, 4, false, true, false);
    r1.i = r5.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[31] ++;
    tmp = r6.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) r4.i);
    v = (r6.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    if (!z)
    {
        goto L27;
    }
    counters[32] ++;
    r0.i = 10;
    printf("%c", (char)r0.i);
    counters[33] ++;
    r0.i = 0;
    sp.i = sp.i + (40);
    load_counter ++;
    ldr(&r4.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&r6.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    counter_summary();
    return;

}

