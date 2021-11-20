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

reg r3, r2, r1, r5, r6, r0, r8, r4, r10, r9, r7;

int32_t LC0, LC1;

int counters[70] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[70] = {8,3,5,1,2,3,4,1,1,3,3,3,3,2,2,1,3,4,1,4,1,1,3,3,3,3,2,2,6,1,3,1,2,2,1,1,2,2,1,3,1,5,2,2,4,1,1,3,3,3,2,2,4,2,4,1,1,3,3,3,2,2,2,2,2,1,2,4,9,2};

int Millerpart;

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

    LC0 = (int32_t) ((uint8_t*) malloc(25) - malloc_0);
    strcpy(malloc_0+LC0, "\012%d is prime\012\000");

    LC1 = (int32_t) ((uint8_t*) malloc(29) - malloc_0);
    strcpy(malloc_0+LC1, "\012%d is not prime\012\000");

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "miller_rabin.c";

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

void idivmod()
{
    int32_t quot = r0.i / r1.i;
    int32_t rem = r0.i % r1.i;
    r0.i = quot;
    r1.i = rem;
}
void rand_help()
{
    r0.i = rand();
}

void mulmod()
{
    counters[41] ++;
    store_counter ++;
    sp.i -= 24;
    str(&r4.i, &sp.i, 0*4, 4, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false);
    str(&r7.i, &sp.i, 3*4, 4, false, false);
    str(&r8.i, &sp.i, 4*4, 4, false, false);
    str(&lr.i, &sp.i, 5*4, 4, false, false);
    r5.i = r1.i;
    r1.i = r2.i;
    r7.i = r2.i;
    idivmod();
    counters[42] ++;
    tmp = r5.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) 0);
    v = (r5.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (z || n != v)
    {
        goto L47;
    }
    counters[43] ++;
    r4.i = r1.i;
    r6.i = 0;
L46:
    counters[44] ++;
    tmp = r5.i & 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    r0.i = r6.i + r4.i;
    r1.i = r7.i;
    if (z)
    {
        goto L45;
    }
    counters[45] ++;
    idivmod();
    counters[46] ++;
    r6.i = r1.i;
L45:
    counters[47] ++;
    r0.i = (uint32_t)r4.i << 1;
    r1.i = r7.i;
    idivmod();
    counters[48] ++;
    r5.i = r5.i >> 1;
    z = r5.i == 0;
    n = r5.i & 0x80000000;
    c = r5.i & (1 << 1 - 1);
    r4.i = r1.i;
    if (!z)
    {
        goto L46;
    }
    counters[49] ++;
    r1.i = r7.i;
    r0.i = r6.i;
    idivmod();
    counters[50] ++;
    r0.i = r1.i;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false);
    ldr(&r7.i, &sp.i, 3*4, 4, false, false);
    ldr(&r8.i, &sp.i, 4*4, 4, false, false);
    ldr(&pc.i, &sp.i, 5*4, 4, false, false);
    sp.i += 24;
    return;
L47:
    counters[51] ++;
    r0.i = 0;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false);
    ldr(&r7.i, &sp.i, 3*4, 4, false, false);
    ldr(&r8.i, &sp.i, 4*4, 4, false, false);
    ldr(&pc.i, &sp.i, 5*4, 4, false, false);
    sp.i += 24;
    return;

}

void modulo()
{
    counters[52] ++;
    store_counter ++;
    sp.i -= 24;
    str(&r4.i, &sp.i, 0*4, 4, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false);
    str(&r7.i, &sp.i, 3*4, 4, false, false);
    str(&r8.i, &sp.i, 4*4, 4, false, false);
    str(&lr.i, &sp.i, 5*4, 4, false, false);
    r5.i = r1.i - 0;
    z = r5.i == 0;
    n = r5.i & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 0);
    v = (r1.i&0x80000000) != (0&0x80000000) && (r5.i&0x80000000) != (r1.i&0x80000000);
    r7.i = r2.i;
    if (z || n != v)
    {
        goto L57;
    }
    counters[53] ++;
    r4.i = r0.i;
    r6.i = 1;
L56:
    counters[54] ++;
    tmp = r5.i & 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    r1.i = r7.i;
    r0.i = r4.i * r6.i;
    if (z)
    {
        goto L55;
    }
    counters[55] ++;
    idivmod();
    counters[56] ++;
    r6.i = r1.i;
L55:
    counters[57] ++;
    r0.i = r4.i * r4.i;
    r1.i = r7.i;
    idivmod();
    counters[58] ++;
    r5.i = r5.i >> 1;
    z = r5.i == 0;
    n = r5.i & 0x80000000;
    c = r5.i & (1 << 1 - 1);
    r4.i = r1.i;
    if (!z)
    {
        goto L56;
    }
L54:
    counters[59] ++;
    r1.i = r7.i;
    r0.i = r6.i;
    idivmod();
    counters[60] ++;
    r0.i = r1.i;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false);
    ldr(&r7.i, &sp.i, 3*4, 4, false, false);
    ldr(&r8.i, &sp.i, 4*4, 4, false, false);
    ldr(&pc.i, &sp.i, 5*4, 4, false, false);
    sp.i += 24;
    return;
L57:
    counters[61] ++;
    r6.i = 1;
    goto L54;
    return;
}

void Miller()
{
    if (Millerpart == -1)
    {
        counters[62] ++;
        tmp = r0.i - 1;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r0.i) >= ((uint32_t) 1);
        v = (r0.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
        if (z || n != v)
        {
            goto L63;
        }
        counters[63] ++;
        tmp = r0.i - 2;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r0.i) >= ((uint32_t) 2);
        v = (r0.i&0x80000000) != (2&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
        if (z)
        {
            goto L65;
        }
        counters[64] ++;
        tmp = r0.i & 1;
        z = tmp == 0;
        n = tmp & 0x80000000;
        if (z)
        {
            goto L63;
        }
L65:
        counters[65] ++;
        goto Millerpart0;
L63:
        counters[66] ++;
        r0.i = 0;
        return;

    }

    void main()
    {
        malloc_start();
        counters[67] ++;
        r1.i = 5;
        r0.i = 131;
        store_counter ++;
        sp.i -= 8;
        str(&r4.i, &sp.i, 0*4, 4, false, false);
        str(&lr.i, &sp.i, 1*4, 4, false, false);
        Millerpart = 0;
        Miller();
        counters[68] ++;
        tmp = r0.i - 0;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r0.i) >= ((uint32_t) 0);
        v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
        r0.i = 1;
        if (!z)
        {
            r1.i = (LC0 & 0xffff);
        }
        if (z)
        {
            r1.i = (LC1 & 0xffff);
        }
        if (!z)
        {
            r1.i = r1.i | (((uint32_t)LC0 >> 16) << 16);
        }
        if (z)
        {
            r1.i = r1.i | (((uint32_t)LC1 >> 16) << 16);
        }
        if (!z)
        {
            r2.i = 131;
        }
        if (z)
        {
            r2.i = 131;
        }
        printf(malloc_0+r1.i, r2.i);
        counters[69] ++;
        r0.i = 0;
        load_counter ++;
        ldr(&r4.i, &sp.i, 0*4, 4, false, false);
        ldr(&pc.i, &sp.i, 1*4, 4, false, false);
        sp.i += 8;
        counter_summary();
        return;

    }

