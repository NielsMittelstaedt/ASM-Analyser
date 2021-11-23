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

reg r6, r3, r8, r4, r10, r0, r1, r7, r9, r5, r2;

int32_t LC0;

int counters[62] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[62] = {6,3,4,2,3,4,1,2,4,7,7,7,7,7,3,3,6,4,5,5,5,4,2,2,5,3,4,1,1,2,2,6,4,5,6,4,5,4,5,4,2,2,2,2,2,2,3,3,2,2,8,3,6,1,8,3,2,4,2,2,2,2};

int RecursionInsertionSortpart;

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

    int32_t malloc_total = (int32_t) ((uint8_t*) malloc(9) - malloc_0);
    LC0 = malloc_total;
    strcpy(malloc_0+LC0, " %d\000");

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "insertion_sort_recursive.c";

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

void RecursionInsertionSort();
void main();

void rand_help()
{
    r0.i = rand();
}
void time_help()
{
    r0.i = time(NULL);
}
void srand_help()
{
    srand(r0.i);
}
void free_help()
{
    free(malloc_0+r0.i);
}
void calloc_help()
{
    uint8_t* ptr = (uint8_t*) calloc(r0.i, r1.i);
    r0.i = (int32_t) (ptr - malloc_0);
}
void smull(int32_t *dest_lo, int32_t *dest_hi, int32_t *op1, int32_t *op2)
{
    uint64_t res = (uint64_t) (*op1) * (*op2);
    *dest_lo = (uint32_t) res;
    *dest_hi = (uint32_t) (res >> 32);
}

