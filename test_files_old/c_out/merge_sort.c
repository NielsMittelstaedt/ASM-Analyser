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

reg r6, r1, r0, r7, r8, r2, r5, r9, r10, r3, r4;

int32_t LC1, LC0;

int counters[29] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[29] = {2,1,8,3,4,5,2,3,4,3,3,3,11,2,3,4,2,2,3,4,2,3,3,3,4,16,4,2,3};

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
    malloc_0 = (uint8_t*) malloc(20033);
    sp.i = 19996;
    fp = sp;
    LC1 = 20000;
    strcpy(malloc_0+LC1, "%d \000");

    LC0 = 20009;
    int32_t arrayLC0[] = {5,3,0,2,6,1};
    for(int i=0; i<6; i++) str(&arrayLC0[i], &LC0, i*4, 4, false, false, false);

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "merge_sort.c";

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

void mergeSort();
void mergeSortpart0();
void main();

void malloc_help()
{
    uint8_t* ptr = (uint8_t*) malloc(r0.i);
    r0.i = (int32_t) (ptr - malloc_0);
}
void printf_help(const char *format, int32_t test)
{
    if (strstr(format, "%s") != NULL)
        printf(format, malloc_0 + test);
    else
        printf(format, test);
}
void free_help()
{
    free(malloc_0+r0.i);
}

void mergeSort()
{
    counters[0] ++;
    tmp = r1.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 1);
    v = (r1.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!c || z)
    {
        return;
    }
    counters[1] ++;
    mergeSortpart0();
    return;

}

void mergeSortpart0()
{
    counters[2] ++;
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
    r4.i = (uint32_t)r1.i >> 1;
    r9.i = r0.i;
    r5.i = r1.i - (((uint32_t)r1.i >> 1));
    r10.i = (uint32_t)r4.i << 2;
    r7.i = (uint32_t)r5.i << 2;
    r0.i = r10.i;
    malloc_help();
    counters[3] ++;
    r8.i = r0.i;
    r0.i = r7.i;
    malloc_help();
    counters[4] ++;
    r1.i = r9.i - (4);
    r2.i = r8.i - (4);
    r3.i = 0;
    r6.i = r0.i;
L5:
    counters[5] ++;
    load_counter ++;
    ldr(&r0.i, &r1.i, 4, 4, true, false, false);
    r3.i = r3.i + (1);
    tmp = r4.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r3.i);
    v = (r4.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    store_counter ++;
    str(&r0.i, &r2.i, 4, 4, true, false, false);
    if (!z && n == v)
    {
        goto L5;
    }
    counters[6] ++;
    tmp = r5.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) 0);
    v = (r5.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (z || n != v)
    {
        goto L6;
    }
    counters[7] ++;
    r2.i = r9.i + (r10.i);
    r0.i = r7.i + (r6.i);
    r3.i = r6.i;
L7:
    counters[8] ++;
    load_counter ++;
    ldr(&r1.i, &r2.i, 4, 4, false, true, false);
    store_counter ++;
    str(&r1.i, &r3.i, 4, 4, false, true, false);
    tmp = r0.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) r3.i);
    v = (r0.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        goto L7;
    }
    counters[9] ++;
    r1.i = r4.i;
    r0.i = r8.i;
    mergeSort();
    counters[10] ++;
    r0.i = r6.i;
    r1.i = r5.i;
    mergeSort();
    counters[11] ++;
    r0.i = 0;
    r3.i = r0.i;
    r2.i = r0.i;
L11:
    counters[12] ++;
    load_counter ++;
    ldr(&ip.i, &r8.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    load_counter ++;
    ldr(&r1.i, &r6.i, ((uint32_t)r3.i << 2), 4, false, false, false);
    tmp = ip.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r1.i);
    v = (ip.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    store_counter ++;
    if (!c || z)
    {
        str(&ip.i, &r9.i, ((uint32_t)r0.i << 2), 4, false, false, false);
    }
    if (!c || z)
    {
        r2.i = r2.i + (1);
    }
    if (c && !z)
    {
        r3.i = r3.i + (1);
    }
    store_counter ++;
    if (c && !z)
    {
        str(&r1.i, &r9.i, ((uint32_t)r0.i << 2), 2, false, false, false);
    }
    tmp = r4.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r2.i);
    v = (r4.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z && n == v)
    {
        tmp = r5.i - r3.i;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r5.i) >= ((uint32_t) r3.i);
        v = (r5.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    }
    r0.i = r0.i + (1);
    if (!z && n == v)
    {
        goto L11;
    }
    counters[13] ++;
    tmp = r4.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r2.i);
    v = (r4.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (z || n != v)
    {
        goto L12;
    }
L17:
    counters[14] ++;
    r10.i = r8.i + (r10.i);
    r1.i = r8.i + (((uint32_t)r2.i << 2));
    ip.i = r9.i + (((uint32_t)r0.i << 2));
L13:
    counters[15] ++;
    load_counter ++;
    ldr(&lr.i, &r1.i, 4, 4, false, true, false);
    tmp = r10.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r10.i) >= ((uint32_t) r1.i);
    v = (r10.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r10.i&0x80000000);
    store_counter ++;
    str(&lr.i, &ip.i, 4, 4, false, true, false);
    if (!z)
    {
        goto L13;
    }
    counters[16] ++;
    r0.i = r4.i + (r0.i);
    r0.i = r0.i - (r2.i);
L12:
    counters[17] ++;
    tmp = r5.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r3.i);
    v = (r5.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (z || n != v)
    {
        goto L16;
    }
    counters[18] ++;
    r3.i = r6.i + (((uint32_t)r3.i << 2));
    r0.i = r9.i + (((uint32_t)r0.i << 2));
    r7.i = r6.i + (r7.i);
L15:
    counters[19] ++;
    load_counter ++;
    ldr(&r2.i, &r3.i, 4, 4, false, true, false);
    tmp = r7.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r7.i) >= ((uint32_t) r3.i);
    v = (r7.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
    store_counter ++;
    str(&r2.i, &r0.i, 4, 4, false, true, false);
    if (!z)
    {
        goto L15;
    }
L16:
    counters[20] ++;
    r0.i = r8.i;
    free_help();
    counters[21] ++;
    r0.i = r6.i;
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
    ldr(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    free_help();
    return;
L6:
    counters[22] ++;
    r1.i = r4.i;
    r0.i = r8.i;
    mergeSort();
    counters[23] ++;
    r0.i = r6.i;
    r1.i = r5.i;
    mergeSort();
    counters[24] ++;
    r0.i = 0;
    r3.i = r0.i;
    r2.i = r0.i;
    goto L17;
    return;
}

void main()
{
    malloc_start();
    counters[25] ++;
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
    lr.i = sp.i;
    r5.i = (LC1 & 0xffff);
    r6.i = sp.i + (24);
    r5.i = r5.i | (((uint32_t)LC1 >> 16) << 16);
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
    tmp = ip.i;
    ldr(&r0.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    ldr(&r1.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    ip.i = tmp;
    store_counter ++;
    tmp = lr.i;
    str(&r0.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    str(&r1.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    lr.i = tmp;
    r0.i = sp.i;
    r1.i = 6;
    mergeSortpart0();
L26:
    counters[26] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 4, 4, false, true, false);
    r1.i = r5.i;
    r0.i = 1;
    printf_help(malloc_0+r1.i, r2.i);
    counters[27] ++;
    tmp = r4.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r6.i);
    v = (r4.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        goto L26;
    }
    counters[28] ++;
    r0.i = 0;
    sp.i = sp.i + (24);
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

}

