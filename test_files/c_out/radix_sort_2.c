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

reg r10, r0, r7, r4, r5, r3, r2, r9, r1, r8, r6;

int32_t LC1, LC2, LC0;

int counters[34] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[34] = {4,1,5,1,11,2,3,5,3,11,30,4,4,13,3,4,4,3,4,4,2,3,11,3,4,2,2,4,6,1,13,4,3,3};


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
    strcpy(malloc_0+LC1, "%d \000");

    LC2 = malloc_total + 9;
    strcpy(malloc_0+LC2, "Sorted array: \000");

    LC0 = malloc_total + 29;
    int32_t arrayLC0[] = {6,5,4,3,2,1};
    for(int i=0; i<6; i++) str(&arrayLC0[i], &LC0, i*4, 4, false, false, false);

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "radix_sort_2.c";

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

void MAX();
void countSort();
void display();
void radixsort2();
void main();

void memset_help()
{
    memset(malloc_0+r0.i, r1.i, r2.i);
}
void smull(int32_t *dest_lo, int32_t *dest_hi, int32_t *op1, int32_t *op2)
{
    uint64_t res = (uint64_t) (*op1) * (*op2);
    *dest_lo = (uint32_t) res;
    *dest_hi = (uint32_t) (res >> 32);
}
void memcpy_help()
{
    memcpy(malloc_0+r0.i, malloc_0+r1.i, r2.i);
}
void free_help()
{
    free(malloc_0+r0.i);
}
void malloc_help()
{
    uint8_t* ptr = (uint8_t*) malloc(r0.i);
    r0.i = (int32_t) (ptr - malloc_0);
}
void idiv()
{
    r0.i = r0.i / r1.i;
}

void MAX()
{
    counters[0] ++;
    tmp = r1.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 0);
    v = (r1.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    r3.i = r0.i;
    load_counter ++;
    ldr(&r0.i, &r0.i, 0, 4, false, true, false);
    if (z || n != v)
    {
        return;
    }
    counters[1] ++;
    r1.i = r3.i + (((uint32_t)r1.i << 2));
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

void countSort()
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
    sp.i = sp.i - (52);
    r10.i = (uint32_t)r1.i << 2;
    r6.i = r1.i;
    store_counter ++;
    str(&r1.i, &sp.i, 4, 4, false, false, false);
    r5.i = r0.i;
    r1.i = 0;
    r0.i = sp.i + (8);
    r4.i = r2.i;
    r2.i = 40;
    memset_help();
    counters[5] ++;
    r0.i = r10.i;
    malloc_help();
    counters[6] ++;
    tmp = r6.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) 0);
    v = (r6.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    r6.i = r0.i;
    if (z || n != v)
    {
        goto L7;
    }
    counters[7] ++;
    r7.i = 26215;
    fp.i = r10.i + (r5.i);
    r7.i = r7.i | (26214 << 16);
    r9.i = r5.i;
    r8.i = 10;
L8:
    counters[8] ++;
    load_counter ++;
    ldr(&r0.i, &r9.i, 4, 4, false, true, false);
    r1.i = r4.i;
    idiv();
    counters[9] ++;
    r2.i = sp.i + (48);
    tmp = fp.i - r9.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) fp.i) >= ((uint32_t) r9.i);
    v = (fp.i&0x80000000) != (r9.i&0x80000000) && (tmp&0x80000000) != (fp.i&0x80000000);
    smull(&r3.i, &r1.i, &r7.i, &r0.i);
    r3.i = r0.i >> 31;
    r3.i = (r1.i >> 2) - r3.i;
    r3.i = r0.i - ((r8.i) * (r3.i));
    z = r3.i == 0;
    n = r3.i & 0x80000000;
    r3.i = r2.i + (((uint32_t)r3.i << 2));
    load_counter ++;
    ldr(&r1.i, &r3.i, -40, 4, false, false, false);
    r1.i = r1.i + (1);
    store_counter ++;
    str(&r1.i, &r3.i, -40, 4, false, false, false);
    if (!z)
    {
        goto L8;
    }
