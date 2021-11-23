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

int32_t LC0, LC1, __PRETTY_FUNCTION__5581;

int counters[61] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[61] = {5,5,5,8,5,1,5,5,1,7,3,3,4,5,6,3,6,3,6,3,6,3,6,3,6,3,6,5,5,2,3,3,3,3,3,3,3,3,3,2,4,2,3,2,3,2,3,2,3,2,3,2,3,2,1,2,8,3,1,1,2};


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

    int32_t malloc_total = (int32_t) ((uint8_t*) malloc(84) - malloc_0);
    LC0 = malloc_total;
    strcpy(malloc_0+LC0, "../test_files/c_in/bubble_sort_recursion.c\000");

    LC1 = malloc_total + 48;
    strcpy(malloc_0+LC1, "arr[i] <= arr[i + 1]\000");

    __PRETTY_FUNCTION__5581 = malloc_total + 74;
    strcpy(malloc_0+__PRETTY_FUNCTION__5581, "test\000");

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "bubble_sort_recursion.c";

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
void free_help()
{
    free(malloc_0+r0.i);
}
void rand_help()
{
    r0.i = rand();
}
void time_help()
{
    r0.i = time(NULL);
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

void bubbleSort()
{
    counters[1] ++;
    tmp = r1.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 1);
    v = (r1.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    store_counter ++;
    sp.i -= 8;
    str(&r4.i, &sp.i, 0*4, 4, false, false, false);
    str(&lr.i, &sp.i, 1*4, 4, false, false, false);
    lr.i = r0.i + ((uint32_t)r1.i << 2);
    lr.i = lr.i - 4;
    load_counter ++;
    if (z)
    {
        ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
        ldr(&pc.i, &sp.i, 1*4, 4, false, false, false);
        sp.i += 8;
        return;
    }
L15:
    counters[2] ++;
    r1.i = r1.i - 1;
    tmp = r1.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 0);
    v = (r1.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    load_counter ++;
    if (z || n != v)
    {
        ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
        ldr(&pc.i, &sp.i, 1*4, 4, false, false, false);
        sp.i += 8;
        return;
    }
    r3.i = r0.i;
    r4.i = 0;
L6:
    counters[3] ++;
    load_counter ++;
    ldr(&r2.i, &r3.i, 0, 4, false, true, false);
    load_counter ++;
    ldr(&ip.i, &r3.i, 4, 4, true, false, false);
    tmp = r2.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) ip.i);
    v = (r2.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    store_counter ++;
    if (!z && n == v)
    {
        str(&ip.i, &r3.i, -4, 4, false, false, false);
    }
    if (!z && n == v)
    {
        r4.i = 1;
    }
    store_counter ++;
    if (!z && n == v)
    {
        str(&r2.i, &r3.i, 0, 4, false, true, false);
    }
    tmp = lr.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) r3.i);
    v = (lr.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    if (!z)
    {
        goto L6;
    }
    counters[4] ++;
    tmp = r4.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 0);
    v = (r4.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    lr.i = lr.i - 4;
    load_counter ++;
    if (z)
    {
        ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
        ldr(&pc.i, &sp.i, 1*4, 4, false, false, false);
        sp.i += 8;
        return;
    }
    tmp = r1.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 1);
    v = (r1.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!z)
    {
        goto L15;
    }
    counters[5] ++;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
    ldr(&pc.i, &sp.i, 1*4, 4, false, false, false);
    sp.i += 8;
    return;

}

