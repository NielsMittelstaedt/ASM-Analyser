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

reg r5, r2, r4, r1, r3, r0;

int32_t LC1, LC2, LC3, LC4, LC5, L35, LC0, __PRETTY_FUNCTION__4824;

int counters[24] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[24] = {6,5,2,4,4,2,2,14,3,4,2,4,2,4,2,4,1,4,4,7,7,7,3,3};

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
    malloc_0 = (uint8_t*) malloc(20272);
    sp.i = 19996;
    fp = sp;
    LC1 = 20000;
    strcpy(malloc_0+LC1, "../test_files/c_in/sentinel_linear_search.c\000");

    LC2 = 20049;
    strcpy(malloc_0+LC2, "sentinel_linear_search( arr, n, 2 )==1\000");

    LC3 = 20093;
    strcpy(malloc_0+LC3, "sentinel_linear_search( arr, n, 6 )==3\000");

    LC4 = 20137;
    strcpy(malloc_0+LC4, "All test cases have successfully passed!\000");

    LC5 = 20183;
    strcpy(malloc_0+LC5, "sentinel_linear_search( arr, n, 101 )==-1\000");

    LC0 = 20230;
    int32_t arrayLC0[] = {1,2,2,6,99,100,999};
    for(int i=0; i<7; i++) str(&arrayLC0[i], &LC0, i*4, 4, false, false, false);

    L35 = 20258;
    int32_t arrayL35[] = {LC0};
    for(int i=0; i<1; i++) str(&arrayL35[i], &L35, i*4, 4, false, false, false);

    __PRETTY_FUNCTION__4824 = 20262;
    strcpy(malloc_0+__PRETTY_FUNCTION__4824, "test\000");

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "sentinel_linear_search.c";

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

void sentinel_linear_search();
void main();

void assert_help()
{
    __assert_fail(malloc_0+r0.i, malloc_0+r1.i, r2.i, malloc_0+r3.i);
}
void printf_help(const char *format, int32_t test)
{
    if (strstr(format, "%s") != NULL)
        printf(format, malloc_0 + test);
    else
        printf(format, test);
}

