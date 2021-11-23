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

int32_t LC0, LC1, LC2;

int counters[41] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[41] = {7,3,7,6,3,3,2,8,2,5,3,10,10,5,5,1,4,4,3,3,3,3,3,1,4,2,7,2,3,21,1,4,2,3,4,2,4,2,2,2,2};


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
    char filename[] = "pigeonhole_sort.c";

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

void pigeonholeSort();
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
void memset_help()
{
    memset(malloc_0+r0.i, r1.i, r2.i);
}

void pigeonholeSort()
{
    counters[0] ++;
    tmp = r1.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 1);
    v = (r1.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    store_counter ++;
    sp.i -= 36;
    str(&r4.i, &sp.i, 0*4, 4, false, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false, false);
    str(&r7.i, &sp.i, 3*4, 4, false, false, false);
    str(&r8.i, &sp.i, 4*4, 4, false, false, false);
    str(&r9.i, &sp.i, 5*4, 4, false, false, false);
    str(&r10.i, &sp.i, 6*4, 4, false, false, false);
    str(&fp.i, &sp.i, 7*4, 4, false, false, false);
    str(&lr.i, &sp.i, 8*4, 4, false, false, false);
    r6.i = r1.i;
    load_counter ++;
    ldr(&r4.i, &r0.i, 0, 4, false, true, false);
    sp.i = sp.i - 12;
    r5.i = r0.i;
    if (z || n != v)
    {
        goto L2;
    }
    counters[1] ++;
    r1.i = r0.i + 4;
    r0.i = r0.i + ((uint32_t)r6.i << 2);
    r2.i = r4.i;
L3:
    counters[2] ++;
    load_counter ++;
    ldr(&r3.i, &r1.i, 4, 4, false, true, false);
    tmp = r4.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r3.i);
    v = (r4.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (n == v)
    {
        r4.i = r3.i;
    }
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n != v)
    {
        r2.i = r3.i;
    }
    tmp = r1.i - r0.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r0.i);
    v = (r1.i&0x80000000) != (r0.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!z)
    {
        goto L3;
    }
    counters[3] ++;
    r2.i = r2.i - r4.i;
    r7.i = r2.i + 1;
    r8.i = (uint32_t)r7.i << 2;
    r9.i = r7.i;
    r0.i = r8.i;
    malloc_help();
    counters[4] ++;
    tmp = r7.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r7.i) >= ((uint32_t) 0);
    v = (r7.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
    r7.i = r0.i;
    if (z || n != v)
    {
        goto L15;
    }
    counters[5] ++;
    r2.i = r8.i;
    r1.i = 0;
    memset_help();
L15:
    counters[6] ++;
    r0.i = r5.i - 4;
    r1.i = 0;
L5:
    counters[7] ++;
    load_counter ++;
    ldr(&r3.i, &r0.i, 4, 4, true, false, false);
    r1.i = r1.i + 1;
    tmp = r6.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) r1.i);
    v = (r6.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    r3.i = r3.i - r4.i;
    load_counter ++;
    ldr(&r2.i, &r7.i, ((uint32_t)r3.i << 2), 4, false, false, false);
    r2.i = r2.i + 1;
    store_counter ++;
    str(&r2.i, &r7.i, ((uint32_t)r3.i << 2), 4, false, false, false);
    if (!z && n == v)
    {
        goto L5;
    }
    counters[8] ++;
    tmp = r9.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r9.i) >= ((uint32_t) 0);
    v = (r9.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r9.i&0x80000000);
    if (z || n != v)
    {
        goto L7;
    }
L6:
    counters[9] ++;
    r3.i = 0;
    r8.i = r7.i - 4;
    r0.i = r3.i;
    fp.i = r9.i;
    store_counter ++;
    str(&r7.i, &sp.i, 4, 4, false, false, false);
