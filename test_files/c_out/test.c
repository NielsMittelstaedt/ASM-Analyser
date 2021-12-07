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

reg r1, r0, r3, r2;

int32_t LC1, LC2, LC3, LC0;

int counters[93] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[93] = {12,3,6,6,2,5,7,3,4,4,11,6,6,2,5,7,3,4,4,8,2,3,4,2,4,5,4,3,1,6,9,2,4,4,5,3,5,5,4,2,3,4,1,3,32,20,12,2,4,12,2,4,5,4,3,10,4,3,3,3,8,8,3,5,4,7,14,3,4,3,14,3,5,12,8,4,9,8,3,3,4,16,19,21,3,5,8,3,4,1,4,4,4};

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
    malloc_0 = (uint8_t*) malloc(20108);
    sp.i = 19996;
    fp = sp;
    LC1 = 20000;
    strcpy(malloc_0+LC1, "%d is prime\012\000");

    LC2 = 20021;
    strcpy(malloc_0+LC2, "%d is not prime\012\000");

    LC3 = 20046;
    strcpy(malloc_0+LC3, "Ergebnis: %d\012\000");

    LC0 = 20068;
    int32_t arrayLC0[] = {1,34,6,2,6,2,7,2,17,7};
    for(int i=0; i<10; i++) str(&arrayLC0[i], &LC0, i*4, 4, false, false, false);

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

void mulmod();
void modulo();
void Miller();
void swap();
void heapify();
void heapSort();
void test();
void main();

void rand_help()
{
    r0.i = rand();
}
void idiv()
{
    r0.i = r0.i / r1.i;
}
void smull(int32_t *dest_lo, int32_t *dest_hi, int32_t *op1, int32_t *op2)
{
    uint64_t res = (uint64_t) (*op1) * (*op2);
    *dest_lo = (uint32_t) res;
    *dest_hi = (uint32_t) (res >> 32);
}
void printf_help(const char *format, int32_t test)
{
    if (strstr(format, "%s") != NULL)
        printf(format, malloc_0 + test);
    else
        printf(format, test);
}
void idivmod()
{
    int32_t quot = r0.i / r1.i;
    int32_t rem = r0.i % r1.i;
    r0.i = quot;
    r1.i = rem;
}

void mulmod()
{
    counters[0] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&fp.i, &sp.i, 0, 4, false, false, false);
    fp.i = sp.i + (4);
    sp.i = sp.i - (24);
    store_counter ++;
    str(&r0.i, &fp.i, -16, 4, false, false, false);
    store_counter ++;
    str(&r1.i, &fp.i, -20, 4, false, false, false);
    store_counter ++;
    str(&r2.i, &fp.i, -24, 4, false, false, false);
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false, false);
    load_counter ++;
    ldr(&r1.i, &fp.i, -24, 4, false, false, false);
    r0.i = r3.i;
    idivmod();
    counters[1] ++;
    r3.i = r1.i;
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false, false);
    goto L2;
L4:
    counters[2] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false, false);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    r3.i = r3.i & 1;
    if (n != v)
    {
        r3.i = 0 - r3.i;
    }
    tmp = r3.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 1);
    v = (r3.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L3;
    }
    counters[3] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -8, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false, false);
    r3.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r1.i, &fp.i, -24, 4, false, false, false);
    r0.i = r3.i;
    idivmod();
    counters[4] ++;
    r3.i = r1.i;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
L3:
    counters[5] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 1;
    load_counter ++;
    ldr(&r1.i, &fp.i, -24, 4, false, false, false);
    r0.i = r3.i;
    idivmod();
    counters[6] ++;
    r3.i = r1.i;
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false, false);
    r2.i = (uint32_t)r3.i >> 31;
    r3.i = r2.i + (r3.i);
    r3.i = r3.i >> 1;
    store_counter ++;
    str(&r3.i, &fp.i, -20, 4, false, false, false);
L2:
    counters[7] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false, false);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z && n == v)
    {
        goto L4;
    }
    counters[8] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    load_counter ++;
    ldr(&r1.i, &fp.i, -24, 4, false, false, false);
    r0.i = r3.i;
    idivmod();
    counters[9] ++;
    r3.i = r1.i;
    r0.i = r3.i;
    sp.i = fp.i - (4);
    load_counter ++;
    ldr(&fp.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;

}

