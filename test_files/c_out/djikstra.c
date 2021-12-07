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

int32_t mat, V, dist, q, qp, visited, vp, LC0, LC1, LC2, LC3, LC4;

int counters[39] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[39] = {19,18,12,15,13,12,4,5,2,3,6,1,1,15,10,19,17,3,6,1,3,4,8,5,3,3,3,13,3,6,3,6,2,3,3,9,3,6,4};

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
    malloc_0 = (uint8_t*) malloc(21965);
    sp.i = 19996;
    fp = sp;
    mat = 20000;
    V = 21600;
    dist = 21604;
    q = 21684;
    qp = 21764;
    visited = 21768;
    vp = 21848;
    LC0 = 21852;
    strcpy(malloc_0+LC0, "Enter the number of vertices: \000");

    LC1 = 21888;
    strcpy(malloc_0+LC1, " %d\000");

    LC2 = 21897;
    strcpy(malloc_0+LC2, "Enter the adj matrix: \000");

    LC3 = 21925;
    strcpy(malloc_0+LC3, "\012Node\011Dist\000");

    LC4 = 21947;
    strcpy(malloc_0+LC4, "%d\011%d\012\000");

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "djikstra.c";

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

void enqueue();
void cf();
void dequeue();
void queue_has_something();
void dijkstra();
void main();

void scanf_help()
{
    scanf(malloc_0+r0.i, malloc_0+r1.i);
}
void printf_help(const char *format, int32_t test)
{
    if (strstr(format, "%s") != NULL)
        printf(format, malloc_0 + test);
    else
        printf(format, test);
}

void enqueue()
{
    counters[0] ++;
    store_counter ++;
    str(&fp.i, &sp.i, -4, 4, true, false, false);
    fp.i = sp.i + (0);
    sp.i = sp.i - (12);
    store_counter ++;
    str(&r0.i, &fp.i, -8, 4, false, false, false);
    r3.i = (qp & 0xffff);
    r3.i = r3.i | (((uint32_t)qp >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &r3.i, 0, 4, false, false, false);
    r1.i = r2.i + (1);
    r3.i = (qp & 0xffff);
    r3.i = r3.i | (((uint32_t)qp >> 16) << 16);
    store_counter ++;
    str(&r1.i, &r3.i, 0, 4, false, false, false);
    r3.i = (q & 0xffff);
    r3.i = r3.i | (((uint32_t)q >> 16) << 16);
    load_counter ++;
    ldr(&r1.i, &fp.i, -8, 4, false, false, false);
    store_counter ++;
    str(&r1.i, &r3.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    sp.i = fp.i + (0);
    load_counter ++;
    ldr(&fp.i, &sp.i, 4, 4, false, true, false);
    return;

}

void cf()
{
    counters[1] ++;
    store_counter ++;
    str(&fp.i, &sp.i, -4, 4, true, false, false);
    fp.i = sp.i + (0);
    sp.i = sp.i - (20);
    store_counter ++;
    str(&r0.i, &fp.i, -16, 4, false, false, false);
    store_counter ++;
    str(&r1.i, &fp.i, -20, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false, false);
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -20, 4, false, false, false);
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &r3.i, 0, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, false, false);
    r3.i = r2.i - (r3.i);
    r0.i = r3.i;
    sp.i = fp.i + (0);
    load_counter ++;
    ldr(&fp.i, &sp.i, 4, 4, false, true, false);
    return;

}

