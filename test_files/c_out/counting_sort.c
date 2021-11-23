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

int32_t LC0;

int counters[11] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[11] = {3,15,27,3,3,5,3,1,2,2,2};


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

    int32_t malloc_total = (int32_t) ((uint8_t*) malloc(9) - malloc_0);
    LC0 = malloc_total;
    strcpy(malloc_0+LC0, "%d \000");

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "counting_sort.c";

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

void main();

void free_help()
{
    free(malloc_0+r0.i);
}
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

void main()
{
    malloc_start();
    counters[0] ++;
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
    r0.i = 24;
    malloc_help();
    counters[1] ++;
    r1.i = 1;
    r3.i = 6;
    r4.i = 5;
    r5.i = 4;
    r7.i = (LC0 & 0xffff);
    r7.i = r7.i | (((uint32_t)LC0 >> 16) << 16);
    r9.i = r0.i;
    r0.i = 28;
    store_counter ++;
    str(&r4.i, &r9.i, 4, 4, false, false, false);
    str(&r5.i, &r9.i, 8, 4, false, false, false);
    r5.i = 2;
    store_counter ++;
    str(&r1.i, &r9.i, 20, 4, false, false, false);
    r4.i = 3;
    store_counter ++;
    str(&r3.i, &r9.i, 0, 4, false, true, false);
    store_counter ++;
    str(&r4.i, &r9.i, 12, 4, false, false, false);
    str(&r5.i, &r9.i, 16, 4, false, false, false);
    calloc_help();
    counters[2] ++;
    load_counter ++;
    ldr(&r1.i, &r9.i, 0, 4, false, true, false);
    r5.i = 0;
    load_counter ++;
    ldr(&r2.i, &r9.i, 4, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &r0.i, ((uint32_t)r1.i << 2), 4, false, false, false);
    r8.i = r0.i;
    load_counter ++;
    ldr(&r0.i, &r9.i, 8, 4, false, false, false);
    r6.i = r8.i - 4;
    r3.i = r3.i + 1;
    store_counter ++;
    str(&r3.i, &r8.i, ((uint32_t)r1.i << 2), 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &r8.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    load_counter ++;
    ldr(&r1.i, &r9.i, 12, 4, false, false, false);
    r3.i = r3.i + 1;
    store_counter ++;
    str(&r3.i, &r8.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &r8.i, ((uint32_t)r0.i << 2), 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &r9.i, 16, 4, false, false, false);
    r3.i = r3.i + 1;
    store_counter ++;
    str(&r3.i, &r8.i, ((uint32_t)r0.i << 2), 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &r8.i, ((uint32_t)r1.i << 2), 4, false, false, false);
    r3.i = r3.i + 1;
    store_counter ++;
    str(&r3.i, &r8.i, ((uint32_t)r1.i << 2), 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &r8.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    r3.i = r3.i + 1;
    store_counter ++;
    str(&r3.i, &r8.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &r8.i, 4, 4, false, false, false);
    r3.i = r3.i + 1;
    store_counter ++;
    str(&r3.i, &r8.i, 4, 4, false, false, false);
    goto L4;
L2:
    counters[3] ++;
    r5.i = r5.i + 1;
    tmp = r5.i - 7;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) 7);
    v = (r5.i&0x80000000) != (7&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (z)
    {
        goto L9;
    }
L4:
    counters[4] ++;
    load_counter ++;
    ldr(&r4.i, &r6.i, 4, 4, true, false, false);
    tmp = r4.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 0);
    v = (r4.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (z || n != v)
    {
        goto L2;
    }
L3:
    counters[5] ++;
    r4.i = r4.i - 1;
    r2.i = r5.i;
    r1.i = r7.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[6] ++;
    tmp = r4.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 0);
    v = (r4.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    store_counter ++;
    str(&r4.i, &r6.i, 0, 4, false, true, false);
    if (!z)
    {
        goto L3;
    }
    counters[7] ++;
    goto L2;
L9:
    counters[8] ++;
    r0.i = r9.i;
    free_help();
    counters[9] ++;
    r0.i = r8.i;
    free_help();
    counters[10] ++;
    r0.i = 0;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false, false);
    ldr(&r7.i, &sp.i, 3*4, 4, false, false, false);
    ldr(&r8.i, &sp.i, 4*4, 4, false, false, false);
    ldr(&r9.i, &sp.i, 5*4, 4, false, false, false);
    ldr(&r10.i, &sp.i, 6*4, 4, false, false, false);
    ldr(&pc.i, &sp.i, 7*4, 4, false, false, false);
    sp.i += 32;
    counter_summary();
    return;

}

