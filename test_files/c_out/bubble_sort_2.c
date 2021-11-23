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

int32_t LC0, LC1, __PRETTY_FUNCTION__4927;

int counters[17] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[17] = {2,2,7,2,1,7,5,1,7,2,7,2,1,4,2,3,8};


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

    int32_t malloc_total = (int32_t) ((uint8_t*) malloc(88) - malloc_0);
    LC0 = malloc_total;
    strcpy(malloc_0+LC0, "../test_files/c_in/bubble_sort_2.c\000");

    LC1 = malloc_total + 40;
    strcpy(malloc_0+LC1, "array_sort[i] <= array_sort[i+1]\000");

    __PRETTY_FUNCTION__4927 = malloc_total + 78;
    strcpy(malloc_0+__PRETTY_FUNCTION__4927, "test\000");

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "bubble_sort_2.c";

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

void bubble_sort();
void main();

void rand_help()
{
    r0.i = rand();
}
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
void memset_help()
{
    memset(malloc_0+r0.i, r1.i, r2.i);
}

void bubble_sort()
{
    counters[0] ++;
    ip.i = r0.i + 76;
    store_counter ++;
    str(&lr.i, &sp.i, -4, 4, true, false, false);
L2:
    counters[1] ++;
    r3.i = r0.i;
    lr.i = 1;
L4:
    counters[2] ++;
    load_counter ++;
    ldr(&r2.i, &r3.i, 0, 4, false, true, false);
    load_counter ++;
    ldr(&r1.i, &r3.i, 4, 4, true, false, false);
    tmp = r2.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r1.i);
    v = (r2.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    store_counter ++;
    if (!z && n == v)
    {
    }
    if (!z && n == v)
    {
        lr.i = 0;
    }
    tmp = r3.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) ip.i);
    v = (r3.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L4;
    }
    counters[3] ++;
    tmp = lr.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) 0);
    v = (lr.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    if (z)
    {
        goto L2;
    }
    counters[4] ++;
    load_counter ++;
    ldr(&pc.i, &sp.i, 4, 4, false, true, false);
    return;
}

void main()
{
    malloc_start();
    counters[5] ++;
    store_counter ++;
    sp.i -= 24;
    str(&r4.i, &sp.i, 0*4, 4, false, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false, false);
    str(&r7.i, &sp.i, 3*4, 4, false, false, false);
    str(&r8.i, &sp.i, 4*4, 4, false, false, false);
    str(&lr.i, &sp.i, 5*4, 4, false, false, false);
    sp.i = sp.i - 80;
    r2.i = 80;
    r1.i = 0;
    r0.i = sp.i;
    r7.i = 61643;
    memset_help();
    counters[6] ++;
    r7.i = r7.i | (10381 << 16);
    r6.i = sp.i - 4;
    r5.i = sp.i + 76;
    r4.i = sp.i;
    r8.i = 101;
L12:
    counters[7] ++;
    rand_help();
    counters[8] ++;
    smull(&r3.i, &r2.i, &r7.i, &r0.i);
    r3.i = r0.i >> 31;
    r3.i = (r2.i >> 4) - r3.i;
    r0.i = r0.i - (r8.i * r3.i);
    z = r0.i == 0;
    n = r0.i & 0x80000000;
    store_counter ++;
    str(&r0.i, &r6.i, 4, 4, true, false, false);
    tmp = r6.i - r5.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) r5.i);
    v = (r6.i&0x80000000) != (r5.i&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    if (!z)
    {
        goto L12;
    }
L13:
    counters[9] ++;
    r3.i = sp.i;
    r2.i = 1;
L15:
    counters[10] ++;
    load_counter ++;
    ldr(&r1.i, &r3.i, 0, 4, false, true, false);
    load_counter ++;
    ldr(&r0.i, &r3.i, 4, 4, true, false, false);
    tmp = r1.i - r0.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r0.i);
    v = (r1.i&0x80000000) != (r0.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    store_counter ++;
    if (!z && n == v)
    {
        str(&r0.i, &r3.i, -4, 4, false, false, false);
        str(&r1.i, &r3.i, 00, 4, false, false, false);
    }
    if (!z && n == v)
    {
        r2.i = 0;
    }
    tmp = r3.i - r5.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r5.i);
    v = (r3.i&0x80000000) != (r5.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L15;
    }
    counters[11] ++;
    tmp = r2.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) 0);
    v = (r2.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (z)
    {
        goto L13;
    }
    counters[12] ++;
    load_counter ++;
    ldr(&r3.i, &sp.i, 0, 4, false, true, false);
L17:
    counters[13] ++;
    r2.i = r3.i;
    load_counter ++;
    ldr(&r3.i, &r4.i, 4, 4, true, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z && n == v)
    {
        goto L25;
    }
    counters[14] ++;
    tmp = r4.i - r5.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r5.i);
    v = (r4.i&0x80000000) != (r5.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        goto L17;
    }
    counters[15] ++;
    r0.i = 0;
    sp.i = sp.i + 80;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false, false);
    ldr(&r7.i, &sp.i, 3*4, 4, false, false, false);
    ldr(&r8.i, &sp.i, 4*4, 4, false, false, false);
    ldr(&pc.i, &sp.i, 5*4, 4, false, false, false);
    sp.i += 24;
    return;
L25:
    counters[16] ++;
    r3.i = (LC0 & 0xffff);
    r1.i = (LC0 & 0xffff);
    r0.i = (LC1 & 0xffff);
    r3.i = r3.i | (((uint32_t)LC0 >> 16) << 16);
    r1.i = r1.i | (((uint32_t)LC0 >> 16) << 16);
    r0.i = r0.i | (((uint32_t)LC1 >> 16) << 16);
    r2.i = 75;
    assert_help();
    counter_summary();
    return;
}

