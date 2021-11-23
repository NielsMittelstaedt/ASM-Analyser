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

int32_t LC1, LC2, LC3, LC4, LC5, LC6, LC7, LC8, LC9, L123, __PRETTY_FUNCTION__5477, LC0;

int counters[93] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[93] = {5,11,3,9,7,4,3,4,3,3,2,3,3,3,3,5,2,3,2,3,4,6,3,7,4,1,4,5,4,3,3,2,2,4,2,7,2,7,2,6,2,6,2,6,2,6,2,6,2,5,8,5,1,1,2,3,3,2,2,4,2,3,2,2,3,6,7,3,2,3,4,6,1,6,1,2,6,5,4,2,3,5,4,3,1,13,2,2,2,2,3,2,3};


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

    int32_t malloc_total = (int32_t) ((uint8_t*) malloc(239) - malloc_0);
    LC1 = malloc_total;
    strcpy(malloc_0+LC1, "Bucket[\"%d\"] : \000");

    LC2 = malloc_total + 23;
    strcpy(malloc_0+LC2, "%d \000");

    LC3 = malloc_total + 32;
    strcpy(malloc_0+LC3, "--------------\000");

    LC4 = malloc_total + 52;
    strcpy(malloc_0+LC4, "Buckets after sorted\000");

    LC5 = malloc_total + 78;
    strcpy(malloc_0+LC5, "../test_files/c_in/bucket_sort.c\000");

    LC6 = malloc_total + 116;
    strcpy(malloc_0+LC6, "j < NARRAY\000");

    LC7 = malloc_total + 132;
    strcpy(malloc_0+LC7, "Initial array\000");

    LC8 = malloc_total + 151;
    strcpy(malloc_0+LC8, "------------\000");

    LC9 = malloc_total + 169;
    strcpy(malloc_0+LC9, "Sorted array\000");

    L123 = malloc_total + 187;
    int32_t arrayL123[] = {LC0+12};
    for(int i=0; i<1; i++) str(&arrayL123[i], &L123, i*4, 4, false, false, false);

    __PRETTY_FUNCTION__5477 = malloc_total + 191;
    strcpy(malloc_0+__PRETTY_FUNCTION__5477, "BucketSort\000");

    LC0 = malloc_total + 207;
    int32_t arrayLC0[] = {29,25,-1,49,9,37,21,43};
    for(int i=0; i<8; i++) str(&arrayLC0[i], &LC0, i*4, 4, false, false, false);

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "bucket_sort.c";

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

void BucketSort();
void InsertionSort();
void getBucketIndex();
void print();
void printBuckets();
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

void BucketSort()
{
    counters[0] ++;
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
    r8.i = r0.i;
    sp.i = sp.i - 12;
    r0.i = 20;
    malloc_help();
    counters[1] ++;
    r4.i = 26215;
    r9.i = r8.i - 4;
    r6.i = r8.i + 28;
    r4.i = r4.i | (26214 << 16);
    r3.i = 0;
    r2.i = 0;
    r5.i = r0.i;
    store_counter ++;
    str(&r3.i, &r0.i, 16, 4, false, false, false);
    r3.i = 0;
    store_counter ++;
    str(&r2.i, &r0.i, 0, 4, false, true, false);
    str(&r3.i, &r0.i, 4, 4, false, true, false);
    store_counter ++;
    str(&r2.i, &r0.i, 8, 4, false, false, false);
    str(&r3.i, &r0.i, 12, 4, false, false, false);
L2:
    counters[2] ++;
    r0.i = 8;
    load_counter ++;
    ldr(&r7.i, &r9.i, 4, 4, true, false, false);
    malloc_help();
    counters[3] ++;
    tmp = r9.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r9.i) >= ((uint32_t) r6.i);
    v = (r9.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r9.i&0x80000000);
    smull(&r3.i, &r2.i, &r4.i, &r7.i);
    r3.i = r7.i >> 31;
    r3.i = (r2.i >> 2) - r3.i;
    load_counter ++;
    ldr(&r2.i, &r5.i, ((uint32_t)r3.i << 2), 4, false, false, false);
    store_counter ++;
    str(&r7.i, &r0.i, 0, 4, false, true, false);
    store_counter ++;
    str(&r0.i, &r5.i, ((uint32_t)r3.i << 2), 4, false, false, false);
    store_counter ++;
    str(&r2.i, &r0.i, 4, 4, false, false, false);
    if (!z)
    {
        goto L2;
    }
    counters[4] ++;
    r7.i = r5.i - 4;
    fp.i = (LC1 & 0xffff);
    r6.i = (LC2 & 0xffff);
    fp.i = fp.i | (((uint32_t)LC1 >> 16) << 16);
    r6.i = r6.i | (((uint32_t)LC2 >> 16) << 16);
    r10.i = r7.i;
    r9.i = 0;
