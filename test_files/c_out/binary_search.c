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

int32_t LC1, LC2, LC3, LC4, LC5, LC6, LC7, L50, LC0, __PRETTY_FUNCTION__4832;

int counters[44] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[44] = {4,6,3,2,3,1,13,14,2,13,2,7,1,3,7,3,1,2,4,7,1,5,11,2,3,4,2,7,1,3,4,5,1,5,11,2,5,3,1,7,7,7,2,2};

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
    malloc_0 = (uint8_t*) malloc(20194);
    sp.i = 19996;
    fp = sp;
    LC1 = 20000;
    strcpy(malloc_0+LC1, "Test 1.... \000");

    LC2 = 20017;
    strcpy(malloc_0+LC2, "../test_files/c_in/binary_search.c\000");

    LC3 = 20057;
    strcpy(malloc_0+LC3, "result == 3\000");

    LC4 = 20074;
    strcpy(malloc_0+LC4, "passed recursive... \000");

    LC5 = 20100;
    strcpy(malloc_0+LC5, "passed iterative...\000");

    LC6 = 20125;
    strcpy(malloc_0+LC6, "Test 2.... \000");

    LC7 = 20142;
    strcpy(malloc_0+LC7, "result == -1\000");

    LC0 = 20160;
    int32_t arrayLC0[] = {2,3,4,10,40};
    for(int i=0; i<5; i++) str(&arrayLC0[i], &LC0, i*4, 4, false, false, false);

    L50 = 20180;
    int32_t arrayL50[] = {LC0};
    for(int i=0; i<1; i++) str(&arrayL50[i], &L50, i*4, 4, false, false, false);

    __PRETTY_FUNCTION__4832 = 20184;
    strcpy(malloc_0+__PRETTY_FUNCTION__4832, "test\000");

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "binary_search.c";

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

void binarysearch1();
void binarysearch2();
void test();
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

void binarysearch1()
{
    counters[0] ++;
    tmp = r1.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r2.i);
    v = (r1.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    store_counter ++;
    str(&lr.i, &sp.i, -4, 4, true, false, false);
    lr.i = r0.i;
    if (!z && n == v)
    {
        goto L8;
    }
L2:
    counters[1] ++;
    r0.i = r2.i - (r1.i);
    r0.i = r1.i + ((r0.i >> 1));
    load_counter ++;
    ldr(&ip.i, &lr.i, ((uint32_t)r0.i << 2), 4, false, false, false);
    tmp = ip.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r3.i);
    v = (ip.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    load_counter ++;
    if (z)
    {
        ldr(&pc.i, &sp.i, 4, 4, false, true, false);
        return;
    }
    if (z || n != v)
    {
        goto L4;
    }
    counters[2] ++;
    r2.i = r0.i - (1);
    tmp = r2.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r1.i);
    v = (r2.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n == v)
    {
        goto L2;
    }
L8:
    counters[3] ++;
    r0.i = ~0;
    load_counter ++;
    ldr(&pc.i, &sp.i, 4, 4, false, true, false);
    return;
L4:
    counters[4] ++;
    r1.i = r0.i + (1);
    tmp = r1.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r2.i);
    v = (r1.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (z || n != v)
    {
        goto L2;
    }
    counters[5] ++;
    goto L8;
    return;
}

void binarysearch2()
{
    counters[6] ++;
    ip.i = r2.i - (r1.i);
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r4.i, &sp.i, 0, 4, false, false, false);
    ip.i = ip.i + (((uint32_t)ip.i >> 31));
    r4.i = r0.i;
    r0.i = r1.i + ((ip.i >> 1));
    load_counter ++;
    ldr(&ip.i, &r4.i, ((uint32_t)r0.i << 2), 4, false, false, false);
    tmp = r3.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) ip.i);
    v = (r3.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    load_counter ++;
    if (z)
    {
        ldr(&r4.i, &sp.i, 0, 4, false, false, false);
        sp.i += 4;
        ldr(&pc.i, &sp.i, 0, 4, false, false, false);
        sp.i += 4;
        return;
    }
    tmp = r2.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r1.i);
    v = (r2.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z && n == v)
    {
        lr.i = 0;
    }
    if (z || n != v)
    {
        lr.i = 1;
    }
    c = r2.i & (1 << 31 - 1);
    lr.i = lr.i | ((uint32_t)r2.i >> 31);
    z = lr.i == 0;
    n = lr.i & 0x80000000;
    if (!z)
    {
        goto L17;
    }
