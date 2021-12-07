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

reg r7, r3, r0, r2, r4, r1, r5, r6, r8, r9, r10;

int32_t LC0, L49, q, tail, head, pred, color, flow, capacity, e, num;

int counters[39] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[39] = {3,14,14,13,3,26,6,10,3,9,3,1,3,14,8,8,1,3,3,3,8,6,4,11,1,13,1,2,2,3,3,8,6,1,3,3,56,5,2};

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

void clz(int32_t *dest, int32_t *op)
{
    int msb = 1 << (32 - 1);
    int count = 0;
    uint32_t num = (uint32_t)*op;

    for(int i=0; i<32; i++)
    {
        if((num << i) & msb)
            break;
        count++;
    }

    *dest = num;
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
    malloc_0 = (uint8_t*) malloc(8032050);
    sp.i = 19996;
    fp = sp;
    LC0 = 20000;
    strcpy(malloc_0+LC0, "Max Flow: %d\012\000");

    L49 = 20022;
    int32_t arrayL49[] = {capacity};
    for(int i=0; i<1; i++) str(&arrayL49[i], &L49, i*4, 4, false, false, false);

    q = 20026;
    tail = 24034;
    head = 24038;
    pred = 24042;
    color = 28042;
    flow = 32042;
    capacity = 4032042;
    e = 8032042;
    num = 8032046;
}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "ford_fulkerson.c";

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

void min();
void enqueue();
void dequeue();
void bfs();
void fordFulkerson();
void main();

void printf_help(const char *format, int32_t test)
{
    if (strstr(format, "%s") != NULL)
        printf(format, malloc_0 + test);
    else
        printf(format, test);
}

void min()
{
    counters[0] ++;
    tmp = r1.i - r0.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r0.i);
    v = (r1.i&0x80000000) != (r0.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (n != v)
    {
        r0.i = r1.i;
    }
    return;

}

void enqueue()
{
    counters[1] ++;
    r3.i = (tail & 0xffff);
    r3.i = r3.i | (((uint32_t)tail >> 16) << 16);
    r1.i = (q & 0xffff);
    r2.i = (color & 0xffff);
    load_counter ++;
    ldr(&ip.i, &r3.i, 0, 4, false, false, false);
    r1.i = r1.i | (((uint32_t)q >> 16) << 16);
    r2.i = r2.i | (((uint32_t)color >> 16) << 16);
    store_counter ++;
    str(&lr.i, &sp.i, -4, 4, true, false, false);
    lr.i = ip.i + (1);
    store_counter ++;
    str(&r0.i, &r1.i, ((uint32_t)ip.i << 2), 4, false, false, false);
    r1.i = 1;
    store_counter ++;
    str(&lr.i, &r3.i, 0, 4, false, false, false);
    store_counter ++;
    str(&r1.i, &r2.i, ((uint32_t)r0.i << 2), 4, false, false, false);
    load_counter ++;
    ldr(&pc.i, &sp.i, 4, 4, false, true, false);
    return;

}

void dequeue()
{
    counters[2] ++;
    r3.i = (head & 0xffff);
    r3.i = r3.i | (((uint32_t)head >> 16) << 16);
    r1.i = (q & 0xffff);
    r1.i = r1.i | (((uint32_t)q >> 16) << 16);
    load_counter ++;
    ldr(&r0.i, &r3.i, 0, 4, false, false, false);
    r2.i = (color & 0xffff);
    store_counter ++;
    str(&lr.i, &sp.i, -4, 4, true, false, false);
    lr.i = r0.i + (1);
    load_counter ++;
    ldr(&r0.i, &r1.i, ((uint32_t)r0.i << 2), 4, false, false, false);
    r2.i = r2.i | (((uint32_t)color >> 16) << 16);
    ip.i = 2;
    store_counter ++;
    str(&lr.i, &r3.i, 0, 4, false, false, false);
    store_counter ++;
    str(&ip.i, &r2.i, ((uint32_t)r0.i << 2), 4, false, false, false);
    load_counter ++;
    ldr(&pc.i, &sp.i, 4, 4, false, true, false);
    return;

}

