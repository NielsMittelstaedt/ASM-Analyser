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

reg r3, r6, r0, r4, r1, r2, r5, r8, r7, r9;

int32_t LC0, LC1, LC2;

int counters[36] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[36] = {2,4,8,1,2,5,7,1,2,2,2,5,9,4,2,1,5,8,2,9,3,1,3,4,4,2,3,7,1,7,4,3,3,4,3,3};


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
    char filename[] = "pancake_sort.c";

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

void flip();
void findMax();
void pancakeSort();
void display();
void main();

void rand_help()
{
    r0.i = rand();
}
void smull(int32_t *dest_lo, int32_t *dest_hi, int32_t *op1, int32_t *op2)
{
    uint64_t res = (uint64_t) (*op1) * (*op2);
    *dest_lo = (uint32_t) res;
    *dest_hi = (uint32_t) (res >> 32);
}

void flip()
{
    counters[0] ++;
    tmp = r1.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 0);
    v = (r1.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (z || n != v)
    {
        return;
    }
    counters[1] ++;
    r2.i = r0.i - 4;
    r0.i = r0.i + ((uint32_t)r1.i << 2);
    r3.i = 0;
    store_counter ++;
    sp.i -= 8;
    str(&r4.i, &sp.i, 0*4, 4, false, false, false);
    str(&lr.i, &sp.i, 1*4, 4, false, false, false);
L3:
    counters[2] ++;
    r3.i = r3.i + 1;
    load_counter ++;
    ldr(&ip.i, &r2.i, 4, 4, true, false, false);
    r4.i = r1.i - r3.i;
    load_counter ++;
    ldr(&lr.i, &r0.i, 0, 4, false, true, false);
    tmp = r3.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r4.i);
    v = (r3.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    store_counter ++;
    str(&lr.i, &r2.i, 0, 4, false, true, false);
    store_counter ++;
    str(&ip.i, &r0.i, -4, 4, false, true, false);
    if (n != v)
    {
        goto L3;
    }
    counters[3] ++;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
    ldr(&pc.i, &sp.i, 1*4, 4, false, false, false);
    sp.i += 8;
    return;

}

void findMax()
{
    counters[4] ++;
    tmp = r1.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 0);
    v = (r1.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (z || n != v)
    {
        goto L14;
    }
    counters[5] ++;
    store_counter ++;
    str(&lr.i, &sp.i, -4, 4, true, false, false);
    lr.i = r0.i;
    load_counter ++;
    ldr(&r2.i, &lr.i, -4, 4, false, true, false);
    r3.i = 0;
    r0.i = r3.i;
L13:
    counters[6] ++;
    load_counter ++;
    ldr(&ip.i, &lr.i, 4, 4, true, false, false);
    tmp = r2.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) ip.i);
    v = (r2.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n != v)
    {
        r0.i = r3.i;
    }
    r3.i = r3.i + 1;
    if (n != v)
    {
        r2.i = ip.i;
    }
    tmp = r3.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r1.i);
    v = (r3.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L13;
    }
    counters[7] ++;
    load_counter ++;
    ldr(&pc.i, &sp.i, 4, 4, false, true, false);
L14:
    counters[8] ++;
    r0.i = 0;
    return;

}

void pancakeSort()
{
    counters[9] ++;
    tmp = r1.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 1);
    v = (r1.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (z || n != v)
    {
        return;
    }
    counters[10] ++;
    store_counter ++;
    sp.i -= 28;
    str(&r4.i, &sp.i, 0*4, 4, false, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false, false);
    str(&r7.i, &sp.i, 3*4, 4, false, false, false);
    str(&r8.i, &sp.i, 4*4, 4, false, false, false);
    str(&r9.i, &sp.i, 5*4, 4, false, false, false);
    str(&lr.i, &sp.i, 6*4, 4, false, false, false);
    r7.i = r0.i - 4;
L22:
    counters[11] ++;
    load_counter ++;
    ldr(&ip.i, &r0.i, 0, 4, false, true, false);
    r2.i = 0;
    r3.i = r2.i;
    r6.i = r7.i;
    r5.i = r7.i;
L24:
    counters[12] ++;
    load_counter ++;
    ldr(&lr.i, &r5.i, 4, 4, true, false, false);
    tmp = lr.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) ip.i);
    v = (lr.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    if (!z && n == v)
    {
        r4.i = r3.i;
    }
    r3.i = r3.i + 1;
    if (z || n != v)
    {
        r4.i = r2.i;
    }
    if (!z && n == v)
    {
        ip.i = lr.i;
    }
    tmp = r3.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r1.i);
    v = (r3.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    r2.i = r4.i;
    if (n != v)
    {
        goto L24;
    }
    counters[13] ++;
    lr.i = r1.i - 1;
    tmp = lr.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) r4.i);
    v = (lr.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    if (z)
    {
        r1.i = r4.i;
    }
    if (!z)
    {
        goto L41;
    }
    counters[14] ++;
    tmp = r1.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 1);
    v = (r1.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!z && n == v)
    {
        goto L22;
    }
    counters[15] ++;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false, false);
    ldr(&r7.i, &sp.i, 3*4, 4, false, false, false);
    ldr(&r8.i, &sp.i, 4*4, 4, false, false, false);
    ldr(&r9.i, &sp.i, 5*4, 4, false, false, false);
    ldr(&pc.i, &sp.i, 6*4, 4, false, false, false);
    sp.i += 28;
    return;