L12:
    counters[7] ++;
    tmp = r3.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) ip.i);
    v = (r3.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (n == v)
    {
        r1.i = r0.i + (1);
    }
    if (n != v)
    {
        r2.i = r0.i - (1);
    }
    r0.i = r2.i - (r1.i);
    r0.i = r0.i + (((uint32_t)r0.i >> 31));
    r0.i = r1.i + ((r0.i >> 1));
    load_counter ++;
    ldr(&ip.i, &r4.i, ((uint32_t)r0.i << 2), 4, false, false, false);
    tmp = ip.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r3.i);
    v = (ip.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    load_counter ++;
    if (z)
    {
        ldr(&r4.i, &sp.i, 0, 4, false, false, false);
        sp.i += 4;
        ldr(&pc.i, &sp.i, 0, 4, false, false, false);
        sp.i += 4;
        return;
    }
    tmp = r1.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r2.i);
    v = (r1.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (n != v)
    {
        lr.i = 0;
    }
    if (n == v)
    {
        lr.i = 1;
    }
    c = r2.i & (1 << 31 - 1);
    lr.i = lr.i | ((uint32_t)r2.i >> 31);
    z = lr.i == 0;
    n = lr.i & 0x80000000;
    if (z)
    {
        goto L12;
    }
L17:
    counters[8] ++;
    r0.i = ~0;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;

}

void test()
{
    counters[9] ++;
    ip.i = (LC0 & 0xffff);
    ip.i = ip.i | (((uint32_t)LC0 >> 16) << 16);
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r4.i, &sp.i, 0, 4, false, false, false);
    sp.i = sp.i - (24);
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
    load_counter ++;
    ldr(&ip.i, &ip.i, 0, 4, false, false, false);
    store_counter ++;
    str(&r0.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    str(&r1.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    str(&r2.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    str(&r3.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    r1.i = (LC1 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC1 >> 16) << 16);
    store_counter ++;
    str(&ip.i, &lr.i, 0, 4, false, false, false);
    printf_help(malloc_0+r1.i, r2.i);
    counters[10] ++;
    r2.i = 0;
    r1.i = 4;
L21:
    counters[11] ++;
    r3.i = r1.i - (r2.i);
    r0.i = sp.i + (24);
    r3.i = r2.i + ((r3.i >> 1));
    r0.i = r0.i + (((uint32_t)r3.i << 2));
    load_counter ++;
    ldr(&r0.i, &r0.i, -20, 4, false, false, false);
    tmp = r0.i - 10;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 10);
    v = (r0.i&0x80000000) != (10&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (z)
    {
        goto L22;
    }
    counters[12] ++;
    if (z || n != v)
    {
        goto L23;
    }
    counters[13] ++;
    r1.i = r3.i - (1);
    tmp = r1.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r2.i);
    v = (r1.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (n == v)
    {
        goto L21;
    }
L25:
    counters[14] ++;
    r1.i = (LC2 & 0xffff);
    r0.i = (LC3 & 0xffff);
    load_counter ++;
    ldr(&r3.i, &L50, 0, 4, false, false, false);
    r1.i = r1.i | (((uint32_t)LC2 >> 16) << 16);
    r0.i = r0.i | (((uint32_t)LC3 >> 16) << 16);
    r2.i = 87;
    assert_help();
L23:
    counters[15] ++;
    r2.i = r3.i + (1);
    tmp = r2.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r1.i);
    v = (r2.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (z || n != v)
    {
        goto L21;
    }
    counters[16] ++;
    goto L25;
L22:
    counters[17] ++;
    tmp = r3.i - 3;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 3);
    v = (r3.i&0x80000000) != (3&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L25;
    }
    counters[18] ++;
    r1.i = (LC4 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC4 >> 16) << 16);
    printf_help(malloc_0+r1.i, r2.i);
    counters[19] ++;
    load_counter ++;
    ldr(&r4.i, &sp.i, 12, 4, false, false, false);
    tmp = r4.i - 10;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 10);
    v = (r4.i&0x80000000) != (10&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        r0.i = r4.i;
    }
    if (!z)
    {
        r3.i = 2;
    }
    if (!z)
    {
        r1.i = 4;
    }
    if (!z)
    {
        r2.i = 0;
    }
    if (!z)
    {
        goto L27;
    }
    counters[20] ++;
    goto L28;
L31:
    counters[21] ++;
    tmp = r1.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r2.i);
    v = (r1.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!z && n == v)
    {
        ip.i = 0;
    }
    if (z || n != v)
    {
        ip.i = 1;
    }
    c = r1.i & (1 << 31 - 1);
    ip.i = ip.i | ((uint32_t)r1.i >> 31);
    z = ip.i == 0;
    n = ip.i & 0x80000000;
    if (!z)
    {
        goto L28;
    }
L27:
    counters[22] ++;
    tmp = r0.i - 10;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 10);
    v = (r0.i&0x80000000) != (10&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    r0.i = sp.i + (24);
    if (z || n != v)
    {
        r2.i = r3.i + (1);
    }
    if (!z && n == v)
    {
        r1.i = r3.i - (1);
    }
    r3.i = r1.i - (r2.i);
    r3.i = r3.i + (((uint32_t)r3.i >> 31));
    r3.i = r2.i + ((r3.i >> 1));
    r0.i = r0.i + (((uint32_t)r3.i << 2));
    load_counter ++;
    ldr(&r0.i, &r0.i, -20, 4, false, false, false);
    tmp = r0.i - 10;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 10);
    v = (r0.i&0x80000000) != (10&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        goto L31;
    }
    counters[23] ++;
    tmp = r3.i - 3;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 3);
    v = (r3.i&0x80000000) != (3&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L28;
    }
    counters[24] ++;
    r0.i = (LC5 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC5 >> 16) << 16);
    printf_help("%s\n", r0.i);
    counters[25] ++;
    r1.i = (LC6 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC6 >> 16) << 16);
    printf_help(malloc_0+r1.i, r2.i);
    counters[26] ++;
    r2.i = 0;
    r1.i = 4;
