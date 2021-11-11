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
char* malloc_0 = 0;

reg r2, r3, r6, r5, r9, r0, r4, r8, r1, r7;

int32_t LC0, LC1;

int counters[50] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[50] = {11,2,30,9,1,8,13,4,3,4,11,30,14,1,13,13,4,3,4,9,2,4,7,2,5,12,10,3,1,10,13,2,5,8,10,4,10,10,10,2,3,4,1,3,11,3,4,1,4,4};

void ldr(int32_t *target, int32_t *address, int32_t offset, int bytes, bool update, bool post_index)
{
    char *ptr;
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
    char *ptr;
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
    malloc_0 = (char*) malloc(1);
    char* stack_ptr = (char*) malloc(1000);
    sp.i = (int32_t) (stack_ptr - malloc_0) + 999;
    fp = sp;

    LC0 = (int32_t) ((char*) malloc(27) - malloc_0);
    strcpy(malloc_0+LC0, "\012%lld is prime\012\000");

    LC1 = (int32_t) ((char*) malloc(31) - malloc_0);
    strcpy(malloc_0+LC1, "\012%lld is not prime\012\000");

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "test.c";

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


void mulmod()
{
    counters[0] ++;
    store_counter ++;
    sp.i -= 32;
    str(&r4.i, &sp.i, 0*4, 4, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false);
    str(&r7.i, &sp.i, 3*4, 4, false, false);
    str(&r8.i, &sp.i, 4*4, 4, false, false);
    str(&r9.i, &sp.i, 5*4, 4, false, false);
    str(&fp.i, &sp.i, 6*4, 4, false, false);
    str(&lr.i, &sp.i, 7*4, 4, false, false);
    fp.i = sp.i + 28;
    sp.i = sp.i - 72;
    store_counter ++;
    str(&r0.i, &fp.i, -52, 8, false, false);
    store_counter ++;
    str(&r2.i, &fp.i, -60, 8, false, false);
    r2.i = 0;
    r3.i = 0;
    store_counter ++;
    str(&r2.i, &fp.i, -36, 8, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, -52, 8, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, 4, 8, false, false);
    __aeabi_ldivmod();
    counters[1] ++;
    store_counter ++;
    str(&r2.i, &fp.i, -44, 8, false, false);
    goto L2;
L4:
    counters[2] ++;
    load_counter ++;
    ldr(&r0.i, &fp.i, -60, 8, false, false);
    r3.i = r1.i >> 31;
    r2.i = r3.i;
    r3.i = r2.i >> 31;
    ip.i = r0.i ^ r2.i;
    store_counter ++;
    str(&ip.i, &fp.i, -84, 4, false, false);
    r1.i = r1.i ^ r3.i;
    store_counter ++;
    str(&r1.i, &fp.i, -80, 4, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, -84, 8, false, false);
    ip.i = r0.i;
    ip.i = ip.i - r2.i;
    z = ip.i == 0;
    n = ip.i & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r2.i);
    v = (ip.i&0x80000000) != (r2.i&0x80000000) && (ip.i&0x80000000) != (ip.i&0x80000000);
    store_counter ++;
    str(&ip.i, &fp.i, -68, 4, false, false);
    r1.i = r1.i - r3.i - !c;
    store_counter ++;
    str(&r1.i, &fp.i, -64, 4, false, false);
    r0.i = 1;
    r1.i = 0;
    load_counter ++;
    ldr(&ip.i, &fp.i, -68, 4, false, false);
    r8.i = ip.i & r0.i;
    load_counter ++;
    ldr(&ip.i, &fp.i, -64, 4, false, false);
    r9.i = ip.i & r1.i;
    r6.i = r8.i ^ r2.i;
    r7.i = r9.i ^ r3.i;
    r1.i = r6.i - r2.i;
    z = r1.i == 0;
    n = r1.i & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) r2.i);
    v = (r6.i&0x80000000) != (r2.i&0x80000000) && (r1.i&0x80000000) != (r6.i&0x80000000);
    store_counter ++;
    str(&r1.i, &fp.i, -92, 4, false, false);
    r3.i = r7.i - r3.i - !c;
    store_counter ++;
    str(&r3.i, &fp.i, -88, 4, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -92, 8, false, false);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        tmp = r2.i - 1;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r2.i) >= ((uint32_t) 1);
        v = (r2.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    }
    if (!z)
    {
        goto L3;
    }
    counters[3] ++;
    load_counter ++;
    ldr(&r0.i, &fp.i, -36, 8, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -44, 8, false, false);
    ip.i = r0.i + r2.i;
    z = ip.i == 0;
    n = ip.i & 0x80000000;
    c = ((uint32_t) ip.i) < ((uint32_t) r0.i);
    v = (r0.i&0x80000000) == (r2.i&0x80000000) && (ip.i&0x80000000) != (r0.i&0x80000000);
    store_counter ++;
    str(&ip.i, &fp.i, -76, 4, false, false);
    r3.i = r1.i + r3.i + c;
    store_counter ++;
    str(&r3.i, &fp.i, -72, 4, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, 4, 8, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, -76, 8, false, false);
    __aeabi_ldivmod();
    counters[4] ++;
    store_counter ++;
    str(&r2.i, &fp.i, -36, 8, false, false);
