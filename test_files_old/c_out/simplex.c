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

reg r4, r2, r8, r9, r3, r7, r10, r0, r5, r6, r1;

int32_t LC1, LC2, L40, L59, LC3, LC4, LC5, LC6, L121, TempState, SimplexTable, LC0;

int counters[234] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[234] = {9,7,6,2,5,9,5,5,9,1,4,2,3,3,11,4,4,8,4,7,4,7,4,7,4,8,1,4,2,3,3,37,8,6,8,3,7,2,5,2,1,4,2,3,3,2,5,7,5,5,12,1,4,2,3,3,11,4,4,8,4,7,4,7,4,7,4,8,1,4,2,3,3,38,8,6,8,3,7,2,5,2,1,4,2,3,3,2,4,2,4,2,11,5,5,5,6,8,2,1,4,2,3,3,9,7,5,9,4,6,4,6,4,6,4,8,1,4,2,3,3,38,8,6,8,3,7,2,4,1,5,2,1,4,2,3,3,2,9,4,5,5,5,5,5,5,8,2,5,6,5,5,5,5,5,5,8,5,7,5,5,7,5,12,4,5,7,6,7,5,4,6,2,4,1,2,4,6,5,5,7,5,5,7,9,7,4,7,4,7,4,7,4,7,4,2,5,4,4,7,4,7,4,7,4,7,4,2,7,16,7,17,7,3,1,4,2,3,2,1,7,40,1,1,4,2,3,2,2,2,1,1,1,2};


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
    malloc_0 = (uint8_t*) malloc(20434);
    sp.i = 19996;
    fp = sp;
    LC1 = 20000;
    strcpy(malloc_0+LC1, "\012------------------Simplex Table Step = %d------");

    LC2 = 20053;
    strcpy(malloc_0+LC2, "%10lf \000");

    TempState = 20065;
    SimplexTable = 20105;
    L40 = 20225;
    int32_t arrayL40[] = {SimplexTable};
    for(int i=0; i<1; i++) str(&arrayL40[i], &L40, i*4, 4, false, false, false);

    LC3 = 20229;
    strcpy(malloc_0+LC3, "\012***** Result *****\000");

    LC4 = 20257;
    strcpy(malloc_0+LC4, "x1 = %lf, \000");

    LC5 = 20273;
    strcpy(malloc_0+LC5, "x2 = %lf, \000");

    LC6 = 20289;
    strcpy(malloc_0+LC6, "f = %lf\012\000");

    L59 = 20306;
    int32_t arrayL59[] = {SimplexTable};
    for(int i=0; i<1; i++) str(&arrayL59[i], &L59, i*4, 4, false, false, false);

    L121 = 20310;
    int32_t arrayL121[] = {SimplexTable};
    for(int i=0; i<1; i++) str(&arrayL121[i], &L121, i*4, 4, false, false, false);

    LC0 = 20314;
    int32_t arrayLC0[] = {0,1077739520,0,1078362112,0,0,0,0,0,0,0,1073741824,0,1075838976,0,1072693248,0,0,0,1078853632,0,1074790400,0,1074790400,0,0,0,1072693248,0,1078853632};
    for(int i=0; i<30; i++) str(&arrayLC0[i], &LC0, i*4, 4, false, false, false);

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "simplex.c";

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

void X2Calc();
void X1Calc();
void Result();
void Maxim();
void GaussCalc();
void Exchange();
void ShowTable();
void Input();
void main();

void dcmpeq()
{
    uint64_t op1 = ((uint64_t)(uint32_t) r1.i) << 32 | ((uint64_t)(uint32_t) r0.i);
    uint64_t op2 = ((uint64_t)(uint32_t) r3.i) << 32 | ((uint64_t)(uint32_t) r2.i);
    r0.i = *(double *)&op1 == *(double *)&op2;
}
void dsub()
{
    uint64_t op1 = ((uint64_t)(uint32_t) r1.i) << 32 | ((uint64_t)(uint32_t) r0.i);
    uint64_t op2 = ((uint64_t)(uint32_t) r3.i) << 32 | ((uint64_t)(uint32_t) r2.i);
    double result = *(double *)&op1 - *(double *)&op2;
    uint64_t result_uint64 = *(uint64_t *)&result;
    r1.i = (uint32_t) (result_uint64 >> 32);
    r0.i = (uint32_t) result_uint64;
}
void dmul()
{
    uint64_t op1 = ((uint64_t)(uint32_t) r1.i) << 32 | ((uint64_t)(uint32_t) r0.i);
    uint64_t op2 = ((uint64_t)(uint32_t) r3.i) << 32 | ((uint64_t)(uint32_t) r2.i);
    double result = *(double *)&op1 * *(double *)&op2;
    uint64_t result_uint64 = *(uint64_t *)&result;
    r1.i = (uint32_t) (result_uint64 >> 32);
    r0.i = (uint32_t) result_uint64;
}
void ddiv()
{
    uint64_t op1 = ((uint64_t)(uint32_t) r1.i) << 32 | ((uint64_t)(uint32_t) r0.i);
    uint64_t op2 = ((uint64_t)(uint32_t) r3.i) << 32 | ((uint64_t)(uint32_t) r2.i);
    double result = *(double *)&op1 / *(double *)&op2;
    uint64_t result_uint64 = *(uint64_t *)&result;
    r1.i = (uint32_t) (result_uint64 >> 32);
    r0.i = (uint32_t) result_uint64;
}
void memcpy_help()
{
    memcpy(malloc_0+r0.i, malloc_0+r1.i, r2.i);
}
void dcmplt()
{
    uint64_t op1 = ((uint64_t)(uint32_t) r1.i) << 32 | ((uint64_t)(uint32_t) r0.i);
    uint64_t op2 = ((uint64_t)(uint32_t) r3.i) << 32 | ((uint64_t)(uint32_t) r2.i);
    r0.i = *(double *)&op1 < *(double *)&op2;
}
void dadd()
{
    uint64_t op1 = ((uint64_t)(uint32_t) r1.i) << 32 | ((uint64_t)(uint32_t) r0.i);
    uint64_t op2 = ((uint64_t)(uint32_t) r3.i) << 32 | ((uint64_t)(uint32_t) r2.i);
    double result = *(double *)&op1 + *(double *)&op2;
    uint64_t result_uint64 = *(uint64_t *)&result;
    r1.i = (uint32_t) (result_uint64 >> 32);
    r0.i = (uint32_t) result_uint64;
}

void X2Calc()
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
    fp.i = (SimplexTable & 0xffff);
    fp.i = fp.i | (((uint32_t)SimplexTable >> 16) << 16);
    sp.i = sp.i - (28);
    load_counter ++;
    ldr(&r8.i, &fp.i, 48, 4, false, false, false);
    ldr(&r9.i, &fp.i, 52, 4, false, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, 72, 4, false, false, false);
    ldr(&r1.i, &fp.i, 76, 4, false, false, false);
    r2.i = r8.i;
    r3.i = r9.i;
    ddiv();
    counters[1] ++;
    load_counter ++;
    ldr(&r6.i, &fp.i, 88, 4, false, false, false);
    ldr(&r7.i, &fp.i, 92, 4, false, false, false);
    r2.i = r6.i;
    r3.i = r7.i;
    r4.i = r0.i;
    r5.i = r1.i;
    load_counter ++;
    ldr(&r0.i, &fp.i, 112, 4, false, false, false);
    ldr(&r1.i, &fp.i, 116, 4, false, false, false);
    ddiv();
    counters[2] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r4.i;
    r1.i = r5.i;
    store_counter ++;
    str(&r2.i, &sp.i, 0, 4, false, false, false);
    str(&r3.i, &sp.i, 4, 4, false, false, false);
    dcmplt();
    counters[3] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (z)
    {
        goto L34;
    }
    counters[4] ++;
    r2.i = r8.i;
    r3.i = r9.i;
    load_counter ++;
    ldr(&r0.i, &fp.i, 40, 4, false, false, false);
    ldr(&r1.i, &fp.i, 44, 4, false, false, false);
    r10.i = fp.i + (40);
    ddiv();
    counters[5] ++;
    r2.i = r8.i;
    r3.i = r9.i;
    r7.i = (LC2 & 0xffff);
    r6.i = r10.i;
    r7.i = r7.i | (((uint32_t)LC2 >> 16) << 16);
    store_counter ++;
    str(&r0.i, &fp.i, 40, 4, false, false, false);
    str(&r1.i, &fp.i, 44, 4, false, false, false);
    r0.i = r8.i;
    r1.i = r9.i;
    ddiv();
    counters[6] ++;
    r2.i = r8.i;
    r3.i = r9.i;
    store_counter ++;
    str(&r0.i, &fp.i, 48, 4, false, false, false);
    str(&r1.i, &fp.i, 52, 4, false, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, 56, 4, false, false, false);
    ldr(&r1.i, &fp.i, 60, 4, false, false, false);
    ddiv();
    counters[7] ++;
    r2.i = r8.i;
    r3.i = r9.i;
    store_counter ++;
    str(&r0.i, &fp.i, 56, 4, false, false, false);
    str(&r1.i, &fp.i, 60, 4, false, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, 64, 4, false, false, false);
    ldr(&r1.i, &fp.i, 68, 4, false, false, false);
    ddiv();
    counters[8] ++;
    r2.i = 1;
    store_counter ++;
    str(&r4.i, &fp.i, 72, 4, false, false, false);
    str(&r5.i, &fp.i, 76, 4, false, false, false);
    r8.i = r0.i;
    r9.i = r1.i;
    r0.i = r2.i;
    r1.i = (LC1 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC1 >> 16) << 16);
    store_counter ++;
    str(&r8.i, &fp.i, 64, 4, false, false, false);
    str(&r9.i, &fp.i, 68, 4, false, false, false);
    printf(malloc_0+r1.i, r2.i);
L4:
    counters[9] ++;
    r4.i = r6.i - (40);
