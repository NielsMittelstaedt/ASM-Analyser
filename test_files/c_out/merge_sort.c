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

reg r1, r2, r3, r0;

int32_t LC1, LC0;

int counters[35] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[35] = {8,11,6,5,13,4,3,15,4,4,4,7,12,14,13,3,4,4,1,16,4,1,16,4,2,2,1,1,2,18,3,9,3,4,4};


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

    LC1 = (int32_t) ((uint8_t*) malloc(9) - malloc_0);
    strcpy(malloc_0+LC1, "%d \000");

    LC0 = (int32_t) ((uint8_t*) malloc(6*sizeof(int32_t)) - malloc_0);
    int32_t arrayLC0[] = {5,3,0,2,6,1};
    for(int i=0; i<6; i++) str(&arrayLC0[i], &LC0, i*4, 4, false, false);
}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "merge_sort.c";

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
    uint8_t* ptr = (uint8_t*) malloc(r0.i);
    r0.i = (int32_t) (ptr - malloc_0);
}
void free_help()
{
    free(malloc_0+r0.i);
}

void mergeSort()
{
    counters[0] ++;
    store_counter ++;
    sp.i -= 8;
    str(&fp.i, &sp.i, 0*4, 4, false, false);
    str(&lr.i, &sp.i, 1*4, 4, false, false);
    fp.i = sp.i + 4;
    sp.i = sp.i - 48;
    store_counter ++;
    str(&r0.i, &fp.i, -48, 4, false, false);
    store_counter ++;
    str(&r1.i, &fp.i, -52, 4, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -52, 4, false, false);
    tmp = r3.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 1);
    v = (r3.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!c || z)
    {
        goto L17;
    }
    counters[1] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -52, 4, false, false);
    r3.i = (uint32_t)r3.i >> 1;
    store_counter ++;
    str(&r3.i, &fp.i, -28, 4, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -28, 4, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -52, 4, false, false);
    r3.i = r2.i - r3.i;
    store_counter ++;
    str(&r3.i, &fp.i, -32, 4, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -28, 4, false, false);
    r3.i = (uint32_t)r3.i << 2;
    r0.i = r3.i;
    malloc_help();
    counters[2] ++;
    r3.i = r0.i;
    store_counter ++;
    str(&r3.i, &fp.i, -36, 4, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -32, 4, false, false);
    r3.i = (uint32_t)r3.i << 2;
    r0.i = r3.i;
    malloc_help();
    counters[3] ++;
    r3.i = r0.i;
    store_counter ++;
    str(&r3.i, &fp.i, -40, 4, false, false);
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false);
    goto L4;
L5:
    counters[4] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -48, 4, false, false);
    r2.i = r2.i + r3.i;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r1.i, &fp.i, -36, 4, false, false);
    r3.i = r1.i + r3.i;
    load_counter ++;
    ldr(&r2.i, &r2.i, 0, 4, false, true);
    store_counter ++;
    str(&r2.i, &r3.i, 0, 4, false, true);
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false);
    r3.i = r3.i + 1;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false);
L4:
    counters[5] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -8, 4, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -28, 4, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n != v)
    {
        goto L5;
    }
    counters[6] ++;
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false);
    goto L6;
L7:
    counters[7] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -28, 4, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false);
    r3.i = r2.i + r3.i;
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -48, 4, false, false);
    r2.i = r2.i + r3.i;
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r1.i, &fp.i, -40, 4, false, false);
    r3.i = r1.i + r3.i;
    load_counter ++;
    ldr(&r2.i, &r2.i, 0, 4, false, true);
    store_counter ++;
    str(&r2.i, &r3.i, 0, 4, false, true);
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false);
    r3.i = r3.i + 1;
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false);
L6:
    counters[8] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -12, 4, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -32, 4, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n != v)
    {
        goto L7;
    }
    counters[9] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -28, 4, false, false);
    r1.i = r3.i;
    load_counter ++;
    ldr(&r0.i, &fp.i, -36, 4, false, false);
    mergeSort();
    counters[10] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -32, 4, false, false);
    r1.i = r3.i;
    load_counter ++;
    ldr(&r0.i, &fp.i, -40, 4, false, false);
    mergeSort();
    counters[11] ++;
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -16, 4, false, false);
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -20, 4, false, false);
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -24, 4, false, false);
    goto L8;
L12:
    counters[12] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -36, 4, false, false);
    r3.i = r2.i + r3.i;
    load_counter ++;
    ldr(&r2.i, &r3.i, 0, 4, false, true);
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r1.i, &fp.i, -40, 4, false, false);
    r3.i = r1.i + r3.i;
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, true);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (c && !z)
    {
        goto L9;
    }
    counters[13] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -36, 4, false, false);
    r2.i = r2.i + r3.i;
    load_counter ++;
    ldr(&r3.i, &fp.i, -24, 4, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r1.i, &fp.i, -48, 4, false, false);
    r3.i = r1.i + r3.i;
    load_counter ++;
    ldr(&r2.i, &r2.i, 0, 4, false, true);
    store_counter ++;
    str(&r2.i, &r3.i, 0, 4, false, true);
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false);
    r3.i = r3.i + 1;
    store_counter ++;
    str(&r3.i, &fp.i, -16, 4, false, false);
    goto L10;
L9:
    counters[14] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -40, 4, false, false);
    r2.i = r2.i + r3.i;
    load_counter ++;
    ldr(&r3.i, &fp.i, -24, 4, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r1.i, &fp.i, -48, 4, false, false);
    r3.i = r1.i + r3.i;
    load_counter ++;
    ldr(&r2.i, &r2.i, 0, 4, false, true);
    store_counter ++;
    str(&r2.i, &r3.i, 0, 4, false, true);
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false);
    r3.i = r3.i + 1;
    store_counter ++;
    str(&r3.i, &fp.i, -20, 4, false, false);
