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

int32_t LC0, LC1, __PRETTY_FUNCTION__5580;

int counters[24] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[24] = {2,4,3,5,4,1,4,1,3,2,2,8,3,5,1,8,3,2,3,4,2,2,2,8};


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
    strcpy(malloc_0+LC0, "../test_files/c_in/insertion_sort.c\000");

    LC1 = malloc_total + 41;
    strcpy(malloc_0+LC1, "arr[i] <= arr[i + 1]\000");

    __PRETTY_FUNCTION__5580 = malloc_total + 67;
    strcpy(malloc_0+__PRETTY_FUNCTION__5580, "test\000");

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "insertion_sort.c";

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

void insertionSort();
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

void insertionSort()
{
    counters[0] ++;
    tmp = r1.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 1);
    v = (r1.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (z || n != v)
    {
        return;
    }
    counters[1] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r6.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r4.i, &sp.i, 0, 4, false, false, false);
    r6.i = r1.i - (1);
    r5.i = r0.i;
    r4.i = 0;
L6:
    counters[2] ++;
    load_counter ++;
    ldr(&lr.i, &r5.i, 4, 4, true, false, false);
    r2.i = r4.i;
    r3.i = r5.i;
L3:
    counters[3] ++;
    load_counter ++;
    ldr(&r1.i, &r3.i, -4, 4, false, false, false);
    r2.i = r2.i - (1);
    ip.i = r3.i;
    tmp = r1.i - lr.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) lr.i);
    v = (r1.i&0x80000000) != (lr.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (z || n != v)
    {
        goto L4;
    }
    counters[4] ++;
    tmp = r2.i + 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) tmp) < ((uint32_t) r2.i);
    v = (r2.i&0x80000000) == (1&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    store_counter ++;
    str(&r1.i, &r3.i, 0, 4, false, true, false);
    r3.i = ip.i - (4);
    if (!z)
    {
        goto L3;
    }
    counters[5] ++;
    ip.i = r0.i;
L4:
    counters[6] ++;
    r4.i = r4.i + (1);
    store_counter ++;
    str(&lr.i, &ip.i, 0, 4, false, true, false);
    tmp = r6.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) r4.i);
    v = (r6.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    if (!z)
    {
        goto L6;
    }
    counters[7] ++;
    load_counter ++;
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

void main()
{
    malloc_start();
    counters[8] ++;
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
    counters[9] ++;
    r4.i = 19923;
    srand_help();
    counters[10] ++;
    r4.i = r4.i | (4194 << 16);
    rand_help();
    counters[11] ++;
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
    counters[12] ++;
    tmp = r4.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 0);
    v = (r4.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    r5.i = r0.i;
    if (z || n != v)
    {
        goto L17;
    }
    counters[13] ++;
    r9.i = 34079;
    r7.i = r0.i + (((uint32_t)r4.i << 2));
    r9.i = r9.i | (20971 << 16);
    r8.i = r0.i;
    r6.i = 100;
L18:
    counters[14] ++;
    rand_help();
    counters[15] ++;
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
        goto L18;
    }
L17:
    counters[16] ++;
    r1.i = r4.i;
    r0.i = r5.i;
    insertionSort();
    counters[17] ++;
    tmp = r4.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 1);
    v = (r4.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (z || n != v)
    {
        goto L19;
    }
    counters[18] ++;
    r3.i = r5.i;
    r4.i = r5.i + (((uint32_t)r4.i << 2));
    load_counter ++;
    ldr(&r2.i, &r3.i, 4, 4, false, true, false);
L21:
    counters[19] ++;
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
        goto L25;
    }
    counters[20] ++;
    tmp = r4.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r3.i);
    v = (r4.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        goto L21;
    }
L19:
    counters[21] ++;
    r0.i = r5.i;
    free_help();
    counters[22] ++;
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
L25:
    counters[23] ++;
    r3.i = (LC0 & 0xffff);
    r1.i = (LC0 & 0xffff);
    r0.i = (LC1 & 0xffff);
    r3.i = r3.i | (((uint32_t)LC0 >> 16) << 16);
    r1.i = r1.i | (((uint32_t)LC0 >> 16) << 16);
    r0.i = r0.i | (((uint32_t)LC1 >> 16) << 16);
    r2.i = 49;
    assert_help();
    counter_summary();
    return;
}