L5:
    counters[10] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 8, 4, false, true, false);
    ldr(&r3.i, &r4.i, 12, 4, false, true, false);
    r1.i = r7.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[11] ++;
    tmp = r4.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r6.i);
    v = (r4.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        goto L5;
    }
    counters[12] ++;
    r0.i = 10;
    r6.i = r4.i + (40);
    printf("%c", (char)r0.i);
    counters[13] ++;
    load_counter ++;
    ldr(&r3.i, &L40, 0, 4, false, false, false);
    tmp = r3.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r6.i);
    v = (r3.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L4;
    }
    counters[14] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, 88, 4, false, false, false);
    ldr(&r3.i, &fp.i, 92, 4, false, false, false);
    r5.i = (LC2 & 0xffff);
    load_counter ++;
    ldr(&r6.i, &fp.i, 48, 4, false, false, false);
    ldr(&r7.i, &fp.i, 52, 4, false, false, false);
    r5.i = r5.i | (((uint32_t)LC2 >> 16) << 16);
    r4.i = r10.i;
    store_counter ++;
    str(&r2.i, &sp.i, 0, 4, false, false, false);
    str(&r3.i, &sp.i, 4, 4, false, false, false);
    r0.i = r2.i;
    r1.i = r3.i;
    r2.i = r6.i;
    r3.i = r7.i;
    ddiv();
    counters[15] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, 40, 4, false, false, false);
    ldr(&r3.i, &fp.i, 44, 4, false, false, false);
    r8.i = r0.i;
    r9.i = r1.i;
    dmul();
    counters[16] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    load_counter ++;
    ldr(&r0.i, &fp.i, 80, 4, false, false, false);
    ldr(&r1.i, &fp.i, 84, 4, false, false, false);
    dsub();
    counters[17] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r6.i;
    store_counter ++;
    str(&r2.i, &fp.i, 80, 4, false, false, false);
    str(&r3.i, &fp.i, 84, 4, false, false, false);
    r1.i = r7.i;
    r2.i = r8.i;
    r3.i = r9.i;
    dmul();
    counters[18] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    load_counter ++;
    ldr(&r0.i, &sp.i, 0, 4, false, false, false);
    ldr(&r1.i, &sp.i, 4, 4, false, false, false);
    dsub();
    counters[19] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, 56, 4, false, false, false);
    ldr(&r3.i, &fp.i, 60, 4, false, false, false);
    r6.i = r0.i;
    r7.i = r1.i;
    r0.i = r8.i;
    store_counter ++;
    str(&r6.i, &fp.i, 88, 4, false, false, false);
    str(&r7.i, &fp.i, 92, 4, false, false, false);
    r1.i = r9.i;
    dmul();
    counters[20] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    load_counter ++;
    ldr(&r0.i, &fp.i, 96, 4, false, false, false);
    ldr(&r1.i, &fp.i, 100, 4, false, false, false);
    dsub();
    counters[21] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, 64, 4, false, false, false);
    ldr(&r3.i, &fp.i, 68, 4, false, false, false);
    r6.i = r0.i;
    r7.i = r1.i;
    r0.i = r8.i;
    store_counter ++;
    str(&r6.i, &fp.i, 96, 4, false, false, false);
    str(&r7.i, &fp.i, 100, 4, false, false, false);
    r1.i = r9.i;
    dmul();
    counters[22] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    load_counter ++;
    ldr(&r0.i, &fp.i, 104, 4, false, false, false);
    ldr(&r1.i, &fp.i, 108, 4, false, false, false);
    dsub();
    counters[23] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, 72, 4, false, false, false);
    ldr(&r3.i, &fp.i, 76, 4, false, false, false);
    r6.i = r0.i;
    r7.i = r1.i;
    r0.i = r8.i;
    store_counter ++;
    str(&r6.i, &fp.i, 104, 4, false, false, false);
    str(&r7.i, &fp.i, 108, 4, false, false, false);
    r1.i = r9.i;
    dmul();
    counters[24] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    load_counter ++;
    ldr(&r0.i, &fp.i, 112, 4, false, false, false);
    ldr(&r1.i, &fp.i, 116, 4, false, false, false);
    dsub();
    counters[25] ++;
    r2.i = 2;
    r6.i = r0.i;
    r7.i = r1.i;
    r0.i = 1;
    r1.i = (LC1 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC1 >> 16) << 16);
    store_counter ++;
    str(&r6.i, &fp.i, 112, 4, false, false, false);
    str(&r7.i, &fp.i, 116, 4, false, false, false);
    printf(malloc_0+r1.i, r2.i);
L7:
    counters[26] ++;
    r6.i = r4.i - (40);
L8:
    counters[27] ++;
    load_counter ++;
    ldr(&r2.i, &r6.i, 8, 4, false, true, false);
    ldr(&r3.i, &r6.i, 12, 4, false, true, false);
    r1.i = r5.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[28] ++;
    tmp = r6.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) r4.i);
    v = (r6.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    if (!z)
    {
        goto L8;
    }
    counters[29] ++;
    r0.i = 10;
    r4.i = r6.i + (40);
    printf("%c", (char)r0.i);
    counters[30] ++;
    load_counter ++;
    ldr(&r3.i, &L40, 0, 4, false, false, false);
    tmp = r3.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r4.i);
    v = (r3.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L7;
    }
    counters[31] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, 44, 4, false, false, false);
    ip.i = (TempState & 0xffff);
    load_counter ++;
    ldr(&r5.i, &fp.i, 40, 4, false, false, false);
    ip.i = ip.i | (((uint32_t)TempState >> 16) << 16);
    r3.i = r3.i + (-2147483648);
    store_counter ++;
    str(&r3.i, &sp.i, 12, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &sp.i, 12, 4, false, false, false);
    load_counter ++;
    ldr(&r1.i, &fp.i, 60, 4, false, false, false);
    r2.i = r5.i;
    load_counter ++;
    ldr(&r0.i, &fp.i, 56, 4, false, false, false);
    store_counter ++;
    str(&r2.i, &ip.i, 0, 4, false, false, false);
    str(&r3.i, &ip.i, 4, 4, false, false, false);
    lr.i = r1.i + (-2147483648);
    load_counter ++;
    ldr(&r2.i, &fp.i, 72, 4, false, false, false);
    ldr(&r3.i, &fp.i, 76, 4, false, false, false);
    load_counter ++;
    ldr(&r1.i, &fp.i, 64, 4, false, false, false);
    r7.i = lr.i;
    r6.i = r0.i;
    load_counter ++;
    ldr(&r4.i, &fp.i, 68, 4, false, false, false);
    store_counter ++;
    str(&r2.i, &sp.i, 0, 4, false, false, false);
    str(&r3.i, &sp.i, 4, 4, false, false, false);
    r3.i = lr.i;
    load_counter ++;
    ldr(&lr.i, &fp.i, 48, 4, false, false, false);
    r2.i = r6.i;
    store_counter ++;
    str(&r1.i, &sp.i, 16, 4, false, false, false);
    r4.i = r4.i + (-2147483648);
    load_counter ++;
    ldr(&r8.i, &fp.i, 8, 4, false, false, false);
    ldr(&r9.i, &fp.i, 12, 4, false, false, false);
    store_counter ++;
    str(&r6.i, &ip.i, 16, 4, false, false, false);
    str(&r7.i, &ip.i, 20, 4, false, false, false);
    r1.i = r4.i;
    load_counter ++;
    ldr(&r0.i, &sp.i, 16, 4, false, false, false);
    load_counter ++;
    ldr(&r6.i, &sp.i, 0, 4, false, false, false);
    ldr(&r7.i, &sp.i, 4, 4, false, false, false);
    store_counter ++;
    str(&lr.i, &ip.i, 8, 4, false, false, false);
    load_counter ++;
    ldr(&lr.i, &fp.i, 52, 4, false, false, false);
    store_counter ++;
    str(&r0.i, &ip.i, 24, 4, false, false, false);
    str(&r1.i, &ip.i, 28, 4, false, false, false);
    r0.i = r8.i;
    lr.i = lr.i + (-2147483648);
    store_counter ++;
    str(&r6.i, &ip.i, 32, 4, false, false, false);
    str(&r7.i, &ip.i, 36, 4, false, false, false);
    store_counter ++;
    str(&lr.i, &ip.i, 12, 4, false, false, false);
    r1.i = r9.i;
    dmul();
    counters[32] ++;
    load_counter ++;
    ldr(&r6.i, &fp.i, 32, 4, false, false, false);
    ldr(&r7.i, &fp.i, 36, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &sp.i, 16, 4, false, false, false);
    r3.i = r4.i;
    store_counter ++;
    str(&r6.i, &sp.i, 16, 4, false, false, false);
    str(&r7.i, &sp.i, 20, 4, false, false, false);
    store_counter ++;
    str(&r0.i, &fp.i, 16, 4, false, false, false);
    str(&r1.i, &fp.i, 20, 4, false, false, false);
    r0.i = r8.i;
    r1.i = r9.i;
    dmul();
    counters[33] ++;
    load_counter ++;
    ldr(&r2.i, &sp.i, 0, 4, false, false, false);
    ldr(&r3.i, &sp.i, 4, 4, false, false, false);
    load_counter ++;
    ldr(&r6.i, &fp.i, 0, 4, false, false, false);
    ldr(&r7.i, &fp.i, 4, 4, false, false, false);
    store_counter ++;
    str(&r0.i, &fp.i, 24, 4, false, false, false);
    str(&r1.i, &fp.i, 28, 4, false, false, false);
    r0.i = r8.i;
    r1.i = r9.i;
    dmul();
    counters[34] ++;
    r2.i = r5.i;
    load_counter ++;
    ldr(&r3.i, &sp.i, 12, 4, false, false, false);
    r4.i = r0.i;
    r5.i = r1.i;
    r0.i = r8.i;
    r1.i = r9.i;
    store_counter ++;
    str(&r4.i, &fp.i, 32, 4, false, false, false);
    str(&r5.i, &fp.i, 36, 4, false, false, false);
    dmul();
    counters[35] ++;
    r2.i = r6.i;
    r3.i = r7.i;
    dadd();
    counters[36] ++;
    r2.i = 0;
    r3.i = 0;
    store_counter ++;
    str(&r2.i, &fp.i, 8, 4, false, false, false);
    str(&r3.i, &fp.i, 12, 4, false, false, false);
    store_counter ++;
    str(&r0.i, &fp.i, 0, 4, false, false, false);
    str(&r1.i, &fp.i, 4, 4, false, false, false);
    r0.i = r4.i;
    r1.i = r5.i;
    dcmpeq();
    counters[37] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (z)
    {
        goto L38;
    }
L10:
    counters[38] ++;
    r1.i = (LC1 & 0xffff);
    r2.i = 3;
    r1.i = r1.i | (((uint32_t)LC1 >> 16) << 16);
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[39] ++;
    r5.i = (LC2 & 0xffff);
    r5.i = r5.i | (((uint32_t)LC2 >> 16) << 16);
L12:
    counters[40] ++;
    r4.i = r10.i - (40);
L13:
    counters[41] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 8, 4, false, true, false);
    ldr(&r3.i, &r4.i, 12, 4, false, true, false);
    r1.i = r5.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[42] ++;
    tmp = r10.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r10.i) >= ((uint32_t) r4.i);
    v = (r10.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r10.i&0x80000000);
    if (!z)
    {
        goto L13;
    }
    counters[43] ++;
    r0.i = 10;
    r10.i = r10.i + (40);
    printf("%c", (char)r0.i);
    counters[44] ++;
    load_counter ++;
    ldr(&r3.i, &L40, 0, 4, false, false, false);
    tmp = r3.i - r10.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r10.i);
    v = (r3.i&0x80000000) != (r10.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L12;
    }
    counters[45] ++;
    sp.i = sp.i + (28);
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
L34:
    counters[46] ++;
    r2.i = r6.i;
    r3.i = r7.i;
    load_counter ++;
    ldr(&r0.i, &fp.i, 80, 4, false, false, false);
    ldr(&r1.i, &fp.i, 84, 4, false, false, false);
    r10.i = fp.i + (40);
    ddiv();
    counters[47] ++;
    r2.i = r6.i;
    r3.i = r7.i;
    r5.i = r10.i;
    store_counter ++;
    str(&r0.i, &fp.i, 80, 4, false, false, false);
    str(&r1.i, &fp.i, 84, 4, false, false, false);
    r0.i = r6.i;
    r1.i = r7.i;
    ddiv();
    counters[48] ++;
    r2.i = r6.i;
    r3.i = r7.i;
    store_counter ++;
    str(&r0.i, &fp.i, 88, 4, false, false, false);
    str(&r1.i, &fp.i, 92, 4, false, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, 96, 4, false, false, false);
    ldr(&r1.i, &fp.i, 100, 4, false, false, false);
    ddiv();
    counters[49] ++;
    r2.i = r6.i;
    r3.i = r7.i;
    store_counter ++;
    str(&r0.i, &fp.i, 96, 4, false, false, false);
    str(&r1.i, &fp.i, 100, 4, false, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, 104, 4, false, false, false);
    ldr(&r1.i, &fp.i, 108, 4, false, false, false);
    ddiv();
    counters[50] ++;
    load_counter ++;
    ldr(&r8.i, &sp.i, 0, 4, false, false, false);
    ldr(&r9.i, &sp.i, 4, 4, false, false, false);
    r2.i = 1;
    store_counter ++;
    str(&r8.i, &fp.i, 112, 4, false, false, false);
    str(&r9.i, &fp.i, 116, 4, false, false, false);
    r6.i = r0.i;
    r7.i = r1.i;
    r0.i = r2.i;
    r1.i = (LC1 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC1 >> 16) << 16);
    store_counter ++;
    str(&r6.i, &fp.i, 104, 4, false, false, false);
    str(&r7.i, &fp.i, 108, 4, false, false, false);
    r6.i = (LC2 & 0xffff);
    r6.i = r6.i | (((uint32_t)LC2 >> 16) << 16);
    printf(malloc_0+r1.i, r2.i);
