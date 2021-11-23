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

int counters[64] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[64] = {7,2,1,6,3,5,2,9,6,6,6,6,4,2,1,6,5,5,5,5,5,2,3,2,6,4,4,4,4,4,3,2,7,6,6,6,5,5,3,4,2,5,5,2,3,2,2,4,4,4,4,3,3,2,4,5,1,7,3,2,4,2,2,2};

int findIndexpart;

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
    char filename[] = "selection_sort_recursive.c";

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
void findIndex();
void selectionSort();
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
    counters[5] ++;
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

void findIndex()
{
    if (findIndexpart == -1)
    {
        counters[6] ++;
        tmp = r1.i - 1;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r1.i) >= ((uint32_t) 1);
        v = (r1.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
        if (z)
        {
            goto L21;
        }
        counters[7] ++;
        store_counter ++;
        sp.i -= 40;
        str(&r3.i, &sp.i, 0*4, 4, false, false, false);
        str(&r4.i, &sp.i, 1*4, 4, false, false, false);
        str(&r5.i, &sp.i, 2*4, 4, false, false, false);
        str(&r6.i, &sp.i, 3*4, 4, false, false, false);
        str(&r7.i, &sp.i, 4*4, 4, false, false, false);
        str(&r8.i, &sp.i, 5*4, 4, false, false, false);
        str(&r9.i, &sp.i, 6*4, 4, false, false, false);
        str(&r10.i, &sp.i, 7*4, 4, false, false, false);
        str(&fp.i, &sp.i, 8*4, 4, false, false, false);
        str(&lr.i, &sp.i, 9*4, 4, false, false, false);
        r7.i = r1.i - 1;
        r4.i = r0.i;
        r6.i = r1.i;
        r7.i = 0xff & (uint8_t)r7.i;
        tmp = r7.i - 1;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r7.i) >= ((uint32_t) 1);
        v = (r7.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
        load_counter ++;
        if (z)
        {
            ldr(&r3.i, &r0.i, 0, 1, false, true, true);
        }
        if (z)
        {
            r0.i = 0;
        }
        if (z)
        {
            goto L11;
        }
        counters[8] ++;
        r5.i = r1.i - 2;
        r5.i = 0xff & (uint8_t)r5.i;
        tmp = r5.i - 1;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r5.i) >= ((uint32_t) 1);
        v = (r5.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
        load_counter ++;
        if (z)
        {
            ldr(&r3.i, &r4.i, 0, 1, false, true, true);
        }
        if (z)
        {
            r0.i = 0;
        }
        if (z)
        {
            goto L13;
        }
        counters[9] ++;
        r8.i = r1.i - 3;
        r8.i = 0xff & (uint8_t)r8.i;
        tmp = r8.i - 1;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r8.i) >= ((uint32_t) 1);
        v = (r8.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
        load_counter ++;
        if (z)
        {
            ldr(&r3.i, &r4.i, 0, 1, false, true, true);
        }
        if (z)
        {
            r0.i = 0;
        }
        if (z)
        {
            goto L15;
        }
        counters[10] ++;
        r9.i = r1.i - 4;
        r9.i = 0xff & (uint8_t)r9.i;
        tmp = r9.i - 1;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r9.i) >= ((uint32_t) 1);
        v = (r9.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r9.i&0x80000000);
        load_counter ++;
        if (z)
        {
            ldr(&r3.i, &r4.i, 0, 1, false, true, true);
        }
        if (z)
        {
            r0.i = 0;
        }
        if (z)
        {
            goto L17;
        }
        counters[11] ++;
        r10.i = r1.i - 5;
        r10.i = 0xff & (uint8_t)r10.i;
        tmp = r10.i - 1;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r10.i) >= ((uint32_t) 1);
        v = (r10.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r10.i&0x80000000);
        load_counter ++;
        if (z)
        {
            ldr(&r3.i, &r4.i, 0, 1, false, true, true);
        }
        if (z)
        {
            r0.i = 0;
        }
        if (z)
        {
            goto L19;
        }
        counters[12] ++;
        fp.i = r1.i - 6;
        fp.i = 0xff & (uint8_t)fp.i;
        tmp = fp.i - 1;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) fp.i) >= ((uint32_t) 1);
        v = (fp.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (fp.i&0x80000000);
        if (z)
        {
            goto L22;
        }
        counters[13] ++;
        r1.i = fp.i;
        goto findIndexpart0;
    }
    if (findIndexpart == 0)
    {
findIndexpart0:
        counters[0] ++;
        store_counter ++;
        sp.i -= 16;
        str(&r4.i, &sp.i, 0*4, 4, false, false, false);
        str(&r5.i, &sp.i, 1*4, 4, false, false, false);
        str(&r6.i, &sp.i, 2*4, 4, false, false, false);
        str(&lr.i, &sp.i, 3*4, 4, false, false, false);
        r5.i = r1.i - 1;
        r6.i = r1.i;
        r4.i = r0.i;
        r5.i = 0xff & (uint8_t)r5.i;
        tmp = r5.i - 1;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r5.i) >= ((uint32_t) 1);
        v = (r5.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
        if (z)
        {
            goto L4;
        }
        counters[1] ++;
        r1.i = r5.i;
        counters[2] ++;
        r3.i = r4.i + r0.i;
L2:
        counters[3] ++;
        r4.i = r4.i + r6.i;
        load_counter ++;
        ldr(&r3.i, &r3.i, 0, 1, false, true, true);
        load_counter ++;
        ldr(&r2.i, &r4.i, -1, 1, false, false, true);
        tmp = r2.i - r3.i;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
        v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
        if (n != v)
        {
            r0.i = r5.i;
        }
        load_counter ++;
        ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
        ldr(&r5.i, &sp.i, 1*4, 4, false, false, false);
        ldr(&r6.i, &sp.i, 2*4, 4, false, false, false);
        ldr(&pc.i, &sp.i, 3*4, 4, false, false, false);
        sp.i += 16;
        return;
L4:
        counters[4] ++;
        r3.i = r0.i;
        r0.i = 0;
        goto L2;
    }
    counters[14] ++;
    r3.i = r4.i + r0.i;