void test()
{
    counters[6] ++;
    store_counter ++;
    sp.i -= 24;
    str(&r4.i, &sp.i, 0*4, 4, false, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false, false);
    str(&r7.i, &sp.i, 3*4, 4, false, false, false);
    str(&r8.i, &sp.i, 4*4, 4, false, false, false);
    str(&lr.i, &sp.i, 5*4, 4, false, false, false);
    r1.i = 4;
    r0.i = 10;
    r5.i = 34079;
    calloc_help();
    counters[7] ++;
    r5.i = r5.i | (20971 << 16);
    r6.i = 100;
    r8.i = r0.i - 4;
    r7.i = r0.i + 36;
    r4.i = r0.i;
L17:
    counters[8] ++;
    rand_help();
    counters[9] ++;
    smull(&r3.i, &r2.i, &r5.i, &r0.i);
    r3.i = r0.i >> 31;
    r3.i = (r2.i >> 5) - r3.i;
    r0.i = r0.i - (r6.i * r3.i);
    z = r0.i == 0;
    n = r0.i & 0x80000000;
    store_counter ++;
    str(&r0.i, &r8.i, 4, 4, true, false, false);
    tmp = r8.i - r7.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) r7.i);
    v = (r8.i&0x80000000) != (r7.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    if (!z)
    {
        goto L17;
    }
    counters[10] ++;
    load_counter ++;
    ldr(&lr.i, &r4.i, 0, 4, false, true, false);
    r3.i = 10;
    load_counter ++;
    ldr(&r1.i, &r4.i, 4, 4, false, false, false);
L18:
    counters[11] ++;
    tmp = lr.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) r1.i);
    v = (lr.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    r3.i = r3.i - 1;
    if (z || n != v)
    {
        goto L20;
    }
    counters[12] ++;
    tmp = r3.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 1);
    v = (r3.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    store_counter ++;
    str(&r1.i, &r4.i, 0*4, 4, false, false, false);
    str(&lr.i, &r4.i, 1*4, 4, false, false, false);
    lr.i = r1.i;
    if (z)
    {
        goto L77;
    }
    counters[13] ++;
    load_counter ++;
    ldr(&r1.i, &r4.i, 4, 4, false, false, false);
    r2.i = 1;
    load_counter ++;
    ldr(&r0.i, &r4.i, 8, 4, false, false, false);
    tmp = r1.i - r0.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r0.i);
    v = (r1.i&0x80000000) != (r0.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (z || n != v)
    {
        goto L21;
    }
L78:
    counters[14] ++;
    tmp = r3.i - 2;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 2);
    v = (r3.i&0x80000000) != (2&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    store_counter ++;
    str(&r0.i, &r4.i, 4, 4, false, false, false);
    str(&r1.i, &r4.i, 8, 4, false, false, false);
    r1.i = r0.i;
    if (!z)
    {
        r2.i = 1;
    }
    load_counter ++;
    if (!z)
    {
        ldr(&r0.i, &r4.i, 8, 4, false, false, false);
    }
    if (z)
    {
        goto L18;
    }
    counters[15] ++;
    load_counter ++;
    ldr(&ip.i, &r4.i, 12, 4, false, false, false);
    tmp = r0.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) ip.i);
    v = (r0.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (z || n != v)
    {
        goto L25;
    }
L79:
    counters[16] ++;
    tmp = r3.i - 3;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 3);
    v = (r3.i&0x80000000) != (3&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    store_counter ++;
    str(&ip.i, &r4.i, 8, 4, false, false, false);
    store_counter ++;
    str(&r0.i, &r4.i, 12, 4, false, false, false);
    if (!z)
    {
        ip.i = r0.i;
    }
    if (!z)
    {
        r2.i = 1;
    }
    if (z)
    {
        goto L18;
    }
    counters[17] ++;
    load_counter ++;
    ldr(&r0.i, &r4.i, 16, 4, false, false, false);
    tmp = ip.i - r0.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r0.i);
    v = (ip.i&0x80000000) != (r0.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (z || n != v)
    {
        goto L27;
    }
L80:
    counters[18] ++;
    tmp = r3.i - 4;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 4);
    v = (r3.i&0x80000000) != (4&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    store_counter ++;
    str(&r0.i, &r4.i, 12, 4, false, false, false);
    store_counter ++;
    str(&ip.i, &r4.i, 16, 4, false, false, false);
    if (!z)
    {
        r0.i = ip.i;
    }
    if (!z)
    {
        r2.i = 1;
    }
    if (z)
    {
        goto L18;
    }
    counters[19] ++;
    load_counter ++;
    ldr(&ip.i, &r4.i, 20, 4, false, false, false);
    tmp = r0.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) ip.i);
    v = (r0.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (z || n != v)
    {
        goto L29;
    }
L81:
    counters[20] ++;
    tmp = r3.i - 5;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 5);
    v = (r3.i&0x80000000) != (5&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    store_counter ++;
    str(&ip.i, &r4.i, 16, 4, false, false, false);
    store_counter ++;
    str(&r0.i, &r4.i, 20, 4, false, false, false);
    if (!z)
    {
        ip.i = r0.i;
    }
    if (!z)
    {
        r2.i = 1;
    }
    if (z)
    {
        goto L18;
    }
    counters[21] ++;
    load_counter ++;
    ldr(&r0.i, &r4.i, 24, 4, false, false, false);
    tmp = ip.i - r0.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r0.i);
    v = (ip.i&0x80000000) != (r0.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (z || n != v)
    {
        goto L31;
    }
L82:
    counters[22] ++;
    tmp = r3.i - 6;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 6);
    v = (r3.i&0x80000000) != (6&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    store_counter ++;
    str(&r0.i, &r4.i, 20, 4, false, false, false);
    store_counter ++;
    str(&ip.i, &r4.i, 24, 4, false, false, false);
    if (!z)
    {
        r0.i = ip.i;
    }
    if (!z)
    {
        r2.i = 1;
    }
    if (z)
    {
        goto L18;
    }
    counters[23] ++;
    load_counter ++;
    ldr(&ip.i, &r4.i, 28, 4, false, false, false);
    tmp = r0.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) ip.i);
    v = (r0.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (z || n != v)
    {
        goto L33;
    }
L83:
    counters[24] ++;
    tmp = r3.i - 7;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 7);
    v = (r3.i&0x80000000) != (7&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    store_counter ++;
    str(&ip.i, &r4.i, 24, 4, false, false, false);
    store_counter ++;
    str(&r0.i, &r4.i, 28, 4, false, false, false);
    if (!z)
    {
        ip.i = r0.i;
    }
    if (!z)
    {
        r2.i = 1;
    }
    if (z)
    {
        goto L18;
    }
    counters[25] ++;
    load_counter ++;
    ldr(&r0.i, &r4.i, 32, 4, false, false, false);
    tmp = ip.i - r0.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r0.i);
    v = (ip.i&0x80000000) != (r0.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (z || n != v)
    {
        goto L35;
    }
L84:
    counters[26] ++;
    tmp = r3.i - 9;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 9);
    v = (r3.i&0x80000000) != (9&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    store_counter ++;
    str(&r0.i, &r4.i, 28, 4, false, false, false);
    store_counter ++;
    str(&ip.i, &r4.i, 32, 4, false, false, false);
    if (z)
    {
        r0.i = ip.i;
    }
    if (z)
    {
        r2.i = 1;
    }
    if (!z)
    {
        goto L18;
    }
L36:
    counters[27] ++;
    load_counter ++;
    ldr(&ip.i, &r4.i, 36, 4, false, false, false);
    tmp = r0.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) ip.i);
    v = (r0.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    store_counter ++;
    if (!z && n == v)
    {
        str(&r0.i, &r4.i, 36, 4, false, false, false);
    }
    store_counter ++;
    if (!z && n == v)
    {
        str(&ip.i, &r4.i, 32, 4, false, false, false);
    }
    if (!z && n == v)
    {
        goto L18;
    }
L24:
    counters[28] ++;
    r2.i = r2.i ^ 1;
    tmp = r3.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 1);
    v = (r3.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        r2.i = r2.i | 1;
    }
    tmp = r2.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) 0);
    v = (r2.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (z)
    {
        goto L18;
    }
L19:
    counters[29] ++;
    tmp = r1.i - lr.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) lr.i);
    v = (r1.i&0x80000000) != (lr.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (n != v)
    {
        goto L37;
    }
    counters[30] ++;
    load_counter ++;
    ldr(&r3.i, &r4.i, 8, 4, false, false, false);
    tmp = r1.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r3.i);
    v = (r1.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!z && n == v)
    {
        goto L37;
    }
    counters[31] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 12, 4, false, false, false);
    tmp = r3.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r2.i);
    v = (r3.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z && n == v)
    {
        goto L37;
    }
    counters[32] ++;
    load_counter ++;
    ldr(&r3.i, &r4.i, 16, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z && n == v)
    {
        goto L37;
    }
    counters[33] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 20, 4, false, false, false);
    tmp = r3.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r2.i);
    v = (r3.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z && n == v)
    {
        goto L37;
    }
    counters[34] ++;
    load_counter ++;
    ldr(&r3.i, &r4.i, 24, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z && n == v)
    {
        goto L37;
    }
    counters[35] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 28, 4, false, false, false);
    tmp = r3.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r2.i);
    v = (r3.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z && n == v)
    {
        goto L37;
    }
    counters[36] ++;
    load_counter ++;
    ldr(&r3.i, &r4.i, 32, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z && n == v)
    {
        goto L37;
    }
    counters[37] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 36, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n != v)
    {
        goto L37;
    }
    counters[38] ++;
    r0.i = r4.i;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false, false);
    ldr(&r7.i, &sp.i, 3*4, 4, false, false, false);
    ldr(&r8.i, &sp.i, 4*4, 4, false, false, false);
    ldr(&lr.i, &sp.i, 5*4, 4, false, false, false);
    sp.i += 24;
    free_help();
    return;