void modulo()
{
    counters[10] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&fp.i, &sp.i, 0, 4, false, false, false);
    fp.i = sp.i + (4);
    sp.i = sp.i - (24);
    store_counter ++;
    str(&r0.i, &fp.i, -16, 4, false, false, false);
    store_counter ++;
    str(&r1.i, &fp.i, -20, 4, false, false, false);
    store_counter ++;
    str(&r2.i, &fp.i, -24, 4, false, false, false);
    r3.i = 1;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false, false);
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false, false);
    goto L7;
L9:
    counters[11] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false, false);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    r3.i = r3.i & 1;
    if (n != v)
    {
        r3.i = 0 - r3.i;
    }
    tmp = r3.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 1);
    v = (r3.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L8;
    }
    counters[12] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -12, 4, false, false, false);
    r3.i = (r2.i) * (r3.i);
    load_counter ++;
    ldr(&r1.i, &fp.i, -24, 4, false, false, false);
    r0.i = r3.i;
    idivmod();
    counters[13] ++;
    r3.i = r1.i;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
L8:
    counters[14] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false, false);
    r3.i = (r3.i) * (r3.i);
    load_counter ++;
    ldr(&r1.i, &fp.i, -24, 4, false, false, false);
    r0.i = r3.i;
    idivmod();
    counters[15] ++;
    r3.i = r1.i;
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false, false);
    r2.i = (uint32_t)r3.i >> 31;
    r3.i = r2.i + (r3.i);
    r3.i = r3.i >> 1;
    store_counter ++;
    str(&r3.i, &fp.i, -20, 4, false, false, false);
L7:
    counters[16] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false, false);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z && n == v)
    {
        goto L9;
    }
    counters[17] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    load_counter ++;
    ldr(&r1.i, &fp.i, -24, 4, false, false, false);
    r0.i = r3.i;
    idivmod();
    counters[18] ++;
    r3.i = r1.i;
    r0.i = r3.i;
    sp.i = fp.i - (4);
    load_counter ++;
    ldr(&fp.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;

}

void Miller()
{
    counters[19] ++;
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
    load_counter ++;
    ldr(&r3.i, &fp.i, -32, 4, false, false, false);
    tmp = r3.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 1);
    v = (r3.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z && n == v)
    {
        goto L12;
    }
    counters[20] ++;
    r3.i = 0;
    goto L13;
L12:
    counters[21] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -32, 4, false, false, false);
    tmp = r3.i - 2;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 2);
    v = (r3.i&0x80000000) != (2&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L14;
    }
    counters[22] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -32, 4, false, false, false);
    r3.i = r3.i & 1;
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
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
    ldr(&r3.i, &fp.i, -32, 4, false, false, false);
    r3.i = r3.i - (1);
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false, false);
    goto L15;
L16:
    counters[25] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false, false);
    r2.i = (uint32_t)r3.i >> 31;
    r3.i = r2.i + (r3.i);
    r3.i = r3.i >> 1;
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false, false);
L15:
    counters[26] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false, false);
    r3.i = r3.i & 1;
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L16;
    }
    counters[27] ++;
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
    goto L17;
L22:
    counters[28] ++;
    rand_help();
    counters[29] ++;
    r2.i = r0.i;
    load_counter ++;
    ldr(&r3.i, &fp.i, -32, 4, false, false, false);
    r3.i = r3.i - (1);
    r1.i = r3.i;
    r0.i = r2.i;
    idivmod();
    counters[30] ++;
    r3.i = r1.i;
    r3.i = r3.i + (1);
    store_counter ++;
    str(&r3.i, &fp.i, -24, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false, false);
    store_counter ++;
    str(&r3.i, &fp.i, -16, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -32, 4, false, false, false);
    load_counter ++;
    ldr(&r1.i, &fp.i, -16, 4, false, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, -24, 4, false, false, false);
    modulo();
    counters[31] ++;
    store_counter ++;
    str(&r0.i, &fp.i, -20, 4, false, false, false);
    goto L18;
L20:
    counters[32] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -32, 4, false, false, false);
    load_counter ++;
    ldr(&r1.i, &fp.i, -20, 4, false, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, -20, 4, false, false, false);
    mulmod();
    counters[33] ++;
    store_counter ++;
    str(&r0.i, &fp.i, -20, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 1;
    store_counter ++;
    str(&r3.i, &fp.i, -16, 4, false, false, false);
L18:
    counters[34] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -32, 4, false, false, false);
    r3.i = r3.i - (1);
    load_counter ++;
    ldr(&r2.i, &fp.i, -16, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (z)
    {
        goto L19;
    }
    counters[35] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false, false);
    tmp = r3.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 1);
    v = (r3.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L19;
    }
    counters[36] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -32, 4, false, false, false);
    r3.i = r3.i - (1);
    load_counter ++;
    ldr(&r2.i, &fp.i, -20, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z)
    {
        goto L20;
    }