L3:
    counters[5] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -44, 8, false, false);
    r1.i = r2.i + r2.i;
    z = r1.i == 0;
    n = r1.i & 0x80000000;
    c = ((uint32_t) r1.i) < ((uint32_t) r2.i);
    v = (r2.i&0x80000000) == (r2.i&0x80000000) && (r1.i&0x80000000) != (r2.i&0x80000000);
    store_counter ++;
    str(&r1.i, &fp.i, -100, 4, false, false);
    r3.i = r3.i + r3.i + c;
    store_counter ++;
    str(&r3.i, &fp.i, -96, 4, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, -100, 8, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, 4, 8, false, false);
    __aeabi_ldivmod();
    counters[6] ++;
    store_counter ++;
    str(&r2.i, &fp.i, -44, 8, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, -60, 8, false, false);
    r3.i = (uint32_t)r1.i >> 31;
    r2.i = r3.i;
    r3.i = 0;
    r4.i = r2.i + r0.i;
    z = r4.i == 0;
    n = r4.i & 0x80000000;
    c = ((uint32_t) r4.i) < ((uint32_t) r2.i);
    v = (r2.i&0x80000000) == (r0.i&0x80000000) && (r4.i&0x80000000) != (r2.i&0x80000000);
    r5.i = r3.i + r1.i + c;
    r2.i = 0;
    r3.i = 0;
    r2.i = (uint32_t)r4.i >> 1;
    r2.i = r2.i | ((uint32_t)r5.i << 31);
    r3.i = r5.i >> 1;
    store_counter ++;
    str(&r2.i, &fp.i, -60, 8, false, false);
L2:
    counters[7] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -60, 8, false, false);
    tmp = r2.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) 1);
    v = (r2.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    r3.i = r3.i - 0 - !c;
    z = r3.i == 0;
    n = r3.i & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (r3.i&0x80000000) != (r3.i&0x80000000);
    if (n == v)
    {
        goto L4;
    }
    counters[8] ++;
    load_counter ++;
    ldr(&r0.i, &fp.i, -36, 8, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, 4, 8, false, false);
    __aeabi_ldivmod();
    counters[9] ++;
    r0.i = r2.i;
    r1.i = r3.i;
    sp.i = fp.i - 28;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false);
    ldr(&r7.i, &sp.i, 3*4, 4, false, false);
    ldr(&r8.i, &sp.i, 4*4, 4, false, false);
    ldr(&r9.i, &sp.i, 5*4, 4, false, false);
    ldr(&fp.i, &sp.i, 6*4, 4, false, false);
    ldr(&pc.i, &sp.i, 7*4, 4, false, false);
    sp.i += 32;
    return;

}

