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

reg r0, r3, r1, r2;

int32_t num, e, capacity, flow, color, pred, head, tail, q, LC0;

int counters[45] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[45] = {14,27,27,8,8,6,12,6,1,4,6,19,2,5,3,6,8,11,10,3,12,6,3,6,1,9,26,6,6,6,53,6,4,3,3,4,6,3,12,6,3,6,57,5,4};


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
    malloc_0 = (uint8_t*) malloc(1);
    uint8_t* stack_ptr = (uint8_t*) malloc(20000);
    int32_t abc = (int32_t) (stack_ptr - malloc_0);
    sp.i = (int32_t) (stack_ptr - malloc_0) + 19996;
    fp = sp;

    uint8_t* test = (uint8_t*) malloc(8012046);

    int32_t malloc_total = (int32_t) (test - malloc_0);
    num = malloc_total;
    num = (int32_t) ((uint8_t*) malloc(4*sizeof(int8_t)) - malloc_0);

    e = malloc_total + 4;
    e = (int32_t) ((uint8_t*) malloc(4*sizeof(int8_t)) - malloc_0);

    capacity = malloc_total + 8;
    capacity = (int32_t) ((uint8_t*) malloc(4000000*sizeof(int8_t)) - malloc_0);

    flow = malloc_total + 4000008;
    flow = (int32_t) ((uint8_t*) malloc(4000000*sizeof(int8_t)) - malloc_0);

    color = malloc_total + 8000008;
    color = (int32_t) ((uint8_t*) malloc(4000*sizeof(int8_t)) - malloc_0);

    pred = malloc_total + 8004008;
    pred = (int32_t) ((uint8_t*) malloc(4000*sizeof(int8_t)) - malloc_0);

    head = malloc_total + 8008008;
    head = (int32_t) ((uint8_t*) malloc(4*sizeof(int8_t)) - malloc_0);

    tail = malloc_total + 8008012;
    tail = (int32_t) ((uint8_t*) malloc(4*sizeof(int8_t)) - malloc_0);

    q = malloc_total + 8008016;
    q = (int32_t) ((uint8_t*) malloc(4008*sizeof(int8_t)) - malloc_0);

    LC0 = malloc_total + 8012024;
    strcpy(malloc_0+LC0, "Max Flow: %d\012\000");

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


void min()
{
    counters[0] ++;
    store_counter ++;
    str(&fp.i, &sp.i, -4, 4, true, false, false);
    fp.i = sp.i + (0);
    sp.i = sp.i - (12);
    store_counter ++;
    str(&r0.i, &fp.i, -8, 4, false, false, false);
    store_counter ++;
    str(&r1.i, &fp.i, -12, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -12, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n != v)
    {
        r3.i = r2.i;
    }
    if (n == v)
    {
        r3.i = r3.i;
    }
    r0.i = r3.i;
    sp.i = fp.i + (0);
    load_counter ++;
    ldr(&fp.i, &sp.i, 4, 4, false, true, false);
    return;

}