void RecursionInsertionSort()
{
    if (RecursionInsertionSortpart == -1)
    {
        counters[8] ++;
        store_counter ++;
        sp.i -= 36;
        str(&r4.i, &sp.i, 0*4, 4, false, false, false);
        str(&r5.i, &sp.i, 1*4, 4, false, false, false);
        str(&r6.i, &sp.i, 2*4, 4, false, false, false);
        str(&r7.i, &sp.i, 3*4, 4, false, false, false);
        str(&r8.i, &sp.i, 4*4, 4, false, false, false);
        str(&r9.i, &sp.i, 5*4, 4, false, false, false);
        str(&r10.i, &sp.i, 6*4, 4, false, false, false);
        str(&fp.i, &sp.i, 7*4, 4, false, false, false);
        str(&lr.i, &sp.i, 8*4, 4, false, false, false);
        r4.i = r1.i - 0;
        z = r4.i == 0;
        n = r4.i & 0x80000000;
        c = ((uint32_t) r1.i) >= ((uint32_t) 0);
        v = (r1.i&0x80000000) != (0&0x80000000) && (r4.i&0x80000000) != (r1.i&0x80000000);
        sp.i = sp.i - 44;
        if (z || n != v)
        {
            goto L16;
        }
        counters[9] ++;
        r2.i = r4.i - -1073741823;
        tmp = r4.i - 1;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r4.i) >= ((uint32_t) 1);
        v = (r4.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
        r8.i = r0.i;
        fp.i = (uint32_t)r2.i << 2;
        load_counter ++;
        if (z)
        {
            ldr(&r2.i, &r0.i, ((uint32_t)r2.i << 2), 4, false, false, false);
        }
        r3.i = r0.i + fp.i;
        if (z)
        {
            goto L40;
        }
        counters[10] ++;
        r5.i = r4.i - 2;
        tmp = r4.i - 2;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r4.i) >= ((uint32_t) 2);
        v = (r4.i&0x80000000) != (2&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
        r2.i = fp.i - 4;
        r1.i = r0.i + r2.i;
        r6.i = r5.i;
        store_counter ++;
        str(&r1.i, &sp.i, 4, 4, false, false, false);
        if (z)
        {
            goto L19;
        }
        counters[11] ++;
        tmp = r4.i - 3;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r4.i) >= ((uint32_t) 3);
        v = (r4.i&0x80000000) != (3&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
        r2.i = fp.i - 8;
        r7.i = r4.i - 3;
        r1.i = r0.i + r2.i;
        store_counter ++;
        str(&r7.i, &sp.i, 12, 4, false, false, false);
        store_counter ++;
        str(&r1.i, &sp.i, 8, 4, false, false, false);
        if (z)
        {
            goto L20;
        }
        counters[12] ++;
        tmp = r4.i - 4;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r4.i) >= ((uint32_t) 4);
        v = (r4.i&0x80000000) != (4&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
        r2.i = fp.i - 12;
        r9.i = r4.i - 4;
        r1.i = r0.i + r2.i;
        store_counter ++;
        str(&r9.i, &sp.i, 20, 4, false, false, false);
        store_counter ++;
        str(&r1.i, &sp.i, 16, 4, false, false, false);
        if (z)
        {
            goto L21;
        }
        counters[13] ++;
        tmp = r4.i - 5;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r4.i) >= ((uint32_t) 5);
        v = (r4.i&0x80000000) != (5&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
        r2.i = fp.i - 16;
        r10.i = r4.i - 5;
        r1.i = r0.i + r2.i;
        store_counter ++;
        str(&r10.i, &sp.i, 28, 4, false, false, false);
        store_counter ++;
        str(&r1.i, &sp.i, 24, 4, false, false, false);
        if (z)
        {
            goto L22;
        }
        counters[14] ++;
        r1.i = r4.i - 6;
        z = r1.i == 0;
        n = r1.i & 0x80000000;
        c = ((uint32_t) r4.i) >= ((uint32_t) 6);
        v = (r4.i&0x80000000) != (6&0x80000000) && (r1.i&0x80000000) != (r4.i&0x80000000);
        fp.i = fp.i - 20;
        if (z)
        {
            goto L23;
        }
        counters[15] ++;
        store_counter ++;
        str(&r3.i, &sp.i, 36, 4, false, false, false);
        store_counter ++;
        str(&r1.i, &sp.i, 32, 4, false, false, false);
        goto RecursionInsertionSortpart0;
    }
    if (RecursionInsertionSortpart == 0)
    {
RecursionInsertionSortpart0:
        counters[0] ++;
        store_counter ++;
        sp.i -= 24;
        str(&r4.i, &sp.i, 0*4, 4, false, false, false);
        str(&r5.i, &sp.i, 1*4, 4, false, false, false);
        str(&r6.i, &sp.i, 2*4, 4, false, false, false);
        str(&r7.i, &sp.i, 3*4, 4, false, false, false);
        str(&r8.i, &sp.i, 4*4, 4, false, false, false);
        str(&lr.i, &sp.i, 5*4, 4, false, false, false);
        r5.i = r1.i - 1;
        z = r5.i == 0;
        n = r5.i & 0x80000000;
        c = ((uint32_t) r1.i) >= ((uint32_t) 1);
        v = (r1.i&0x80000000) != (1&0x80000000) && (r5.i&0x80000000) != (r1.i&0x80000000);
        r7.i = r1.i - -1073741823;
        r6.i = r0.i;
        load_counter ++;
        if (z)
        {
            ldr(&ip.i, &r0.i, ((uint32_t)r7.i << 2), 4, false, false, false);
        }
        if (z)
        {
            goto L3;
        }
        counters[1] ++;
        r4.i = r1.i;
        r1.i = r5.i;
        counters[2] ++;
        tmp = r4.i - 1;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r4.i) >= ((uint32_t) 1);
        v = (r4.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
        load_counter ++;
        ldr(&ip.i, &r6.i, ((uint32_t)r7.i << 2), 4, false, false, false);
        r3.i = r4.i - 2;
        if (z)
        {
            goto L3;
        }
        counters[3] ++;
        r1.i = r6.i + ((uint32_t)r5.i << 2);
        goto L4;
L5:
        counters[4] ++;
        tmp = r3.i + 1;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) tmp) < ((uint32_t) r3.i);
        v = (r3.i&0x80000000) == (1&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
        store_counter ++;
        str(&r2.i, &r1.i, -4, 4, false, true, false);
        if (z)
        {
            goto L3;
        }
L4:
        counters[5] ++;
        load_counter ++;
        ldr(&r2.i, &r1.i, -4, 4, false, false, false);
        r3.i = r3.i - 1;
        tmp = ip.i - r2.i;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) ip.i) >= ((uint32_t) r2.i);
        v = (ip.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
        if (n != v)
        {
            goto L5;
        }
        counters[6] ++;
        r6.i = r1.i;
L3:
        counters[7] ++;
        store_counter ++;
        str(&ip.i, &r6.i, 0, 4, false, true, false);
        load_counter ++;
        ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
        ldr(&r5.i, &sp.i, 1*4, 4, false, false, false);
        ldr(&r6.i, &sp.i, 2*4, 4, false, false, false);
        ldr(&r7.i, &sp.i, 3*4, 4, false, false, false);
        ldr(&r8.i, &sp.i, 4*4, 4, false, false, false);
        ldr(&pc.i, &sp.i, 5*4, 4, false, false, false);
        sp.i += 24;
        return;
    }
    counters[16] ++;
    load_counter ++;
    ldr(&r1.i, &sp.i, 32, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &sp.i, 36, 4, false, false, false);
    r2.i = r8.i + ((uint32_t)r1.i << 2);
    load_counter ++;
    ldr(&fp.i, &r0.i, fp.i, 4, false, false, false);
    r0.i = r4.i - 7;
    goto L24;