L4:
    counters[5] ++;
    r2.i = r9.i;
    r1.i = fp.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[6] ++;
    load_counter ++;
    ldr(&r4.i, &r10.i, 4, 4, true, false, false);
    tmp = r4.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 0);
    v = (r4.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (z)
    {
        goto L6;
    }
L3:
    counters[7] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 0, 4, false, true, false);
    r1.i = r6.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[8] ++;
    load_counter ++;
    ldr(&r4.i, &r4.i, 4, 4, false, false, false);
    tmp = r4.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 0);
    v = (r4.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        goto L3;
    }
L6:
    counters[9] ++;
    r9.i = r9.i + 1;
    r0.i = 10;
    printf("%c", (char)r0.i);
    counters[10] ++;
    tmp = r9.i - 5;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r9.i) >= ((uint32_t) 5);
    v = (r9.i&0x80000000) != (5&0x80000000) && (tmp&0x80000000) != (r9.i&0x80000000);
    if (!z)
    {
        goto L4;
    }
    counters[11] ++;
    r9.i = r5.i + 16;
    r6.i = r7.i;
    r10.i = 0;
L14:
    counters[12] ++;
    load_counter ++;
    ldr(&lr.i, &r6.i, 4, 4, true, false, false);
    tmp = lr.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) 0);
    v = (lr.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    if (z)
    {
        goto L7;
    }
    counters[13] ++;
    load_counter ++;
    ldr(&r1.i, &lr.i, 4, 4, false, false, false);
    tmp = r1.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 0);
    v = (r1.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (z)
    {
        goto L7;
    }
    counters[14] ++;
    load_counter ++;
    ldr(&r4.i, &lr.i, 0, 4, false, true, false);
    store_counter ++;
    str(&r10.i, &lr.i, 4, 4, false, false, false);
    goto L13;
L85:
    counters[15] ++;
    load_counter ++;
    ldr(&r3.i, &r1.i, 4, 4, false, false, false);
    r4.i = r0.i;
    store_counter ++;
    str(&lr.i, &r1.i, 4, 4, false, false, false);
    lr.i = r1.i;
    r1.i = r3.i;
L9:
    counters[16] ++;
    tmp = r1.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 0);
    v = (r1.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (z)
    {
        goto L7;
    }
L13:
    counters[17] ++;
    load_counter ++;
    ldr(&r0.i, &r1.i, 0, 4, false, true, false);
    tmp = r0.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) r4.i);
    v = (r0.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (n != v)
    {
        goto L85;
    }
    counters[18] ++;
    r3.i = lr.i;
    goto L8;
L11:
    counters[19] ++;
    load_counter ++;
    ldr(&r2.i, &r3.i, 0, 4, false, true, false);
    tmp = r0.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) r2.i);
    v = (r0.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (n != v)
    {
        goto L86;
    }
L8:
    counters[20] ++;
    ip.i = r3.i;
    load_counter ++;
    ldr(&r3.i, &r3.i, 4, 4, false, false, false);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L11;
    }
    counters[21] ++;
    store_counter ++;
    str(&r1.i, &ip.i, 4, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &r1.i, 4, 4, false, false, false);
    store_counter ++;
    str(&r3.i, &r1.i, 4, 4, false, false, false);
    r1.i = r2.i;
    tmp = r1.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 0);
    v = (r1.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!z)
    {
        goto L13;
    }
L7:
    counters[22] ++;
    tmp = r6.i - r9.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) r9.i);
    v = (r6.i&0x80000000) != (r9.i&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    store_counter ++;
    str(&lr.i, &r6.i, 0, 4, false, true, false);
    if (!z)
    {
        goto L14;
    }
    counters[23] ++;
    r0.i = (LC3 & 0xffff);
    fp.i = (LC1 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC3 >> 16) << 16);
    r4.i = (LC2 & 0xffff);
    fp.i = fp.i | (((uint32_t)LC1 >> 16) << 16);
    r4.i = r4.i | (((uint32_t)LC2 >> 16) << 16);
    printf("%s\n", malloc_0+r0.i);
    counters[24] ++;
    r6.i = 0;
    r0.i = (LC4 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC4 >> 16) << 16);
    printf("%s\n", malloc_0+r0.i);
    counters[25] ++;
    store_counter ++;
    str(&r7.i, &sp.i, 4, 4, false, false, false);
