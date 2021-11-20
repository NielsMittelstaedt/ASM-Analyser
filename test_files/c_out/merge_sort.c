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
uint8_t* malloc_0 = 0;

reg r1, r9, r10, r7, r5, r2, r6, r3, r8, r4, r0;

int32_t LC1, LC0;

int counters[27] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[27] = {8,3,7,2,4,2,3,2,3,5,5,2,6,3,7,2,7,2,5,2,3,2,1,16,4,2,3};

int mergeSortpart;

void ldr(int32_t *target, int32_t *address, int32_t offset, int bytes, bool update, bool post_index)
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

void str(int32_t *target, int32_t *address, int32_t offset, int bytes, bool update, bool post_index)
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

void malloc_start()
{
    malloc_0 = (uint8_t*) malloc(1);
    uint8_t* stack_ptr = (uint8_t*) malloc(1000);
    sp.i = (int32_t) (stack_ptr - malloc_0) + 999;
    fp = sp;

    LC1 = (int32_t) ((uint8_t*) malloc(9) - malloc_0);
    strcpy(malloc_0+LC1, "%d \000");

    LC0 = (int32_t) ((uint8_t*) malloc(6*sizeof(int32_t)) - malloc_0);
    int32_t arrayLC0[] = {5,3,0,2,6,1};
    for(int i=0; i<6; i++) str(&arrayLC0[i], &LC0, i*4, 4, false, false);
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

void free_help()
{
    free(malloc_0+r0.i);
}
void malloc_help()
{
    uint8_t* ptr = (uint8_t*) malloc(r0.i);
    r0.i = (int32_t) (ptr - malloc_0);
}
void memcpy_help()
{
    memcpy(malloc_0+r0.i, malloc_0+r1.i, r2.i);
}

void mergeSort()
{
    if (mergeSortpart == -1)
    {
        counters[21] ++;
        tmp = r1.i - 1;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r1.i) >= ((uint32_t) 1);
        v = (r1.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
        if (!c || z)
        {
            return;
        }
        counters[22] ++;
        goto mergeSortpart0;
    }
    if (mergeSortpart == 0)
    {
mergeSortpart0:
        counters[0] ++;
        store_counter ++;
        sp.i -= 40;
        str(&r3.i, &sp.i, 0*4, 4, false, false);
        str(&r4.i, &sp.i, 1*4, 4, false, false);
        str(&r5.i, &sp.i, 2*4, 4, false, false);
        str(&r6.i, &sp.i, 3*4, 4, false, false);
        str(&r7.i, &sp.i, 4*4, 4, false, false);
        str(&r8.i, &sp.i, 5*4, 4, false, false);
        str(&r9.i, &sp.i, 6*4, 4, false, false);
        str(&r10.i, &sp.i, 7*4, 4, false, false);
        str(&fp.i, &sp.i, 8*4, 4, false, false);
        str(&lr.i, &sp.i, 9*4, 4, false, false);
        r8.i = (uint32_t)r1.i >> 1;
        fp.i = r0.i;
        r7.i = r1.i - ((uint32_t)r1.i >> 1);
        r4.i = (uint32_t)r8.i << 2;
        r5.i = (uint32_t)r7.i << 2;
        r0.i = r4.i;
        malloc_help();
        counters[1] ++;
        r9.i = r0.i;
        r0.i = r5.i;
        malloc_help();
        counters[2] ++;
        tmp = r8.i - 0;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r8.i) >= ((uint32_t) 0);
        v = (r8.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
        r1.i = fp.i;
        if (!z && n == v)
        {
            r2.i = r4.i;
        }
        if (z || n != v)
        {
            r2.i = 4;
        }
        r10.i = r0.i;
        r0.i = r9.i;
        memcpy_help();
        counters[3] ++;
        tmp = r7.i - 0;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r7.i) >= ((uint32_t) 0);
        v = (r7.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
        if (z || n != v)
        {
            goto L5;
        }
        counters[4] ++;
        r1.i = fp.i + r4.i;
        r2.i = r5.i;
        r0.i = r10.i;
        memcpy_help();
L5:
        counters[5] ++;
        tmp = r8.i - 1;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r8.i) >= ((uint32_t) 1);
        v = (r8.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
        if (z)
        {
            goto L3;
        }
        counters[6] ++;
        r1.i = r8.i;
        r0.i = r9.i;
        mergeSortpart = 0;
        mergeSort();
L3:
        counters[7] ++;
        tmp = r7.i - 1;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r7.i) >= ((uint32_t) 1);
        v = (r7.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
        if (!c || z)
        {
            goto L6;
        }
        counters[8] ++;
        r1.i = r7.i;
        r0.i = r10.i;
        mergeSortpart = 0;
        mergeSort();
L6:
        counters[9] ++;
        tmp = r7.i - 0;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r7.i) >= ((uint32_t) 0);
        v = (r7.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
        if (z || n != v)
        {
            r4.i = 0;
        }
        if (z || n != v)
        {
            r5.i = r4.i;
        }
        if (z || n != v)
        {
            r6.i = r4.i;
        }
        if (z || n != v)
        {
            goto L8;
        }
        counters[10] ++;
        load_counter ++;
        ldr(&r2.i, &r9.i, 0, 4, false, true);
        r4.i = 0;
        load_counter ++;
        ldr(&r3.i, &r10.i, 0, 4, false, true);
        r6.i = r4.i;
        r5.i = r4.i;
L7:
        counters[11] ++;
        tmp = r2.i - r3.i;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
        v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
        if (c && !z)
        {
            goto L10;
        }
L26:
        counters[12] ++;
        r5.i = r5.i + 1;
        store_counter ++;
        str(&r2.i, &fp.i, ((uint32_t)r4.i << 2), 4, false, false);
        tmp = r8.i - r5.i;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r8.i) >= ((uint32_t) r5.i);
        v = (r8.i&0x80000000) != (r5.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
        if (!z && n == v)
        {
            tmp = r7.i - r6.i;
            z = tmp == 0;
            n = tmp & 0x80000000;
            c = ((uint32_t) r7.i) >= ((uint32_t) r6.i);
            v = (r7.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
        }
        r4.i = r4.i + 1;
        if (z || n != v)
        {
            goto L12;
        }
        counters[13] ++;
        load_counter ++;
        ldr(&r2.i, &r9.i, ((uint32_t)r5.i << 2), 4, false, false);
        tmp = r2.i - r3.i;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
        v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
        if (!c || z)
        {
            goto L26;
        }
L10:
        counters[14] ++;
        r6.i = r6.i + 1;
        store_counter ++;
        str(&r3.i, &fp.i, ((uint32_t)r4.i << 2), 4, false, false);
        tmp = r8.i - r5.i;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r8.i) >= ((uint32_t) r5.i);
        v = (r8.i&0x80000000) != (r5.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
        if (!z && n == v)
        {
            tmp = r7.i - r6.i;
            z = tmp == 0;
            n = tmp & 0x80000000;
            c = ((uint32_t) r7.i) >= ((uint32_t) r6.i);
            v = (r7.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
        }
        r4.i = r4.i + 1;
        load_counter ++;
        if (!z && n == v)
        {
            ldr(&r3.i, &r10.i, ((uint32_t)r6.i << 2), 4, false, false);
        }
        if (!z && n == v)
        {
            goto L7;
        }
L12:
        counters[15] ++;
        tmp = r8.i - r5.i;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r8.i) >= ((uint32_t) r5.i);
        v = (r8.i&0x80000000) != (r5.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
        if (z || n != v)
        {
            goto L9;
        }
L8:
        counters[16] ++;
        r2.i = r8.i - r5.i;
        r0.i = fp.i + ((uint32_t)r4.i << 2);
        r1.i = r9.i + ((uint32_t)r5.i << 2);
        r4.i = r8.i + r4.i;
        r2.i = (uint32_t)r2.i << 2;
        r4.i = r4.i - r5.i;
        memcpy_help();
L9:
        counters[17] ++;
        tmp = r7.i - r6.i;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r7.i) >= ((uint32_t) r6.i);
        v = (r7.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
        if (z || n != v)
        {
            goto L14;
        }
        counters[18] ++;
        r2.i = r7.i - r6.i;
        r1.i = r10.i + ((uint32_t)r6.i << 2);
        r0.i = fp.i + ((uint32_t)r4.i << 2);
        r2.i = (uint32_t)r2.i << 2;
        memcpy_help();
L14:
        counters[19] ++;
        r0.i = r9.i;
        free_help();
        counters[20] ++;
        r0.i = r10.i;
        load_counter ++;
        ldr(&r3.i, &sp.i, 0*4, 4, false, false);
        ldr(&r4.i, &sp.i, 1*4, 4, false, false);
        ldr(&r5.i, &sp.i, 2*4, 4, false, false);
        ldr(&r6.i, &sp.i, 3*4, 4, false, false);
        ldr(&r7.i, &sp.i, 4*4, 4, false, false);
        ldr(&r8.i, &sp.i, 5*4, 4, false, false);
        ldr(&r9.i, &sp.i, 6*4, 4, false, false);
        ldr(&r10.i, &sp.i, 7*4, 4, false, false);
        ldr(&fp.i, &sp.i, 8*4, 4, false, false);
        ldr(&lr.i, &sp.i, 9*4, 4, false, false);
        sp.i += 40;
        free_help();
        return;
    }

}

void main()
{
    malloc_start();
    counters[23] ++;
    ip.i = (LC0 & 0xffff);
    ip.i = ip.i | (((uint32_t)LC0 >> 16) << 16);
    store_counter ++;
    sp.i -= 16;
    str(&r4.i, &sp.i, 0*4, 4, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false);
    str(&lr.i, &sp.i, 3*4, 4, false, false);
    sp.i = sp.i - 24;
    load_counter ++;
    ldr(&r0.i, &ip.i, 0*4, 4, false, false);
    ldr(&r1.i, &ip.i, 1*4, 4, false, false);
    ldr(&r2.i, &ip.i, 2*4, 4, false, false);
    ldr(&r3.i, &ip.i, 3*4, 4, false, false);
    ip.i += 16;
    lr.i = sp.i;
    r5.i = (LC1 & 0xffff);
    r6.i = sp.i + 24;
    r5.i = r5.i | (((uint32_t)LC1 >> 16) << 16);
    r4.i = sp.i;
    store_counter ++;
    str(&r0.i, &lr.i, 0*4, 4, false, false);
    str(&r1.i, &lr.i, 1*4, 4, false, false);
    str(&r2.i, &lr.i, 2*4, 4, false, false);
    str(&r3.i, &lr.i, 3*4, 4, false, false);
    lr.i += 16;
    load_counter ++;
    ldr(&r0.i, &ip.i, 0*4, 4, false, false);
    ldr(&r1.i, &ip.i, 1*4, 4, false, false);
    store_counter ++;
    str(&r0.i, &lr.i, 0*4, 4, false, false);
    str(&r1.i, &lr.i, 1*4, 4, false, false);
    r0.i = sp.i;
    r1.i = 6;
    mergeSortpart = 0;
    mergeSort();
L30:
    counters[24] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 4, 4, false, true);
    r1.i = r5.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[25] ++;
    tmp = r4.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r6.i);
    v = (r4.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        goto L30;
    }
    counters[26] ++;
    r0.i = 0;
    sp.i = sp.i + 24;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false);
    ldr(&pc.i, &sp.i, 3*4, 4, false, false);
    sp.i += 16;
    counter_summary();
    return;

}

