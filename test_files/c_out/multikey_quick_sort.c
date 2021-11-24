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

reg r2, r8, r1, r0, r9, r10, r3, r5, r4, r6, r7;

int32_t LC0, LC1, LC2, LC5, srchtop, srcharr, nodecnt, freearr, freen, bufn, buffer, root, LC4, storestring;

int counters[269] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[269] = {2,21,5,6,9,2,6,1,5,4,1,6,8,8,2,2,7,6,5,2,8,17,5,6,9,6,4,20,5,6,10,4,5,5,2,6,2,6,1,6,1,2,3,6,1,2,2,13,4,7,7,7,1,12,2,2,3,2,2,2,3,7,3,8,1,4,2,3,1,2,3,1,7,12,12,6,2,2,4,9,5,2,2,9,6,2,2,1,2,5,2,2,5,5,6,7,2,2,5,6,2,4,2,9,8,5,15,5,6,7,6,6,18,4,6,7,2,5,2,5,4,3,8,1,4,2,3,2,2,4,3,1,5,14,5,2,9,1,4,1,3,2,8,2,2,2,2,2,4,1,6,1,2,6,1,2,1,3,2,3,2,3,3,1,9,2,2,4,4,1,3,1,2,3,3,2,6,2,3,3,2,5,2,2,3,11,6,5,5,10,12,2,5,2,17,6,9,3,3,1,3,2,5,2,3,3,2,2,4,2,4,2,5,2,3,2,12,3,3,3,3,6,3,2,2,2,6,3,2,1,3,2,3,1,3,3,1,5,13,2,5,4,1,1,6,7,4,1,2,2,2,7,4,1,1,1,3,7,3,2,2,6,2,4,1,15,4,2,3};


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
    int32_t size = (10028-start)/4;
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

    int32_t malloc_total = (int32_t) ((uint8_t*) malloc(440078) - malloc_0);
    LC0 = malloc_total;
    strcpy(malloc_0+LC0, "apple\000");

    LC1 = malloc_total + 11;
    strcpy(malloc_0+LC1, "cat\000");

    LC2 = malloc_total + 20;
    strcpy(malloc_0+LC2, "boy\000");

    LC5 = malloc_total + 29;
    strcpy(malloc_0+LC5, "%s \000");

    srchtop = malloc_total + 38;
    srchtop = (int32_t) ((uint8_t*) malloc(4*sizeof(int8_t)) - malloc_0);

    srcharr = malloc_total + 42;
    srcharr = (int32_t) ((uint8_t*) malloc(400000*sizeof(int8_t)) - malloc_0);

    nodecnt = malloc_total + 400042;
    nodecnt = (int32_t) ((uint8_t*) malloc(4*sizeof(int8_t)) - malloc_0);

    freearr = malloc_total + 400046;
    freearr = (int32_t) ((uint8_t*) malloc(40000*sizeof(int8_t)) - malloc_0);

    freen = malloc_total + 440046;
    freen = (int32_t) ((uint8_t*) malloc(4*sizeof(int8_t)) - malloc_0);

    bufn = malloc_total + 440050;
    bufn = (int32_t) ((uint8_t*) malloc(4*sizeof(int8_t)) - malloc_0);

    buffer = malloc_total + 440054;
    buffer = (int32_t) ((uint8_t*) malloc(4*sizeof(int8_t)) - malloc_0);

    root = malloc_total + 440058;
    root = (int32_t) ((uint8_t*) malloc(4*sizeof(int8_t)) - malloc_0);

    LC4 = malloc_total + 440062;
    int32_t arrayLC4[] = {.LC0,.LC1,.LC2};
    for(int i=0; i<3; i++) str(&arrayLC4[i], &LC4, i*4, 4, false, false, false);

    storestring = malloc_total + 440074;
    storestring = (int32_t) ((uint8_t*) calloc(4, sizeof(int8_t)) - malloc_0);

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "multikey_quick_sort.c";

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

void vecswap();
void ssort1();
void ssort1main();
void vecswap2();
void med3func();
void inssort();
void ssort2();
void ssort2main();
void insert1();
void cleanup1();
void insert2();
void cleanup2();
void search1();
void search2();
void pmsearch();
void nearsearch();
void main();

void idivmod()
{
    int32_t quot = r0.i / r1.i;
    int32_t rem = r0.i % r1.i;
    r0.i = quot;
    r1.i = rem;
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
void strlen_help()
{
    r0.i = (int32_t) strlen(malloc_0+r0.i);
}
void rand_help()
{
    r0.i = rand();
}

void vecswap()
{
    counters[0] ++;
    tmp = r2.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) 0);
    v = (r2.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (z || n != v)
    {
        return;
    }
    counters[1] ++;
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
    r4.i = (uint32_t)r0.i << 2;
    ip.i = (uint32_t)r1.i << 2;
    r6.i = r2.i - (1);
    r5.i = r4.i;
    r7.i = ip.i + (8);
    r4.i = r4.i + (8);
    lr.i = r3.i + (r5.i);
    tmp = r7.i - r5.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r7.i) >= ((uint32_t) r5.i);
    v = (r7.i&0x80000000) != (r5.i&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
    if (!z && n == v)
    {
        tmp = r4.i - ip.i;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r4.i) >= ((uint32_t) ip.i);
        v = (r4.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    }
    ip.i = r3.i + (ip.i);
    r5.i = ip.i | lr.i;
    if (z || n != v)
    {
        r4.i = 1;
    }
    if (!z && n == v)
    {
        r4.i = 0;
    }
    tmp = r6.i - 6;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) 6);
    v = (r6.i&0x80000000) != (6&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    if (!c || z)
    {
        r4.i = 0;
    }
    if (c && !z)
    {
        r4.i = r4.i & 1;
    }
    tmp = r5.i & 7;
    z = tmp == 0;
    n = tmp & 0x80000000;
    if (!z)
    {
        r4.i = 0;
    }
    tmp = r4.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 0);
    v = (r4.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (z)
    {
        goto L3;
    }
    counters[2] ++;
    r10.i = (uint32_t)r2.i >> 1;
    lr.i = lr.i - (8);
    r9.i = ip.i - (8);
    r10.i = ip.i + (((uint32_t)r10.i << 3));
    r8.i = lr.i;
L4:
    counters[3] ++;
    load_counter ++;
    ldr(&r4.i, &lr.i, 8, 4, true, false, false);
    ldr(&r5.i, &lr.i, 12, 4, true, false, false);
    load_counter ++;
    ldr(&r6.i, &r9.i, 8, 4, true, false, false);
    ldr(&r7.i, &r9.i, 12, 4, true, false, false);
    store_counter ++;
    str(&r6.i, &r8.i, 8, 4, true, false, false);
    str(&r7.i, &r8.i, 12, 4, true, false, false);
    store_counter ++;
    str(&r4.i, &ip.i, 8, 4, false, true, false);
    str(&r5.i, &ip.i, 12, 4, false, true, false);
    tmp = ip.i - r10.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r10.i);
    v = (ip.i&0x80000000) != (r10.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (!z)
    {
        goto L4;
    }
    counters[4] ++;
    ip.i = r2.i & ~1;
    tmp = r2.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) ip.i);
    v = (r2.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    r0.i = r0.i + (ip.i);
    r1.i = r1.i + (ip.i);
    load_counter ++;
    if (!z)
    {
        ldr(&r2.i, &r3.i, ((uint32_t)r0.i << 2), 4, false, false, false);
    }
    load_counter ++;
    if (!z)
    {
        ldr(&ip.i, &r3.i, ((uint32_t)r1.i << 2), 4, false, false, false);
    }
    store_counter ++;
    if (!z)
    {
        str(&ip.i, &r3.i, ((uint32_t)r0.i << 2), 4, false, false, false);
    }
    store_counter ++;
    if (!z)
    {
        str(&r2.i, &r3.i, ((uint32_t)r1.i << 2), 4, false, false, false);
    }
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
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;
L3:
    counters[5] ++;
    r0.i = r2.i + (r0.i);
    r3.i = r3.i + (((uint32_t)r0.i << 2));
L6:
    counters[6] ++;
    load_counter ++;
    ldr(&r1.i, &ip.i, 0, 4, false, true, false);
    load_counter ++;
    ldr(&r2.i, &lr.i, 0, 4, false, true, false);
    store_counter ++;
    str(&r1.i, &lr.i, 4, 4, false, true, false);
    tmp = lr.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) r3.i);
    v = (lr.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    store_counter ++;
    str(&r2.i, &ip.i, 4, 4, false, true, false);
    if (!z)
    {
        goto L6;
    }
    counters[7] ++;
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
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;

}

void ssort1()
{
    counters[8] ++;
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
    tmp = r1.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 1);
    v = (r1.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    sp.i = sp.i - (20);
    store_counter ++;
    str(&r1.i, &sp.i, 0, 4, false, true, false);
    if (z || n != v)
    {
        goto L15;
    }
    counters[9] ++;
    r6.i = r0.i;
    r7.i = r2.i;
    r3.i = r2.i + (1);
    store_counter ++;
    str(&r3.i, &sp.i, 12, 4, false, false, false);
L47:
    counters[10] ++;
    rand_help();
    counters[11] ++;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0, 4, false, true, false);
    r10.i = r6.i;
    fp.i = 0;
    r5.i = 1;
    r1.i = r4.i;
    idivmod();
    counters[12] ++;
    load_counter ++;
    ldr(&r3.i, &r6.i, 0, 4, false, true, false);
    r0.i = r4.i - (1);
    r4.i = r0.i;
    load_counter ++;
    ldr(&r2.i, &r6.i, ((uint32_t)r1.i << 2), 4, false, false, false);
    store_counter ++;
    str(&r2.i, &r6.i, 0, 4, false, true, false);
    store_counter ++;
    str(&r3.i, &r6.i, ((uint32_t)r1.i << 2), 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &r6.i, 0, 4, false, true, false);
    load_counter ++;
    ldr(&r9.i, &r3.i, r7.i, 1, false, false, false);
L17:
    counters[13] ++;
    load_counter ++;
    ldr(&r2.i, &r10.i, 4, 4, true, false, false);
    lr.i = fp.i;
    fp.i = fp.i + (1);
    load_counter ++;
    ldr(&r3.i, &r2.i, r7.i, 1, false, false, false);
    ip.i = fp.i;
    r3.i = r3.i - (r9.i);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L20;
    }
    counters[14] ++;
    tmp = fp.i - r0.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) fp.i) >= ((uint32_t) r0.i);
    v = (fp.i&0x80000000) != (r0.i&0x80000000) && (tmp&0x80000000) != (fp.i&0x80000000);
    if (!z && n == v)
    {
        goto L19;
    }
    counters[15] ++;
    r2.i = r6.i + (((uint32_t)r0.i << 2));
    goto L23;