L16:
    counters[26] ++;
    r2.i = r6.i;
    r1.i = fp.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[27] ++;
    load_counter ++;
    ldr(&r3.i, &sp.i, 4, 4, false, false, false);
    load_counter ++;
    ldr(&r10.i, &r3.i, 4, 4, true, false, false);
    tmp = r10.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r10.i) >= ((uint32_t) 0);
    v = (r10.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r10.i&0x80000000);
    store_counter ++;
    str(&r3.i, &sp.i, 4, 4, false, false, false);
    if (z)
    {
        goto L18;
    }
L15:
    counters[28] ++;
    load_counter ++;
    ldr(&r2.i, &r10.i, 0, 4, false, true, false);
    r1.i = r4.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[29] ++;
    load_counter ++;
    ldr(&r10.i, &r10.i, 4, 4, false, false, false);
    tmp = r10.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r10.i) >= ((uint32_t) 0);
    v = (r10.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r10.i&0x80000000);
    if (!z)
    {
        goto L15;
    }
L18:
    counters[30] ++;
    r6.i = r6.i + 1;
    r0.i = 10;
    printf("%c", (char)r0.i);
    counters[31] ++;
    tmp = r6.i - 5;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) 5);
    v = (r6.i&0x80000000) != (5&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    if (!z)
    {
        goto L16;
    }
    counters[32] ++;
    r1.i = r7.i;
    r3.i = 0;
L17:
    counters[33] ++;
    load_counter ++;
    ldr(&r2.i, &r1.i, 4, 4, false, false, false);
    lr.i = r1.i + 4;
    tmp = r2.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) 0);
    v = (r2.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (z)
    {
        goto L30;
    }
    counters[34] ++;
    tmp = r3.i - 8;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 8);
    v = (r3.i&0x80000000) != (8&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L20;
    }
    counters[35] ++;
    load_counter ++;
    ldr(&r0.i, &r2.i, 4, 4, false, false, false);
    r4.i = r3.i + 1;
    load_counter ++;
    ldr(&ip.i, &r2.i, 0, 4, false, true, false);
    r2.i = (uint32_t)r3.i << 2;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    store_counter ++;
    str(&ip.i, &r8.i, ((uint32_t)r3.i << 2), 4, false, false, false);
    if (z)
    {
        goto L36;
    }
    counters[36] ++;
    tmp = r4.i - 8;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 8);
    v = (r4.i&0x80000000) != (8&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (z)
    {
        goto L20;
    }
    counters[37] ++;
    load_counter ++;
    ldr(&ip.i, &r0.i, 4, 4, false, false, false);
    r2.i = r8.i + r2.i;
    load_counter ++;
    ldr(&r0.i, &r0.i, 0, 4, false, true, false);
    r4.i = r3.i + 2;
    tmp = ip.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) 0);
    v = (ip.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    store_counter ++;
    str(&r0.i, &r2.i, 4, 4, false, false, false);
    if (z)
    {
        goto L36;
    }
    counters[38] ++;
    tmp = r4.i - 8;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 8);
    v = (r4.i&0x80000000) != (8&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (z)
    {
        goto L20;
    }
    counters[39] ++;
    load_counter ++;
    ldr(&r0.i, &ip.i, 4, 4, false, false, false);
    r4.i = r3.i + 3;
    load_counter ++;
    ldr(&ip.i, &ip.i, 0, 4, false, true, false);
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    store_counter ++;
    str(&ip.i, &r2.i, 8, 4, false, false, false);
    if (z)
    {
        goto L36;
    }
    counters[40] ++;
    tmp = r4.i - 8;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 8);
    v = (r4.i&0x80000000) != (8&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (z)
    {
        goto L20;
    }
    counters[41] ++;
    load_counter ++;
    ldr(&ip.i, &r0.i, 4, 4, false, false, false);
    r4.i = r3.i + 4;
    load_counter ++;
    ldr(&r0.i, &r0.i, 0, 4, false, true, false);
    tmp = ip.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) 0);
    v = (ip.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    store_counter ++;
    str(&r0.i, &r2.i, 12, 4, false, false, false);
    if (z)
    {
        goto L36;
    }
    counters[42] ++;
    tmp = r4.i - 8;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 8);
    v = (r4.i&0x80000000) != (8&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (z)
    {
        goto L20;
    }
    counters[43] ++;
    load_counter ++;
    ldr(&r0.i, &ip.i, 4, 4, false, false, false);
    r4.i = r3.i + 5;
    load_counter ++;
    ldr(&ip.i, &ip.i, 0, 4, false, true, false);
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    store_counter ++;
    str(&ip.i, &r2.i, 16, 4, false, false, false);
    if (z)
    {
        goto L36;
    }
    counters[44] ++;
    tmp = r4.i - 8;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 8);
    v = (r4.i&0x80000000) != (8&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (z)
    {
        goto L20;
    }
    counters[45] ++;
    load_counter ++;
    ldr(&ip.i, &r0.i, 4, 4, false, false, false);
    r4.i = r3.i + 6;
    load_counter ++;
    ldr(&r0.i, &r0.i, 0, 4, false, true, false);
    tmp = ip.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) 0);
    v = (ip.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    store_counter ++;
    str(&r0.i, &r2.i, 20, 4, false, false, false);
    if (z)
    {
        goto L36;
    }
    counters[46] ++;
    tmp = r4.i - 8;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 8);
    v = (r4.i&0x80000000) != (8&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (z)
    {
        goto L20;
    }
    counters[47] ++;
    load_counter ++;
    ldr(&r0.i, &ip.i, 4, 4, false, false, false);
    r3.i = r3.i + 7;
    load_counter ++;
    ldr(&ip.i, &ip.i, 0, 4, false, true, false);
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    store_counter ++;
    str(&ip.i, &r2.i, 24, 4, false, false, false);
    if (z)
    {
        goto L30;
    }
    counters[48] ++;
    tmp = r3.i - 7;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 7);
    v = (r3.i&0x80000000) != (7&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L20;
    }
    counters[49] ++;
    load_counter ++;
    ldr(&r2.i, &r0.i, 4, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &r0.i, 0, 4, false, true, false);
    tmp = r2.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) 0);
    v = (r2.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    store_counter ++;
    str(&r3.i, &r8.i, 28, 4, false, false, false);
    if (z)
    {
        goto L87;
    }
L20:
    counters[50] ++;
    r3.i = (LC0 & 0xffff);
    r1.i = (LC5 & 0xffff);
    r0.i = (LC6 & 0xffff);
    r3.i = r3.i | (((uint32_t)LC0 >> 16) << 16);
    r1.i = r1.i | (((uint32_t)LC5 >> 16) << 16);
    r0.i = r0.i | (((uint32_t)LC6 >> 16) << 16);
    r2.i = 83;
    assert_help();
L86:
    counters[51] ++;
    load_counter ++;
    ldr(&r2.i, &r1.i, 4, 4, false, false, false);
    store_counter ++;
    str(&r3.i, &r1.i, 4, 4, false, false, false);
    store_counter ++;
    str(&r1.i, &ip.i, 4, 4, false, false, false);
    r1.i = r2.i;
    goto L9;
L36:
    counters[52] ++;
    r3.i = r4.i;
L30:
    counters[53] ++;
    r1.i = lr.i;
L19:
    counters[54] ++;
    tmp = r1.i - r9.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r9.i);
    v = (r1.i&0x80000000) != (r9.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!z)
    {
        goto L17;
    }
