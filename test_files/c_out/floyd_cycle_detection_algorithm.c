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

reg r2, r4, r1, r3, r0;

int32_t LC1, LC2, LC3, LC4, LC0, __PRETTY_FUNCTION__4919;

int counters[13] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[13] = {3,3,5,2,4,1,2,17,3,2,3,3,7};

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

void print_stack(int32_t start, int32_t bytes)
{
    int32_t size = bytes/4;
    int32_t cur_val = 0;

    for(int32_t i=0; i<size; i++)
    {
        ldr(&cur_val, &start, i*4, 4, false, false, false);
        printf("%d: %d\n", start+i*4, cur_val);
    }
}

void malloc_start()
{
    malloc_0 = (uint8_t*) malloc(20169);
    sp.i = 19996;
    fp = sp;
    LC1 = 20000;
    strcpy(malloc_0+LC1, "1st test... \000");

    LC2 = 20018;
    strcpy(malloc_0+LC2, "../test_files/c_in/floyd_cycle_detection_algorithm.");

    LC3 = 20071;
    strcpy(malloc_0+LC3, "index == 1\000");

    LC4 = 20087;
    strcpy(malloc_0+LC4, "passed\000");

    LC0 = 20099;
    int32_t arrayLC0[] = {1,1,2,3,5,8,13,21,34,55,89,144,233,377,610};
    for(int i=0; i<15; i++) str(&arrayLC0[i], &LC0, i*4, 4, false, false, false);

    __PRETTY_FUNCTION__4919 = 20159;
    strcpy(malloc_0+__PRETTY_FUNCTION__4919, "test\000");

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "floyd_cycle_detection_algorithm.c";

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

void duplicateNumber();
void main();

void printf_help(const char *format, int32_t test)
{
    if (strstr(format, "%s") != NULL)
        printf(format, malloc_0 + test);
    else
        printf(format, test);
}
void assert_help()
{
    __assert_fail(malloc_0+r0.i, malloc_0+r1.i, r2.i, malloc_0+r3.i);
}

void duplicateNumber()
{
    counters[0] ++;
    tmp = r1.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 1);
    v = (r1.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    r3.i = r0.i;
    if (!c || z)
    {
        goto L5;
    }
    counters[1] ++;
    load_counter ++;
    ldr(&r2.i, &r0.i, 0, 4, false, false, false);
    r0.i = r2.i;
    r1.i = r2.i;
L3:
    counters[2] ++;
    load_counter ++;
    ldr(&r0.i, &r3.i, ((uint32_t)r0.i << 2), 4, false, false, false);
    load_counter ++;
    ldr(&r1.i, &r3.i, ((uint32_t)r1.i << 2), 4, false, false, false);
    load_counter ++;
    ldr(&r0.i, &r3.i, ((uint32_t)r0.i << 2), 4, false, false, false);
    tmp = r1.i - r0.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r0.i);
    v = (r1.i&0x80000000) != (r0.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!z)
    {
        goto L3;
    }
    counters[3] ++;
    tmp = r2.i - r0.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r0.i);
    v = (r2.i&0x80000000) != (r0.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (z)
    {
        return;
    }
L4:
    counters[4] ++;
    load_counter ++;
    ldr(&r2.i, &r3.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    load_counter ++;
    ldr(&r0.i, &r3.i, ((uint32_t)r0.i << 2), 4, false, false, false);
    tmp = r2.i - r0.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r0.i);
    v = (r2.i&0x80000000) != (r0.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z)
    {
        goto L4;
    }
    counters[5] ++;
    return;
L5:
    counters[6] ++;
    r0.i = ~0;
    return;

}

void main()
{
    malloc_start();
    counters[7] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r4.i, &sp.i, 0, 4, false, false, false);
    r4.i = (LC0 & 0xffff);
    r4.i = r4.i | (((uint32_t)LC0 >> 16) << 16);
    sp.i = sp.i - (64);
    ip.i = sp.i + (4);
    load_counter ++;
    ldr(&r0.i, &r4.i, 0, 4, false, false, false);
    r4.i += 4;
    ldr(&r1.i, &r4.i, 0, 4, false, false, false);
    r4.i += 4;
    ldr(&r2.i, &r4.i, 0, 4, false, false, false);
    r4.i += 4;
    ldr(&r3.i, &r4.i, 0, 4, false, false, false);
    r4.i += 4;
    store_counter ++;
    str(&r0.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    str(&r1.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    str(&r2.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    str(&r3.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    load_counter ++;
    ldr(&r0.i, &r4.i, 0, 4, false, false, false);
    r4.i += 4;
    ldr(&r1.i, &r4.i, 0, 4, false, false, false);
    r4.i += 4;
    ldr(&r2.i, &r4.i, 0, 4, false, false, false);
    r4.i += 4;
    ldr(&r3.i, &r4.i, 0, 4, false, false, false);
    r4.i += 4;
    store_counter ++;
    str(&r0.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    str(&r1.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    str(&r2.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    str(&r3.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    load_counter ++;
    ldr(&r0.i, &r4.i, 0, 4, false, false, false);
    r4.i += 4;
    ldr(&r1.i, &r4.i, 0, 4, false, false, false);
    r4.i += 4;
    ldr(&r2.i, &r4.i, 0, 4, false, false, false);
    r4.i += 4;
    ldr(&r3.i, &r4.i, 0, 4, false, false, false);
    r4.i += 4;
    store_counter ++;
    str(&r0.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    str(&r1.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    str(&r2.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    str(&r3.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    load_counter ++;
    tmp = r4.i;
    ldr(&r0.i, &r4.i, 0, 4, false, false, false);
    r4.i += 4;
    ldr(&r1.i, &r4.i, 0, 4, false, false, false);
    r4.i += 4;
    ldr(&r2.i, &r4.i, 0, 4, false, false, false);
    r4.i += 4;
    r4.i = tmp;
    store_counter ++;
    tmp = ip.i;
    str(&r0.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    str(&r1.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    str(&r2.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    ip.i = tmp;
    r1.i = (LC1 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC1 >> 16) << 16);
    printf_help(malloc_0+r1.i, r2.i);
    counters[8] ++;
    r0.i = sp.i + (4);
    r1.i = 15;
    duplicateNumber();
    counters[9] ++;
    tmp = r0.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 1);
    v = (r0.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        goto L13;
    }
    counters[10] ++;
    r0.i = (LC4 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC4 >> 16) << 16);
    printf_help("%s\n", r0.i);
    counters[11] ++;
    r0.i = 0;
    sp.i = sp.i + (64);
    load_counter ++;
    ldr(&r4.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;
L13:
    counters[12] ++;
    r1.i = (LC2 & 0xffff);
    r0.i = (LC3 & 0xffff);
    r3.i = r4.i + (12);
    r1.i = r1.i | (((uint32_t)LC2 >> 16) << 16);
    r0.i = r0.i | (((uint32_t)LC3 >> 16) << 16);
    r2.i = 56;
    assert_help();
    return;
}

