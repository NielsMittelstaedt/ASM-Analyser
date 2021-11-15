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

reg r7, r4, r1, r2, r0, r6, r8, r5, r3;

int32_t LC0;

int counters[21] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[21] = {12,3,5,6,2,4,2,1,10,3,2,7,3,3,2,1,3,6,10,2,69};

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

    LC0 = (int32_t) ((uint8_t*) malloc(16) - malloc_0);
    strcpy(malloc_0+LC0, "r1: %d\012\000");

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "test1.c";

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

void malloc_help()
{
    char* ptr = (char*) malloc(r0.i);
    r0.i = (int32_t) (ptr - malloc_0);
}

void ldr()
{
    counters[0] ++;
    store_counter ++;
    sp.i -= 20;
    str(&r4.i, &sp.i, 0*4, 4, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false);
    str(&r7.i, &sp.i, 3*4, 4, false, false);
    str(&lr.i, &sp.i, 4*4, 4, false, false);
    ip.i = (LC0 & 0xffff);
    load_counter ++;
    ldr(&r6.i, &sp.i, 24, 1, false, false);
    ip.i = ip.i | (((uint32_t)LC0 >> 16) << 16);
    load_counter ++;
    ldr(&lr.i, &r1.i, 0, 4, false, true);
    load_counter ++;
    ldr(&r5.i, &ip.i, 0, 4, false, true);
    tmp = r6.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) 0);
    v = (r6.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    ip.i = 0;
    load_counter ++;
    ldr(&r7.i, &sp.i, 20, 1, false, false);
    r5.i = r5.i + lr.i;
    store_counter ++;
    str(&ip.i, &r0.i, 0, 4, false, true);
    if (!z)
    {
        goto L2;
    }
    counters[1] ++;
    tmp = r3.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) ip.i);
    v = (r3.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    r5.i = r5.i + r2.i;
    if (z || n != v)
    {
        goto L7;
    }
L3:
    counters[2] ++;
    r3.i = r3.i - 1;
    lr.i = r5.i - 1;
    r5.i = r5.i + r3.i;
    r3.i = 0;
    ip.i = r3.i;
L6:
    counters[3] ++;
    load_counter ++;
    ldr(&r4.i, &lr.i, 1, 1, true, false);
    tmp = r5.i - lr.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) lr.i);
    v = (r5.i&0x80000000) != (lr.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    ip.i = ip.i + ((uint32_t)r4.i << r3.i);
    r3.i = r3.i + 8;
    store_counter ++;
    str(&ip.i, &r0.i, 0, 4, false, true);
    if (!z)
    {
        goto L6;
    }
L7:
    counters[4] ++;
    r3.i = r6.i | r7.i;
    z = r3.i == 0;
    n = r3.i & 0x80000000;
    load_counter ++;
    if (z)
    {
        ldr(&r4.i, &sp.i, 0*4, 4, false, false);
        ldr(&r5.i, &sp.i, 1*4, 4, false, false);
        ldr(&r6.i, &sp.i, 2*4, 4, false, false);
        ldr(&r7.i, &sp.i, 3*4, 4, false, false);
        ldr(&pc.i, &sp.i, 4*4, 4, false, false);
        sp.i += 20;
        return;
    }
L4:
    counters[5] ++;
    load_counter ++;
    ldr(&r3.i, &r1.i, 0, 4, false, true);
    r2.i = r3.i + r2.i;
    store_counter ++;
    str(&r2.i, &r1.i, 0, 4, false, true);
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false);
    ldr(&r7.i, &sp.i, 3*4, 4, false, false);
    ldr(&pc.i, &sp.i, 4*4, 4, false, false);
    sp.i += 20;
    return;
L2:
    counters[6] ++;
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z && n == v)
    {
        goto L3;
    }
    counters[7] ++;
    goto L4;
    return;
}

