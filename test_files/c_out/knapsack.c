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

reg r0, r5, r3, r1, r9, r6, r8, r2, r4, r7, r10;

int32_t LC2, LC3, LC0, LC1;

int counters[24] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[24] = {3,20,2,8,8,6,7,7,4,9,1,10,8,4,9,2,12,2,2,2,7,2,16,3};

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

void clz(int32_t *dest, int32_t *op)
{
    int msb = 1 << (32 - 1);
    int count = 0;
    uint32_t num = (uint32_t)*op;

    for(int i=0; i<32; i++)
    {
        if((num << i) & msb)
            break;
        count++;
    }

    *dest = num;
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
    malloc_0 = (uint8_t*) malloc(20045);
    sp.i = 19996;
    fp = sp;
    LC2 = 20000;
    strcpy(malloc_0+LC2, "%d\012\000");

    LC3 = 20012;
    strcpy(malloc_0+LC3, "%d \000");

    LC0 = 20021;
    int32_t arrayLC0[] = {60,100,120};
    for(int i=0; i<3; i++) str(&arrayLC0[i], &LC0, i*4, 4, false, false, false);

    LC1 = 20033;
    int32_t arrayLC1[] = {10,20,30};
    for(int i=0; i<3; i++) str(&arrayLC1[i], &LC1, i*4, 4, false, false, false);

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "knapsack.c";

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

void max();
void printknapSack();
void main();

void printf_help(const char *format, int32_t test)
{
    if (strstr(format, "%s") != NULL)
        printf(format, malloc_0 + test);
    else
        printf(format, test);
}

void max()
{
    counters[0] ++;
    tmp = r1.i - r0.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r0.i);
    v = (r1.i&0x80000000) != (r0.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (n == v)
    {
        r0.i = r1.i;
    }
    return;

}

void printknapSack()
{
    counters[1] ++;
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
    r4.i = r0.i + (1);
    r5.i = r3.i - (0);
    z = r5.i == 0;
    n = r5.i & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (r5.i&0x80000000) != (r3.i&0x80000000);
    fp.i = sp.i + (32);
    r3.i = ((r3.i) * (r4.i)) + (r4.i);
    sp.i = sp.i - (36);
    ip.i = (uint32_t)r4.i << 2;
    store_counter ++;
    str(&r0.i, &fp.i, -60, 4, false, false, false);
    store_counter ++;
    str(&ip.i, &fp.i, -56, 4, false, false, false);
    ip.i = r4.i & ~-1073741824;
    store_counter ++;
    str(&r1.i, &fp.i, -64, 4, false, false, false);
    store_counter ++;
    str(&r2.i, &fp.i, -68, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    store_counter ++;
    str(&ip.i, &fp.i, -48, 4, false, false, false);
    r3.i = r3.i + (7);
    r3.i = r3.i & ~7;
    sp.i = sp.i - (r3.i);
    r3.i = sp.i;
    store_counter ++;
    str(&r3.i, &fp.i, -40, 4, false, false, false);
    if (n != v)
    {
        goto L4;
    }
    counters[2] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (n != v)
    {
        goto L5;
    }
    counters[3] ++;
    store_counter ++;
    str(&r3.i, &fp.i, -44, 4, false, false, false);
    r9.i = r2.i - (4);
    r3.i = ~0;
    r6.i = r1.i - (4);
    r8.i = 0 - ip.i;
    store_counter ++;
    str(&r5.i, &fp.i, -52, 4, false, false, false);
    r7.i = 0;
    r5.i = r3.i;
L6:
    counters[4] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -48, 4, false, false, false);
    lr.i = r5.i;
    load_counter ++;
    ldr(&r2.i, &fp.i, -44, 4, false, false, false);
    r5.i = r5.i + (1);
    z = r5.i == 0;
    n = r5.i & 0x80000000;
    c = ((uint32_t) r5.i) < ((uint32_t) r5.i);
    v = (r5.i&0x80000000) == (1&0x80000000) && (r5.i&0x80000000) != (r5.i&0x80000000);
    lr.i = (lr.i) * (r3.i);
    if (z)
    {
        ip.i = 1;
    }
    if (!z)
    {
        ip.i = 0;
    }
    r3.i = 0;
L10:
    counters[5] ++;
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        r1.i = ip.i;
    }
    if (z)
    {
        r1.i = 1;
    }
    tmp = r1.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 0);
    v = (r1.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    store_counter ++;
    if (!z)
    {
        str(&r7.i, &r2.i, 0, 4, false, false, false);
    }
    if (!z)
    {
        goto L8;
    }
    counters[6] ++;
    load_counter ++;
    ldr(&r10.i, &r6.i, 0, 4, false, false, false);
    load_counter ++;
    ldr(&r0.i, &r2.i, ((uint32_t)r8.i << 2), 4, false, false, false);
    tmp = r10.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r10.i) >= ((uint32_t) r3.i);
    v = (r10.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r10.i&0x80000000);
    r1.i = r3.i - (r10.i);
    r1.i = lr.i + (r1.i);
    store_counter ++;
    if (!z && n == v)
    {
        str(&r0.i, &r2.i, 0, 4, false, false, false);
    }
    if (!z && n == v)
    {
        goto L8;
    }
    counters[7] ++;
    load_counter ++;
    ldr(&r10.i, &fp.i, -40, 4, false, false, false);
    load_counter ++;
    ldr(&r1.i, &r10.i, ((uint32_t)r1.i << 2), 4, false, false, false);
    load_counter ++;
    ldr(&r10.i, &r9.i, 0, 4, false, false, false);
    r1.i = r1.i + (r10.i);
    tmp = r1.i - r0.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r0.i);
    v = (r1.i&0x80000000) != (r0.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (n != v)
    {
        r1.i = r0.i;
    }
    store_counter ++;
    str(&r1.i, &r2.i, 0, 4, false, false, false);
L8:
    counters[8] ++;
    r3.i = r3.i + (1);
    r2.i = r2.i + (4);
    tmp = r3.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r4.i);
    v = (r3.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L10;
    }
    counters[9] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -52, 4, false, false, false);
    r9.i = r9.i + (4);
    load_counter ++;
    ldr(&r2.i, &fp.i, -56, 4, false, false, false);
    r6.i = r6.i + (4);
    tmp = r3.i - r5.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r5.i);
    v = (r3.i&0x80000000) != (r5.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    load_counter ++;
    ldr(&r3.i, &fp.i, -44, 4, false, false, false);
    r3.i = r3.i + (r2.i);
    store_counter ++;
    str(&r3.i, &fp.i, -44, 4, false, false, false);
    if (!z)
    {
        goto L6;
    }
    counters[10] ++;
    load_counter ++;
    ldr(&r5.i, &fp.i, -52, 4, false, false, false);
L5:
    counters[11] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -48, 4, false, false, false);
    r1.i = (LC2 & 0xffff);
    load_counter ++;
    ldr(&r7.i, &fp.i, -60, 4, false, false, false);
    r1.i = r1.i | (((uint32_t)LC2 >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &fp.i, -40, 4, false, false, false);
    r0.i = 1;
    r3.i = ((r3.i) * (r5.i)) + (r7.i);
    load_counter ++;
    ldr(&r4.i, &r2.i, ((uint32_t)r3.i << 2), 4, false, false, false);
    r2.i = r4.i;
    printf_help(malloc_0+r1.i, r2.i);
    counters[12] ++;
    tmp = r5.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) 0);
    v = (r5.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (!z && n == v)
    {
        r3.i = 1;
    }
    if (z || n != v)
    {
        r3.i = 0;
    }
    tmp = r4.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 0);
    v = (r4.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (z || n != v)
    {
        r3.i = 0;
    }
    if (!z && n == v)
    {
        r3.i = r3.i & 1;
    }
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L3;
    }
    counters[13] ++;
    load_counter ++;
    ldr(&r8.i, &fp.i, -64, 4, false, false, false);
    r6.i = (LC3 & 0xffff);
    load_counter ++;
    ldr(&r9.i, &fp.i, -68, 4, false, false, false);
    r6.i = r6.i | (((uint32_t)LC3 >> 16) << 16);
