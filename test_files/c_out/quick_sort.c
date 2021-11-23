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

reg r3, r6, r0, r4, r1, r2, r5, r8, r7;

int32_t LC0, LC1, LC2;

int counters[28] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[28] = {3,4,4,2,3,5,6,2,5,6,2,1,4,2,2,4,4,9,8,3,1,3,17,3,4,4,3,2};


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
    char filename[] = "quick_sort.c";

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
void partition();
void quickSort();
void main();

void malloc_help()
{
    uint8_t* ptr = (uint8_t*) malloc(r0.i);
    r0.i = (int32_t) (ptr - malloc_0);
}

void display()
{
    counters[0] ++;
    store_counter ++;
    sp.i -= 16;
    str(&r4.i, &sp.i, 0*4, 4, false, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false, false);
    str(&lr.i, &sp.i, 3*4, 4, false, false, false);
    r5.i = r1.i - 0;
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
    r5.i = r0.i + ((uint32_t)r5.i << 2);
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
    ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false, false);
    ldr(&lr.i, &sp.i, 3*4, 4, false, false, false);
    sp.i += 16;
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

void partition()
{
    counters[6] ++;
    tmp = r1.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r2.i);
    v = (r1.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    store_counter ++;
    sp.i -= 24;
    str(&r4.i, &sp.i, 0*4, 4, false, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false, false);
    str(&r7.i, &sp.i, 3*4, 4, false, false, false);
    str(&r8.i, &sp.i, 4*4, 4, false, false, false);
    str(&lr.i, &sp.i, 5*4, 4, false, false, false);
    r7.i = r0.i + ((uint32_t)r2.i << 2);
    load_counter ++;
    ldr(&r6.i, &r0.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    lr.i = r0.i;
    if (n == v)
    {
        goto L12;
    }
    counters[7] ++;
    r4.i = r1.i - 1;
    r3.i = r0.i + ((uint32_t)r1.i << 2);
L11:
    counters[8] ++;
    load_counter ++;
    ldr(&ip.i, &r3.i, 4, 4, false, true, false);
    r5.i = r4.i + 2;
    r0.i = r1.i;
    tmp = ip.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r6.i);
    v = (ip.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (!z && n == v)
    {
        goto L10;
    }
    counters[9] ++;
    load_counter ++;
    ldr(&r8.i, &lr.i, ((uint32_t)r1.i << 2), 4, false, false, false);
    r4.i = r1.i;
    store_counter ++;
    str(&ip.i, &lr.i, ((uint32_t)r1.i << 2), 4, false, false, false);
    r1.i = r1.i + 1;
    r0.i = r5.i;
    store_counter ++;
    str(&r8.i, &r3.i, -4, 4, false, false, false);
L10:
    counters[10] ++;
    tmp = r7.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r7.i) >= ((uint32_t) r3.i);
    v = (r7.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
    if (!z)
    {
        goto L11;
    }
    counters[11] ++;
    load_counter ++;
    ldr(&r6.i, &lr.i, ((uint32_t)r2.i << 2), 4, false, false, false);
L9:
    counters[12] ++;
    load_counter ++;
    ldr(&r3.i, &lr.i, ((uint32_t)r1.i << 2), 4, false, false, false);
    store_counter ++;
    str(&r6.i, &lr.i, ((uint32_t)r1.i << 2), 4, false, false, false);
    store_counter ++;
    str(&r3.i, &lr.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false, false);
    ldr(&r7.i, &sp.i, 3*4, 4, false, false, false);
    ldr(&r8.i, &sp.i, 4*4, 4, false, false, false);
    ldr(&pc.i, &sp.i, 5*4, 4, false, false, false);
    sp.i += 24;
    return;
L12:
    counters[13] ++;
    r0.i = r1.i;
    goto L9;
    return;
}

void quickSort()
{
    counters[14] ++;
    tmp = r1.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r2.i);
    v = (r1.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (n == v)
    {
        return;
    }
    counters[15] ++;
    store_counter ++;
    sp.i -= 24;
    str(&r4.i, &sp.i, 0*4, 4, false, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false, false);
    str(&r7.i, &sp.i, 3*4, 4, false, false, false);
    str(&r8.i, &sp.i, 4*4, 4, false, false, false);
    str(&lr.i, &sp.i, 5*4, 4, false, false, false);
    r7.i = r0.i + ((uint32_t)r2.i << 2);
    r6.i = r2.i;
    r5.i = r0.i;
L19:
    counters[16] ++;
    load_counter ++;
    ldr(&lr.i, &r7.i, 0, 4, false, true, false);
    r4.i = r1.i - 1;
    r0.i = r5.i + ((uint32_t)r1.i << 2);
    r3.i = r1.i;
L18:
    counters[17] ++;
    load_counter ++;
    ldr(&ip.i, &r0.i, 4, 4, false, true, false);
    r3.i = r3.i + 1;
    tmp = lr.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) ip.i);
    v = (lr.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    if (n == v)
    {
        r4.i = r4.i + 1;
    }
    load_counter ++;
    if (n == v)
    {
        ldr(&r2.i, &r5.i, ((uint32_t)r4.i << 2), 4, false, false, false);
    }
    store_counter ++;
    if (n == v)
    {
        str(&ip.i, &r5.i, ((uint32_t)r4.i << 2), 4, false, false, false);
    }
    store_counter ++;
    if (n == v)
    {
        str(&r2.i, &r0.i, -4, 4, false, false, false);
    }
    tmp = r6.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) r3.i);
    v = (r6.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    if (!z && n == v)
    {
        goto L18;
    }
    counters[18] ++;
    r3.i = r4.i + 1;
    load_counter ++;
    ldr(&lr.i, &r7.i, 0, 4, false, true, false);
    r2.i = r4.i;
    r0.i = r5.i;
    load_counter ++;
    ldr(&ip.i, &r5.i, ((uint32_t)r3.i << 2), 4, false, false, false);
    store_counter ++;
    str(&lr.i, &r5.i, ((uint32_t)r3.i << 2), 4, false, false, false);
    store_counter ++;
    str(&ip.i, &r7.i, 0, 4, false, true, false);
    quickSort();
    counters[19] ++;
    r1.i = r4.i + 2;
    tmp = r1.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r6.i);
    v = (r1.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (n != v)
    {
        goto L19;
    }
    counters[20] ++;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false, false);
    ldr(&r7.i, &sp.i, 3*4, 4, false, false, false);
    ldr(&r8.i, &sp.i, 4*4, 4, false, false, false);
    ldr(&pc.i, &sp.i, 5*4, 4, false, false, false);
    sp.i += 24;
    return;

}

