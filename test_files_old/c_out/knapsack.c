#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

typedef union
{
    int32_t i;
    float f;
} reg;

int32_t tmp;
reg sp, fp, lr, pc, ip;
bool z, n, c, v;
uint8_t* malloc_0 = 0;

reg r0, r8, r4, r2, r3, r5, r1, r6, r10, r9, r7;

int32_t LC2, LC3, LC0, LC1;

int counters[24] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[24] = {3,20,2,8,8,6,7,7,4,9,1,10,8,4,9,2,12,2,2,2,7,2,16,3};


void ldr(int32_t *target, int32_t *address, int32_t offset, int bytes, bool update, bool post_index)
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

void str(int32_t *target, int32_t *address, int32_t offset, int bytes, bool update, bool post_index)
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
        ldr(&cur_val, &start, i*4, 4, false, false);
        printf("%d: %d\n", start+i*4, cur_val);
    }
}

void malloc_start()
{
    malloc_0 = (uint8_t*) malloc(1);
    uint8_t* stack_ptr = (uint8_t*) malloc(1000);
    sp.i = (int32_t) (stack_ptr - malloc_0) + 996;
    fp = sp;

    int32_t malloc_total = (int32_t) ((uint8_t*) malloc(45) - malloc_0);
    LC2 = malloc_total;
    strcpy(malloc_0+LC2, "%d\012\000");

    LC3 = malloc_total + 12;
    strcpy(malloc_0+LC3, "%d \000");

    LC0 = malloc_total + 21;
    int32_t arrayLC0[] = {60,100,120};
    for(int i=0; i<3; i++) str(&arrayLC0[i], &LC0, i*4, 4, false, false);

    LC1 = malloc_total + 33;
    int32_t arrayLC1[] = {10,20,30};
    for(int i=0; i<3; i++) str(&arrayLC1[i], &LC1, i*4, 4, false, false);

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
    sp.i -= 36;
    str(&r4.i, &sp.i, 0*4, 4, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false);
    str(&r7.i, &sp.i, 3*4, 4, false, false);
    str(&r8.i, &sp.i, 4*4, 4, false, false);
    str(&r9.i, &sp.i, 5*4, 4, false, false);
    str(&r10.i, &sp.i, 6*4, 4, false, false);
    str(&fp.i, &sp.i, 7*4, 4, false, false);
    str(&lr.i, &sp.i, 8*4, 4, false, false);
    r4.i = r0.i + 1;
    r5.i = r3.i - 0;
    z = r5.i == 0;
    n = r5.i & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (r5.i&0x80000000) != (r3.i&0x80000000);
    fp.i = sp.i + 32;
    r3.i = (r3.i * r4.i) + r4.i;
    sp.i = sp.i - 36;
    ip.i = (uint32_t)r4.i << 2;
    store_counter ++;
    str(&r0.i, &fp.i, -60, 4, false, false);
    store_counter ++;
    str(&ip.i, &fp.i, -56, 4, false, false);
    ip.i = r4.i & ~-1073741824;
    store_counter ++;
    str(&r1.i, &fp.i, -64, 4, false, false);
    store_counter ++;
    str(&r2.i, &fp.i, -68, 4, false, false);
    r3.i = (uint32_t)r3.i << 2;
    store_counter ++;
    str(&ip.i, &fp.i, -48, 4, false, false);
    r3.i = r3.i + 7;
    r3.i = r3.i & ~7;
    sp.i = sp.i - r3.i;
    r3.i = sp.i;
    store_counter ++;
    str(&r3.i, &fp.i, -40, 4, false, false);
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
    str(&r3.i, &fp.i, -44, 4, false, false);
    r9.i = r2.i - 4;
    r3.i = ~0;
    r6.i = r1.i - 4;
    r8.i = 0 - ip.i;
    store_counter ++;
    str(&r5.i, &fp.i, -52, 4, false, false);
    r7.i = 0;
    r5.i = r3.i;
L6:
    counters[4] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -48, 4, false, false);
    lr.i = r5.i;
    load_counter ++;
    ldr(&r2.i, &fp.i, -44, 4, false, false);
    r5.i = r5.i + 1;
    z = r5.i == 0;
    n = r5.i & 0x80000000;
    c = ((uint32_t) r5.i) < ((uint32_t) r5.i);
    v = (r5.i&0x80000000) == (1&0x80000000) && (r5.i&0x80000000) != (r5.i&0x80000000);
    lr.i = lr.i * r3.i;
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
        str(&r7.i, &r2.i, 0, 4, false, true);
    }
    if (!z)
    {
        goto L8;
    }
    counters[6] ++;
    load_counter ++;
    ldr(&r10.i, &r6.i, 0, 4, false, true);
    load_counter ++;
    ldr(&r0.i, &r2.i, ((uint32_t)r8.i << 2), 4, false, false);
    tmp = r10.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r10.i) >= ((uint32_t) r3.i);
    v = (r10.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r10.i&0x80000000);
    r1.i = r3.i - r10.i;
    r1.i = lr.i + r1.i;
    store_counter ++;
    if (!z && n == v)
    {
        str(&r0.i, &r2.i, 0, 4, false, true);
    }
    if (!z && n == v)
    {
        goto L8;
    }
    counters[7] ++;
    load_counter ++;
    ldr(&r10.i, &fp.i, -40, 4, false, false);
    load_counter ++;
    ldr(&r1.i, &r10.i, ((uint32_t)r1.i << 2), 4, false, false);
    load_counter ++;
    ldr(&r10.i, &r9.i, 0, 4, false, true);
    r1.i = r1.i + r10.i;
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
    str(&r1.i, &r2.i, 0, 4, false, true);