L15:
    counters[51] ++;
    r4.i = r5.i - (40);
L16:
    counters[52] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 8, 4, false, true, false);
    ldr(&r3.i, &r4.i, 12, 4, false, true, false);
    r1.i = r6.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[53] ++;
    tmp = r5.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r4.i);
    v = (r5.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (!z)
    {
        goto L16;
    }
    counters[54] ++;
    r0.i = 10;
    r5.i = r5.i + (40);
    printf("%c", (char)r0.i);
    counters[55] ++;
    load_counter ++;
    ldr(&r3.i, &L40, 0, 4, false, false, false);
    tmp = r5.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r3.i);
    v = (r5.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (!z)
    {
        goto L15;
    }
    counters[56] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, 48, 4, false, false, false);
    ldr(&r3.i, &fp.i, 52, 4, false, false, false);
    r5.i = (LC2 & 0xffff);
    load_counter ++;
    ldr(&r6.i, &fp.i, 88, 4, false, false, false);
    ldr(&r7.i, &fp.i, 92, 4, false, false, false);
    r5.i = r5.i | (((uint32_t)LC2 >> 16) << 16);
    r4.i = r10.i;
    store_counter ++;
    str(&r2.i, &sp.i, 0, 4, false, false, false);
    str(&r3.i, &sp.i, 4, 4, false, false, false);
    r0.i = r2.i;
    r1.i = r3.i;
    r2.i = r6.i;
    r3.i = r7.i;
    ddiv();
    counters[57] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, 80, 4, false, false, false);
    ldr(&r3.i, &fp.i, 84, 4, false, false, false);
    r8.i = r0.i;
    r9.i = r1.i;
    dmul();
    counters[58] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    load_counter ++;
    ldr(&r0.i, &fp.i, 40, 4, false, false, false);
    ldr(&r1.i, &fp.i, 44, 4, false, false, false);
    dsub();
    counters[59] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r6.i;
    store_counter ++;
    str(&r2.i, &fp.i, 40, 4, false, false, false);
    str(&r3.i, &fp.i, 44, 4, false, false, false);
    r1.i = r7.i;
    r2.i = r8.i;
    r3.i = r9.i;
    dmul();
    counters[60] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    load_counter ++;
    ldr(&r0.i, &sp.i, 0, 4, false, false, false);
    ldr(&r1.i, &sp.i, 4, 4, false, false, false);
    dsub();
    counters[61] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, 96, 4, false, false, false);
    ldr(&r3.i, &fp.i, 100, 4, false, false, false);
    r6.i = r0.i;
    r7.i = r1.i;
    r0.i = r8.i;
    store_counter ++;
    str(&r6.i, &fp.i, 48, 4, false, false, false);
    str(&r7.i, &fp.i, 52, 4, false, false, false);
    r1.i = r9.i;
    dmul();
    counters[62] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    load_counter ++;
    ldr(&r0.i, &fp.i, 56, 4, false, false, false);
    ldr(&r1.i, &fp.i, 60, 4, false, false, false);
    dsub();
    counters[63] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, 104, 4, false, false, false);
    ldr(&r3.i, &fp.i, 108, 4, false, false, false);
    r6.i = r0.i;
    r7.i = r1.i;
    r0.i = r8.i;
    store_counter ++;
    str(&r6.i, &fp.i, 56, 4, false, false, false);
    str(&r7.i, &fp.i, 60, 4, false, false, false);
    r1.i = r9.i;
    dmul();
    counters[64] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    load_counter ++;
    ldr(&r0.i, &fp.i, 64, 4, false, false, false);
    ldr(&r1.i, &fp.i, 68, 4, false, false, false);
    dsub();
    counters[65] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, 112, 4, false, false, false);
    ldr(&r3.i, &fp.i, 116, 4, false, false, false);
    r6.i = r0.i;
    r7.i = r1.i;
    r0.i = r8.i;
    store_counter ++;
    str(&r6.i, &fp.i, 64, 4, false, false, false);
    str(&r7.i, &fp.i, 68, 4, false, false, false);
    r1.i = r9.i;
    dmul();
    counters[66] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    load_counter ++;
    ldr(&r0.i, &fp.i, 72, 4, false, false, false);
    ldr(&r1.i, &fp.i, 76, 4, false, false, false);
    dsub();
    counters[67] ++;
    r2.i = 2;
    r6.i = r0.i;
    r7.i = r1.i;
    r0.i = 1;
    r1.i = (LC1 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC1 >> 16) << 16);
    store_counter ++;
    str(&r6.i, &fp.i, 72, 4, false, false, false);
    str(&r7.i, &fp.i, 76, 4, false, false, false);
    printf(malloc_0+r1.i, r2.i);
L18:
    counters[68] ++;
    r6.i = r4.i - (40);
L19:
    counters[69] ++;
    load_counter ++;
    ldr(&r2.i, &r6.i, 8, 4, false, true, false);
    ldr(&r3.i, &r6.i, 12, 4, false, true, false);
    r1.i = r5.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[70] ++;
    tmp = r6.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) r4.i);
    v = (r6.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    if (!z)
    {
        goto L19;
    }
    counters[71] ++;
    r0.i = 10;
    r4.i = r6.i + (40);
    printf("%c", (char)r0.i);
    counters[72] ++;
    load_counter ++;
    ldr(&r3.i, &L40, 0, 4, false, false, false);
    tmp = r4.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r3.i);
    v = (r4.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        goto L18;
    }
    counters[73] ++;
    load_counter ++;
    ldr(&lr.i, &fp.i, 84, 4, false, false, false);
    ip.i = (TempState & 0xffff);
    load_counter ++;
    ldr(&r5.i, &fp.i, 80, 4, false, false, false);
    ip.i = ip.i | (((uint32_t)TempState >> 16) << 16);
    load_counter ++;
    ldr(&r6.i, &fp.i, 104, 4, false, false, false);
    lr.i = lr.i + (-2147483648);
    load_counter ++;
    ldr(&r3.i, &fp.i, 100, 4, false, false, false);
    r0.i = r5.i;
    r1.i = lr.i;
    r3.i = r3.i + (-2147483648);
    store_counter ++;
    str(&r0.i, &ip.i, 0, 4, false, false, false);
    str(&r1.i, &ip.i, 4, 4, false, false, false);
    store_counter ++;
    str(&r3.i, &sp.i, 12, 4, false, false, false);
    r2.i = r5.i;
    load_counter ++;
    ldr(&r0.i, &fp.i, 112, 4, false, false, false);
    ldr(&r1.i, &fp.i, 116, 4, false, false, false);
    r3.i = lr.i;
    store_counter ++;
    str(&r6.i, &sp.i, 16, 4, false, false, false);
    load_counter ++;
    ldr(&r5.i, &fp.i, 96, 4, false, false, false);
    load_counter ++;
    ldr(&r6.i, &sp.i, 16, 4, false, false, false);
    load_counter ++;
    ldr(&r9.i, &sp.i, 12, 4, false, false, false);
    store_counter ++;
    str(&r0.i, &sp.i, 0, 4, false, false, false);
    str(&r1.i, &sp.i, 4, 4, false, false, false);
    r8.i = r5.i;
    load_counter ++;
    ldr(&r4.i, &fp.i, 108, 4, false, false, false);
    r0.i = r6.i;
    store_counter ++;
    str(&r8.i, &ip.i, 16, 4, false, false, false);
    str(&r9.i, &ip.i, 20, 4, false, false, false);
    load_counter ++;
    ldr(&r1.i, &fp.i, 88, 4, false, false, false);
    r4.i = r4.i + (-2147483648);
    load_counter ++;
    ldr(&r8.i, &fp.i, 8, 4, false, false, false);
    ldr(&r9.i, &fp.i, 12, 4, false, false, false);
    load_counter ++;
    ldr(&r6.i, &sp.i, 0, 4, false, false, false);
    ldr(&r7.i, &sp.i, 4, 4, false, false, false);
    load_counter ++;
    ldr(&lr.i, &fp.i, 92, 4, false, false, false);
    store_counter ++;
    str(&r1.i, &ip.i, 8, 4, false, false, false);
    r1.i = r4.i;
    lr.i = lr.i + (-2147483648);
    store_counter ++;
    str(&r0.i, &ip.i, 24, 4, false, false, false);
    str(&r1.i, &ip.i, 28, 4, false, false, false);
    store_counter ++;
    str(&r6.i, &ip.i, 32, 4, false, false, false);
    str(&r7.i, &ip.i, 36, 4, false, false, false);
    r0.i = r8.i;
    store_counter ++;
    str(&lr.i, &ip.i, 12, 4, false, false, false);
    r1.i = r9.i;
    dmul();
    counters[74] ++;
    load_counter ++;
    ldr(&r6.i, &fp.i, 32, 4, false, false, false);
    ldr(&r7.i, &fp.i, 36, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &sp.i, 16, 4, false, false, false);
    r3.i = r4.i;
    store_counter ++;
    str(&r6.i, &sp.i, 16, 4, false, false, false);
    str(&r7.i, &sp.i, 20, 4, false, false, false);
    store_counter ++;
    str(&r0.i, &fp.i, 0, 4, false, false, false);
    str(&r1.i, &fp.i, 4, 4, false, false, false);
    r0.i = r8.i;
    r1.i = r9.i;
    dmul();
    counters[75] ++;
    load_counter ++;
    ldr(&r2.i, &sp.i, 0, 4, false, false, false);
    ldr(&r3.i, &sp.i, 4, 4, false, false, false);
    load_counter ++;
    ldr(&r6.i, &fp.i, 16, 4, false, false, false);
    ldr(&r7.i, &fp.i, 20, 4, false, false, false);
    store_counter ++;
    str(&r0.i, &fp.i, 24, 4, false, false, false);
    str(&r1.i, &fp.i, 28, 4, false, false, false);
    r0.i = r8.i;
    r1.i = r9.i;
    dmul();
    counters[76] ++;
    r2.i = r5.i;
    load_counter ++;
    ldr(&r3.i, &sp.i, 12, 4, false, false, false);
    r4.i = r0.i;
    r5.i = r1.i;
    r0.i = r8.i;
    r1.i = r9.i;
    store_counter ++;
    str(&r4.i, &fp.i, 32, 4, false, false, false);
    str(&r5.i, &fp.i, 36, 4, false, false, false);
    dmul();
    counters[77] ++;
    r2.i = r6.i;
    r3.i = r7.i;
    dadd();
    counters[78] ++;
    r2.i = 0;
    r3.i = 0;
    store_counter ++;
    str(&r2.i, &fp.i, 8, 4, false, false, false);
    str(&r3.i, &fp.i, 12, 4, false, false, false);
    store_counter ++;
    str(&r0.i, &fp.i, 16, 4, false, false, false);
    str(&r1.i, &fp.i, 20, 4, false, false, false);
    r0.i = r4.i;
    r1.i = r5.i;
    dcmpeq();
    counters[79] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (z)
    {
        goto L39;
    }