L26:
    counters[55] ++;
    load_counter ++;
    ldr(&r4.i, &r7.i, 4, 4, true, false, false);
    tmp = r4.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 0);
    v = (r4.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (z)
    {
        goto L28;
    }
L25:
    counters[56] ++;
    r0.i = r4.i;
    load_counter ++;
    ldr(&r4.i, &r4.i, 4, 4, false, false, false);
    free_help();
    counters[57] ++;
    tmp = r4.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 0);
    v = (r4.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        goto L25;
    }
L28:
    counters[58] ++;
    tmp = r7.i - r9.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r7.i) >= ((uint32_t) r9.i);
    v = (r7.i&0x80000000) != (r9.i&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
    if (!z)
    {
        goto L26;
    }
    counters[59] ++;
    r0.i = r5.i;
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
L87:
    counters[60] ++;
    tmp = lr.i - r9.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) r9.i);
    v = (lr.i&0x80000000) != (r9.i&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    if (z)
    {
        goto L26;
    }
    counters[61] ++;
    load_counter ++;
    ldr(&r3.i, &r1.i, 8, 4, true, false, false);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L20;
    }
    counters[62] ++;
    r3.i = 8;
    goto L19;
    return;
}

void InsertionSort()
{
    counters[63] ++;
    r3.i = r0.i - 0;
    z = r3.i == 0;
    n = r3.i & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (r3.i&0x80000000) != (r0.i&0x80000000);
    if (z)
    {
        goto L97;
    }
    counters[64] ++;
    load_counter ++;
    ldr(&ip.i, &r3.i, 4, 4, false, false, false);
    tmp = ip.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) 0);
    v = (ip.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (z)
    {
        goto L97;
    }
    counters[65] ++;
    store_counter ++;
    sp.i -= 8;
    str(&r4.i, &sp.i, 0*4, 4, false, false, false);
    str(&lr.i, &sp.i, 1*4, 4, false, false, false);
    r2.i = 0;
    load_counter ++;
    ldr(&r4.i, &r3.i, 0, 4, false, true, false);
    r0.i = r3.i;
    store_counter ++;
    str(&r2.i, &r3.i, 4, 4, false, false, false);
    goto L95;
L106:
    counters[66] ++;
    load_counter ++;
    ldr(&r3.i, &ip.i, 4, 4, false, false, false);
    r4.i = r1.i;
    store_counter ++;
    str(&r0.i, &ip.i, 4, 4, false, false, false);
    r0.i = ip.i;
    ip.i = r3.i;
    tmp = ip.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) 0);
    v = (ip.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    load_counter ++;
    if (z)
    {
        ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
        ldr(&pc.i, &sp.i, 1*4, 4, false, false, false);
        sp.i += 8;
        return;
    }
L95:
    counters[67] ++;
    load_counter ++;
    ldr(&r1.i, &ip.i, 0, 4, false, true, false);
    tmp = r1.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r4.i);
    v = (r1.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (n != v)
    {
        goto L106;
    }
    counters[68] ++;
    r3.i = r0.i;
    goto L90;
L93:
    counters[69] ++;
    load_counter ++;
    ldr(&r2.i, &r3.i, 0, 4, false, true, false);
    tmp = r1.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r2.i);
    v = (r1.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (n != v)
    {
        goto L107;
    }
L90:
    counters[70] ++;
    lr.i = r3.i;
    load_counter ++;
    ldr(&r3.i, &r3.i, 4, 4, false, false, false);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L93;
    }
    counters[71] ++;
    store_counter ++;
    str(&ip.i, &lr.i, 4, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &ip.i, 4, 4, false, false, false);
    store_counter ++;
    str(&r3.i, &ip.i, 4, 4, false, false, false);
    ip.i = r2.i;
    tmp = ip.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) 0);
    v = (ip.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (!z)
    {
        goto L95;
    }
    counters[72] ++;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
    ldr(&pc.i, &sp.i, 1*4, 4, false, false, false);
    sp.i += 8;
    return;
L107:
    counters[73] ++;
    load_counter ++;
    ldr(&r2.i, &ip.i, 4, 4, false, false, false);
    store_counter ++;
    str(&r3.i, &ip.i, 4, 4, false, false, false);
    store_counter ++;
    str(&ip.i, &lr.i, 4, 4, false, false, false);
    ip.i = r2.i;
    tmp = ip.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) 0);
    v = (ip.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (!z)
    {
        goto L95;
    }
    counters[74] ++;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
    ldr(&pc.i, &sp.i, 1*4, 4, false, false, false);
    sp.i += 8;
    return;
L97:
    counters[75] ++;
    r0.i = r3.i;
    return;

}

