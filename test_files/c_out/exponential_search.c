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

reg r3, r0, r2, r4, r1, r5, r6, r8, r9;

int32_t LC3, LC4, LC5, LC6, LC7, LC8, LC9, LC10, LC0, __PRETTY_FUNCTION__4935, LC2;

int counters[59] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[59] = {2,3,3,10,1,5,1,7,2,7,1,2,2,2,2,3,3,10,1,5,1,7,2,7,1,2,2,6,1,5,1,7,2,7,1,2,2,11,2,5,2,7,2,5,2,10,2,10,2,10,2,3,7,7,7,7,7,7,7};

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
    malloc_0 = (uint8_t*) malloc(20419);
    sp.i = 19996;
    fp = sp;
    LC3 = 20000;
    strcpy(malloc_0+LC3, "../test_files/c_in/exponential_search.c\000");

    LC4 = 20045;
    strcpy(malloc_0+LC4, "exponential_search(arr_found, 3, 10) == -1\000");

    LC5 = 20093;
    strcpy(malloc_0+LC5, "exponential_search(arr_found, 1, 1) == 0\000");

    LC6 = 20139;
    strcpy(malloc_0+LC6, "exponential_search(arr_first_2, 2, 1) == 0\000");

    LC7 = 20187;
    strcpy(malloc_0+LC7, "exponential_search(arr_last_2, 2, 2) == 1\000");

    LC8 = 20234;
    strcpy(malloc_0+LC8, "exponential_search(arr_first_n, 5, -1) == 0\000");

    LC9 = 20283;
    strcpy(malloc_0+LC9, "exponential_search(arr_last_n, 5, 8) == 4\000");

    LC10 = 20330;
    strcpy(malloc_0+LC10, "exponential_search(arr_middle, 5, 6) == 3\000");

    LC0 = 20377;
    int32_t arrayLC0[] = {1,2,3};
    for(int i=0; i<3; i++) str(&arrayLC0[i], &LC0, i*4, 4, false, false, false);

    LC2 = 20389;
    int32_t arrayLC2[] = {-1,2,4,6,8};
    for(int i=0; i<5; i++) str(&arrayLC2[i], &LC2, i*4, 4, false, false, false);

    __PRETTY_FUNCTION__4935 = 20409;
    strcpy(malloc_0+__PRETTY_FUNCTION__4935, "test\000");

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "exponential_search.c";

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

void exponential_searchpart0();
void exponential_search();
void binary_search();
void main();

void assert_help()
{
    __assert_fail(malloc_0+r0.i, malloc_0+r1.i, r2.i, malloc_0+r3.i);
}

void exponential_searchpart0()
{
    counters[0] ++;
    r3.i = 1;
    goto L2;
L4:
    counters[1] ++;
    r3.i = (uint32_t)r3.i << 1;
    tmp = r3.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r1.i);
    v = (r3.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (c && !z)
    {
        goto L3;
    }
L2:
    counters[2] ++;
    load_counter ++;
    ldr(&ip.i, &r0.i, ((uint32_t)r3.i << 2), 4, false, false, false);
    tmp = ip.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r2.i);
    v = (ip.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (n != v)
    {
        goto L4;
    }
L3:
    counters[3] ++;
    tmp = r1.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r3.i);
    v = (r1.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    ip.i = (r3.i >> 1) & ((1 << 16) - 1);
    if (c)
    {
        r1.i = r3.i;
    }
    r3.i = r1.i - (((uint32_t)r3.i >> 1));
    r1.i = 0xffff & (uint16_t)r1.i;
    r3.i = r3.i + (((uint32_t)r3.i >> 31));
    tmp = ip.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r1.i);
    v = (ip.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    r3.i = ip.i + ((r3.i >> 1));
    r3.i = 0xffff & (uint16_t)r3.i;
    if (c && !z)
    {
        goto L10;
    }
    counters[4] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r4.i, &sp.i, 0, 4, false, false, false);
