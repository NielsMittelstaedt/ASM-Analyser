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

reg r2, r8, r1, r0, r3, r9, r10, r5, r4, r6, r7;

int32_t LC0;

int counters[55] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[55] = {2,2,3,3,2,2,2,3,3,2,5,2,5,1,2,4,3,3,1,2,4,3,2,2,9,1,3,3,2,1,4,4,2,5,4,9,2,1,2,9,2,1,5,2,1,3,2,2,17,1,4,2,2,2,2};


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

    int32_t malloc_total = (int32_t) ((uint8_t*) malloc(9) - malloc_0);
    LC0 = malloc_total;
    strcpy(malloc_0+LC0, "%d \000");

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "random_quick_sort.c";

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

void getBig();
void getSmall();
void swap();
void random_quick();
void main();

void idivmod()
{
    int32_t quot = r0.i / r1.i;
    int32_t rem = r0.i % r1.i;
    r0.i = quot;
    r1.i = rem;
}
void time_help()
{
    r0.i = time(NULL);
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
void srand_help()
{
    srand(r0.i);
}
void rand_help()
{
    r0.i = rand();
}

void getBig()
{
    counters[0] ++;
    tmp = r1.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r2.i);
    v = (r1.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!z && n == v)
    {
        goto L2;
    }
    counters[1] ++;
    ip.i = r0.i + (((uint32_t)r1.i << 2));
    r0.i = r1.i;
L4:
    counters[2] ++;
    load_counter ++;
    ldr(&r1.i, &ip.i, 4, 4, false, true, false);
    tmp = r1.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r3.i);
    v = (r1.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!z && n == v)
    {
        return;
    }
    counters[3] ++;
    r0.i = r0.i + (1);
    tmp = r2.i - r0.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r0.i);
    v = (r2.i&0x80000000) != (r0.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n == v)
    {
        goto L4;
    }
L2:
    counters[4] ++;
    r0.i = r2.i + (1);
    return;

}

void getSmall()
{
    counters[5] ++;
    tmp = r1.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r2.i);
    v = (r1.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (n != v)
    {
        goto L10;
    }
    counters[6] ++;
    ip.i = r0.i + (((uint32_t)r1.i << 2));
    r0.i = r1.i;
L9:
    counters[7] ++;
    load_counter ++;
    ldr(&r1.i, &ip.i, -4, 4, false, true, false);
    tmp = r1.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r3.i);
    v = (r1.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (n != v)
    {
        return;
    }
    counters[8] ++;
    r0.i = r0.i - (1);
    tmp = r2.i - r0.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r0.i);
    v = (r2.i&0x80000000) != (r0.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (z || n != v)
    {
        goto L9;
    }
L10:
    counters[9] ++;
    r0.i = ~0;
    return;

}

void swap()
{
    counters[10] ++;
    load_counter ++;
    ldr(&r3.i, &r0.i, 0, 4, false, true, false);
    load_counter ++;
    ldr(&r2.i, &r1.i, 0, 4, false, true, false);
    store_counter ++;
    str(&r2.i, &r0.i, 0, 4, false, true, false);
    store_counter ++;
    str(&r3.i, &r1.i, 0, 4, false, true, false);
    return;

}