void modulo()
{
    counters[10] ++;
    store_counter ++;
    sp.i -= 32;
    str(&r4.i, &sp.i, 0*4, 4, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false);
    str(&r7.i, &sp.i, 3*4, 4, false, false);
    str(&r8.i, &sp.i, 4*4, 4, false, false);
    str(&r9.i, &sp.i, 5*4, 4, false, false);
    str(&fp.i, &sp.i, 6*4, 4, false, false);
    str(&lr.i, &sp.i, 7*4, 4, false, false);
    fp.i = sp.i + 28;
    sp.i = sp.i - 56;
    store_counter ++;
    str(&r0.i, &fp.i, -52, 8, false, false);
    store_counter ++;
    str(&r2.i, &fp.i, -60, 8, false, false);
    r2.i = 1;
    r3.i = 0;
    store_counter ++;
    str(&r2.i, &fp.i, -36, 8, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -52, 8, false, false);
    store_counter ++;
    str(&r2.i, &fp.i, -44, 8, false, false);
    goto L7;
L9:
    counters[11] ++;
    load_counter ++;
    ldr(&r0.i, &fp.i, -60, 8, false, false);
    r3.i = r1.i >> 31;
    r2.i = r3.i;
    r3.i = r2.i >> 31;
    ip.i = r0.i ^ r2.i;
    store_counter ++;
    str(&ip.i, &fp.i, -68, 4, false, false);
    r1.i = r1.i ^ r3.i;
    store_counter ++;
    str(&r1.i, &fp.i, -64, 4, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, -68, 8, false, false);
    ip.i = r0.i;
    r6.i = ip.i - r2.i;
    z = r6.i == 0;
    n = r6.i & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r2.i);
    v = (ip.i&0x80000000) != (r2.i&0x80000000) && (r6.i&0x80000000) != (ip.i&0x80000000);
    r7.i = r1.i - r3.i - !c;
    r0.i = 1;
    r1.i = 0;
    ip.i = r6.i & r0.i;
    store_counter ++;
    str(&ip.i, &fp.i, -76, 4, false, false);
    r1.i = r7.i & r1.i;
    store_counter ++;
    str(&r1.i, &fp.i, -72, 4, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, -76, 8, false, false);
    ip.i = r0.i;
    r8.i = ip.i ^ r2.i;
    r9.i = r1.i ^ r3.i;
    r1.i = r8.i - r2.i;
    z = r1.i == 0;
    n = r1.i & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) r2.i);
    v = (r8.i&0x80000000) != (r2.i&0x80000000) && (r1.i&0x80000000) != (r8.i&0x80000000);
    store_counter ++;
    str(&r1.i, &fp.i, -84, 4, false, false);
    r3.i = r9.i - r3.i - !c;
    store_counter ++;
    str(&r3.i, &fp.i, -80, 4, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -84, 8, false, false);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        tmp = r2.i - 1;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r2.i) >= ((uint32_t) 1);
        v = (r2.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    }
    if (!z)
    {
        goto L8;
    }
    counters[12] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -32, 4, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -44, 4, false, false);
    r1.i = r2.i * r3.i;
    load_counter ++;
    ldr(&r2.i, &fp.i, -40, 4, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -36, 4, false, false);
    r3.i = r3.i * r2.i;
    ip.i = r1.i + r3.i;
    load_counter ++;
    ldr(&r2.i, &fp.i, -36, 4, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -44, 4, false, false);
    r3.i = ip.i + r1.i;
    r1.i = r3.i;
    load_counter ++;
    ldr(&r2.i, &fp.i, 4, 8, false, false);
    __aeabi_ldivmod();
    counters[13] ++;
    store_counter ++;
    str(&r2.i, &fp.i, -36, 8, false, false);
L8:
    counters[14] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -40, 4, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -44, 4, false, false);
    r1.i = r2.i * r3.i;
    load_counter ++;
    ldr(&r2.i, &fp.i, -40, 4, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -44, 4, false, false);
    r3.i = r3.i * r2.i;
    r2.i = r1.i + r3.i;
    load_counter ++;
    ldr(&r3.i, &fp.i, -44, 4, false, false);
    r3.i = r2.i + r1.i;
    r1.i = r3.i;
    load_counter ++;
    ldr(&r2.i, &fp.i, 4, 8, false, false);
    __aeabi_ldivmod();
    counters[15] ++;
    store_counter ++;
    str(&r2.i, &fp.i, -44, 8, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, -60, 8, false, false);
    r3.i = (uint32_t)r1.i >> 31;
    r2.i = r3.i;
    r3.i = 0;
    r4.i = r2.i + r0.i;
    z = r4.i == 0;
    n = r4.i & 0x80000000;
    c = ((uint32_t) r4.i) < ((uint32_t) r2.i);
    v = (r2.i&0x80000000) == (r0.i&0x80000000) && (r4.i&0x80000000) != (r2.i&0x80000000);
    r5.i = r3.i + r1.i + c;
    r2.i = 0;
    r3.i = 0;
    r2.i = (uint32_t)r4.i >> 1;
    r2.i = r2.i | ((uint32_t)r5.i << 31);
    r3.i = r5.i >> 1;
    store_counter ++;
    str(&r2.i, &fp.i, -60, 8, false, false);