L27:
    counters[16] ++;
    load_counter ++;
    if (z)
    {
        ldr(&r3.i, &r6.i, ((uint32_t)r4.i << 2), 4, false, false, false);
    }
    r0.i = r0.i - (1);
    store_counter ++;
    if (z)
    {
        str(&r3.i, &r2.i, 4, 4, false, false, false);
    }
    store_counter ++;
    if (z)
    {
        str(&r1.i, &r6.i, ((uint32_t)r4.i << 2), 4, false, false, false);
    }
    if (z)
    {
        r4.i = r4.i - (1);
    }
    tmp = r0.i - lr.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) lr.i);
    v = (r0.i&0x80000000) != (lr.i&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (z)
    {
        goto L19;
    }
L23:
    counters[17] ++;
    r8.i = r2.i;
    load_counter ++;
    ldr(&r1.i, &r2.i, -4, 4, false, true, false);
    load_counter ++;
    ldr(&r3.i, &r1.i, r7.i, 1, false, false, false);
    r3.i = r3.i - (r9.i);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (n == v)
    {
        goto L27;
    }
    counters[18] ++;
    load_counter ++;
    ldr(&r3.i, &r10.i, 0, 4, false, true, false);
    ip.i = lr.i + (2);
    r0.i = r0.i - (1);
    store_counter ++;
    str(&r1.i, &r10.i, 0, 4, false, true, false);
    store_counter ++;
    str(&r3.i, &r8.i, 0, 4, false, true, false);
L48:
    counters[19] ++;
    tmp = ip.i - r0.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r0.i);
    v = (ip.i&0x80000000) != (r0.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (z || n != v)
    {
        goto L17;
    }
L19:
    counters[20] ++;
    r8.i = ip.i - (r5.i);
    tmp = r8.i - r5.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) r5.i);
    v = (r8.i&0x80000000) != (r5.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    if (n != v)
    {
        lr.i = r8.i;
    }
    if (n == v)
    {
        lr.i = r5.i;
    }
    tmp = lr.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) 0);
    v = (lr.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    r9.i = ip.i - (lr.i);
    r10.i = lr.i - (1);
    if (z || n != v)
    {
        goto L32;
    }
    counters[21] ++;
    r2.i = (uint32_t)r9.i << 2;
    r3.i = r6.i + (8);
    r1.i = r6.i + (r2.i);
    r2.i = r2.i + (8);
    tmp = r1.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r3.i);
    v = (r1.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    fp.i = r6.i | r1.i;
    if (!c)
    {
        r3.i = 0;
    }
    if (c)
    {
        r3.i = 1;
    }
    tmp = r2.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) 0);
    v = (r2.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (z || n != v)
    {
        r3.i = r3.i | 1;
    }
    tmp = r10.i - 6;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r10.i) >= ((uint32_t) 6);
    v = (r10.i&0x80000000) != (6&0x80000000) && (tmp&0x80000000) != (r10.i&0x80000000);
    if (!c || z)
    {
        r3.i = 0;
    }
    if (c && !z)
    {
        r3.i = r3.i & 1;
    }
    tmp = fp.i & 7;
    z = tmp == 0;
    n = tmp & 0x80000000;
    if (!z)
    {
        r3.i = 0;
    }
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L29;
    }
    counters[22] ++;
    r10.i = (uint32_t)lr.i >> 1;
    fp.i = r6.i - (8);
    store_counter ++;
    str(&r5.i, &sp.i, 4, 4, false, false, false);
    r10.i = r1.i + (((uint32_t)r10.i << 3));
    store_counter ++;
    str(&r4.i, &sp.i, 8, 4, false, false, false);
L30:
    counters[23] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, 8, 4, true, false, false);
    ldr(&r3.i, &fp.i, 12, 4, true, false, false);
    load_counter ++;
    ldr(&r4.i, &r1.i, 0, 4, false, true, false);
    ldr(&r5.i, &r1.i, 4, 4, false, true, false);
    store_counter ++;
    str(&r4.i, &fp.i, 0, 4, false, true, false);
    str(&r5.i, &fp.i, 4, 4, false, true, false);
    store_counter ++;
    str(&r2.i, &r1.i, 8, 4, false, true, false);
    str(&r3.i, &r1.i, 12, 4, false, true, false);
    tmp = r10.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r10.i) >= ((uint32_t) r1.i);
    v = (r10.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r10.i&0x80000000);
    if (!z)
    {
        goto L30;
    }
    counters[24] ++;
    r3.i = lr.i & ~1;
    load_counter ++;
    ldr(&r5.i, &sp.i, 4, 4, false, false, false);
    tmp = lr.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) r3.i);
    v = (lr.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    load_counter ++;
    ldr(&r4.i, &sp.i, 8, 4, false, false, false);
    r9.i = r3.i + (r9.i);
    load_counter ++;
    if (!z)
    {
        ldr(&r2.i, &r6.i, ((uint32_t)r3.i << 2), 4, false, false, false);
    }
    load_counter ++;
    if (!z)
    {
        ldr(&r1.i, &r6.i, ((uint32_t)r9.i << 2), 4, false, false, false);
    }
    store_counter ++;
    if (!z)
    {
        str(&r1.i, &r6.i, ((uint32_t)r3.i << 2), 4, false, false, false);
    }
    store_counter ++;
    if (!z)
    {
        str(&r2.i, &r6.i, ((uint32_t)r9.i << 2), 4, false, false, false);
    }
L32:
    counters[25] ++;
    load_counter ++;
    ldr(&r3.i, &sp.i, 0, 4, false, true, false);
    r9.i = r4.i - (r0.i);
    r1.i = r3.i - (r4.i);
    tmp = r1.i - r9.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r9.i);
    v = (r1.i&0x80000000) != (r9.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!z && n == v)
    {
        r1.i = r9.i;
    }
    if (z || n != v)
    {
        r1.i = r1.i - (1);
    }
L25:
    counters[26] ++;
    tmp = r1.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 0);
    v = (r1.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    fp.i = r3.i - (r1.i);
    r10.i = r1.i - (1);
    if (z || n != v)
    {
        goto L42;
    }
    counters[27] ++;
    lr.i = (uint32_t)ip.i << 2;
    r3.i = (uint32_t)fp.i << 2;
    r0.i = lr.i + (8);
    r2.i = r6.i + (lr.i);
    store_counter ++;
    str(&r2.i, &sp.i, 4, 4, false, false, false);
    r2.i = r3.i + (8);
    tmp = lr.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) r2.i);
    v = (lr.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    if (n != v)
    {
        tmp = r3.i - r0.i;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r3.i) >= ((uint32_t) r0.i);
        v = (r3.i&0x80000000) != (r0.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    }
    load_counter ++;
    ldr(&r2.i, &sp.i, 4, 4, false, false, false);
    lr.i = r6.i + (r3.i);
    r3.i = lr.i | r2.i;
    if (n == v)
    {
        r0.i = 1;
    }
    if (n != v)
    {
        r0.i = 0;
    }
    tmp = r10.i - 6;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r10.i) >= ((uint32_t) 6);
    v = (r10.i&0x80000000) != (6&0x80000000) && (tmp&0x80000000) != (r10.i&0x80000000);
    if (!c || z)
    {
        r0.i = 0;
    }
    if (c && !z)
    {
        r0.i = r0.i & 1;
    }
    tmp = r3.i & 7;
    z = tmp == 0;
    n = tmp & 0x80000000;
    if (!z)
    {
        r0.i = 0;
    }
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (z)
    {
        goto L39;
    }
    counters[28] ++;
    r10.i = (uint32_t)r1.i >> 1;
    r0.i = r2.i - (8);
    store_counter ++;
    str(&r5.i, &sp.i, 4, 4, false, false, false);
    r10.i = lr.i + (((uint32_t)r10.i << 3));
    store_counter ++;
    str(&r4.i, &sp.i, 8, 4, false, false, false);
L40:
    counters[29] ++;
    load_counter ++;
    ldr(&r2.i, &r0.i, 8, 4, true, false, false);
    ldr(&r3.i, &r0.i, 12, 4, true, false, false);
    load_counter ++;
    ldr(&r4.i, &lr.i, 0, 4, false, true, false);
    ldr(&r5.i, &lr.i, 4, 4, false, true, false);
    store_counter ++;
    str(&r4.i, &r0.i, 0, 4, false, true, false);
    str(&r5.i, &r0.i, 4, 4, false, true, false);
    store_counter ++;
    str(&r2.i, &lr.i, 8, 4, false, true, false);
    str(&r3.i, &lr.i, 12, 4, false, true, false);
    tmp = lr.i - r10.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) r10.i);
    v = (lr.i&0x80000000) != (r10.i&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    if (!z)
    {
        goto L40;
    }
    counters[30] ++;
    r3.i = r1.i & ~1;
    load_counter ++;
    ldr(&r5.i, &sp.i, 4, 4, false, false, false);
    tmp = r3.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r1.i);
    v = (r3.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    ip.i = r3.i + (ip.i);
    load_counter ++;
    ldr(&r4.i, &sp.i, 8, 4, false, false, false);
    r3.i = fp.i + (r3.i);
    load_counter ++;
    if (!z)
    {
        ldr(&r2.i, &r6.i, ((uint32_t)ip.i << 2), 4, false, false, false);
    }
    load_counter ++;
    if (!z)
    {
        ldr(&r1.i, &r6.i, ((uint32_t)r3.i << 2), 4, false, false, false);
    }
    store_counter ++;
    if (!z)
    {
        str(&r1.i, &r6.i, ((uint32_t)ip.i << 2), 4, false, false, false);
    }
    store_counter ++;
    if (!z)
    {
        str(&r2.i, &r6.i, ((uint32_t)r3.i << 2), 4, false, false, false);
    }
L42:
    counters[31] ++;
    r0.i = r6.i;
    r2.i = r7.i;
    r1.i = r8.i;
    ssort1();
    counters[32] ++;
    load_counter ++;
    ldr(&r3.i, &r6.i, ((uint32_t)r8.i << 2), 4, false, false, false);
    r0.i = r6.i + (((uint32_t)r8.i << 2));
    load_counter ++;
    ldr(&r3.i, &r3.i, r7.i, 1, false, false, false);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L59;
    }
L38:
    counters[33] ++;
    load_counter ++;
    ldr(&r3.i, &sp.i, 0, 4, false, true, false);
    tmp = r9.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r9.i) >= ((uint32_t) 1);
    v = (r9.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r9.i&0x80000000);
    r3.i = r3.i - (r9.i);
    r6.i = r6.i + (((uint32_t)r3.i << 2));
    if (z || n != v)
    {
        goto L15;
    }
    counters[34] ++;
    store_counter ++;
    str(&r9.i, &sp.i, 0, 4, false, true, false);
    goto L47;
L20:
    counters[35] ++;
    load_counter ++;
    if (z)
    {
        ldr(&r3.i, &r6.i, ((uint32_t)r5.i << 2), 4, false, false, false);
    }
    ip.i = lr.i + (2);
    store_counter ++;
    if (z)
    {
        str(&r2.i, &r6.i, ((uint32_t)r5.i << 2), 4, false, false, false);
    }
    if (z)
    {
        r5.i = r5.i + (1);
    }
    store_counter ++;
    if (z)
    {
        str(&r3.i, &r10.i, 0, 4, false, true, false);
    }
    goto L48;
L29:
    counters[36] ++;
    lr.i = r6.i + (((uint32_t)lr.i << 2));
    r3.i = r6.i;