L11:
    counters[14] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -48, 4, false, false, false);
    r5.i = r5.i - (1);
    load_counter ++;
    ldr(&r2.i, &fp.i, -40, 4, false, false, false);
    r1.i = r6.i;
    r0.i = 1;
    r3.i = ((r3.i) * (r5.i)) + (r7.i);
    load_counter ++;
    ldr(&r3.i, &r2.i, ((uint32_t)r3.i << 2), 4, false, false, false);
    tmp = r3.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r4.i);
    v = (r3.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L13;
    }
    counters[15] ++;
    load_counter ++;
    ldr(&r2.i, &r8.i, ((uint32_t)r5.i << 2), 4, false, false, false);
    printf_help(malloc_0+r1.i, r2.i);
    counters[16] ++;
    load_counter ++;
    ldr(&r3.i, &r9.i, ((uint32_t)r5.i << 2), 4, false, false, false);
    tmp = r5.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) 0);
    v = (r5.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    load_counter ++;
    ldr(&r2.i, &r8.i, ((uint32_t)r5.i << 2), 4, false, false, false);
    r4.i = r4.i - (r3.i);
    if (!z && n == v)
    {
        r3.i = 1;
    }
    if (z || n != v)
    {
        r3.i = 0;
    }
    tmp = r4.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 0);
    v = (r4.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    r7.i = r7.i - (r2.i);
    if (!z && n == v)
    {
        r3.i = r3.i & 1;
    }
    if (z || n != v)
    {
        r3.i = 0;
    }
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L11;
    }
