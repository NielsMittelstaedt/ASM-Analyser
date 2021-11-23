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

reg r3, r6, r10, r0, r4, r1, r2, r5, r8, r7, r9;

int32_t LC0, LC1;

int counters[25] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[25] = {3,4,3,2,2,6,2,2,5,1,8,2,7,3,2,2,5,1,5,12,4,4,2,2,3};


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
    int32_t size = (1028-start)/4;
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

    int32_t malloc_total = (int32_t) ((uint8_t*) malloc(44) - malloc_0);
    LC0 = malloc_total;
    strcpy(malloc_0+LC0, "Enter 6 numbers unsorted \012\000");

    LC1 = malloc_total + 35;
    strcpy(malloc_0+LC1, "%d \000");

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "bogo_sort.c";

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

void check_sorted();
void shuffle();
void sort();
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

void check_sorted()
{
    counters[0] ++;
    r3.i = r1.i - -1073741823;
    r0.i = r0.i + ((uint32_t)r3.i << 2);
    goto L2;
L4:
    counters[1] ++;
    load_counter ++;
    ldr(&r2.i, &r0.i, 0, 4, false, true, false);
    load_counter ++;
    ldr(&r3.i, &r0.i, -4, 4, true, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n != v)
    {
        goto L5;
    }
L2:
    counters[2] ++;
    r1.i = r1.i - 1;
    tmp = r1.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 0);
    v = (r1.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!z && n == v)
    {
        goto L4;
    }
    counters[3] ++;
    r0.i = 1;
    return;
L5:
    counters[4] ++;
    r0.i = 0;
    return;

}

void shuffle()
{
    counters[5] ++;
    store_counter ++;
    sp.i -= 24;
    str(&r4.i, &sp.i, 0*4, 4, false, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false, false);
    str(&r7.i, &sp.i, 3*4, 4, false, false, false);
    str(&r8.i, &sp.i, 4*4, 4, false, false, false);
    str(&lr.i, &sp.i, 5*4, 4, false, false, false);
    r7.i = r1.i - 0;
    z = r7.i == 0;
    n = r7.i & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 0);
    v = (r1.i&0x80000000) != (0&0x80000000) && (r7.i&0x80000000) != (r1.i&0x80000000);
    load_counter ++;
    if (z || n != v)
    {
        ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
        ldr(&r5.i, &sp.i, 1*4, 4, false, false, false);
        ldr(&r6.i, &sp.i, 2*4, 4, false, false, false);
        ldr(&r7.i, &sp.i, 3*4, 4, false, false, false);
        ldr(&r8.i, &sp.i, 4*4, 4, false, false, false);
        ldr(&pc.i, &sp.i, 5*4, 4, false, false, false);
        sp.i += 24;
        return;
    }
    r8.i = r0.i + ((uint32_t)r7.i << 2);
    r5.i = r0.i;
    r4.i = r0.i;
L9:
    counters[6] ++;
    load_counter ++;
    ldr(&r6.i, &r4.i, 0, 4, false, true, false);
    rand_help();
    counters[7] ++;
    r1.i = r7.i;
    idivmod();
    counters[8] ++;
    load_counter ++;
    ldr(&r3.i, &r5.i, ((uint32_t)r1.i << 2), 4, false, false, false);
    store_counter ++;
    str(&r3.i, &r4.i, 4, 4, false, true, false);
    tmp = r8.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) r4.i);
    v = (r8.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    store_counter ++;
    str(&r6.i, &r5.i, ((uint32_t)r1.i << 2), 4, false, false, false);
    if (!z)
    {
        goto L9;
    }
    counters[9] ++;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false, false);
    ldr(&r7.i, &sp.i, 3*4, 4, false, false, false);
    ldr(&r8.i, &sp.i, 4*4, 4, false, false, false);
    ldr(&pc.i, &sp.i, 5*4, 4, false, false, false);
    sp.i += 24;
    return;

}