L6:
    counters[5] ++;
    r5.i = r3.i - (1);
    load_counter ++;
    ldr(&lr.i, &r0.i, ((uint32_t)r3.i << 2), 4, false, false, false);
    r4.i = r3.i + (1);
    tmp = r2.i - lr.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) lr.i);
    v = (r2.i&0x80000000) != (lr.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (z)
    {
        goto L16;
    }
    counters[6] ++;
    if (n == v)
    {
        goto L8;
    }
    counters[7] ++;
    r1.i = 0xffff & (uint16_t)r5.i;
    r3.i = r1.i - (ip.i);
    tmp = r1.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) ip.i);
    v = (r1.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    r3.i = r3.i + (((uint32_t)r3.i >> 31));
    r3.i = ip.i + ((r3.i >> 1));
    r3.i = 0xffff & (uint16_t)r3.i;
    if (c)
    {
        goto L6;
    }
L11:
    counters[8] ++;
    r0.i = ~0;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;
L8:
    counters[9] ++;
    ip.i = 0xffff & (uint16_t)r4.i;
    r3.i = r1.i - (ip.i);
    tmp = ip.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r1.i);
    v = (ip.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    r3.i = r3.i + (((uint32_t)r3.i >> 31));
    r3.i = ip.i + ((r3.i >> 1));
    r3.i = 0xffff & (uint16_t)r3.i;
    if (!c || z)
    {
        goto L6;
    }
    counters[10] ++;
    goto L11;
L16:
    counters[11] ++;
    r0.i = r3.i;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;
L10:
    counters[12] ++;
    r0.i = ~0;
    return;

}

void exponential_search()
{
    counters[13] ++;
    tmp = r1.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 0);
    v = (r1.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (z)
    {
        goto L27;
    }
    counters[14] ++;
    r3.i = 1;
    goto L19;
L21:
    counters[15] ++;
    r3.i = (uint32_t)r3.i << 1;
    tmp = r1.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r3.i);
    v = (r1.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!c)
    {
        goto L20;
    }
L19:
    counters[16] ++;
    load_counter ++;
    ldr(&ip.i, &r0.i, ((uint32_t)r3.i << 2), 4, false, false, false);
    tmp = r2.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) ip.i);
    v = (r2.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z && n == v)
    {
        goto L21;
    }
L20:
    counters[17] ++;
    tmp = r1.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r3.i);
    v = (r1.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    ip.i = (r3.i >> 1) & ((1 << 16) - 1);
    if (c)
    {
        r1.i = r3.i;
    }
    r3.i = r1.i - (((uint32_t)r3.i >> 1));
    r1.i = 0xffff & (uint16_t)r1.i;
    r3.i = r3.i + (((uint32_t)r3.i >> 31));
    tmp = ip.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r1.i);
    v = (ip.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    r3.i = ip.i + ((r3.i >> 1));
    r3.i = 0xffff & (uint16_t)r3.i;
    if (c && !z)
    {
        goto L27;
    }
    counters[18] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r4.i, &sp.i, 0, 4, false, false, false);
L22:
    counters[19] ++;
    r5.i = r3.i - (1);
    load_counter ++;
    ldr(&lr.i, &r0.i, ((uint32_t)r3.i << 2), 4, false, false, false);
    r4.i = r3.i + (1);
    tmp = r2.i - lr.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) lr.i);
    v = (r2.i&0x80000000) != (lr.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (z)
    {
        goto L32;
    }
    counters[20] ++;
    if (n == v)
    {
        goto L24;
    }
    counters[21] ++;
    r1.i = 0xffff & (uint16_t)r5.i;
    r3.i = r1.i - (ip.i);
    tmp = r1.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) ip.i);
    v = (r1.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    r3.i = r3.i + (((uint32_t)r3.i >> 31));
    r3.i = ip.i + ((r3.i >> 1));
    r3.i = 0xffff & (uint16_t)r3.i;
    if (c)
    {
        goto L22;
    }
L28:
    counters[22] ++;
    r0.i = ~0;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;
L24:
    counters[23] ++;
    ip.i = 0xffff & (uint16_t)r4.i;
    r3.i = r1.i - (ip.i);
    tmp = ip.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r1.i);
    v = (ip.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    r3.i = r3.i + (((uint32_t)r3.i >> 31));
    r3.i = ip.i + ((r3.i >> 1));
    r3.i = 0xffff & (uint16_t)r3.i;
    if (!c || z)
    {
        goto L22;
    }
    counters[24] ++;
    goto L28;
L32:
    counters[25] ++;
    r0.i = r3.i;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;
L27:
    counters[26] ++;
    r0.i = ~0;
    return;

}

void binary_search()
{
    counters[27] ++;
    ip.i = r2.i - (r1.i);
    tmp = r1.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r2.i);
    v = (r1.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    ip.i = ip.i + (((uint32_t)ip.i >> 31));
    ip.i = r1.i + ((ip.i >> 1));
    ip.i = 0xffff & (uint16_t)ip.i;
    if (c && !z)
    {
        goto L39;
    }
    counters[28] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r4.i, &sp.i, 0, 4, false, false, false);