L7:
    counters[10] ++;
    load_counter ++;
    ldr(&r3.i, &sp.i, 4, 4, false, false, false);
    load_counter ++;
    ldr(&r0.i, &sp.i, 8, 4, false, false, false);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    load_counter ++;
    ldr(&r3.i, &sp.i, 12, 4, false, false, false);
    load_counter ++;
    ldr(&r1.i, &sp.i, 16, 4, false, false, false);
    r0.i = r0.i + (r3.i);
    load_counter ++;
    ldr(&r2.i, &sp.i, 20, 4, false, false, false);
    r1.i = r0.i + (r1.i);
    load_counter ++;
    ldr(&r3.i, &sp.i, 24, 4, false, false, false);
    r2.i = r1.i + (r2.i);
    store_counter ++;
    str(&r0.i, &sp.i, 12, 4, false, false, false);
    load_counter ++;
    ldr(&r0.i, &sp.i, 28, 4, false, false, false);
    r3.i = r2.i + (r3.i);
    store_counter ++;
    str(&r1.i, &sp.i, 16, 4, false, false, false);
    load_counter ++;
    ldr(&r1.i, &sp.i, 32, 4, false, false, false);
    r0.i = r3.i + (r0.i);
    store_counter ++;
    str(&r2.i, &sp.i, 20, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &sp.i, 36, 4, false, false, false);
    r1.i = r0.i + (r1.i);
    store_counter ++;
    str(&r3.i, &sp.i, 24, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &sp.i, 40, 4, false, false, false);
    r2.i = r1.i + (r2.i);
    store_counter ++;
    str(&r1.i, &sp.i, 32, 4, false, false, false);
    load_counter ++;
    ldr(&r1.i, &sp.i, 44, 4, false, false, false);
    r3.i = r2.i + (r3.i);
    store_counter ++;
    str(&r0.i, &sp.i, 28, 4, false, false, false);
    store_counter ++;
    str(&r2.i, &sp.i, 36, 4, false, false, false);
    str(&r3.i, &sp.i, 40, 4, false, false, false);
    r3.i = r1.i + (r3.i);
    store_counter ++;
    str(&r3.i, &sp.i, 44, 4, false, false, false);
    if (z || n != v)
    {
        goto L11;
    }
    counters[11] ++;
    r7.i = 26215;
    fp.i = r5.i + (r10.i);
    r7.i = r7.i | (26214 << 16);
    r8.i = 10;
L10:
    counters[12] ++;
    load_counter ++;
    ldr(&r9.i, &fp.i, -4, 4, true, false, false);
    r1.i = r4.i;
    r0.i = r9.i;
    idiv();
    counters[13] ++;
    r2.i = sp.i + (48);
    tmp = r5.i - fp.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) fp.i);
    v = (r5.i&0x80000000) != (fp.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    smull(&r3.i, &r1.i, &r7.i, &r0.i);
    r3.i = r0.i >> 31;
    r3.i = (r1.i >> 2) - r3.i;
    r3.i = r0.i - ((r8.i) * (r3.i));
    z = r3.i == 0;
    n = r3.i & 0x80000000;
    r3.i = r2.i + (((uint32_t)r3.i << 2));
    load_counter ++;
    ldr(&r1.i, &r3.i, -40, 4, false, false, false);
    r0.i = r1.i - (-1073741823);
    r1.i = r1.i - (1);
    store_counter ++;
    str(&r1.i, &r3.i, -40, 4, false, false, false);
    store_counter ++;
    str(&r9.i, &r6.i, ((uint32_t)r0.i << 2), 4, false, false, false);
    if (!z)
    {
        goto L10;
    }
    counters[14] ++;
    load_counter ++;
    ldr(&r3.i, &sp.i, 4, 4, false, false, false);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L11;
    }
    counters[15] ++;
    r2.i = r10.i;
    r0.i = r5.i;
    r1.i = r6.i;
    memcpy_help();