L33:
    counters[27] ++;
    r3.i = r1.i - (r2.i);
    r0.i = sp.i + (24);
    r3.i = r2.i + ((r3.i >> 1));
    r0.i = r0.i + (((uint32_t)r3.i << 2));
    load_counter ++;
    ldr(&r0.i, &r0.i, -20, 4, false, false, false);
    tmp = r0.i - 5;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 5);
    v = (r0.i&0x80000000) != (5&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (z)
    {
        goto L34;
    }
    counters[28] ++;
    if (z || n != v)
    {
        goto L35;
    }
    counters[29] ++;
    r1.i = r3.i - (1);
    tmp = r1.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r2.i);
    v = (r1.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (n == v)
    {
        goto L33;
    }
L37:
    counters[30] ++;
    r1.i = (LC4 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC4 >> 16) << 16);
    printf_help(malloc_0+r1.i, r2.i);
    counters[31] ++;
    tmp = r4.i - 5;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 5);
    v = (r4.i&0x80000000) != (5&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        r3.i = 2;
    }
    if (!z)
    {
        r1.i = 4;
    }
    if (!z)
    {
        r2.i = 0;
    }
    if (!z)
    {
        goto L42;
    }
    counters[32] ++;
    goto L43;
L41:
    counters[33] ++;
    tmp = r1.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r2.i);
    v = (r1.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!z && n == v)
    {
        r0.i = 0;
    }
    if (z || n != v)
    {
        r0.i = 1;
    }
    c = r1.i & (1 << 31 - 1);
    r0.i = r0.i | ((uint32_t)r1.i >> 31);
    z = r0.i == 0;
    n = r0.i & 0x80000000;
    if (!z)
    {
        goto L38;
    }
L42:
    counters[34] ++;
    tmp = r4.i - 5;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 5);
    v = (r4.i&0x80000000) != (5&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    r0.i = sp.i + (24);
    if (z || n != v)
    {
        r2.i = r3.i + (1);
    }
    if (!z && n == v)
    {
        r1.i = r3.i - (1);
    }
    r3.i = r1.i - (r2.i);
    r3.i = r3.i + (((uint32_t)r3.i >> 31));
    r3.i = r2.i + ((r3.i >> 1));
    r0.i = r0.i + (((uint32_t)r3.i << 2));
    load_counter ++;
    ldr(&r4.i, &r0.i, -20, 4, false, false, false);
    tmp = r4.i - 5;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 5);
    v = (r4.i&0x80000000) != (5&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        goto L41;
    }
    counters[35] ++;
    tmp = r3.i + 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) tmp) < ((uint32_t) r3.i);
    v = (r3.i&0x80000000) == (1&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L43;
    }
L38:
    counters[36] ++;
    r0.i = (LC5 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC5 >> 16) << 16);
    sp.i = sp.i + (24);
    load_counter ++;
    ldr(&r4.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    printf_help("%s\n", r0.i);
    return;
L35:
    counters[37] ++;
    r2.i = r3.i + (1);
    tmp = r2.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r1.i);
    v = (r2.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (z || n != v)
    {
        goto L33;
    }
    counters[38] ++;
    goto L37;
L28:
    counters[39] ++;
    r1.i = (LC2 & 0xffff);
    r0.i = (LC3 & 0xffff);
    load_counter ++;
    ldr(&r3.i, &L50, 0, 4, false, false, false);
    r1.i = r1.i | (((uint32_t)LC2 >> 16) << 16);
    r0.i = r0.i | (((uint32_t)LC3 >> 16) << 16);
    r2.i = 90;
    assert_help();
L43:
    counters[40] ++;
    r1.i = (LC2 & 0xffff);
    r0.i = (LC7 & 0xffff);
    load_counter ++;
    ldr(&r3.i, &L50, 0, 4, false, false, false);
    r1.i = r1.i | (((uint32_t)LC2 >> 16) << 16);
    r0.i = r0.i | (((uint32_t)LC7 >> 16) << 16);
    r2.i = 100;
    assert_help();
L34:
    counters[41] ++;
    r1.i = (LC2 & 0xffff);
    r0.i = (LC7 & 0xffff);
    load_counter ++;
    ldr(&r3.i, &L50, 0, 4, false, false, false);
    r1.i = r1.i | (((uint32_t)LC2 >> 16) << 16);
    r0.i = r0.i | (((uint32_t)LC7 >> 16) << 16);
    r2.i = 97;
    assert_help();
    return;
}

void main()
{
    malloc_start();
    counters[42] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r4.i, &sp.i, 0, 4, false, false, false);
    test();
    counters[43] ++;
    r0.i = 0;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;

}

