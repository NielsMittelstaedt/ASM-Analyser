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

reg r2, r8, r1, r0, r9, r10, r3, r5, r4, r6, r7;

int32_t LC1, LC2, LC0;

int counters[28] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[28] = {3,4,4,2,3,15,3,6,3,8,3,4,3,2,5,1,3,6,2,1,1,8,3,3,3,3,2,2};


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

    int32_t malloc_total = (int32_t) ((uint8_t*) malloc(59) - malloc_0);
    LC1 = malloc_total;
    strcpy(malloc_0+LC1, "%3d \000");

    LC2 = malloc_total + 10;
    strcpy(malloc_0+LC2, "Data Sorted\000");

    LC0 = malloc_total + 27;
    int32_t arrayLC0[] = {701,301,132,57,23,10,4,1};
    for(int i=0; i<8; i++) str(&arrayLC0[i], &LC0, i*4, 4, false, false, false);

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "shell_sort2.c";

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

void show_data();
void shell_sort();
void main();

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
void malloc_help()
{
    uint8_t* ptr = (uint8_t*) malloc(r0.i);
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

void show_data()
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
    r6.i = (LC1 & 0xffff);
    r5.i = r0.i + (((uint32_t)r5.i << 2));
    r6.i = r6.i | (((uint32_t)LC1 >> 16) << 16);
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

void shell_sort()
{
    counters[5] ++;
    ip.i = (LC0 & 0xffff);
    ip.i = ip.i | (((uint32_t)LC0 >> 16) << 16);
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&fp.i, &sp.i, 0, 4, false, false, false);
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
    r4.i = r0.i;
    r7.i = r1.i;
    sp.i = sp.i - (44);
    load_counter ++;
    ldr(&r0.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    ldr(&r1.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    ldr(&r2.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    ldr(&r3.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    lr.i = sp.i + (8);
    r5.i = r4.i - (4);
    r6.i = sp.i + (4);
    r5.i = r5.i + (((uint32_t)r7.i << 2));
    store_counter ++;
    str(&r4.i, &sp.i, 4, 4, false, false, false);
    store_counter ++;
    str(&r0.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    str(&r1.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    str(&r2.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    str(&r3.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    load_counter ++;
    tmp = ip.i;
    ldr(&r0.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    ldr(&r1.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    ldr(&r2.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    ldr(&r3.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    ip.i = tmp;
    store_counter ++;
    tmp = lr.i;
    str(&r0.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    str(&r1.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    str(&r2.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    str(&r3.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    lr.i = tmp;
L9:
    counters[6] ++;
    load_counter ++;
    ldr(&r4.i, &r6.i, 4, 4, true, false, false);
    tmp = r4.i - r7.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r7.i);
    v = (r4.i&0x80000000) != (r7.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (n == v)
    {
        goto L15;
    }
    counters[7] ++;
    load_counter ++;
    ldr(&r3.i, &sp.i, 4, 4, false, false, false);
    r10.i = r4.i - (-1073741823);
    lr.i = (uint32_t)r4.i << 2;
    fp.i = r4.i;
    lr.i = 0 - lr.i;
    r10.i = r3.i + (((uint32_t)r10.i << 2));
L14:
    counters[8] ++;
    load_counter ++;
    ldr(&r9.i, &r10.i, 4, 4, true, false, false);
    r2.i = fp.i;
    ip.i = r10.i;
L11:
    counters[9] ++;
    load_counter ++;
    ldr(&r1.i, &ip.i, lr.i, 4, false, false, false);
    r0.i = ip.i + (lr.i);
    r3.i = ip.i;
    r2.i = r2.i - (r4.i);
    r8.i = r1.i - (r9.i);
    ip.i = r0.i;
    tmp = r8.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) 0);
    v = (r8.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    if (z || n != v)
    {
        goto L21;
    }
    counters[10] ++;
    tmp = r2.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r4.i);
    v = (r2.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    store_counter ++;
    str(&r1.i, &r3.i, 0, 4, false, true, false);
    if (n == v)
    {
        goto L11;
    }
    counters[11] ++;
    tmp = r5.i - r10.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r10.i);
    v = (r5.i&0x80000000) != (r10.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    fp.i = fp.i + (1);
    store_counter ++;
    str(&r9.i, &r0.i, 0, 4, false, true, false);
    if (!z)
    {
        goto L14;
    }
L15:
    counters[12] ++;
    r3.i = sp.i + (36);
    tmp = r6.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) r3.i);
    v = (r6.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    if (!z)
    {
        goto L9;
    }
    counters[13] ++;
    sp.i = sp.i + (44);
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
    ldr(&fp.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;
L21:
    counters[14] ++;
    tmp = r5.i - r10.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r10.i);
    v = (r5.i&0x80000000) != (r10.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    r0.i = r3.i;
    fp.i = fp.i + (1);
    store_counter ++;
    str(&r9.i, &r0.i, 0, 4, false, true, false);
    if (!z)
    {
        goto L14;
    }
    counters[15] ++;
    goto L15;
    return;
}

void main()
{
    malloc_start();
    counters[16] ++;
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
    r0.i = 40;
    malloc_help();
    counters[17] ++;
    r4.i = 19923;
    r4.i = r4.i | (4194 << 16);
    r5.i = 500;
    r7.i = r0.i;
    r0.i = 0;
    time_help();
    counters[18] ++;
    r8.i = r7.i - (4);
    srand_help();
    counters[19] ++;
    r6.i = r7.i + (36);
L23:
    counters[20] ++;
    rand_help();
    counters[21] ++;
    smull(&r3.i, &r2.i, &r4.i, &r0.i);
    r3.i = r0.i >> 31;
    r3.i = (r2.i >> 5) - r3.i;
    r3.i = r0.i - ((r5.i) * (r3.i));
    z = r3.i == 0;
    n = r3.i & 0x80000000;
    r3.i = r3.i + (1);
    store_counter ++;
    str(&r3.i, &r8.i, 4, 4, true, false, false);
    tmp = r8.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) r6.i);
    v = (r8.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    if (!z)
    {
        goto L23;
    }
    counters[22] ++;
    r0.i = r7.i;
    r1.i = 10;
    show_data();
    counters[23] ++;
    r1.i = 10;
    r0.i = r7.i;
    shell_sort();
    counters[24] ++;
    r0.i = (LC2 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC2 >> 16) << 16);
    printf("%s\n", malloc_0+r0.i);
    counters[25] ++;
    r1.i = 10;
    r0.i = r7.i;
    show_data();
    counters[26] ++;
    r0.i = r7.i;
    free_help();
    counters[27] ++;
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
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    counter_summary();
    return;

}

