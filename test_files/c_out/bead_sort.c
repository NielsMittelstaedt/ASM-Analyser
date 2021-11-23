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

reg r3, r6, r10, r0, r4, r1, r2, r5, r8, r7, r9;

int32_t LC0, LC1, LC2, LC3, LC4;

int counters[44] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[44] = {3,4,4,2,3,6,2,5,3,1,3,5,1,4,5,5,7,3,2,5,3,2,2,3,3,3,3,4,3,5,1,3,3,1,5,4,2,14,3,3,4,3,2,2};


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
    char filename[] = "bead_sort.c";

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
void bead_sort();
void main();

void calloc_help()
{
    uint8_t* ptr = (uint8_t*) calloc(r0.i, r1.i);
    r0.i = (int32_t) (ptr - malloc_0);
}
void malloc_help()
{
    uint8_t* ptr = (uint8_t*) malloc(r0.i);
    r0.i = (int32_t) (ptr - malloc_0);
}
void free_help()
{
    free(malloc_0+r0.i);
}
void memset_help()
{
    memset(malloc_0+r0.i, r1.i, r2.i);
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

void bead_sort()
{
    counters[5] ++;
    tmp = r1.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 1);
    v = (r1.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    store_counter ++;
    sp.i -= 32;
    str(&r4.i, &sp.i, 0*4, 4, false, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false, false);
    str(&r7.i, &sp.i, 3*4, 4, false, false, false);
    str(&r8.i, &sp.i, 4*4, 4, false, false, false);
    str(&r9.i, &sp.i, 5*4, 4, false, false, false);
    str(&r10.i, &sp.i, 6*4, 4, false, false, false);
    str(&lr.i, &sp.i, 7*4, 4, false, false, false);
    r7.i = r1.i;
    load_counter ++;
    ldr(&r4.i, &r0.i, 0, 4, false, true, false);
    r5.i = r0.i;
    if (!c || z)
    {
        goto L8;
    }
    counters[6] ++;
    r3.i = r0.i + 4;
    r1.i = r0.i + ((uint32_t)r1.i << 2);
L9:
    counters[7] ++;
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
    tmp = r1.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r3.i);
    v = (r1.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!z)
    {
        goto L9;
    }
    counters[8] ++;
    r1.i = r7.i * r4.i;
    r0.i = 1;
    calloc_help();
    counters[9] ++;
    r6.i = r0.i;
L11:
    counters[10] ++;
    r10.i = r5.i - 4;
    r9.i = r6.i;
    r8.i = 0;
L13:
    counters[11] ++;
    load_counter ++;
    ldr(&r2.i, &r10.i, 4, 4, true, false, false);
    r0.i = r9.i;
    r1.i = 1;
    tmp = r2.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) 0);
    v = (r2.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (z || n != v)
    {
        goto L15;
    }
    counters[12] ++;
    memset_help();
L15:
    counters[13] ++;
    r8.i = r8.i + 1;
    r9.i = r9.i + r4.i;
    tmp = r7.i - r8.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r7.i) >= ((uint32_t) r8.i);
    v = (r7.i&0x80000000) != (r8.i&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
    if (c && !z)
    {
        goto L13;
    }
L12:
    counters[14] ++;
    tmp = r4.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 0);
    v = (r4.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z && n == v)
    {
        r8.i = 0;
    }
    if (!z && n == v)
    {
        r0.i = 1;
    }
    if (!z && n == v)
    {
        r1.i = r8.i;
    }
    if (z || n != v)
    {
        goto L17;
    }
L16:
    counters[15] ++;
    tmp = r7.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r7.i) >= ((uint32_t) 0);
    v = (r7.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
    if (!z)
    {
        ip.i = r6.i + r8.i;
    }
    if (!z)
    {
        r3.i = 0;
    }
    if (!z)
    {
        r2.i = r3.i;
    }
    if (z)
    {
        goto L19;
    }
L18:
    counters[16] ++;
    lr.i = r2.i;
    r2.i = r2.i + 1;
    load_counter ++;
    ldr(&r9.i, &ip.i, 0, 1, false, true, false);
    tmp = r2.i - r7.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r7.i);
    v = (r2.i&0x80000000) != (r7.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    store_counter ++;
    str(&r1.i, &ip.i, r4.i, 1, false, true, false);
    r3.i = r3.i + r9.i;
    if (!z)
    {
        goto L18;
    }
    counters[17] ++;
    r3.i = r7.i - r3.i;
    tmp = r3.i - r7.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r7.i);
    v = (r3.i&0x80000000) != (r7.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (c)
    {
        goto L19;
    }
    counters[18] ++;
    r2.i = (r3.i * r4.i) + r8.i;
    r2.i = r6.i + r2.i;
L20:
    counters[19] ++;
    tmp = lr.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) r3.i);
    v = (lr.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    ip.i = r3.i;
    store_counter ++;
    str(&r0.i, &r2.i, r4.i, 1, false, true, false);
    r3.i = r3.i + 1;
    if (!z)
    {
        goto L20;
    }
L19:
    counters[20] ++;
    r8.i = r8.i + 1;
    tmp = r4.i - r8.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r8.i);
    v = (r4.i&0x80000000) != (r8.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        goto L16;
    }