void bfs()
{
    counters[3] ++;
    r3.i = (num & 0xffff);
    r3.i = r3.i | (((uint32_t)num >> 16) << 16);
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&fp.i, &sp.i, 0, 4, false, false, false);
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
    sp.i = sp.i - (28);
    load_counter ++;
    ldr(&ip.i, &r3.i, 0, 4, false, false, false);
    r3.i = (color & 0xffff);
    r3.i = r3.i | (((uint32_t)color >> 16) << 16);
    store_counter ++;
    str(&r1.i, &sp.i, 16, 4, false, false, false);
    tmp = ip.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) 0);
    v = (ip.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    store_counter ++;
    str(&r3.i, &sp.i, 4, 4, false, false, false);
    if (!z && n == v)
    {
        r1.i = r3.i + (((uint32_t)ip.i << 2));
    }
    if (!z && n == v)
    {
        r2.i = 0;
    }
    if (z || n != v)
    {
        goto L11;
    }
L10:
    counters[4] ++;
    store_counter ++;
    str(&r2.i, &r3.i, 4, 4, false, true, false);
    tmp = r3.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r1.i);
    v = (r3.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L10;
    }
L11:
    counters[5] ++;
    r3.i = (q & 0xffff);
    r3.i = r3.i | (((uint32_t)q >> 16) << 16);
    r1.i = (tail & 0xffff);
    r8.i = (pred & 0xffff);
    r10.i = r3.i;
    r4.i = r3.i;
    store_counter ++;
    str(&r0.i, &r3.i, 0, 4, false, false, false);
    r1.i = r1.i | (((uint32_t)tail >> 16) << 16);
    load_counter ++;
    ldr(&r3.i, &sp.i, 4, 4, false, false, false);
    r8.i = r8.i | (((uint32_t)pred >> 16) << 16);
    r9.i = 0;
    r2.i = 1;
    r7.i = r9.i;
    lr.i = r2.i;
    store_counter ++;
    str(&r2.i, &r3.i, ((uint32_t)r0.i << 2), 4, false, false, false);
    fp.i = r2.i;
    r3.i = ~0;
    store_counter ++;
    str(&r2.i, &r1.i, 0, 4, false, false, false);
    store_counter ++;
    str(&r3.i, &r8.i, ((uint32_t)r0.i << 2), 4, false, false, false);
    r2.i = (flow & 0xffff);
    r3.i = (capacity & 0xffff);
    r2.i = r2.i | (((uint32_t)flow >> 16) << 16);
    r3.i = r3.i | (((uint32_t)capacity >> 16) << 16);
    store_counter ++;
    str(&r1.i, &sp.i, 20, 4, false, false, false);
    store_counter ++;
    str(&r3.i, &sp.i, 8, 4, false, false, false);
    store_counter ++;
    str(&r2.i, &sp.i, 12, 4, false, false, false);
L9:
    counters[6] ++;
    load_counter ++;
    ldr(&r3.i, &sp.i, 4, 4, false, false, false);
    tmp = ip.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) 0);
    v = (ip.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    r2.i = 2;
    r7.i = r7.i + (1);
    store_counter ++;
    str(&r2.i, &r3.i, ((uint32_t)r0.i << 2), 4, false, false, false);
    if (z || n != v)
    {
        goto L12;
    }
    counters[7] ++;
    r3.i = 4000;
    load_counter ++;
    ldr(&r1.i, &sp.i, 8, 4, false, false, false);
    r5.i = (r3.i) * (r0.i);
    r2.i = (color & 0xffff);
    r2.i = r2.i | (((uint32_t)color >> 16) << 16);
    r3.i = 0;
    store_counter ++;
    str(&r4.i, &sp.i, 0, 4, false, false, false);
    r6.i = r5.i + (r1.i);
    load_counter ++;
    ldr(&r1.i, &sp.i, 12, 4, false, false, false);
    r5.i = r5.i + (r1.i);
L14:
    counters[8] ++;
    load_counter ++;
    ldr(&r1.i, &r2.i, 4, 4, false, true, false);
    tmp = r1.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 0);
    v = (r1.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!z)
    {
        goto L13;
    }
    counters[9] ++;
    load_counter ++;
    ldr(&r1.i, &r6.i, ((uint32_t)r3.i << 2), 4, false, false, false);
    load_counter ++;
    ldr(&r4.i, &r5.i, ((uint32_t)r3.i << 2), 4, false, false, false);
    r1.i = r1.i - (r4.i);
    tmp = r1.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 0);
    v = (r1.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    store_counter ++;
    if (!z && n == v)
    {
        str(&r3.i, &r10.i, ((uint32_t)lr.i << 2), 4, false, false, false);
    }
    if (!z && n == v)
    {
        lr.i = lr.i + (1);
    }
    store_counter ++;
    if (!z && n == v)
    {
        str(&fp.i, &r2.i, -4, 4, false, false, false);
    }
    if (!z && n == v)
    {
        r9.i = 1;
    }
    store_counter ++;
    if (!z && n == v)
    {
        str(&r0.i, &r8.i, ((uint32_t)r3.i << 2), 4, false, false, false);
    }
L13:
    counters[10] ++;
    r3.i = r3.i + (1);
    tmp = r3.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) ip.i);
    v = (r3.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L14;
    }
    counters[11] ++;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0, 4, false, false, false);