L34:
    counters[37] ++;
    load_counter ++;
    ldr(&r9.i, &r1.i, 0, 4, false, true, false);
    load_counter ++;
    ldr(&r2.i, &r3.i, 0, 4, false, true, false);
    store_counter ++;
    str(&r9.i, &r3.i, 4, 4, false, true, false);
    tmp = lr.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) r3.i);
    v = (lr.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    store_counter ++;
    str(&r2.i, &r1.i, 4, 4, false, true, false);
    if (!z)
    {
        goto L34;
    }
    counters[38] ++;
    goto L32;
L59:
    counters[39] ++;
    load_counter ++;
    ldr(&r3.i, &sp.i, 0, 4, false, true, false);
    load_counter ++;
    ldr(&r2.i, &sp.i, 12, 4, false, false, false);
    r1.i = r3.i + (r5.i);
    r1.i = r1.i - (r4.i);
    r1.i = r1.i - (1);
    ssort1();
    counters[40] ++;
    goto L38;
L15:
    counters[41] ++;
    sp.i = sp.i + (20);
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
L39:
    counters[42] ++;
    r1.i = r1.i + (ip.i);
    r3.i = lr.i;
    r1.i = r6.i + (((uint32_t)r1.i << 2));
L44:
    counters[43] ++;
    load_counter ++;
    ldr(&ip.i, &r3.i, 0, 4, false, true, false);
    load_counter ++;
    ldr(&r0.i, &r2.i, 0, 4, false, true, false);
    store_counter ++;
    str(&ip.i, &r2.i, 4, 4, false, true, false);
    tmp = r2.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r1.i);
    v = (r2.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    store_counter ++;
    str(&r0.i, &r3.i, 4, 4, false, true, false);
    if (!z)
    {
        goto L44;
    }
    counters[44] ++;
    goto L42;
    return;
}

void ssort1main()
{
    counters[45] ++;
    r2.i = 0;
    ssort1();
    return;

}

void vecswap2()
{
    counters[46] ++;
    tmp = r2.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) 0);
    v = (r2.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (z || n != v)
    {
        return;
    }
    counters[47] ++;
    r3.i = r0.i + (7);
    ip.i = r2.i - (1);
    r3.i = r3.i - (r1.i);
    tmp = r3.i - 14;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 14);
    v = (r3.i&0x80000000) != (14&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (c && !z)
    {
        tmp = ip.i - 6;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) ip.i) >= ((uint32_t) 6);
        v = (ip.i&0x80000000) != (6&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    }
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
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
    lr.i = r0.i | r1.i;
    if (c && !z)
    {
        r3.i = 1;
    }
    if (!c || z)
    {
        r3.i = 0;
    }
    tmp = lr.i & 7;
    z = tmp == 0;
    n = tmp & 0x80000000;
    if (!z)
    {
        r3.i = 0;
    }
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L63;
    }
    counters[48] ++;
    r8.i = (uint32_t)r2.i >> 1;
    lr.i = r0.i - (8);
    ip.i = r1.i;
    r3.i = 0;
L64:
    counters[49] ++;
    load_counter ++;
    ldr(&r6.i, &lr.i, 8, 4, true, false, false);
    ldr(&r7.i, &lr.i, 12, 4, true, false, false);
    r3.i = r3.i + (1);
    load_counter ++;
    ldr(&r4.i, &ip.i, 0, 4, false, true, false);
    ldr(&r5.i, &ip.i, 4, 4, false, true, false);
    tmp = r3.i - r8.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r8.i);
    v = (r3.i&0x80000000) != (r8.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    store_counter ++;
    str(&r4.i, &lr.i, 0, 4, false, true, false);
    str(&r5.i, &lr.i, 4, 4, false, true, false);
    store_counter ++;
    str(&r6.i, &ip.i, 8, 4, false, true, false);
    str(&r7.i, &ip.i, 12, 4, false, true, false);
    if (!z)
    {
        goto L64;
    }
    counters[50] ++;
    tmp = r2.i & 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    r2.i = r2.i & ~1;
    load_counter ++;
    if (!z)
    {
        ldr(&r3.i, &r0.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    }
    load_counter ++;
    if (!z)
    {
        ldr(&ip.i, &r1.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    }
    store_counter ++;
    if (!z)
    {
        str(&ip.i, &r0.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    }
    store_counter ++;
    if (!z)
    {
        str(&r3.i, &r1.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    }
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
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;
L63:
    counters[51] ++;
    load_counter ++;
    ldr(&r3.i, &r0.i, 0, 4, false, true, false);
    ip.i = ip.i - (1);
    load_counter ++;
    ldr(&r2.i, &r1.i, 0, 4, false, true, false);
    tmp = ip.i + 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) tmp) < ((uint32_t) ip.i);
    v = (ip.i&0x80000000) == (1&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    store_counter ++;
    str(&r2.i, &r0.i, 4, 4, false, true, false);
    store_counter ++;
    str(&r3.i, &r1.i, 4, 4, false, true, false);
    if (!z)
    {
        goto L63;
    }
    counters[52] ++;
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
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;

}

void med3func()
{
    counters[53] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r4.i, &sp.i, 0, 4, false, false, false);
    load_counter ++;
    ldr(&ip.i, &r1.i, 0, 4, false, true, false);
    load_counter ++;
    ldr(&lr.i, &r0.i, 0, 4, false, true, false);
    load_counter ++;
    ldr(&ip.i, &ip.i, r3.i, 1, false, false, false);
    load_counter ++;
    ldr(&lr.i, &lr.i, r3.i, 1, false, false, false);
    tmp = lr.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) ip.i);
    v = (lr.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    load_counter ++;
    if (z)
    {
        ldr(&r4.i, &sp.i, 0, 4, false, false, false);
        sp.i += 4;
        ldr(&pc.i, &sp.i, 0, 4, false, false, false);
        sp.i += 4;
        return;
    }
    load_counter ++;
    ldr(&r4.i, &r2.i, 0, 4, false, true, false);
    load_counter ++;
    ldr(&r3.i, &r4.i, r3.i, 1, false, false, false);
    tmp = ip.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r3.i);
    v = (ip.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (!z)
    {
        tmp = lr.i - r3.i;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) lr.i) >= ((uint32_t) r3.i);
        v = (lr.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    }
    if (z)
    {
        goto L79;
    }
    counters[54] ++;
    tmp = lr.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) ip.i);
    v = (lr.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    if (n == v)
    {
        goto L77;
    }
    counters[55] ++;
    tmp = ip.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r3.i);
    v = (ip.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (n != v)
    {
        goto L82;
    }
    counters[56] ++;
    tmp = lr.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) r3.i);
    v = (lr.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    if (n != v)
    {
        r0.i = r2.i;
    }
    load_counter ++;
    ldr(&r4.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;
L79:
    counters[57] ++;
    r0.i = r2.i;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;
L77:
    counters[58] ++;
    tmp = ip.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r3.i);
    v = (ip.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (z || n != v)
    {
        goto L85;
    }
L82:
    counters[59] ++;
    r0.i = r1.i;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;
L85:
    counters[60] ++;
    tmp = lr.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) r3.i);
    v = (lr.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    if (n == v)
    {
        r0.i = r2.i;
    }
    load_counter ++;
    ldr(&r4.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;

}

void inssort()
{
    counters[61] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
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
    r6.i = r1.i - (1);
    tmp = r6.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) 0);
    v = (r6.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    load_counter ++;
    if (z || n != v)
    {
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
        ldr(&pc.i, &sp.i, 0, 4, false, false, false);
        sp.i += 4;
        return;
    }
    r7.i = r0.i + (4);
    r8.i = r0.i;
    lr.i = r2.i;
L87:
    counters[62] ++;
    tmp = r8.i - r7.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) r7.i);
    v = (r8.i&0x80000000) != (r7.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    if (!c)
    {
        ip.i = r7.i;
    }
    if (c)
    {
        goto L92;
    }
L93:
    counters[63] ++;
    load_counter ++;
    ldr(&r5.i, &ip.i, -4, 4, false, false, false);
    load_counter ++;
    ldr(&r4.i, &ip.i, -4, 4, false, true, false);
    r0.i = r5.i + (lr.i);
    load_counter ++;
    ldr(&r3.i, &r5.i, lr.i, 1, false, false, false);
    r1.i = r4.i + (lr.i);
    load_counter ++;
    ldr(&r2.i, &r4.i, lr.i, 1, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (z)
    {
        goto L90;
    }
    counters[64] ++;
    goto L89;
L91:
    counters[65] ++;
    load_counter ++;
    ldr(&r3.i, &r0.i, 1, 1, true, false, false);
    load_counter ++;
    ldr(&r2.i, &r1.i, 1, 1, true, false, false);
    tmp = r3.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r2.i);
    v = (r3.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L89;
    }
L90:
    counters[66] ++;
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L91;
    }
L92:
    counters[67] ++;
    r6.i = r6.i - (1);
    z = r6.i == 0;
    n = r6.i & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) 1);
    v = (r6.i&0x80000000) != (1&0x80000000) && (r6.i&0x80000000) != (r6.i&0x80000000);
    r7.i = r7.i + (4);
    if (!z)
    {
        goto L87;
    }
    counters[68] ++;
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
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;
L89:
    counters[69] ++;
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (c)
    {
        goto L92;
    }
    counters[70] ++;
    tmp = ip.i - r8.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r8.i);
    v = (ip.i&0x80000000) != (r8.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    store_counter ++;
    str(&r4.i, &ip.i, 0, 4, false, true, false);
    str(&r5.i, &ip.i, 4, 4, false, true, false);
    if (c && !z)
    {
        goto L93;
    }
    counters[71] ++;
    goto L92;
    return;
}