void getBucketIndex()
{
    counters[76] ++;
    r3.i = 26215;
    r3.i = r3.i | (26214 << 16);
    r2.i = r0.i >> 31;
    smull(&r3.i, &r0.i, &r3.i, &r0.i);
    r0.i = (r0.i >> 2) - r2.i;
    return;

}

void print()
{
    counters[77] ++;
    store_counter ++;
    sp.i -= 16;
    str(&r4.i, &sp.i, 0*4, 4, false, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false, false);
    str(&lr.i, &sp.i, 3*4, 4, false, false, false);
    r6.i = (LC2 & 0xffff);
    r4.i = r0.i - 4;
    r6.i = r6.i | (((uint32_t)LC2 >> 16) << 16);
    r5.i = r0.i + 28;
L110:
    counters[78] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 4, 4, true, false, false);
    r1.i = r6.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[79] ++;
    tmp = r4.i - r5.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r5.i);
    v = (r4.i&0x80000000) != (r5.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        goto L110;
    }
    counters[80] ++;
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

void printBuckets()
{
    counters[81] ++;
    store_counter ++;
    sp.i -= 16;
    str(&r4.i, &sp.i, 0*4, 4, false, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false, false);
    str(&lr.i, &sp.i, 3*4, 4, false, false, false);
    r4.i = r0.i - 0;
    z = r4.i == 0;
    n = r4.i & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (r4.i&0x80000000) != (r0.i&0x80000000);
    load_counter ++;
    if (z)
    {
        ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
        ldr(&r5.i, &sp.i, 1*4, 4, false, false, false);
        ldr(&r6.i, &sp.i, 2*4, 4, false, false, false);
        ldr(&pc.i, &sp.i, 3*4, 4, false, false, false);
        sp.i += 16;
        return;
    }
    r5.i = (LC2 & 0xffff);
    r5.i = r5.i | (((uint32_t)LC2 >> 16) << 16);
L115:
    counters[82] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 0, 4, false, true, false);
    r1.i = r5.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[83] ++;
    load_counter ++;
    ldr(&r4.i, &r4.i, 4, 4, false, false, false);
    tmp = r4.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 0);
    v = (r4.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        goto L115;
    }
    counters[84] ++;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false, false);
    ldr(&pc.i, &sp.i, 3*4, 4, false, false, false);
    sp.i += 16;
    return;

}

