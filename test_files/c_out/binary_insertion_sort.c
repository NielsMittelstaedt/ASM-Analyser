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

int32_t LC0, LC1, LC2, LC3, LC4;

int counters[41] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[41] = {3,4,4,2,3,4,1,5,1,4,5,3,1,2,2,8,3,4,1,4,1,3,3,2,4,3,9,3,3,4,2,5,4,2,14,3,3,4,3,2,2};


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

    int32_t malloc_total = (int32_t) ((uint8_t*) malloc(114) - malloc_0);
    LC0 = malloc_total;
    strcpy(malloc_0+LC0, "%d \000");

    LC1 = malloc_total + 9;
    strcpy(malloc_0+LC1, "Enter size of array:\000");

    LC2 = malloc_total + 35;
    strcpy(malloc_0+LC2, "Enter the elements of the array\000");

    LC3 = malloc_total + 72;
    strcpy(malloc_0+LC3, "Original array: \000");

    LC4 = malloc_total + 94;
    strcpy(malloc_0+LC4, "Sorted array: \000");

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "binary_insertion_sort.c";

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
void binarySearch();
void insertionSort();
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

void binarySearch()
{
    counters[5] ++;
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r4.i, &sp.i, 0, 4, false, false, false);
    r5.i = r0.i;
    if (n == v)
    {
        goto L15;
    }
    counters[6] ++;
    lr.i = r3.i - (1);
L9:
    counters[7] ++;
    ip.i = lr.i + (((uint32_t)lr.i >> 31));
    ip.i = r2.i + ((ip.i >> 1));
    load_counter ++;
    ldr(&r4.i, &r5.i, ((uint32_t)ip.i << 2), 4, false, false, false);
    tmp = r4.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r1.i);
    v = (r4.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (z)
    {
        goto L17;
    }
    counters[8] ++;
    if (z || n != v)
    {
        goto L12;
    }
    counters[9] ++;
    r3.i = ip.i - (1);
    tmp = r3.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r2.i);
    v = (r3.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    lr.i = r3.i - (1);
    if (!z && n == v)
    {
        goto L9;
    }
L15:
    counters[10] ++;
    load_counter ++;
    ldr(&r3.i, &r5.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    r0.i = r2.i;
    tmp = r3.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r1.i);
    v = (r3.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (n != v)
    {
        r0.i = r2.i + (1);
    }
    load_counter ++;
    ldr(&r4.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;
L12:
    counters[11] ++;
    r2.i = ip.i + (1);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n != v)
    {
        goto L9;
    }
    counters[12] ++;
    goto L15;
L17:
    counters[13] ++;
    r0.i = ip.i + (1);
    load_counter ++;
    ldr(&r4.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;

}

void insertionSort()
{
    counters[14] ++;
    tmp = r1.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 0);
    v = (r1.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (z || n != v)
    {
        return;
    }
    counters[15] ++;
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
    r5.i = ~0;
    r6.i = r0.i - (4);
    tmp = r5.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) 0);
    v = (r5.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    r7.i = r1.i - (1);
    r8.i = r5.i;
    load_counter ++;
    ldr(&r4.i, &r6.i, 4, 4, true, false, false);
    if (z || n != v)
    {
        goto L31;
    }
L42:
    counters[16] ++;
    lr.i = r5.i - (1);
    ip.i = r5.i;
    r2.i = 0;
L21:
    counters[17] ++;
    r3.i = r2.i + ((lr.i >> 1));
    load_counter ++;
    ldr(&r1.i, &r0.i, ((uint32_t)r3.i << 2), 4, false, false, false);
    tmp = r4.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r1.i);
    v = (r4.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (z)
    {
        goto L41;
    }
L23:
    counters[18] ++;
    if (n == v)
    {
        goto L24;
    }
    counters[19] ++;
    ip.i = r3.i - (1);
    tmp = ip.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r2.i);
    v = (ip.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    lr.i = ip.i - (1);
    if (!z && n == v)
    {
        goto L21;
    }
L25:
    counters[20] ++;
    r3.i = r0.i + (((uint32_t)r2.i << 2));
L20:
    counters[21] ++;
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, true, false);
    tmp = r4.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r3.i);
    v = (r4.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z && n == v)
    {
        r2.i = r2.i + (1);
    }
L22:
    counters[22] ++;
    tmp = r5.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r2.i);
    v = (r5.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (n != v)
    {
        r3.i = r5.i + (1);
    }
    if (n != v)
    {
        goto L27;
    }
    counters[23] ++;
    ip.i = r0.i + (((uint32_t)r2.i << 2));
    r3.i = r6.i;
L28:
    counters[24] ++;
    load_counter ++;
    ldr(&r1.i, &r3.i, -4, 4, false, false, false);
    store_counter ++;
    str(&r1.i, &r3.i, -4, 4, false, true, false);
    tmp = ip.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r3.i);
    v = (ip.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (!z)
    {
        goto L28;
    }
    counters[25] ++;
    r3.i = r5.i + (1);
    r2.i = r2.i - (r3.i);
    r8.i = r2.i + (r5.i);
L27:
    counters[26] ++;
    r2.i = r8.i + (1);
    tmp = r7.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r7.i) >= ((uint32_t) r3.i);
    v = (r7.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
    r5.i = r3.i;
    store_counter ++;
    str(&r4.i, &r0.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    load_counter ++;
    if (z)
    {
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
        return;
    }
    tmp = r5.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) 0);
    v = (r5.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    load_counter ++;
    ldr(&r4.i, &r6.i, 4, 4, true, false, false);
    r8.i = r5.i;
    if (!z && n == v)
    {
        goto L42;
    }
L31:
    counters[27] ++;
    r3.i = r0.i;
    r2.i = 0;
    goto L20;
L24:
    counters[28] ++;
    r2.i = r3.i + (1);
    tmp = r2.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) ip.i);
    v = (r2.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n == v)
    {
        goto L25;
    }
    counters[29] ++;
    r3.i = r2.i + ((lr.i >> 1));
    load_counter ++;
    ldr(&r1.i, &r0.i, ((uint32_t)r3.i << 2), 4, false, false, false);
    tmp = r4.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r1.i);
    v = (r4.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        goto L23;
    }
L41:
    counters[30] ++;
    r2.i = r3.i + (1);
    goto L22;
    return;
}

void main()
{
    malloc_start();
    counters[31] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r6.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r4.i, &sp.i, 0, 4, false, false, false);
    r0.i = (LC1 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC1 >> 16) << 16);
    r6.i = 1;
    printf("%s\n", malloc_0+r0.i);
    counters[32] ++;
    r0.i = (LC2 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC2 >> 16) << 16);
    r5.i = 6;
    printf("%s\n", malloc_0+r0.i);
    counters[33] ++;
    r0.i = 24;
    malloc_help();
    counters[34] ++;
    r1.i = (LC3 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC3 >> 16) << 16);
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
    counters[35] ++;
    r1.i = r5.i;
    r0.i = r4.i;
    display();
    counters[36] ++;
    r1.i = r5.i;
    r0.i = r4.i;
    insertionSort();
    counters[37] ++;
    r0.i = r6.i;
    r1.i = (LC4 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC4 >> 16) << 16);
    printf(malloc_0+r1.i, r2.i);
    counters[38] ++;
    r1.i = r5.i;
    r0.i = r4.i;
    display();
    counters[39] ++;
    r0.i = r4.i;
    free_help();
    counters[40] ++;
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