L21:
    counters[80] ++;
    r1.i = (LC1 & 0xffff);
    r2.i = 3;
    r1.i = r1.i | (((uint32_t)LC1 >> 16) << 16);
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[81] ++;
    r5.i = (LC2 & 0xffff);
    r5.i = r5.i | (((uint32_t)LC2 >> 16) << 16);
L23:
    counters[82] ++;
    r4.i = r10.i - (40);
L24:
    counters[83] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 8, 4, false, true, false);
    ldr(&r3.i, &r4.i, 12, 4, false, true, false);
    r1.i = r5.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[84] ++;
    tmp = r4.i - r10.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r10.i);
    v = (r4.i&0x80000000) != (r10.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        goto L24;
    }
    counters[85] ++;
    r0.i = 10;
    r10.i = r10.i + (40);
    printf("%c", (char)r0.i);
    counters[86] ++;
    load_counter ++;
    ldr(&r3.i, &L40, 0, 4, false, false, false);
    tmp = r10.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r10.i) >= ((uint32_t) r3.i);
    v = (r10.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r10.i&0x80000000);
    if (!z)
    {
        goto L23;
    }
    counters[87] ++;
    sp.i = sp.i + (28);
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
    counters[88] ++;
    load_counter ++;
    ldr(&r0.i, &sp.i, 16, 4, false, false, false);
    ldr(&r1.i, &sp.i, 20, 4, false, false, false);
    r2.i = r4.i;
    r3.i = r5.i;
    dadd();
    counters[89] ++;
    store_counter ++;
    str(&r0.i, &fp.i, 32, 4, false, false, false);
    str(&r1.i, &fp.i, 36, 4, false, false, false);
    goto L21;
L38:
    counters[90] ++;
    load_counter ++;
    ldr(&r0.i, &sp.i, 16, 4, false, false, false);
    ldr(&r1.i, &sp.i, 20, 4, false, false, false);
    r2.i = r4.i;
    r3.i = r5.i;
    dadd();
    counters[91] ++;
    store_counter ++;
    str(&r0.i, &fp.i, 32, 4, false, false, false);
    str(&r1.i, &fp.i, 36, 4, false, false, false);
    goto L10;
    return;
}

void X1Calc()
{
    counters[92] ++;
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
    fp.i = (SimplexTable & 0xffff);
    fp.i = fp.i | (((uint32_t)SimplexTable >> 16) << 16);
    sp.i = sp.i - (28);
    r10.i = fp.i + (40);
    load_counter ++;
    ldr(&r4.i, &fp.i, 80, 4, false, false, false);
    ldr(&r5.i, &fp.i, 84, 4, false, false, false);
    r3.i = r5.i;
    r2.i = r4.i;
    r1.i = r5.i;
    r0.i = r4.i;
    ddiv();
    counters[93] ++;
    r3.i = r5.i;
    r2.i = r4.i;
    store_counter ++;
    str(&r0.i, &fp.i, 80, 4, false, false, false);
    str(&r1.i, &fp.i, 84, 4, false, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, 88, 4, false, false, false);
    ldr(&r1.i, &fp.i, 92, 4, false, false, false);
    ddiv();
    counters[94] ++;
    r3.i = r5.i;
    r2.i = r4.i;
    store_counter ++;
    str(&r0.i, &fp.i, 88, 4, false, false, false);
    str(&r1.i, &fp.i, 92, 4, false, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, 96, 4, false, false, false);
    ldr(&r1.i, &fp.i, 100, 4, false, false, false);
    ddiv();
    counters[95] ++;
    r3.i = r5.i;
    r2.i = r4.i;
    store_counter ++;
    str(&r0.i, &fp.i, 96, 4, false, false, false);
    str(&r1.i, &fp.i, 100, 4, false, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, 104, 4, false, false, false);
    ldr(&r1.i, &fp.i, 108, 4, false, false, false);
    ddiv();
    counters[96] ++;
    r3.i = r5.i;
    r2.i = r4.i;
    r5.i = r10.i;
    store_counter ++;
    str(&r0.i, &fp.i, 104, 4, false, false, false);
    str(&r1.i, &fp.i, 108, 4, false, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, 112, 4, false, false, false);
    ldr(&r1.i, &fp.i, 116, 4, false, false, false);
    ddiv();
    counters[97] ++;
    r2.i = 4;
    r6.i = r0.i;
    r7.i = r1.i;
    r0.i = 1;
    r1.i = (LC1 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC1 >> 16) << 16);
    store_counter ++;
    str(&r6.i, &fp.i, 112, 4, false, false, false);
    str(&r7.i, &fp.i, 116, 4, false, false, false);
    printf(malloc_0+r1.i, r2.i);
    counters[98] ++;
    r6.i = (LC2 & 0xffff);
    r6.i = r6.i | (((uint32_t)LC2 >> 16) << 16);
L43:
    counters[99] ++;
    r4.i = r5.i - (40);
L44:
    counters[100] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 8, 4, false, true, false);
    ldr(&r3.i, &r4.i, 12, 4, false, true, false);
    r1.i = r6.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[101] ++;
    tmp = r4.i - r5.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r5.i);
    v = (r4.i&0x80000000) != (r5.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        goto L44;
    }
    counters[102] ++;
    r0.i = 10;
    r5.i = r4.i + (40);
    printf("%c", (char)r0.i);
    counters[103] ++;
    load_counter ++;
    ldr(&r3.i, &L59, 0, 4, false, false, false);
    tmp = r5.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r3.i);
    v = (r5.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (!z)
    {
        goto L43;
    }
    counters[104] ++;
    load_counter ++;
    ldr(&r4.i, &fp.i, 40, 4, false, false, false);
    ldr(&r5.i, &fp.i, 44, 4, false, false, false);
    r6.i = (LC2 & 0xffff);
    load_counter ++;
    ldr(&r8.i, &fp.i, 80, 4, false, false, false);
    ldr(&r9.i, &fp.i, 84, 4, false, false, false);
    r6.i = r6.i | (((uint32_t)LC2 >> 16) << 16);
    r0.i = r4.i;
    r1.i = r5.i;
    r2.i = r8.i;
    r3.i = r9.i;
    ddiv();
    counters[105] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r8.i;
    r1.i = r9.i;
    r8.i = r2.i;
    r9.i = r3.i;
    dmul();
    counters[106] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r4.i;
    r1.i = r5.i;
    dsub();
    counters[107] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, 88, 4, false, false, false);
    ldr(&r3.i, &fp.i, 92, 4, false, false, false);
    store_counter ++;
    str(&r8.i, &sp.i, 0, 4, false, false, false);
    str(&r9.i, &sp.i, 4, 4, false, false, false);
    r4.i = r0.i;
    r5.i = r1.i;
    r0.i = r8.i;
    r1.i = r9.i;
    store_counter ++;
    str(&r4.i, &fp.i, 40, 4, false, false, false);
    str(&r5.i, &fp.i, 44, 4, false, false, false);
    r4.i = r10.i;
    dmul();
    counters[108] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    load_counter ++;
    ldr(&r0.i, &fp.i, 48, 4, false, false, false);
    ldr(&r1.i, &fp.i, 52, 4, false, false, false);
    dsub();
    counters[109] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, 96, 4, false, false, false);
    ldr(&r3.i, &fp.i, 100, 4, false, false, false);
    r8.i = r0.i;
    r9.i = r1.i;
    load_counter ++;
    ldr(&r0.i, &sp.i, 0, 4, false, false, false);
    ldr(&r1.i, &sp.i, 4, 4, false, false, false);
    store_counter ++;
    str(&r8.i, &fp.i, 48, 4, false, false, false);
    str(&r9.i, &fp.i, 52, 4, false, false, false);
    dmul();
    counters[110] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    load_counter ++;
    ldr(&r0.i, &fp.i, 56, 4, false, false, false);
    ldr(&r1.i, &fp.i, 60, 4, false, false, false);
    dsub();
    counters[111] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, 104, 4, false, false, false);
    ldr(&r3.i, &fp.i, 108, 4, false, false, false);
    r8.i = r0.i;
    r9.i = r1.i;
    load_counter ++;
    ldr(&r0.i, &sp.i, 0, 4, false, false, false);
    ldr(&r1.i, &sp.i, 4, 4, false, false, false);
    store_counter ++;
    str(&r8.i, &fp.i, 56, 4, false, false, false);
    str(&r9.i, &fp.i, 60, 4, false, false, false);
    dmul();
    counters[112] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    load_counter ++;
    ldr(&r0.i, &fp.i, 64, 4, false, false, false);
    ldr(&r1.i, &fp.i, 68, 4, false, false, false);
    dsub();
    counters[113] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, 112, 4, false, false, false);
    ldr(&r3.i, &fp.i, 116, 4, false, false, false);
    r8.i = r0.i;
    r9.i = r1.i;
    load_counter ++;
    ldr(&r0.i, &sp.i, 0, 4, false, false, false);
    ldr(&r1.i, &sp.i, 4, 4, false, false, false);
    store_counter ++;
    str(&r8.i, &fp.i, 64, 4, false, false, false);
    str(&r9.i, &fp.i, 68, 4, false, false, false);
    dmul();
    counters[114] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    load_counter ++;
    ldr(&r0.i, &fp.i, 72, 4, false, false, false);
    ldr(&r1.i, &fp.i, 76, 4, false, false, false);
    dsub();
    counters[115] ++;
    r2.i = 5;
    r8.i = r0.i;
    r9.i = r1.i;
    r0.i = 1;
    r1.i = (LC1 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC1 >> 16) << 16);
    store_counter ++;
    str(&r8.i, &fp.i, 72, 4, false, false, false);
    str(&r9.i, &fp.i, 76, 4, false, false, false);
    printf(malloc_0+r1.i, r2.i);
L46:
    counters[116] ++;
    r5.i = r4.i - (40);