L20:
    counters[15] ++;
    r2.i = r4.i + r10.i;
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 1, false, true, true);
    load_counter ++;
    ldr(&r2.i, &r2.i, -1, 1, false, false, true);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    load_counter ++;
    if (n != v)
    {
        ldr(&r3.i, &r4.i, fp.i, 1, false, false, true);
    }
    if (n != v)
    {
        r0.i = fp.i;
    }
L19:
    counters[16] ++;
    r2.i = r4.i + r9.i;
    load_counter ++;
    ldr(&r2.i, &r2.i, -1, 1, false, false, true);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    load_counter ++;
    if (n != v)
    {
        ldr(&r3.i, &r4.i, r10.i, 1, false, false, true);
    }
    if (n != v)
    {
        r0.i = r10.i;
    }
L17:
    counters[17] ++;
    r2.i = r4.i + r8.i;
    load_counter ++;
    ldr(&r2.i, &r2.i, -1, 1, false, false, true);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    load_counter ++;
    if (n != v)
    {
        ldr(&r3.i, &r4.i, r9.i, 1, false, false, true);
    }
    if (n != v)
    {
        r0.i = r9.i;
    }
L15:
    counters[18] ++;
    r2.i = r4.i + r5.i;
    load_counter ++;
    ldr(&r2.i, &r2.i, -1, 1, false, false, true);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    load_counter ++;
    if (n != v)
    {
        ldr(&r3.i, &r4.i, r8.i, 1, false, false, true);
    }
    if (n != v)
    {
        r0.i = r8.i;
    }
L13:
    counters[19] ++;
    r2.i = r4.i + r7.i;
    load_counter ++;
    ldr(&r2.i, &r2.i, -1, 1, false, false, true);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    load_counter ++;
    if (n != v)
    {
        ldr(&r3.i, &r4.i, r5.i, 1, false, false, true);
    }
    if (n != v)
    {
        r0.i = r5.i;
    }
L11:
    counters[20] ++;
    r4.i = r4.i + r6.i;
    load_counter ++;
    ldr(&r2.i, &r4.i, -1, 1, false, false, true);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n != v)
    {
        r0.i = r7.i;
    }
    load_counter ++;
    ldr(&r3.i, &sp.i, 0*4, 4, false, false, false);
    ldr(&r4.i, &sp.i, 1*4, 4, false, false, false);
    ldr(&r5.i, &sp.i, 2*4, 4, false, false, false);
    ldr(&r6.i, &sp.i, 3*4, 4, false, false, false);
    ldr(&r7.i, &sp.i, 4*4, 4, false, false, false);
    ldr(&r8.i, &sp.i, 5*4, 4, false, false, false);
    ldr(&r9.i, &sp.i, 6*4, 4, false, false, false);
    ldr(&r10.i, &sp.i, 7*4, 4, false, false, false);
    ldr(&fp.i, &sp.i, 8*4, 4, false, false, false);
    ldr(&pc.i, &sp.i, 9*4, 4, false, false, false);
    sp.i += 40;
    return;