void sort()
{
    counters[10] ++;
    store_counter ++;
    sp.i -= 32;
    str(&r4.i, &sp.i, 0*4, 4, false, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false, false);
    str(&r7.i, &sp.i, 3*4, 4, false, false, false);
    str(&r8.i, &sp.i, 4*4, 4, false, false, false);
    str(&r9.i, &sp.i, 5*4, 4, false, false, false);
    str(&r10.i, &sp.i, 6*4, 4, false, false, false);
    str(&lr.i, &sp.i, 7*4, 4, false, false, false);
    r7.i = r1.i - -1073741823;
    r5.i = r1.i;
    r8.i = r0.i;
    r7.i = (uint32_t)r7.i << 2;
    r6.i = r7.i + 4;
    r7.i = r0.i + r7.i;
    r6.i = r6.i + r0.i;
L13:
    counters[11] ++;
    r2.i = r7.i;
    r3.i = r5.i;
L15:
    counters[12] ++;
    r3.i = r3.i - 1;
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    load_counter ++;
    if (z || n != v)
    {
        ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
        ldr(&r5.i, &sp.i, 1*4, 4, false, false, false);
        ldr(&r6.i, &sp.i, 2*4, 4, false, false, false);
        ldr(&r7.i, &sp.i, 3*4, 4, false, false, false);
        ldr(&r8.i, &sp.i, 4*4, 4, false, false, false);
        ldr(&r9.i, &sp.i, 5*4, 4, false, false, false);
        ldr(&r10.i, &sp.i, 6*4, 4, false, false, false);
        ldr(&pc.i, &sp.i, 7*4, 4, false, false, false);
        sp.i += 32;
        return;
    }
    load_counter ++;
    ldr(&r0.i, &r2.i, 0, 4, false, true, false);
    load_counter ++;
    ldr(&r1.i, &r2.i, -4, 4, true, false, false);
    tmp = r0.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) r1.i);
    v = (r0.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (n == v)
    {
        goto L15;
    }
    counters[13] ++;
    tmp = r5.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) 0);
    v = (r5.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (!z && n == v)
    {
        r4.i = r8.i;
    }
    if (z || n != v)
    {
        goto L13;
    }
L14:
    counters[14] ++;
    load_counter ++;
    ldr(&r9.i, &r4.i, 0, 4, false, true, false);
    rand_help();
    counters[15] ++;
    r1.i = r5.i;
    idivmod();
    counters[16] ++;
    load_counter ++;
    ldr(&r3.i, &r8.i, ((uint32_t)r1.i << 2), 4, false, false, false);
    store_counter ++;
    str(&r3.i, &r4.i, 4, 4, false, true, false);
    tmp = r6.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) r4.i);
    v = (r6.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    store_counter ++;
    str(&r9.i, &r8.i, ((uint32_t)r1.i << 2), 4, false, false, false);
    if (!z)
    {
        goto L14;
    }
    counters[17] ++;
    goto L13;
    return;
}

void main()
{
    malloc_start();
    counters[18] ++;
    store_counter ++;
    sp.i -= 16;
    str(&r4.i, &sp.i, 0*4, 4, false, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false, false);
    str(&lr.i, &sp.i, 3*4, 4, false, false, false);
    sp.i = sp.i - 24;
    r0.i = (LC0 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC0 >> 16) << 16);
    printf("%s\n", malloc_0+r0.i);
    counters[19] ++;
    r0.i = sp.i;
    r1.i = 6;
    r2.i = 6;
    r3.i = 5;
    store_counter ++;
    str(&r2.i, &sp.i, 0, 4, false, true, false);
    str(&r3.i, &sp.i, 4, 4, false, true, false);
    r2.i = 4;
    r3.i = 3;
    store_counter ++;
    str(&r2.i, &sp.i, 8, 4, false, false, false);
    str(&r3.i, &sp.i, 12, 4, false, false, false);
    r2.i = 2;
    r3.i = 1;
    store_counter ++;
    str(&r2.i, &sp.i, 16, 4, false, false, false);
    str(&r3.i, &sp.i, 20, 4, false, false, false);
    sort();
    counters[20] ++;
    r5.i = (LC1 & 0xffff);
    r6.i = sp.i + 24;
    r5.i = r5.i | (((uint32_t)LC1 >> 16) << 16);
    r4.i = sp.i;
L24:
    counters[21] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 4, 4, false, true, false);
    r1.i = r5.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[22] ++;
    tmp = r6.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) r4.i);
    v = (r6.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    if (!z)
    {
        goto L24;
    }
    counters[23] ++;
    r0.i = 10;
    printf("%c", (char)r0.i);
    counters[24] ++;
    r0.i = 0;
    sp.i = sp.i + 24;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false, false);
    ldr(&pc.i, &sp.i, 3*4, 4, false, false, false);
    sp.i += 16;
    counter_summary();
    return;

}