void main()
{
    malloc_start();
    counters[21] ++;
    store_counter ++;
    sp.i -= 24;
    str(&r4.i, &sp.i, 0*4, 4, false, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false, false);
    str(&r7.i, &sp.i, 3*4, 4, false, false, false);
    str(&r8.i, &sp.i, 4*4, 4, false, false, false);
    str(&lr.i, &sp.i, 5*4, 4, false, false, false);
    r0.i = 24;
    malloc_help();
    counters[22] ++;
    r6.i = 1;
    r5.i = 6;
    r1.i = (LC1 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC1 >> 16) << 16);
    r2.i = 3;
    r7.i = 5;
    r3.i = 4;
    r4.i = r0.i;
    r0.i = r6.i;
    store_counter ++;
    str(&r2.i, &r4.i, 12, 4, false, false, false);
    store_counter ++;
    str(&r3.i, &r4.i, 8, 4, false, false, false);
    r3.i = 2;
    store_counter ++;
    str(&r5.i, &r4.i, 0, 4, false, true, false);
    store_counter ++;
    str(&r3.i, &r4.i, 16, 4, false, false, false);
    store_counter ++;
    str(&r7.i, &r4.i, 4, 4, false, false, false);
    store_counter ++;
    str(&r6.i, &r4.i, 20, 4, false, false, false);
    printf(malloc_0+r1.i, r2.i);
    counters[23] ++;
    r1.i = r5.i;
    r0.i = r4.i;
    display();
    counters[24] ++;
    r2.i = r7.i;
    r0.i = r4.i;
    r1.i = 0;
    quickSort();
    counters[25] ++;
    r0.i = r6.i;
    r1.i = (LC2 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC2 >> 16) << 16);
    printf(malloc_0+r1.i, r2.i);
    counters[26] ++;
    r0.i = r4.i;
    r1.i = r5.i;
    display();
    counters[27] ++;
    r0.i = 0;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false, false);
    ldr(&r7.i, &sp.i, 3*4, 4, false, false, false);
    ldr(&r8.i, &sp.i, 4*4, 4, false, false, false);
    ldr(&pc.i, &sp.i, 5*4, 4, false, false, false);
    sp.i += 24;
    counter_summary();
    return;

}