L47:
    counters[117] ++;
    load_counter ++;
    ldr(&r2.i, &r5.i, 8, 4, false, true, false);
    ldr(&r3.i, &r5.i, 12, 4, false, true, false);
    r1.i = r6.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[118] ++;
    tmp = r5.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r4.i);
    v = (r5.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (!z)
    {
        goto L47;
    }
    counters[119] ++;
    r0.i = 10;
    r4.i = r5.i + (40);
    printf("%c", (char)r0.i);
    counters[120] ++;
    load_counter ++;
    ldr(&r3.i, &L59, 0, 4, false, false, false);
    tmp = r4.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r3.i);
    v = (r4.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        goto L46;
    }
    counters[121] ++;
    load_counter ++;
    ldr(&lr.i, &fp.i, 92, 4, false, false, false);
    ip.i = (TempState & 0xffff);
    load_counter ++;
    ldr(&r5.i, &fp.i, 88, 4, false, false, false);
    ip.i = ip.i | (((uint32_t)TempState >> 16) << 16);
    load_counter ++;
    ldr(&r6.i, &fp.i, 104, 4, false, false, false);
    lr.i = lr.i + (-2147483648);
    load_counter ++;
    ldr(&r3.i, &fp.i, 100, 4, false, false, false);
    r0.i = r5.i;
    r1.i = lr.i;
    r3.i = r3.i + (-2147483648);
    store_counter ++;
    str(&r0.i, &ip.i, 8, 4, false, false, false);
    str(&r1.i, &ip.i, 12, 4, false, false, false);
    store_counter ++;
    str(&r3.i, &sp.i, 12, 4, false, false, false);
    r2.i = r5.i;
    load_counter ++;
    ldr(&r0.i, &fp.i, 112, 4, false, false, false);
    ldr(&r1.i, &fp.i, 116, 4, false, false, false);
    r3.i = lr.i;
    store_counter ++;
    str(&r6.i, &sp.i, 16, 4, false, false, false);
    load_counter ++;
    ldr(&r5.i, &fp.i, 96, 4, false, false, false);
    load_counter ++;
    ldr(&r6.i, &sp.i, 16, 4, false, false, false);
    load_counter ++;
    ldr(&r9.i, &sp.i, 12, 4, false, false, false);
    store_counter ++;
    str(&r0.i, &sp.i, 0, 4, false, false, false);
    str(&r1.i, &sp.i, 4, 4, false, false, false);
    r8.i = r5.i;
    load_counter ++;
    ldr(&r4.i, &fp.i, 108, 4, false, false, false);
    r0.i = r6.i;
    store_counter ++;
    str(&r8.i, &ip.i, 16, 4, false, false, false);
    str(&r9.i, &ip.i, 20, 4, false, false, false);
    load_counter ++;
    ldr(&r1.i, &fp.i, 80, 4, false, false, false);
    r4.i = r4.i + (-2147483648);
    load_counter ++;
    ldr(&r8.i, &fp.i, 0, 4, false, false, false);
    ldr(&r9.i, &fp.i, 4, 4, false, false, false);
    load_counter ++;
    ldr(&r6.i, &sp.i, 0, 4, false, false, false);
    ldr(&r7.i, &sp.i, 4, 4, false, false, false);
    load_counter ++;
    ldr(&lr.i, &fp.i, 84, 4, false, false, false);
    store_counter ++;
    str(&r1.i, &ip.i, 0, 4, false, false, false);
    r1.i = r4.i;
    lr.i = lr.i + (-2147483648);
    store_counter ++;
    str(&r0.i, &ip.i, 24, 4, false, false, false);
    str(&r1.i, &ip.i, 28, 4, false, false, false);
    store_counter ++;
    str(&r6.i, &ip.i, 32, 4, false, false, false);
    str(&r7.i, &ip.i, 36, 4, false, false, false);
    r0.i = r8.i;
    store_counter ++;
    str(&lr.i, &ip.i, 4, 4, false, false, false);
    r1.i = r9.i;
    dmul();
    counters[122] ++;
    load_counter ++;
    ldr(&r6.i, &fp.i, 32, 4, false, false, false);
    ldr(&r7.i, &fp.i, 36, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &sp.i, 16, 4, false, false, false);
    r3.i = r4.i;
    store_counter ++;
    str(&r6.i, &sp.i, 16, 4, false, false, false);
    str(&r7.i, &sp.i, 20, 4, false, false, false);
    store_counter ++;
    str(&r0.i, &fp.i, 8, 4, false, false, false);
    str(&r1.i, &fp.i, 12, 4, false, false, false);
    r0.i = r8.i;
    r1.i = r9.i;
    dmul();
    counters[123] ++;
    load_counter ++;
    ldr(&r2.i, &sp.i, 0, 4, false, false, false);
    ldr(&r3.i, &sp.i, 4, 4, false, false, false);
    load_counter ++;
    ldr(&r6.i, &fp.i, 16, 4, false, false, false);
    ldr(&r7.i, &fp.i, 20, 4, false, false, false);
    store_counter ++;
    str(&r0.i, &fp.i, 24, 4, false, false, false);
    str(&r1.i, &fp.i, 28, 4, false, false, false);
    r0.i = r8.i;
    r1.i = r9.i;
    dmul();
    counters[124] ++;
    r2.i = r5.i;
    load_counter ++;
    ldr(&r3.i, &sp.i, 12, 4, false, false, false);
    r4.i = r0.i;
    r5.i = r1.i;
    r0.i = r8.i;
    r1.i = r9.i;
    store_counter ++;
    str(&r4.i, &fp.i, 32, 4, false, false, false);
    str(&r5.i, &fp.i, 36, 4, false, false, false);
    dmul();
    counters[125] ++;
    r2.i = r6.i;
    r3.i = r7.i;
    dadd();
    counters[126] ++;
    r2.i = 0;
    r3.i = 0;
    store_counter ++;
    str(&r2.i, &fp.i, 0, 4, false, false, false);
    str(&r3.i, &fp.i, 4, 4, false, false, false);
    store_counter ++;
    str(&r0.i, &fp.i, 16, 4, false, false, false);
    str(&r1.i, &fp.i, 20, 4, false, false, false);
    r0.i = r4.i;
    r1.i = r5.i;
    dcmpeq();
    counters[127] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        goto L49;
    }
    counters[128] ++;
    load_counter ++;
    ldr(&r0.i, &sp.i, 16, 4, false, false, false);
    ldr(&r1.i, &sp.i, 20, 4, false, false, false);
    r2.i = r4.i;
    r3.i = r5.i;
    dadd();
    counters[129] ++;
    store_counter ++;
    str(&r0.i, &fp.i, 32, 4, false, false, false);
    str(&r1.i, &fp.i, 36, 4, false, false, false);
L49:
    counters[130] ++;
    r1.i = (LC1 & 0xffff);
    r2.i = 6;
    r1.i = r1.i | (((uint32_t)LC1 >> 16) << 16);
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[131] ++;
    r5.i = (LC2 & 0xffff);
    r5.i = r5.i | (((uint32_t)LC2 >> 16) << 16);
L51:
    counters[132] ++;
    r4.i = r10.i - (40);
L52:
    counters[133] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 8, 4, false, true, false);
    ldr(&r3.i, &r4.i, 12, 4, false, true, false);
    r1.i = r5.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[134] ++;
    tmp = r10.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r10.i) >= ((uint32_t) r4.i);
    v = (r10.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r10.i&0x80000000);
    if (!z)
    {
        goto L52;
    }
    counters[135] ++;
    r0.i = 10;
    r10.i = r10.i + (40);
    printf("%c", (char)r0.i);
    counters[136] ++;
    load_counter ++;
    ldr(&r3.i, &L59, 0, 4, false, false, false);
    tmp = r10.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r10.i) >= ((uint32_t) r3.i);
    v = (r10.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r10.i&0x80000000);
    if (!z)
    {
        goto L51;
    }
    counters[137] ++;
    sp.i = sp.i + (28);
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

}

void Result()
{
    counters[138] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
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
    r5.i = (SimplexTable & 0xffff);
    r5.i = r5.i | (((uint32_t)SimplexTable >> 16) << 16);
    sp.i = sp.i - (28);
    r2.i = 0;
    r3.i = 0;
    load_counter ++;
    ldr(&r0.i, &r5.i, 40, 4, false, false, false);
    ldr(&r1.i, &r5.i, 44, 4, false, false, false);
    r3.i = r3.i | (16368 << 16);
    dcmpeq();
    counters[139] ++;
    load_counter ++;
    ldr(&r6.i, &r5.i, 72, 4, false, false, false);
    ldr(&r7.i, &r5.i, 76, 4, false, false, false);
    r4.i = r0.i - (0);
    z = r4.i == 0;
    n = r4.i & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (r4.i&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        r4.i = 1;
    }
    store_counter ++;
    if (!z)
    {
        str(&r6.i, &sp.i, 0, 4, false, false, false);
    }
    if (!z)
    {
        str(&r7.i, &sp.i, 4, 4, false, false, false);
    }
L62:
    counters[140] ++;
    load_counter ++;
    ldr(&r0.i, &r5.i, 48, 4, false, false, false);
    ldr(&r1.i, &r5.i, 52, 4, false, false, false);
    r2.i = 0;
    r3.i = 0;
    r3.i = r3.i | (16368 << 16);
    dcmpeq();
    counters[141] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        r3.i = sp.i + (24);
    }
    if (!z)
    {
        r3.i = r3.i + (((uint32_t)r4.i << 3));
    }
    if (!z)
    {
        r4.i = r4.i + (1);
    }
    store_counter ++;
    if (!z)
    {
        str(&r6.i, &r3.i, -24, 4, false, false, false);
    }
    if (!z)
    {
        str(&r7.i, &r3.i, -20, 4, false, false, false);
    }
L64:
    counters[142] ++;
    load_counter ++;
    ldr(&r0.i, &r5.i, 56, 4, false, false, false);
    ldr(&r1.i, &r5.i, 60, 4, false, false, false);
    r2.i = 0;
    r3.i = 0;
    r3.i = r3.i | (16368 << 16);
    dcmpeq();
    counters[143] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        r3.i = sp.i + (24);
    }
    if (!z)
    {
        r3.i = r3.i + (((uint32_t)r4.i << 3));
    }
    if (!z)
    {
        r4.i = r4.i + (1);
    }
    store_counter ++;
    if (!z)
    {
        str(&r6.i, &r3.i, -24, 4, false, false, false);
    }
    if (!z)
    {
        str(&r7.i, &r3.i, -20, 4, false, false, false);
    }
L66:
    counters[144] ++;
    load_counter ++;
    ldr(&r0.i, &r5.i, 64, 4, false, false, false);
    ldr(&r1.i, &r5.i, 68, 4, false, false, false);
    r2.i = 0;
    r3.i = 0;
    r3.i = r3.i | (16368 << 16);
    dcmpeq();
    counters[145] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        r3.i = sp.i + (24);
    }
    if (!z)
    {
        r3.i = r3.i + (((uint32_t)r4.i << 3));
    }
    if (!z)
    {
        r4.i = r4.i + (1);
    }
    store_counter ++;
    if (!z)
    {
        str(&r6.i, &r3.i, -24, 4, false, false, false);
    }
    if (!z)
    {
        str(&r7.i, &r3.i, -20, 4, false, false, false);
    }
L68:
    counters[146] ++;
    r9.i = 0;
    r9.i = r9.i | (16368 << 16);
    r8.i = 0;
    r0.i = r6.i;
    r1.i = r7.i;
    r2.i = r8.i;
    r3.i = r9.i;
    dcmpeq();
    counters[147] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        goto L95;
    }
