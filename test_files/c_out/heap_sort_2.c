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

reg r3, r6, r10, r0, r4, r1, r2, r5, r8, r7, r9;

int32_t LC0;

int counters[39] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[39] = {4,2,4,6,4,2,9,4,10,6,4,5,1,3,5,2,5,10,6,9,1,2,6,4,1,2,1,3,2,4,5,1,7,3,2,4,2,2,2};

int heapSortpart;

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

void print_stack(int32_t start)
{
    int32_t size = (1028-start)/4;
    int32_t cur_val = 0;

    for(int32_t i=0; i<size; i++)
    {
        ldr(&cur_val, &start, i*4, 4, false, false, false);
        printf("%d: %d\n", start+i*4, cur_val);
    }
}

void malloc_start()
{
    malloc_0 = (uint8_t*) malloc(1);
    uint8_t* stack_ptr = (uint8_t*) malloc(10000);
    sp.i = (int32_t) (stack_ptr - malloc_0) + 9996;
    fp = sp;

    int32_t malloc_total = (int32_t) ((uint8_t*) malloc(12) - malloc_0);
    LC0 = malloc_total;
    strcpy(malloc_0+LC0, "%d\012\000");

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "heap_sort_2.c";

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

void swap();
void heapifyDown();
void heapifyUp();
void heapSort();
void main();

void srand_help()
{
    srand(r0.i);
}
void calloc_help()
{
    uint8_t* ptr = (uint8_t*) calloc(r0.i, r1.i);
    r0.i = (int32_t) (ptr - malloc_0);
}
void free_help()
{
    free(malloc_0+r0.i);
}
void rand_help()
{
    r0.i = rand();
}
void time_help()
{
    r0.i = time(NULL);
}
void smull(int32_t *dest_lo, int32_t *dest_hi, int32_t *op1, int32_t *op2)
{
    uint64_t res = (uint64_t) (*op1) * (*op2);
    *dest_lo = (uint32_t) res;
    *dest_hi = (uint32_t) (res >> 32);
}

void swap()
{
    counters[14] ++;
    load_counter ++;
    ldr(&r3.i, &r0.i, 0, 1, false, true, true);
    load_counter ++;
    ldr(&r2.i, &r1.i, 0, 1, false, true, true);
    store_counter ++;
    str(&r2.i, &r0.i, 0, 1, false, true, false);
    store_counter ++;
    str(&r3.i, &r1.i, 0, 1, false, true, false);
    return;

}

void heapifyDown()
{
    counters[15] ++;
    tmp = r1.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 1);
    v = (r1.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (z || n != v)
    {
        return;
    }
    counters[16] ++;
    store_counter ++;
    sp.i -= 16;
    str(&r4.i, &sp.i, 0*4, 4, false, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false, false);
    str(&lr.i, &sp.i, 3*4, 4, false, false, false);
    r4.i = 0;
    load_counter ++;
    ldr(&r5.i, &r0.i, 0, 1, false, true, true);
    lr.i = r4.i;
    r3.i = r4.i;
L24:
    counters[17] ++;
    r2.i = (uint32_t)r4.i << 1;
    r3.i = r3.i + 1;
    lr.i = r0.i + lr.i;
    r2.i = 0xff & (uint8_t)r2.i;
    tmp = r1.i - ((uint32_t)r3.i << 1);
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) ((uint32_t)r3.i << 1));
    v = (r1.i&0x80000000) != (((uint32_t)r3.i << 1)&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    ip.i = r2.i + 1;
    r3.i = 0xff & (uint8_t)ip.i;
    ip.i = (0xff & (uint8_t)ip.i) + r0.i;
    load_counter ++;
    ldr(&r6.i, &r0.i, r3.i, 1, false, false, true);
    if (z || n != v)
    {
        goto L22;
    }
    counters[18] ++;
    load_counter ++;
    ldr(&lr.i, &lr.i, 2, 1, false, false, true);
    r2.i = r2.i + 2;
    tmp = lr.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) r6.i);
    v = (lr.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    if (!z && n == v)
    {
        r3.i = 0xff & (uint8_t)r2.i;
    }
    if (!z && n == v)
    {
        ip.i = r0.i + r3.i;
    }
    load_counter ++;
    if (!z && n == v)
    {
        ldr(&r6.i, &r0.i, r3.i, 1, false, false, true);
    }
L22:
    counters[19] ++;
    tmp = r5.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r6.i);
    v = (r5.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    lr.i = (uint32_t)r3.i << 1;
    r2.i = lr.i + 1;
    load_counter ++;
    if (n == v)
    {
        ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
        ldr(&r5.i, &sp.i, 1*4, 4, false, false, false);
        ldr(&r6.i, &sp.i, 2*4, 4, false, false, false);
        ldr(&pc.i, &sp.i, 3*4, 4, false, false, false);
        sp.i += 16;
        return;
    }
    tmp = r2.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r1.i);
    v = (r2.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    store_counter ++;
    str(&r6.i, &r0.i, r4.i, 1, false, false, false);
    r4.i = r3.i;
    store_counter ++;
    str(&r5.i, &ip.i, 0, 1, false, true, false);
    if (n != v)
    {
        goto L24;
    }
    counters[20] ++;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false, false);
    ldr(&pc.i, &sp.i, 3*4, 4, false, false, false);
    sp.i += 16;
    return;

}