void str()
{
    counters[8] ++;
    store_counter ++;
    sp.i -= 20;
    str(&r4.i, &sp.i, 0*4, 4, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false);
    str(&r7.i, &sp.i, 3*4, 4, false, false);
    str(&lr.i, &sp.i, 4*4, 4, false, false);
    ip.i = (LC0 & 0xffff);
    load_counter ++;
    ldr(&r6.i, &sp.i, 24, 1, false, false);
    ip.i = ip.i | (((uint32_t)LC0 >> 16) << 16);
    load_counter ++;
    ldr(&lr.i, &r1.i, 0, 4, false, true);
    load_counter ++;
    ldr(&r4.i, &ip.i, 0, 4, false, true);
    tmp = r6.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) 0);
    v = (r6.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    load_counter ++;
    ldr(&r7.i, &sp.i, 20, 1, false, false);
    r4.i = r4.i + lr.i;
    if (!z)
    {
        goto L12;
    }
    counters[9] ++;
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    r4.i = r4.i + r2.i;
    if (z || n != v)
    {
        goto L17;
    }
L13:
    counters[10] ++;
    r4.i = r4.i - 1;
    ip.i = 0;
L16:
    counters[11] ++;
    load_counter ++;
    ldr(&lr.i, &r0.i, 0, 4, false, true);
    r5.i = (uint32_t)ip.i << 3;
    ip.i = ip.i + 1;
    tmp = r3.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) ip.i);
    v = (r3.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    lr.i = lr.i >> r5.i;
    store_counter ++;
    str(&lr.i, &r4.i, 1, 1, true, false);
    if (!z && n == v)
    {
        goto L16;
    }
L17:
    counters[12] ++;
    r3.i = r6.i | r7.i;
    z = r3.i == 0;
    n = r3.i & 0x80000000;
    load_counter ++;
    if (z)
    {
        ldr(&r4.i, &sp.i, 0*4, 4, false, false);
        ldr(&r5.i, &sp.i, 1*4, 4, false, false);
        ldr(&r6.i, &sp.i, 2*4, 4, false, false);
        ldr(&r7.i, &sp.i, 3*4, 4, false, false);
        ldr(&pc.i, &sp.i, 4*4, 4, false, false);
        sp.i += 20;
        return;
    }
    load_counter ++;
    ldr(&lr.i, &r1.i, 0, 4, false, true);
L18:
    counters[13] ++;
    r2.i = r2.i + lr.i;
    store_counter ++;
    str(&r2.i, &r1.i, 0, 4, false, true);
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false);
    ldr(&r7.i, &sp.i, 3*4, 4, false, false);
    ldr(&pc.i, &sp.i, 4*4, 4, false, false);
    sp.i += 20;
    return;
L12:
    counters[14] ++;
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z && n == v)
    {
        goto L13;
    }
    counters[15] ++;
    goto L18;
    return;
}

void malloc_start()
{
    counters[16] ++;
    store_counter ++;
    sp.i -= 8;
    str(&r4.i, &sp.i, 0*4, 4, false, false);
    str(&lr.i, &sp.i, 1*4, 4, false, false);
    r0.i = 1;
    malloc_help();
    counters[17] ++;
    r3.i = (LC0 & 0xffff);
    r3.i = r3.i | (((uint32_t)LC0 >> 16) << 16);
    r4.i = r0.i;
    r0.i = 1000;
    store_counter ++;
    str(&r4.i, &r3.i, 0, 4, false, true);
    malloc_help();
    counters[18] ++;
    r2.i = (sp & 0xffff);
    r3.i = (fp & 0xffff);
    r2.i = r2.i | (((uint32_t)sp >> 16) << 16);
    r3.i = r3.i | (((uint32_t)fp >> 16) << 16);
    r0.i = r0.i - r4.i;
    r0.i = r0.i + 996;
    r0.i = r0.i + 3;
    store_counter ++;
    str(&r0.i, &r2.i, 0, 4, false, true);
    store_counter ++;
    str(&r0.i, &r3.i, 0, 4, false, true);
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false);
    ldr(&pc.i, &sp.i, 1*4, 4, false, false);
    sp.i += 8;
    return;

}