L70:
    counters[148] ++;
    load_counter ++;
    ldr(&r0.i, &r5.i, 80, 4, false, false, false);
    ldr(&r1.i, &r5.i, 84, 4, false, false, false);
    r2.i = 0;
    r3.i = 0;
    r3.i = r3.i | (16368 << 16);
    dcmpeq();
    counters[149] ++;
    load_counter ++;
    ldr(&r6.i, &r5.i, 112, 4, false, false, false);
    ldr(&r7.i, &r5.i, 116, 4, false, false, false);
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        r3.i = sp.i + (24);
    }
    if (!z)
    {
        r3.i = r3.i + (((uint32_t)r4.i << 3));
    }
    if (!z)
    {
        r4.i = r4.i + (1);
    }
    store_counter ++;
    if (!z)
    {
        str(&r6.i, &r3.i, -24, 4, false, false, false);
    }
    if (!z)
    {
        str(&r7.i, &r3.i, -20, 4, false, false, false);
    }
L72:
    counters[150] ++;
    load_counter ++;
    ldr(&r0.i, &r5.i, 88, 4, false, false, false);
    ldr(&r1.i, &r5.i, 92, 4, false, false, false);
    r2.i = 0;
    r3.i = 0;
    r3.i = r3.i | (16368 << 16);
    dcmpeq();
    counters[151] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        r3.i = sp.i + (24);
    }
    if (!z)
    {
        r3.i = r3.i + (((uint32_t)r4.i << 3));
    }
    if (!z)
    {
        r4.i = r4.i + (1);
    }
    store_counter ++;
    if (!z)
    {
        str(&r6.i, &r3.i, -24, 4, false, false, false);
    }
    if (!z)
    {
        str(&r7.i, &r3.i, -20, 4, false, false, false);
    }
L74:
    counters[152] ++;
    load_counter ++;
    ldr(&r0.i, &r5.i, 96, 4, false, false, false);
    ldr(&r1.i, &r5.i, 100, 4, false, false, false);
    r2.i = 0;
    r3.i = 0;
    r3.i = r3.i | (16368 << 16);
    dcmpeq();
    counters[153] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        r3.i = sp.i + (24);
    }
    if (!z)
    {
        r3.i = r3.i + (((uint32_t)r4.i << 3));
    }
    if (!z)
    {
        r4.i = r4.i + (1);
    }
    store_counter ++;
    if (!z)
    {
        str(&r6.i, &r3.i, -24, 4, false, false, false);
    }
    if (!z)
    {
        str(&r7.i, &r3.i, -20, 4, false, false, false);
    }
L76:
    counters[154] ++;
    load_counter ++;
    ldr(&r0.i, &r5.i, 104, 4, false, false, false);
    ldr(&r1.i, &r5.i, 108, 4, false, false, false);
    r2.i = 0;
    r3.i = 0;
    r3.i = r3.i | (16368 << 16);
    dcmpeq();
    counters[155] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        r3.i = sp.i + (24);
    }
    if (!z)
    {
        r3.i = r3.i + (((uint32_t)r4.i << 3));
    }
    if (!z)
    {
        r4.i = r4.i + (1);
    }
    store_counter ++;
    if (!z)
    {
        str(&r6.i, &r3.i, -24, 4, false, false, false);
    }
    if (!z)
    {
        str(&r7.i, &r3.i, -20, 4, false, false, false);
    }
L78:
    counters[156] ++;
    r9.i = 0;
    r9.i = r9.i | (16368 << 16);
    r8.i = 0;
    r0.i = r6.i;
    r1.i = r7.i;
    r2.i = r8.i;
    r3.i = r9.i;
    dcmpeq();
    counters[157] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        r3.i = sp.i + (24);
    }
    if (!z)
    {
        r3.i = r3.i + (((uint32_t)r4.i << 3));
    }
    if (!z)
    {
        r4.i = r4.i + (1);
    }
    store_counter ++;
    if (!z)
    {
        str(&r8.i, &r3.i, -24, 4, false, false, false);
    }
    if (!z)
    {
        str(&r9.i, &r3.i, -20, 4, false, false, false);
    }
L80:
    counters[158] ++;
    load_counter ++;
    ldr(&r2.i, &r5.i, 32, 4, false, false, false);
    ldr(&r3.i, &r5.i, 36, 4, false, false, false);
    r1.i = sp.i + (24);
    r4.i = r1.i + (((uint32_t)r4.i << 3));
    r0.i = (LC3 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC3 >> 16) << 16);
    store_counter ++;
    str(&r2.i, &r4.i, -24, 4, false, false, false);
    str(&r3.i, &r4.i, -20, 4, false, false, false);
    printf("%s\n", malloc_0+r0.i);
    counters[159] ++;
    load_counter ++;
    ldr(&r2.i, &sp.i, 0, 4, false, false, false);
    ldr(&r3.i, &sp.i, 4, 4, false, false, false);
    r1.i = (LC4 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC4 >> 16) << 16);
    printf(malloc_0+r1.i, r2.i);
    counters[160] ++;
    load_counter ++;
    ldr(&r2.i, &sp.i, 8, 4, false, false, false);
    ldr(&r3.i, &sp.i, 12, 4, false, false, false);
    r1.i = (LC5 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC5 >> 16) << 16);
    printf(malloc_0+r1.i, r2.i);
    counters[161] ++;
    load_counter ++;
    ldr(&r2.i, &sp.i, 16, 4, false, false, false);
    ldr(&r3.i, &sp.i, 20, 4, false, false, false);
    r1.i = (LC6 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC6 >> 16) << 16);
    sp.i = sp.i + (28);
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
    ldr(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    printf(malloc_0+r1.i, r2.i);
    return;
L95:
    counters[162] ++;
    r3.i = sp.i + (24);
    r3.i = r3.i + (((uint32_t)r4.i << 3));
    r4.i = r4.i + (1);
    store_counter ++;
    str(&r8.i, &r3.i, -24, 4, false, false, false);
    str(&r9.i, &r3.i, -20, 4, false, false, false);
    goto L70;
    return;
}

void Maxim()
{
    counters[163] ++;
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
    r4.i = (SimplexTable & 0xffff);
    r4.i = r4.i | (((uint32_t)SimplexTable >> 16) << 16);
    sp.i = sp.i - (16);
    r10.i = (uint32_t)r1.i << 3;
    tmp = r0.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 1);
    v = (r0.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    load_counter ++;
    ldr(&r2.i, &r4.i, 32, 4, false, false, false);
    ldr(&r3.i, &r4.i, 36, 4, false, false, false);
    r5.i = (TempState & 0xffff);
    load_counter ++;
    ldr(&r6.i, &r4.i, r10.i, 4, false, false, false);
    ldr(&r7.i, &r4.i, r10.i, 4, false, false, false);
    r5.i = r5.i | (((uint32_t)TempState >> 16) << 16);
    store_counter ++;
    str(&r2.i, &sp.i, 0, 4, false, false, false);
    str(&r3.i, &sp.i, 4, 4, false, false, false);
    if (z)
    {
        goto L103;
    }
    counters[164] ++;
    r2.i = r6.i;
    r3.i = r7.i;
    load_counter ++;
    ldr(&r0.i, &r5.i, 0, 4, false, false, false);
    ldr(&r1.i, &r5.i, 4, 4, false, false, false);
    dmul();
    counters[165] ++;
    r2.i = r6.i;
    r3.i = r7.i;
    store_counter ++;
    str(&r0.i, &r4.i, 0, 4, false, false, false);
    str(&r1.i, &r4.i, 4, 4, false, false, false);
    load_counter ++;
    ldr(&r0.i, &r5.i, 8, 4, false, false, false);
    ldr(&r1.i, &r5.i, 12, 4, false, false, false);
    dmul();
    counters[166] ++;
    load_counter ++;
    ldr(&r2.i, &r5.i, 16, 4, false, false, false);
    ldr(&r3.i, &r5.i, 20, 4, false, false, false);
    r8.i = r0.i;
    r9.i = r1.i;
    r0.i = r6.i;
    store_counter ++;
    str(&r8.i, &r4.i, 8, 4, false, false, false);
    str(&r9.i, &r4.i, 12, 4, false, false, false);
    r1.i = r7.i;
    dmul();
    counters[167] ++;
    r2.i = r6.i;
    r3.i = r7.i;
    r8.i = r0.i;
    r9.i = r1.i;
    load_counter ++;
    ldr(&r0.i, &r5.i, 24, 4, false, false, false);
    ldr(&r1.i, &r5.i, 28, 4, false, false, false);
    dmul();
    counters[168] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 16, 4, false, false, false);
    ldr(&r3.i, &r4.i, 20, 4, false, false, false);
    store_counter ++;
    str(&r2.i, &sp.i, 8, 4, false, false, false);
    str(&r3.i, &sp.i, 12, 4, false, false, false);
    r2.i = r6.i;
    r3.i = r7.i;
    store_counter ++;
    str(&r0.i, &r4.i, 24, 4, false, false, false);
    str(&r1.i, &r4.i, 28, 4, false, false, false);
    load_counter ++;
    ldr(&r0.i, &r5.i, 32, 4, false, false, false);
    ldr(&r1.i, &r5.i, 36, 4, false, false, false);
    dmul();
    counters[169] ++;
    r2.i = r8.i;
    r3.i = r9.i;
    store_counter ++;
    str(&r0.i, &r4.i, 32, 4, false, false, false);
    str(&r1.i, &r4.i, 36, 4, false, false, false);
    load_counter ++;
    ldr(&r0.i, &sp.i, 8, 4, false, false, false);
    ldr(&r1.i, &sp.i, 12, 4, false, false, false);
    dadd();
    counters[170] ++;
    r2.i = 0;
    r3.i = 0;
    store_counter ++;
    str(&r0.i, &r4.i, 16, 4, false, false, false);
    str(&r1.i, &r4.i, 20, 4, false, false, false);
    store_counter ++;
    str(&r2.i, &r4.i, r10.i, 4, false, false, false);
    str(&r3.i, &r4.i, r10.i, 4, false, false, false);
L98:
    counters[171] ++;
    load_counter ++;
    ldr(&r6.i, &r4.i, 32, 4, false, false, false);
    ldr(&r7.i, &r4.i, 36, 4, false, false, false);
    r2.i = 0;
    r3.i = 0;
    r0.i = r6.i;
    r1.i = r7.i;
    dcmpeq();
    counters[172] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        goto L96;
    }
    counters[173] ++;
    load_counter ++;
    ldr(&r2.i, &sp.i, 0, 4, false, false, false);
    ldr(&r3.i, &sp.i, 4, 4, false, false, false);
    r0.i = r6.i;
    r1.i = r7.i;
    dadd();
    counters[174] ++;
    store_counter ++;
    str(&r0.i, &r4.i, 32, 4, false, false, false);
    str(&r1.i, &r4.i, 36, 4, false, false, false);