L26:
    counters[17] ++;
    tmp = r0.i + 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) tmp) < ((uint32_t) r0.i);
    v = (r0.i&0x80000000) == (1&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    store_counter ++;
    str(&ip.i, &r2.i, 0, 4, false, true, false);
    r2.i = lr.i - 4;
    if (z)
    {
        goto L42;
    }
L24:
    counters[18] ++;
    load_counter ++;
    ldr(&ip.i, &r2.i, -4, 4, false, false, false);
    r0.i = r0.i - 1;
    lr.i = r2.i;
    tmp = ip.i - fp.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) fp.i);
    v = (ip.i&0x80000000) != (fp.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (!z && n == v)
    {
        goto L26;
    }
L25:
    counters[19] ++;
    load_counter ++;
    ldr(&r0.i, &sp.i, 24, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &sp.i, 28, 4, false, false, false);
    store_counter ++;
    str(&fp.i, &lr.i, 0, 4, false, true, false);
    load_counter ++;
    ldr(&lr.i, &r0.i, 0, 4, false, true, false);
    r2.i = r8.i + ((uint32_t)r2.i << 2);
L27:
    counters[20] ++;
    load_counter ++;
    ldr(&r0.i, &r2.i, -4, 4, false, false, false);
    r1.i = r1.i - 1;
    ip.i = r2.i;
    tmp = r0.i - lr.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) lr.i);
    v = (r0.i&0x80000000) != (lr.i&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (z || n != v)
    {
        goto L28;
    }
    counters[21] ++;
    tmp = r1.i + 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) tmp) < ((uint32_t) r1.i);
    v = (r1.i&0x80000000) == (1&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    store_counter ++;
    str(&r0.i, &r2.i, 0, 4, false, true, false);
    r2.i = ip.i - 4;
    if (!z)
    {
        goto L27;
    }
    counters[22] ++;
    ip.i = r8.i;
    goto L28;
L19:
    counters[23] ++;
    load_counter ++;
    ldr(&r0.i, &r0.i, r2.i, 4, false, false, false);
    r1.i = r8.i;
L37:
    counters[24] ++;
    r4.i = r4.i - 1;
    store_counter ++;
    str(&r0.i, &r1.i, 0, 4, false, true, false);
    load_counter ++;
    ldr(&r2.i, &r3.i, 0, 4, false, true, false);
    r4.i = r8.i + ((uint32_t)r4.i << 2);
    goto L39;
L41:
    counters[25] ++;
    tmp = r5.i + 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) tmp) < ((uint32_t) r5.i);
    v = (r5.i&0x80000000) == (1&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    store_counter ++;
    str(&r3.i, &r4.i, -4, 4, false, true, false);
    if (z)
    {
        goto L40;
    }
L39:
    counters[26] ++;
    load_counter ++;
    ldr(&r3.i, &r4.i, -4, 4, false, false, false);
    r5.i = r5.i - 1;
    tmp = r3.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r2.i);
    v = (r3.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z && n == v)
    {
        goto L41;
    }
    counters[27] ++;
    r8.i = r4.i;