L7:
    counters[16] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -60, 8, false, false);
    tmp = r2.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) 1);
    v = (r2.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    r3.i = r3.i - 0 - !c;
    z = r3.i == 0;
    n = r3.i & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (r3.i&0x80000000) != (r3.i&0x80000000);
    if (n == v)
    {
        goto L9;
    }
    counters[17] ++;
    load_counter ++;
    ldr(&r0.i, &fp.i, -36, 8, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, 4, 8, false, false);
    __aeabi_ldivmod();
    counters[18] ++;
    r0.i = r2.i;
    r1.i = r3.i;
    sp.i = fp.i - 28;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false);
    ldr(&r7.i, &sp.i, 3*4, 4, false, false);
    ldr(&r8.i, &sp.i, 4*4, 4, false, false);
    ldr(&r9.i, &sp.i, 5*4, 4, false, false);
    ldr(&fp.i, &sp.i, 6*4, 4, false, false);
    ldr(&pc.i, &sp.i, 7*4, 4, false, false);
    sp.i += 32;
    return;

}

void Miller()
{
    counters[19] ++;
    store_counter ++;
    sp.i -= 32;
    str(&r4.i, &sp.i, 0*4, 4, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false);
    str(&r7.i, &sp.i, 3*4, 4, false, false);
    str(&r8.i, &sp.i, 4*4, 4, false, false);
    str(&r9.i, &sp.i, 5*4, 4, false, false);
    str(&fp.i, &sp.i, 6*4, 4, false, false);
    str(&lr.i, &sp.i, 7*4, 4, false, false);
    fp.i = sp.i + 28;
    sp.i = sp.i - 128;
    store_counter ++;
    str(&r0.i, &fp.i, -76, 8, false, false);
    store_counter ++;
    str(&r2.i, &fp.i, -80, 4, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -76, 8, false, false);
    tmp = r2.i - 2;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) 2);
    v = (r2.i&0x80000000) != (2&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    r3.i = r3.i - 0 - !c;
    z = r3.i == 0;
    n = r3.i & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (r3.i&0x80000000) != (r3.i&0x80000000);
    if (n == v)
    {
        goto L12;
    }
    counters[20] ++;
    r3.i = 0;
    goto L13;
L12:
    counters[21] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -76, 8, false, false);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        tmp = r2.i - 2;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r2.i) >= ((uint32_t) 2);
        v = (r2.i&0x80000000) != (2&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    }
    if (z)
    {
        goto L14;
    }
    counters[22] ++;
    load_counter ++;
    ldr(&r0.i, &fp.i, -76, 8, false, false);
    r2.i = 1;
    r3.i = 0;
    r4.i = r0.i & r2.i;
    r5.i = r1.i & r3.i;
    r3.i = r4.i | r5.i;
    z = r3.i == 0;
    n = r3.i & 0x80000000;
    if (!z)
    {
        goto L14;
    }
    counters[23] ++;
    r3.i = 0;
    goto L13;
L14:
    counters[24] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -76, 8, false, false);
    r8.i = r2.i - 1;
    z = r8.i == 0;
    n = r8.i & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) 1);
    v = (r2.i&0x80000000) != (1&0x80000000) && (r8.i&0x80000000) != (r2.i&0x80000000);
    r9.i = r3.i - 0 - !c;
    store_counter ++;
    str(&r8.i, &fp.i, -44, 8, false, false);
    goto L15;
L16:
    counters[25] ++;
    load_counter ++;
    ldr(&r0.i, &fp.i, -44, 8, false, false);
    r3.i = (uint32_t)r1.i >> 31;
    r2.i = r3.i;
    r3.i = 0;
    r6.i = r2.i + r0.i;
    z = r6.i == 0;
    n = r6.i & 0x80000000;
    c = ((uint32_t) r6.i) < ((uint32_t) r2.i);
    v = (r2.i&0x80000000) == (r0.i&0x80000000) && (r6.i&0x80000000) != (r2.i&0x80000000);
    r7.i = r3.i + r1.i + c;
    r2.i = 0;
    r3.i = 0;
    r2.i = (uint32_t)r6.i >> 1;
    r2.i = r2.i | ((uint32_t)r7.i << 31);
    r3.i = r7.i >> 1;
    store_counter ++;
    str(&r2.i, &fp.i, -44, 8, false, false);
