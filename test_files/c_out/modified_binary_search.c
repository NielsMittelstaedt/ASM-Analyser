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

reg r2, r3, r0, r4, r1;

int32_t LC0, LC1, LC2, LC3;

int counters[60] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[60] = {8,19,5,2,12,4,3,4,3,1,3,10,9,1,11,19,5,1,12,3,2,5,12,5,1,13,7,1,13,9,1,13,13,10,1,14,10,1,11,2,9,4,5,8,5,4,3,3,12,3,4,3,4,5,3,7,3,4,2,4};


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
    malloc_0 = (uint8_t*) malloc(20075);
    sp.i = 19996;
    fp = sp;
    LC0 = 20000;
    strcpy(malloc_0+LC0, "Found at (%d,%d)\012\000");

    LC1 = 20026;
    strcpy(malloc_0+LC1, "element not found\000");

    LC2 = 20049;
    strcpy(malloc_0+LC2, "%d %d %d\012\000");

    LC3 = 20067;
    strcpy(malloc_0+LC3, "%d\000");

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "modified_binary_search.c";

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

void binarySearch();
void modifiedBinarySearch();
void main();

void free_help()
{
    free(malloc_0+r0.i);
}
void scanf_help()
{
    scanf(malloc_0+r0.i, malloc_0+r1.i);
}
void printf_help(const char *format, int32_t test)
{
    if (strstr(format, "%s") != NULL)
        printf(format, malloc_0 + test);
    else
        printf(format, test);
}
void malloc_help()
{
    uint8_t* ptr = (uint8_t*) malloc(r0.i);
    r0.i = (int32_t) (ptr - malloc_0);
}

void binarySearch()
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
    str(&r0.i, &fp.i, -16, 4, false, false, false);
    store_counter ++;
    str(&r1.i, &fp.i, -20, 4, false, false, false);
    store_counter ++;
    str(&r2.i, &fp.i, -24, 4, false, false, false);
    store_counter ++;
    str(&r3.i, &fp.i, -28, 4, false, false, false);
    goto L2;
L6:
    counters[1] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -24, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -28, 4, false, false, false);
    r3.i = r2.i + (r3.i);
    r2.i = (uint32_t)r3.i >> 31;
    r3.i = r2.i + (r3.i);
    r3.i = r3.i >> 1;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -16, 4, false, false, false);
    r3.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r2.i, &r3.i, 0, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, 4, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z)
    {
        goto L3;
    }
    counters[2] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -8, 4, false, false, false);
    load_counter ++;
    ldr(&r1.i, &fp.i, -20, 4, false, false, false);
    r0.i = (LC0 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC0 >> 16) << 16);
    printf_help(malloc_0+r0.i, r1.i);
    counters[3] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    goto L4;
L3:
    counters[4] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -16, 4, false, false, false);
    r3.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r2.i, &r3.i, 0, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, 4, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n == v)
    {
        goto L5;
    }
    counters[5] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = r3.i - (1);
    store_counter ++;
    str(&r3.i, &fp.i, -28, 4, false, false, false);
    goto L2;
L5:
    counters[6] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = r3.i + (1);
    store_counter ++;
    str(&r3.i, &fp.i, -24, 4, false, false, false);
L2:
    counters[7] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -24, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -28, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (z || n != v)
    {
        goto L6;
    }
    counters[8] ++;
    r0.i = (LC1 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC1 >> 16) << 16);
    printf_help("%s\n", r0.i);
    counters[9] ++;
    r3.i = ~0;
L4:
    counters[10] ++;
    r0.i = r3.i;
    sp.i = fp.i - (4);
    load_counter ++;
    ldr(&fp.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;

}

void modifiedBinarySearch()
{
    counters[11] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&fp.i, &sp.i, 0, 4, false, false, false);
    fp.i = sp.i + (4);
    sp.i = sp.i - (40);
    store_counter ++;
    str(&r0.i, &fp.i, -24, 4, false, false, false);
    store_counter ++;
    str(&r1.i, &fp.i, -28, 4, false, false, false);
    store_counter ++;
    str(&r2.i, &fp.i, -32, 4, false, false, false);
    store_counter ++;
    str(&r3.i, &fp.i, -36, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -28, 4, false, false, false);
    tmp = r3.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 1);
    v = (r3.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L8;
    }
    counters[12] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -32, 4, false, false, false);
    r2.i = r3.i - (1);
    load_counter ++;
    ldr(&r3.i, &fp.i, -36, 4, false, false, false);
    store_counter ++;
    str(&r3.i, &sp.i, 0, 4, false, false, false);
    r3.i = r2.i;
    r2.i = 0;
    r1.i = 0;
    load_counter ++;
    ldr(&r0.i, &fp.i, -24, 4, false, false, false);
    binarySearch();
    counters[13] ++;
    goto L7;
