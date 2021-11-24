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

int32_t LC0;

int counters[15] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[15] = {5,11,3,1,6,4,7,6,1,3,18,4,2,2,2};


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

    int32_t malloc_total = (int32_t) ((uint8_t*) malloc(9) - malloc_0);
    LC0 = malloc_total;
    strcpy(malloc_0+LC0, "%d \000");

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "shaker_sort.c";

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
void shakersort();
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

void shakersort()
{
    counters[1] ++;
    tmp = r1.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 1);
    v = (r1.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
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
    r6.i = r1.i + (((uint32_t)r1.i >> 31));
    load_counter ++;
    if (z || n != v)
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
    ip.i = r1.i - (1);
    r6.i = r6.i >> 1;
    r5.i = r1.i - (2);
    lr.i = r0.i;
    ip.i = r0.i + (((uint32_t)ip.i << 2));
    r4.i = 0;
    r7.i = 1;
L11:
    counters[2] ++;
    r3.i = r1.i - (r7.i);
    tmp = r4.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r3.i);
    v = (r4.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (n == v)
    {
        goto L5;
    }
    counters[3] ++;
    r3.i = lr.i;
L7:
    counters[4] ++;
    load_counter ++;
    ldr(&r2.i, &r3.i, 0, 4, false, true, false);
    load_counter ++;
    ldr(&r0.i, &r3.i, 4, 4, true, false, false);
    tmp = r2.i - r0.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r0.i);
    v = (r2.i&0x80000000) != (r0.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    store_counter ++;
    if (!z && n == v)
    {
        tmp = r3.i;
        str(&r2.i, &r3.i, 0, 4, false, false, false);
        r3.i -= 4;
        str(&r0.i, &r3.i, 0, 4, false, false, false);
        r3.i -= 4;
        r3.i = tmp;
    }
    tmp = r3.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) ip.i);
    v = (r3.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L7;
    }
L5:
    counters[5] ++;
    ip.i = ip.i - (4);
    tmp = r5.i - r7.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r7.i);
    v = (r5.i&0x80000000) != (r7.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (n == v)
    {
        r3.i = ip.i;
    }
    if (n != v)
    {
        goto L8;
    }
L10:
    counters[6] ++;
    load_counter ++;
    ldr(&r2.i, &r3.i, 0, 4, false, true, false);
    load_counter ++;
    ldr(&r0.i, &r3.i, -4, 4, true, false, false);
    tmp = r2.i - r0.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r0.i);
    v = (r2.i&0x80000000) != (r0.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    store_counter ++;
    if (n != v)
    {
        str(&r0.i, &r3.i, 4, 4, false, false, false);
    }
    store_counter ++;
    if (n != v)
    {
        str(&r2.i, &r3.i, 0, 4, false, true, false);
    }
    tmp = r3.i - lr.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) lr.i);
    v = (r3.i&0x80000000) != (lr.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L10;
    }
L8:
    counters[7] ++;
    r7.i = r7.i + (1);
    r4.i = r4.i + (1);
    tmp = r7.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r7.i) >= ((uint32_t) r6.i);
    v = (r7.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
    r5.i = r5.i - (1);
    lr.i = lr.i + (4);
    if (z || n != v)
    {
        goto L11;
    }
    counters[8] ++;
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
    return;

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
    r1.i = 6;
    r3.i = 5;
    r2.i = 4;
    r6.i = (LC0 & 0xffff);
    r6.i = r6.i | (((uint32_t)LC0 >> 16) << 16);
    store_counter ++;
    str(&r3.i, &r0.i, 4, 4, false, false, false);
    r3.i = 3;
    store_counter ++;
    str(&r2.i, &r0.i, 8, 4, false, false, false);
    r2.i = 2;
    store_counter ++;
    str(&r3.i, &r0.i, 12, 4, false, false, false);
    r3.i = 1;
    store_counter ++;
    str(&r1.i, &r0.i, 0, 4, false, true, false);
    r5.i = r0.i;
    store_counter ++;
    str(&r2.i, &r0.i, 16, 4, false, false, false);
    r4.i = r5.i - (4);
    store_counter ++;
    str(&r3.i, &r0.i, 20, 4, false, false, false);
    r7.i = r5.i + (20);
    shakersort();
L19:
    counters[11] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 4, 4, true, false, false);
    r1.i = r6.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[12] ++;
    tmp = r7.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r7.i) >= ((uint32_t) r4.i);
    v = (r7.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
    if (!z)
    {
        goto L19;
    }
    counters[13] ++;
    r0.i = r5.i;
    free_help();
    counters[14] ++;
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