L12:
    counters[10] ++;
    load_counter ++;
    ldr(&ip.i, &r8.i, 4, 4, true, false, false);
    tmp = ip.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) 0);
    v = (ip.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (z || n != v)
    {
        goto L14;
    }
    counters[11] ++;
    r6.i = ip.i - 1;
    r7.i = (uint32_t)r3.i << 2;
    tmp = r6.i - 5;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) 5);
    v = (r6.i&0x80000000) != (5&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    r2.i = r5.i + r7.i;
    r9.i = r3.i + 1;
    r2.i = (r2.i >> 2) & ((1 << 1) - 1);
    r1.i = r4.i + r0.i;
    r10.i = r6.i;
    lr.i = ip.i;
    if (z || n != v)
    {
        goto L8;
    }
    counters[12] ++;
    tmp = r2.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) 0);
    v = (r2.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    lr.i = lr.i - r2.i;
    r2.i = r3.i + r2.i;
    store_counter ++;
    if (!z)
    {
        str(&r1.i, &r5.i, r7.i, 4, false, false, false);
    }
    if (z)
    {
        r7.i = r3.i;
    }
    r3.i = (uint32_t)lr.i >> 1;
    r2.i = r5.i + ((uint32_t)r2.i << 2);
    if (!z)
    {
        ip.i = r6.i;
    }
    r3.i = r2.i + ((uint32_t)r3.i << 3);
    if (!z)
    {
        r7.i = r9.i;
    }
L10:
    counters[13] ++;
    store_counter ++;
    str(&r1.i, &r2.i, 0, 4, false, true, false);
    r2.i = r2.i + 8;
    store_counter ++;
    str(&r1.i, &r2.i, -4, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z)
    {
        goto L10;
    }
    counters[14] ++;
    r3.i = lr.i & ~1;
    tmp = r3.i - lr.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) lr.i);
    v = (r3.i&0x80000000) != (lr.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    ip.i = ip.i - r3.i;
    r3.i = r3.i + r7.i;
    if (z)
    {
        goto L11;
    }
    counters[15] ++;
    r10.i = ip.i - 1;
L8:
    counters[16] ++;
    tmp = r10.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r10.i) >= ((uint32_t) 0);
    v = (r10.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r10.i&0x80000000);
    store_counter ++;
    str(&r1.i, &r5.i, ((uint32_t)r3.i << 2), 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    if (z)
    {
        goto L11;
    }
    counters[17] ++;
    r3.i = r5.i + r3.i;
    tmp = ip.i - 2;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) 2);
    v = (ip.i&0x80000000) != (2&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    store_counter ++;
    str(&r1.i, &r3.i, 4, 4, false, false, false);
    if (z)
    {
        goto L11;
    }
    counters[18] ++;
    tmp = ip.i - 3;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) 3);
    v = (ip.i&0x80000000) != (3&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    store_counter ++;
    str(&r1.i, &r3.i, 8, 4, false, false, false);
    if (z)
    {
        goto L11;
    }
    counters[19] ++;
    tmp = ip.i - 4;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) 4);
    v = (ip.i&0x80000000) != (4&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    store_counter ++;
    str(&r1.i, &r3.i, 12, 4, false, false, false);
    if (z)
    {
        goto L11;
    }
    counters[20] ++;
    tmp = ip.i - 5;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) 5);
    v = (ip.i&0x80000000) != (5&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    store_counter ++;
    str(&r1.i, &r3.i, 16, 4, false, false, false);
    store_counter ++;
    if (!z)
    {
        str(&r1.i, &r3.i, 20, 4, false, false, false);
    }
L11:
    counters[21] ++;
    r3.i = r6.i + r9.i;
    r2.i = 0;
    store_counter ++;
    str(&r2.i, &r8.i, 0, 4, false, true, false);
L14:
    counters[22] ++;
    r0.i = r0.i + 1;
    tmp = r0.i - fp.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) fp.i);
    v = (r0.i&0x80000000) != (fp.i&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (n != v)
    {
        goto L12;
    }
    counters[23] ++;
    load_counter ++;
    ldr(&r7.i, &sp.i, 4, 4, false, false, false);
L7:
    counters[24] ++;
    r0.i = r7.i;
    sp.i = sp.i + 12;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false, false);
    ldr(&r7.i, &sp.i, 3*4, 4, false, false, false);
    ldr(&r8.i, &sp.i, 4*4, 4, false, false, false);
    ldr(&r9.i, &sp.i, 5*4, 4, false, false, false);
    ldr(&r10.i, &sp.i, 6*4, 4, false, false, false);
    ldr(&fp.i, &sp.i, 7*4, 4, false, false, false);
    ldr(&lr.i, &sp.i, 8*4, 4, false, false, false);
    sp.i += 36;
    free_help();
    return;
L2:
    counters[25] ++;
    r0.i = 4;
    malloc_help();
    counters[26] ++;
    tmp = r6.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) 1);
    v = (r6.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    r3.i = 0;
    r7.i = r0.i;
    store_counter ++;
    str(&r3.i, &r0.i, 0, 4, false, true, false);
    if (!z)
    {
        r3.i = 1;
    }
    if (!z)
    {
        r9.i = r3.i;
    }
    if (!z)
    {
        goto L6;
    }
L18:
    counters[27] ++;
    r9.i = r6.i;
    goto L15;
    return;
}

void main()
{
    malloc_start();
    counters[28] ++;
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
    counters[29] ++;
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
    r4.i = r7.i - 4;
    store_counter ++;
    str(&r2.i, &r7.i, 12, 4, false, false, false);
    r6.i = r7.i + 20;
    store_counter ++;
    str(&r3.i, &r7.i, 16, 4, false, false, false);
    printf(malloc_0+r1.i, r2.i);
    counters[30] ++;
    r5.i = r4.i;
L41:
    counters[31] ++;
    load_counter ++;
    ldr(&r2.i, &r5.i, 4, 4, true, false, false);
    r1.i = r8.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[32] ++;
    tmp = r5.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r6.i);
    v = (r5.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (!z)
    {
        goto L41;
    }
    counters[33] ++;
    r1.i = 6;
    r0.i = r7.i;
    pigeonholeSort();
    counters[34] ++;
    r1.i = (LC2 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC2 >> 16) << 16);
    printf(malloc_0+r1.i, r2.i);
    counters[35] ++;
    r5.i = (LC1 & 0xffff);
    r5.i = r5.i | (((uint32_t)LC1 >> 16) << 16);
L42:
    counters[36] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 4, 4, true, false, false);
    r1.i = r5.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[37] ++;
    tmp = r6.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) r4.i);
    v = (r6.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    if (!z)
    {
        goto L42;
    }
    counters[38] ++;
    r0.i = 10;
    printf("%c", (char)r0.i);
    counters[39] ++;
    r0.i = r7.i;
    free_help();
    counters[40] ++;
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