L35:
    counters[29] ++;
    r5.i = ip.i - (1);
    load_counter ++;
    ldr(&lr.i, &r0.i, ((uint32_t)ip.i << 2), 4, false, false, false);
    r4.i = ip.i + (1);
    tmp = lr.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) r3.i);
    v = (lr.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    if (z)
    {
        goto L44;
    }
    counters[30] ++;
    if (z || n != v)
    {
        goto L37;
    }
    counters[31] ++;
    r2.i = 0xffff & (uint16_t)r5.i;
    ip.i = r2.i - (r1.i);
    tmp = r2.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r1.i);
    v = (r2.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    ip.i = ip.i + (((uint32_t)ip.i >> 31));
    ip.i = r1.i + ((ip.i >> 1));
    ip.i = 0xffff & (uint16_t)ip.i;
    if (c)
    {
        goto L35;
    }
L40:
    counters[32] ++;
    r0.i = ~0;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;
L37:
    counters[33] ++;
    r1.i = 0xffff & (uint16_t)r4.i;
    ip.i = r2.i - (r1.i);
    tmp = r1.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r2.i);
    v = (r1.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    ip.i = ip.i + (((uint32_t)ip.i >> 31));
    ip.i = r1.i + ((ip.i >> 1));
    ip.i = 0xffff & (uint16_t)ip.i;
    if (!c || z)
    {
        goto L35;
    }
    counters[34] ++;
    goto L40;
L44:
    counters[35] ++;
    r0.i = ip.i;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;
L39:
    counters[36] ++;
    r0.i = ~0;
    return;

}