L8:
    counters[14] ++;
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -28, 4, false, false, false);
    r3.i = r3.i - (1);
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -32, 4, false, false, false);
    r2.i = (uint32_t)r3.i >> 31;
    r3.i = r2.i + (r3.i);
    r3.i = r3.i >> 1;
    store_counter ++;
    str(&r3.i, &fp.i, -16, 4, false, false, false);
    goto L10;
L13:
    counters[15] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -8, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false, false);
    r3.i = r2.i + (r3.i);
    r2.i = (uint32_t)r3.i >> 31;
    r3.i = r2.i + (r3.i);
    r3.i = r3.i >> 1;
    store_counter ++;
    str(&r3.i, &fp.i, -20, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -24, 4, false, false, false);
    r3.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r2.i, &r3.i, 0, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -36, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z)
    {
        goto L11;
    }
    counters[16] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -16, 4, false, false, false);
    load_counter ++;
    ldr(&r1.i, &fp.i, -20, 4, false, false, false);
    r0.i = (LC0 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC0 >> 16) << 16);
    printf_help(malloc_0+r0.i, r1.i);
    counters[17] ++;
    goto L7;
L11:
    counters[18] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -24, 4, false, false, false);
    r3.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r2.i, &r3.i, 0, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -36, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n == v)
    {
        goto L12;
    }
    counters[19] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false, false);
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false, false);
    goto L10;
L12:
    counters[20] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false, false);
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
L10:
    counters[21] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = r3.i + (1);
    load_counter ++;
    ldr(&r2.i, &fp.i, -12, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z && n == v)
    {
        goto L13;
    }
    counters[22] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -24, 4, false, false, false);
    r3.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r2.i, &r3.i, 0, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -36, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z)
    {
        goto L14;
    }
    counters[23] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -16, 4, false, false, false);
    load_counter ++;
    ldr(&r1.i, &fp.i, -8, 4, false, false, false);
    r0.i = (LC0 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC0 >> 16) << 16);
    printf_help(malloc_0+r0.i, r1.i);
    counters[24] ++;
    goto L7;
L14:
    counters[25] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = r3.i + (1);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -24, 4, false, false, false);
    r3.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r2.i, &r3.i, 0, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -36, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z)
    {
        goto L15;
    }
    counters[26] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = r3.i + (1);
    load_counter ++;
    ldr(&r2.i, &fp.i, -16, 4, false, false, false);
    r1.i = r3.i;
    r0.i = (LC0 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC0 >> 16) << 16);
    printf_help(malloc_0+r0.i, r1.i);
    counters[27] ++;
    goto L7;
L15:
    counters[28] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -24, 4, false, false, false);
    r3.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r2.i, &r3.i, 0, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false, false);
    r3.i = r3.i - (-1073741823);
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -36, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z && n == v)
    {
        goto L16;
    }
    counters[29] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false, false);
    r2.i = r3.i - (1);
    load_counter ++;
    ldr(&r3.i, &fp.i, -36, 4, false, false, false);
    store_counter ++;
    str(&r3.i, &sp.i, 0, 4, false, false, false);
    r3.i = r2.i;
    r2.i = 0;
    load_counter ++;
    ldr(&r1.i, &fp.i, -8, 4, false, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, -24, 4, false, false, false);
    binarySearch();
    counters[30] ++;
    goto L7;
L16:
    counters[31] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -24, 4, false, false, false);
    r3.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r2.i, &r3.i, 0, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false, false);
    r3.i = r3.i + (1);
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -36, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n != v)
    {
        goto L17;
    }
    counters[32] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -24, 4, false, false, false);
    r3.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r2.i, &r3.i, 0, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -32, 4, false, false, false);
    r3.i = r3.i - (-1073741823);
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -36, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z && n == v)
    {
        goto L17;
    }
    counters[33] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false, false);
    r2.i = r3.i + (1);
    load_counter ++;
    ldr(&r3.i, &fp.i, -32, 4, false, false, false);
    r1.i = r3.i - (1);
    load_counter ++;
    ldr(&r3.i, &fp.i, -36, 4, false, false, false);
    store_counter ++;
    str(&r3.i, &sp.i, 0, 4, false, false, false);
    r3.i = r1.i;
    load_counter ++;
    ldr(&r1.i, &fp.i, -8, 4, false, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, -24, 4, false, false, false);
    binarySearch();
    counters[34] ++;
    goto L7;