L41:
    counters[16] ++;
    tmp = r4.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 0);
    v = (r4.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z && n == v)
    {
        r2.i = r0.i + ((uint32_t)r4.i << 2);
    }
    if (!z && n == v)
    {
        ip.i = r7.i;
    }
    if (!z && n == v)
    {
        r3.i = 0;
    }
    if (z || n != v)
    {
        goto L29;
    }
L28:
    counters[17] ++;
    r3.i = r3.i + 1;
    load_counter ++;
    ldr(&r5.i, &ip.i, 4, 4, true, false, false);
    load_counter ++;
    ldr(&r8.i, &r2.i, 0, 4, false, true, false);
    r9.i = r4.i - r3.i;
    tmp = r3.i - r9.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r9.i);
    v = (r3.i&0x80000000) != (r9.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    store_counter ++;
    str(&r8.i, &ip.i, 0, 4, false, true, false);
    store_counter ++;
    str(&r5.i, &r2.i, -4, 4, false, true, false);
    if (n != v)
    {
        goto L28;
    }
L29:
    counters[18] ++;
    ip.i = r0.i + ((uint32_t)r1.i << 2);
    r3.i = 0;
L27:
    counters[19] ++;
    r3.i = r3.i + 1;
    load_counter ++;
    ldr(&r4.i, &r6.i, 4, 4, true, false, false);
    load_counter ++;
    ldr(&r5.i, &ip.i, -4, 4, true, false, false);
    r2.i = ~r3.i;
    r2.i = r2.i + r1.i;
    tmp = r3.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r2.i);
    v = (r3.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    store_counter ++;
    str(&r5.i, &r6.i, 0, 4, false, true, false);
    store_counter ++;
    str(&r4.i, &ip.i, 0, 4, false, true, false);
    if (n != v)
    {
        goto L27;
    }
    counters[20] ++;
    r1.i = lr.i;
    tmp = r1.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 1);
    v = (r1.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!z && n == v)
    {
        goto L22;
    }
    counters[21] ++;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false, false);
    ldr(&r7.i, &sp.i, 3*4, 4, false, false, false);
    ldr(&r8.i, &sp.i, 4*4, 4, false, false, false);
    ldr(&r9.i, &sp.i, 5*4, 4, false, false, false);
    ldr(&pc.i, &sp.i, 6*4, 4, false, false, false);
    sp.i += 28;
    return;

}

void display()
{
    counters[22] ++;
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
        goto L43;
    }
    counters[23] ++;
    r6.i = (LC0 & 0xffff);
    r5.i = r0.i + ((uint32_t)r5.i << 2);
    r6.i = r6.i | (((uint32_t)LC0 >> 16) << 16);
    r4.i = r0.i;
L44:
    counters[24] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 4, 4, false, true, false);
    r1.i = r6.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[25] ++;
    tmp = r5.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r4.i);
    v = (r5.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (!z)
    {
        goto L44;
    }
L43:
    counters[26] ++;
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

void main()
{
    malloc_start();
    counters[27] ++;
    store_counter ++;
    sp.i -= 20;
    str(&r4.i, &sp.i, 0*4, 4, false, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false, false);
    str(&r7.i, &sp.i, 3*4, 4, false, false, false);
    str(&lr.i, &sp.i, 4*4, 4, false, false, false);
    sp.i = sp.i - 204;
    r4.i = 34079;
    r7.i = sp.i - 4;
    r4.i = r4.i | (20971 << 16);
    r6.i = sp.i + 196;
    r5.i = 100;
L48:
    counters[28] ++;
    rand_help();
    counters[29] ++;
    smull(&r3.i, &r2.i, &r4.i, &r0.i);
    r3.i = r0.i >> 31;
    r3.i = (r2.i >> 5) - r3.i;
    r0.i = r0.i - (r5.i * r3.i);
    z = r0.i == 0;
    n = r0.i & 0x80000000;
    store_counter ++;
    str(&r0.i, &r7.i, 4, 4, true, false, false);
    tmp = r7.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r7.i) >= ((uint32_t) r6.i);
    v = (r7.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
    if (!z)
    {
        goto L48;
    }
    counters[30] ++;
    r1.i = (LC1 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC1 >> 16) << 16);
    printf(malloc_0+r1.i, r2.i);
    counters[31] ++;
    r0.i = sp.i;
    r1.i = 50;
    display();
    counters[32] ++;
    r0.i = sp.i;
    r1.i = 50;
    pancakeSort();
    counters[33] ++;
    r1.i = (LC2 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC2 >> 16) << 16);
    printf(malloc_0+r1.i, r2.i);
    counters[34] ++;
    r0.i = sp.i;
    r1.i = 50;
    display();
    counters[35] ++;
    r0.i = 0;
    sp.i = sp.i + 204;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false, false);
    ldr(&r7.i, &sp.i, 3*4, 4, false, false, false);
    ldr(&pc.i, &sp.i, 4*4, 4, false, false, false);
    sp.i += 20;
    counter_summary();
    return;

}