L15:
    counters[26] ++;
    load_counter ++;
    ldr(&r0.i, &fp.i, -44, 8, false, false);
    r2.i = 1;
    r3.i = 0;
    ip.i = r0.i & r2.i;
    store_counter ++;
    str(&ip.i, &fp.i, -92, 4, false, false);
    r3.i = r1.i & r3.i;
    store_counter ++;
    str(&r3.i, &fp.i, -88, 4, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -92, 8, false, false);
    r3.i = r2.i | r3.i;
    z = r3.i == 0;
    n = r3.i & 0x80000000;
    if (z)
    {
        goto L16;
    }
    counters[27] ++;
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -32, 4, false, false);
    goto L17;
L22:
    counters[28] ++;
    rand();
    counters[29] ++;
    r3.i = r0.i;
    r0.i = r3.i;
    r1.i = r0.i >> 31;
    load_counter ++;
    ldr(&r2.i, &fp.i, -76, 8, false, false);
    ip.i = r2.i - 1;
    z = ip.i == 0;
    n = ip.i & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) 1);
    v = (r2.i&0x80000000) != (1&0x80000000) && (ip.i&0x80000000) != (r2.i&0x80000000);
    store_counter ++;
    str(&ip.i, &fp.i, -100, 4, false, false);
    r3.i = r3.i - 0 - !c;
    store_counter ++;
    str(&r3.i, &fp.i, -96, 4, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -100, 8, false, false);
    __aeabi_ldivmod();
    counters[30] ++;
    r1.i = r2.i + 1;
    z = r1.i == 0;
    n = r1.i & 0x80000000;
    c = ((uint32_t) r1.i) < ((uint32_t) r2.i);
    v = (r2.i&0x80000000) == (1&0x80000000) && (r1.i&0x80000000) != (r2.i&0x80000000);
    store_counter ++;
    str(&r1.i, &fp.i, -140, 4, false, false);
    r3.i = r3.i + 0 + c;
    store_counter ++;
    str(&r3.i, &fp.i, -136, 4, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -140, 8, false, false);
    store_counter ++;
    str(&r2.i, &fp.i, -68, 8, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -44, 8, false, false);
    store_counter ++;
    str(&r2.i, &fp.i, -52, 8, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -76, 8, false, false);
    store_counter ++;
    str(&r2.i, &sp.i, 0, 8, false, true);
    load_counter ++;
    ldr(&r2.i, &fp.i, -52, 8, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, -68, 8, false, false);
    modulo();
    counters[31] ++;
    store_counter ++;
    str(&r0.i, &fp.i, -60, 8, false, false);
    goto L18;
L20:
    counters[32] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -76, 8, false, false);
    store_counter ++;
    str(&r2.i, &sp.i, 0, 8, false, true);
    load_counter ++;
    ldr(&r2.i, &fp.i, -60, 8, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, -60, 8, false, false);
    mulmod();
    counters[33] ++;
    store_counter ++;
    str(&r0.i, &fp.i, -60, 8, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -52, 8, false, false);
    r1.i = r2.i + r2.i;
    z = r1.i == 0;
    n = r1.i & 0x80000000;
    c = ((uint32_t) r1.i) < ((uint32_t) r2.i);
    v = (r2.i&0x80000000) == (r2.i&0x80000000) && (r1.i&0x80000000) != (r2.i&0x80000000);
    store_counter ++;
    str(&r1.i, &fp.i, -148, 4, false, false);
    r3.i = r3.i + r3.i + c;
    store_counter ++;
    str(&r3.i, &fp.i, -144, 4, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -148, 8, false, false);
    store_counter ++;
    str(&r2.i, &fp.i, -52, 8, false, false);
L18:
    counters[34] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -76, 8, false, false);
    r1.i = r2.i - 1;
    z = r1.i == 0;
    n = r1.i & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) 1);
    v = (r2.i&0x80000000) != (1&0x80000000) && (r1.i&0x80000000) != (r2.i&0x80000000);
    store_counter ++;
    str(&r1.i, &fp.i, -108, 4, false, false);
    r3.i = r3.i - 0 - !c;
    store_counter ++;
    str(&r3.i, &fp.i, -104, 4, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -52, 8, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, -108, 8, false, false);
    tmp = r3.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r1.i);
    v = (r3.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        tmp = r2.i - r0.i;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r2.i) >= ((uint32_t) r0.i);
        v = (r2.i&0x80000000) != (r0.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    }
    if (z)
    {
        goto L19;
    }
    counters[35] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -60, 8, false, false);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        tmp = r2.i - 1;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r2.i) >= ((uint32_t) 1);
        v = (r2.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    }
    if (z)
    {
        goto L19;
    }
    counters[36] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -76, 8, false, false);
    r1.i = r2.i - 1;
    z = r1.i == 0;
    n = r1.i & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) 1);
    v = (r2.i&0x80000000) != (1&0x80000000) && (r1.i&0x80000000) != (r2.i&0x80000000);
    store_counter ++;
    str(&r1.i, &fp.i, -116, 4, false, false);
    r3.i = r3.i - 0 - !c;
    store_counter ++;
    str(&r3.i, &fp.i, -112, 4, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -60, 8, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, -116, 8, false, false);
    tmp = r3.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r1.i);
    v = (r3.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        tmp = r2.i - r0.i;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r2.i) >= ((uint32_t) r0.i);
        v = (r2.i&0x80000000) != (r0.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    }
    if (!z)
    {
        goto L20;
    }
