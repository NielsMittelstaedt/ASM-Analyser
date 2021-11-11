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

reg sp, fp, lr, pc, ip;
int32_t cond_reg;
char* malloc_0 = 0;
bool carry;

reg r5, r2, r7, r6, r10, r9, r1, r3, r4, r0, r8;

int32_t LC1, LC0;

int counters[27] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[27] = {8,3,7,2,4,2,3,2,3,5,5,2,6,3,7,2,7,2,5,2,3,2,1,16,4,2,3};

void ldr(int32_t *target, int32_t *address, int32_t offset, bool byte, bool update, bool post_index)
{
    int bytes = 1;
    char *ptr;
    ptr = malloc_0 + *address;
    *target = 0;

    if (!post_index)
        ptr += offset;

    if (!byte)
        bytes = 4;

    for(int j=0; j<bytes; j++)
        *target += (*(ptr+j) << 8*j) & (0xff << 8*j);

    if (update || post_index)
        *address += offset;
}

void str(int32_t *target, int32_t *address, int32_t offset, bool byte, bool update, bool post_index)
{
    int bytes = 1;
    char *ptr;
    ptr = malloc_0 + *address;

    if (!post_index)
        ptr += offset;

    if (!byte)
        bytes = 4;

    for(int j=0; j<bytes; j++)
        *(ptr+j) = (*target >> (8*j)) & 0xff;

    if(update || post_index)
        *address += offset;
}

void malloc_start()
{
    malloc_0 = (char*) malloc(1);
    char* stack_ptr = (char*) malloc(1000);
    sp.i = (int32_t) (stack_ptr - malloc_0) + 999;
    fp = sp;

    LC1 = (int32_t) ((char*) malloc(9) - malloc_0);
    strcpy(malloc_0+LC1, "%d \000");

    LC0 = (int32_t) ((char*) malloc(6*sizeof(int32_t)) - malloc_0);
    int32_t arrayLC0[] = {5,3,9,2,6,1};
    for(int i=0; i<6; i++) str(&arrayLC0[i], &LC0, i*4, false, false, false);
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
    char* ptr = (char*) malloc(r0.i);
    r0.i = (int32_t) (ptr - malloc_0);
}
void free_help()
{
    free(malloc_0+r0.i);
}