void ssort2()
{
    counters[72] ++;
    tmp = r1.i - 9;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 9);
    v = (r1.i&0x80000000) != (9&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
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
    r8.i = r1.i;
    sp.i = sp.i - (36);
    fp.i = r0.i;
    r6.i = r2.i;
    if (z || n != v)
    {
        goto L154;
    }
L155:
    counters[73] ++;
    r3.i = r8.i >> 1;
    load_counter ++;
    ldr(&r0.i, &fp.i, 0, 4, false, true, false);
    r10.i = r8.i - (-1073741823);
    tmp = r8.i - 30;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) 30);
    v = (r8.i&0x80000000) != (30&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    load_counter ++;
    ldr(&r9.i, &fp.i, ((uint32_t)r3.i << 2), 4, false, false, false);
    r3.i = fp.i + (((uint32_t)r3.i << 2));
    r10.i = (uint32_t)r10.i << 2;
    load_counter ++;
    ldr(&r1.i, &r0.i, r6.i, 1, false, false, false);
    r4.i = fp.i + (r10.i);
    store_counter ++;
    str(&r8.i, &sp.i, 16, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &r9.i, r6.i, 1, false, false, false);
    if (z || n != v)
    {
        goto L156;
    }
    counters[74] ++;
    lr.i = r8.i >> 3;
    load_counter ++;
    ldr(&r5.i, &fp.i, ((uint32_t)lr.i << 2), 4, false, false, false);
    ip.i = (uint32_t)lr.i << 2;
    r8.i = fp.i + (ip.i);
    r7.i = (uint32_t)lr.i << 3;
    store_counter ++;
    str(&r7.i, &sp.i, 8, 4, false, false, false);
    r7.i = r8.i + (ip.i);
    store_counter ++;
    str(&r5.i, &sp.i, 12, 4, false, false, false);
    load_counter ++;
    ldr(&r5.i, &r5.i, r6.i, 1, false, false, false);
    store_counter ++;
    str(&r7.i, &sp.i, 0, 4, false, true, false);
    tmp = r5.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r1.i);
    v = (r5.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (z)
    {
        goto L160;
    }
    counters[75] ++;
    load_counter ++;
    ldr(&r7.i, &r8.i, ((uint32_t)lr.i << 2), 4, false, false, false);
    store_counter ++;
    str(&r7.i, &sp.i, 4, 4, false, false, false);
    load_counter ++;
    ldr(&r7.i, &r7.i, r6.i, 1, false, false, false);
    tmp = r7.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r7.i) >= ((uint32_t) r1.i);
    v = (r7.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
    if (!z)
    {
        tmp = r5.i - r7.i;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r5.i) >= ((uint32_t) r7.i);
        v = (r5.i&0x80000000) != (r7.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    }
    if (z)
    {
        goto L162;
    }
    counters[76] ++;
    tmp = r5.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r1.i);
    v = (r5.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (z || n != v)
    {
        goto L115;
    }
    counters[77] ++;
    tmp = r5.i - r7.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r7.i);
    v = (r5.i&0x80000000) != (r7.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (n == v)
    {
        goto L198;
    }
L161:
    counters[78] ++;
    r1.i = r5.i;
    load_counter ++;
    ldr(&r5.i, &sp.i, 12, 4, false, false, false);
    store_counter ++;
    str(&r8.i, &sp.i, 0, 4, false, true, false);
    store_counter ++;
    str(&r5.i, &sp.i, 4, 4, false, false, false);
L114:
    counters[79] ++;
    r5.i = 0 - ip.i;
    r7.i = r3.i - (ip.i);
    store_counter ++;
    str(&r7.i, &sp.i, 12, 4, false, false, false);
    ip.i = r3.i + (ip.i);
    load_counter ++;
    ldr(&r7.i, &r3.i, r5.i, 4, false, false, false);
    store_counter ++;
    str(&ip.i, &sp.i, 20, 4, false, false, false);
    load_counter ++;
    ldr(&ip.i, &r7.i, r6.i, 1, false, false, false);
    tmp = ip.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r2.i);
    v = (ip.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (z)
    {
        goto L195;
    }
    counters[80] ++;
    load_counter ++;
    ldr(&r8.i, &r3.i, ((uint32_t)lr.i << 2), 4, false, false, false);
    load_counter ++;
    ldr(&lr.i, &r8.i, r6.i, 1, false, false, false);
    tmp = lr.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) r2.i);
    v = (lr.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    if (!z)
    {
        tmp = ip.i - lr.i;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) ip.i) >= ((uint32_t) lr.i);
        v = (ip.i&0x80000000) != (lr.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    }
    if (z)
    {
        goto L166;
    }
    counters[81] ++;
    tmp = ip.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r2.i);
    v = (ip.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (n == v)
    {
        goto L117;
    }
    counters[82] ++;
    tmp = lr.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) r2.i);
    v = (lr.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    if (z || n != v)
    {
        goto L199;
    }
L116:
    counters[83] ++;
    load_counter ++;
    ldr(&ip.i, &sp.i, 8, 4, false, false, false);
    r8.i = r4.i + (r5.i);
    load_counter ++;
    ldr(&lr.i, &r4.i, r5.i, 4, false, false, false);
    ip.i = r4.i - (ip.i);
    load_counter ++;
    ldr(&r7.i, &ip.i, 0, 4, false, true, false);
    load_counter ++;
    ldr(&r5.i, &lr.i, r6.i, 1, false, false, false);
    load_counter ++;
    ldr(&lr.i, &r7.i, r6.i, 1, false, false, false);
    tmp = lr.i - r5.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) r5.i);
    v = (lr.i&0x80000000) != (r5.i&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    if (z)
    {
        goto L113;
    }
    counters[84] ++;
    load_counter ++;
    ldr(&r7.i, &r4.i, 0, 4, false, true, false);
    load_counter ++;
    ldr(&r7.i, &r7.i, r6.i, 1, false, false, false);
    tmp = lr.i - r7.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) r7.i);
    v = (lr.i&0x80000000) != (r7.i&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    if (!z)
    {
        tmp = r5.i - r7.i;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r5.i) >= ((uint32_t) r7.i);
        v = (r5.i&0x80000000) != (r7.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    }
    if (z)
    {
        ip.i = r4.i;
    }
    if (z)
    {
        goto L113;
    }
    counters[85] ++;
    tmp = lr.i - r5.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) r5.i);
    v = (lr.i&0x80000000) != (r5.i&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    if (n == v)
    {
        goto L118;
    }
    counters[86] ++;
    tmp = r5.i - r7.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r7.i);
    v = (r5.i&0x80000000) != (r7.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (n == v)
    {
        goto L200;
    }
L170:
    counters[87] ++;
    ip.i = r8.i;
L113:
    counters[88] ++;
    tmp = r1.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r2.i);
    v = (r1.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (z)
    {
        goto L171;
    }
L205:
    counters[89] ++;
    load_counter ++;
    ldr(&lr.i, &ip.i, 0, 4, false, true, false);
    load_counter ++;
    ldr(&r5.i, &lr.i, r6.i, 1, false, false, false);
    tmp = r5.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r1.i);
    v = (r5.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (!z)
    {
        tmp = r5.i - r2.i;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r5.i) >= ((uint32_t) r2.i);
        v = (r5.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    }
    if (z)
    {
        goto L119;
    }
    counters[90] ++;
    tmp = r1.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r2.i);
    v = (r1.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (n == v)
    {
        goto L120;
    }
    counters[91] ++;
    tmp = r5.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r2.i);
    v = (r5.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (!z && n == v)
    {
        goto L173;
    }
    counters[92] ++;
    load_counter ++;
    ldr(&r3.i, &sp.i, 4, 4, false, false, false);
    tmp = r5.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r1.i);
    v = (r5.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (z || n != v)
    {
        lr.i = r3.i;
    }
    load_counter ++;
    ldr(&r3.i, &sp.i, 0, 4, false, true, false);
    if (z || n != v)
    {
        ip.i = r3.i;
    }
L119:
    counters[93] ++;
    r2.i = fp.i;
    store_counter ++;
    str(&lr.i, &r2.i, 4, 4, false, true, false);
    tmp = r4.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r2.i);
    v = (r4.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    store_counter ++;
    str(&r0.i, &ip.i, 0, 4, false, true, false);
    if (!c)
    {
        goto L201;
    }
    counters[94] ++;
    load_counter ++;
    ldr(&r1.i, &fp.i, 0, 4, false, true, false);
    r3.i = r2.i;
    r7.i = r2.i;
    lr.i = fp.i;
    r5.i = r4.i;
    load_counter ++;
    ldr(&r8.i, &r1.i, r6.i, 1, false, false, false);
L124:
    counters[95] ++;
    load_counter ++;
    ldr(&r0.i, &lr.i, 4, 4, true, false, false);
    r2.i = r3.i;
    r3.i = r3.i + (4);
    load_counter ++;
    ldr(&r1.i, &r0.i, r6.i, 1, false, false, false);
    r1.i = r1.i - (r8.i);
    tmp = r1.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 0);
    v = (r1.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (z || n != v)
    {
        goto L126;
    }
    counters[96] ++;
    tmp = lr.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) r4.i);
    v = (lr.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    if (c && !z)
    {
        goto L197;
    }
    counters[97] ++;
    r1.i = r4.i;
    goto L129;
L130:
    counters[98] ++;
    load_counter ++;
    if (z)
    {
        ldr(&r0.i, &r5.i, 0, 4, false, true, false);
    }
    store_counter ++;
    if (z)
    {
        str(&r0.i, &r1.i, 4, 4, false, false, false);
    }
    store_counter ++;
    if (z)
    {
        str(&ip.i, &r5.i, -4, 4, false, true, false);
    }
    tmp = r1.i - lr.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) lr.i);
    v = (r1.i&0x80000000) != (lr.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!c)
    {
        goto L202;
    }
