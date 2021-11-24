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

reg r2, r8, r1, r0, r3, r5, r4, r6, r7;

int32_t LC0, LC1, LC2;

int counters[22] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[22] = {5,3,1,5,5,7,8,10,3,3,21,1,4,2,3,4,2,4,2,2,2,2};


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

    int32_t malloc_total = (int32_t) ((uint8_t*) malloc(52) - malloc_0);
    LC0 = malloc_total;
    strcpy(malloc_0+LC0, "You entered: \000");

    LC1 = malloc_total + 19;
    strcpy(malloc_0+LC1, "%d \000");

    LC2 = malloc_total + 28;
    strcpy(malloc_0+LC2, "\012Sorted array: \000");

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "cocktail_sort.c";

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

void cocktailSort();
void main();

void malloc_help()
{
    uint8_t* ptr = (uint8_t*) malloc(r0.i);
    r0.i = (int32_t) (ptr - malloc_0);
}
void free_help()
{
    free(malloc_0+r0.i);
}

void cocktailSort()
{
    counters[0] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r6.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r4.i, &sp.i, 0, 4, false, false, false);
    r4.i = 0;
    r3.i = r1.i - (1);
    r6.i = r4.i;
    r1.i = r4.i;
L2:
    counters[1] ++;
    tmp = r1.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r3.i);
    v = (r1.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    r5.i = r3.i - (1);
    if (n == v)
    {
        goto L20;
    }
L5:
    counters[2] ++;
    r2.i = r0.i + (((uint32_t)r1.i << 2));
L3:
    counters[3] ++;
    load_counter ++;
    ldr(&ip.i, &r2.i, 0, 4, false, true, false);
    r1.i = r1.i + (1);
    load_counter ++;
    ldr(&lr.i, &r2.i, 4, 4, true, false, false);
    tmp = ip.i - lr.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) lr.i);
    v = (ip.i&0x80000000) != (lr.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (z || n != v)
    {
        goto L2;
    }
    counters[4] ++;
    tmp = r3.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r1.i);
    v = (r3.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    r6.i = 1;
    store_counter ++;
    str(&lr.i, &r2.i, -4, 4, false, false, false);
    store_counter ++;
    str(&ip.i, &r2.i, 0, 4, false, true, false);
    if (!z && n == v)
    {
        goto L3;
    }
L4:
    counters[5] ++;
    r2.i = r3.i - (2);
    tmp = r2.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r4.i);
    v = (r2.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    load_counter ++;
    if (n != v)
    {
        ldr(&r4.i, &sp.i, 0, 4, false, false, false);
        sp.i += 4;
        ldr(&r5.i, &sp.i, 0, 4, false, false, false);
        sp.i += 4;
        ldr(&r6.i, &sp.i, 0, 4, false, false, false);
        sp.i += 4;
        ldr(&pc.i, &sp.i, 0, 4, false, false, false);
        sp.i += 4;
        return;
    }
    r3.i = r3.i - (1);
    ip.i = r0.i + (((uint32_t)r4.i << 2));
    lr.i = 0;
    r3.i = r0.i + (((uint32_t)r3.i << 2));
L8:
    counters[6] ++;
    load_counter ++;
    ldr(&r2.i, &r3.i, 0, 4, false, true, false);
    load_counter ++;
    ldr(&r1.i, &r3.i, -4, 4, true, false, false);
    tmp = r2.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r1.i);
    v = (r2.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    store_counter ++;
    if (n != v)
    {
        str(&r1.i, &r3.i, 4, 4, false, false, false);
    }
    if (n != v)
    {
        lr.i = 1;
    }
    store_counter ++;
    if (n != v)
    {
        str(&r2.i, &r3.i, 0, 4, false, true, false);
    }
    tmp = ip.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r3.i);
    v = (ip.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (!z)
    {
        goto L8;
    }
    counters[7] ++;
    tmp = lr.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) 0);
    v = (lr.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    r1.i = r4.i + (1);
    load_counter ++;
    if (z)
    {
        ldr(&r4.i, &sp.i, 0, 4, false, false, false);
        sp.i += 4;
        ldr(&r5.i, &sp.i, 0, 4, false, false, false);
        sp.i += 4;
        ldr(&r6.i, &sp.i, 0, 4, false, false, false);
        sp.i += 4;
        ldr(&pc.i, &sp.i, 0, 4, false, false, false);
        sp.i += 4;
        return;
    }
    tmp = r1.i - r5.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r5.i);
    v = (r1.i&0x80000000) != (r5.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    load_counter ++;
    if (n == v)
    {
        ldr(&r4.i, &sp.i, 0, 4, false, false, false);
        sp.i += 4;
        ldr(&r5.i, &sp.i, 0, 4, false, false, false);
        sp.i += 4;
        ldr(&r6.i, &sp.i, 0, 4, false, false, false);
        sp.i += 4;
        ldr(&pc.i, &sp.i, 0, 4, false, false, false);
        sp.i += 4;
        return;
    }
    r3.i = r5.i;
    r4.i = r1.i;
    r5.i = r5.i - (1);
    r6.i = 0;
    goto L5;
L20:
    counters[8] ++;
    tmp = r6.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) 0);
    v = (r6.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    load_counter ++;
    if (z)
    {
        ldr(&r4.i, &sp.i, 0, 4, false, false, false);
        sp.i += 4;
        ldr(&r5.i, &sp.i, 0, 4, false, false, false);
        sp.i += 4;
        ldr(&r6.i, &sp.i, 0, 4, false, false, false);
        sp.i += 4;
        ldr(&pc.i, &sp.i, 0, 4, false, false, false);
        sp.i += 4;
        return;
    }
    goto L4;

}