L19:
    counters[37] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -32, 4, false, false, false);
    r3.i = r3.i - (1);
    load_counter ++;
    ldr(&r2.i, &fp.i, -20, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (z)
    {
        goto L21;
    }
    counters[38] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false, false);
    r3.i = r3.i & 1;
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
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
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = r3.i + (1);
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
L17:
    counters[41] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -8, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -36, 4, false, false, false);
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
    sp.i = fp.i - (4);
    load_counter ++;
    ldr(&fp.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;

}

void swap()
{
    counters[44] ++;
    store_counter ++;
    str(&fp.i, &sp.i, -4, 4, true, false, false);
    fp.i = sp.i + (0);
    sp.i = sp.i - (28);
    store_counter ++;
    str(&r0.i, &fp.i, -16, 4, false, false, false);
    store_counter ++;
    str(&r1.i, &fp.i, -20, 4, false, false, false);
    store_counter ++;
    str(&r2.i, &fp.i, -24, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -16, 4, false, false, false);
    r3.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, false, false);
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -24, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -16, 4, false, false, false);
    r2.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r1.i, &fp.i, -16, 4, false, false, false);
    r3.i = r1.i + (r3.i);
    load_counter ++;
    ldr(&r2.i, &r2.i, 0, 4, false, false, false);
    store_counter ++;
    str(&r2.i, &r3.i, 0, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -24, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -16, 4, false, false, false);
    r3.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r2.i, &fp.i, -8, 4, false, false, false);
    store_counter ++;
    str(&r2.i, &r3.i, 0, 4, false, false, false);
    sp.i = fp.i + (0);
    load_counter ++;
    ldr(&fp.i, &sp.i, 4, 4, false, true, false);
    return;

}

void heapify()
{
    counters[45] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&fp.i, &sp.i, 0, 4, false, false, false);
    fp.i = sp.i + (4);
    sp.i = sp.i - (32);
    store_counter ++;
    str(&r0.i, &fp.i, -24, 4, false, false, false);
    store_counter ++;
    str(&r1.i, &fp.i, -28, 4, false, false, false);
    store_counter ++;
    str(&r2.i, &fp.i, -32, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -32, 4, false, false, false);
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -32, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 1;
    r3.i = r3.i + (1);
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -32, 4, false, false, false);
    r3.i = r3.i + (1);
    r3.i = (uint32_t)r3.i << 1;
    store_counter ++;
    str(&r3.i, &fp.i, -16, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -28, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!c || z)
    {
        goto L25;
    }
    counters[46] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -24, 4, false, false, false);
    r3.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r2.i, &r3.i, 0, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r1.i, &fp.i, -24, 4, false, false, false);
    r3.i = r1.i + (r3.i);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (c)
    {
        goto L25;
    }
    counters[47] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false, false);
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
L25:
    counters[48] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -28, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!c || z)
    {
        goto L26;
    }
    counters[49] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -24, 4, false, false, false);
    r3.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r2.i, &r3.i, 0, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r1.i, &fp.i, -24, 4, false, false, false);
    r3.i = r1.i + (r3.i);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (c)
    {
        goto L26;
    }
    counters[50] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false, false);
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
L26:
    counters[51] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -8, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -32, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (z)
    {
        goto L28;
    }
    counters[52] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -32, 4, false, false, false);
    r1.i = r3.i;
    load_counter ++;
    ldr(&r0.i, &fp.i, -24, 4, false, false, false);
    swap();
    counters[53] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -8, 4, false, false, false);
    load_counter ++;
    ldr(&r1.i, &fp.i, -28, 4, false, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, -24, 4, false, false, false);
    heapify();
L28:
    counters[54] ++;
    sp.i = fp.i - (4);
    load_counter ++;
    ldr(&fp.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;

}

void heapSort()
{
    counters[55] ++;
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
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false, false);
    r3.i = (uint32_t)r3.i >> 1;
    r3.i = r3.i - (1);
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
    goto L30;
L31:
    counters[56] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -8, 4, false, false, false);
    load_counter ++;
    ldr(&r1.i, &fp.i, -20, 4, false, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, -16, 4, false, false, false);
    heapify();
    counters[57] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = r3.i - (1);
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
L30:
    counters[58] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (n == v)
    {
        goto L31;
    }
    counters[59] ++;
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false, false);
    goto L32;