L21:
    counters[21] ++;
    r0.i = 0;
    return;
L22:
    counters[22] ++;
    r3.i = r4.i;
    r0.i = 0;
    goto L20;
    return;
}

void selectionSort()
{
    counters[23] ++;
    tmp = r1.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 1);
    v = (r1.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!c || z)
    {
        return;
    }
    counters[24] ++;
    r1.i = r1.i - 1;
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
    r7.i = 0xff & (uint8_t)r1.i;
    sp.i = sp.i - 12;
    r4.i = r0.i;
    goto L29;
L30:
    counters[25] ++;
    r8.i = r5.i - 1;
    r8.i = 0xff & (uint8_t)r8.i;
    tmp = r8.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) 1);
    v = (r8.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    if (z)
    {
        goto L54;
    }
    counters[26] ++;
    r9.i = r5.i - 2;
    r9.i = 0xff & (uint8_t)r9.i;
    tmp = r9.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r9.i) >= ((uint32_t) 1);
    v = (r9.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r9.i&0x80000000);
    if (z)
    {
        goto L55;
    }
    counters[27] ++;
    r10.i = r5.i - 3;
    r10.i = 0xff & (uint8_t)r10.i;
    tmp = r10.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r10.i) >= ((uint32_t) 1);
    v = (r10.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r10.i&0x80000000);
    if (z)
    {
        goto L56;
    }
    counters[28] ++;
    fp.i = r5.i - 4;
    fp.i = 0xff & (uint8_t)fp.i;
    tmp = fp.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) fp.i) >= ((uint32_t) 1);
    v = (fp.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (fp.i&0x80000000);
    if (z)
    {
        goto L57;
    }
    counters[29] ++;
    r1.i = r5.i - 5;
    r1.i = 0xff & (uint8_t)r1.i;
    tmp = r1.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 1);
    v = (r1.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (z)
    {
        goto L46;
    }
    counters[30] ++;
    r0.i = r4.i;
    store_counter ++;
    str(&r1.i, &sp.i, 4, 4, false, false, false);
    findIndexpart = 0;
    findIndex();
    counters[31] ++;
    load_counter ++;
    ldr(&r1.i, &sp.i, 4, 4, false, false, false);
    r2.i = r4.i + r0.i;
L39:
    counters[32] ++;
    ip.i = r4.i + fp.i;
    load_counter ++;
    ldr(&r3.i, &r2.i, 0, 1, false, true, true);
    load_counter ++;
    ldr(&ip.i, &ip.i, -1, 1, false, false, true);
    tmp = ip.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r3.i);
    v = (ip.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (n != v)
    {
        r2.i = r4.i + r1.i;
    }
    load_counter ++;
    if (n != v)
    {
        ldr(&r3.i, &r4.i, r1.i, 1, false, false, true);
    }
    if (n != v)
    {
        r0.i = r1.i;
    }
L38:
    counters[33] ++;
    r1.i = r4.i + r10.i;
    load_counter ++;
    ldr(&r1.i, &r1.i, -1, 1, false, false, true);
    tmp = r1.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r3.i);
    v = (r1.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (n != v)
    {
        r2.i = r4.i + fp.i;
    }
    load_counter ++;
    if (n != v)
    {
        ldr(&r3.i, &r4.i, fp.i, 1, false, false, true);
    }
    if (n != v)
    {
        r0.i = fp.i;
    }
L36:
    counters[34] ++;
    r1.i = r4.i + r9.i;
    load_counter ++;
    ldr(&r1.i, &r1.i, -1, 1, false, false, true);
    tmp = r1.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r3.i);
    v = (r1.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (n != v)
    {
        r2.i = r4.i + r10.i;
    }
    load_counter ++;
    if (n != v)
    {
        ldr(&r3.i, &r4.i, r10.i, 1, false, false, true);
    }
    if (n != v)
    {
        r0.i = r10.i;
    }
L34:
    counters[35] ++;
    r1.i = r4.i + r8.i;
    load_counter ++;
    ldr(&r1.i, &r1.i, -1, 1, false, false, true);
    tmp = r1.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r3.i);
    v = (r1.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (n != v)
    {
        r2.i = r4.i + r9.i;
    }
    load_counter ++;
    if (n != v)
    {
        ldr(&r3.i, &r4.i, r9.i, 1, false, false, true);
    }
    if (n != v)
    {
        r0.i = r9.i;
    }
L32:
    counters[36] ++;
    ip.i = r4.i + r7.i;
    load_counter ++;
    ldr(&r1.i, &ip.i, -1, 1, false, false, true);
    tmp = r1.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r3.i);
    v = (r1.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    r1.i = r4.i + r6.i;
    if (n == v)
    {
        goto L40;
    }
    counters[37] ++;
    load_counter ++;
    ldr(&r3.i, &r4.i, r8.i, 1, false, false, true);
    r2.i = r4.i + r8.i;
    load_counter ++;
    ldr(&r1.i, &r1.i, -1, 1, false, false, true);
    tmp = r1.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r3.i);
    v = (r1.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (n == v)
    {
        goto L42;
    }
L41:
    counters[38] ++;
    load_counter ++;
    ldr(&r3.i, &ip.i, 0, 1, false, true, true);
    r2.i = ip.i;
    load_counter ++;
    ldr(&r1.i, &r4.i, 0, 1, false, true, true);
L44:
    counters[39] ++;
    tmp = r5.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) 1);
    v = (r5.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    store_counter ++;
    str(&r3.i, &r4.i, 0, 1, false, true, false);
    store_counter ++;
    str(&r1.i, &r2.i, 0, 1, false, true, false);
    if (!c || z)
    {
        goto L27;
    }
L45:
    counters[40] ++;
    r4.i = r4.i + 1;
    r7.i = r7.i - 1;
L29:
    counters[41] ++;
    r5.i = 0xff & (uint8_t)r7.i;
    r1.i = r5.i + 1;
    tmp = r5.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) 1);
    v = (r5.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    r6.i = 0xff & (uint8_t)r1.i;
    if (!z)
    {
        goto L30;
    }
    counters[42] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 1, 1, false, false, true);
    load_counter ++;
    ldr(&r3.i, &r4.i, 0, 1, false, true, true);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    store_counter ++;
    if (n != v)
    {
        str(&r2.i, &r4.i, 0, 1, false, true, false);
    }
    store_counter ++;
    if (n != v)
    {
        str(&r3.i, &r4.i, 1, 1, false, false, false);
    }