void random_quick()
{
    counters[11] ++;
    tmp = r1.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r2.i);
    v = (r1.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (n == v)
    {
        return;
    }
    counters[12] ++;
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
    r6.i = r0.i + (((uint32_t)r2.i << 2));
    r5.i = r1.i;
    r4.i = r2.i;
    r7.i = r0.i;
L15:
    counters[13] ++;
    rand_help();
    counters[14] ++;
    r1.i = r4.i - (r5.i);
    idivmod();
    counters[15] ++;
    r3.i = r7.i + (((uint32_t)r5.i << 2));
    ip.i = r5.i;
    r8.i = r1.i + (r5.i);
    load_counter ++;
    ldr(&r1.i, &r7.i, ((uint32_t)r8.i << 2), 4, false, false, false);
L17:
    counters[16] ++;
    load_counter ++;
    ldr(&r2.i, &r3.i, 4, 4, false, true, false);
    tmp = r1.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r2.i);
    v = (r1.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (n != v)
    {
        goto L16;
    }
    counters[17] ++;
    ip.i = ip.i + (1);
    tmp = r4.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) ip.i);
    v = (r4.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (n == v)
    {
        goto L17;
    }
    counters[18] ++;
    ip.i = r4.i + (1);
L16:
    counters[19] ++;
    r2.i = r6.i;
    r3.i = r4.i;
L21:
    counters[20] ++;
    load_counter ++;
    ldr(&r0.i, &r2.i, -4, 4, false, true, false);
    r9.i = (uint32_t)r3.i << 2;
    tmp = r1.i - r0.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r0.i);
    v = (r1.i&0x80000000) != (r0.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!z && n == v)
    {
        goto L26;
    }
    counters[21] ++;
    r3.i = r3.i - (1);
    tmp = r3.i - r5.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r5.i);
    v = (r3.i&0x80000000) != (r5.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (n == v)
    {
        goto L21;
    }
L31:
    counters[22] ++;
    r9.i = ~3;
    r3.i = ~0;
L26:
    counters[23] ++;
    tmp = r3.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) ip.i);
    v = (r3.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (n != v)
    {
        goto L44;
    }
L19:
    counters[24] ++;
    load_counter ++;
    ldr(&r9.i, &r7.i, ((uint32_t)ip.i << 2), 4, false, false, false);
    tmp = r4.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) ip.i);
    v = (r4.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    load_counter ++;
    ldr(&r10.i, &r7.i, ((uint32_t)r3.i << 2), 4, false, false, false);
    r0.i = (uint32_t)r3.i << 2;
    lr.i = r7.i + (r0.i);
    r2.i = r7.i + (((uint32_t)ip.i << 2));
    store_counter ++;
    str(&r10.i, &r7.i, ((uint32_t)ip.i << 2), 4, false, false, false);
    store_counter ++;
    str(&r9.i, &r7.i, ((uint32_t)r3.i << 2), 4, false, false, false);
    if (n == v)
    {
        goto L25;
    }
    counters[25] ++;
    goto L23;
L45:
    counters[26] ++;
    ip.i = ip.i + (1);
    tmp = r4.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) ip.i);
    v = (r4.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (n != v)
    {
        goto L23;
    }
L25:
    counters[27] ++;
    load_counter ++;
    ldr(&r9.i, &r2.i, 4, 4, false, true, false);
    tmp = r1.i - r9.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r9.i);
    v = (r1.i&0x80000000) != (r9.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (n == v)
    {
        goto L45;
    }
L24:
    counters[28] ++;
    tmp = r3.i - r5.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r5.i);
    v = (r3.i&0x80000000) != (r5.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (n == v)
    {
        goto L27;
    }
    counters[29] ++;
    goto L31;
L46:
    counters[30] ++;
    r3.i = r3.i - (1);
    tmp = r3.i - r5.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r5.i);
    v = (r3.i&0x80000000) != (r5.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    r0.i = (uint32_t)r3.i << 2;
    if (n != v)
    {
        goto L31;
    }
L27:
    counters[31] ++;
    load_counter ++;
    ldr(&r2.i, &lr.i, -4, 4, false, true, false);
    r9.i = r0.i;
    tmp = r1.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r2.i);
    v = (r1.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (z || n != v)
    {
        goto L46;
    }
    counters[32] ++;
    tmp = r3.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) ip.i);
    v = (r3.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (n == v)
    {
        goto L19;
    }
L44:
    counters[33] ++;
    tmp = ip.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r3.i);
    v = (ip.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (n == v)
    {
        r2.i = ip.i;
    }
    if (n != v)
    {
        r2.i = r3.i;
    }
    tmp = r8.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) r2.i);
    v = (r8.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    if (!z && n == v)
    {
        goto L47;
    }
    counters[34] ++;
    tmp = ip.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r3.i);
    v = (ip.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (n == v)
    {
        ip.i = r3.i;
    }
    tmp = r8.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) ip.i);
    v = (r8.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    if (n == v)
    {
        goto L30;
    }
    counters[35] ++;
    load_counter ++;
    ldr(&ip.i, &r7.i, r9.i, 4, false, false, false);
    r1.i = r5.i;
    load_counter ++;
    ldr(&lr.i, &r7.i, ((uint32_t)r8.i << 2), 4, false, false, false);
    r5.i = r3.i + (1);
    r2.i = r3.i - (1);
    r0.i = r7.i;
    store_counter ++;
    str(&lr.i, &r7.i, r9.i, 4, false, false, false);
    store_counter ++;
    str(&ip.i, &r7.i, ((uint32_t)r8.i << 2), 4, false, false, false);
    random_quick();
    counters[36] ++;
    tmp = r4.i - r5.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r5.i);
    v = (r4.i&0x80000000) != (r5.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z && n == v)
    {
        goto L15;
    }
    counters[37] ++;
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
L23:
    counters[38] ++;
    ip.i = r4.i + (1);
    goto L24;