void main()
{
    malloc_start();
    counters[85] ++;
    store_counter ++;
    sp.i -= 8;
    str(&r4.i, &sp.i, 0*4, 4, false, false, false);
    str(&lr.i, &sp.i, 1*4, 4, false, false, false);
    sp.i = sp.i - 32;
    load_counter ++;
    ldr(&lr.i, &L123.i, 0, 4, false, false, false);
    r4.i = (LC8 & 0xffff);
    ip.i = sp.i;
    r4.i = r4.i | (((uint32_t)LC8 >> 16) << 16);
    load_counter ++;
    ldr(&r0.i, &lr.i, 0*4, 4, false, false, false);
    ldr(&r1.i, &lr.i, 1*4, 4, false, false, false);
    ldr(&r2.i, &lr.i, 2*4, 4, false, false, false);
    ldr(&r3.i, &lr.i, 3*4, 4, false, false, false);
    lr.i += 16;
    store_counter ++;
    str(&r0.i, &ip.i, 0*4, 4, false, false, false);
    str(&r1.i, &ip.i, 1*4, 4, false, false, false);
    str(&r2.i, &ip.i, 2*4, 4, false, false, false);
    str(&r3.i, &ip.i, 3*4, 4, false, false, false);
    ip.i += 16;
    load_counter ++;
    ldr(&r0.i, &lr.i, 0*4, 4, false, false, false);
    ldr(&r1.i, &lr.i, 1*4, 4, false, false, false);
    ldr(&r2.i, &lr.i, 2*4, 4, false, false, false);
    ldr(&r3.i, &lr.i, 3*4, 4, false, false, false);
    store_counter ++;
    str(&r0.i, &ip.i, 0*4, 4, false, false, false);
    str(&r1.i, &ip.i, 1*4, 4, false, false, false);
    str(&r2.i, &ip.i, 2*4, 4, false, false, false);
    str(&r3.i, &ip.i, 3*4, 4, false, false, false);
    r0.i = (LC7 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC7 >> 16) << 16);
    printf("%s\n", malloc_0+r0.i);
    counters[86] ++;
    r0.i = sp.i;
    print();
    counters[87] ++;
    r0.i = r4.i;
    printf("%s\n", malloc_0+r0.i);
    counters[88] ++;
    r0.i = sp.i;
    BucketSort();
    counters[89] ++;
    r0.i = r4.i;
    printf("%s\n", malloc_0+r0.i);
    counters[90] ++;
    r0.i = (LC9 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC9 >> 16) << 16);
    printf("%s\n", malloc_0+r0.i);
    counters[91] ++;
    r0.i = sp.i;
    print();
    counters[92] ++;
    r0.i = 0;
    sp.i = sp.i + 32;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
    ldr(&pc.i, &sp.i, 1*4, 4, false, false, false);
    sp.i += 8;
    return;
L124:
    counter_summary();
    return;
}

