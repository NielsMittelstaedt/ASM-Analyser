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

reg r6, r5, r7, r2, r4, r8, r10, r1, r0, r3, r9;

int32_t LC0, LC1;

int counters[70] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[70] = {8,3,5,1,2,3,4,1,1,3,3,3,3,2,2,1,3,4,1,4,1,1,3,3,3,3,2,2,6,1,3,1,2,2,1,1,2,2,1,3,1,5,2,2,4,1,1,3,3,3,2,2,4,2,4,1,1,3,3,3,2,2,2,2,2,1,2,4,9,2};

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
    malloc_0 = (uint8_t*) malloc(20054);
    sp.i = 19996;
    fp = sp;
    LC0 = 20000;
    strcpy(malloc_0+LC0, "\012%d is prime\012\000");

    LC1 = 20025;
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

void Millerpart0();
void mulmod();
void modulo();
void Miller();
void main();

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
void printf_help(const char *format, int32_t test)
{
    if (strstr(format, "%s") != NULL)
        printf(format, malloc_0 + test);
    else
        printf(format, test);
}

void Millerpart0()
{
    counters[0] ++;
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
    tmp = r0.i & 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    sp.i = sp.i - (12);
    r8.i = r0.i - (1);
    fp.i = r0.i;
    r9.i = r8.i;
    store_counter ++;
    str(&r1.i, &sp.i, 4, 4, false, false, false);
    if (z)
    {
        goto L2;
    }
L3:
    counters[1] ++;
    r9.i = r9.i >> 1;
    tmp = r9.i & 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    if (z)
    {
        goto L3;
    }
L2:
    counters[2] ++;
    load_counter ++;
    ldr(&r3.i, &sp.i, 4, 4, false, false, false);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z && n == v)
    {
        r3.i = 0;
    }
    store_counter ++;
    if (!z && n == v)
    {
        str(&r3.i, &sp.i, 0, 4, false, false, false);
    }
    if (z || n != v)
    {
        goto L14;
    }
L4:
    counters[3] ++;
    rand_help();
    counters[4] ++;
    r1.i = r8.i;
    idivmod();
    counters[5] ++;
    r6.i = r9.i;
    r5.i = 1;
    r4.i = r1.i + (1);
L7:
    counters[6] ++;
    tmp = r6.i & 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    r1.i = fp.i;
    r0.i = (r4.i) * (r5.i);
    if (z)
    {
        goto L6;
    }
    counters[7] ++;
    idivmod();
    counters[8] ++;
    r5.i = r1.i;
L6:
    counters[9] ++;
    r0.i = (r4.i) * (r4.i);
    r1.i = fp.i;
    idivmod();
    counters[10] ++;
    r6.i = r6.i >> 1;
    z = r6.i == 0;
    n = r6.i & 0x80000000;
    c = r6.i & (1 << 1 - 1);
    r4.i = r1.i;
    if (!z)
    {
        goto L7;
    }
    counters[11] ++;
    r0.i = r5.i;
    r1.i = fp.i;
    idivmod();
    counters[12] ++;
    tmp = r8.i - r9.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) r9.i);
    v = (r8.i&0x80000000) != (r9.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    r10.i = r1.i;
    if (z)
    {
        goto L18;
    }
    counters[13] ++;
    tmp = r1.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 1);
    v = (r1.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (z)
    {
        goto L19;
    }
    counters[14] ++;
    tmp = r8.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) r1.i);
    v = (r8.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    if (z)
    {
        goto L9;
    }
    counters[15] ++;
    r7.i = r9.i;
L13:
    counters[16] ++;
    r1.i = fp.i;
    r0.i = r10.i;
    idivmod();
    counters[17] ++;
    tmp = r10.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r10.i) >= ((uint32_t) 0);
    v = (r10.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r10.i&0x80000000);
    r7.i = (uint32_t)r7.i << 1;
    r4.i = r1.i;
    if (z || n != v)
    {
        goto L10;
    }
    counters[18] ++;
    r5.i = 0;