L40:
    counters[28] ++;
    store_counter ++;
    str(&r2.i, &r8.i, 0, 4, false, true, false);
L16:
    counters[29] ++;
    sp.i = sp.i + 44;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false, false);
    ldr(&r7.i, &sp.i, 3*4, 4, false, false, false);
    ldr(&r8.i, &sp.i, 4*4, 4, false, false, false);
    ldr(&r9.i, &sp.i, 5*4, 4, false, false, false);
    ldr(&r10.i, &sp.i, 6*4, 4, false, false, false);
    ldr(&fp.i, &sp.i, 7*4, 4, false, false, false);
    ldr(&pc.i, &sp.i, 8*4, 4, false, false, false);
    sp.i += 36;
    return;
L22:
    counters[30] ++;
    load_counter ++;
    ldr(&lr.i, &r0.i, r2.i, 4, false, false, false);
    ip.i = r0.i;
L28:
    counters[31] ++;
    load_counter ++;
    ldr(&r2.i, &sp.i, 20, 4, false, false, false);
    load_counter ++;
    ldr(&r1.i, &sp.i, 16, 4, false, false, false);
    store_counter ++;
    str(&lr.i, &ip.i, 0, 4, false, true, false);
    r2.i = r8.i + ((uint32_t)r2.i << 2);
    load_counter ++;
    ldr(&ip.i, &r1.i, 0, 4, false, true, false);
    goto L30;
L32:
    counters[32] ++;
    tmp = r10.i + 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) tmp) < ((uint32_t) r10.i);
    v = (r10.i&0x80000000) == (1&0x80000000) && (tmp&0x80000000) != (r10.i&0x80000000);
    store_counter ++;
    str(&r1.i, &r2.i, 0, 4, false, true, false);
    r2.i = r0.i - 4;
    if (z)
    {
        goto L44;
    }
L30:
    counters[33] ++;
    load_counter ++;
    ldr(&r1.i, &r2.i, -4, 4, false, false, false);
    r10.i = r10.i - 1;
    r0.i = r2.i;
    tmp = r1.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) ip.i);
    v = (r1.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!z && n == v)
    {
        goto L32;
    }
L31:
    counters[34] ++;
    load_counter ++;
    ldr(&r2.i, &sp.i, 12, 4, false, false, false);
    load_counter ++;
    ldr(&r1.i, &sp.i, 8, 4, false, false, false);
    store_counter ++;
    str(&ip.i, &r0.i, 0, 4, false, true, false);
    r2.i = r8.i + ((uint32_t)r2.i << 2);
    load_counter ++;
    ldr(&ip.i, &r1.i, 0, 4, false, true, false);
    goto L33;
L35:
    counters[35] ++;
    tmp = r9.i + 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) tmp) < ((uint32_t) r9.i);
    v = (r9.i&0x80000000) == (1&0x80000000) && (tmp&0x80000000) != (r9.i&0x80000000);
    store_counter ++;
    str(&r1.i, &r2.i, 0, 4, false, true, false);
    r2.i = r0.i - 4;
    if (z)
    {
        goto L45;
    }
L33:
    counters[36] ++;
    load_counter ++;
    ldr(&r1.i, &r2.i, -4, 4, false, false, false);
    r9.i = r9.i - 1;
    r0.i = r2.i;
    tmp = r1.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) ip.i);
    v = (r1.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!z && n == v)
    {
        goto L35;
    }
L34:
    counters[37] ++;
    load_counter ++;
    ldr(&r2.i, &sp.i, 4, 4, false, false, false);
    r6.i = r8.i + ((uint32_t)r6.i << 2);
    store_counter ++;
    str(&ip.i, &r0.i, 0, 4, false, true, false);
    load_counter ++;
    ldr(&r0.i, &r2.i, 0, 4, false, true, false);