L129:
    counters[99] ++;
    r4.i = r1.i;
    load_counter ++;
    ldr(&ip.i, &r1.i, -4, 4, false, true, false);
    load_counter ++;
    ldr(&r0.i, &ip.i, r6.i, 1, false, false, false);
    r0.i = r0.i - (r8.i);
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (n == v)
    {
        goto L130;
    }
    counters[100] ++;
    tmp = lr.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) r4.i);
    v = (lr.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    if (c && !z)
    {
        goto L197;
    }
    counters[101] ++;
    load_counter ++;
    ldr(&r1.i, &lr.i, 0, 4, false, true, false);
    r2.i = r3.i;
    store_counter ++;
    str(&ip.i, &lr.i, 0, 4, false, true, false);
    store_counter ++;
    str(&r1.i, &r4.i, -4, 4, false, true, false);
L132:
    counters[102] ++;
    tmp = r4.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r3.i);
    v = (r4.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (c)
    {
        goto L124;
    }
    counters[103] ++;
    r4.i = r5.i - (r4.i);
    r3.i = r3.i - (r7.i);
    r1.i = r7.i - (fp.i);
    store_counter ++;
    str(&r1.i, &sp.i, 4, 4, false, false, false);
    r8.i = r4.i >> 2;
    r1.i = fp.i + (r3.i);
    store_counter ++;
    str(&r1.i, &sp.i, 0, 4, false, true, false);
    r1.i = r3.i >> 2;
    store_counter ++;
    str(&r1.i, &sp.i, 8, 4, false, false, false);
L125:
    counters[104] ++;
    load_counter ++;
    ldr(&r1.i, &sp.i, 4, 4, false, false, false);
    r0.i = r10.i + (4);
    store_counter ++;
    str(&r0.i, &sp.i, 20, 4, false, false, false);
    r0.i = fp.i + (r0.i);
    tmp = r1.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r3.i);
    v = (r1.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    store_counter ++;
    str(&r0.i, &sp.i, 12, 4, false, false, false);
    if (z || n != v)
    {
        ip.i = r1.i >> 2;
    }
    load_counter ++;
    if (!z && n == v)
    {
        ldr(&ip.i, &sp.i, 8, 4, false, false, false);
    }
L133:
    counters[105] ++;
    tmp = ip.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) 0);
    v = (ip.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    r0.i = (uint32_t)ip.i << 2;
    r7.i = r2.i - (r0.i);
    r10.i = ip.i - (1);
    if (z || n != v)
    {
        goto L140;
    }
    counters[106] ++;
    r1.i = 8 - r0.i;
    r9.i = fp.i + (8);
    r1.i = r2.i + (r1.i);
    lr.i = r7.i | fp.i;
    tmp = r7.i - r9.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r7.i) >= ((uint32_t) r9.i);
    v = (r7.i&0x80000000) != (r9.i&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
    if (!c)
    {
        tmp = fp.i - r1.i;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) fp.i) >= ((uint32_t) r1.i);
        v = (fp.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (fp.i&0x80000000);
    }
    if (c)
    {
        r1.i = 1;
    }
    if (!c)
    {
        r1.i = 0;
    }
    tmp = r10.i - 6;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r10.i) >= ((uint32_t) 6);
    v = (r10.i&0x80000000) != (6&0x80000000) && (tmp&0x80000000) != (r10.i&0x80000000);
    if (!c || z)
    {
        r1.i = 0;
    }
    if (c && !z)
    {
        r1.i = r1.i & 1;
    }
    tmp = lr.i & 7;
    z = tmp == 0;
    n = tmp & 0x80000000;
    if (!z)
    {
        r1.i = 0;
    }
    tmp = r1.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 0);
    v = (r1.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (z)
    {
        goto L137;
    }
    counters[107] ++;
    r10.i = (uint32_t)ip.i >> 1;
    r9.i = fp.i - (8);
    lr.i = r7.i;
    store_counter ++;
    str(&r2.i, &sp.i, 24, 4, false, false, false);
    str(&r3.i, &sp.i, 28, 4, false, false, false);
    r10.i = r7.i + (((uint32_t)r10.i << 3));
L138:
    counters[108] ++;
    load_counter ++;
    ldr(&r0.i, &r9.i, 8, 4, true, false, false);
    ldr(&r1.i, &r9.i, 12, 4, true, false, false);
    load_counter ++;
    ldr(&r2.i, &lr.i, 0, 4, false, true, false);
    ldr(&r3.i, &lr.i, 4, 4, false, true, false);
    store_counter ++;
    str(&r2.i, &r9.i, 0, 4, false, true, false);
    str(&r3.i, &r9.i, 4, 4, false, true, false);
    store_counter ++;
    str(&r0.i, &lr.i, 8, 4, false, true, false);
    str(&r1.i, &lr.i, 12, 4, false, true, false);
    tmp = r10.i - lr.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r10.i) >= ((uint32_t) lr.i);
    v = (r10.i&0x80000000) != (lr.i&0x80000000) && (tmp&0x80000000) != (r10.i&0x80000000);
    if (!z)
    {
        goto L138;
    }
    counters[109] ++;
    tmp = ip.i & 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    load_counter ++;
    ldr(&r2.i, &sp.i, 24, 4, false, false, false);
    ldr(&r3.i, &sp.i, 28, 4, false, false, false);
    ip.i = ip.i & ~1;
    load_counter ++;
    if (!z)
    {
        ldr(&r1.i, &fp.i, ((uint32_t)ip.i << 2), 4, false, false, false);
    }
    load_counter ++;
    if (!z)
    {
        ldr(&r0.i, &r7.i, ((uint32_t)ip.i << 2), 4, false, false, false);
    }
    store_counter ++;
    if (!z)
    {
        str(&r0.i, &fp.i, ((uint32_t)ip.i << 2), 4, false, false, false);
    }
    store_counter ++;
    if (!z)
    {
        str(&r1.i, &r7.i, ((uint32_t)ip.i << 2), 4, false, false, false);
    }
L140:
    counters[110] ++;
    load_counter ++;
    ldr(&r1.i, &sp.i, 12, 4, false, false, false);
    r1.i = r1.i - (r5.i);
    tmp = r1.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r4.i);
    v = (r1.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!z && n == v)
    {
        ip.i = r8.i;
    }
    if (z || n != v)
    {
        r1.i = r1.i >> 2;
    }
    if (z || n != v)
    {
        ip.i = r1.i - (1);
    }
L135:
    counters[111] ++;
    load_counter ++;
    ldr(&r1.i, &sp.i, 12, 4, false, false, false);
    tmp = ip.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) 0);
    v = (ip.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    lr.i = (uint32_t)ip.i << 2;
    r9.i = ip.i - (1);
    r7.i = r1.i - (lr.i);
    if (z || n != v)
    {
        goto L150;
    }
    counters[112] ++;
    load_counter ++;
    ldr(&r1.i, &sp.i, 20, 4, false, false, false);
    r0.i = r2.i + (8);
    lr.i = r1.i - (lr.i);
    r1.i = lr.i + (8);
    lr.i = fp.i + (lr.i);
    r1.i = fp.i + (r1.i);
    r10.i = lr.i | r2.i;
    tmp = lr.i - r0.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) r0.i);
    v = (lr.i&0x80000000) != (r0.i&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    if (!c)
    {
        tmp = r2.i - r1.i;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r2.i) >= ((uint32_t) r1.i);
        v = (r2.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    }
    if (c)
    {
        r1.i = 1;
    }
    if (!c)
    {
        r1.i = 0;
    }
    tmp = r9.i - 6;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r9.i) >= ((uint32_t) 6);
    v = (r9.i&0x80000000) != (6&0x80000000) && (tmp&0x80000000) != (r9.i&0x80000000);
    if (!c || z)
    {
        r1.i = 0;
    }
    if (c && !z)
    {
        r1.i = r1.i & 1;
    }
    tmp = r10.i & 7;
    z = tmp == 0;
    n = tmp & 0x80000000;
    if (!z)
    {
        r1.i = 0;
    }
    tmp = r1.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 0);
    v = (r1.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (z)
    {
        goto L193;
    }
    counters[113] ++;
    r10.i = (uint32_t)ip.i >> 1;
    r9.i = r2.i - (8);
    store_counter ++;
    str(&r2.i, &sp.i, 20, 4, false, false, false);
    str(&r3.i, &sp.i, 24, 4, false, false, false);
    r10.i = lr.i + (((uint32_t)r10.i << 3));
L148:
    counters[114] ++;
    load_counter ++;
    ldr(&r0.i, &r9.i, 8, 4, true, false, false);
    ldr(&r1.i, &r9.i, 12, 4, true, false, false);
    load_counter ++;
    ldr(&r2.i, &lr.i, 0, 4, false, true, false);
    ldr(&r3.i, &lr.i, 4, 4, false, true, false);
    store_counter ++;
    str(&r2.i, &r9.i, 0, 4, false, true, false);
    str(&r3.i, &r9.i, 4, 4, false, true, false);
    store_counter ++;
    str(&r0.i, &lr.i, 8, 4, false, true, false);
    str(&r1.i, &lr.i, 12, 4, false, true, false);
    tmp = lr.i - r10.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) r10.i);
    v = (lr.i&0x80000000) != (r10.i&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    if (!z)
    {
        goto L148;
    }
    counters[115] ++;
    tmp = ip.i & 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    load_counter ++;
    ldr(&r2.i, &sp.i, 20, 4, false, false, false);
    ldr(&r3.i, &sp.i, 24, 4, false, false, false);
    ip.i = ip.i & ~1;
    load_counter ++;
    if (!z)
    {
        ldr(&r1.i, &r2.i, ((uint32_t)ip.i << 2), 4, false, false, false);
    }
    load_counter ++;
    if (!z)
    {
        ldr(&r0.i, &r7.i, ((uint32_t)ip.i << 2), 4, false, false, false);
    }
    store_counter ++;
    if (!z)
    {
        str(&r0.i, &r2.i, ((uint32_t)ip.i << 2), 4, false, false, false);
    }
    store_counter ++;
    if (!z)
    {
        str(&r1.i, &r7.i, ((uint32_t)ip.i << 2), 4, false, false, false);
    }
L150:
    counters[116] ++;
    tmp = r3.i - 4;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 4);
    v = (r3.i&0x80000000) != (4&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z && n == v)
    {
        goto L203;
    }
L146:
    counters[117] ++;
    load_counter ++;
    ldr(&r3.i, &sp.i, 0, 4, false, true, false);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, true, false);
    load_counter ++;
    ldr(&r3.i, &r3.i, r6.i, 1, false, false, false);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L204;
    }
L153:
    counters[118] ++;
    tmp = r4.i - 4;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 4);
    v = (r4.i&0x80000000) != (4&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (z || n != v)
    {
        goto L102;
    }
    counters[119] ++;
    load_counter ++;
    ldr(&r3.i, &sp.i, 16, 4, false, false, false);
    tmp = r4.i - 36;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 36);
    v = (r4.i&0x80000000) != (36&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    r3.i = r3.i - (r8.i);
    fp.i = fp.i + (((uint32_t)r3.i << 2));
    if (!z && n == v)
    {
        goto L155;
    }
L154:
    counters[120] ++;
    tmp = r8.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) 1);
    v = (r8.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    r5.i = fp.i + (4);
    if (!z && n == v)
    {
        r7.i = fp.i + (((uint32_t)r8.i << 2));
    }
    if (z || n != v)
    {
        goto L102;
    }
L109:
    counters[121] ++;
    tmp = fp.i - r5.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) fp.i) >= ((uint32_t) r5.i);
    v = (fp.i&0x80000000) != (r5.i&0x80000000) && (tmp&0x80000000) != (fp.i&0x80000000);
    if (!c)
    {
        ip.i = r5.i;
    }
    if (c)
    {
        goto L110;
    }
L111:
    counters[122] ++;
    load_counter ++;
    ldr(&r4.i, &ip.i, -4, 4, false, false, false);
    load_counter ++;
    ldr(&lr.i, &ip.i, -4, 4, false, true, false);
    r0.i = r4.i + (r6.i);
    load_counter ++;
    ldr(&r3.i, &r4.i, r6.i, 1, false, false, false);
    r1.i = lr.i + (r6.i);
    load_counter ++;
    ldr(&r2.i, &lr.i, r6.i, 1, false, false, false);
    tmp = r3.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r2.i);
    v = (r3.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L107;
    }
    counters[123] ++;
    goto L106;
L108:
    counters[124] ++;
    load_counter ++;
    ldr(&r3.i, &r0.i, 1, 1, true, false, false);
    load_counter ++;
    ldr(&r2.i, &r1.i, 1, 1, true, false, false);
    tmp = r3.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r2.i);
    v = (r3.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L106;
    }
L107:
    counters[125] ++;
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L108;
    }