L96:
    counters[175] ++;
    sp.i = sp.i + (16);
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
L103:
    counters[176] ++;
    load_counter ++;
    ldr(&r2.i, &r5.i, 0, 4, false, false, false);
    ldr(&r3.i, &r5.i, 4, 4, false, false, false);
    r0.i = r6.i;
    r1.i = r7.i;
    dmul();
    counters[177] ++;
    r2.i = r6.i;
    r3.i = r7.i;
    r8.i = r0.i;
    r9.i = r1.i;
    load_counter ++;
    ldr(&r0.i, &r5.i, 8, 4, false, false, false);
    ldr(&r1.i, &r5.i, 12, 4, false, false, false);
    dmul();
    counters[178] ++;
    r2.i = r6.i;
    r3.i = r7.i;
    store_counter ++;
    str(&r0.i, &r4.i, 8, 4, false, false, false);
    str(&r1.i, &r4.i, 12, 4, false, false, false);
    load_counter ++;
    ldr(&r0.i, &r5.i, 16, 4, false, false, false);
    ldr(&r1.i, &r5.i, 20, 4, false, false, false);
    dmul();
    counters[179] ++;
    r2.i = r6.i;
    r3.i = r7.i;
    store_counter ++;
    str(&r0.i, &r4.i, 16, 4, false, false, false);
    str(&r1.i, &r4.i, 20, 4, false, false, false);
    load_counter ++;
    ldr(&r0.i, &r5.i, 24, 4, false, false, false);
    ldr(&r1.i, &r5.i, 28, 4, false, false, false);
    dmul();
    counters[180] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 0, 4, false, false, false);
    ldr(&r3.i, &r4.i, 4, 4, false, false, false);
    store_counter ++;
    str(&r2.i, &sp.i, 8, 4, false, false, false);
    str(&r3.i, &sp.i, 12, 4, false, false, false);
    r2.i = r6.i;
    r3.i = r7.i;
    store_counter ++;
    str(&r0.i, &r4.i, 24, 4, false, false, false);
    str(&r1.i, &r4.i, 28, 4, false, false, false);
    load_counter ++;
    ldr(&r0.i, &r5.i, 32, 4, false, false, false);
    ldr(&r1.i, &r5.i, 36, 4, false, false, false);
    dmul();
    counters[181] ++;
    r2.i = r8.i;
    r3.i = r9.i;
    store_counter ++;
    str(&r0.i, &r4.i, 32, 4, false, false, false);
    str(&r1.i, &r4.i, 36, 4, false, false, false);
    load_counter ++;
    ldr(&r0.i, &sp.i, 8, 4, false, false, false);
    ldr(&r1.i, &sp.i, 12, 4, false, false, false);
    dadd();
    counters[182] ++;
    r2.i = 0;
    r3.i = 0;
    store_counter ++;
    str(&r0.i, &r4.i, 0, 4, false, false, false);
    str(&r1.i, &r4.i, 4, 4, false, false, false);
    store_counter ++;
    str(&r2.i, &r4.i, r10.i, 4, false, false, false);
    str(&r3.i, &r4.i, r10.i, 4, false, false, false);
    goto L98;
    return;
}

void GaussCalc()
{
    counters[183] ++;
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
    r4.i = (SimplexTable & 0xffff);
    r4.i = r4.i | (((uint32_t)SimplexTable >> 16) << 16);
    tmp = r0.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 1);
    v = (r0.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    r2.i = r4.i + (((uint32_t)r1.i << 3));
    load_counter ++;
    ldr(&r6.i, &r2.i, 40, 4, false, false, false);
    ldr(&r7.i, &r2.i, 44, 4, false, false, false);
    if (z)
    {
        goto L108;
    }
    counters[184] ++;
    ip.i = r0.i + (((uint32_t)r0.i << 2));
    r3.i = r1.i;
    r3.i = ip.i + (r3.i);
    r5.i = r0.i;
    r1.i = r7.i;
    r0.i = r6.i;
    r3.i = (uint32_t)r3.i << 3;
    load_counter ++;
    ldr(&r2.i, &r3.i, r4.i, 4, false, false, false);
    ldr(&r3.i, &r3.i, r4.i, 4, false, false, false);
    ddiv();
    counters[185] ++;
    r3.i = 40;
    r5.i = (r3.i) * (r5.i);
    r8.i = r4.i + (r5.i);
    load_counter ++;
    ldr(&r2.i, &r4.i, r5.i, 4, false, false, false);
    ldr(&r3.i, &r4.i, r5.i, 4, false, false, false);
    r6.i = r0.i;
    r7.i = r1.i;
    dmul();
    counters[186] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    load_counter ++;
    ldr(&r0.i, &r4.i, 40, 4, false, false, false);
    ldr(&r1.i, &r4.i, 44, 4, false, false, false);
    dsub();
    counters[187] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r6.i;
    store_counter ++;
    str(&r2.i, &r4.i, 40, 4, false, false, false);
    str(&r3.i, &r4.i, 44, 4, false, false, false);
    r1.i = r7.i;
    load_counter ++;
    ldr(&r2.i, &r8.i, 8, 4, false, false, false);
    ldr(&r3.i, &r8.i, 12, 4, false, false, false);
    dmul();
    counters[188] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    load_counter ++;
    ldr(&r0.i, &r4.i, 48, 4, false, false, false);
    ldr(&r1.i, &r4.i, 52, 4, false, false, false);
    dsub();
    counters[189] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r6.i;
    store_counter ++;
    str(&r2.i, &r4.i, 48, 4, false, false, false);
    str(&r3.i, &r4.i, 52, 4, false, false, false);
    r1.i = r7.i;
    load_counter ++;
    ldr(&r2.i, &r8.i, 16, 4, false, false, false);
    ldr(&r3.i, &r8.i, 20, 4, false, false, false);
    dmul();
    counters[190] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    load_counter ++;
    ldr(&r0.i, &r4.i, 56, 4, false, false, false);
    ldr(&r1.i, &r4.i, 60, 4, false, false, false);
    dsub();
    counters[191] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r6.i;
    store_counter ++;
    str(&r2.i, &r4.i, 56, 4, false, false, false);
    str(&r3.i, &r4.i, 60, 4, false, false, false);
    r1.i = r7.i;
    load_counter ++;
    ldr(&r2.i, &r8.i, 24, 4, false, false, false);
    ldr(&r3.i, &r8.i, 28, 4, false, false, false);
    dmul();
    counters[192] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    load_counter ++;
    ldr(&r0.i, &r4.i, 64, 4, false, false, false);
    ldr(&r1.i, &r4.i, 68, 4, false, false, false);
    dsub();
    counters[193] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r6.i;
    store_counter ++;
    str(&r2.i, &r4.i, 64, 4, false, false, false);
    str(&r3.i, &r4.i, 68, 4, false, false, false);
    r1.i = r7.i;
    load_counter ++;
    ldr(&r2.i, &r8.i, 32, 4, false, false, false);
    ldr(&r3.i, &r8.i, 36, 4, false, false, false);
    dmul();
    counters[194] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    load_counter ++;
    ldr(&r0.i, &r4.i, 72, 4, false, false, false);
    ldr(&r1.i, &r4.i, 76, 4, false, false, false);
    dsub();
    counters[195] ++;
    store_counter ++;
    str(&r0.i, &r4.i, 72, 4, false, false, false);
    str(&r1.i, &r4.i, 76, 4, false, false, false);
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
L108:
    counters[196] ++;
    r1.i = r2.i;
    r3.i = r7.i;
    load_counter ++;
    ldr(&r0.i, &r1.i, 80, 4, false, false, false);
    ldr(&r1.i, &r1.i, 84, 4, false, false, false);
    r2.i = r6.i;
    ddiv();
    counters[197] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 40, 4, false, false, false);
    ldr(&r3.i, &r4.i, 44, 4, false, false, false);
    r6.i = r0.i;
    r7.i = r1.i;
    dmul();
    counters[198] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    load_counter ++;
    ldr(&r0.i, &r4.i, 80, 4, false, false, false);
    ldr(&r1.i, &r4.i, 84, 4, false, false, false);
    dsub();
    counters[199] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 48, 4, false, false, false);
    ldr(&r3.i, &r4.i, 52, 4, false, false, false);
    r8.i = r0.i;
    r9.i = r1.i;
    r0.i = r6.i;
    store_counter ++;
    str(&r8.i, &r4.i, 80, 4, false, false, false);
    str(&r9.i, &r4.i, 84, 4, false, false, false);
    r1.i = r7.i;
    dmul();
    counters[200] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    load_counter ++;
    ldr(&r0.i, &r4.i, 88, 4, false, false, false);
    ldr(&r1.i, &r4.i, 92, 4, false, false, false);
    dsub();
    counters[201] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 56, 4, false, false, false);
    ldr(&r3.i, &r4.i, 60, 4, false, false, false);
    r8.i = r0.i;
    r9.i = r1.i;
    r0.i = r6.i;
    store_counter ++;
    str(&r8.i, &r4.i, 88, 4, false, false, false);
    str(&r9.i, &r4.i, 92, 4, false, false, false);
    r1.i = r7.i;
    dmul();
    counters[202] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    load_counter ++;
    ldr(&r0.i, &r4.i, 96, 4, false, false, false);
    ldr(&r1.i, &r4.i, 100, 4, false, false, false);
    dsub();
    counters[203] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 64, 4, false, false, false);
    ldr(&r3.i, &r4.i, 68, 4, false, false, false);
    r8.i = r0.i;
    r9.i = r1.i;
    r0.i = r6.i;
    store_counter ++;
    str(&r8.i, &r4.i, 96, 4, false, false, false);
    str(&r9.i, &r4.i, 100, 4, false, false, false);
    r1.i = r7.i;
    dmul();
    counters[204] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    load_counter ++;
    ldr(&r0.i, &r4.i, 104, 4, false, false, false);
    ldr(&r1.i, &r4.i, 108, 4, false, false, false);
    dsub();
    counters[205] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 72, 4, false, false, false);
    ldr(&r3.i, &r4.i, 76, 4, false, false, false);
    r8.i = r0.i;
    r9.i = r1.i;
    r0.i = r6.i;
    r1.i = r7.i;
    store_counter ++;
    str(&r8.i, &r4.i, 104, 4, false, false, false);
    str(&r9.i, &r4.i, 108, 4, false, false, false);
    dmul();
    counters[206] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    load_counter ++;
    ldr(&r0.i, &r4.i, 112, 4, false, false, false);
    ldr(&r1.i, &r4.i, 116, 4, false, false, false);
    dsub();
    counters[207] ++;
    store_counter ++;
    str(&r0.i, &r4.i, 112, 4, false, false, false);
    str(&r1.i, &r4.i, 116, 4, false, false, false);
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

