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

int32_t LC0, LC1;

int counters[67] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[67] = {3,4,4,2,3,5,8,6,6,8,1,3,2,1,5,6,1,7,1,3,4,5,5,3,6,3,6,3,6,3,6,3,6,3,4,3,1,2,4,2,4,2,2,2,2,2,4,2,3,2,3,2,3,2,3,2,3,2,3,2,3,2,1,3,1,1,2};


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

    int32_t malloc_total = (int32_t) ((uint8_t*) malloc(21) - malloc_0);
    LC0 = malloc_total;
    strcpy(malloc_0+LC0, "%d \000");

    LC1 = malloc_total + 9;
    strcpy(malloc_0+LC1, "%d\012\000");

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "bubble_sort.c";

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
void bubbleSort();
void test();
void main();

void srand_help()
{
    srand(r0.i);
}
void calloc_help()
{
    uint8_t* ptr = (uint8_t*) calloc(r0.i, r1.i);
    r0.i = (int32_t) (ptr - malloc_0);
}
void rand_help()
{
    r0.i = rand();
}
void free_help()
{
    free(malloc_0+r0.i);
}
void time_help()
{
    r0.i = time(NULL);
}
void smull(int32_t *dest_lo, int32_t *dest_hi, int32_t *op1, int32_t *op2)
{
    uint64_t res = (uint64_t) (*op1) * (*op2);
    *dest_lo = (uint32_t) res;
    *dest_hi = (uint32_t) (res >> 32);
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

void bubbleSort()
{
    counters[6] ++;
    store_counter ++;
    sp.i -= 16;
    str(&r4.i, &sp.i, 0*4, 4, false, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false, false);
    str(&lr.i, &sp.i, 3*4, 4, false, false, false);
    r6.i = r1.i - 1;
    tmp = r6.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) 0);
    v = (r6.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    load_counter ++;
    if (z || n != v)
    {
        ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
        ldr(&r5.i, &sp.i, 1*4, 4, false, false, false);
        ldr(&r6.i, &sp.i, 2*4, 4, false, false, false);
        ldr(&pc.i, &sp.i, 3*4, 4, false, false, false);
        sp.i += 16;
        return;
    }
    r5.i = 0;
    lr.i = r6.i;
    r2.i = r5.i;
    r4.i = r5.i;
L9:
    counters[7] ++;
    r3.i = (uint32_t)r2.i << 2;
    load_counter ++;
    ldr(&r1.i, &r0.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    r3.i = r3.i + 4;
    load_counter ++;
    ldr(&ip.i, &r0.i, r3.i, 4, false, false, false);
    tmp = r1.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) ip.i);
    v = (r1.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (z || n != v)
    {
        goto L10;
    }
    counters[8] ++;
    store_counter ++;
    str(&ip.i, &r0.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    r2.i = r2.i + 1;
    tmp = lr.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) r2.i);
    v = (lr.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    r4.i = 1;
    store_counter ++;
    str(&r1.i, &r0.i, r3.i, 4, false, false, false);
    if (!z && n == v)
    {
        goto L9;
    }
L12:
    counters[9] ++;
    r5.i = r5.i + 1;
    r2.i = 0;
    tmp = r5.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r6.i);
    v = (r5.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    lr.i = r6.i - r5.i;
    r4.i = r2.i;
    load_counter ++;
    if (n == v)
    {
        ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
        ldr(&r5.i, &sp.i, 1*4, 4, false, false, false);
        ldr(&r6.i, &sp.i, 2*4, 4, false, false, false);
        ldr(&pc.i, &sp.i, 3*4, 4, false, false, false);
        sp.i += 16;
        return;
    }
    tmp = lr.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) r2.i);
    v = (lr.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    if (!z && n == v)
    {
        goto L9;
    }
    counters[10] ++;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false, false);
    ldr(&pc.i, &sp.i, 3*4, 4, false, false, false);
    sp.i += 16;
    return;