L20:
    counters[39] ++;
    tmp = r3.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 1);
    v = (r3.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L19;
    }
    counters[40] ++;
    load_counter ++;
    ldr(&r0.i, &r4.i, 8, 4, false, false, false);
    r2.i = 0;
    tmp = r1.i - r0.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r0.i);
    v = (r1.i&0x80000000) != (r0.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!z && n == v)
    {
        goto L78;
    }
L21:
    counters[41] ++;
    tmp = r3.i - 2;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 2);
    v = (r3.i&0x80000000) != (2&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L24;
    }
    counters[42] ++;
    load_counter ++;
    ldr(&ip.i, &r4.i, 12, 4, false, false, false);
    tmp = r0.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) ip.i);
    v = (r0.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z && n == v)
    {
        goto L79;
    }
L25:
    counters[43] ++;
    tmp = r3.i - 3;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 3);
    v = (r3.i&0x80000000) != (3&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L24;
    }
    counters[44] ++;
    load_counter ++;
    ldr(&r0.i, &r4.i, 16, 4, false, false, false);
    tmp = ip.i - r0.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r0.i);
    v = (ip.i&0x80000000) != (r0.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (!z && n == v)
    {
        goto L80;
    }
L27:
    counters[45] ++;
    tmp = r3.i - 4;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 4);
    v = (r3.i&0x80000000) != (4&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L24;
    }
    counters[46] ++;
    load_counter ++;
    ldr(&ip.i, &r4.i, 20, 4, false, false, false);
    tmp = r0.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) ip.i);
    v = (r0.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z && n == v)
    {
        goto L81;
    }