void Exchange()
{
    counters[208] ++;
    tmp = r0.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 1);
    v = (r0.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    r2.i = (SimplexTable & 0xffff);
    r3.i = (TempState & 0xffff);
    r2.i = r2.i | (((uint32_t)SimplexTable >> 16) << 16);
    r3.i = r3.i | (((uint32_t)TempState >> 16) << 16);
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r4.i, &sp.i, 0, 4, false, false, false);
    if (z)
    {
        goto L114;
    }
    counters[209] ++;
    load_counter ++;
    ldr(&r0.i, &r2.i, 88, 4, false, false, false);
    load_counter ++;
    ldr(&r4.i, &r2.i, 80, 4, false, false, false);
    load_counter ++;
    ldr(&r1.i, &r2.i, 84, 4, false, false, false);
    store_counter ++;
    str(&r0.i, &r3.i, 8, 4, false, false, false);
    load_counter ++;
    ldr(&r0.i, &r2.i, 92, 4, false, false, false);
    r1.i = r1.i + (-2147483648);
    load_counter ++;
    ldr(&lr.i, &r2.i, 96, 4, false, false, false);
    load_counter ++;
    ldr(&ip.i, &r2.i, 104, 4, false, false, false);
    r0.i = r0.i + (-2147483648);
    store_counter ++;
    str(&r4.i, &r3.i, 0, 4, false, false, false);
    store_counter ++;
    str(&r1.i, &r3.i, 4, 4, false, false, false);
    load_counter ++;
    ldr(&r4.i, &r2.i, 112, 4, false, false, false);
    ldr(&r5.i, &r2.i, 116, 4, false, false, false);
    load_counter ++;
    ldr(&r1.i, &r2.i, 100, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &r2.i, 108, 4, false, false, false);
    store_counter ++;
    str(&lr.i, &r3.i, 16, 4, false, false, false);
    store_counter ++;
    str(&ip.i, &r3.i, 24, 4, false, false, false);
L113:
    counters[210] ++;
    r1.i = r1.i + (-2147483648);
    r2.i = r2.i + (-2147483648);
    store_counter ++;
    str(&r0.i, &r3.i, 12, 4, false, false, false);
    store_counter ++;
    str(&r1.i, &r3.i, 20, 4, false, false, false);
    store_counter ++;
    str(&r2.i, &r3.i, 28, 4, false, false, false);
    store_counter ++;
    str(&r4.i, &r3.i, 32, 4, false, false, false);
    str(&r5.i, &r3.i, 36, 4, false, false, false);
    load_counter ++;
    ldr(&r4.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;
L114:
    counters[211] ++;
    load_counter ++;
    ldr(&r0.i, &r2.i, 48, 4, false, false, false);
    load_counter ++;
    ldr(&r4.i, &r2.i, 40, 4, false, false, false);
    load_counter ++;
    ldr(&lr.i, &r2.i, 56, 4, false, false, false);
    load_counter ++;
    ldr(&ip.i, &r2.i, 64, 4, false, false, false);
    load_counter ++;
    ldr(&r1.i, &r2.i, 44, 4, false, false, false);
    store_counter ++;
    str(&r0.i, &r3.i, 8, 4, false, false, false);
    load_counter ++;
    ldr(&r0.i, &r2.i, 52, 4, false, false, false);
    r1.i = r1.i + (-2147483648);
    store_counter ++;
    str(&r4.i, &r3.i, 0, 4, false, false, false);
    store_counter ++;
    str(&r1.i, &r3.i, 4, 4, false, false, false);
    r0.i = r0.i + (-2147483648);
    load_counter ++;
    ldr(&r4.i, &r2.i, 72, 4, false, false, false);
    ldr(&r5.i, &r2.i, 76, 4, false, false, false);
    load_counter ++;
    ldr(&r1.i, &r2.i, 60, 4, false, false, false);
    store_counter ++;
    str(&lr.i, &r3.i, 16, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &r2.i, 68, 4, false, false, false);
    store_counter ++;
    str(&ip.i, &r3.i, 24, 4, false, false, false);
    goto L113;
    return;
}

void ShowTable()
{
    counters[212] ++;
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
    r2.i = r0.i;
    r1.i = (LC1 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC1 >> 16) << 16);
    load_counter ++;
    ldr(&r5.i, &L121, 0, 4, false, false, false);
    printf(malloc_0+r1.i, r2.i);
    counters[213] ++;
    r6.i = (LC2 & 0xffff);
    r7.i = r5.i + (120);
    r6.i = r6.i | (((uint32_t)LC2 >> 16) << 16);
L116:
    counters[214] ++;
    r4.i = r5.i - (40);
L117:
    counters[215] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 8, 4, false, true, false);
    ldr(&r3.i, &r4.i, 12, 4, false, true, false);
    r1.i = r6.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[216] ++;
    tmp = r4.i - r5.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r5.i);
    v = (r4.i&0x80000000) != (r5.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        goto L117;
    }
    counters[217] ++;
    r5.i = r4.i + (40);
    r0.i = 10;
    printf("%c", (char)r0.i);
    counters[218] ++;
    tmp = r5.i - r7.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r7.i);
    v = (r5.i&0x80000000) != (r7.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (!z)
    {
        goto L116;
    }
    counters[219] ++;
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

void Input()
{
    counters[220] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
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
    sp.i = sp.i - (124);
    r2.i = 120;
    r1.i = (LC0 & 0xffff);
    r0.i = sp.i;
    r1.i = r1.i | (((uint32_t)LC0 >> 16) << 16);
    memcpy_help();
    counters[221] ++;
    load_counter ++;
    ldr(&r4.i, &sp.i, 16, 4, false, false, false);
    ldr(&r5.i, &sp.i, 20, 4, false, false, false);
    ip.i = (SimplexTable & 0xffff);
    ip.i = ip.i | (((uint32_t)SimplexTable >> 16) << 16);
    load_counter ++;
    ldr(&r6.i, &sp.i, 24, 4, false, false, false);
    ldr(&r7.i, &sp.i, 28, 4, false, false, false);
    r8.i = ip.i + (40);
    store_counter ++;
    str(&r4.i, &ip.i, 16, 4, false, false, false);
    str(&r5.i, &ip.i, 20, 4, false, false, false);
    r9.i = ip.i + (160);
    load_counter ++;
    ldr(&r4.i, &sp.i, 32, 4, false, false, false);
    ldr(&r5.i, &sp.i, 36, 4, false, false, false);
    store_counter ++;
    str(&r6.i, &ip.i, 24, 4, false, false, false);
    str(&r7.i, &ip.i, 28, 4, false, false, false);
    load_counter ++;
    ldr(&r6.i, &sp.i, 48, 4, false, false, false);
    ldr(&r7.i, &sp.i, 52, 4, false, false, false);
    store_counter ++;
    str(&r4.i, &ip.i, 32, 4, false, false, false);
    str(&r5.i, &ip.i, 36, 4, false, false, false);
    load_counter ++;
    ldr(&r4.i, &sp.i, 40, 4, false, false, false);
    ldr(&r5.i, &sp.i, 44, 4, false, false, false);
    store_counter ++;
    str(&r6.i, &ip.i, 48, 4, false, false, false);
    str(&r7.i, &ip.i, 52, 4, false, false, false);
    load_counter ++;
    ldr(&r6.i, &sp.i, 64, 4, false, false, false);
    ldr(&r7.i, &sp.i, 68, 4, false, false, false);
    store_counter ++;
    str(&r4.i, &ip.i, 40, 4, false, false, false);
    str(&r5.i, &ip.i, 44, 4, false, false, false);
    load_counter ++;
    ldr(&r4.i, &sp.i, 56, 4, false, false, false);
    ldr(&r5.i, &sp.i, 60, 4, false, false, false);
    store_counter ++;
    str(&r6.i, &ip.i, 64, 4, false, false, false);
    str(&r7.i, &ip.i, 68, 4, false, false, false);
    load_counter ++;
    ldr(&r6.i, &sp.i, 80, 4, false, false, false);
    ldr(&r7.i, &sp.i, 84, 4, false, false, false);
    store_counter ++;
    str(&r4.i, &ip.i, 56, 4, false, false, false);
    str(&r5.i, &ip.i, 60, 4, false, false, false);
    load_counter ++;
    ldr(&r4.i, &sp.i, 72, 4, false, false, false);
    ldr(&r5.i, &sp.i, 76, 4, false, false, false);
    store_counter ++;
    str(&r6.i, &ip.i, 80, 4, false, false, false);
    str(&r7.i, &ip.i, 84, 4, false, false, false);
    load_counter ++;
    ldr(&r6.i, &sp.i, 96, 4, false, false, false);
    ldr(&r7.i, &sp.i, 100, 4, false, false, false);
    store_counter ++;
    str(&r4.i, &ip.i, 72, 4, false, false, false);
    str(&r5.i, &ip.i, 76, 4, false, false, false);
    load_counter ++;
    ldr(&r4.i, &sp.i, 88, 4, false, false, false);
    ldr(&r5.i, &sp.i, 92, 4, false, false, false);
    load_counter ++;
    ldr(&r0.i, &sp.i, 0, 4, false, false, false);
    ldr(&r1.i, &sp.i, 4, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &sp.i, 8, 4, false, false, false);
    ldr(&r3.i, &sp.i, 12, 4, false, false, false);
    store_counter ++;
    str(&r4.i, &ip.i, 88, 4, false, false, false);
    str(&r5.i, &ip.i, 92, 4, false, false, false);
    store_counter ++;
    str(&r6.i, &ip.i, 96, 4, false, false, false);
    str(&r7.i, &ip.i, 100, 4, false, false, false);
    load_counter ++;
    ldr(&r4.i, &sp.i, 104, 4, false, false, false);
    ldr(&r5.i, &sp.i, 108, 4, false, false, false);
    load_counter ++;
    ldr(&r6.i, &sp.i, 112, 4, false, false, false);
    ldr(&r7.i, &sp.i, 116, 4, false, false, false);
    store_counter ++;
    str(&r0.i, &ip.i, 0, 4, false, false, false);
    str(&r1.i, &ip.i, 4, 4, false, false, false);
    r1.i = (LC1 & 0xffff);
    store_counter ++;
    str(&r2.i, &ip.i, 8, 4, false, false, false);
    str(&r3.i, &ip.i, 12, 4, false, false, false);
    r1.i = r1.i | (((uint32_t)LC1 >> 16) << 16);
    r2.i = 0;
    r0.i = 1;
    store_counter ++;
    str(&r4.i, &ip.i, 104, 4, false, false, false);
    str(&r5.i, &ip.i, 108, 4, false, false, false);
    r5.i = (LC2 & 0xffff);
    store_counter ++;
    str(&r6.i, &ip.i, 112, 4, false, false, false);
    str(&r7.i, &ip.i, 116, 4, false, false, false);
    printf(malloc_0+r1.i, r2.i);
    counters[222] ++;
    r5.i = r5.i | (((uint32_t)LC2 >> 16) << 16);
L124:
    counters[223] ++;
    r4.i = r8.i - (40);
L125:
    counters[224] ++;
    load_counter ++;
    ldr(&r2.i, &r4.i, 8, 4, false, true, false);
    ldr(&r3.i, &r4.i, 12, 4, false, true, false);
    r1.i = r5.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[225] ++;
    tmp = r4.i - r8.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r8.i);
    v = (r4.i&0x80000000) != (r8.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        goto L125;
    }
    counters[226] ++;
    r8.i = r4.i + (40);
    r0.i = 10;
    printf("%c", (char)r0.i);
    counters[227] ++;
    tmp = r8.i - r9.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) r9.i);
    v = (r8.i&0x80000000) != (r9.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    if (!z)
    {
        goto L124;
    }
    counters[228] ++;
    sp.i = sp.i + (124);
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
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;

}

void main()
{
    malloc_start();
    counters[229] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r4.i, &sp.i, 0, 4, false, false, false);
    Input();
    counters[230] ++;
    X2Calc();
    counters[231] ++;
    X1Calc();
    counters[232] ++;
    Result();
    counters[233] ++;
    r0.i = 0;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;

}