L10:
    counters[11] ++;
    r2.i = r2.i + 1;
    tmp = r2.i - lr.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) lr.i);
    v = (r2.i&0x80000000) != (lr.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n != v)
    {
        goto L9;
    }
    counters[12] ++;
    tmp = r4.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 0);
    v = (r4.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        goto L12;
    }
    counters[13] ++;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false, false);
    ldr(&pc.i, &sp.i, 3*4, 4, false, false, false);
    sp.i += 16;
    return;

}

void test()
{
    counters[14] ++;
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
    r1.i = 4;
    r0.i = 10;
    r7.i = 34079;
    calloc_help();
    counters[15] ++;
    r7.i = r7.i | (20971 << 16);
    r8.i = 100;
    r5.i = r0.i - 4;
    r6.i = r0.i + 36;
    r4.i = r0.i;
    r9.i = r5.i;
L22:
    counters[16] ++;
    rand_help();
    counters[17] ++;
    smull(&r3.i, &r2.i, &r7.i, &r0.i);
    r3.i = r0.i >> 31;
    r3.i = (r2.i >> 5) - r3.i;
    r0.i = r0.i - (r8.i * r3.i);
    z = r0.i == 0;
    n = r0.i & 0x80000000;
    store_counter ++;
    str(&r0.i, &r9.i, 4, 4, true, false, false);
    tmp = r9.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r9.i) >= ((uint32_t) r6.i);
    v = (r9.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r9.i&0x80000000);
    if (!z)
    {
        goto L22;
    }
    counters[18] ++;
    r3.i = 9;