L3:
    counters[17] ++;
    sp.i = fp.i - (32);
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
L13:
    counters[18] ++;
    tmp = r5.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) 0);
    v = (r5.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (!z && n == v)
    {
        goto L11;
    }
    counters[19] ++;
    sp.i = fp.i - (32);
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
L4:
    counters[20] ++;
    r5.i = ((ip.i) * (r5.i)) + (r0.i);
    load_counter ++;
    ldr(&r3.i, &fp.i, -40, 4, false, false, false);
    r1.i = (LC2 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC2 >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &r3.i, ((uint32_t)r5.i << 2), 4, false, false, false);
    printf_help(malloc_0+r1.i, r2.i);
    counters[21] ++;
    sp.i = fp.i - (32);
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
    counters[22] ++;
    r3.i = (LC0 & 0xffff);
    r3.i = r3.i | (((uint32_t)LC0 >> 16) << 16);
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r4.i, &sp.i, 0, 4, false, false, false);
    sp.i = sp.i - (24);
    load_counter ++;
    tmp = r3.i;
    ldr(&r0.i, &r3.i, 0, 4, false, false, false);
    r3.i += 4;
    ldr(&r1.i, &r3.i, 0, 4, false, false, false);
    r3.i += 4;
    ldr(&r2.i, &r3.i, 0, 4, false, false, false);
    r3.i += 4;
    r3.i = tmp;
    r4.i = r3.i + (12);
    lr.i = sp.i;
    ip.i = sp.i + (12);
    r3.i = 3;
    store_counter ++;
    tmp = lr.i;
    str(&r0.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    str(&r1.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    str(&r2.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    lr.i = tmp;
    load_counter ++;
    tmp = r4.i;
    ldr(&r0.i, &r4.i, 0, 4, false, false, false);
    r4.i += 4;
    ldr(&r1.i, &r4.i, 0, 4, false, false, false);
    r4.i += 4;
    ldr(&r2.i, &r4.i, 0, 4, false, false, false);
    r4.i += 4;
    r4.i = tmp;
    store_counter ++;
    tmp = ip.i;
    str(&r0.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    str(&r1.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    str(&r2.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    ip.i = tmp;
    r2.i = lr.i;
    r1.i = ip.i;
    r0.i = 50;
    printknapSack();
    counters[23] ++;
    r0.i = 0;
    sp.i = sp.i + (24);
    load_counter ++;
    ldr(&r4.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;

}