L10:
    counters[15] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -24, 4, false, false);
    r3.i = r3.i + 1;
    store_counter ++;
    str(&r3.i, &fp.i, -24, 4, false, false);
L8:
    counters[16] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -16, 4, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -28, 4, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n == v)
    {
        goto L13;
    }
    counters[17] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -20, 4, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -32, 4, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n != v)
    {
        goto L12;
    }
    counters[18] ++;
    goto L13;
L14:
    counters[19] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -36, 4, false, false);
    r2.i = r2.i + r3.i;
    load_counter ++;
    ldr(&r3.i, &fp.i, -24, 4, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r1.i, &fp.i, -48, 4, false, false);
    r3.i = r1.i + r3.i;
    load_counter ++;
    ldr(&r2.i, &r2.i, 0, 4, false, true);
    store_counter ++;
    str(&r2.i, &r3.i, 0, 4, false, true);
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false);
    r3.i = r3.i + 1;
    store_counter ++;
    str(&r3.i, &fp.i, -16, 4, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -24, 4, false, false);
    r3.i = r3.i + 1;
    store_counter ++;
    str(&r3.i, &fp.i, -24, 4, false, false);
L13:
    counters[20] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -16, 4, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -28, 4, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n != v)
    {
        goto L14;
    }
    counters[21] ++;
    goto L15;
L16:
    counters[22] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r2.i, &fp.i, -40, 4, false, false);
    r2.i = r2.i + r3.i;
    load_counter ++;
    ldr(&r3.i, &fp.i, -24, 4, false, false);
    r3.i = (uint32_t)r3.i << 2;
    load_counter ++;
    ldr(&r1.i, &fp.i, -48, 4, false, false);
    r3.i = r1.i + r3.i;
    load_counter ++;
    ldr(&r2.i, &r2.i, 0, 4, false, true);
    store_counter ++;
    str(&r2.i, &r3.i, 0, 4, false, true);
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false);
    r3.i = r3.i + 1;
    store_counter ++;
    str(&r3.i, &fp.i, -20, 4, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -24, 4, false, false);
    r3.i = r3.i + 1;
    store_counter ++;
    str(&r3.i, &fp.i, -24, 4, false, false);
L15:
    counters[23] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -20, 4, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -32, 4, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n != v)
    {
        goto L16;
    }
    counters[24] ++;
    load_counter ++;
    ldr(&r0.i, &fp.i, -36, 4, false, false);
    free_help();
    counters[25] ++;
    load_counter ++;
    ldr(&r0.i, &fp.i, -40, 4, false, false);
    free_help();
    counters[26] ++;
    goto L1;
L17:
    counters[27] ++;
L1:
    counters[28] ++;
    sp.i = fp.i - 4;
    load_counter ++;
    ldr(&fp.i, &sp.i, 0*4, 4, false, false);
    ldr(&pc.i, &sp.i, 1*4, 4, false, false);
    sp.i += 8;
    return;

}

void main()
{
    malloc_start();
    counters[29] ++;
    store_counter ++;
    sp.i -= 8;
    str(&fp.i, &sp.i, 0*4, 4, false, false);
    str(&lr.i, &sp.i, 1*4, 4, false, false);
    fp.i = sp.i + 4;
    sp.i = sp.i - 32;
    r3.i = (LC0 & 0xffff);
    r3.i = r3.i | (((uint32_t)LC0 >> 16) << 16);
    ip.i = fp.i - 36;
    lr.i = r3.i;
    load_counter ++;
    ldr(&r0.i, &lr.i, 0*4, 4, false, false);
    ldr(&r1.i, &lr.i, 1*4, 4, false, false);
    ldr(&r2.i, &lr.i, 2*4, 4, false, false);
    ldr(&r3.i, &lr.i, 3*4, 4, false, false);
    lr.i += 16;
    store_counter ++;
    str(&r0.i, &ip.i, 0*4, 4, false, false);
    str(&r1.i, &ip.i, 1*4, 4, false, false);
    str(&r2.i, &ip.i, 2*4, 4, false, false);
    str(&r3.i, &ip.i, 3*4, 4, false, false);
    ip.i += 16;
    load_counter ++;
    ldr(&r0.i, &lr.i, 0*4, 4, false, false);
    ldr(&r1.i, &lr.i, 1*4, 4, false, false);
    store_counter ++;
    str(&r0.i, &ip.i, 0*4, 4, false, false);
    str(&r1.i, &ip.i, 1*4, 4, false, false);
    r3.i = 6;
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -12, 4, false, false);
    r3.i = fp.i - 36;
    r1.i = r2.i;
    r0.i = r3.i;
    mergeSort();
    counters[30] ++;
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false);
    goto L19;
L20:
    counters[31] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false);
    r3.i = (uint32_t)r3.i << 2;
    r2.i = fp.i - 4;
    r3.i = r2.i + r3.i;
    load_counter ++;
    ldr(&r3.i, &r3.i, -32, 4, false, false);
    r1.i = r3.i;
    r0.i = (LC1 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC1 >> 16) << 16);
    printf(malloc_0+r0.i, r1.i);
    counters[32] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false);
    r3.i = r3.i + 1;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false);
L19:
    counters[33] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -8, 4, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n != v)
    {
        goto L20;
    }
    counters[34] ++;
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