L23:
    counters[19] ++;
    load_counter ++;
    ldr(&r1.i, &r4.i, 0*4, 4, false, false, false);
    ldr(&r2.i, &r4.i, 1*4, 4, false, false, false);
    tmp = r1.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r2.i);
    v = (r1.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (z || n != v)
    {
        goto L27;
    }
L89:
    counters[20] ++;
    tmp = r3.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 1);
    v = (r3.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    store_counter ++;
    str(&r2.i, &r4.i, 0, 4, false, true, false);
    store_counter ++;
    str(&r1.i, &r4.i, 4, 4, false, false, false);
    if (z)
    {
        goto L28;
    }
    counters[21] ++;
    r2.i = r1.i;
    load_counter ++;
    ldr(&r1.i, &r4.i, 8, 4, false, false, false);
    r0.i = 1;
    tmp = r2.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r1.i);
    v = (r2.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (z || n != v)
    {
        goto L29;
    }
L90:
    counters[22] ++;
    tmp = r3.i - 2;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 2);
    v = (r3.i&0x80000000) != (2&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    store_counter ++;
    if (!z)
    {
        r0.i = 1;
    }
    if (!z)
    {
        r1.i = r2.i;
    }
    if (z)
    {
        goto L31;
    }
L30:
    counters[23] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 12, 4, false, false, false);
    tmp = r1.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r2.i);
    v = (r1.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (z || n != v)
    {
        goto L32;
    }
    counters[24] ++;
    tmp = r3.i - 3;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 3);
    v = (r3.i&0x80000000) != (3&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    store_counter ++;
    str(&r2.i, &r4.i, 8, 4, false, false, false);
    store_counter ++;
    str(&r1.i, &r4.i, 12, 4, false, false, false);
    if (!z)
    {
        r2.i = r1.i;
    }
    if (!z)
    {
        r0.i = 1;
    }
    if (z)
    {
        goto L31;
    }
    counters[25] ++;
    load_counter ++;
    ldr(&r1.i, &r4.i, 16, 4, false, false, false);
    tmp = r2.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r1.i);
    v = (r2.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (z || n != v)
    {
        goto L34;
    }
L91:
    counters[26] ++;
    tmp = r3.i - 4;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 4);
    v = (r3.i&0x80000000) != (4&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    store_counter ++;
    str(&r1.i, &r4.i, 12, 4, false, false, false);
    store_counter ++;
    str(&r2.i, &r4.i, 16, 4, false, false, false);
    if (!z)
    {
        r1.i = r2.i;
    }
    if (!z)
    {
        r0.i = 1;
    }
    if (z)
    {
        goto L31;
    }
    counters[27] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 20, 4, false, false, false);
    tmp = r1.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r2.i);
    v = (r1.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (z || n != v)
    {
        goto L36;
    }
L92:
    counters[28] ++;
    tmp = r3.i - 5;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 5);
    v = (r3.i&0x80000000) != (5&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    store_counter ++;
    str(&r2.i, &r4.i, 16, 4, false, false, false);
    store_counter ++;
    str(&r1.i, &r4.i, 20, 4, false, false, false);
    if (!z)
    {
        r2.i = r1.i;
    }
    if (!z)
    {
        r0.i = 1;
    }
    if (z)
    {
        goto L31;
    }
    counters[29] ++;
    load_counter ++;
    ldr(&r1.i, &r4.i, 24, 4, false, false, false);
    tmp = r2.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r1.i);
    v = (r2.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (z || n != v)
    {
        goto L38;
    }
L93:
    counters[30] ++;
    tmp = r3.i - 6;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 6);
    v = (r3.i&0x80000000) != (6&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    store_counter ++;
    str(&r1.i, &r4.i, 20, 4, false, false, false);
    store_counter ++;
    str(&r2.i, &r4.i, 24, 4, false, false, false);
    if (!z)
    {
        r1.i = r2.i;
    }
    if (!z)
    {
        r0.i = 1;
    }
    if (z)
    {
        goto L31;
    }
    counters[31] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 28, 4, false, false, false);
    tmp = r1.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r2.i);
    v = (r1.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (z || n != v)
    {
        goto L40;
    }
L94:
    counters[32] ++;
    tmp = r3.i - 7;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 7);
    v = (r3.i&0x80000000) != (7&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    store_counter ++;
    str(&r2.i, &r4.i, 24, 4, false, false, false);
    store_counter ++;
    str(&r1.i, &r4.i, 28, 4, false, false, false);
    if (!z)
    {
        r2.i = r1.i;
    }
    if (!z)
    {
        r0.i = 1;
    }
    if (z)
    {
        goto L31;
    }
    counters[33] ++;
    load_counter ++;
    ldr(&r1.i, &r4.i, 32, 4, false, false, false);
    tmp = r2.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r1.i);
    v = (r2.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (z || n != v)
    {
        goto L42;
    }
L95:
    counters[34] ++;
    tmp = r3.i - 9;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 9);
    v = (r3.i&0x80000000) != (9&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    store_counter ++;
    str(&r1.i, &r4.i, 28, 4, false, false, false);
    store_counter ++;
    str(&r2.i, &r4.i, 32, 4, false, false, false);
    if (!z)
    {
        goto L28;
    }
    counters[35] ++;
    load_counter ++;
    ldr(&ip.i, &r4.i, 36, 4, false, false, false);
    tmp = ip.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r2.i);
    v = (ip.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (n == v)
    {
        goto L25;
    }
    counters[36] ++;
    r1.i = r2.i;
L43:
    counters[37] ++;
    store_counter ++;
    str(&ip.i, &r4.i, 32, 4, false, false, false);
    store_counter ++;
    str(&r1.i, &r6.i, 0, 4, false, true, false);
L25:
    counters[38] ++;
    load_counter ++;
    ldr(&r1.i, &r4.i, 0*4, 4, false, false, false);
    ldr(&r2.i, &r4.i, 1*4, 4, false, false, false);
    r3.i = 8;
    tmp = r1.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r2.i);
    v = (r1.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!z && n == v)
    {
        goto L89;
    }
L27:
    counters[39] ++;
    tmp = r3.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 1);
    v = (r3.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L26;
    }
    counters[40] ++;
    load_counter ++;
    ldr(&r1.i, &r4.i, 8, 4, false, false, false);
    r0.i = 0;
    tmp = r2.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r1.i);
    v = (r2.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z && n == v)
    {
        goto L90;
    }