L11:
    counters[16] ++;
    r0.i = r6.i;
    sp.i = sp.i + (52);
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
    ldr(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    free_help();
    return;

}

void display()
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
        goto L16;
    }
    counters[18] ++;
    r6.i = (LC1 & 0xffff);
    r5.i = r0.i + (((uint32_t)r5.i << 2));
    r6.i = r6.i | (((uint32_t)LC1 >> 16) << 16);
    r4.i = r0.i;
L17:
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
        goto L17;
    }
L16:
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

void radixsort2()
{
    counters[22] ++;
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
    r4.i = r2.i - (0);
    z = r4.i == 0;
    n = r4.i & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) 0);
    v = (r2.i&0x80000000) != (0&0x80000000) && (r4.i&0x80000000) != (r2.i&0x80000000);
    load_counter ++;
    if (z)
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
    r8.i = (LC1 & 0xffff);
    r10.i = 26215;
    r8.i = r8.i | (((uint32_t)LC1 >> 16) << 16);
    r10.i = r10.i | (26214 << 16);
    r9.i = r0.i + (((uint32_t)r1.i << 2));
    r7.i = r0.i;
    r6.i = r1.i;
    r5.i = 1;
L22:
    counters[23] ++;
    tmp = r6.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) 0);
    v = (r6.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    if (!z && n == v)
    {
        fp.i = r7.i;
    }
    if (z || n != v)
    {
        goto L24;
    }
L23:
    counters[24] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, 4, 4, false, true, false);
    r1.i = r8.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[25] ++;
    tmp = r9.i - fp.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r9.i) >= ((uint32_t) fp.i);
    v = (r9.i&0x80000000) != (fp.i&0x80000000) && (tmp&0x80000000) != (r9.i&0x80000000);
    if (!z)
    {
        goto L23;
    }
L24:
    counters[26] ++;
    r0.i = 10;
    printf("%c", (char)r0.i);
    counters[27] ++;
    r2.i = r5.i;
    r1.i = r6.i;
    r0.i = r7.i;
    countSort();
    counters[28] ++;
    smull(&r2.i, &r3.i, &r10.i, &r4.i);
    r4.i = r4.i >> 31;
    r2.i = 10;
    r5.i = (r2.i) * (r5.i);
    r4.i = (r3.i >> 2) - r4.i;
    z = r4.i == 0;
    n = r4.i & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) (r3.i >> 2));
    v = (r4.i&0x80000000) != ((r3.i >> 2)&0x80000000) && (r4.i&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        goto L22;
    }
    counters[29] ++;
    load_counter ++;
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

void main()
{
    malloc_start();
    counters[30] ++;
    ip.i = (LC0 & 0xffff);
    ip.i = ip.i | (((uint32_t)LC0 >> 16) << 16);
    store_counter ++;
    str(&lr.i, &sp.i, -4, 4, true, false, false);
    sp.i = sp.i - (28);
    load_counter ++;
    ldr(&r0.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    ldr(&r1.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    ldr(&r2.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    ldr(&r3.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    lr.i = sp.i;
    store_counter ++;
    str(&r0.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    str(&r1.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    str(&r2.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    str(&r3.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    r2.i = 6;
    load_counter ++;
    tmp = ip.i;
    ldr(&r0.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    ldr(&r1.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    ip.i = tmp;
    store_counter ++;
    tmp = lr.i;
    str(&r0.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    str(&r1.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    lr.i = tmp;
    r1.i = r2.i;
    r0.i = sp.i;
    radixsort2();
    counters[31] ++;
    r1.i = (LC2 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC2 >> 16) << 16);
    printf(malloc_0+r1.i, r2.i);
    counters[32] ++;
    r0.i = sp.i;
    r1.i = 6;
    display();
    counters[33] ++;
    r0.i = 0;
    sp.i = sp.i + (28);
    load_counter ++;
    ldr(&pc.i, &sp.i, 4, 4, false, true, false);
    counter_summary();
    return;
}