void dequeue()
{
    counters[2] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&fp.i, &sp.i, 0, 4, false, false, false);
    fp.i = sp.i + (4);
    r3.i = (qp & 0xffff);
    r3.i = r3.i | (((uint32_t)qp >> 16) << 16);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, false, false);
    r1.i = r3.i;
    r3.i = (cf & 0xffff);
    r3.i = r3.i | (((uint32_t)cf >> 16) << 16);
    r2.i = 4;
    r0.i = (q & 0xffff);
    r0.i = r0.i | (((uint32_t)q >> 16) << 16);
    qsort();
    counters[3] ++;
    r3.i = (qp & 0xffff);
    r3.i = r3.i | (((uint32_t)qp >> 16) << 16);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, false, false);
    r2.i = r3.i - (1);
    r3.i = (qp & 0xffff);
    r3.i = r3.i | (((uint32_t)qp >> 16) << 16);
    store_counter ++;
    str(&r2.i, &r3.i, 0, 4, false, false, false);
    r3.i = (qp & 0xffff);
    r3.i = r3.i | (((uint32_t)qp >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &r3.i, 0, 4, false, false, false);
    r3.i = (q & 0xffff);
    r3.i = r3.i | (((uint32_t)q >> 16) << 16);
    load_counter ++;
    ldr(&r3.i, &r3.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    r0.i = r3.i;
    load_counter ++;
    ldr(&fp.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;

}

void queue_has_something()
{
    counters[4] ++;
    store_counter ++;
    str(&fp.i, &sp.i, -4, 4, true, false, false);
    fp.i = sp.i + (0);
    r3.i = (qp & 0xffff);
    r3.i = r3.i | (((uint32_t)qp >> 16) << 16);
    load_counter ++;
    ldr(&r3.i, &r3.i, 0, 4, false, false, false);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z && n == v)
    {
        r3.i = 1;
    }
    if (z || n != v)
    {
        r3.i = 0;
    }
    r3.i = 0xff & (uint8_t)r3.i;
    r0.i = r3.i;
    sp.i = fp.i + (0);
    load_counter ++;
    ldr(&fp.i, &sp.i, 4, 4, false, true, false);
    return;

}

void dijkstra()
{
    counters[5] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&fp.i, &sp.i, 0, 4, false, false, false);
    fp.i = sp.i + (4);
    sp.i = sp.i - (16);
    store_counter ++;
    str(&r0.i, &fp.i, -16, 4, false, false, false);
    r3.i = (dist & 0xffff);
    r3.i = r3.i | (((uint32_t)dist >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &fp.i, -16, 4, false, false, false);
    r1.i = 0;
    store_counter ++;
    str(&r1.i, &r3.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
    goto L9;
L11:
    counters[6] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -8, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false, false);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (z)
    {
        goto L10;
    }
    counters[7] ++;
    r3.i = (dist & 0xffff);
    r3.i = r3.i | (((uint32_t)dist >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &fp.i, -8, 4, false, false, false);
    r1.i = 999;
    store_counter ++;
    str(&r1.i, &r3.i, ((uint32_t)r2.i << 2), 4, false, false, false);
L10:
    counters[8] ++;
    load_counter ++;
    ldr(&r0.i, &fp.i, -8, 4, false, false, false);
    enqueue();
    counters[9] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = r3.i + (1);
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
L9:
    counters[10] ++;
    r3.i = (V & 0xffff);
    r3.i = r3.i | (((uint32_t)V >> 16) << 16);
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
        goto L11;
    }
    counters[11] ++;
    goto L12;
L16:
    counters[12] ++;
    dequeue();
    counters[13] ++;
    store_counter ++;
    str(&r0.i, &fp.i, -12, 4, false, false, false);
    r3.i = (vp & 0xffff);
    r3.i = r3.i | (((uint32_t)vp >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &r3.i, 0, 4, false, false, false);
    r1.i = r2.i + (1);
    r3.i = (vp & 0xffff);
    r3.i = r3.i | (((uint32_t)vp >> 16) << 16);
    store_counter ++;
    str(&r1.i, &r3.i, 0, 4, false, false, false);
    r3.i = (visited & 0xffff);
    r3.i = r3.i | (((uint32_t)visited >> 16) << 16);
    load_counter ++;
    ldr(&r1.i, &fp.i, -12, 4, false, false, false);
    store_counter ++;
    str(&r1.i, &r3.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
    goto L13;
L15:
    counters[14] ++;
    r3.i = (mat & 0xffff);
    r3.i = r3.i | (((uint32_t)mat >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &fp.i, -12, 4, false, false, false);
    r1.i = 20;
    r1.i = (r1.i) * (r2.i);
    load_counter ++;
    ldr(&r2.i, &fp.i, -8, 4, false, false, false);
    r2.i = r1.i + (r2.i);
    load_counter ++;
    ldr(&r3.i, &r3.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L14;
    }
    counters[15] ++;
    r3.i = (dist & 0xffff);
    r3.i = r3.i | (((uint32_t)dist >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &fp.i, -8, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &r3.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    r3.i = (dist & 0xffff);
    r3.i = r3.i | (((uint32_t)dist >> 16) << 16);
    load_counter ++;
    ldr(&r1.i, &fp.i, -12, 4, false, false, false);
    load_counter ++;
    ldr(&r1.i, &r3.i, ((uint32_t)r1.i << 2), 4, false, false, false);
    r3.i = (mat & 0xffff);
    r3.i = r3.i | (((uint32_t)mat >> 16) << 16);
    load_counter ++;
    ldr(&r0.i, &fp.i, -12, 4, false, false, false);
    ip.i = 20;
    ip.i = (ip.i) * (r0.i);
    load_counter ++;
    ldr(&r0.i, &fp.i, -8, 4, false, false, false);
    r0.i = ip.i + (r0.i);
    load_counter ++;
    ldr(&r3.i, &r3.i, ((uint32_t)r0.i << 2), 4, false, false, false);
    r3.i = r1.i + (r3.i);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (z || n != v)
    {
        goto L14;
    }
    counters[16] ++;
    r3.i = (dist & 0xffff);
    r3.i = r3.i | (((uint32_t)dist >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &fp.i, -12, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &r3.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    r3.i = (mat & 0xffff);
    r3.i = r3.i | (((uint32_t)mat >> 16) << 16);
    load_counter ++;
    ldr(&r1.i, &fp.i, -12, 4, false, false, false);
    r0.i = 20;
    r0.i = (r0.i) * (r1.i);
    load_counter ++;
    ldr(&r1.i, &fp.i, -8, 4, false, false, false);
    r1.i = r0.i + (r1.i);
    load_counter ++;
    ldr(&r3.i, &r3.i, ((uint32_t)r1.i << 2), 4, false, false, false);
    r1.i = r2.i + (r3.i);
    r3.i = (dist & 0xffff);
    r3.i = r3.i | (((uint32_t)dist >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &fp.i, -8, 4, false, false, false);
    store_counter ++;
    str(&r1.i, &r3.i, ((uint32_t)r2.i << 2), 4, false, false, false);
L14:
    counters[17] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = r3.i + (1);
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
L13:
    counters[18] ++;
    r3.i = (V & 0xffff);
    r3.i = r3.i | (((uint32_t)V >> 16) << 16);
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
        goto L15;
    }
L12:
    counters[19] ++;
    queue_has_something();
    counters[20] ++;
    r3.i = r0.i;
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L16;
    }
    counters[21] ++;
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
    counters[22] ++;
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
    r0.i = (LC0 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC0 >> 16) << 16);
    printf_help(malloc_0+r0.i, r1.i);
    counters[23] ++;
    r1.i = (V & 0xffff);
    r1.i = r1.i | (((uint32_t)V >> 16) << 16);
    r0.i = (LC1 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC1 >> 16) << 16);
    scanf_help();
    counters[24] ++;
    r0.i = (LC2 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC2 >> 16) << 16);
    printf_help(malloc_0+r0.i, r1.i);
    counters[25] ++;
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
    goto L18;
L21:
    counters[26] ++;
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false, false);
    goto L19;
L20:
    counters[27] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r2.i = 20;
    r2.i = (r2.i) * (r3.i);
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false, false);
    r3.i = r2.i + (r3.i);
    r2.i = (uint32_t)r3.i << 2;
    r3.i = (mat & 0xffff);
    r3.i = r3.i | (((uint32_t)mat >> 16) << 16);
    r3.i = r2.i + (r3.i);
    r1.i = r3.i;
    r0.i = (LC1 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC1 >> 16) << 16);
    scanf_help();
    counters[28] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false, false);
    r3.i = r3.i + (1);
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false, false);
L19:
    counters[29] ++;
    r3.i = (V & 0xffff);
    r3.i = r3.i | (((uint32_t)V >> 16) << 16);
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
        goto L20;
    }
    counters[30] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = r3.i + (1);
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
L18:
    counters[31] ++;
    r3.i = (V & 0xffff);
    r3.i = r3.i | (((uint32_t)V >> 16) << 16);
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
        goto L21;
    }
    counters[32] ++;
    r0.i = 0;
    dijkstra();
    counters[33] ++;
    r0.i = (LC3 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC3 >> 16) << 16);
    printf_help("%s\n", r0.i);
    counters[34] ++;
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
    goto L22;
L23:
    counters[35] ++;
    r3.i = (dist & 0xffff);
    r3.i = r3.i | (((uint32_t)dist >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &fp.i, -8, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &r3.i, ((uint32_t)r2.i << 2), 4, false, false, false);
    r2.i = r3.i;
    load_counter ++;
    ldr(&r1.i, &fp.i, -8, 4, false, false, false);
    r0.i = (LC4 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC4 >> 16) << 16);
    printf_help(malloc_0+r0.i, r1.i);
    counters[36] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false, false);
    r3.i = r3.i + (1);
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false, false);
L22:
    counters[37] ++;
    r3.i = (V & 0xffff);
    r3.i = r3.i | (((uint32_t)V >> 16) << 16);
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
        goto L23;
    }
    counters[38] ++;
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