L29:
    counters[41] ++;
    tmp = r3.i - 2;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 2);
    v = (r3.i&0x80000000) != (2&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L30;
    }
L24:
    counters[42] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (z)
    {
        goto L26;
    }
L31:
    counters[43] ++;
    r3.i = r3.i - 1;
    goto L23;
L28:
    counters[44] ++;
    r3.i = r3.i - 1;
    z = r3.i == 0;
    n = r3.i & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 1);
    v = (r3.i&0x80000000) != (1&0x80000000) && (r3.i&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L23;
    }
L26:
    counters[45] ++;
    r7.i = (LC1 & 0xffff);
    r7.i = r7.i | (((uint32_t)LC1 >> 16) << 16);
L45:
    counters[46] ++;
    load_counter ++;
    ldr(&r2.i, &r5.i, 4, 4, true, false, false);
    r1.i = r7.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[47] ++;
    tmp = r5.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r6.i);
    v = (r5.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (!z)
    {
        goto L45;
    }
    counters[48] ++;
    r0.i = r4.i;
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
L32:
    counters[49] ++;
    tmp = r3.i - 3;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 3);
    v = (r3.i&0x80000000) != (3&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L24;
    }
    counters[50] ++;
    load_counter ++;
    ldr(&r1.i, &r4.i, 16, 4, false, false, false);
    tmp = r2.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r1.i);
    v = (r2.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z && n == v)
    {
        goto L91;
    }
L34:
    counters[51] ++;
    tmp = r3.i - 4;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 4);
    v = (r3.i&0x80000000) != (4&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L24;
    }
    counters[52] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 20, 4, false, false, false);
    tmp = r1.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r2.i);
    v = (r1.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!z && n == v)
    {
        goto L92;
    }
L36:
    counters[53] ++;
    tmp = r3.i - 5;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 5);
    v = (r3.i&0x80000000) != (5&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L24;
    }
    counters[54] ++;
    load_counter ++;
    ldr(&r1.i, &r4.i, 24, 4, false, false, false);
    tmp = r2.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r1.i);
    v = (r2.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z && n == v)
    {
        goto L93;
    }
L38:
    counters[55] ++;
    tmp = r3.i - 6;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 6);
    v = (r3.i&0x80000000) != (6&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L24;
    }
    counters[56] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 28, 4, false, false, false);
    tmp = r1.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r2.i);
    v = (r1.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!z && n == v)
    {
        goto L94;
    }
L40:
    counters[57] ++;
    tmp = r3.i - 7;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 7);
    v = (r3.i&0x80000000) != (7&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L24;
    }
    counters[58] ++;
    load_counter ++;
    ldr(&r1.i, &r4.i, 32, 4, false, false, false);
    tmp = r2.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r1.i);
    v = (r2.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z && n == v)
    {
        goto L95;
    }
L42:
    counters[59] ++;
    tmp = r3.i - 9;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 9);
    v = (r3.i&0x80000000) != (9&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L24;
    }
    counters[60] ++;
    load_counter ++;
    ldr(&ip.i, &r4.i, 36, 4, false, false, false);
    tmp = ip.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r1.i);
    v = (ip.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (n != v)
    {
        goto L43;
    }
    counters[61] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        goto L31;
    }
    counters[62] ++;
    goto L26;
    return;
}

void main()
{
    malloc_start();
    counters[63] ++;
    store_counter ++;
    sp.i -= 8;
    str(&r4.i, &sp.i, 0*4, 4, false, false, false);
    str(&lr.i, &sp.i, 1*4, 4, false, false, false);
    r0.i = 0;
    time_help();
    counters[64] ++;
    srand_help();
    counters[65] ++;
    test();
    counters[66] ++;
    r0.i = 0;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
    ldr(&pc.i, &sp.i, 1*4, 4, false, false, false);
    sp.i += 8;
    counter_summary();
    return;

}