L110:
    counters[126] ++;
    r5.i = r5.i + (4);
    tmp = r7.i - r5.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r7.i) >= ((uint32_t) r5.i);
    v = (r7.i&0x80000000) != (r5.i&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
    if (!z)
    {
        goto L109;
    }
L102:
    counters[127] ++;
    sp.i = sp.i + (36);
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
L106:
    counters[128] ++;
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (c)
    {
        goto L110;
    }
    counters[129] ++;
    tmp = ip.i - fp.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) fp.i);
    v = (ip.i&0x80000000) != (fp.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    store_counter ++;
    str(&r4.i, &ip.i, 4, 4, false, false, false);
    store_counter ++;
    str(&lr.i, &ip.i, 0, 4, false, true, false);
    if (c && !z)
    {
        goto L111;
    }
    counters[130] ++;
    r5.i = r5.i + (4);
    tmp = r7.i - r5.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r7.i) >= ((uint32_t) r5.i);
    v = (r7.i&0x80000000) != (r5.i&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
    if (!z)
    {
        goto L109;
    }
    counters[131] ++;
    goto L102;
L126:
    counters[132] ++;
    load_counter ++;
    if (z)
    {
        ldr(&r2.i, &r7.i, 0, 4, false, true, false);
    }
    store_counter ++;
    if (z)
    {
        str(&r0.i, &r7.i, 4, 4, false, true, false);
    }
    store_counter ++;
    if (z)
    {
        str(&r2.i, &lr.i, 0, 4, false, true, false);
    }
    r2.i = r3.i;
    goto L132;
L201:
    counters[133] ++;
    r8.i = 0;
    r3.i = r10.i + (4);
    r5.i = r4.i;
    r1.i = 4;
    store_counter ++;
    str(&r3.i, &sp.i, 20, 4, false, false, false);
    r4.i = r8.i;
    r3.i = fp.i + (r3.i);
    ip.i = r8.i;
    store_counter ++;
    str(&r3.i, &sp.i, 12, 4, false, false, false);
    r3.i = r8.i;
    store_counter ++;
    str(&r8.i, &sp.i, 8, 4, false, false, false);
    store_counter ++;
    str(&fp.i, &sp.i, 0, 4, false, true, false);
    store_counter ++;
    str(&r1.i, &sp.i, 4, 4, false, false, false);
    goto L133;
L156:
    counters[134] ++;
    tmp = r1.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r2.i);
    v = (r1.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    ip.i = r4.i;
    store_counter ++;
    str(&r0.i, &sp.i, 4, 4, false, false, false);
    store_counter ++;
    str(&fp.i, &sp.i, 0, 4, false, true, false);
    if (!z)
    {
        goto L205;
    }
L171:
    counters[135] ++;
    load_counter ++;
    tmp = sp.i;
    ldr(&ip.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    sp.i = tmp;
    goto L119;
L204:
    counters[136] ++;
    load_counter ++;
    ldr(&r2.i, &sp.i, 4, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &sp.i, 12, 4, false, false, false);
    load_counter ++;
    ldr(&r0.i, &sp.i, 0, 4, false, true, false);
    r1.i = r3.i + (r2.i);
    r2.i = r6.i + (1);
    r1.i = r1.i - (r5.i);
    r1.i = r1.i >> 2;
    r1.i = r1.i - (1);
    ssort2();
    counters[137] ++;
    goto L153;
L203:
    counters[138] ++;
    load_counter ++;
    ldr(&r1.i, &sp.i, 8, 4, false, false, false);
    r2.i = r6.i;
    r0.i = fp.i;
    ssort2();
    counters[139] ++;
    goto L146;
L173:
    counters[140] ++;
    lr.i = r9.i;
    ip.i = r3.i;
    goto L119;
L120:
    counters[141] ++;
    tmp = r5.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r2.i);
    v = (r5.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (n != v)
    {
        goto L173;
    }
    counters[142] ++;
    load_counter ++;
    ldr(&r3.i, &sp.i, 4, 4, false, false, false);
    tmp = r5.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r1.i);
    v = (r5.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (z || n != v)
    {
        r3.i = lr.i;
    }
    lr.i = r3.i;
    load_counter ++;
    ldr(&r3.i, &sp.i, 0, 4, false, true, false);
    if (z || n != v)
    {
        r3.i = ip.i;
    }
    ip.i = r3.i;
    goto L119;
L115:
    counters[143] ++;
    tmp = r5.i - r7.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r7.i);
    v = (r5.i&0x80000000) != (r7.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (!z && n == v)
    {
        goto L161;
    }
    counters[144] ++;
    tmp = r7.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r7.i) >= ((uint32_t) r1.i);
    v = (r7.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
    if (!z && n == v)
    {
        goto L160;
    }
L162:
    counters[145] ++;
    r1.i = r7.i;
    goto L114;
L117:
    counters[146] ++;
    tmp = lr.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) r2.i);
    v = (lr.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    if (n != v)
    {
        goto L116;
    }
    counters[147] ++;
    tmp = ip.i - lr.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) lr.i);
    v = (ip.i&0x80000000) != (lr.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (n != v)
    {
        goto L165;
    }
L166:
    counters[148] ++;
    load_counter ++;
    ldr(&r3.i, &sp.i, 20, 4, false, false, false);
    r2.i = lr.i;
    r9.i = r8.i;
    goto L116;
L193:
    counters[149] ++;
    load_counter ++;
    ldr(&ip.i, &sp.i, 12, 4, false, false, false);
L147:
    counters[150] ++;
    load_counter ++;
    ldr(&r1.i, &r2.i, 0, 4, false, true, false);
    load_counter ++;
    ldr(&r0.i, &r7.i, 0, 4, false, true, false);
    store_counter ++;
    str(&r0.i, &r2.i, 4, 4, false, true, false);
    store_counter ++;
    str(&r1.i, &r7.i, 4, 4, false, true, false);
    tmp = ip.i - r7.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r7.i);
    v = (ip.i&0x80000000) != (r7.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (!z)
    {
        goto L147;
    }
    counters[151] ++;
    goto L150;
L137:
    counters[152] ++;
    r0.i = fp.i + (r0.i);
    r1.i = fp.i;
L142:
    counters[153] ++;
    load_counter ++;
    ldr(&lr.i, &r7.i, 0, 4, false, true, false);
    load_counter ++;
    ldr(&ip.i, &r1.i, 0, 4, false, true, false);
    store_counter ++;
    str(&lr.i, &r1.i, 4, 4, false, true, false);
    tmp = r1.i - r0.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r0.i);
    v = (r1.i&0x80000000) != (r0.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    store_counter ++;
    str(&ip.i, &r7.i, 4, 4, false, true, false);
    if (!z)
    {
        goto L142;
    }
    counters[154] ++;
    goto L140;
L199:
    counters[155] ++;
    tmp = ip.i - lr.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) lr.i);
    v = (ip.i&0x80000000) != (lr.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (n != v)
    {
        goto L166;
    }
L165:
    counters[156] ++;
    r2.i = ip.i;
L195:
    counters[157] ++;
    load_counter ++;
    ldr(&r3.i, &sp.i, 12, 4, false, false, false);
    r9.i = r7.i;
    goto L116;
L198:
    counters[158] ++;
    tmp = r7.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r7.i) >= ((uint32_t) r1.i);
    v = (r7.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
    if (!z && n == v)
    {
        goto L162;
    }
L160:
    counters[159] ++;
    store_counter ++;
    str(&r0.i, &sp.i, 4, 4, false, false, false);
    store_counter ++;
    str(&fp.i, &sp.i, 0, 4, false, true, false);
    goto L114;
L118:
    counters[160] ++;
    tmp = r5.i - r7.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r7.i);
    v = (r5.i&0x80000000) != (r7.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (!z && n == v)
    {
        goto L170;
    }
    counters[161] ++;
    tmp = lr.i - r7.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) r7.i);
    v = (lr.i&0x80000000) != (r7.i&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    if (n == v)
    {
        ip.i = r4.i;
    }
    goto L113;
L200:
    counters[162] ++;
    tmp = lr.i - r7.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) r7.i);
    v = (lr.i&0x80000000) != (r7.i&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    if (n != v)
    {
        ip.i = r4.i;
    }
    goto L113;
L197:
    counters[163] ++;
    r4.i = r5.i - (r4.i);
L196:
    counters[164] ++;
    r3.i = r2.i - (r7.i);
    r1.i = r7.i - (fp.i);
    r8.i = r4.i >> 2;
    store_counter ++;
    str(&r1.i, &sp.i, 4, 4, false, false, false);
    r1.i = fp.i + (r3.i);
    store_counter ++;
    str(&r1.i, &sp.i, 0, 4, false, true, false);
    r1.i = r3.i >> 2;
    store_counter ++;
    str(&r1.i, &sp.i, 8, 4, false, false, false);
    goto L125;
L202:
    counters[165] ++;
    r4.i = r5.i - (r1.i);
    goto L196;
    return;
}

void ssort2main()
{
    counters[166] ++;
    r2.i = 0;
    ssort2();
    return;

}

void insert1()
{
    counters[167] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r6.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r4.i, &sp.i, 0, 4, false, false, false);
    r4.i = r0.i - (0);
    z = r4.i == 0;
    n = r4.i & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (r4.i&0x80000000) != (r0.i&0x80000000);
    r5.i = r1.i;
    if (z)
    {
        goto L217;
    }
    counters[168] ++;
    load_counter ++;
    ldr(&r2.i, &r1.i, 0, 1, false, true, false);
    load_counter ++;
    ldr(&r3.i, &r4.i, 0, 1, false, true, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!c)
    {
        goto L218;
    }
    counters[169] ++;
    if (z)
    {
        goto L219;
    }
    counters[170] ++;
    load_counter ++;
    ldr(&r0.i, &r4.i, 12, 4, false, false, false);
    r6.i = r4.i;
    insert1();
    counters[171] ++;
    store_counter ++;
    str(&r0.i, &r4.i, 12, 4, false, false, false);
L207:
    counters[172] ++;
    r0.i = r6.i;
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
L218:
    counters[173] ++;
    load_counter ++;
    ldr(&r0.i, &r4.i, 4, 4, false, false, false);
    r6.i = r4.i;
    insert1();
    counters[174] ++;
    store_counter ++;
    str(&r0.i, &r4.i, 4, 4, false, false, false);
    r0.i = r6.i;
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
L217:
    counters[175] ++;
    r0.i = 16;
    malloc_help();
    counters[176] ++;
    load_counter ++;
    ldr(&r3.i, &r5.i, 0, 1, false, true, false);
    r6.i = r0.i;
    store_counter ++;
    str(&r4.i, &r0.i, 12, 4, false, false, false);
    store_counter ++;
    str(&r4.i, &r0.i, 8, 4, false, false, false);
    store_counter ++;
    str(&r4.i, &r0.i, 4, 4, false, false, false);
    store_counter ++;
    str(&r3.i, &r0.i, 0, 1, false, true, false);
L209:
    counters[177] ++;
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L207;
    }
    counters[178] ++;
    load_counter ++;
    ldr(&r0.i, &r6.i, 8, 4, false, false, false);
    r1.i = r5.i + (1);
    insert1();
    counters[179] ++;
    store_counter ++;
    str(&r0.i, &r6.i, 8, 4, false, false, false);
    r0.i = r6.i;
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
L219:
    counters[180] ++;
    r6.i = r4.i;
    goto L209;
    return;
}

void cleanup1()
{
    counters[181] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r4.i, &sp.i, 0, 4, false, false, false);
    r4.i = r0.i - (0);
    z = r4.i == 0;
    n = r4.i & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (r4.i&0x80000000) != (r0.i&0x80000000);
    load_counter ++;
    if (z)
    {
        ldr(&r4.i, &sp.i, 0, 4, false, false, false);
        sp.i += 4;
        ldr(&pc.i, &sp.i, 0, 4, false, false, false);
        sp.i += 4;
        return;
    }
    load_counter ++;
    ldr(&r0.i, &r4.i, 4, 4, false, false, false);
    cleanup1();
    counters[182] ++;
    load_counter ++;
    ldr(&r0.i, &r4.i, 8, 4, false, false, false);
    cleanup1();
    counters[183] ++;
    load_counter ++;
    ldr(&r0.i, &r4.i, 12, 4, false, false, false);
    cleanup1();
    counters[184] ++;
    r0.i = r4.i;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    free_help();
    return;

}

