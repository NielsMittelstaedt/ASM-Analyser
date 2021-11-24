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

int32_t LC0, LC1, __PRETTY_FUNCTION__5585;

int counters[25] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[25] = {5,2,4,4,5,9,3,3,1,3,2,2,8,3,5,1,8,3,2,3,4,2,2,2,8};


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

    int32_t malloc_total = (int32_t) ((uint8_t*) malloc(77) - malloc_0);
    LC0 = malloc_total;
    strcpy(malloc_0+LC0, "../test_files/c_in/selection_sort.c\000");

    LC1 = malloc_total + 41;
    strcpy(malloc_0+LC1, "arr[i] <= arr[i + 1]\000");

    __PRETTY_FUNCTION__5585 = malloc_total + 67;
    strcpy(malloc_0+__PRETTY_FUNCTION__5585, "test\000");

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "selection_sort.c";

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
void selectionSort();
void main();

void assert_help()
{
    __assert_fail(malloc_0+r0.i, malloc_0+r1.i, r2.i, malloc_0+r3.i);
}
void smull(int32_t *dest_lo, int32_t *dest_hi, int32_t *op1, int32_t *op2)
{
    uint64_t res = (uint64_t) (*op1) * (*op2);
    *dest_lo = (uint32_t) res;
    *dest_hi = (uint32_t) (res >> 32);
}
void time_help()
{
    r0.i = time(NULL);
}
void free_help()
{
    free(malloc_0+r0.i);
}
void calloc_help()
{
    uint8_t* ptr = (uint8_t*) calloc(r0.i, r1.i);
    r0.i = (int32_t) (ptr - malloc_0);
}
void srand_help()
{
    srand(r0.i);
}
void rand_help()
{
    r0.i = rand();
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

void selectionSort()
{
    counters[1] ++;
    tmp = r1.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 1);
    v = (r1.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (z || n != v)
    {
        return;
    }
    counters[2] ++;
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
    r7.i = r0.i + (4);
    r10.i = r1.i - (1);
    r6.i = 0;
L8:
    counters[3] ++;
    r8.i = r6.i;
    r6.i = r6.i + (1);
    tmp = r1.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r6.i);
    v = (r1.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (z || n != v)
    {
        goto L5;
    }
    counters[4] ++;
    load_counter ++;
    ldr(&r9.i, &r7.i, -4, 4, false, false, false);
    r2.i = r7.i;
    r3.i = r6.i;
    r5.i = r8.i;
    lr.i = r9.i;
L7:
    counters[5] ++;
    r4.i = r2.i;
    load_counter ++;
    ldr(&ip.i, &r2.i, 4, 4, false, true, false);
    tmp = ip.i - lr.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) lr.i);
    v = (ip.i&0x80000000) != (lr.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (n == v)
    {
        r4.i = r0.i + (((uint32_t)r5.i << 2));
    }
    if (n != v)
    {
        r5.i = r3.i;
    }
    r3.i = r3.i + (1);
    if (n != v)
    {
        lr.i = ip.i;
    }
    tmp = r3.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r1.i);
    v = (r3.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L7;
    }
    counters[6] ++;
    tmp = r8.i - r5.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) r5.i);
    v = (r8.i&0x80000000) != (r5.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    store_counter ++;
    if (!z)
    {
        str(&lr.i, &r7.i, -4, 4, false, false, false);
    }
    store_counter ++;
    if (!z)
    {
        str(&r9.i, &r4.i, 0, 4, false, true, false);
    }
L5:
    counters[7] ++;
    tmp = r6.i - r10.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) r10.i);
    v = (r6.i&0x80000000) != (r10.i&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    r7.i = r7.i + (4);
    if (!z)
    {
        goto L8;
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
    counters[9] ++;
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
    r0.i = 0;
    time_help();
    counters[10] ++;
    r4.i = 19923;
    srand_help();
    counters[11] ++;
    r4.i = r4.i | (4194 << 16);
    rand_help();
    counters[12] ++;
    r3.i = 500;
    r1.i = 4;
    smull(&r2.i, &r4.i, &r4.i, &r0.i);
    r2.i = r0.i >> 31;
    r4.i = (r4.i >> 5) - r2.i;
    r4.i = r0.i - ((r3.i) * (r4.i));
    z = r4.i == 0;
    n = r4.i & 0x80000000;
    r0.i = r4.i;
    calloc_help();
    counters[13] ++;
    tmp = r4.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 0);
    v = (r4.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    r5.i = r0.i;
    if (z || n != v)
    {
        goto L18;
    }
    counters[14] ++;
    r9.i = 34079;
    r7.i = r0.i + (((uint32_t)r4.i << 2));
    r9.i = r9.i | (20971 << 16);
    r8.i = r0.i;
    r6.i = 100;
L19:
    counters[15] ++;
    rand_help();
    counters[16] ++;
    smull(&r3.i, &r2.i, &r9.i, &r0.i);
    r3.i = r0.i >> 31;
    r3.i = (r2.i >> 5) - r3.i;
    r0.i = r0.i - ((r6.i) * (r3.i));
    z = r0.i == 0;
    n = r0.i & 0x80000000;
    r0.i = r0.i - (50);
    store_counter ++;
    str(&r0.i, &r8.i, 4, 4, false, true, false);
    tmp = r8.i - r7.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) r7.i);
    v = (r8.i&0x80000000) != (r7.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    if (!z)
    {
        goto L19;
    }
L18:
    counters[17] ++;
    r1.i = r4.i;
    r0.i = r5.i;
    selectionSort();
    counters[18] ++;
    tmp = r4.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 1);
    v = (r4.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (z || n != v)
    {
        goto L20;
    }
    counters[19] ++;
    r3.i = r5.i;
    r4.i = r5.i + (((uint32_t)r4.i << 2));
    load_counter ++;
    ldr(&r2.i, &r3.i, 4, 4, false, true, false);
L22:
    counters[20] ++;
    r1.i = r2.i;
    load_counter ++;
    ldr(&r2.i, &r3.i, 4, 4, false, true, false);
    tmp = r2.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r1.i);
    v = (r2.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n != v)
    {
        goto L26;
    }
    counters[21] ++;
    tmp = r4.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r3.i);
    v = (r4.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        goto L22;
    }
L20:
    counters[22] ++;
    r0.i = r5.i;
    free_help();
    counters[23] ++;
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
    ldr(&r9.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&r10.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;
L26:
    counters[24] ++;
    r3.i = (LC0 & 0xffff);
    r1.i = (LC0 & 0xffff);
    r0.i = (LC1 & 0xffff);
    r3.i = r3.i | (((uint32_t)LC0 >> 16) << 16);
    r1.i = r1.i | (((uint32_t)LC0 >> 16) << 16);
    r0.i = r0.i | (((uint32_t)LC1 >> 16) << 16);
    r2.i = 63;
    assert_help();
    counter_summary();
    return;
}