L8:
    counters[8] ++;
    r3.i = r3.i + 1;
    r2.i = r2.i + 4;
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
    ldr(&r3.i, &fp.i, -52, 4, false, false);
    r9.i = r9.i + 4;
    load_counter ++;
    ldr(&r2.i, &fp.i, -56, 4, false, false);
    r6.i = r6.i + 4;
    tmp = r3.i - r5.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r5.i);
    v = (r3.i&0x80000000) != (r5.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    load_counter ++;
    ldr(&r3.i, &fp.i, -44, 4, false, false);
    r3.i = r3.i + r2.i;
    store_counter ++;
    str(&r3.i, &fp.i, -44, 4, false, false);
    if (!z)
    {
        goto L6;
    }
    counters[10] ++;
    load_counter ++;
    ldr(&r5.i, &fp.i, -52, 4, false, false);
L5:
    counters[11] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -48, 4, false, false);
    r1.i = (LC2 & 0xffff);
    load_counter ++;
    ldr(&r7.i, &fp.i, -60, 4, false, false);
    r1.i = r1.i | (((uint32_t)LC2 >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &fp.i, -40, 4, false, false);
    r0.i = 1;
    r3.i = (r3.i * r5.i) + r7.i;
    load_counter ++;
    ldr(&r4.i, &r2.i, ((uint32_t)r3.i << 2), 4, false, false);
    r2.i = r4.i;
    printf(malloc_0+r1.i, r2.i);
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
    ldr(&r8.i, &fp.i, -64, 4, false, false);
    r6.i = (LC3 & 0xffff);
    load_counter ++;
    ldr(&r9.i, &fp.i, -68, 4, false, false);
    r6.i = r6.i | (((uint32_t)LC3 >> 16) << 16);
L11:
    counters[14] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -48, 4, false, false);
    r5.i = r5.i - 1;
    load_counter ++;
    ldr(&r2.i, &fp.i, -40, 4, false, false);
    r1.i = r6.i;
    r0.i = 1;
    r3.i = (r3.i * r5.i) + r7.i;
    load_counter ++;
    ldr(&r3.i, &r2.i, ((uint32_t)r3.i << 2), 4, false, false);
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
    ldr(&r2.i, &r8.i, ((uint32_t)r5.i << 2), 4, false, false);
    printf(malloc_0+r1.i, r2.i);
    counters[16] ++;
    load_counter ++;
    ldr(&r3.i, &r9.i, ((uint32_t)r5.i << 2), 4, false, false);
    tmp = r5.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) 0);
    v = (r5.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    load_counter ++;
    ldr(&r2.i, &r8.i, ((uint32_t)r5.i << 2), 4, false, false);
    r4.i = r4.i - r3.i;
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
    r7.i = r7.i - r2.i;
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
    sp.i = fp.i - 32;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false);
    ldr(&r7.i, &sp.i, 3*4, 4, false, false);
    ldr(&r8.i, &sp.i, 4*4, 4, false, false);
    ldr(&r9.i, &sp.i, 5*4, 4, false, false);
    ldr(&r10.i, &sp.i, 6*4, 4, false, false);
    ldr(&fp.i, &sp.i, 7*4, 4, false, false);
    ldr(&pc.i, &sp.i, 8*4, 4, false, false);
    sp.i += 36;
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
    sp.i = fp.i - 32;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false);
    ldr(&r7.i, &sp.i, 3*4, 4, false, false);
    ldr(&r8.i, &sp.i, 4*4, 4, false, false);
    ldr(&r9.i, &sp.i, 5*4, 4, false, false);
    ldr(&r10.i, &sp.i, 6*4, 4, false, false);
    ldr(&fp.i, &sp.i, 7*4, 4, false, false);
    ldr(&pc.i, &sp.i, 8*4, 4, false, false);
    sp.i += 36;
    return;