void insert2()
{
    counters[185] ++;
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
    sp.i -= 4;
    str(&r3.i, &sp.i, 0, 4, false, false, false);
    r3.i = (root & 0xffff);
    r3.i = r3.i | (((uint32_t)root >> 16) << 16);
    r7.i = r0.i;
    r5.i = r0.i;
    load_counter ++;
    ldr(&r1.i, &r3.i, 0, 4, false, true, false);
    r6.i = r1.i + (4);
    ip.i = r1.i + (8);
    lr.i = r1.i;
    load_counter ++;
    ldr(&r0.i, &lr.i, 12, 1, false, true, false);
    goto L228;
L247:
    counters[186] ++;
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    r5.i = r5.i + (1);
    load_counter ++;
    if (z)
    {
        ldr(&r3.i, &sp.i, 0, 4, false, false, false);
        sp.i += 4;
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
    load_counter ++;
    ldr(&r3.i, &r4.i, 0, 4, false, true, false);
    tmp = r3.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r1.i);
    v = (r3.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L246;
    }
L228:
    counters[187] ++;
    load_counter ++;
    ldr(&r3.i, &r5.i, 0, 1, false, true, false);
    r4.i = ip.i;
    r2.i = r3.i - (r0.i);
    tmp = r2.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) 0);
    v = (r2.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (z)
    {
        goto L247;
    }
    counters[188] ++;
    r4.i = lr.i;
    if (n != v)
    {
        r4.i = r6.i;
    }
    load_counter ++;
    ldr(&r3.i, &r4.i, 0, 4, false, true, false);
    tmp = r3.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r1.i);
    v = (r3.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L228;
    }
L246:
    counters[189] ++;
    r9.i = (bufn & 0xffff);
    r9.i = r9.i | (((uint32_t)bufn >> 16) << 16);
    r8.i = (buffer & 0xffff);
    r10.i = (freen & 0xffff);
    fp.i = (freearr & 0xffff);
    load_counter ++;
    ldr(&r6.i, &r9.i, 0, 4, false, true, false);
    r8.i = r8.i | (((uint32_t)buffer >> 16) << 16);
    r10.i = r10.i | (((uint32_t)freen >> 16) << 16);
    fp.i = fp.i | (((uint32_t)freearr >> 16) << 16);
    goto L233;
L248:
    counters[190] ++;
    load_counter ++;
    ldr(&r0.i, &r8.i, 0, 4, false, true, false);
    r1.i = r0.i + (16);
    store_counter ++;
    str(&r1.i, &r8.i, 0, 4, false, true, false);
    store_counter ++;
    str(&r0.i, &r4.i, 0, 4, false, true, false);
    load_counter ++;
    ldr(&r1.i, &r5.i, 0, 1, false, true, false);
    store_counter ++;
    str(&r2.i, &r0.i, 12, 4, false, false, false);
    store_counter ++;
    str(&r2.i, &r0.i, 8, 4, false, false, false);
    store_counter ++;
    str(&r1.i, &r0.i, 0, 1, false, true, false);
    store_counter ++;
    str(&r2.i, &r0.i, 4, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &r5.i, 1, 1, false, true, false);
    tmp = r2.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) 0);
    v = (r2.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (z)
    {
        goto L230;
    }
L231:
    counters[191] ++;
    r4.i = r0.i + (8);
    r6.i = r3.i;
L233:
    counters[192] ++;
    r2.i = 0;
    tmp = r6.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) r2.i);
    v = (r6.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    r3.i = r6.i - (1);
    store_counter ++;
    str(&r3.i, &r9.i, 0, 4, false, true, false);
    if (!z)
    {
        goto L248;
    }
    counters[193] ++;
    r0.i = 16000;
    malloc_help();
    counters[194] ++;
    load_counter ++;
    ldr(&r3.i, &r10.i, 0, 4, false, true, false);
    r2.i = r0.i + (16);
    store_counter ++;
    str(&r0.i, &fp.i, ((uint32_t)r3.i << 2), 4, false, false, false);
    store_counter ++;
    str(&r2.i, &r8.i, 0, 4, false, true, false);
    r2.i = r3.i + (1);
    r3.i = 999;
    store_counter ++;
    str(&r2.i, &r10.i, 0, 4, false, true, false);
    store_counter ++;
    str(&r3.i, &r9.i, 0, 4, false, true, false);
    store_counter ++;
    str(&r0.i, &r4.i, 0, 4, false, true, false);
    load_counter ++;
    ldr(&r2.i, &r5.i, 0, 1, false, true, false);
    load_counter ++;
    ldr(&r1.i, &r5.i, 1, 1, false, true, false);
    store_counter ++;
    str(&r6.i, &r0.i, 12, 4, false, false, false);
    tmp = r1.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 0);
    v = (r1.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    store_counter ++;
    str(&r6.i, &r0.i, 8, 4, false, false, false);
    store_counter ++;
    str(&r6.i, &r0.i, 4, 4, false, false, false);
    store_counter ++;
    str(&r2.i, &r0.i, 0, 1, false, true, false);
    if (!z)
    {
        goto L231;
    }
L230:
    counters[195] ++;
    r3.i = (LC0 & 0xffff);
    r3.i = r3.i | (((uint32_t)LC0 >> 16) << 16);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, true, false);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    store_counter ++;
    if (!z)
    {
        str(&r7.i, &r0.i, 8, 4, false, false, false);
    }
    load_counter ++;
    ldr(&r3.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
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

void cleanup2()
{
    counters[196] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r6.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r4.i, &sp.i, 0, 4, false, false, false);
    r6.i = (freen & 0xffff);
    r6.i = r6.i | (((uint32_t)freen >> 16) << 16);
    load_counter ++;
    ldr(&r3.i, &r6.i, 0, 4, false, true, false);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    load_counter ++;
    if (z || n != v)
    {
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
    r5.i = (freearr & 0xffff);
    r5.i = r5.i | (((uint32_t)freearr >> 16) << 16);
    r4.i = 0;
L251:
    counters[197] ++;
    load_counter ++;
    ldr(&r0.i, &r5.i, 4, 4, false, true, false);
    r4.i = r4.i + (1);
    free_help();
    counters[198] ++;
    load_counter ++;
    ldr(&r3.i, &r6.i, 0, 4, false, true, false);
    tmp = r3.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r4.i);
    v = (r3.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z && n == v)
    {
        goto L251;
    }
    counters[199] ++;
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

void search1()
{
    counters[200] ++;
    r3.i = (root & 0xffff);
    r3.i = r3.i | (((uint32_t)root >> 16) << 16);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, true, false);
L263:
    counters[201] ++;
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L260;
    }
L264:
    counters[202] ++;
    load_counter ++;
    ldr(&r1.i, &r3.i, 0, 1, false, true, false);
    load_counter ++;
    ldr(&r2.i, &r0.i, 0, 1, false, true, false);
    tmp = r2.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r1.i);
    v = (r2.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    load_counter ++;
    if (!c)
    {
        ldr(&r3.i, &r3.i, 4, 4, false, false, false);
    }
    if (!c)
    {
        goto L263;
    }
    counters[203] ++;
    load_counter ++;
    if (!z)
    {
        ldr(&r3.i, &r3.i, 12, 4, false, false, false);
    }
    if (!z)
    {
        goto L263;
    }
    counters[204] ++;
    tmp = r2.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) 0);
    v = (r2.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    r0.i = r0.i + (1);
    if (z)
    {
        goto L261;
    }
    counters[205] ++;
    load_counter ++;
    ldr(&r3.i, &r3.i, 8, 4, false, false, false);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L264;
    }
L260:
    counters[206] ++;
    r0.i = r3.i;
    return;
L261:
    counters[207] ++;
    r0.i = 1;
    return;

}

void search2()
{
    counters[208] ++;
    r3.i = (root & 0xffff);
    r3.i = r3.i | (((uint32_t)root >> 16) << 16);
    load_counter ++;
    ldr(&r1.i, &r0.i, 0, 1, false, true, false);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, true, false);
L274:
    counters[209] ++;
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L271;
    }
L275:
    counters[210] ++;
    load_counter ++;
    ldr(&r2.i, &r3.i, 0, 1, false, true, false);
    r2.i = r1.i - (r2.i);
    tmp = r2.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) 0);
    v = (r2.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z)
    {
        goto L267;
    }
    counters[211] ++;
    tmp = r1.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 0);
    v = (r1.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (z)
    {
        goto L272;
    }
    counters[212] ++;
    load_counter ++;
    ldr(&r3.i, &r3.i, 8, 4, false, false, false);
    r0.i = r0.i + (1);
    load_counter ++;
    ldr(&r1.i, &r0.i, 0, 1, false, true, false);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L275;
    }
L271:
    counters[213] ++;
    r0.i = r3.i;
    return;
L267:
    counters[214] ++;
    load_counter ++;
    if (n != v)
    {
        ldr(&r3.i, &r3.i, 4, 4, false, false, false);
    }
    load_counter ++;
    if (n == v)
    {
        ldr(&r3.i, &r3.i, 12, 4, false, false, false);
    }
    goto L274;
L272:
    counters[215] ++;
    r0.i = 1;
    return;

}

void pmsearch()
{
    counters[216] ++;
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
    r4.i = r0.i - (0);
    z = r4.i == 0;
    n = r4.i & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (r4.i&0x80000000) != (r0.i&0x80000000);
    load_counter ++;
    if (z)
    {
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
        ldr(&pc.i, &sp.i, 0, 4, false, false, false);
        sp.i += 4;
        return;
    }
    r9.i = (nodecnt & 0xffff);
    r5.i = (srchtop & 0xffff);
    r6.i = (srcharr & 0xffff);
    r9.i = r9.i | (((uint32_t)nodecnt >> 16) << 16);
    r5.i = r5.i | (((uint32_t)srchtop >> 16) << 16);
    r7.i = r1.i + (1);
    r6.i = r6.i | (((uint32_t)srcharr >> 16) << 16);
    r8.i = r1.i;
    goto L277;
L278:
    counters[217] ++;
    load_counter ++;
    ldr(&r0.i, &r4.i, 4, 4, false, false, false);
    r1.i = r8.i;
    pmsearch();
    counters[218] ++;
    load_counter ++;
    ldr(&r3.i, &r8.i, 0, 1, false, true, false);
    tmp = r3.i - 46;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 46);
    v = (r3.i&0x80000000) != (46&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L308;
    }
    counters[219] ++;
    load_counter ++;
    ldr(&r3.i, &r4.i, 0, 1, false, true, false);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L289;
    }