void mergeSortpart0()
{
    counters[0] ++;
    store_counter ++;
    sp.i -= 40;
    str(&r3.i, &sp.i, 0*4, false, false, false);
    str(&r4.i, &sp.i, 1*4, false, false, false);
    str(&r5.i, &sp.i, 2*4, false, false, false);
    str(&r6.i, &sp.i, 3*4, false, false, false);
    str(&r7.i, &sp.i, 4*4, false, false, false);
    str(&r8.i, &sp.i, 5*4, false, false, false);
    str(&r9.i, &sp.i, 6*4, false, false, false);
    str(&r10.i, &sp.i, 7*4, false, false, false);
    str(&fp.i, &sp.i, 8*4, false, false, false);
    str(&lr.i, &sp.i, 9*4, false, false, false);
    r8.i = (uint32_t)r1.i >> 1;
    fp.i = r0.i;
    r7.i = r1.i - ((uint32_t)r1.i >> 1);
    r4.i = (uint32_t)r8.i << 2;
    r5.i = (uint32_t)r7.i << 2;
    r0.i = r4.i;
    malloc_help();
    counters[1] ++;
    r9.i = r0.i;
    r0.i = r5.i;
    malloc_help();
    counters[2] ++;
    cond_reg = r8.i > 0 ? 1 : (r8.i < 0 ? -1 : 0);
    r1.i = fp.i;
    if (cond_reg > 0)
    {
        r2.i = r4.i;
    }
    if (cond_reg <= 0)
    {
        r2.i = 4;
    }
    r10.i = r0.i;
    r0.i = r9.i;
    memcpy();
    counters[3] ++;
    cond_reg = r7.i > 0 ? 1 : (r7.i < 0 ? -1 : 0);
    if (cond_reg <= 0)
    {
        goto L5;
    }
    counters[4] ++;
    r1.i = fp.i + r4.i;
    r2.i = r5.i;
    r0.i = r10.i;
    memcpy();
L5:
    counters[5] ++;
    cond_reg = r8.i > 1 ? 1 : (r8.i < 1 ? -1 : 0);
    if (cond_reg == 0)
    {
        goto L3;
    }
    counters[6] ++;
    r1.i = r8.i;
    r0.i = r9.i;
    mergeSortpart0();
L3:
    counters[7] ++;
    cond_reg = r7.i > 1 ? 1 : (r7.i < 1 ? -1 : 0);
    if (cond_reg <= 0)
    {
        goto L6;
    }
    counters[8] ++;
    r1.i = r7.i;
    r0.i = r10.i;
    mergeSortpart0();
L6:
    counters[9] ++;
    cond_reg = r7.i > 0 ? 1 : (r7.i < 0 ? -1 : 0);
    if (cond_reg <= 0)
    {
        r4.i = 0;
    }
    if (cond_reg <= 0)
    {
        r5.i = r4.i;
    }
    if (cond_reg <= 0)
    {
        r6.i = r4.i;
    }
    if (cond_reg <= 0)
    {
        goto L8;
    }
    counters[10] ++;
    load_counter ++;
    ldr(&r2.i, &r9.i, 0, false, false, true);
    r4.i = 0;
    load_counter ++;
    ldr(&r3.i, &r10.i, 0, false, false, true);
    r6.i = r4.i;
    r5.i = r4.i;
L7:
    counters[11] ++;
    cond_reg = r2.i > r3.i ? 1 : (r2.i < r3.i ? -1 : 0);
    if (cond_reg > 0)
    {
        goto L10;
    }
L26:
    counters[12] ++;
    r5.i = r5.i + 1;
    store_counter ++;
    str(&r2.i, &fp.i, ((uint32_t)r4.i << 2), false, false, false);
    cond_reg = r8.i > r5.i ? 1 : (r8.i < r5.i ? -1 : 0);
    if (cond_reg > 0)
    {
        cond_reg = r7.i > r6.i ? 1 : (r7.i < r6.i ? -1 : 0);
    }
    r4.i = r4.i + 1;
    if (cond_reg <= 0)
    {
        goto L12;
    }
    counters[13] ++;
    load_counter ++;
    ldr(&r2.i, &r9.i, ((uint32_t)r5.i << 2), false, false, false);
    cond_reg = r2.i > r3.i ? 1 : (r2.i < r3.i ? -1 : 0);
    if (cond_reg <= 0)
    {
        goto L26;
    }
L10:
    counters[14] ++;
    r6.i = r6.i + 1;
    store_counter ++;
    str(&r3.i, &fp.i, ((uint32_t)r4.i << 2), false, false, false);
    cond_reg = r8.i > r5.i ? 1 : (r8.i < r5.i ? -1 : 0);
    if (cond_reg > 0)
    {
        cond_reg = r7.i > r6.i ? 1 : (r7.i < r6.i ? -1 : 0);
    }
    r4.i = r4.i + 1;
    load_counter ++;
    if (cond_reg > 0)
    {
        ldr(&r3.i, &r10.i, ((uint32_t)r6.i << 2), false, false, false);
    }
    if (cond_reg > 0)
    {
        goto L7;
    }
L12:
    counters[15] ++;
    cond_reg = r8.i > r5.i ? 1 : (r8.i < r5.i ? -1 : 0);
    if (cond_reg <= 0)
    {
        goto L9;
    }
L8:
    counters[16] ++;
    r2.i = r8.i - r5.i;
    r0.i = fp.i + ((uint32_t)r4.i << 2);
    r1.i = r9.i + ((uint32_t)r5.i << 2);
    r4.i = r8.i + r4.i;
    r2.i = (uint32_t)r2.i << 2;
    r4.i = r4.i - r5.i;
    memcpy();
L9:
    counters[17] ++;
    cond_reg = r7.i > r6.i ? 1 : (r7.i < r6.i ? -1 : 0);
    if (cond_reg <= 0)
    {
        goto L14;
    }
    counters[18] ++;
    r2.i = r7.i - r6.i;
    r1.i = r10.i + ((uint32_t)r6.i << 2);
    r0.i = fp.i + ((uint32_t)r4.i << 2);
    r2.i = (uint32_t)r2.i << 2;
    memcpy();
L14:
    counters[19] ++;
    r0.i = r9.i;
    free_help();
    counters[20] ++;
    r0.i = r10.i;
    load_counter ++;
    ldr(&r3.i, &sp.i, 0*4, false, false, false);
    ldr(&r4.i, &sp.i, 1*4, false, false, false);
    ldr(&r5.i, &sp.i, 2*4, false, false, false);
    ldr(&r6.i, &sp.i, 3*4, false, false, false);
    ldr(&r7.i, &sp.i, 4*4, false, false, false);
    ldr(&r8.i, &sp.i, 5*4, false, false, false);
    ldr(&r9.i, &sp.i, 6*4, false, false, false);
    ldr(&r10.i, &sp.i, 7*4, false, false, false);
    ldr(&fp.i, &sp.i, 8*4, false, false, false);
    ldr(&lr.i, &sp.i, 9*4, false, false, false);
    sp.i += 40;
    free_help();
    return;
}