void main()
{
    malloc_start();
    counters[9] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
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
    r0.i = 24;
    malloc_help();
    counters[10] ++;
    r3.i = 1;
    r1.i = (LC0 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC0 >> 16) << 16);
    ip.i = 6;
    r2.i = 5;
    r8.i = (LC1 & 0xffff);
    r8.i = r8.i | (((uint32_t)LC1 >> 16) << 16);
    r7.i = r0.i;
    r0.i = r3.i;
    store_counter ++;
    str(&r3.i, &r7.i, 20, 4, false, false, false);
    r3.i = 4;
    store_counter ++;
    str(&r2.i, &r7.i, 4, 4, false, false, false);
    r2.i = 3;
    store_counter ++;
    str(&r3.i, &r7.i, 8, 4, false, false, false);
    r3.i = 2;
    store_counter ++;
    str(&ip.i, &r7.i, 0, 4, false, true, false);
    r4.i = r7.i - (4);
    store_counter ++;
    str(&r2.i, &r7.i, 12, 4, false, false, false);
    r6.i = r7.i + (20);
    store_counter ++;
    str(&r3.i, &r7.i, 16, 4, false, false, false);
    printf(malloc_0+r1.i, r2.i);
    counters[11] ++;
    r5.i = r4.i;
L22:
    counters[12] ++;
    load_counter ++;
    ldr(&r2.i, &r5.i, 4, 4, true, false, false);
    r1.i = r8.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[13] ++;
    tmp = r5.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r6.i);
    v = (r5.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (!z)
    {
        goto L22;
    }
    counters[14] ++;
    r1.i = 6;
    r0.i = r7.i;
    cocktailSort();
    counters[15] ++;
    r1.i = (LC2 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC2 >> 16) << 16);
    printf(malloc_0+r1.i, r2.i);
    counters[16] ++;
    r5.i = (LC1 & 0xffff);
    r5.i = r5.i | (((uint32_t)LC1 >> 16) << 16);
L23:
    counters[17] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 4, 4, true, false, false);
    r1.i = r5.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[18] ++;
    tmp = r6.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) r4.i);
    v = (r6.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    if (!z)
    {
        goto L23;
    }
    counters[19] ++;
    r0.i = 10;
    printf("%c", (char)r0.i);
    counters[20] ++;
    r0.i = r7.i;
    free_help();
    counters[21] ++;
    r0.i = 0;
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
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    counter_summary();
    return;

}