L27:
    counters[43] ++;
    sp.i = sp.i + 12;
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
L40:
    counters[44] ++;
    load_counter ++;
    ldr(&r1.i, &r1.i, -1, 1, false, false, true);
    tmp = r1.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r3.i);
    v = (r1.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (n != v)
    {
        goto L41;
    }
    counters[45] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (z)
    {
        goto L45;
    }
L42:
    counters[46] ++;
    load_counter ++;
    ldr(&r1.i, &r4.i, 0, 1, false, true, true);
    goto L44;
L54:
    counters[47] ++;
    load_counter ++;
    ldr(&r3.i, &r4.i, 0, 1, false, true, true);
    r2.i = r4.i;
    r0.i = 0;
    goto L32;
L55:
    counters[48] ++;
    load_counter ++;
    ldr(&r3.i, &r4.i, 0, 1, false, true, true);
    r2.i = r4.i;
    r0.i = 0;
    goto L34;
L56:
    counters[49] ++;
    load_counter ++;
    ldr(&r3.i, &r4.i, 0, 1, false, true, true);
    r2.i = r4.i;
    r0.i = 0;
    goto L36;
L57:
    counters[50] ++;
    load_counter ++;
    ldr(&r3.i, &r4.i, 0, 1, false, true, true);
    r2.i = r4.i;
    r0.i = 0;
    goto L38;
L46:
    counters[51] ++;
    r2.i = r4.i;
    r0.i = 0;
    goto L39;
    return;
}

void main()
{
    malloc_start();
    counters[52] ++;
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
    counters[53] ++;
    r8.i = 34079;
    srand_help();
    counters[54] ++;
    r1.i = 1;
    r0.i = 10;
    r8.i = r8.i | (20971 << 16);
    calloc_help();
    counters[55] ++;
    r7.i = 100;
    r5.i = r0.i - 1;
    r6.i = r0.i + 9;
    r4.i = r0.i;
    r9.i = r5.i;
L59:
    counters[56] ++;
    rand_help();
    counters[57] ++;
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
        goto L59;
    }
    counters[58] ++;
    r1.i = 10;
    r0.i = r4.i;
    selectionSort();
    counters[59] ++;
    r7.i = (LC0 & 0xffff);
    r7.i = r7.i | (((uint32_t)LC0 >> 16) << 16);
L60:
    counters[60] ++;
    load_counter ++;
    ldr(&r2.i, &r5.i, 1, 1, true, false, true);
    r1.i = r7.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[61] ++;
    tmp = r5.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r6.i);
    v = (r5.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (!z)
    {
        goto L60;
    }
    counters[62] ++;
    r0.i = r4.i;
    free_help();
    counters[63] ++;
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

