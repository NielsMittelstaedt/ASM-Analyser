#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

typedef union
{
    int32_t i;
    float f;
} reg;

int32_t tmp;
reg sp, fp, lr, pc, ip;
bool z, n, c, v;
char* malloc_0 = 0;

reg r4, r3, r0, r5, r6, r2, r1;

int32_t LC1, LC0;

int counters[2] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[2] = {28,3};

void ldr(int32_t *target, int32_t *address, int32_t offset, int bytes, bool update, bool post_index)
{
    char *ptr;
    ptr = malloc_0 + *address;
    *target = 0;

    if (!post_index)
        ptr += offset;

    for(int j=0; j<bytes; j++)
        *target += (*(ptr+j) << 8*j) & (0xff << 8*j);

    if (update || post_index)
        *address += offset;
}

void str(int32_t *target, int32_t *address, int32_t offset, int bytes, bool update, bool post_index)
{
    char *ptr;
    ptr = malloc_0 + *address;

    if (!post_index)
        ptr += offset;

    for(int j=0; j<bytes; j++)
        *(ptr+j) = (*target >> (8*j)) & 0xff;

    if(update || post_index)
        *address += offset;
}

void malloc_start()
{
    malloc_0 = (char*) malloc(1);
    char* stack_ptr = (char*) malloc(1000);
    sp.i = (int32_t) (stack_ptr - malloc_0) + 999;
    fp = sp;

    LC1 = (int32_t) ((char*) malloc(8) - malloc_0);
    strcpy(malloc_0+LC1, "%s\000");

    LC0 = (int32_t) ((char*) malloc(35) - malloc_0);
    strcpy(malloc_0+LC0, "http://www.tutorialspoint.com\000");

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "test.c";

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


void main()
{
    malloc_start();
    counters[0] ++;
    store_counter ++;
    sp.i -= 16;
    str(&r4.i, &sp.i, 0*4, 4, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false);
    str(&lr.i, &sp.i, 3*4, 4, false, false);
    r4.i = (LC0 & 0xffff);
    r4.i = r4.i | (((uint32_t)LC0 >> 16) << 16);
    sp.i = sp.i - 104;
    r6.i = 0;
    ip.i = sp.i + 52;
    load_counter ++;
    ldr(&r0.i, &r4.i, 0*4, 4, false, false);
    ldr(&r1.i, &r4.i, 1*4, 4, false, false);
    ldr(&r2.i, &r4.i, 2*4, 4, false, false);
    ldr(&r3.i, &r4.i, 3*4, 4, false, false);
    r4.i += 16;
    lr.i = sp.i;
    r5.i = sp.i;
    store_counter ++;
    str(&r6.i, &sp.i, 30, 4, false, false);
    store_counter ++;
    str(&r6.i, &sp.i, 34, 4, false, false);
    store_counter ++;
    str(&r6.i, &sp.i, 38, 4, false, false);
    store_counter ++;
    str(&r0.i, &lr.i, 0*4, 4, false, false);
    str(&r1.i, &lr.i, 1*4, 4, false, false);
    str(&r2.i, &lr.i, 2*4, 4, false, false);
    str(&r3.i, &lr.i, 3*4, 4, false, false);
    lr.i += 16;
    load_counter ++;
    ldr(&r0.i, &r4.i, 0*4, 4, false, false);
    ldr(&r1.i, &r4.i, 1*4, 4, false, false);
    ldr(&r2.i, &r4.i, 2*4, 4, false, false);
    ldr(&r3.i, &r4.i, 3*4, 4, false, false);
    store_counter ++;
    str(&r6.i, &sp.i, 42, 4, false, false);
    store_counter ++;
    str(&r6.i, &sp.i, 46, 4, false, false);
    store_counter ++;
    str(&r0.i, &lr.i, 0*4, 4, false, false);
    str(&r1.i, &lr.i, 1*4, 4, false, false);
    str(&r2.i, &lr.i, 2*4, 4, false, false);
    lr.i += 12;
    store_counter ++;
    str(&r3.i, &lr.i, 0, 2, false, true);
    load_counter ++;
    ldr(&r0.i, &r5.i, 0*4, 4, false, false);
    ldr(&r1.i, &r5.i, 1*4, 4, false, false);
    ldr(&r2.i, &r5.i, 2*4, 4, false, false);
    ldr(&r3.i, &r5.i, 3*4, 4, false, false);
    r5.i += 16;
    store_counter ++;
    str(&r0.i, &ip.i, 0*4, 4, false, false);
    str(&r1.i, &ip.i, 1*4, 4, false, false);
    str(&r2.i, &ip.i, 2*4, 4, false, false);
    str(&r3.i, &ip.i, 3*4, 4, false, false);
    ip.i += 16;
    load_counter ++;
    ldr(&r0.i, &r5.i, 0*4, 4, false, false);
    ldr(&r1.i, &r5.i, 1*4, 4, false, false);
    ldr(&r2.i, &r5.i, 2*4, 4, false, false);
    ldr(&r3.i, &r5.i, 3*4, 4, false, false);
    store_counter ++;
    str(&r0.i, &ip.i, 0*4, 4, false, false);
    str(&r1.i, &ip.i, 1*4, 4, false, false);
    str(&r2.i, &ip.i, 2*4, 4, false, false);
    ip.i += 12;
    r2.i = sp.i + 52;
    r1.i = (LC1 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC1 >> 16) << 16);
    store_counter ++;
    str(&r3.i, &ip.i, 0, 2, false, true);
    printf(malloc_0+r1.i, r2.i);
    counters[1] ++;
    r0.i = r6.i;
    sp.i = sp.i + 104;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false);
    ldr(&pc.i, &sp.i, 3*4, 4, false, false);
    sp.i += 16;
    counter_summary();
    return;

}

