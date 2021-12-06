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

reg r5, r2, r4, r1, r3, r6, r8, r0, r7;

int32_t LC1, LC2, LC3, LC4, LC5, LC0;

int counters[19] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[19] = {6,1,4,1,5,2,2,6,2,21,4,2,4,4,3,4,3,3,1};

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
    malloc_0 = (uint8_t*) malloc(20188);
    sp.i = 19996;
    fp = sp;
    LC1 = 20000;
    strcpy(malloc_0+LC1, "Array: \000");

    LC2 = 20013;
    strcpy(malloc_0+LC2, "%d \000");

    LC3 = 20022;
    strcpy(malloc_0+LC3, "\012Enter the number to be searched: \000");

    LC4 = 20065;
    strcpy(malloc_0+LC4, "Element found at position: %d\012\000");

    LC5 = 20104;
    strcpy(malloc_0+LC5, "Element not found.\000");

    LC0 = 20128;
    int32_t arrayLC0[] = {10,12,13,16,18,19,20,21,22,23,24,33,35,42,47};
    for(int i=0; i<15; i++) str(&arrayLC0[i], &LC0, i*4, 4, false, false, false);

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "interpolation_search.c";

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

void interpolationSearch();
void main();

void printf_help(const char *format, int32_t test)
{
    if (strstr(format, "%s") != NULL)
        printf(format, malloc_0 + test);
    else
        printf(format, test);
}
void idiv()
{
    r0.i = r0.i / r1.i;
}

void interpolationSearch()
{
    counters[0] ++;
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
    r6.i = r1.i - (1);
    z = r6.i == 0;
    n = r6.i & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 1);
    v = (r1.i&0x80000000) != (1&0x80000000) && (r6.i&0x80000000) != (r1.i&0x80000000);
    if (!n)
    {
        r7.i = r0.i;
    }
    if (!n)
    {
        r5.i = r2.i;
    }
    if (!n)
    {
        r4.i = 0;
    }
    if (!n)
    {
        goto L2;
    }
    counters[1] ++;
    goto L9;
L12:
    counters[2] ++;
    load_counter ++;
    ldr(&r3.i, &r7.i, ((uint32_t)r6.i << 2), 4, false, false, false);
    tmp = r3.i - r5.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r5.i);
    v = (r3.i&0x80000000) != (r5.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    r1.i = r3.i - (r1.i);
    if (n != v)
    {
        goto L9;
    }
    counters[3] ++;
    idiv();
    counters[4] ++;
    r0.i = r0.i + (r4.i);
    load_counter ++;
    ldr(&r3.i, &r7.i, ((uint32_t)r0.i << 2), 4, false, false, false);
    tmp = r3.i - r5.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r5.i);
    v = (r3.i&0x80000000) != (r5.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (n != v)
    {
        r4.i = r0.i + (1);
    }
    if (n != v)
    {
        goto L5;
    }
    counters[5] ++;
    r6.i = r0.i - (1);
    load_counter ++;
    if (z || n != v)
    {
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
        return;
    }
L5:
    counters[6] ++;
    tmp = r6.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) r4.i);
    v = (r6.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    if (n != v)
    {
        goto L9;
    }
L2:
    counters[7] ++;
    load_counter ++;
    ldr(&r1.i, &r7.i, ((uint32_t)r4.i << 2), 4, false, false, false);
    r3.i = r6.i - (r4.i);
    r0.i = r5.i - (r1.i);
    tmp = r1.i - r5.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r5.i);
    v = (r1.i&0x80000000) != (r5.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    r0.i = (r3.i) * (r0.i);
    if (z || n != v)
    {
        goto L12;
    }
L9:
    counters[8] ++;
    r0.i = ~0;
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
    return;

}

void main()
{
    malloc_start();
    counters[9] ++;
    ip.i = (LC0 & 0xffff);
    ip.i = ip.i | (((uint32_t)LC0 >> 16) << 16);
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r6.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r4.i, &sp.i, 0, 4, false, false, false);
    sp.i = sp.i - (64);
    load_counter ++;
    ldr(&r0.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    ldr(&r1.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    ldr(&r2.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    ldr(&r3.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    lr.i = sp.i + (4);
    r5.i = (LC2 & 0xffff);
    r6.i = sp.i + (60);
    r5.i = r5.i | (((uint32_t)LC2 >> 16) << 16);
    r4.i = sp.i;
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
    ldr(&r0.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    ldr(&r1.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    ldr(&r2.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    ldr(&r3.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
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
    ldr(&r0.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    ldr(&r1.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    ldr(&r2.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    ldr(&r3.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
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
    ip.i = tmp;
    store_counter ++;
    tmp = lr.i;
    str(&r0.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    str(&r1.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    str(&r2.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    lr.i = tmp;
    r1.i = (LC1 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC1 >> 16) << 16);
    printf_help(malloc_0+r1.i, r2.i);
L14:
    counters[10] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 4, 4, true, false, false);
    r1.i = r5.i;
    r0.i = 1;
    printf_help(malloc_0+r1.i, r2.i);
    counters[11] ++;
    tmp = r4.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r6.i);
    v = (r4.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        goto L14;
    }
    counters[12] ++;
    r1.i = (LC3 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC3 >> 16) << 16);
    printf_help(malloc_0+r1.i, r2.i);
    counters[13] ++;
    r2.i = 42;
    r0.i = sp.i + (4);
    r1.i = 15;
    interpolationSearch();
    counters[14] ++;
    tmp = r0.i + 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) tmp) < ((uint32_t) r0.i);
    v = (r0.i&0x80000000) == (1&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    r2.i = r0.i;
    if (z)
    {
        goto L15;
    }
    counters[15] ++;
    r1.i = (LC4 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC4 >> 16) << 16);
    printf_help(malloc_0+r1.i, r2.i);
L16:
    counters[16] ++;
    r0.i = 0;
    sp.i = sp.i + (64);
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
L15:
    counters[17] ++;
    r0.i = (LC5 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC5 >> 16) << 16);
    printf_help("%s\n", r0.i);
    counters[18] ++;
    goto L16;
    return;
}