void heapifyUp()
{
    counters[21] ++;
    tmp = r1.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 0);
    v = (r1.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (z)
    {
        return;
    }
L31:
    counters[22] ++;
    ip.i = r1.i;
    r1.i = (uint32_t)r1.i >> 1;
    load_counter ++;
    ldr(&r3.i, &r0.i, ip.i, 1, false, false, true);
    load_counter ++;
    ldr(&r2.i, &r0.i, r1.i, 1, false, false, true);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n == v)
    {
        return;
    }
    counters[23] ++;
    tmp = r1.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 0);
    v = (r1.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    store_counter ++;
    str(&r3.i, &r0.i, r1.i, 1, false, false, false);
    store_counter ++;
    str(&r2.i, &r0.i, ip.i, 1, false, false, false);
    if (!z)
    {
        goto L31;
    }
    counters[24] ++;
    return;

}

void heapSort()
{
    if (heapSortpart == -1)
    {
        counters[25] ++;
        tmp = r1.i - 1;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r1.i) >= ((uint32_t) 1);
        v = (r1.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
        if (!c || z)
        {
            return;
        }
        counters[26] ++;
        goto heapSortpart0;
    }
    if (heapSortpart == 0)
    {
heapSortpart0:
        counters[0] ++;
        tmp = r1.i - 1;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r1.i) >= ((uint32_t) 1);
        v = (r1.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
        store_counter ++;
        sp.i -= 20;
        str(&r4.i, &sp.i, 0*4, 4, false, false, false);
        str(&r5.i, &sp.i, 1*4, 4, false, false, false);
        str(&r6.i, &sp.i, 2*4, 4, false, false, false);
        str(&r7.i, &sp.i, 3*4, 4, false, false, false);
        str(&lr.i, &sp.i, 4*4, 4, false, false, false);
        if (c && !z)
        {
            r4.i = 1;
        }
        if (!c || z)
        {
            goto L5;
        }
L2:
        counters[1] ++;
        r3.i = r4.i;
        goto L4;
L6:
        counters[2] ++;
        tmp = r3.i - 0;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r3.i) >= ((uint32_t) 0);
        v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
        store_counter ++;
        str(&ip.i, &r0.i, r3.i, 1, false, false, false);
        store_counter ++;
        str(&r2.i, &r0.i, lr.i, 1, false, false, false);
        if (z)
        {
            goto L7;
        }
L4:
        counters[3] ++;
        lr.i = r3.i;
        r3.i = (r3.i >> 1) & ((1 << 8) - 1);
        load_counter ++;
        ldr(&ip.i, &r0.i, lr.i, 1, false, false, true);
        load_counter ++;
        ldr(&r2.i, &r0.i, r3.i, 1, false, false, true);
        tmp = ip.i - r2.i;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) ip.i) >= ((uint32_t) r2.i);
        v = (ip.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
        if (!z && n == v)
        {
            goto L6;
        }
L7:
        counters[4] ++;
        r4.i = r4.i + 1;
        r4.i = 0xff & (uint8_t)r4.i;
        tmp = r4.i - r1.i;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r4.i) >= ((uint32_t) r1.i);
        v = (r4.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
        if (!z)
        {
            goto L2;
        }
L5:
        counters[5] ++;
        r1.i = r1.i - 1;
        r6.i = 0xff & (uint8_t)r1.i;
L3:
        counters[6] ++;
        load_counter ++;
        ldr(&r1.i, &r0.i, r6.i, 1, false, false, true);
        tmp = r6.i - 1;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r6.i) >= ((uint32_t) 1);
        v = (r6.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
        load_counter ++;
        ldr(&r2.i, &r0.i, 0, 1, false, true, true);
        r3.i = r6.i - 1;
        r4.i = r6.i;
        store_counter ++;
        str(&r1.i, &r0.i, 0, 1, false, true, false);
        store_counter ++;
        str(&r2.i, &r0.i, r6.i, 1, false, false, false);
        r6.i = 0xff & (uint8_t)r3.i;
        if (z)
        {
            goto L8;
        }
        counters[7] ++;
        load_counter ++;
        ldr(&r5.i, &r0.i, 0, 1, false, true, true);
        r1.i = 0;
        r3.i = r1.i;
        lr.i = r1.i;
L11:
        counters[8] ++;
        r2.i = (uint32_t)lr.i << 1;
        r3.i = r3.i + 1;
        r1.i = r0.i + r1.i;
        r2.i = 0xff & (uint8_t)r2.i;
        tmp = r4.i - ((uint32_t)r3.i << 1);
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r4.i) >= ((uint32_t) ((uint32_t)r3.i << 1));
        v = (r4.i&0x80000000) != (((uint32_t)r3.i << 1)&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
        ip.i = r2.i + 1;
        r3.i = 0xff & (uint8_t)ip.i;
        ip.i = (0xff & (uint8_t)ip.i) + r0.i;
        load_counter ++;
        ldr(&r7.i, &r0.i, r3.i, 1, false, false, true);
        if (z || n != v)
        {
            goto L9;
        }
        counters[9] ++;
        load_counter ++;
        ldr(&r1.i, &r1.i, 2, 1, false, false, true);
        r2.i = r2.i + 2;
        tmp = r1.i - r7.i;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r1.i) >= ((uint32_t) r7.i);
        v = (r1.i&0x80000000) != (r7.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
        if (!z && n == v)
        {
            r3.i = 0xff & (uint8_t)r2.i;
        }
        if (!z && n == v)
        {
            ip.i = r0.i + r3.i;
        }
        load_counter ++;
        if (!z && n == v)
        {
            ldr(&r7.i, &r0.i, r3.i, 1, false, false, true);
        }
L9:
        counters[10] ++;
        tmp = r5.i - r7.i;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r5.i) >= ((uint32_t) r7.i);
        v = (r5.i&0x80000000) != (r7.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
        r1.i = (uint32_t)r3.i << 1;
        r2.i = r1.i + 1;
        if (n == v)
        {
            goto L3;
        }
        counters[11] ++;
        tmp = r2.i - r4.i;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r2.i) >= ((uint32_t) r4.i);
        v = (r2.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
        store_counter ++;
        str(&r7.i, &r0.i, lr.i, 1, false, false, false);
        lr.i = r3.i;
        store_counter ++;
        str(&r5.i, &ip.i, 0, 1, false, true, false);
        if (n != v)
        {
            goto L11;
        }
        counters[12] ++;
        goto L3;
L8:
        counters[13] ++;
        tmp = r6.i - 0;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r6.i) >= ((uint32_t) 0);
        v = (r6.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
        load_counter ++;
        if (z)
        {
            ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
            ldr(&r5.i, &sp.i, 1*4, 4, false, false, false);
            ldr(&r6.i, &sp.i, 2*4, 4, false, false, false);
            ldr(&r7.i, &sp.i, 3*4, 4, false, false, false);
            ldr(&pc.i, &sp.i, 4*4, 4, false, false, false);
            sp.i += 20;
            return;
        }
        goto L3;
    }
    return;
}