L12:
    counters[12] ++;
    tmp = r7.i - lr.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r7.i) >= ((uint32_t) lr.i);
    v = (r7.i&0x80000000) != (lr.i&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
    load_counter ++;
    if (!z)
    {
        ldr(&r0.i, &r4.i, 4, 4, true, false, false);
    }
    if (!z)
    {
        goto L9;
    }
L15:
    counters[13] ++;
    tmp = r9.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r9.i) >= ((uint32_t) 0);
    v = (r9.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r9.i&0x80000000);
    r3.i = (head & 0xffff);
    r3.i = r3.i | (((uint32_t)head >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &sp.i, 16, 4, false, false, false);
    store_counter ++;
    str(&r7.i, &r3.i, 0, 4, false, false, false);
    load_counter ++;
    if (!z)
    {
        ldr(&r3.i, &sp.i, 20, 4, false, false, false);
    }
    store_counter ++;
    if (!z)
    {
        str(&r7.i, &r3.i, 0, 4, false, false, false);
    }
    load_counter ++;
    ldr(&r3.i, &sp.i, 4, 4, false, false, false);
    load_counter ++;
    ldr(&r0.i, &r3.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    r0.i = r0.i - (2);
    clz(&r0.i, &r0.i);
    r0.i = (uint32_t)r0.i >> 5;
    sp.i = sp.i + (28);
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
    ldr(&fp.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;

}

void fordFulkerson()
{
    counters[14] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&fp.i, &sp.i, 0, 4, false, false, false);
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
    r8.i = (num & 0xffff);
    r8.i = r8.i | (((uint32_t)num >> 16) << 16);
    sp.i = sp.i - (12);
    load_counter ++;
    ldr(&r3.i, &r8.i, 0, 4, false, false, false);
    store_counter ++;
    str(&r0.i, &sp.i, 0, 4, false, false, false);
    str(&r1.i, &sp.i, 4, 4, false, false, false);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L24;
    }
    counters[15] ++;
    r2.i = (flow & 0xffff);
    r2.i = r2.i | (((uint32_t)flow >> 16) << 16);
    ip.i = (uint32_t)r3.i << 2;
    r0.i = 4004;
    r0.i = ((r0.i) * (r3.i)) + (r2.i);
    r2.i = r2.i + (ip.i);
    ip.i = 0 - ip.i;
    r1.i = 0;
L26:
    counters[16] ++;
    r3.i = r2.i + (ip.i);
L25:
    counters[17] ++;
    store_counter ++;
    str(&r1.i, &r3.i, 4, 4, false, true, false);
    tmp = r3.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r2.i);
    v = (r3.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L25;
    }
    counters[18] ++;
    r2.i = r2.i + (4000);
    tmp = r2.i - r0.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r0.i);
    v = (r2.i&0x80000000) != (r0.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z)
    {
        goto L26;
    }
L24:
    counters[19] ++;
    load_counter ++;
    ldr(&r0.i, &sp.i, 0, 4, false, false, false);
    ldr(&r1.i, &sp.i, 4, 4, false, false, false);
    r5.i = (pred & 0xffff);
    bfs();
    counters[20] ++;
    r4.i = (flow & 0xffff);
    r6.i = (capacity & 0xffff);
    r5.i = r5.i | (((uint32_t)pred >> 16) << 16);
    r4.i = r4.i | (((uint32_t)flow >> 16) << 16);
    r6.i = r6.i | (((uint32_t)capacity >> 16) << 16);
    r7.i = 0;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (z)
    {
        goto L38;
    }