L17:
    counters[21] ++;
    tmp = r7.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r7.i) >= ((uint32_t) 0);
    v = (r7.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
    if (z)
    {
        goto L22;
    }
    counters[22] ++;
    r0.i = r6.i - 1;
    r7.i = r5.i + ((uint32_t)r7.i << 2);
L23:
    counters[23] ++;
    tmp = r4.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 0);
    v = (r4.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (z || n != v)
    {
        r3.i = 0;
    }
    if (z || n != v)
    {
        goto L24;
    }
    counters[24] ++;
    r2.i = r0.i;
    r3.i = 0;
    goto L26;
L25:
    counters[25] ++;
    r3.i = r3.i + 1;
    tmp = r4.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r3.i);
    v = (r4.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (z)
    {
        goto L40;
    }
L26:
    counters[26] ++;
    load_counter ++;
    ldr(&r1.i, &r2.i, 1, 1, true, false, false);
    tmp = r1.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 0);
    v = (r1.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!z)
    {
        goto L25;
    }
L24:
    counters[27] ++;
    store_counter ++;
    str(&r3.i, &r5.i, 4, 4, false, true, false);
    tmp = r5.i - r7.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r7.i);
    v = (r5.i&0x80000000) != (r7.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    r0.i = r0.i + r4.i;
    if (!z)
    {
        goto L23;
    }
L22:
    counters[28] ++;
    r0.i = r6.i;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false, false);
    ldr(&r7.i, &sp.i, 3*4, 4, false, false, false);
    ldr(&r8.i, &sp.i, 4*4, 4, false, false, false);
    ldr(&r9.i, &sp.i, 5*4, 4, false, false, false);
    ldr(&r10.i, &sp.i, 6*4, 4, false, false, false);
    ldr(&lr.i, &sp.i, 7*4, 4, false, false, false);
    sp.i += 32;
    free_help();
    return;
L40:
    counters[29] ++;
    r3.i = r4.i;
    store_counter ++;
    str(&r3.i, &r5.i, 4, 4, false, true, false);
    tmp = r5.i - r7.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r7.i);
    v = (r5.i&0x80000000) != (r7.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    r0.i = r0.i + r4.i;
    if (!z)
    {
        goto L23;
    }
    counters[30] ++;
    goto L22;
L8:
    counters[31] ++;
    r1.i = r1.i * r4.i;
    r0.i = 1;
    calloc_help();
    counters[32] ++;
    tmp = r7.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r7.i) >= ((uint32_t) 0);
    v = (r7.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
    r6.i = r0.i;
    if (z)
    {
        goto L12;
    }
    counters[33] ++;
    goto L11;
    return;
}

void main()
{
    malloc_start();
    counters[34] ++;
    store_counter ++;
    sp.i -= 16;
    str(&r4.i, &sp.i, 0*4, 4, false, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false, false);
    str(&lr.i, &sp.i, 3*4, 4, false, false, false);
    r0.i = (LC1 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC1 >> 16) << 16);
    r6.i = 1;
    printf("%s\n", malloc_0+r0.i);
    counters[35] ++;
    r0.i = (LC2 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC2 >> 16) << 16);
    r5.i = 6;
    printf("%s\n", malloc_0+r0.i);
    counters[36] ++;
    r0.i = 24;
    malloc_help();
    counters[37] ++;
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
    counters[38] ++;
    r1.i = r5.i;
    r0.i = r4.i;
    display();
    counters[39] ++;
    r1.i = r5.i;
    r0.i = r4.i;
    bead_sort();
    counters[40] ++;
    r0.i = r6.i;
    r1.i = (LC4 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC4 >> 16) << 16);
    printf(malloc_0+r1.i, r2.i);
    counters[41] ++;
    r1.i = r5.i;
    r0.i = r4.i;
    display();
    counters[42] ++;
    r0.i = r4.i;
    free_help();
    counters[43] ++;
    r0.i = 0;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false, false);
    ldr(&pc.i, &sp.i, 3*4, 4, false, false, false);
    sp.i += 16;
    counter_summary();
    return;

}