L29:
    counters[47] ++;
    tmp = r3.i - 5;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 5);
    v = (r3.i&0x80000000) != (5&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L24;
    }
    counters[48] ++;
    load_counter ++;
    ldr(&r0.i, &r4.i, 24, 4, false, false, false);
    tmp = ip.i - r0.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r0.i);
    v = (ip.i&0x80000000) != (r0.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (!z && n == v)
    {
        goto L82;
    }
L31:
    counters[49] ++;
    tmp = r3.i - 6;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 6);
    v = (r3.i&0x80000000) != (6&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L24;
    }
    counters[50] ++;
    load_counter ++;
    ldr(&ip.i, &r4.i, 28, 4, false, false, false);
    tmp = r0.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) ip.i);
    v = (r0.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z && n == v)
    {
        goto L83;
    }
L33:
    counters[51] ++;
    tmp = r3.i - 7;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 7);
    v = (r3.i&0x80000000) != (7&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L24;
    }
    counters[52] ++;
    load_counter ++;
    ldr(&r0.i, &r4.i, 32, 4, false, false, false);
    tmp = ip.i - r0.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r0.i);
    v = (ip.i&0x80000000) != (r0.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (!z && n == v)
    {
        goto L84;
    }
L35:
    counters[53] ++;
    tmp = r3.i - 9;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 9);
    v = (r3.i&0x80000000) != (9&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L36;
    }
    counters[54] ++;
    goto L24;
L77:
    counters[55] ++;
    load_counter ++;
    ldr(&r1.i, &r4.i, 4, 4, false, false, false);
    goto L19;
L37:
    counters[56] ++;
    r3.i = (LC0 & 0xffff);
    r1.i = (LC0 & 0xffff);
    r0.i = (LC1 & 0xffff);
    r3.i = r3.i | (((uint32_t)LC0 >> 16) << 16);
    r1.i = r1.i | (((uint32_t)LC0 >> 16) << 16);
    r0.i = r0.i | (((uint32_t)LC1 >> 16) << 16);
    r2.i = 66;
    assert_help();
    return;
}

void main()
{
    malloc_start();
    counters[57] ++;
    store_counter ++;
    sp.i -= 8;
    str(&r4.i, &sp.i, 0*4, 4, false, false, false);
    str(&lr.i, &sp.i, 1*4, 4, false, false, false);
    r0.i = 0;
    time_help();
    counters[58] ++;
    srand_help();
    counters[59] ++;
    test();
    counters[60] ++;
    r0.i = 0;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
    ldr(&pc.i, &sp.i, 1*4, 4, false, false, false);
    sp.i += 8;
    counter_summary();
    return;

}