void main()
{
    malloc_start();
    counters[19] ++;
    store_counter ++;
    sp.i -= 24;
    str(&r4.i, &sp.i, 0*4, 4, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false);
    str(&r7.i, &sp.i, 3*4, 4, false, false);
    str(&r8.i, &sp.i, 4*4, 4, false, false);
    str(&lr.i, &sp.i, 5*4, 4, false, false);
    malloc_start();
    counters[20] ++;
    r2.i = (fp & 0xffff);
    r2.i = r2.i | (((uint32_t)fp >> 16) << 16);
    r4.i = (LC0 & 0xffff);
    r4.i = r4.i | (((uint32_t)LC0 >> 16) << 16);
    r3.i = (r0 & 0xffff);
    load_counter ++;
    ldr(&lr.i, &r2.i, 0, 4, false, true);
    r3.i = r3.i | (((uint32_t)r0 >> 16) << 16);
    load_counter ++;
    ldr(&r0.i, &r4.i, 0, 4, false, true);
    ip.i = (r1 & 0xffff);
    r1.i = lr.i - 12;
    ip.i = ip.i | (((uint32_t)r1 >> 16) << 16);
    store_counter ++;
    str(&r1.i, &r3.i, 0, 4, false, true);
    r6.i = 123;
    store_counter ++;
    str(&r1.i, &r2.i, 0, 4, false, true);
    lr.i = r0.i + lr.i;
    store_counter ++;
    str(&r6.i, &ip.i, 0, 4, false, true);
    r5.i = 0;
    store_counter ++;
    str(&r6.i, &r0.i, r1.i, 1, false, false);
    r1.i = (LC0 & 0xffff);
    load_counter ++;
    ldr(&r6.i, &ip.i, 0, 4, false, true);
    r1.i = r1.i | (((uint32_t)LC0 >> 16) << 16);
    r0.i = 1;
    r6.i = r6.i >> 8;
    store_counter ++;
    str(&r6.i, &lr.i, -11, 1, false, false);
    load_counter ++;
    ldr(&r6.i, &ip.i, 2, 4, false, false);
    store_counter ++;
    str(&r6.i, &lr.i, -10, 1, false, false);
    load_counter ++;
    ldr(&r6.i, &ip.i, 3, 4, false, false);
    store_counter ++;
    str(&r6.i, &lr.i, -9, 1, false, false);
    load_counter ++;
    ldr(&r7.i, &r2.i, 0, 4, false, true);
    load_counter ++;
    ldr(&lr.i, &r4.i, 0, 4, false, true);
    load_counter ++;
    ldr(&r6.i, &r3.i, 0, 4, false, true);
    lr.i = lr.i + r7.i;
    store_counter ++;
    str(&r6.i, &lr.i, 4, 1, false, false);
    load_counter ++;
    ldr(&r6.i, &r3.i, 0, 4, false, true);
    r6.i = r6.i >> 8;
    store_counter ++;
    str(&r6.i, &lr.i, 5, 1, false, false);
    load_counter ++;
    ldr(&r6.i, &r3.i, 2, 4, false, false);
    store_counter ++;
    str(&r6.i, &lr.i, 6, 1, false, false);
    load_counter ++;
    ldr(&r6.i, &r3.i, 3, 4, false, false);
    store_counter ++;
    str(&r6.i, &lr.i, 7, 1, false, false);
    load_counter ++;
    ldr(&lr.i, &r4.i, 0, 4, false, true);
    load_counter ++;
    ldr(&r4.i, &r2.i, 0, 4, false, true);
    store_counter ++;
    str(&r5.i, &r3.i, 0, 4, false, true);
    r4.i = lr.i + r4.i;
    load_counter ++;
    ldr(&r2.i, &r4.i, 4, 1, false, false);
    store_counter ++;
    str(&r2.i, &r3.i, 0, 4, false, true);
    load_counter ++;
    ldr(&r6.i, &r4.i, 5, 1, false, false);
    r2.i = r2.i + ((uint32_t)r6.i << 8);
    store_counter ++;
    str(&r2.i, &r3.i, 0, 4, false, true);
    load_counter ++;
    ldr(&r6.i, &r4.i, 6, 1, false, false);
    r2.i = r2.i + ((uint32_t)r6.i << 16);
    store_counter ++;
    str(&r2.i, &r3.i, 0, 4, false, true);
    load_counter ++;
    ldr(&r4.i, &r4.i, 7, 1, false, false);
    r2.i = r2.i + ((uint32_t)r4.i << 24);
    store_counter ++;
    str(&r2.i, &r3.i, 0, 4, false, true);
    store_counter ++;
    str(&r5.i, &ip.i, 0, 4, false, true);
    load_counter ++;
    ldr(&r2.i, &lr.i, r2.i, 1, true, false);
    store_counter ++;
    str(&r2.i, &ip.i, 0, 4, false, true);
    load_counter ++;
    ldr(&r3.i, &lr.i, 1, 1, false, false);
    r2.i = r2.i + ((uint32_t)r3.i << 8);
    store_counter ++;
    str(&r2.i, &ip.i, 0, 4, false, true);
    load_counter ++;
    ldr(&r3.i, &lr.i, 2, 1, false, false);
    r2.i = r2.i + ((uint32_t)r3.i << 16);
    store_counter ++;
    str(&r2.i, &ip.i, 0, 4, false, true);
    load_counter ++;
    ldr(&r3.i, &lr.i, 3, 1, false, false);
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false);
    ldr(&r7.i, &sp.i, 3*4, 4, false, false);
    ldr(&r8.i, &sp.i, 4*4, 4, false, false);
    ldr(&lr.i, &sp.i, 5*4, 4, false, false);
    sp.i += 24;
    r2.i = r2.i + ((uint32_t)r3.i << 24);
    store_counter ++;
    str(&r2.i, &ip.i, 0, 4, false, true);
    printf(malloc_0+r1.i, r2.i);
malloc_0:
    counter_summary();
    return;
}