void mergeSort()
{
    counters[21] ++;
    cond_reg = r1.i > 1 ? 1 : (r1.i < 1 ? -1 : 0);
    if (cond_reg <= 0)
    {
        return;
    }
    counters[22] ++;
    goto mergeSortpart0;
    return;
}

void main()
{
    malloc_start();
    counters[23] ++;
    ip.i = (LC0 & 0xffff);
    ip.i = ip.i | (((uint32_t)LC0 >> 16) << 16);
    store_counter ++;
    sp.i -= 16;
    str(&r4.i, &sp.i, 0*4, false, false, false);
    str(&r5.i, &sp.i, 1*4, false, false, false);
    str(&r6.i, &sp.i, 2*4, false, false, false);
    str(&lr.i, &sp.i, 3*4, false, false, false);
    sp.i = sp.i - 24;
    load_counter ++;
    ldr(&r0.i, &ip.i, 0*4, false, false, false);
    ldr(&r1.i, &ip.i, 1*4, false, false, false);
    ldr(&r2.i, &ip.i, 2*4, false, false, false);
    ldr(&r3.i, &ip.i, 3*4, false, false, false);
    ip.i += 16;
    lr.i = sp.i;
    r5.i = (LC1 & 0xffff);
    r6.i = sp.i + 24;
    r5.i = r5.i | (((uint32_t)LC1 >> 16) << 16);
    r4.i = sp.i;
    store_counter ++;
    str(&r0.i, &lr.i, 0*4, false, false, false);
    str(&r1.i, &lr.i, 1*4, false, false, false);
    str(&r2.i, &lr.i, 2*4, false, false, false);
    str(&r3.i, &lr.i, 3*4, false, false, false);
    lr.i += 16;
    load_counter ++;
    ldr(&r0.i, &ip.i, 0*4, false, false, false);
    ldr(&r1.i, &ip.i, 1*4, false, false, false);
    store_counter ++;
    str(&r0.i, &lr.i, 0*4, false, false, false);
    str(&r1.i, &lr.i, 1*4, false, false, false);
    r0.i = sp.i;
    r1.i = 6;
    mergeSortpart0();
L30:
    counters[24] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 4, false, false, true);
    r1.i = r5.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[25] ++;
    cond_reg = r4.i > r6.i ? 1 : (r4.i < r6.i ? -1 : 0);
    if (cond_reg != 0)
    {
        goto L30;
    }
    counters[26] ++;
    r0.i = 0;
    sp.i = sp.i + 24;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, false, false, false);
    ldr(&r5.i, &sp.i, 1*4, false, false, false);
    ldr(&r6.i, &sp.i, 2*4, false, false, false);
    ldr(&pc.i, &sp.i, 3*4, false, false, false);
    sp.i += 16;
    counter_summary();
    return;

}