L19:
    counters[37] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -76, 8, false, false);
    r1.i = r2.i - 1;
    z = r1.i == 0;
    n = r1.i & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) 1);
    v = (r2.i&0x80000000) != (1&0x80000000) && (r1.i&0x80000000) != (r2.i&0x80000000);
    store_counter ++;
    str(&r1.i, &fp.i, -124, 4, false, false);
    r3.i = r3.i - 0 - !c;
    store_counter ++;
    str(&r3.i, &fp.i, -120, 4, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -60, 8, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, -124, 8, false, false);
    tmp = r3.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r1.i);
    v = (r3.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        tmp = r2.i - r0.i;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r2.i) >= ((uint32_t) r0.i);
        v = (r2.i&0x80000000) != (r0.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    }
    if (z)
    {
        goto L21;
    }
    counters[38] ++;
    load_counter ++;
    ldr(&r0.i, &fp.i, -52, 8, false, false);
    r2.i = 1;
    r3.i = 0;
    ip.i = r0.i & r2.i;
    store_counter ++;
    str(&ip.i, &fp.i, -132, 4, false, false);
    r3.i = r1.i & r3.i;
    store_counter ++;
    str(&r3.i, &fp.i, -128, 4, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -132, 8, false, false);
    r3.i = r2.i | r3.i;
    z = r3.i == 0;
    n = r3.i & 0x80000000;
    if (!z)
    {
        goto L21;
    }
    counters[39] ++;
    r3.i = 0;
    goto L13;
L21:
    counters[40] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -32, 4, false, false);
    r3.i = r3.i + 1;
    store_counter ++;
    str(&r3.i, &fp.i, -32, 4, false, false);
L17:
    counters[41] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -32, 4, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -80, 4, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n != v)
    {
        goto L22;
    }
    counters[42] ++;
    r3.i = 1;
L13:
    counters[43] ++;
    r0.i = r3.i;
    sp.i = fp.i - 28;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false);
    ldr(&r7.i, &sp.i, 3*4, 4, false, false);
    ldr(&r8.i, &sp.i, 4*4, 4, false, false);
    ldr(&r9.i, &sp.i, 5*4, 4, false, false);
    ldr(&fp.i, &sp.i, 6*4, 4, false, false);
    ldr(&pc.i, &sp.i, 7*4, 4, false, false);
    sp.i += 32;
    return;

}

void main()
{
    malloc_start();
    counters[44] ++;
    store_counter ++;
    sp.i -= 8;
    str(&fp.i, &sp.i, 0*4, 4, false, false);
    str(&lr.i, &sp.i, 1*4, 4, false, false);
    fp.i = sp.i + 4;
    sp.i = sp.i - 16;
    r3.i = 5;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false);
    r2.i = 117;
    r3.i = 0;
    store_counter ++;
    str(&r2.i, &fp.i, -20, 8, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -8, 4, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, -20, 8, false, false);
    Miller();
    counters[45] ++;
    r3.i = r0.i;
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L24;
    }
    counters[46] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -20, 8, false, false);
    r0.i = (LC0 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC0 >> 16) << 16);
    printf(malloc_0+r0.i, r1.i);
    counters[47] ++;
    goto L25;
L24:
    counters[48] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -20, 8, false, false);
    r0.i = (LC1 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC1 >> 16) << 16);
    printf(malloc_0+r0.i, r1.i);
L25:
    counters[49] ++;
    r3.i = 0;
    r0.i = r3.i;
    sp.i = fp.i - 4;
    load_counter ++;
    ldr(&fp.i, &sp.i, 0*4, 4, false, false);
    ldr(&pc.i, &sp.i, 1*4, 4, false, false);
    sp.i += 8;
    counter_summary();
    return;

}

