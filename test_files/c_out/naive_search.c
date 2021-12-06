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

reg r9, r5, r2, r4, r1, r10, r3, r6, r8, r0, r7;

int32_t LC0, LC3, LC4, LC5, LC6, LC7, LC1, LC2;

int counters[21] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[21] = {4,3,8,5,1,2,7,3,1,2,4,1,24,5,5,3,5,3,5,3,3};

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
    malloc_0 = (uint8_t*) malloc(20214);
    sp.i = 19996;
    fp = sp;
    LC0 = 20000;
    strcpy(malloc_0+LC0, "--Pattern is found at: %d\012\000");

    LC3 = 20035;
    strcpy(malloc_0+LC3, "moin\000");

    LC4 = 20045;
    strcpy(malloc_0+LC4, "String test: %s\012\000");

    LC5 = 20070;
    strcpy(malloc_0+LC5, "Test1: search pattern %s\012\000");

    LC6 = 20104;
    strcpy(malloc_0+LC6, "Test2: search pattern %s\012\000");

    LC7 = 20138;
    strcpy(malloc_0+LC7, "Test3: search pattern %s\012\000");

    LC1 = 20172;
    strcpy(malloc_0+LC1, "AABCAB12AFAABCABFFEGABCAB\000");

    LC2 = 20203;
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

void printf_help(const char *format, int32_t test)
{
    if (strstr(format, "%s") != NULL)
        printf(format, malloc_0 + test);
    else
        printf(format, test);
}
void strlen_help()
{
    r0.i = (int32_t) strlen(malloc_0+r0.i);
}

void naive_search()
{
    counters[0] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
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
    r4.i = r1.i;
    r8.i = r0.i;
    strlen_help();
    counters[1] ++;
    r5.i = r0.i;
    r0.i = r4.i;
    strlen_help();
    counters[2] ++;
    r5.i = r5.i - (r0.i);
    z = r5.i == 0;
    n = r5.i & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r0.i);
    v = (r5.i&0x80000000) != (r0.i&0x80000000) && (r5.i&0x80000000) != (r5.i&0x80000000);
    load_counter ++;
    if (n)
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
        ldr(&r9.i, &sp.i, 0, 4, false, false, false);
        sp.i += 4;
        ldr(&r10.i, &sp.i, 0, 4, false, false, false);
        sp.i += 4;
        ldr(&pc.i, &sp.i, 0, 4, false, false, false);
        sp.i += 4;
        return;
    }
    r9.i = (LC0 & 0xffff);
    r8.i = r8.i - (1);
    r9.i = r9.i | (((uint32_t)LC0 >> 16) << 16);
    r7.i = r5.i + (1);
    r6.i = r0.i;
    r5.i = 0;
L3:
    counters[3] ++;
    tmp = r6.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) 0);
    v = (r6.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    if (!z)
    {
        ip.i = r4.i - (1);
    }
    if (!z)
    {
        r2.i = r8.i + (r5.i);
    }
    if (!z)
    {
        lr.i = ip.i + (r6.i);
    }
    if (!z)
    {
        goto L5;
    }
    counters[4] ++;
    goto L7;
L12:
    counters[5] ++;
    tmp = ip.i - lr.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) lr.i);
    v = (ip.i&0x80000000) != (lr.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (z)
    {
        goto L11;
    }
L5:
    counters[6] ++;
    r3.i = ip.i;
    load_counter ++;
    ldr(&r0.i, &r2.i, 1, 1, true, false, false);
    load_counter ++;
    ldr(&r1.i, &ip.i, 1, 1, true, false, false);
    r3.i = r3.i + (2);
    r3.i = r3.i - (r4.i);
    tmp = r0.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) r1.i);
    v = (r0.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (z)
    {
        goto L12;
    }
L4:
    counters[7] ++;
    r5.i = r5.i + (1);
    tmp = r5.i - r7.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r7.i);
    v = (r5.i&0x80000000) != (r7.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (!z)
    {
        goto L3;
    }
    counters[8] ++;
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
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;
L11:
    counters[9] ++;
    tmp = r6.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) r3.i);
    v = (r6.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    if (!z)
    {
        goto L4;
    }
L7:
    counters[10] ++;
    r2.i = r5.i;
    r1.i = r9.i;
    r0.i = 1;
    printf_help(malloc_0+r1.i, r2.i);
    counters[11] ++;
    goto L4;
    return;
}

void main()
{
    malloc_start();
    counters[12] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r4.i, &sp.i, 0, 4, false, false, false);
    lr.i = (LC1 & 0xffff);
    lr.i = lr.i | (((uint32_t)LC1 >> 16) << 16);
    sp.i = sp.i - (48);
    ip.i = sp.i + (20);
    r4.i = (LC2 & 0xffff);
    load_counter ++;
    ldr(&r0.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    ldr(&r1.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    ldr(&r2.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    ldr(&r3.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    r4.i = r4.i | (((uint32_t)LC2 >> 16) << 16);
    store_counter ++;
    str(&r0.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    str(&r1.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    str(&r2.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    str(&r3.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    r3.i = 17990;
    load_counter ++;
    tmp = lr.i;
    ldr(&r0.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    ldr(&r1.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    ldr(&r2.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    lr.i = tmp;
    r3.i = r3.i | (70 << 16);
    store_counter ++;
    str(&r3.i, &sp.i, 4, 4, false, false, false);
    r3.i = 16707;
    r3.i = r3.i | (66 << 16);
    store_counter ++;
    str(&r3.i, &sp.i, 8, 4, false, false, false);
    store_counter ++;
    str(&r0.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    str(&r1.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    load_counter ++;
    tmp = r4.i;
    ldr(&r0.i, &r4.i, 0, 4, false, false, false);
    r4.i += 4;
    ldr(&r1.i, &r4.i, 0, 4, false, false, false);
    r4.i += 4;
    r4.i = tmp;
    store_counter ++;
    str(&r2.i, &ip.i, 0, 2, false, false, false);
    store_counter ++;
    str(&r0.i, &sp.i, 12, 4, false, false, false);
    r0.i = (LC3 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC3 >> 16) << 16);
    store_counter ++;
    str(&r1.i, &sp.i, 16, 2, false, false, false);
    printf_help("%s\n", r0.i);
    counters[13] ++;
    r2.i = sp.i + (20);
    r1.i = (LC4 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC4 >> 16) << 16);
    printf_help(malloc_0+r1.i, r2.i);
    counters[14] ++;
    r2.i = sp.i + (12);
    r1.i = (LC5 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC5 >> 16) << 16);
    printf_help(malloc_0+r1.i, r2.i);
    counters[15] ++;
    r1.i = sp.i + (12);
    r0.i = sp.i + (20);
    naive_search();
    counters[16] ++;
    r2.i = sp.i + (4);
    r1.i = (LC6 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC6 >> 16) << 16);
    printf_help(malloc_0+r1.i, r2.i);
    counters[17] ++;
    r1.i = sp.i + (4);
    r0.i = sp.i + (20);
    naive_search();
    counters[18] ++;
    r2.i = sp.i + (8);
    r1.i = (LC7 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC7 >> 16) << 16);
    printf_help(malloc_0+r1.i, r2.i);
    counters[19] ++;
    r0.i = sp.i + (20);
    r1.i = sp.i + (8);
    naive_search();
    counters[20] ++;
    r0.i = 0;
    sp.i = sp.i + (48);
    load_counter ++;
    ldr(&r4.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    counter_summary();
    return;

}