L31:
    counters[21] ++;
    load_counter ++;
    ldr(&ip.i, &r8.i, 0, 4, false, false, false);
    r3.i = 51712;
    ip.i = ip.i - (1);
    load_counter ++;
    ldr(&r2.i, &r5.i, ((uint32_t)ip.i << 2), 4, false, false, false);
    tmp = r2.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) 0);
    v = (r2.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n != v)
    {
        goto L32;
    }
    counters[22] ++;
    r3.i = r3.i | (15258 << 16);
    r10.i = ip.i;
    r0.i = r2.i;
    fp.i = 1000;
L29:
    counters[23] ++;
    r9.i = ((fp.i) * (r0.i)) + (r10.i);
    load_counter ++;
    ldr(&lr.i, &r5.i, ((uint32_t)r0.i << 2), 4, false, false, false);
    r10.i = r0.i;
    r0.i = lr.i;
    load_counter ++;
    ldr(&r1.i, &r6.i, ((uint32_t)r9.i << 2), 4, false, false, false);
    load_counter ++;
    ldr(&r9.i, &r4.i, ((uint32_t)r9.i << 2), 4, false, false, false);
    r1.i = r1.i - (r9.i);
    tmp = r3.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r1.i);
    v = (r3.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (n == v)
    {
        r3.i = r1.i;
    }
    tmp = lr.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) 0);
    v = (lr.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    if (n == v)
    {
        goto L29;
    }
    counters[24] ++;
    lr.i = 1000;
L30:
    counters[25] ++;
    r9.i = ((lr.i) * (r2.i)) + (ip.i);
    load_counter ++;
    ldr(&r1.i, &r5.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    r0.i = ((lr.i) * (ip.i)) + (r2.i);
    tmp = r1.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 0);
    v = (r1.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    ip.i = r2.i;
    r2.i = r1.i;
    load_counter ++;
    ldr(&r1.i, &r4.i, ((uint32_t)r9.i << 2), 4, false, false, false);
    r1.i = r1.i + (r3.i);
    store_counter ++;
    str(&r1.i, &r4.i, ((uint32_t)r9.i << 2), 4, false, false, false);
    load_counter ++;
    ldr(&r1.i, &r4.i, ((uint32_t)r0.i << 2), 4, false, false, false);
    r1.i = r1.i - (r3.i);
    store_counter ++;
    str(&r1.i, &r4.i, ((uint32_t)r0.i << 2), 4, false, false, false);
    if (n == v)
    {
        goto L30;
    }
    counters[26] ++;
    r7.i = r7.i + (r3.i);
L39:
    counters[27] ++;
    load_counter ++;
    ldr(&r0.i, &sp.i, 0, 4, false, false, false);
    ldr(&r1.i, &sp.i, 4, 4, false, false, false);
    bfs();
    counters[28] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        goto L31;
    }
L38:
    counters[29] ++;
    r0.i = r7.i;
    sp.i = sp.i + (12);
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
    ldr(&fp.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;
L32:
    counters[30] ++;
    r3.i = r3.i | (15258 << 16);
    r7.i = r7.i + (r3.i);
    goto L39;
    return;
}

void main()
{
    malloc_start();
    counters[31] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r6.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r4.i, &sp.i, 0, 4, false, false, false);
    r5.i = (num & 0xffff);
    r5.i = r5.i | (((uint32_t)num >> 16) << 16);
    r0.i = (capacity & 0xffff);
    r0.i = r0.i | (((uint32_t)capacity >> 16) << 16);
    load_counter ++;
    ldr(&ip.i, &r5.i, 0, 4, false, false, false);
    tmp = ip.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) 0);
    v = (ip.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (z || n != v)
    {
        goto L41;
    }
    counters[32] ++;
    r3.i = 4004;
    lr.i = (uint32_t)ip.i << 2;
    ip.i = ((r3.i) * (ip.i)) + (r0.i);
    r2.i = r0.i + (lr.i);
    lr.i = 0 - lr.i;
    r1.i = 0;
L43:
    counters[33] ++;
    r3.i = r2.i + (lr.i);
L42:
    counters[34] ++;
    store_counter ++;
    str(&r1.i, &r3.i, 4, 4, false, true, false);
    tmp = r3.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r2.i);
    v = (r3.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L42;
    }
    counters[35] ++;
    r2.i = r2.i + (4000);
    tmp = r2.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) ip.i);
    v = (r2.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z)
    {
        goto L43;
    }