L33:
    counters[60] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -20, 4, false, false, false);
    r3.i = r2.i - (r3.i);
    r3.i = r3.i - (1);
    r2.i = r3.i;
    r1.i = 0;
    load_counter ++;
    ldr(&r0.i, &fp.i, -16, 4, false, false, false);
    swap();
    counters[61] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -20, 4, false, false, false);
    r3.i = r2.i - (r3.i);
    r3.i = r3.i - (1);
    r2.i = 0;
    r1.i = r3.i;
    load_counter ++;
    ldr(&r0.i, &fp.i, -16, 4, false, false, false);
    heapify();
    counters[62] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false, false);
    r3.i = r3.i + (1);
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false, false);
L32:
    counters[63] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false, false);
    r2.i = r3.i - (1);
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (c && !z)
    {
        goto L33;
    }
    counters[64] ++;
    sp.i = fp.i - (4);
    load_counter ++;
    ldr(&fp.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;

}

void test()
{
    counters[65] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&fp.i, &sp.i, 0, 4, false, false, false);
    fp.i = sp.i + (4);
    sp.i = sp.i - (64);
    store_counter ++;
    str(&r0.i, &fp.i, -64, 4, false, false, false);
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
    goto L35;
L36:
    counters[66] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -64, 4, false, false, false);
    r3.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, false, false);
    r2.i = r3.i;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    r1.i = fp.i - (4);
    r3.i = r1.i + (r3.i);
    store_counter ++;
    str(&r2.i, &r3.i, -56, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = r3.i + (1);
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
L35:
    counters[67] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    tmp = r3.i - 9;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 9);
    v = (r3.i&0x80000000) != (9&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L36;
    }
    counters[68] ++;
    r3.i = fp.i - (60);
    r1.i = 10;
    r0.i = r3.i;
    heapSort();
    counters[69] ++;
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false, false);
    goto L37;
L38:
    counters[70] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    r2.i = fp.i - (4);
    r3.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r1.i, &r3.i, -56, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -64, 4, false, false, false);
    r3.i = r2.i + (r3.i);
    r2.i = r1.i;
    store_counter ++;
    str(&r2.i, &r3.i, 0, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false, false);
    r3.i = r3.i + (1);
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false, false);
L37:
    counters[71] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false, false);
    tmp = r3.i - 9;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 9);
    v = (r3.i&0x80000000) != (9&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L38;
    }
    counters[72] ++;
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -16, 4, false, false, false);
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -20, 4, false, false, false);
    goto L39;
L43:
    counters[73] ++;
    load_counter ++;
    ldr(&r1.i, &fp.i, -20, 4, false, false, false);
    r3.i = 21846;
    r3.i = r3.i | (21845 << 16);
    smull(&r3.i, &r2.i, &r3.i, &r1.i);
    r3.i = r1.i >> 31;
    r2.i = r2.i - (r3.i);
    r3.i = r2.i;
    r3.i = (uint32_t)r3.i << 1;
    r3.i = r3.i + (r2.i);
    r2.i = r1.i - (r3.i);
    tmp = r2.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) 0);
    v = (r2.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (z)
    {
        goto L40;
    }
    counters[74] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -64, 4, false, false, false);
    r3.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r2.i, &r3.i, 0, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false, false);
    r3.i = (r2.i) * (r3.i);
    store_counter ++;
    str(&r3.i, &fp.i, -16, 4, false, false, false);
L40:
    counters[75] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false, false);
    r3.i = r3.i & 1;
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L41;
    }
    counters[76] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -64, 4, false, false, false);
    r3.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -16, 4, false, false, false);
    r3.i = r2.i + (r3.i);
    store_counter ++;
    str(&r3.i, &fp.i, -16, 4, false, false, false);
    goto L42;
L41:
    counters[77] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -64, 4, false, false, false);
    r3.i = r2.i + (r3.i);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -16, 4, false, false, false);
    r3.i = r2.i - (r3.i);
    store_counter ++;
    str(&r3.i, &fp.i, -16, 4, false, false, false);
L42:
    counters[78] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false, false);
    r3.i = r3.i + (1);
    store_counter ++;
    str(&r3.i, &fp.i, -20, 4, false, false, false);