L12:
    counters[19] ++;
    tmp = r10.i & 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    r0.i = r5.i + (r4.i);
    r1.i = fp.i;
    if (z)
    {
        goto L11;
    }
    counters[20] ++;
    idivmod();
    counters[21] ++;
    r5.i = r1.i;
L11:
    counters[22] ++;
    r0.i = (uint32_t)r4.i << 1;
    r1.i = fp.i;
    idivmod();
    counters[23] ++;
    r10.i = r10.i >> 1;
    z = r10.i == 0;
    n = r10.i & 0x80000000;
    c = r10.i & (1 << 1 - 1);
    r4.i = r1.i;
    if (!z)
    {
        goto L12;
    }
    counters[24] ++;
    r0.i = r5.i;
    r1.i = fp.i;
    idivmod();
    counters[25] ++;
    tmp = r8.i - r7.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) r7.i);
    v = (r8.i&0x80000000) != (r7.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    r10.i = r1.i;
    if (z)
    {
        goto L8;
    }
    counters[26] ++;
    tmp = r1.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 1);
    v = (r1.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (z)
    {
        goto L8;
    }
    counters[27] ++;
    tmp = r8.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) r1.i);
    v = (r8.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    if (!z)
    {
        goto L13;
    }
L9:
    counters[28] ++;
    load_counter ++;
    ldr(&r3.i, &sp.i, 0, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &sp.i, 4, 4, false, false, false);
    r3.i = r3.i + (1);
    store_counter ++;
    str(&r3.i, &sp.i, 0, 4, false, false, false);
    tmp = r3.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r2.i);
    v = (r3.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L4;
    }
L14:
    counters[29] ++;
    r6.i = 1;
L1:
    counters[30] ++;
    r0.i = r6.i;
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
L41:
    counters[31] ++;
    r7.i = (uint32_t)r7.i << 1;
L10:
    counters[32] ++;
    tmp = r8.i - r7.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) r7.i);
    v = (r8.i&0x80000000) != (r7.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    if (!z)
    {
        goto L41;
    }
    counters[33] ++;
    tmp = r7.i & 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    if (!z)
    {
        goto L9;
    }
    counters[34] ++;
    goto L1;
L19:
    counters[35] ++;
    r7.i = r9.i;
L8:
    counters[36] ++;
    tmp = r8.i - r10.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) r10.i);
    v = (r8.i&0x80000000) != (r10.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    if (z)
    {
        goto L9;
    }
L42:
    counters[37] ++;
    tmp = r7.i & 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    if (!z)
    {
        goto L9;
    }
    counters[38] ++;
    goto L1;
L18:
    counters[39] ++;
    tmp = r8.i - r10.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) r10.i);
    v = (r8.i&0x80000000) != (r10.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    r7.i = r8.i;
    if (!z)
    {
        goto L42;
    }
    counters[40] ++;
    goto L9;
    return;
}

void mulmod()
{
    counters[41] ++;
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
    r0.i = r6.i + (r4.i);
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
L47:
    counters[51] ++;
    r0.i = 0;
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

void modulo()
{
    counters[52] ++;
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
    r5.i = r1.i - (0);
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
    r0.i = (r4.i) * (r6.i);
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
    r0.i = (r4.i) * (r4.i);
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
L57:
    counters[61] ++;
    r6.i = 1;
    goto L54;
    return;
}

void Miller()
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
    Millerpart0();
    return;
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
    r0.i = 347;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r4.i, &sp.i, 0, 4, false, false, false);
    Millerpart0();
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
        r2.i = 347;
    }
    if (z)
    {
        r2.i = 347;
    }
    printf_help(malloc_0+r1.i, r2.i);
    counters[69] ++;
    r0.i = 0;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    counter_summary();
    return;

}