void enqueue()
{
    counters[1] ++;
    store_counter ++;
    str(&fp.i, &sp.i, -4, 4, true, false, false);
    fp.i = sp.i + (0);
    sp.i = sp.i - (12);
    store_counter ++;
    str(&r0.i, &fp.i, -8, 4, false, false, false);
    r3.i = (tail & 0xffff);
    r3.i = r3.i | (((uint32_t)tail >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &r3.i, 0, 4, false, false, false);
    r3.i = (q & 0xffff);
    r3.i = r3.i | (((uint32_t)q >> 16) << 16);
    load_counter ++;
    ldr(&r1.i, &fp.i, -8, 4, false, false, false);
    store_counter ++;
    str(&r1.i, &r3.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    r3.i = (tail & 0xffff);
    r3.i = r3.i | (((uint32_t)tail >> 16) << 16);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, false, false);
    r2.i = r3.i + (1);
    r3.i = (tail & 0xffff);
    r3.i = r3.i | (((uint32_t)tail >> 16) << 16);
    store_counter ++;
    str(&r2.i, &r3.i, 0, 4, false, false, false);
    r3.i = (color & 0xffff);
    r3.i = r3.i | (((uint32_t)color >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &fp.i, -8, 4, false, false, false);
    r1.i = 1;
    store_counter ++;
    str(&r1.i, &r3.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    sp.i = fp.i + (0);
    load_counter ++;
    ldr(&fp.i, &sp.i, 4, 4, false, true, false);
    return;

}

void dequeue()
{
    counters[2] ++;
    store_counter ++;
    str(&fp.i, &sp.i, -4, 4, true, false, false);
    fp.i = sp.i + (0);
    sp.i = sp.i - (12);
    r3.i = (head & 0xffff);
    r3.i = r3.i | (((uint32_t)head >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &r3.i, 0, 4, false, false, false);
    r3.i = (q & 0xffff);
    r3.i = r3.i | (((uint32_t)q >> 16) << 16);
    load_counter ++;
    ldr(&r3.i, &r3.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = (head & 0xffff);
    r3.i = r3.i | (((uint32_t)head >> 16) << 16);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, false, false);
    r2.i = r3.i + (1);
    r3.i = (head & 0xffff);
    r3.i = r3.i | (((uint32_t)head >> 16) << 16);
    store_counter ++;
    str(&r2.i, &r3.i, 0, 4, false, false, false);
    r3.i = (color & 0xffff);
    r3.i = r3.i | (((uint32_t)color >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &fp.i, -8, 4, false, false, false);
    r1.i = 2;
    store_counter ++;
    str(&r1.i, &r3.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r0.i = r3.i;
    sp.i = fp.i + (0);
    load_counter ++;
    ldr(&fp.i, &sp.i, 4, 4, false, true, false);
    return;

}

void bfs()
{
    counters[3] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&fp.i, &sp.i, 0, 4, false, false, false);
    fp.i = sp.i + (4);
    sp.i = sp.i - (16);
    store_counter ++;
    str(&r0.i, &fp.i, -16, 4, false, false, false);
    store_counter ++;
    str(&r1.i, &fp.i, -20, 4, false, false, false);
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
    goto L7;
L8:
    counters[4] ++;
    r3.i = (color & 0xffff);
    r3.i = r3.i | (((uint32_t)color >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &fp.i, -8, 4, false, false, false);
    r1.i = 0;
    store_counter ++;
    str(&r1.i, &r3.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = r3.i + (1);
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
L7:
    counters[5] ++;
    r3.i = (num & 0xffff);
    r3.i = r3.i | (((uint32_t)num >> 16) << 16);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -8, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n != v)
    {
        goto L8;
    }
    counters[6] ++;
    r3.i = (tail & 0xffff);
    r3.i = r3.i | (((uint32_t)tail >> 16) << 16);
    r2.i = 0;
    store_counter ++;
    str(&r2.i, &r3.i, 0, 4, false, false, false);
    r3.i = (tail & 0xffff);
    r3.i = r3.i | (((uint32_t)tail >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &r3.i, 0, 4, false, false, false);
    r3.i = (head & 0xffff);
    r3.i = r3.i | (((uint32_t)head >> 16) << 16);
    store_counter ++;
    str(&r2.i, &r3.i, 0, 4, false, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, -16, 4, false, false, false);
    enqueue();
    counters[7] ++;
    r3.i = (pred & 0xffff);
    r3.i = r3.i | (((uint32_t)pred >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &fp.i, -16, 4, false, false, false);
    r1.i = ~0;
    store_counter ++;
    str(&r1.i, &r3.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    goto L9;
L13:
    counters[8] ++;
    dequeue();
    counters[9] ++;
    store_counter ++;
    str(&r0.i, &fp.i, -8, 4, false, false, false);
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false, false);
    goto L10;
L12:
    counters[10] ++;
    r3.i = (color & 0xffff);
    r3.i = r3.i | (((uint32_t)color >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &fp.i, -12, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &r3.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L11;
    }
    counters[11] ++;
    r3.i = (capacity & 0xffff);
    r3.i = r3.i | (((uint32_t)capacity >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &fp.i, -8, 4, false, false, false);
    r1.i = 1000;
    r1.i = (r1.i) * (r2.i);
    load_counter ++;
    ldr(&r2.i, &fp.i, -12, 4, false, false, false);
    r2.i = r1.i + (r2.i);
    load_counter ++;
    ldr(&r2.i, &r3.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    r3.i = (flow & 0xffff);
    r3.i = r3.i | (((uint32_t)flow >> 16) << 16);
    load_counter ++;
    ldr(&r1.i, &fp.i, -8, 4, false, false, false);
    r0.i = 1000;
    r0.i = (r0.i) * (r1.i);
    load_counter ++;
    ldr(&r1.i, &fp.i, -12, 4, false, false, false);
    r1.i = r0.i + (r1.i);
    load_counter ++;
    ldr(&r3.i, &r3.i, ((uint32_t)r1.i << 2), 4, false, false, false);
    r3.i = r2.i - (r3.i);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L11;
    }
    counters[12] ++;
    load_counter ++;
    ldr(&r0.i, &fp.i, -12, 4, false, false, false);
    enqueue();
    counters[13] ++;
    r3.i = (pred & 0xffff);
    r3.i = r3.i | (((uint32_t)pred >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &fp.i, -12, 4, false, false, false);
    load_counter ++;
    ldr(&r1.i, &fp.i, -8, 4, false, false, false);
    store_counter ++;
    str(&r1.i, &r3.i, ((uint32_t)r2.i << 2), 4, false, false, false);
L11:
    counters[14] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false, false);
    r3.i = r3.i + (1);
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false, false);
L10:
    counters[15] ++;
    r3.i = (num & 0xffff);
    r3.i = r3.i | (((uint32_t)num >> 16) << 16);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -12, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n != v)
    {
        goto L12;
    }
L9:
    counters[16] ++;
    r3.i = (head & 0xffff);
    r3.i = r3.i | (((uint32_t)head >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &r3.i, 0, 4, false, false, false);
    r3.i = (tail & 0xffff);
    r3.i = r3.i | (((uint32_t)tail >> 16) << 16);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z)
    {
        goto L13;
    }
    counters[17] ++;
    r3.i = (color & 0xffff);
    r3.i = r3.i | (((uint32_t)color >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &fp.i, -20, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &r3.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    tmp = r3.i - 2;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 2);
    v = (r3.i&0x80000000) != (2&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        r3.i = 1;
    }
    if (!z)
    {
        r3.i = 0;
    }
    r3.i = 0xff & (uint8_t)r3.i;
    r0.i = r3.i;
    sp.i = fp.i - (4);
    load_counter ++;
    ldr(&fp.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;

}

void fordFulkerson()
{
    counters[18] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&fp.i, &sp.i, 0, 4, false, false, false);
    fp.i = sp.i + (4);
    sp.i = sp.i - (32);
    store_counter ++;
    str(&r0.i, &fp.i, -32, 4, false, false, false);
    store_counter ++;
    str(&r1.i, &fp.i, -36, 4, false, false, false);
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -20, 4, false, false, false);
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
    goto L16;
L19:
    counters[19] ++;
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false, false);
    goto L17;
L18:
    counters[20] ++;
    r3.i = (flow & 0xffff);
    r3.i = r3.i | (((uint32_t)flow >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &fp.i, -8, 4, false, false, false);
    r1.i = 1000;
    r1.i = (r1.i) * (r2.i);
    load_counter ++;
    ldr(&r2.i, &fp.i, -12, 4, false, false, false);
    r2.i = r1.i + (r2.i);
    r1.i = 0;
    store_counter ++;
    str(&r1.i, &r3.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false, false);
    r3.i = r3.i + (1);
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false, false);
L17:
    counters[21] ++;
    r3.i = (num & 0xffff);
    r3.i = r3.i | (((uint32_t)num >> 16) << 16);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -12, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n != v)
    {
        goto L18;
    }
    counters[22] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = r3.i + (1);
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
L16:
    counters[23] ++;
    r3.i = (num & 0xffff);
    r3.i = r3.i | (((uint32_t)num >> 16) << 16);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -8, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n != v)
    {
        goto L19;
    }
    counters[24] ++;
    goto L20;
L25:
    counters[25] ++;
    r3.i = 51712;
    r3.i = r3.i | (15258 << 16);
    store_counter ++;
    str(&r3.i, &fp.i, -24, 4, false, false, false);
    r3.i = (num & 0xffff);
    r3.i = r3.i | (((uint32_t)num >> 16) << 16);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, false, false);
    r3.i = r3.i - (1);
    store_counter ++;
    str(&r3.i, &fp.i, -16, 4, false, false, false);
    goto L21;
L22:
    counters[26] ++;
    r3.i = (pred & 0xffff);
    r3.i = r3.i | (((uint32_t)pred >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &fp.i, -16, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &r3.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    r3.i = (capacity & 0xffff);
    r3.i = r3.i | (((uint32_t)capacity >> 16) << 16);
    r1.i = 1000;
    r1.i = (r1.i) * (r2.i);
    load_counter ++;
    ldr(&r2.i, &fp.i, -16, 4, false, false, false);
    r2.i = r1.i + (r2.i);
    load_counter ++;
    ldr(&r2.i, &r3.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    r3.i = (pred & 0xffff);
    r3.i = r3.i | (((uint32_t)pred >> 16) << 16);
    load_counter ++;
    ldr(&r1.i, &fp.i, -16, 4, false, false, false);
    load_counter ++;
    ldr(&r1.i, &r3.i, ((uint32_t)r1.i << 2), 4, false, false, false);
    r3.i = (flow & 0xffff);
    r3.i = r3.i | (((uint32_t)flow >> 16) << 16);
    r0.i = 1000;
    r0.i = (r0.i) * (r1.i);
    load_counter ++;
    ldr(&r1.i, &fp.i, -16, 4, false, false, false);
    r1.i = r0.i + (r1.i);
    load_counter ++;
    ldr(&r3.i, &r3.i, ((uint32_t)r1.i << 2), 4, false, false, false);
    r3.i = r2.i - (r3.i);
    r1.i = r3.i;
    load_counter ++;
    ldr(&r0.i, &fp.i, -24, 4, false, false, false);
    min();
    counters[27] ++;
    store_counter ++;
    str(&r0.i, &fp.i, -24, 4, false, false, false);
    r3.i = (pred & 0xffff);
    r3.i = r3.i | (((uint32_t)pred >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &fp.i, -16, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &r3.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    store_counter ++;
    str(&r3.i, &fp.i, -16, 4, false, false, false);
L21:
    counters[28] ++;
    r3.i = (pred & 0xffff);
    r3.i = r3.i | (((uint32_t)pred >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &fp.i, -16, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &r3.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (n == v)
    {
        goto L22;
    }
    counters[29] ++;
    r3.i = (num & 0xffff);
    r3.i = r3.i | (((uint32_t)num >> 16) << 16);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, false, false);
    r3.i = r3.i - (1);
    store_counter ++;
    str(&r3.i, &fp.i, -16, 4, false, false, false);
    goto L23;
L24:
    counters[30] ++;
    r3.i = (pred & 0xffff);
    r3.i = r3.i | (((uint32_t)pred >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &fp.i, -16, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &r3.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    r3.i = (flow & 0xffff);
    r3.i = r3.i | (((uint32_t)flow >> 16) << 16);
    r1.i = 1000;
    r1.i = (r1.i) * (r2.i);
    load_counter ++;
    ldr(&r2.i, &fp.i, -16, 4, false, false, false);
    r2.i = r1.i + (r2.i);
    load_counter ++;
    ldr(&r1.i, &r3.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    r3.i = (pred & 0xffff);
    r3.i = r3.i | (((uint32_t)pred >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &fp.i, -16, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &r3.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -24, 4, false, false, false);
    r1.i = r1.i + (r3.i);
    r3.i = (flow & 0xffff);
    r3.i = r3.i | (((uint32_t)flow >> 16) << 16);
    r0.i = 1000;
    r0.i = (r0.i) * (r2.i);
    load_counter ++;
    ldr(&r2.i, &fp.i, -16, 4, false, false, false);
    r2.i = r0.i + (r2.i);
    store_counter ++;
    str(&r1.i, &r3.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    r3.i = (pred & 0xffff);
    r3.i = r3.i | (((uint32_t)pred >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &fp.i, -16, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &r3.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    r3.i = (flow & 0xffff);
    r3.i = r3.i | (((uint32_t)flow >> 16) << 16);
    load_counter ++;
    ldr(&r1.i, &fp.i, -16, 4, false, false, false);
    r0.i = 1000;
    r1.i = (r0.i) * (r1.i);
    r2.i = r1.i + (r2.i);
    load_counter ++;
    ldr(&r1.i, &r3.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    r3.i = (pred & 0xffff);
    r3.i = r3.i | (((uint32_t)pred >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &fp.i, -16, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &r3.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -24, 4, false, false, false);
    r1.i = r1.i - (r3.i);
    r3.i = (flow & 0xffff);
    r3.i = r3.i | (((uint32_t)flow >> 16) << 16);
    load_counter ++;
    ldr(&r0.i, &fp.i, -16, 4, false, false, false);
    ip.i = 1000;
    r0.i = (ip.i) * (r0.i);
    r2.i = r0.i + (r2.i);
    store_counter ++;
    str(&r1.i, &r3.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    r3.i = (pred & 0xffff);
    r3.i = r3.i | (((uint32_t)pred >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &fp.i, -16, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &r3.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    store_counter ++;
    str(&r3.i, &fp.i, -16, 4, false, false, false);
L23:
    counters[31] ++;
    r3.i = (pred & 0xffff);
    r3.i = r3.i | (((uint32_t)pred >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &fp.i, -16, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &r3.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (n == v)
    {
        goto L24;
    }
    counters[32] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -20, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -24, 4, false, false, false);
    r3.i = r2.i + (r3.i);
    store_counter ++;
    str(&r3.i, &fp.i, -20, 4, false, false, false);
L20:
    counters[33] ++;
    load_counter ++;
    ldr(&r1.i, &fp.i, -36, 4, false, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, -32, 4, false, false, false);
    bfs();
    counters[34] ++;
    r3.i = r0.i;
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L25;
    }
    counters[35] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false, false);
    r0.i = r3.i;
    sp.i = fp.i - (4);
    load_counter ++;
    ldr(&fp.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;

}

void main()
{
    malloc_start();
    counters[36] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&fp.i, &sp.i, 0, 4, false, false, false);
    fp.i = sp.i + (4);
    sp.i = sp.i - (16);
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
    goto L28;
L31:
    counters[37] ++;
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false, false);
    goto L29;
L30:
    counters[38] ++;
    r3.i = (capacity & 0xffff);
    r3.i = r3.i | (((uint32_t)capacity >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &fp.i, -8, 4, false, false, false);
    r1.i = 1000;
    r1.i = (r1.i) * (r2.i);
    load_counter ++;
    ldr(&r2.i, &fp.i, -12, 4, false, false, false);
    r2.i = r1.i + (r2.i);
    r1.i = 0;
    store_counter ++;
    str(&r1.i, &r3.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false, false);
    r3.i = r3.i + (1);
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false, false);
L29:
    counters[39] ++;
    r3.i = (num & 0xffff);
    r3.i = r3.i | (((uint32_t)num >> 16) << 16);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -12, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n != v)
    {
        goto L30;
    }
    counters[40] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = r3.i + (1);
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
L28:
    counters[41] ++;
    r3.i = (num & 0xffff);
    r3.i = r3.i | (((uint32_t)num >> 16) << 16);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -8, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n != v)
    {
        goto L31;
    }
    counters[42] ++;
    r3.i = (num & 0xffff);
    r3.i = r3.i | (((uint32_t)num >> 16) << 16);
    r2.i = 6;
    store_counter ++;
    str(&r2.i, &r3.i, 0, 4, false, false, false);
    r3.i = (e & 0xffff);
    r3.i = r3.i | (((uint32_t)e >> 16) << 16);
    r2.i = 7;
    store_counter ++;
    str(&r2.i, &r3.i, 0, 4, false, false, false);
    r3.i = (capacity & 0xffff);
    r3.i = r3.i | (((uint32_t)capacity >> 16) << 16);
    r2.i = 8;
    store_counter ++;
    str(&r2.i, &r3.i, 4, 4, false, false, false);
    r3.i = (capacity & 0xffff);
    r3.i = r3.i | (((uint32_t)capacity >> 16) << 16);
    r2.i = 3;
    store_counter ++;
    str(&r2.i, &r3.i, 16, 4, false, false, false);
    r3.i = (capacity & 0xffff);
    r3.i = r3.i | (((uint32_t)capacity >> 16) << 16);
    r2.i = 9;
    store_counter ++;
    str(&r2.i, &r3.i, 4008, 4, false, false, false);
    r3.i = (capacity & 0xffff);
    r3.i = r3.i | (((uint32_t)capacity >> 16) << 16);
    r3.i = r3.i + (4096);
    r2.i = r3.i;
    r3.i = 7;
    store_counter ++;
    str(&r3.i, &r2.i, 3920, 4, false, false, false);
    r3.i = (capacity & 0xffff);
    r3.i = r3.i | (((uint32_t)capacity >> 16) << 16);
    r3.i = r3.i + (4096);
    r2.i = r3.i;
    r3.i = 2;
    store_counter ++;
    str(&r3.i, &r2.i, 3924, 4, false, false, false);
    r3.i = (capacity & 0xffff);
    r3.i = r3.i | (((uint32_t)capacity >> 16) << 16);
    r3.i = r3.i + (8192);
    r2.i = r3.i;
    r3.i = 5;
    store_counter ++;
    str(&r3.i, &r2.i, 3828, 4, false, false, false);
    r3.i = (capacity & 0xffff);
    r3.i = r3.i | (((uint32_t)capacity >> 16) << 16);
    r3.i = r3.i + (12288);
    r2.i = r3.i;
    r3.i = 7;
    store_counter ++;
    str(&r3.i, &r2.i, 3720, 4, false, false, false);
    r3.i = (capacity & 0xffff);
    r3.i = r3.i | (((uint32_t)capacity >> 16) << 16);
    r3.i = r3.i + (12288);
    r2.i = r3.i;
    r3.i = 4;
    store_counter ++;
    str(&r3.i, &r2.i, 3724, 4, false, false, false);
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -16, 4, false, false, false);
    r3.i = 5;
    store_counter ++;
    str(&r3.i, &fp.i, -20, 4, false, false, false);
    load_counter ++;
    ldr(&r1.i, &fp.i, -20, 4, false, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, -16, 4, false, false, false);
    fordFulkerson();
    counters[43] ++;
    r3.i = r0.i;
    r1.i = r3.i;
    r0.i = (LC0 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC0 >> 16) << 16);
    printf(malloc_0+r0.i, r1.i);
    counters[44] ++;
    r3.i = 0;
    r0.i = r3.i;
    sp.i = fp.i - (4);
    load_counter ++;
    ldr(&fp.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    counter_summary();
    return;

}