L287:
    counters[220] ++;
    load_counter ++;
    ldr(&r4.i, &r4.i, 12, 4, false, false, false);
    tmp = r4.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 0);
    v = (r4.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    load_counter ++;
    if (z)
    {
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
        ldr(&pc.i, &sp.i, 0, 4, false, false, false);
        sp.i += 4;
        return;
    }
L277:
    counters[221] ++;
    load_counter ++;
    ldr(&r3.i, &r9.i, 0, 4, false, true, false);
    r3.i = r3.i + (1);
    store_counter ++;
    str(&r3.i, &r9.i, 0, 4, false, true, false);
    load_counter ++;
    ldr(&r3.i, &r8.i, 0, 1, false, true, false);
    tmp = r3.i - 46;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 46);
    v = (r3.i&0x80000000) != (46&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L278;
    }
    counters[222] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 0, 1, false, true, false);
    tmp = r3.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r2.i);
    v = (r3.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!c)
    {
        goto L278;
    }
    counters[223] ++;
    tmp = r3.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r2.i);
    v = (r3.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L309;
    }
L281:
    counters[224] ++;
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L288;
    }
    counters[225] ++;
    tmp = r2.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) 0);
    v = (r2.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    load_counter ++;
    if (!z)
    {
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
        ldr(&pc.i, &sp.i, 0, 4, false, false, false);
        sp.i += 4;
        return;
    }
L310:
    counters[226] ++;
    load_counter ++;
    ldr(&r3.i, &r5.i, 0, 4, false, true, false);
    load_counter ++;
    ldr(&r2.i, &r4.i, 8, 4, false, false, false);
    r1.i = r3.i + (1);
    store_counter ++;
    str(&r1.i, &r5.i, 0, 4, false, true, false);
    store_counter ++;
    str(&r2.i, &r6.i, ((uint32_t)r3.i << 2), 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &r8.i, 0, 1, false, true, false);
L283:
    counters[227] ++;
    tmp = r3.i - 46;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 46);
    v = (r3.i&0x80000000) != (46&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    load_counter ++;
    if (!z)
    {
        ldr(&r2.i, &r4.i, 0, 1, false, true, false);
    }
    if (z)
    {
        goto L287;
    }
L288:
    counters[228] ++;
    tmp = r3.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r2.i);
    v = (r3.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (c && !z)
    {
        goto L287;
    }
    counters[229] ++;
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
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;
L308:
    counters[230] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 0, 1, false, true, false);
    tmp = r3.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r2.i);
    v = (r3.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L281;
    }
L309:
    counters[231] ++;
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L289;
    }
L304:
    counters[232] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 0, 1, false, true, false);
    tmp = r2.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) 0);
    v = (r2.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (z)
    {
        goto L310;
    }
    counters[233] ++;
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
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;
L289:
    counters[234] ++;
    load_counter ++;
    ldr(&r0.i, &r4.i, 8, 4, false, false, false);
    r1.i = r7.i;
    pmsearch();
    counters[235] ++;
    load_counter ++;
    ldr(&r3.i, &r8.i, 0, 1, false, true, false);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L304;
    }
    counters[236] ++;
    goto L283;
    return;
}

void nearsearch()
{
    counters[237] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        r3.i = (uint32_t)r2.i >> 31;
    }
    if (z)
    {
        r3.i = 1;
    }
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        return;
    }
    counters[238] ++;
    tmp = r2.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) 0);
    v = (r2.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
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
    r7.i = (nodecnt & 0xffff);
    r8.i = (srchtop & 0xffff);
    r9.i = (srcharr & 0xffff);
    r7.i = r7.i | (((uint32_t)nodecnt >> 16) << 16);
    r8.i = r8.i | (((uint32_t)srchtop >> 16) << 16);
    if (!z)
    {
        r10.i = r2.i - (1);
    }
    if (!z)
    {
        r9.i = r9.i | (((uint32_t)srcharr >> 16) << 16);
    }
    r6.i = r2.i;
    r5.i = r1.i;
    r4.i = r0.i;
    if (!z)
    {
        goto L313;
    }
    counters[239] ++;
    r9.i = r9.i | (((uint32_t)srcharr >> 16) << 16);
    goto L322;
L340:
    counters[240] ++;
    load_counter ++;
    ldr(&r3.i, &r5.i, 0, 1, false, true, false);
    load_counter ++;
    ldr(&r0.i, &r4.i, 8, 4, false, false, false);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        r1.i = r5.i;
    }
    if (z)
    {
        goto L317;
    }
    counters[241] ++;
    tmp = r6.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) r3.i);
    v = (r6.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    r1.i = r5.i + (1);
    if (z)
    {
        r2.i = 0;
    }
    if (!z)
    {
        goto L317;
    }
L319:
    counters[242] ++;
    nearsearch();
    counters[243] ++;
    load_counter ++;
    ldr(&r6.i, &r4.i, 0, 1, false, true, false);
L318:
    counters[244] ++;
    load_counter ++;
    ldr(&r3.i, &r5.i, 0, 1, false, true, false);
    tmp = r3.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r6.i);
    v = (r3.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    load_counter ++;
    if (!c || z)
    {
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
        ldr(&pc.i, &sp.i, 0, 4, false, false, false);
        sp.i += 4;
        return;
    }
    load_counter ++;
    ldr(&r4.i, &r4.i, 12, 4, false, false, false);
    tmp = r4.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 0);
    v = (r4.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    load_counter ++;
    if (z)
    {
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
        ldr(&pc.i, &sp.i, 0, 4, false, false, false);
        sp.i += 4;
        return;
    }
L322:
    counters[245] ++;
    load_counter ++;
    ldr(&r3.i, &r7.i, 0, 4, false, true, false);
    r3.i = r3.i + (1);
    store_counter ++;
    str(&r3.i, &r7.i, 0, 4, false, true, false);
    load_counter ++;
    ldr(&r6.i, &r4.i, 0, 1, false, true, false);
    load_counter ++;
    ldr(&r3.i, &r5.i, 0, 1, false, true, false);
    tmp = r3.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r6.i);
    v = (r3.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (c)
    {
        goto L314;
    }
    counters[246] ++;
    load_counter ++;
    ldr(&r0.i, &r4.i, 4, 4, false, false, false);
    r2.i = 0;
    r1.i = r5.i;
    nearsearch();
    counters[247] ++;
    load_counter ++;
    ldr(&r6.i, &r4.i, 0, 1, false, true, false);
L314:
    counters[248] ++;
    tmp = r6.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) 0);
    v = (r6.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    if (!z)
    {
        goto L340;
    }
    counters[249] ++;
    r0.i = r5.i;
    strlen_help();
    counters[250] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        goto L318;
    }
    counters[251] ++;
    load_counter ++;
    ldr(&r3.i, &r8.i, 0, 4, false, true, false);
    load_counter ++;
    ldr(&r2.i, &r4.i, 8, 4, false, false, false);
    r1.i = r3.i + (1);
    store_counter ++;
    str(&r1.i, &r8.i, 0, 4, false, true, false);
    store_counter ++;
    str(&r2.i, &r9.i, ((uint32_t)r3.i << 2), 4, false, false, false);
    load_counter ++;
    ldr(&r6.i, &r4.i, 0, 1, false, true, false);
    goto L318;
L323:
    counters[252] ++;
    load_counter ++;
    ldr(&r2.i, &r5.i, 0, 1, false, true, false);
    load_counter ++;
    ldr(&r0.i, &r4.i, 8, 4, false, false, false);
    tmp = r2.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) 0);
    v = (r2.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z)
    {
        goto L341;
    }
    counters[253] ++;
    r1.i = r5.i;
L325:
    counters[254] ++;
    r2.i = r10.i;
L326:
    counters[255] ++;
    nearsearch();
L324:
    counters[256] ++;
    load_counter ++;
    ldr(&r4.i, &r4.i, 12, 4, false, false, false);
    tmp = r4.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 0);
    v = (r4.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    load_counter ++;
    if (z)
    {
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
        ldr(&pc.i, &sp.i, 0, 4, false, false, false);
        sp.i += 4;
        return;
    }
L313:
    counters[257] ++;
    load_counter ++;
    ldr(&r3.i, &r7.i, 0, 4, false, true, false);
    r2.i = r6.i;
    load_counter ++;
    ldr(&r0.i, &r4.i, 4, 4, false, false, false);
    r1.i = r5.i;
    r3.i = r3.i + (1);
    store_counter ++;
    str(&r3.i, &r7.i, 0, 4, false, true, false);
    nearsearch();
    counters[258] ++;
    load_counter ++;
    ldr(&r3.i, &r4.i, 0, 1, false, true, false);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L323;
    }
    counters[259] ++;
    r0.i = r5.i;
    strlen_help();
    counters[260] ++;
    tmp = r0.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) r6.i);
    v = (r0.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z && n == v)
    {
        goto L324;
    }
    counters[261] ++;
    load_counter ++;
    ldr(&r3.i, &r8.i, 0, 4, false, true, false);
    load_counter ++;
    ldr(&r2.i, &r4.i, 8, 4, false, false, false);
    r1.i = r3.i + (1);
    store_counter ++;
    str(&r1.i, &r8.i, 0, 4, false, true, false);
    store_counter ++;
    str(&r2.i, &r9.i, ((uint32_t)r3.i << 2), 4, false, false, false);
    goto L324;
L317:
    counters[262] ++;
    r2.i = ~0;
    goto L319;
L341:
    counters[263] ++;
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    r1.i = r5.i + (1);
    if (z)
    {
        r2.i = r6.i;
    }
    if (z)
    {
        goto L326;
    }
    counters[264] ++;
    goto L325;
    return;
}

void main()
{
    malloc_start();
    counters[265] ++;
    r2.i = (LC1 & 0xffff);
    r2.i = r2.i | (((uint32_t)LC1 >> 16) << 16);
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r6.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r4.i, &sp.i, 0, 4, false, false, false);
    sp.i = sp.i - (16);
    load_counter ++;
    tmp = r2.i;
    ldr(&r0.i, &r2.i, 0, 4, false, false, false);
    r2.i += 4;
    ldr(&r1.i, &r2.i, 0, 4, false, false, false);
    r2.i += 4;
    ldr(&r2.i, &r2.i, 0, 4, false, false, false);
    r2.i += 4;
    r2.i = tmp;
    r3.i = sp.i + (4);
    r5.i = (LC5 & 0xffff);
    r6.i = sp.i + (16);
    r5.i = r5.i | (((uint32_t)LC5 >> 16) << 16);
    r4.i = r3.i;
    store_counter ++;
    tmp = r3.i;
    str(&r0.i, &r3.i, 0, 4, false, false, false);
    r3.i += 4;
    str(&r1.i, &r3.i, 0, 4, false, false, false);
    r3.i += 4;
    str(&r2.i, &r3.i, 0, 4, false, false, false);
    r3.i += 4;
    r3.i = tmp;
    r0.i = r3.i;
    r2.i = 0;
    r1.i = 3;
    ssort1();
L343:
    counters[266] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 4, 4, false, true, false);
    r1.i = r5.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[267] ++;
    tmp = r4.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r6.i);
    v = (r4.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        goto L343;
    }
    counters[268] ++;
    r0.i = 0;
    sp.i = sp.i + (16);
    load_counter ++;
    ldr(&r4.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&r6.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    counter_summary();
    return;

}

