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

int counters[33] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[33] = {3,4,4,2,3,5,2,6,5,2,5,2,5,2,6,2,1,2,5,5,2,5,4,3,1,3,16,3,3,4,3,2,2};


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

    int32_t malloc_total = (int32_t) ((uint8_t*) malloc(51) - malloc_0);
    LC0 = malloc_total;
    strcpy(malloc_0+LC0, "%d \000");

    LC1 = malloc_total + 9;
    strcpy(malloc_0+LC1, "Original array: \000");

    LC2 = malloc_total + 31;
    strcpy(malloc_0+LC2, "Sorted array: \000");

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "cycle_sort.c";

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

void display();
void swap();
void cycleSort();
void main();

void free_help()
{
    free(malloc_0+r0.i);
}
void malloc_help()
{
    uint8_t* ptr = (uint8_t*) malloc(r0.i);
    r0.i = (int32_t) (ptr - malloc_0);
}

void display()
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
    r5.i = r1.i - (0);
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
    r5.i = r0.i + (((uint32_t)r5.i << 2));
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

void cycleSort()
{
    counters[6] ++;
    tmp = r1.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 1);
    v = (r1.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (z || n != v)
    {
        return;
    }
    counters[7] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
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
    r4.i = 0;
    r8.i = r1.i - (1);
    lr.i = r0.i + (((uint32_t)r1.i << 2));
    r7.i = r4.i;
    r5.i = r0.i;
L20:
    counters[8] ++;
    r6.i = r7.i;
    r7.i = r7.i + (1);
    tmp = r1.i - r7.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r7.i);
    v = (r1.i&0x80000000) != (r7.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    load_counter ++;
    ldr(&r9.i, &r5.i, 4, 4, false, true, false);
    if (z || n != v)
    {
        goto L10;
    }
    counters[9] ++;
    r3.i = r5.i;
    r2.i = r6.i;
L12:
    counters[10] ++;
    load_counter ++;
    ldr(&ip.i, &r3.i, 4, 4, false, true, false);
    tmp = r9.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r9.i) >= ((uint32_t) ip.i);
    v = (r9.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r9.i&0x80000000);
    if (!z && n == v)
    {
        r2.i = r2.i + (1);
    }
    tmp = lr.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) r3.i);
    v = (lr.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    if (!z)
    {
        goto L12;
    }
    counters[11] ++;
    tmp = r4.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r2.i);
    v = (r4.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (z)
    {
        goto L10;
    }
    counters[12] ++;
    load_counter ++;
    ldr(&ip.i, &r0.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    r3.i = (uint32_t)r2.i << 2;
    r10.i = r0.i + (r3.i);
    tmp = r9.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r9.i) >= ((uint32_t) ip.i);
    v = (r9.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r9.i&0x80000000);
    if (!z)
    {
        goto L13;
    }
    counters[13] ++;
    r3.i = r3.i + (4);
    r3.i = r0.i + (r3.i);
L14:
    counters[14] ++;
    load_counter ++;
    ldr(&ip.i, &r3.i, 0, 4, false, true, false);
    r10.i = r3.i;
    r2.i = r2.i + (1);
    r3.i = r3.i + (4);
    tmp = r9.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r9.i) >= ((uint32_t) ip.i);
    v = (r9.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r9.i&0x80000000);
    if (z)
    {
        goto L14;
    }
    counters[15] ++;
    tmp = r4.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r2.i);
    v = (r4.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (z)
    {
        goto L10;
    }
L13:
    counters[16] ++;
    store_counter ++;
    str(&r9.i, &r10.i, 0, 4, false, true, false);
L15:
    counters[17] ++;
    r3.i = r5.i;
    r2.i = r6.i;
L17:
    counters[18] ++;
    load_counter ++;
    ldr(&r9.i, &r3.i, 4, 4, false, true, false);
    tmp = ip.i - r9.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r9.i);
    v = (ip.i&0x80000000) != (r9.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (!z && n == v)
    {
        r2.i = r2.i + (1);
    }
    tmp = r3.i - lr.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) lr.i);
    v = (r3.i&0x80000000) != (lr.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L17;
    }
    counters[19] ++;
    load_counter ++;
    ldr(&r9.i, &r0.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    r3.i = (uint32_t)r2.i << 2;
    r10.i = r0.i + (r3.i);
    tmp = r9.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r9.i) >= ((uint32_t) ip.i);
    v = (r9.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r9.i&0x80000000);
    if (!z)
    {
        goto L18;
    }
    counters[20] ++;
    r3.i = r3.i + (4);
    r3.i = r0.i + (r3.i);
L19:
    counters[21] ++;
    r10.i = r3.i;
    load_counter ++;
    ldr(&r9.i, &r3.i, 4, 4, false, true, false);
    r2.i = r2.i + (1);
    tmp = r9.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r9.i) >= ((uint32_t) ip.i);
    v = (r9.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r9.i&0x80000000);
    if (z)
    {
        goto L19;
    }
L18:
    counters[22] ++;
    tmp = r4.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r2.i);
    v = (r4.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    store_counter ++;
    str(&ip.i, &r10.i, 0, 4, false, true, false);
    if (!z)
    {
        ip.i = r9.i;
    }
    if (!z)
    {
        goto L15;
    }
L10:
    counters[23] ++;
    tmp = r8.i - r7.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) r7.i);
    v = (r8.i&0x80000000) != (r7.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    r4.i = r4.i + (1);
    if (!z)
    {
        goto L20;
    }
    counters[24] ++;
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
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;

}

void main()
{
    malloc_start();
    counters[25] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r6.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r4.i, &sp.i, 0, 4, false, false, false);
    r0.i = 24;
    malloc_help();
    counters[26] ++;
    r6.i = 1;
    r5.i = 6;
    r1.i = (LC1 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC1 >> 16) << 16);
    r2.i = 3;
    r3.i = 5;
    r4.i = r0.i;
    r0.i = r6.i;
    store_counter ++;
    str(&r3.i, &r4.i, 4, 4, false, false, false);
    r3.i = 4;
    store_counter ++;
    str(&r5.i, &r4.i, 0, 4, false, true, false);
    store_counter ++;
    str(&r3.i, &r4.i, 8, 4, false, false, false);
    r3.i = 2;
    store_counter ++;
    str(&r6.i, &r4.i, 20, 4, false, false, false);
    store_counter ++;
    str(&r2.i, &r4.i, 12, 4, false, false, false);
    str(&r3.i, &r4.i, 16, 4, false, false, false);
    printf(malloc_0+r1.i, r2.i);
    counters[27] ++;
    r1.i = r5.i;
    r0.i = r4.i;
    display();
    counters[28] ++;
    r1.i = r5.i;
    r0.i = r4.i;
    cycleSort();
    counters[29] ++;
    r0.i = r6.i;
    r1.i = (LC2 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC2 >> 16) << 16);
    printf(malloc_0+r1.i, r2.i);
    counters[30] ++;
    r1.i = r5.i;
    r0.i = r4.i;
    display();
    counters[31] ++;
    r0.i = r4.i;
    free_help();
    counters[32] ++;
    r0.i = 0;
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