L4:
    counters[20] ++;
    r5.i = (ip.i * r5.i) + r0.i;
    load_counter ++;
    ldr(&r3.i, &fp.i, -40, 4, false, false);
    r1.i = (LC2 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC2 >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &r3.i, ((uint32_t)r5.i << 2), 4, false, false);
    printf(malloc_0+r1.i, r2.i);
    counters[21] ++;
    sp.i = fp.i - 32;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false);
    ldr(&r7.i, &sp.i, 3*4, 4, false, false);
    ldr(&r8.i, &sp.i, 4*4, 4, false, false);
    ldr(&r9.i, &sp.i, 5*4, 4, false, false);
    ldr(&r10.i, &sp.i, 6*4, 4, false, false);
    ldr(&fp.i, &sp.i, 7*4, 4, false, false);
    ldr(&pc.i, &sp.i, 8*4, 4, false, false);
    sp.i += 36;
    return;

}

void main()
{
    malloc_start();
    counters[22] ++;
    r3.i = (LC0 & 0xffff);
    r3.i = r3.i | (((uint32_t)LC0 >> 16) << 16);
    store_counter ++;
    sp.i -= 8;
    str(&r4.i, &sp.i, 0*4, 4, false, false);
    str(&lr.i, &sp.i, 1*4, 4, false, false);
    sp.i = sp.i - 24;
    load_counter ++;
    ldr(&r0.i, &r3.i, 0*4, 4, false, false);
    ldr(&r1.i, &r3.i, 1*4, 4, false, false);
    ldr(&r2.i, &r3.i, 2*4, 4, false, false);
    r4.i = r3.i + 12;
    lr.i = sp.i;
    ip.i = sp.i + 12;
    r3.i = 3;
    store_counter ++;
    str(&r0.i, &lr.i, 0*4, 4, false, false);
    str(&r1.i, &lr.i, 1*4, 4, false, false);
    str(&r2.i, &lr.i, 2*4, 4, false, false);
    load_counter ++;
    ldr(&r0.i, &r4.i, 0*4, 4, false, false);
    ldr(&r1.i, &r4.i, 1*4, 4, false, false);
    ldr(&r2.i, &r4.i, 2*4, 4, false, false);
    store_counter ++;
    str(&r0.i, &ip.i, 0*4, 4, false, false);
    str(&r1.i, &ip.i, 1*4, 4, false, false);
    str(&r2.i, &ip.i, 2*4, 4, false, false);
    r2.i = lr.i;
    r1.i = ip.i;
    r0.i = 50;
    printknapSack();
    counters[23] ++;
    r0.i = 0;
    sp.i = sp.i + 24;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false);
    ldr(&pc.i, &sp.i, 1*4, 4, false, false);
    sp.i += 8;
    counter_summary();
    return;

}