void sentinel_linear_search()
{
    counters[0] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r4.i, &sp.i, 0, 4, false, false, false);
    r4.i = r1.i - (-1073741823);
    lr.i = r1.i - (1);
    load_counter ++;
    ldr(&r5.i, &r0.i, ((uint32_t)r4.i << 2), 4, false, false, false);
    tmp = r5.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r2.i);
    v = (r5.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (z)
    {
        goto L5;
    }
    counters[1] ++;
    store_counter ++;
    str(&r2.i, &r0.i, ((uint32_t)r4.i << 2), 4, false, false, false);
    ip.i = r0.i;
    load_counter ++;
    ldr(&r3.i, &r0.i, 0, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (z)
    {
        goto L6;
    }
    counters[2] ++;
    r3.i = r0.i;
    r0.i = 0;
L4:
    counters[3] ++;
    load_counter ++;
    ldr(&r1.i, &r3.i, 4, 4, true, false, false);
    r0.i = r0.i + (1);
    tmp = r1.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r2.i);
    v = (r1.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!z)
    {
        goto L4;
    }
L3:
    counters[4] ++;
    tmp = r0.i - lr.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) lr.i);
    v = (r0.i&0x80000000) != (lr.i&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    store_counter ++;
    str(&r5.i, &ip.i, ((uint32_t)r4.i << 2), 4, false, false, false);
    if (z)
    {
        r0.i = ~0;
    }
    load_counter ++;
    ldr(&r4.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;
L5:
    counters[5] ++;
    r0.i = lr.i;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;
L6:
    counters[6] ++;
    r0.i = 0;
    goto L3;
    return;
}

void main()
{
    malloc_start();
    counters[7] ++;
    ip.i = (LC0 & 0xffff);
    ip.i = ip.i | (((uint32_t)LC0 >> 16) << 16);
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r4.i, &sp.i, 0, 4, false, false, false);
    sp.i = sp.i - (32);
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
    r4.i = 2;
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
    load_counter ++;
    ldr(&ip.i, &sp.i, 4, 4, false, false, false);
    tmp = ip.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r4.i);
    v = (ip.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    store_counter ++;
    tmp = lr.i;
    str(&r0.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    str(&r1.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    str(&r2.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    lr.i = tmp;
    store_counter ++;
    str(&r4.i, &sp.i, 20, 4, false, false, false);
    if (z)
    {
        goto L12;
    }
    counters[8] ++;
    r1.i = sp.i + (4);
    r3.i = 0;
    r2.i = r1.i;
L13:
    counters[9] ++;
    load_counter ++;
    ldr(&r0.i, &r2.i, 4, 4, true, false, false);
    r3.i = r3.i + (1);
    tmp = r0.i - 2;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 2);
    v = (r0.i&0x80000000) != (2&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        goto L13;
    }
    counters[10] ++;
    tmp = r3.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 1);
    v = (r3.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L12;
    }
    counters[11] ++;
    tmp = ip.i - 6;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) 6);
    v = (ip.i&0x80000000) != (6&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    r3.i = 6;
    store_counter ++;
    str(&r3.i, &sp.i, 20, 4, false, false, false);
    if (z)
    {
        goto L15;
    }
    counters[12] ++;
    r3.i = sp.i + (4);
    r2.i = 0;
L16:
    counters[13] ++;
    load_counter ++;
    ldr(&r0.i, &r3.i, 4, 4, true, false, false);
    r2.i = r2.i + (1);
    tmp = r0.i - 6;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 6);
    v = (r0.i&0x80000000) != (6&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        goto L16;
    }
    counters[14] ++;
    tmp = r2.i - 3;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) 3);
    v = (r2.i&0x80000000) != (3&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z)
    {
        goto L15;
    }
    counters[15] ++;
    tmp = ip.i - 101;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) 101);
    v = (ip.i&0x80000000) != (101&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    r3.i = 101;
    store_counter ++;
    str(&r3.i, &sp.i, 20, 4, false, false, false);
    if (z)
    {
        goto L18;
    }
    counters[16] ++;
    r3.i = 0;
L19:
    counters[17] ++;
    load_counter ++;
    ldr(&r2.i, &r1.i, 4, 4, true, false, false);
    r3.i = r3.i + (1);
    tmp = r2.i - 101;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) 101);
    v = (r2.i&0x80000000) != (101&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z)
    {
        goto L19;
    }
    counters[18] ++;
    tmp = r3.i - 4;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 4);
    v = (r3.i&0x80000000) != (4&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    r3.i = 99;
    store_counter ++;
    str(&r3.i, &sp.i, 20, 4, false, false, false);
    if (z)
    {
        goto L33;
    }
L18:
    counters[19] ++;
    r1.i = (LC1 & 0xffff);
    r0.i = (LC5 & 0xffff);
    load_counter ++;
    ldr(&r3.i, &L35, 0, 4, false, false, false);
    r1.i = r1.i | (((uint32_t)LC1 >> 16) << 16);
    r0.i = r0.i | (((uint32_t)LC5 >> 16) << 16);
    r2.i = 68;
    assert_help();
L12:
    counters[20] ++;
    r1.i = (LC1 & 0xffff);
    r0.i = (LC2 & 0xffff);
    load_counter ++;
    ldr(&r3.i, &L35, 0, 4, false, false, false);
    r1.i = r1.i | (((uint32_t)LC1 >> 16) << 16);
    r0.i = r0.i | (((uint32_t)LC2 >> 16) << 16);
    r2.i = 66;
    assert_help();
L15:
    counters[21] ++;
    r1.i = (LC1 & 0xffff);
    r0.i = (LC3 & 0xffff);
    load_counter ++;
    ldr(&r3.i, &L35, 0, 4, false, false, false);
    r1.i = r1.i | (((uint32_t)LC1 >> 16) << 16);
    r0.i = r0.i | (((uint32_t)LC3 >> 16) << 16);
    r2.i = 67;
    assert_help();
L33:
    counters[22] ++;
    r0.i = (LC4 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC4 >> 16) << 16);
    printf_help("%s\n", r0.i);
    counters[23] ++;
    r0.i = 0;
    sp.i = sp.i + (32);
    load_counter ++;
    ldr(&r4.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;

}