void main()
{
    malloc_start();
    counters[37] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r9.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r8.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r6.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r4.i, &sp.i, 0, 4, false, false, false);
    r4.i = (LC0 & 0xffff);
    r4.i = r4.i | (((uint32_t)LC0 >> 16) << 16);
    sp.i = sp.i - (88);
    r5.i = sp.i + (16);
    load_counter ++;
    tmp = r4.i;
    ldr(&r0.i, &r4.i, 0, 4, false, false, false);
    r4.i += 4;
    ldr(&r1.i, &r4.i, 0, 4, false, false, false);
    r4.i += 4;
    ldr(&r2.i, &r4.i, 0, 4, false, false, false);
    r4.i += 4;
    r4.i = tmp;
    store_counter ++;
    tmp = r5.i;
    str(&r0.i, &r5.i, 0, 4, false, false, false);
    r5.i += 4;
    str(&r1.i, &r5.i, 0, 4, false, false, false);
    r5.i += 4;
    str(&r2.i, &r5.i, 0, 4, false, false, false);
    r5.i += 4;
    r5.i = tmp;
    r0.i = r5.i;
    r2.i = 10;
    r1.i = 3;
    exponential_searchpart0();
    counters[38] ++;
    tmp = r0.i + 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) tmp) < ((uint32_t) r0.i);
    v = (r0.i&0x80000000) == (1&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        goto L54;
    }
    counters[39] ++;
    r2.i = 1;
    r6.i = r0.i;
    r1.i = r2.i;
    r0.i = r5.i;
    exponential_searchpart0();
    counters[40] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        goto L55;
    }
    counters[41] ++;
    r2.i = 1;
    r1.i = 2;
    r0.i = sp.i;
    r8.i = 1;
    r9.i = 2;
    store_counter ++;
    str(&r8.i, &sp.i, 0, 4, false, false, false);
    str(&r9.i, &sp.i, 4, 4, false, false, false);
    exponential_searchpart0();
    counters[42] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        goto L56;
    }
    counters[43] ++;
    r2.i = 2;
    r0.i = sp.i + (8);
    r1.i = r2.i;
    store_counter ++;
    str(&r8.i, &sp.i, 8, 4, false, false, false);
    str(&r9.i, &sp.i, 12, 4, false, false, false);
    exponential_searchpart0();
    counters[44] ++;
    tmp = r0.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 1);
    v = (r0.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        goto L57;
    }
    counters[45] ++;
    lr.i = r4.i + (20);
    ip.i = sp.i + (28);
    load_counter ++;
    ldr(&r0.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    ldr(&r1.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    ldr(&r2.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    ldr(&r3.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    load_counter ++;
    ldr(&lr.i, &lr.i, 0, 4, false, false, false);
    store_counter ++;
    str(&r0.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    str(&r1.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    str(&r2.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    str(&r3.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    r0.i = sp.i + (28);
    r2.i = r6.i;
    r1.i = 5;
    store_counter ++;
    str(&lr.i, &ip.i, 0, 4, false, false, false);
    exponential_searchpart0();
    counters[46] ++;
    r5.i = r0.i - (0);
    z = r5.i == 0;
    n = r5.i & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (r5.i&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        goto L58;
    }
    counters[47] ++;
    lr.i = r4.i + (20);
    ip.i = sp.i + (48);
    load_counter ++;
    ldr(&r0.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    ldr(&r1.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    ldr(&r2.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    ldr(&r3.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    load_counter ++;
    ldr(&lr.i, &lr.i, 0, 4, false, false, false);
    store_counter ++;
    str(&r0.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    str(&r1.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    str(&r2.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    str(&r3.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    r0.i = sp.i + (48);
    r2.i = 8;
    r1.i = 5;
    store_counter ++;
    str(&lr.i, &ip.i, 0, 4, false, false, false);
    exponential_searchpart0();
    counters[48] ++;
    tmp = r0.i - 4;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 4);
    v = (r0.i&0x80000000) != (4&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        goto L59;
    }
    counters[49] ++;
    lr.i = r4.i + (20);
    ip.i = sp.i + (68);
    load_counter ++;
    ldr(&r0.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    ldr(&r1.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    ldr(&r2.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    ldr(&r3.i, &lr.i, 0, 4, false, false, false);
    lr.i += 4;
    load_counter ++;
    ldr(&lr.i, &lr.i, 0, 4, false, false, false);
    store_counter ++;
    str(&r0.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    str(&r1.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    str(&r2.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    str(&r3.i, &ip.i, 0, 4, false, false, false);
    ip.i += 4;
    r0.i = sp.i + (68);
    r2.i = 6;
    r1.i = 5;
    store_counter ++;
    str(&lr.i, &ip.i, 0, 4, false, false, false);
    exponential_searchpart0();
    counters[50] ++;
    tmp = r0.i - 3;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 3);
    v = (r0.i&0x80000000) != (3&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        goto L60;
    }
    counters[51] ++;
    r0.i = r5.i;
    sp.i = sp.i + (88);
    load_counter ++;
    ldr(&r4.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&r6.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&r8.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&r9.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;
L54:
    counters[52] ++;
    r1.i = (LC3 & 0xffff);
    r0.i = (LC4 & 0xffff);
    r3.i = r4.i + (12);
    r1.i = r1.i | (((uint32_t)LC3 >> 16) << 16);
    r0.i = r0.i | (((uint32_t)LC4 >> 16) << 16);
    r2.i = 89;
    assert_help();
L60:
    counters[53] ++;
    r1.i = (LC3 & 0xffff);
    r0.i = (LC10 & 0xffff);
    r3.i = r4.i + (12);
    r1.i = r1.i | (((uint32_t)LC3 >> 16) << 16);
    r0.i = r0.i | (((uint32_t)LC10 >> 16) << 16);
    r2.i = 107;
    assert_help();
L59:
    counters[54] ++;
    r1.i = (LC3 & 0xffff);
    r0.i = (LC9 & 0xffff);
    r3.i = r4.i + (12);
    r1.i = r1.i | (((uint32_t)LC3 >> 16) << 16);
    r0.i = r0.i | (((uint32_t)LC9 >> 16) << 16);
    r2.i = 104;
    assert_help();
L58:
    counters[55] ++;
    r1.i = (LC3 & 0xffff);
    r0.i = (LC8 & 0xffff);
    r3.i = r4.i + (12);
    r1.i = r1.i | (((uint32_t)LC3 >> 16) << 16);
    r0.i = r0.i | (((uint32_t)LC8 >> 16) << 16);
    r2.i = 101;
    assert_help();
L57:
    counters[56] ++;
    r1.i = (LC3 & 0xffff);
    r0.i = (LC7 & 0xffff);
    r3.i = r4.i + (12);
    r1.i = r1.i | (((uint32_t)LC3 >> 16) << 16);
    r0.i = r0.i | (((uint32_t)LC7 >> 16) << 16);
    r2.i = 98;
    assert_help();
L56:
    counters[57] ++;
    r1.i = (LC3 & 0xffff);
    r0.i = (LC6 & 0xffff);
    r3.i = r4.i + (12);
    r1.i = r1.i | (((uint32_t)LC3 >> 16) << 16);
    r0.i = r0.i | (((uint32_t)LC6 >> 16) << 16);
    r2.i = 95;
    assert_help();
L55:
    counters[58] ++;
    r1.i = (LC3 & 0xffff);
    r0.i = (LC5 & 0xffff);
    r3.i = r4.i + (12);
    r1.i = r1.i | (((uint32_t)LC3 >> 16) << 16);
    r0.i = r0.i | (((uint32_t)LC5 >> 16) << 16);
    r2.i = 92;
    assert_help();
    return;
}