L17:
    counters[35] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = r3.i + (1);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -24, 4, false, false, false);
    r3.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r2.i, &r3.i, 0, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false, false);
    r3.i = r3.i - (-1073741823);
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -36, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z && n == v)
    {
        goto L18;
    }
    counters[36] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r1.i = r3.i + (1);
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false, false);
    r2.i = r3.i - (1);
    load_counter ++;
    ldr(&r3.i, &fp.i, -36, 4, false, false, false);
    store_counter ++;
    str(&r3.i, &sp.i, 0, 4, false, false, false);
    r3.i = r2.i;
    r2.i = 0;
    load_counter ++;
    ldr(&r0.i, &fp.i, -24, 4, false, false, false);
    binarySearch();
    counters[37] ++;
    goto L7;
L18:
    counters[38] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r1.i = r3.i + (1);
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false, false);
    r2.i = r3.i + (1);
    load_counter ++;
    ldr(&r3.i, &fp.i, -32, 4, false, false, false);
    r0.i = r3.i - (1);
    load_counter ++;
    ldr(&r3.i, &fp.i, -36, 4, false, false, false);
    store_counter ++;
    str(&r3.i, &sp.i, 0, 4, false, false, false);
    r3.i = r0.i;
    load_counter ++;
    ldr(&r0.i, &fp.i, -24, 4, false, false, false);
    binarySearch();
L7:
    counters[39] ++;
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
    counters[40] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&fp.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r4.i, &sp.i, 0, 4, false, false, false);
    fp.i = sp.i + (8);
    sp.i = sp.i - (36);
    r3.i = fp.i - (36);
    r2.i = fp.i - (40);
    r1.i = fp.i - (44);
    r0.i = (LC2 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC2 >> 16) << 16);
    scanf_help();
    counters[41] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -44, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    r0.i = r3.i;
    malloc_help();
    counters[42] ++;
    r3.i = r0.i;
    store_counter ++;
    str(&r3.i, &fp.i, -32, 4, false, false, false);
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -16, 4, false, false, false);
    goto L20;
L21:
    counters[43] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -40, 4, false, false, false);
    r1.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -32, 4, false, false, false);
    r4.i = r2.i + (r3.i);
    r0.i = r1.i;
    malloc_help();
    counters[44] ++;
    r3.i = r0.i;
    store_counter ++;
    str(&r3.i, &r4.i, 0, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false, false);
    r3.i = r3.i + (1);
    store_counter ++;
    str(&r3.i, &fp.i, -16, 4, false, false, false);
L20:
    counters[45] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -40, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -16, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n != v)
    {
        goto L21;
    }
    counters[46] ++;
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -20, 4, false, false, false);
    goto L22;
L25:
    counters[47] ++;
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -24, 4, false, false, false);
    goto L23;
L24:
    counters[48] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -32, 4, false, false, false);
    r3.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r2.i, &r3.i, 0, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -24, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r2.i + (r3.i);
    r1.i = r3.i;
    r0.i = (LC3 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC3 >> 16) << 16);
    scanf_help();
    counters[49] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -24, 4, false, false, false);
    r3.i = r3.i + (1);
    store_counter ++;
    str(&r3.i, &fp.i, -24, 4, false, false, false);
L23:
    counters[50] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -40, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -24, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n != v)
    {
        goto L24;
    }
    counters[51] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false, false);
    r3.i = r3.i + (1);
    store_counter ++;
    str(&r3.i, &fp.i, -20, 4, false, false, false);
L22:
    counters[52] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -44, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -20, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n != v)
    {
        goto L25;
    }
    counters[53] ++;
    load_counter ++;
    ldr(&r1.i, &fp.i, -44, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -40, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -36, 4, false, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, -32, 4, false, false, false);
    modifiedBinarySearch();
    counters[54] ++;
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -28, 4, false, false, false);
    goto L26;
L27:
    counters[55] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -28, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -32, 4, false, false, false);
    r3.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, false, false);
    r0.i = r3.i;
    free_help();
    counters[56] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -28, 4, false, false, false);
    r3.i = r3.i + (1);
    store_counter ++;
    str(&r3.i, &fp.i, -28, 4, false, false, false);
L26:
    counters[57] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -44, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -28, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n != v)
    {
        goto L27;
    }
    counters[58] ++;
    load_counter ++;
    ldr(&r0.i, &fp.i, -32, 4, false, false, false);
    free_help();
    counters[59] ++;
    r3.i = 0;
    r0.i = r3.i;
    sp.i = fp.i - (8);
    load_counter ++;
    ldr(&r4.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&fp.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    counter_summary();
    return;

}