void main()
{
    malloc_start();
    counters[27] ++;
    store_counter ++;
    sp.i -= 32;
    str(&r4.i, &sp.i, 0*4, 4, false, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false, false);
    str(&r7.i, &sp.i, 3*4, 4, false, false, false);
    str(&r8.i, &sp.i, 4*4, 4, false, false, false);
    str(&r9.i, &sp.i, 5*4, 4, false, false, false);
    str(&r10.i, &sp.i, 6*4, 4, false, false, false);
    str(&lr.i, &sp.i, 7*4, 4, false, false, false);
    r0.i = 0;
    time_help();
    counters[28] ++;
    r8.i = 34079;
    srand_help();
    counters[29] ++;
    r1.i = 1;
    r0.i = 10;
    r8.i = r8.i | (20971 << 16);
    calloc_help();
    counters[30] ++;
    r7.i = 100;
    r5.i = r0.i - 1;
    r6.i = r0.i + 9;
    r4.i = r0.i;
    r9.i = r5.i;
L42:
    counters[31] ++;
    rand_help();
    counters[32] ++;
    smull(&r3.i, &r2.i, &r8.i, &r0.i);
    r3.i = r0.i >> 31;
    r3.i = (r2.i >> 5) - r3.i;
    r0.i = r0.i - (r7.i * r3.i);
    z = r0.i == 0;
    n = r0.i & 0x80000000;
    store_counter ++;
    str(&r0.i, &r9.i, 1, 1, true, false, false);
    tmp = r9.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r9.i) >= ((uint32_t) r6.i);
    v = (r9.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r9.i&0x80000000);
    if (!z)
    {
        goto L42;
    }
    counters[33] ++;
    r1.i = 10;
    r0.i = r4.i;
    heapSortpart = 0;
    heapSort();
    counters[34] ++;
    r7.i = (LC0 & 0xffff);
    r7.i = r7.i | (((uint32_t)LC0 >> 16) << 16);
L43:
    counters[35] ++;
    load_counter ++;
    ldr(&r2.i, &r5.i, 1, 1, true, false, true);
    r1.i = r7.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[36] ++;
    tmp = r5.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r6.i);
    v = (r5.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (!z)
    {
        goto L43;
    }
    counters[37] ++;
    r0.i = r4.i;
    free_help();
    counters[38] ++;
    r0.i = 0;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false, false);
    ldr(&r7.i, &sp.i, 3*4, 4, false, false, false);
    ldr(&r8.i, &sp.i, 4*4, 4, false, false, false);
    ldr(&r9.i, &sp.i, 5*4, 4, false, false, false);
    ldr(&r10.i, &sp.i, 6*4, 4, false, false, false);
    ldr(&pc.i, &sp.i, 7*4, 4, false, false, false);
    sp.i += 32;
    counter_summary();
    return;

}