L41:
    counters[36] ++;
    load_counter ++;
    ldr(&r3.i, &L49, 0, 4, false, false, false);
    r4.i = 1;
    store_counter ++;
    str(&r4.i, &r0.i, 4, 4, false, false, false);
    r2.i = (e & 0xffff);
    r1.i = r3.i + (4096);
    ip.i = r3.i + (20480);
    store_counter ++;
    str(&r4.i, &r0.i, 8, 4, false, false, false);
    lr.i = r3.i + (24576);
    store_counter ++;
    str(&r4.i, &r1.i, 3840, 4, false, false, false);
    r2.i = r2.i | (((uint32_t)e >> 16) << 16);
    store_counter ++;
    str(&r4.i, &r1.i, 3848, 4, false, false, false);
    store_counter ++;
    str(&r4.i, &r1.i, 3856, 4, false, false, false);
    r1.i = r3.i + (28672);
    store_counter ++;
    str(&r4.i, &r0.i, 12, 4, false, false, false);
    store_counter ++;
    str(&r4.i, &r0.i, 16, 4, false, false, false);
    store_counter ++;
    str(&r4.i, &r0.i, 20, 4, false, false, false);
    store_counter ++;
    str(&r4.i, &r0.i, 24, 4, false, false, false);
    store_counter ++;
    str(&r4.i, &r0.i, 28, 4, false, false, false);
    store_counter ++;
    str(&r4.i, &r0.i, 4036, 4, false, false, false);
    store_counter ++;
    str(&r4.i, &r0.i, 4052, 4, false, false, false);
    r0.i = r3.i + (32768);
    store_counter ++;
    str(&r4.i, &ip.i, 3476, 4, false, false, false);
    ip.i = r3.i + (36864);
    store_counter ++;
    str(&r4.i, &r1.i, 3292, 4, false, false, false);
    r1.i = r3.i + (8192);
    store_counter ++;
    str(&r4.i, &r0.i, 3196, 4, false, false, false);
    r0.i = r3.i + (12288);
    store_counter ++;
    str(&r4.i, &r3.i, 3940, 4, false, false, false);
    store_counter ++;
    str(&r4.i, &r3.i, 3948, 4, false, false, false);
    store_counter ++;
    str(&r4.i, &lr.i, 3388, 4, false, false, false);
    lr.i = r3.i + (40960);
    store_counter ++;
    str(&r4.i, &ip.i, 3100, 4, false, false, false);
    ip.i = 33;
    store_counter ++;
    str(&ip.i, &r2.i, 0, 4, false, false, false);
    r2.i = r3.i + (16384);
    ip.i = r3.i + (45056);
    r3.i = r3.i + (49152);
    store_counter ++;
    str(&r4.i, &r1.i, 3744, 4, false, false, false);
    store_counter ++;
    str(&r4.i, &r1.i, 3752, 4, false, false, false);
    store_counter ++;
    str(&r4.i, &r1.i, 3760, 4, false, false, false);
    r1.i = 15;
    store_counter ++;
    str(&r4.i, &r0.i, 3652, 4, false, false, false);
    store_counter ++;
    str(&r4.i, &r0.i, 3660, 4, false, false, false);
    store_counter ++;
    str(&r4.i, &r0.i, 3668, 4, false, false, false);
    r0.i = 0;
    store_counter ++;
    str(&r4.i, &r2.i, 3560, 4, false, false, false);
    store_counter ++;
    str(&r4.i, &r2.i, 3564, 4, false, false, false);
    store_counter ++;
    str(&r4.i, &r2.i, 3568, 4, false, false, false);
    store_counter ++;
    str(&r4.i, &r2.i, 3572, 4, false, false, false);
    store_counter ++;
    str(&r4.i, &r2.i, 3576, 4, false, false, false);
    r2.i = 16;
    store_counter ++;
    str(&r2.i, &r5.i, 0, 4, false, false, false);
    store_counter ++;
    str(&r4.i, &lr.i, 3004, 4, false, false, false);
    store_counter ++;
    str(&r4.i, &ip.i, 2908, 4, false, false, false);
    store_counter ++;
    str(&r4.i, &r3.i, 2812, 4, false, false, false);
    fordFulkerson();
    counters[37] ++;
    r1.i = (LC0 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC0 >> 16) << 16);
    r2.i = r0.i;
    r0.i = r4.i;
    printf_help(malloc_0+r1.i, r2.i);
    counters[38] ++;
    r0.i = 0;
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