L36:
    counters[38] ++;
    load_counter ++;
    ldr(&r2.i, &r6.i, -4, 4, false, false, false);
    r7.i = r7.i - 1;
    r1.i = r6.i;
    tmp = r2.i - r0.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r0.i);
    v = (r2.i&0x80000000) != (r0.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (z || n != v)
    {
        goto L37;
    }
    counters[39] ++;
    tmp = r7.i + 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) tmp) < ((uint32_t) r7.i);
    v = (r7.i&0x80000000) == (1&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
    store_counter ++;
    str(&r2.i, &r6.i, 0, 4, false, true, false);
    r6.i = r1.i - 4;
    if (!z)
    {
        goto L36;
    }
    counters[40] ++;
    r1.i = r8.i;
    goto L37;
L45:
    counters[41] ++;
    r0.i = r8.i;
    goto L34;
L44:
    counters[42] ++;
    r0.i = r8.i;
    goto L31;
L42:
    counters[43] ++;
    lr.i = r8.i;
    goto L25;
L20:
    counters[44] ++;
    load_counter ++;
    ldr(&ip.i, &r0.i, r2.i, 4, false, false, false);
    goto L34;
L21:
    counters[45] ++;
    load_counter ++;
    ldr(&ip.i, &r0.i, r2.i, 4, false, false, false);
    goto L31;
L23:
    counters[46] ++;
    load_counter ++;
    ldr(&fp.i, &r0.i, fp.i, 4, false, false, false);
    lr.i = r0.i;
    goto L25;
    return;
}

void main()
{
    malloc_start();
    counters[47] ++;
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
    counters[48] ++;
    r4.i = 19923;
    srand_help();
    counters[49] ++;
    r4.i = r4.i | (4194 << 16);
    rand_help();
    counters[50] ++;
    r3.i = 500;
    r1.i = 4;
    smull(&r2.i, &r4.i, &r4.i, &r0.i);
    r2.i = r0.i >> 31;
    r4.i = (r4.i >> 5) - r2.i;
    r4.i = r0.i - (r3.i * r4.i);
    z = r4.i == 0;
    n = r4.i & 0x80000000;
    r0.i = r4.i;
    calloc_help();
    counters[51] ++;
    tmp = r4.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 0);
    v = (r4.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    r5.i = r0.i;
    if (z || n != v)
    {
        goto L63;
    }
    counters[52] ++;
    r10.i = 34079;
    r7.i = r0.i + ((uint32_t)r4.i << 2);
    r10.i = r10.i | (20971 << 16);
    r6.i = r0.i;
    r9.i = r0.i;
    r8.i = 100;
L60:
    counters[53] ++;
    rand_help();
    counters[54] ++;
    smull(&r3.i, &r2.i, &r10.i, &r0.i);
    r3.i = r0.i >> 31;
    r3.i = (r2.i >> 5) - r3.i;
    r3.i = r0.i - (r8.i * r3.i);
    z = r3.i == 0;
    n = r3.i & 0x80000000;
    r3.i = r3.i - 50;
    store_counter ++;
    str(&r3.i, &r9.i, 4, 4, false, true, false);
    tmp = r9.i - r7.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r9.i) >= ((uint32_t) r7.i);
    v = (r9.i&0x80000000) != (r7.i&0x80000000) && (tmp&0x80000000) != (r9.i&0x80000000);
    if (!z)
    {
        goto L60;
    }
    counters[55] ++;
    r1.i = r4.i;
    r0.i = r5.i;
    RecursionInsertionSortpart = 0;
    RecursionInsertionSort();
    counters[56] ++;
    r4.i = (LC0 & 0xffff);
    r4.i = r4.i | (((uint32_t)LC0 >> 16) << 16);
L62:
    counters[57] ++;
    load_counter ++;
    ldr(&r2.i, &r6.i, 4, 4, false, true, false);
    r1.i = r4.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[58] ++;
    tmp = r7.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r7.i) >= ((uint32_t) r6.i);
    v = (r7.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
    if (!z)
    {
        goto L62;
    }
L63:
    counters[59] ++;
    r0.i = 10;
    printf("%c", (char)r0.i);
    counters[60] ++;
    r0.i = r5.i;
    free_help();
    counters[61] ++;
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

