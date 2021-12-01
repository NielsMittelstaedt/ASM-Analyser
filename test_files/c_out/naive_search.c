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

reg r2, r1, r3, r0;

int32_t LC0, LC3, LC4, LC5, LC6, LC1, LC2;

int counters[22] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[22] = {7,4,5,3,13,3,4,1,1,4,4,3,6,4,30,5,5,5,5,5,5,4};


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
    malloc_0 = (uint8_t*) malloc(20204);
    sp.i = 19996;
    fp = sp;
    LC0 = 20000;
    strcpy(malloc_0+LC0, "--Pattern is found at: %d\012\000");

    LC3 = 20035;
    strcpy(malloc_0+LC3, "String test: %s\012\000");

    LC4 = 20060;
    strcpy(malloc_0+LC4, "Test1: search pattern %s\012\000");

    LC5 = 20094;
    strcpy(malloc_0+LC5, "Test2: search pattern %s\012\000");

    LC6 = 20128;
    strcpy(malloc_0+LC6, "Test3: search pattern %s\012\000");

    LC1 = 20162;
    strcpy(malloc_0+LC1, "AABCAB12AFAABCABFFEGABCAB\000");

    LC2 = 20193;
    strcpy(malloc_0+LC2, "ABCAB\000");

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "naive_search.c";

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

void naive_search();
void main();

void strlen_help()
{
    r0.i = (int32_t) strlen(malloc_0+r0.i);
}
void printf_help(const char *format, int32_t test)
{
    if (strstr(format, "%s") != NULL)
        printf(format, malloc_0 + test);
    else
        printf(format, test);
}

void naive_search()
{
    counters[0] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&fp.i, &sp.i, 0, 4, false, false, false);
    fp.i = sp.i + (4);
    sp.i = sp.i - (24);
    store_counter ++;
    str(&r0.i, &fp.i, -24, 4, false, false, false);
    store_counter ++;
    str(&r1.i, &fp.i, -28, 4, false, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, -24, 4, false, false, false);
    strlen_help();
    counters[1] ++;
    r3.i = r0.i;
    store_counter ++;
    str(&r3.i, &fp.i, -16, 4, false, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, -28, 4, false, false, false);
    strlen_help();
    counters[2] ++;
    r3.i = r0.i;
    store_counter ++;
    str(&r3.i, &fp.i, -20, 4, false, false, false);
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
    goto L2;
L8:
    counters[3] ++;
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false, false);
    goto L3;
L6:
    counters[4] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -8, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false, false);
    r3.i = r2.i + (r3.i);
    r2.i = r3.i;
    load_counter ++;
    ldr(&r3.i, &fp.i, -24, 4, false, false, false);
    r3.i = r3.i + (r2.i);
    load_counter ++;
    ldr(&r2.i, &r3.i, 0, 1, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false, false);
    load_counter ++;
    ldr(&r1.i, &fp.i, -28, 4, false, false, false);
    r3.i = r1.i + (r3.i);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 1, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z)
    {
        goto L9;
    }
    counters[5] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false, false);
    r3.i = r3.i + (1);
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false, false);
L3:
    counters[6] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -12, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n != v)
    {
        goto L6;
    }
    counters[7] ++;
    goto L5;
L9:
    counters[8] ++;
L5:
    counters[9] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -12, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z)
    {
        goto L7;
    }
    counters[10] ++;
    load_counter ++;
    ldr(&r1.i, &fp.i, -8, 4, false, false, false);
    r0.i = (LC0 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC0 >> 16) << 16);
    printf_help(malloc_0+r0.i, r1.i);
L7:
    counters[11] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = r3.i + (1);
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
L2:
    counters[12] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -16, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false, false);
    r3.i = r2.i - (r3.i);
    load_counter ++;
    ldr(&r2.i, &fp.i, -8, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (z || n != v)
    {
        goto L8;
    }
    counters[13] ++;
    sp.i = fp.i - (4);
    load_counter ++;
    ldr(&fp.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;

}

void main()
{
    malloc_start();
    counters[14] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&fp.i, &sp.i, 0, 4, false, false, false);
    fp.i = sp.i + (4);
    sp.i = sp.i - (48);
    r3.i = (LC1 & 0xffff);
    r3.i = r3.i | (((uint32_t)LC1 >> 16) << 16);
    ip.i = fp.i - (32);
    lr.i = r3.i;
    load_counter ++;
    ldr(&r0.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    ldr(&r1.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    ldr(&r2.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    ldr(&r3.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
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
    tmp = lr.i;
    ldr(&r0.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    ldr(&r1.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    ldr(&r2.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    lr.i = tmp;
    store_counter ++;
    str(&r0.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    str(&r1.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    store_counter ++;
    str(&r2.i, &ip.i, 0, 2, false, false, false);
    r2.i = (LC2 & 0xffff);
    r2.i = r2.i | (((uint32_t)LC2 >> 16) << 16);
    r3.i = fp.i - (40);
    load_counter ++;
    tmp = r2.i;
    ldr(&r0.i, &r2.i, 0, 4, false, false, false);
    r2.i += 4;
    ldr(&r1.i, &r2.i, 0, 4, false, false, false);
    r2.i += 4;
    r2.i = tmp;
    store_counter ++;
    str(&r0.i, &r3.i, 0, 4, false, false, false);
    r3.i = r3.i + (4);
    store_counter ++;
    str(&r1.i, &r3.i, 0, 2, false, false, false);
    r3.i = 17990;
    r3.i = r3.i | (70 << 16);
    store_counter ++;
    str(&r3.i, &fp.i, -44, 4, false, false, false);
    r3.i = 16707;
    r3.i = r3.i | (66 << 16);
    store_counter ++;
    str(&r3.i, &fp.i, -48, 4, false, false, false);
    r3.i = fp.i - (32);
    r1.i = r3.i;
    r0.i = (LC3 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC3 >> 16) << 16);
    printf_help(malloc_0+r0.i, r1.i);
    counters[15] ++;
    r3.i = fp.i - (40);
    r1.i = r3.i;
    r0.i = (LC4 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC4 >> 16) << 16);
    printf_help(malloc_0+r0.i, r1.i);
    counters[16] ++;
    r2.i = fp.i - (40);
    r3.i = fp.i - (32);
    r1.i = r2.i;
    r0.i = r3.i;
    naive_search();
    counters[17] ++;
    r3.i = fp.i - (44);
    r1.i = r3.i;
    r0.i = (LC5 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC5 >> 16) << 16);
    printf_help(malloc_0+r0.i, r1.i);
    counters[18] ++;
    r2.i = fp.i - (44);
    r3.i = fp.i - (32);
    r1.i = r2.i;
    r0.i = r3.i;
    naive_search();
    counters[19] ++;
    r3.i = fp.i - (48);
    r1.i = r3.i;
    r0.i = (LC6 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC6 >> 16) << 16);
    printf_help(malloc_0+r0.i, r1.i);
    counters[20] ++;
    r2.i = fp.i - (48);
    r3.i = fp.i - (32);
    r1.i = r2.i;
    r0.i = r3.i;
    naive_search();
    counters[21] ++;
    r3.i = 0;
    r0.i = r3.i;
    sp.i = fp.i - (4);
    load_counter ++;
    ldr(&fp.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    counter_summary();
    return;

}