L47:
    counters[39] ++;
    load_counter ++;
    ldr(&r3.i, &r7.i, ((uint32_t)ip.i << 2), 4, false, false, false);
    r1.i = r5.i;
    load_counter ++;
    ldr(&lr.i, &r7.i, ((uint32_t)r8.i << 2), 4, false, false, false);
    r5.i = ip.i + (1);
    r2.i = ip.i - (1);
    r0.i = r7.i;
    store_counter ++;
    str(&lr.i, &r7.i, ((uint32_t)ip.i << 2), 4, false, false, false);
    store_counter ++;
    str(&r3.i, &r7.i, ((uint32_t)r8.i << 2), 4, false, false, false);
    random_quick();
    counters[40] ++;
    tmp = r4.i - r5.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r5.i);
    v = (r4.i&0x80000000) != (r5.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z && n == v)
    {
        goto L15;
    }
    counters[41] ++;
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
L30:
    counters[42] ++;
    r1.i = r5.i;
    r2.i = r8.i - (1);
    r5.i = r8.i + (1);
    r0.i = r7.i;
    random_quick();
    counters[43] ++;
    tmp = r4.i - r5.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r5.i);
    v = (r4.i&0x80000000) != (r5.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z && n == v)
    {
        goto L15;
    }
    counters[44] ++;
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

void main()
{
    malloc_start();
    counters[45] ++;
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
    r0.i = 0;
    time_help();
    counters[46] ++;
    r6.i = (LC0 & 0xffff);
    srand_help();
    counters[47] ++;
    r0.i = 24;
    malloc_help();
    counters[48] ++;
    r2.i = 5;
    r3.i = 6;
    r1.i = 0;
    r6.i = r6.i | (((uint32_t)LC0 >> 16) << 16);
    store_counter ++;
    str(&r3.i, &r0.i, 0, 4, false, true, false);
    r3.i = 4;
    store_counter ++;
    str(&r2.i, &r0.i, 4, 4, false, false, false);
    r5.i = r0.i;
    store_counter ++;
    str(&r3.i, &r0.i, 8, 4, false, false, false);
    r3.i = 3;
    store_counter ++;
    str(&r3.i, &r0.i, 12, 4, false, false, false);
    r3.i = 2;
    store_counter ++;
    str(&r3.i, &r0.i, 16, 4, false, false, false);
    r3.i = 1;
    store_counter ++;
    str(&r3.i, &r0.i, 20, 4, false, false, false);
    r4.i = r5.i - (4);
    random_quick();
    counters[49] ++;
    r7.i = r5.i + (20);
L49:
    counters[50] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 4, 4, true, false, false);
    r1.i = r6.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[51] ++;
    tmp = r7.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r7.i) >= ((uint32_t) r4.i);
    v = (r7.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
    if (!z)
    {
        goto L49;
    }
    counters[52] ++;
    r0.i = r5.i;
    free_help();
    counters[53] ++;
    r0.i = 10;
    printf("%c", (char)r0.i);
    counters[54] ++;
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
    counter_summary();
    return;

}