L39:
    counters[79] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false, false);
    tmp = r3.i - 9;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 9);
    v = (r3.i&0x80000000) != (9&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L43;
    }
    counters[80] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false, false);
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
    counters[81] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&fp.i, &sp.i, 0, 4, false, false, false);
    fp.i = sp.i + (4);
    sp.i = sp.i - (56);
    r3.i = (LC0 & 0xffff);
    r3.i = r3.i | (((uint32_t)LC0 >> 16) << 16);
    ip.i = fp.i - (56);
    lr.i = r3.i;
    load_counter ++;
    ldr(&r0.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    ldr(&r1.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    ldr(&r2.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    ldr(&r3.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    store_counter ++;
    str(&r0.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    str(&r1.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    str(&r2.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    str(&r3.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    load_counter ++;
    ldr(&r0.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    ldr(&r1.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    ldr(&r2.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    ldr(&r3.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    store_counter ++;
    str(&r0.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    str(&r1.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    str(&r2.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    str(&r3.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    load_counter ++;
    tmp = lr.i;
    ldr(&r0.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    ldr(&r1.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    lr.i = tmp;
    store_counter ++;
    tmp = ip.i;
    str(&r0.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    str(&r1.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    ip.i = tmp;
    r3.i = fp.i - (56);
    r0.i = r3.i;
    test();
    counters[82] ++;
    store_counter ++;
    str(&r0.i, &fp.i, -16, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false, false);
    r3.i = (r3.i) * (r3.i);
    load_counter ++;
    ldr(&r2.i, &fp.i, -16, 4, false, false, false);
    r3.i = (r2.i) * (r3.i);
    load_counter ++;
    ldr(&r2.i, &fp.i, -16, 4, false, false, false);
    r3.i = (r2.i) * (r3.i);
    load_counter ++;
    ldr(&r2.i, &fp.i, -16, 4, false, false, false);
    r3.i = (r2.i) * (r3.i);
    load_counter ++;
    ldr(&r2.i, &fp.i, -16, 4, false, false, false);
    r2.i = (r2.i) * (r3.i);
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false, false);
    r3.i = (r2.i) * (r3.i);
    store_counter ++;
    str(&r3.i, &fp.i, -16, 4, false, false, false);
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false, false);
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false, false);
    goto L46;
L47:
    counters[83] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -12, 4, false, false, false);
    r3.i = 26215;
    r3.i = r3.i | (26214 << 16);
    smull(&r1.i, &r3.i, &r3.i, &r2.i);
    r1.i = r3.i >> 2;
    r3.i = r2.i >> 31;
    r3.i = r1.i - (r3.i);
    r1.i = 10;
    r3.i = (r1.i) * (r3.i);
    r3.i = r2.i - (r3.i);
    load_counter ++;
    ldr(&r2.i, &fp.i, -8, 4, false, false, false);
    r3.i = r2.i + (r3.i);
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -12, 4, false, false, false);
    r3.i = 26215;
    r3.i = r3.i | (26214 << 16);
    smull(&r1.i, &r3.i, &r3.i, &r2.i);
    r1.i = r3.i >> 2;
    r3.i = r2.i >> 31;
    r3.i = r1.i - (r3.i);
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false, false);
L46:
    counters[84] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false, false);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L47;
    }
    counters[85] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = (r3.i) * (r3.i);
    r1.i = r3.i;
    load_counter ++;
    ldr(&r0.i, &fp.i, -16, 4, false, false, false);
    idiv();
    counters[86] ++;
    r3.i = r0.i;
    store_counter ++;
    str(&r3.i, &fp.i, -16, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false, false);
    r3.i = r3.i - (1);
    store_counter ++;
    str(&r3.i, &fp.i, -16, 4, false, false, false);
    r1.i = 10;
    load_counter ++;
    ldr(&r0.i, &fp.i, -16, 4, false, false, false);
    Miller();
    counters[87] ++;
    r3.i = r0.i;
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L48;
    }
    counters[88] ++;
    load_counter ++;
    ldr(&r1.i, &fp.i, -16, 4, false, false, false);
    r0.i = (LC1 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC1 >> 16) << 16);
    printf_help(malloc_0+r0.i, r1.i);
    counters[89] ++;
    goto L49;
L48:
    counters[90] ++;
    load_counter ++;
    ldr(&r1.i, &fp.i, -16, 4, false, false, false);
    r0.i = (LC2 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC2 >> 16) << 16);
    printf_help(malloc_0+r0.i, r1.i);
L49:
    counters[91] ++;
    load_counter ++;
    ldr(&r1.i, &fp.i, -16, 4, false, false, false);
    r0.i = (LC3 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC3 >> 16) << 16);
    printf_help(malloc_0+r0.i, r1.i);
    counters[92] ++;
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

