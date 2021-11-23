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

reg r9, r7, r0, r3, r4, r2, r5, r1, r6, r8;

int32_t SimplexTable, TempState, LC1, LC2, LC3, LC4, LC5, LC6, LC0;

int counters[119] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[119] = {3,1,1,1,3,10,10,6,3,9,13,18,3,2,7,2,3,3,2,1,9,13,18,3,2,7,2,3,3,2,3,12,13,18,3,2,7,2,3,3,2,3,8,3,15,3,17,3,3,3,3,12,4,4,4,3,19,9,8,13,3,5,16,9,8,13,3,5,15,6,3,1,5,7,3,8,25,6,24,5,18,3,1,25,6,24,5,18,3,3,8,5,24,3,9,5,22,3,8,4,10,3,3,14,3,3,2,3,3,4,10,3,3,25,3,3,3,2,3};


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

void print_stack(int32_t start)
{
    int32_t size = (1028-start)/4;
    int32_t cur_val = 0;

    for(int32_t i=0; i<size; i++)
    {
        ldr(&cur_val, &start, i*4, 4, false, false);
        printf("%d: %d\n", start+i*4, cur_val);
    }
}

void malloc_start()
{
    malloc_0 = (uint8_t*) malloc(1);
    uint8_t* stack_ptr = (uint8_t*) malloc(1000);
    sp.i = (int32_t) (stack_ptr - malloc_0) + 996;
    fp = sp;

    int32_t malloc_total = (int32_t) ((uint8_t*) malloc(420) - malloc_0);
    SimplexTable = malloc_total;
    SimplexTable = (int32_t) ((uint8_t*) malloc(120*sizeof(int8_t)) - malloc_0);

    TempState = malloc_total + 120;
    TempState = (int32_t) ((uint8_t*) malloc(40*sizeof(int8_t)) - malloc_0);

    LC1 = malloc_total + 160;
    strcpy(malloc_0+LC1, "\012***** Result *****\000");

    LC2 = malloc_total + 188;
    strcpy(malloc_0+LC2, "x1 = %lf \000");

    LC3 = malloc_total + 203;
    strcpy(malloc_0+LC3, "x2 = %lf \000");

    LC4 = malloc_total + 218;
    strcpy(malloc_0+LC4, "f = %lf\012\000");

    LC5 = malloc_total + 235;
    strcpy(malloc_0+LC5, "\012------------------Simplex Table Step = %d------");

    LC6 = malloc_total + 288;
    strcpy(malloc_0+LC6, "%10lf \000");

    LC0 = malloc_total + 300;
    int32_t arrayLC0[] = {0,1077739520,0,1078362112,0,0,0,0,0,0,0,1073741824,0,1075838976,0,1072693248,0,0,0,1078853632,0,1074790400,0,1074790400,0,0,0,1072693248,0,1078853632};
    for(int i=0; i<30; i++) str(&arrayLC0[i], &LC0, i*4, 4, false, false);

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

void main();
void X2Calc();
void X1Calc();
void Result();
void Maxim();
void GaussCalc();
void Exchange();
void ShowTable();
void Input();

void dadd()
{
    int64_t op1 = ((int64_t) r1.i) << 32 | ((int64_t) r0.i);
    int64_t op2 = ((int64_t) r3.i) << 32 | ((int64_t) r2.i);
    double result = *(double *)&op1 + *(double *)&op2;
    int64_t result_int64 = *(int64_t *)&result;
    r1.i = (int32_t) (result_int64 >> 32);
    r0.i = (int32_t) result_int64;
}
void ddiv()
{
    int64_t op1 = ((int64_t) r1.i) << 32 | ((int64_t) r0.i);
    int64_t op2 = ((int64_t) r3.i) << 32 | ((int64_t) r2.i);
    double result = *(double *)&op1 / *(double *)&op2;
    int64_t result_int64 = *(int64_t *)&result;
    r1.i = (int32_t) (result_int64 >> 32);
    r0.i = (int32_t) result_int64;
}
void dcmpeq()
{
    int64_t op1 = ((int64_t) r1.i) << 32 | ((int64_t) r0.i);
    int64_t op2 = ((int64_t) r3.i) << 32 | ((int64_t) r2.i);
    r0.i = *(double *)&op1 == *(double *)&op2;
}
void dcmplt()
{
    int64_t op1 = ((int64_t) r1.i) << 32 | ((int64_t) r0.i);
    int64_t op2 = ((int64_t) r3.i) << 32 | ((int64_t) r2.i);
    r0.i = *(double *)&op1 < *(double *)&op2;
}
void dmul()
{
    int64_t op1 = ((int64_t) r1.i) << 32 | ((int64_t) r0.i);
    int64_t op2 = ((int64_t) r3.i) << 32 | ((int64_t) r2.i);
    double result = *(double *)&op1 * *(double *)&op2;
    int64_t result_int64 = *(int64_t *)&result;
    r1.i = (int32_t) (result_int64 >> 32);
    r0.i = (int32_t) result_int64;
}
void memcpy_help()
{
    memcpy(malloc_0+r0.i, malloc_0+r1.i, r2.i);
}
void dsub()
{
    int64_t op1 = ((int64_t) r1.i) << 32 | ((int64_t) r0.i);
    int64_t op2 = ((int64_t) r3.i) << 32 | ((int64_t) r2.i);
    double result = *(double *)&op1 - *(double *)&op2;
    int64_t result_int64 = *(int64_t *)&result;
    r1.i = (int32_t) (result_int64 >> 32);
    r0.i = (int32_t) result_int64;
}

void main()
{
    malloc_start();
    counters[0] ++;
    store_counter ++;
    sp.i -= 8;
    str(&fp.i, &sp.i, 0*4, 4, false, false);
    str(&lr.i, &sp.i, 1*4, 4, false, false);
    fp.i = sp.i + 4;
    Input();
    counters[1] ++;
    X2Calc();
    counters[2] ++;
    X1Calc();
    counters[3] ++;
    Result();
    counters[4] ++;
    r3.i = 0;
    r0.i = r3.i;
    load_counter ++;
    ldr(&fp.i, &sp.i, 0*4, 4, false, false);
    ldr(&pc.i, &sp.i, 1*4, 4, false, false);
    sp.i += 8;
    return;

}

void X2Calc()
{
    counters[5] ++;
    store_counter ++;
    sp.i -= 8;
    str(&fp.i, &sp.i, 0*4, 4, false, false);
    str(&lr.i, &sp.i, 1*4, 4, false, false);
    fp.i = sp.i + 4;
    sp.i = sp.i - 56;
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    load_counter ++;
    ldr(&r0.i, &r3.i, 72, 4, false, false);
    ldr(&r1.i, &r3.i, 76, 4, false, false);
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &r3.i, 48, 4, false, false);
    ldr(&r3.i, &r3.i, 52, 4, false, false);
    ddiv();
    counters[6] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    store_counter ++;
    str(&r2.i, &fp.i, -20, 4, false, false);
    str(&r3.i, &fp.i, -16, 4, false, false);
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    load_counter ++;
    ldr(&r0.i, &r3.i, 112, 4, false, false);
    ldr(&r1.i, &r3.i, 116, 4, false, false);
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &r3.i, 88, 4, false, false);
    ldr(&r3.i, &r3.i, 92, 4, false, false);
    ddiv();
    counters[7] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    store_counter ++;
    str(&r2.i, &fp.i, -28, 4, false, false);
    str(&r3.i, &fp.i, -24, 4, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -28, 4, false, false);
    ldr(&r3.i, &fp.i, -24, 4, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, -20, 4, false, false);
    ldr(&r1.i, &fp.i, -16, 4, false, false);
    dcmplt();
    counters[8] ++;
    r3.i = r0.i;
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L12;
    }
    counters[9] ++;
    r3.i = 1;
    store_counter ++;
    str(&r3.i, &fp.i, -32, 4, false, false);
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &r3.i, 48, 4, false, false);
    ldr(&r3.i, &r3.i, 52, 4, false, false);
    store_counter ++;
    str(&r2.i, &fp.i, -60, 4, false, false);
    str(&r3.i, &fp.i, -56, 4, false, false);
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false);
    goto L6;
L7:
    counters[10] ++;
    r2.i = (SimplexTable & 0xffff);
    r2.i = r2.i | (((uint32_t)SimplexTable >> 16) << 16);
    load_counter ++;
    ldr(&r1.i, &fp.i, -32, 4, false, false);
    r3.i = r1.i;
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r3.i + r1.i;
    load_counter ++;
    ldr(&r1.i, &fp.i, -8, 4, false, false);
    r3.i = r3.i + r1.i;
    r3.i = (uint32_t)r3.i << 3;
    r3.i = r2.i + r3.i;
    load_counter ++;
    ldr(&r0.i, &r3.i, 0, 4, false, true);
    ldr(&r1.i, &r3.i, 4, 4, false, true);
    load_counter ++;
    ldr(&r2.i, &fp.i, -60, 4, false, false);
    ldr(&r3.i, &fp.i, -56, 4, false, false);
    ddiv();
    counters[11] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r2.i;
    r1.i = r3.i;
    r2.i = (SimplexTable & 0xffff);
    r2.i = r2.i | (((uint32_t)SimplexTable >> 16) << 16);
    load_counter ++;
    ldr(&ip.i, &fp.i, -32, 4, false, false);
    r3.i = ip.i;
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r3.i + ip.i;
    load_counter ++;
    ldr(&ip.i, &fp.i, -8, 4, false, false);
    r3.i = r3.i + ip.i;
    r3.i = (uint32_t)r3.i << 3;
    r3.i = r2.i + r3.i;
    store_counter ++;
    str(&r0.i, &r3.i, 0, 4, false, true);
    str(&r1.i, &r3.i, 4, 4, false, true);
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false);
    r3.i = r3.i + 1;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false);
L6:
    counters[12] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false);
    tmp = r3.i - 4;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 4);
    v = (r3.i&0x80000000) != (4&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L7;
    }
    counters[13] ++;
    r0.i = 1;
    ShowTable();
    counters[14] ++;
    r3.i = 1;
    store_counter ++;
    str(&r3.i, &fp.i, -48, 4, false, false);
    r3.i = 1;
    store_counter ++;
    str(&r3.i, &fp.i, -52, 4, false, false);
    load_counter ++;
    ldr(&r1.i, &fp.i, -52, 4, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, -48, 4, false, false);
    GaussCalc();
    counters[15] ++;
    r0.i = 2;
    ShowTable();
    counters[16] ++;
    load_counter ++;
    ldr(&r1.i, &fp.i, -52, 4, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, -48, 4, false, false);
    Exchange();
    counters[17] ++;
    load_counter ++;
    ldr(&r1.i, &fp.i, -52, 4, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, -48, 4, false, false);
    Maxim();
    counters[18] ++;
    r0.i = 3;
    ShowTable();
    counters[19] ++;
    goto L13;
L12:
    counters[20] ++;
    r3.i = 2;
    store_counter ++;
    str(&r3.i, &fp.i, -32, 4, false, false);
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &r3.i, 88, 4, false, false);
    ldr(&r3.i, &r3.i, 92, 4, false, false);
    store_counter ++;
    str(&r2.i, &fp.i, -44, 4, false, false);
    str(&r3.i, &fp.i, -40, 4, false, false);
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false);
    goto L9;
L10:
    counters[21] ++;
    r2.i = (SimplexTable & 0xffff);
    r2.i = r2.i | (((uint32_t)SimplexTable >> 16) << 16);
    load_counter ++;
    ldr(&r1.i, &fp.i, -32, 4, false, false);
    r3.i = r1.i;
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r3.i + r1.i;
    load_counter ++;
    ldr(&r1.i, &fp.i, -8, 4, false, false);
    r3.i = r3.i + r1.i;
    r3.i = (uint32_t)r3.i << 3;
    r3.i = r2.i + r3.i;
    load_counter ++;
    ldr(&r0.i, &r3.i, 0, 4, false, true);
    ldr(&r1.i, &r3.i, 4, 4, false, true);
    load_counter ++;
    ldr(&r2.i, &fp.i, -44, 4, false, false);
    ldr(&r3.i, &fp.i, -40, 4, false, false);
    ddiv();
    counters[22] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r2.i;
    r1.i = r3.i;
    r2.i = (SimplexTable & 0xffff);
    r2.i = r2.i | (((uint32_t)SimplexTable >> 16) << 16);
    load_counter ++;
    ldr(&ip.i, &fp.i, -32, 4, false, false);
    r3.i = ip.i;
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r3.i + ip.i;
    load_counter ++;
    ldr(&ip.i, &fp.i, -8, 4, false, false);
    r3.i = r3.i + ip.i;
    r3.i = (uint32_t)r3.i << 3;
    r3.i = r2.i + r3.i;
    store_counter ++;
    str(&r0.i, &r3.i, 0, 4, false, true);
    str(&r1.i, &r3.i, 4, 4, false, true);
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false);
    r3.i = r3.i + 1;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false);
L9:
    counters[23] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false);
    tmp = r3.i - 4;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 4);
    v = (r3.i&0x80000000) != (4&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L10;
    }
    counters[24] ++;
    r0.i = 1;
    ShowTable();
    counters[25] ++;
    r3.i = 2;
    store_counter ++;
    str(&r3.i, &fp.i, -48, 4, false, false);
    r3.i = 1;
    store_counter ++;
    str(&r3.i, &fp.i, -52, 4, false, false);
    load_counter ++;
    ldr(&r1.i, &fp.i, -52, 4, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, -48, 4, false, false);
    GaussCalc();
    counters[26] ++;
    r0.i = 2;
    ShowTable();
    counters[27] ++;
    load_counter ++;
    ldr(&r1.i, &fp.i, -52, 4, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, -48, 4, false, false);
    Exchange();
    counters[28] ++;
    load_counter ++;
    ldr(&r1.i, &fp.i, -52, 4, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, -48, 4, false, false);
    Maxim();
    counters[29] ++;
    r0.i = 3;
    ShowTable();
L13:
    counters[30] ++;
    sp.i = fp.i - 4;
    load_counter ++;
    ldr(&fp.i, &sp.i, 0*4, 4, false, false);
    ldr(&pc.i, &sp.i, 1*4, 4, false, false);
    sp.i += 8;
    return;

}

void X1Calc()
{
    counters[31] ++;
    store_counter ++;
    sp.i -= 8;
    str(&fp.i, &sp.i, 0*4, 4, false, false);
    str(&lr.i, &sp.i, 1*4, 4, false, false);
    fp.i = sp.i + 4;
    sp.i = sp.i - 24;
    r3.i = 2;
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false);
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &r3.i, 80, 4, false, false);
    ldr(&r3.i, &r3.i, 84, 4, false, false);
    store_counter ++;
    str(&r2.i, &fp.i, -20, 4, false, false);
    str(&r3.i, &fp.i, -16, 4, false, false);
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false);
    goto L15;
L16:
    counters[32] ++;
    r2.i = (SimplexTable & 0xffff);
    r2.i = r2.i | (((uint32_t)SimplexTable >> 16) << 16);
    load_counter ++;
    ldr(&r1.i, &fp.i, -12, 4, false, false);
    r3.i = r1.i;
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r3.i + r1.i;
    load_counter ++;
    ldr(&r1.i, &fp.i, -8, 4, false, false);
    r3.i = r3.i + r1.i;
    r3.i = (uint32_t)r3.i << 3;
    r3.i = r2.i + r3.i;
    load_counter ++;
    ldr(&r0.i, &r3.i, 0, 4, false, true);
    ldr(&r1.i, &r3.i, 4, 4, false, true);
    load_counter ++;
    ldr(&r2.i, &fp.i, -20, 4, false, false);
    ldr(&r3.i, &fp.i, -16, 4, false, false);
    ddiv();
    counters[33] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r2.i;
    r1.i = r3.i;
    r2.i = (SimplexTable & 0xffff);
    r2.i = r2.i | (((uint32_t)SimplexTable >> 16) << 16);
    load_counter ++;
    ldr(&ip.i, &fp.i, -12, 4, false, false);
    r3.i = ip.i;
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r3.i + ip.i;
    load_counter ++;
    ldr(&ip.i, &fp.i, -8, 4, false, false);
    r3.i = r3.i + ip.i;
    r3.i = (uint32_t)r3.i << 3;
    r3.i = r2.i + r3.i;
    store_counter ++;
    str(&r0.i, &r3.i, 0, 4, false, true);
    str(&r1.i, &r3.i, 4, 4, false, true);
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false);
    r3.i = r3.i + 1;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false);
L15:
    counters[34] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false);
    tmp = r3.i - 4;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 4);
    v = (r3.i&0x80000000) != (4&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L16;
    }
    counters[35] ++;
    r0.i = 4;
    ShowTable();
    counters[36] ++;
    r3.i = 2;
    store_counter ++;
    str(&r3.i, &fp.i, -24, 4, false, false);
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -28, 4, false, false);
    load_counter ++;
    ldr(&r1.i, &fp.i, -28, 4, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, -24, 4, false, false);
    GaussCalc();
    counters[37] ++;
    r0.i = 5;
    ShowTable();
    counters[38] ++;
    load_counter ++;
    ldr(&r1.i, &fp.i, -28, 4, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, -24, 4, false, false);
    Exchange();
    counters[39] ++;
    load_counter ++;
    ldr(&r1.i, &fp.i, -28, 4, false, false);
    load_counter ++;
    ldr(&r0.i, &fp.i, -24, 4, false, false);
    Maxim();
    counters[40] ++;
    r0.i = 6;
    ShowTable();
    counters[41] ++;
    sp.i = fp.i - 4;
    load_counter ++;
    ldr(&fp.i, &sp.i, 0*4, 4, false, false);
    ldr(&pc.i, &sp.i, 1*4, 4, false, false);
    sp.i += 8;
    return;

}

void Result()
{
    counters[42] ++;
    store_counter ++;
    sp.i -= 8;
    str(&fp.i, &sp.i, 0*4, 4, false, false);
    str(&lr.i, &sp.i, 1*4, 4, false, false);
    fp.i = sp.i + 4;
    sp.i = sp.i - 40;
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -16, 4, false, false);
    r3.i = 1;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false);
    goto L18;
L23:
    counters[43] ++;
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false);
    goto L19;
L22:
    counters[44] ++;
    r2.i = (SimplexTable & 0xffff);
    r2.i = r2.i | (((uint32_t)SimplexTable >> 16) << 16);
    load_counter ++;
    ldr(&r1.i, &fp.i, -8, 4, false, false);
    r3.i = r1.i;
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r3.i + r1.i;
    load_counter ++;
    ldr(&r1.i, &fp.i, -12, 4, false, false);
    r3.i = r3.i + r1.i;
    r3.i = (uint32_t)r3.i << 3;
    r3.i = r2.i + r3.i;
    load_counter ++;
    ldr(&r0.i, &r3.i, 0, 4, false, true);
    ldr(&r1.i, &r3.i, 4, 4, false, true);
    r2.i = 0;
    r3.i = 0;
    r3.i = r3.i | (16368 << 16);
    dcmpeq();
    counters[45] ++;
    r3.i = r0.i;
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L20;
    }
    counters[46] ++;
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &fp.i, -8, 4, false, false);
    r1.i = 40;
    r2.i = r1.i * r2.i;
    r3.i = r3.i + r2.i;
    r3.i = r3.i + 32;
    load_counter ++;
    ldr(&r2.i, &r3.i, 0, 4, false, true);
    ldr(&r3.i, &r3.i, 4, 4, false, true);
    load_counter ++;
    ldr(&r1.i, &fp.i, -16, 4, false, false);
    r1.i = (uint32_t)r1.i << 3;
    r0.i = fp.i - 4;
    r1.i = r0.i + r1.i;
    r1.i = r1.i - 40;
    store_counter ++;
    str(&r2.i, &r1.i, 0, 4, false, true);
    str(&r3.i, &r1.i, 4, 4, false, true);
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false);
    r3.i = r3.i + 1;
    store_counter ++;
    str(&r3.i, &fp.i, -16, 4, false, false);
L20:
    counters[47] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false);
    r3.i = r3.i + 1;
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false);
L19:
    counters[48] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false);
    tmp = r3.i - 4;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 4);
    v = (r3.i&0x80000000) != (4&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L22;
    }
    counters[49] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false);
    r3.i = r3.i + 1;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false);
L18:
    counters[50] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false);
    tmp = r3.i - 2;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 2);
    v = (r3.i&0x80000000) != (2&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L23;
    }
    counters[51] ++;
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &r3.i, 32, 4, false, false);
    ldr(&r3.i, &r3.i, 36, 4, false, false);
    load_counter ++;
    ldr(&r1.i, &fp.i, -16, 4, false, false);
    r1.i = (uint32_t)r1.i << 3;
    r0.i = fp.i - 4;
    r1.i = r0.i + r1.i;
    r1.i = r1.i - 40;
    store_counter ++;
    str(&r2.i, &r1.i, 0, 4, false, true);
    str(&r3.i, &r1.i, 4, 4, false, true);
    r0.i = (LC1 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC1 >> 16) << 16);
    printf("%s\n", malloc_0+r0.i);
    counters[52] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -44, 4, false, false);
    ldr(&r3.i, &fp.i, -40, 4, false, false);
    r0.i = (LC2 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC2 >> 16) << 16);
    printf(malloc_0+r0.i, r1.i);
    counters[53] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -36, 4, false, false);
    ldr(&r3.i, &fp.i, -32, 4, false, false);
    r0.i = (LC3 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC3 >> 16) << 16);
    printf(malloc_0+r0.i, r1.i);
    counters[54] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -28, 4, false, false);
    ldr(&r3.i, &fp.i, -24, 4, false, false);
    r0.i = (LC4 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC4 >> 16) << 16);
    printf(malloc_0+r0.i, r1.i);
    counters[55] ++;
    sp.i = fp.i - 4;
    load_counter ++;
    ldr(&fp.i, &sp.i, 0*4, 4, false, false);
    ldr(&pc.i, &sp.i, 1*4, 4, false, false);
    sp.i += 8;
    return;

}

void Maxim()
{
    counters[56] ++;
    store_counter ++;
    sp.i -= 8;
    str(&fp.i, &sp.i, 0*4, 4, false, false);
    str(&lr.i, &sp.i, 1*4, 4, false, false);
    fp.i = sp.i + 4;
    sp.i = sp.i - 56;
    store_counter ++;
    str(&r0.i, &fp.i, -56, 4, false, false);
    store_counter ++;
    str(&r1.i, &fp.i, -60, 4, false, false);
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &fp.i, -60, 4, false, false);
    r2.i = (uint32_t)r2.i << 3;
    r3.i = r3.i + r2.i;
    load_counter ++;
    ldr(&r2.i, &r3.i, 0, 4, false, true);
    ldr(&r3.i, &r3.i, 4, 4, false, true);
    store_counter ++;
    str(&r2.i, &fp.i, -20, 4, false, false);
    str(&r3.i, &fp.i, -16, 4, false, false);
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &r3.i, 32, 4, false, false);
    ldr(&r3.i, &r3.i, 36, 4, false, false);
    store_counter ++;
    str(&r2.i, &fp.i, -28, 4, false, false);
    str(&r3.i, &fp.i, -24, 4, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -56, 4, false, false);
    tmp = r3.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 1);
    v = (r3.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L26;
    }
    counters[57] ++;
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &r3.i, 0, 4, false, true);
    ldr(&r3.i, &r3.i, 4, 4, false, true);
    store_counter ++;
    str(&r2.i, &fp.i, -52, 4, false, false);
    str(&r3.i, &fp.i, -48, 4, false, false);
    r3.i = 1;
    store_counter ++;
    str(&r3.i, &fp.i, -40, 4, false, false);
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false);
    goto L27;
L28:
    counters[58] ++;
    r3.i = (TempState & 0xffff);
    r3.i = r3.i | (((uint32_t)TempState >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &fp.i, -8, 4, false, false);
    r2.i = (uint32_t)r2.i << 3;
    r3.i = r3.i + r2.i;
    load_counter ++;
    ldr(&r0.i, &r3.i, 0, 4, false, true);
    ldr(&r1.i, &r3.i, 4, 4, false, true);
    load_counter ++;
    ldr(&r2.i, &fp.i, -20, 4, false, false);
    ldr(&r3.i, &fp.i, -16, 4, false, false);
    dmul();
    counters[59] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r2.i;
    r1.i = r3.i;
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &fp.i, -8, 4, false, false);
    r2.i = (uint32_t)r2.i << 3;
    r3.i = r3.i + r2.i;
    store_counter ++;
    str(&r0.i, &r3.i, 0, 4, false, true);
    str(&r1.i, &r3.i, 4, 4, false, true);
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false);
    r3.i = r3.i + 1;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false);
L27:
    counters[60] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false);
    tmp = r3.i - 4;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 4);
    v = (r3.i&0x80000000) != (4&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L28;
    }
    counters[61] ++;
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    load_counter ++;
    ldr(&r0.i, &r3.i, 0, 4, false, true);
    ldr(&r1.i, &r3.i, 4, 4, false, true);
    load_counter ++;
    ldr(&r2.i, &fp.i, -52, 4, false, false);
    ldr(&r3.i, &fp.i, -48, 4, false, false);
    dadd();
    counters[62] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r2.i;
    r1.i = r3.i;
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    store_counter ++;
    str(&r0.i, &r3.i, 0, 4, false, true);
    str(&r1.i, &r3.i, 4, 4, false, true);
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &fp.i, -60, 4, false, false);
    r2.i = (uint32_t)r2.i << 3;
    r1.i = r3.i + r2.i;
    r2.i = 0;
    r3.i = 0;
    store_counter ++;
    str(&r2.i, &r1.i, 0, 4, false, true);
    str(&r3.i, &r1.i, 4, 4, false, true);
    goto L29;
L26:
    counters[63] ++;
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &r3.i, 16, 4, false, false);
    ldr(&r3.i, &r3.i, 20, 4, false, false);
    store_counter ++;
    str(&r2.i, &fp.i, -36, 4, false, false);
    str(&r3.i, &fp.i, -32, 4, false, false);
    r3.i = 2;
    store_counter ++;
    str(&r3.i, &fp.i, -40, 4, false, false);
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false);
    goto L30;
L31:
    counters[64] ++;
    r3.i = (TempState & 0xffff);
    r3.i = r3.i | (((uint32_t)TempState >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &fp.i, -8, 4, false, false);
    r2.i = (uint32_t)r2.i << 3;
    r3.i = r3.i + r2.i;
    load_counter ++;
    ldr(&r0.i, &r3.i, 0, 4, false, true);
    ldr(&r1.i, &r3.i, 4, 4, false, true);
    load_counter ++;
    ldr(&r2.i, &fp.i, -20, 4, false, false);
    ldr(&r3.i, &fp.i, -16, 4, false, false);
    dmul();
    counters[65] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r2.i;
    r1.i = r3.i;
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &fp.i, -8, 4, false, false);
    r2.i = (uint32_t)r2.i << 3;
    r3.i = r3.i + r2.i;
    store_counter ++;
    str(&r0.i, &r3.i, 0, 4, false, true);
    str(&r1.i, &r3.i, 4, 4, false, true);
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false);
    r3.i = r3.i + 1;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false);
L30:
    counters[66] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false);
    tmp = r3.i - 4;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 4);
    v = (r3.i&0x80000000) != (4&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L31;
    }
    counters[67] ++;
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    load_counter ++;
    ldr(&r0.i, &r3.i, 16, 4, false, false);
    ldr(&r1.i, &r3.i, 20, 4, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -36, 4, false, false);
    ldr(&r3.i, &fp.i, -32, 4, false, false);
    dadd();
    counters[68] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r2.i;
    r1.i = r3.i;
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    store_counter ++;
    str(&r0.i, &r3.i, 16, 4, false, false);
    str(&r1.i, &r3.i, 20, 4, false, false);
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &fp.i, -60, 4, false, false);
    r2.i = (uint32_t)r2.i << 3;
    r1.i = r3.i + r2.i;
    r2.i = 0;
    r3.i = 0;
    store_counter ++;
    str(&r2.i, &r1.i, 0, 4, false, true);
    str(&r3.i, &r1.i, 4, 4, false, true);
L29:
    counters[69] ++;
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    load_counter ++;
    ldr(&r0.i, &r3.i, 32, 4, false, false);
    ldr(&r1.i, &r3.i, 36, 4, false, false);
    r2.i = 0;
    r3.i = 0;
    dcmpeq();
    counters[70] ++;
    r3.i = r0.i;
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L34;
    }
    counters[71] ++;
    goto L35;
L34:
    counters[72] ++;
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    load_counter ++;
    ldr(&r0.i, &r3.i, 32, 4, false, false);
    ldr(&r1.i, &r3.i, 36, 4, false, false);
    load_counter ++;
    ldr(&r2.i, &fp.i, -28, 4, false, false);
    ldr(&r3.i, &fp.i, -24, 4, false, false);
    dadd();
    counters[73] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r2.i;
    r1.i = r3.i;
    r3.i = (SimplexTable & 0xffff);
    r3.i = r3.i | (((uint32_t)SimplexTable >> 16) << 16);
    store_counter ++;
    str(&r0.i, &r3.i, 32, 4, false, false);
    str(&r1.i, &r3.i, 36, 4, false, false);
L35:
    counters[74] ++;
    sp.i = fp.i - 4;
    load_counter ++;
    ldr(&fp.i, &sp.i, 0*4, 4, false, false);
    ldr(&pc.i, &sp.i, 1*4, 4, false, false);
    sp.i += 8;
    return;

}

void GaussCalc()
{
    counters[75] ++;
    store_counter ++;
    sp.i -= 16;
    str(&r4.i, &sp.i, 0*4, 4, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false);
    str(&fp.i, &sp.i, 2*4, 4, false, false);
    str(&lr.i, &sp.i, 3*4, 4, false, false);
    fp.i = sp.i + 12;
    sp.i = sp.i - 32;
    store_counter ++;
    str(&r0.i, &fp.i, -40, 4, false, false);
    store_counter ++;
    str(&r1.i, &fp.i, -44, 4, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -40, 4, false, false);
    tmp = r3.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 1);
    v = (r3.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L37;
    }
    counters[76] ++;
    r3.i = 2;
    store_counter ++;
    str(&r3.i, &fp.i, -20, 4, false, false);
    r2.i = (SimplexTable & 0xffff);
    r2.i = r2.i | (((uint32_t)SimplexTable >> 16) << 16);
    load_counter ++;
    ldr(&r1.i, &fp.i, -20, 4, false, false);
    r3.i = r1.i;
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r3.i + r1.i;
    load_counter ++;
    ldr(&r1.i, &fp.i, -44, 4, false, false);
    r3.i = r3.i + r1.i;
    r3.i = (uint32_t)r3.i << 3;
    r3.i = r2.i + r3.i;
    load_counter ++;
    ldr(&r0.i, &r3.i, 0, 4, false, true);
    ldr(&r1.i, &r3.i, 4, 4, false, true);
    r2.i = (SimplexTable & 0xffff);
    r2.i = r2.i | (((uint32_t)SimplexTable >> 16) << 16);
    load_counter ++;
    ldr(&ip.i, &fp.i, -40, 4, false, false);
    r3.i = ip.i;
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r3.i + ip.i;
    load_counter ++;
    ldr(&ip.i, &fp.i, -44, 4, false, false);
    r3.i = r3.i + ip.i;
    r3.i = (uint32_t)r3.i << 3;
    r3.i = r2.i + r3.i;
    load_counter ++;
    ldr(&r2.i, &r3.i, 0, 4, false, true);
    ldr(&r3.i, &r3.i, 4, 4, false, true);
    ddiv();
    counters[77] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    store_counter ++;
    str(&r2.i, &fp.i, -36, 4, false, false);
    str(&r3.i, &fp.i, -32, 4, false, false);
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -16, 4, false, false);
    goto L38;
L39:
    counters[78] ++;
    r2.i = (SimplexTable & 0xffff);
    r2.i = r2.i | (((uint32_t)SimplexTable >> 16) << 16);
    load_counter ++;
    ldr(&r1.i, &fp.i, -20, 4, false, false);
    r3.i = r1.i;
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r3.i + r1.i;
    load_counter ++;
    ldr(&r1.i, &fp.i, -16, 4, false, false);
    r3.i = r3.i + r1.i;
    r3.i = (uint32_t)r3.i << 3;
    r3.i = r2.i + r3.i;
    load_counter ++;
    ldr(&r4.i, &r3.i, 0, 4, false, true);
    ldr(&r5.i, &r3.i, 4, 4, false, true);
    r2.i = (SimplexTable & 0xffff);
    r2.i = r2.i | (((uint32_t)SimplexTable >> 16) << 16);
    load_counter ++;
    ldr(&r1.i, &fp.i, -40, 4, false, false);
    r3.i = r1.i;
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r3.i + r1.i;
    load_counter ++;
    ldr(&r1.i, &fp.i, -16, 4, false, false);
    r3.i = r3.i + r1.i;
    r3.i = (uint32_t)r3.i << 3;
    r3.i = r2.i + r3.i;
    load_counter ++;
    ldr(&r0.i, &r3.i, 0, 4, false, true);
    ldr(&r1.i, &r3.i, 4, 4, false, true);
    load_counter ++;
    ldr(&r2.i, &fp.i, -36, 4, false, false);
    ldr(&r3.i, &fp.i, -32, 4, false, false);
    dmul();
    counters[79] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r4.i;
    r1.i = r5.i;
    dsub();
    counters[80] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r2.i;
    r1.i = r3.i;
    r2.i = (SimplexTable & 0xffff);
    r2.i = r2.i | (((uint32_t)SimplexTable >> 16) << 16);
    load_counter ++;
    ldr(&ip.i, &fp.i, -20, 4, false, false);
    r3.i = ip.i;
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r3.i + ip.i;
    load_counter ++;
    ldr(&ip.i, &fp.i, -16, 4, false, false);
    r3.i = r3.i + ip.i;
    r3.i = (uint32_t)r3.i << 3;
    r3.i = r2.i + r3.i;
    store_counter ++;
    str(&r0.i, &r3.i, 0, 4, false, true);
    str(&r1.i, &r3.i, 4, 4, false, true);
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false);
    r3.i = r3.i + 1;
    store_counter ++;
    str(&r3.i, &fp.i, -16, 4, false, false);
L38:
    counters[81] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false);
    tmp = r3.i - 4;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 4);
    v = (r3.i&0x80000000) != (4&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L39;
    }
    counters[82] ++;
    goto L43;
L37:
    counters[83] ++;
    r3.i = 1;
    store_counter ++;
    str(&r3.i, &fp.i, -20, 4, false, false);
    r2.i = (SimplexTable & 0xffff);
    r2.i = r2.i | (((uint32_t)SimplexTable >> 16) << 16);
    load_counter ++;
    ldr(&r1.i, &fp.i, -20, 4, false, false);
    r3.i = r1.i;
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r3.i + r1.i;
    load_counter ++;
    ldr(&r1.i, &fp.i, -44, 4, false, false);
    r3.i = r3.i + r1.i;
    r3.i = (uint32_t)r3.i << 3;
    r3.i = r2.i + r3.i;
    load_counter ++;
    ldr(&r0.i, &r3.i, 0, 4, false, true);
    ldr(&r1.i, &r3.i, 4, 4, false, true);
    r2.i = (SimplexTable & 0xffff);
    r2.i = r2.i | (((uint32_t)SimplexTable >> 16) << 16);
    load_counter ++;
    ldr(&ip.i, &fp.i, -40, 4, false, false);
    r3.i = ip.i;
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r3.i + ip.i;
    load_counter ++;
    ldr(&ip.i, &fp.i, -44, 4, false, false);
    r3.i = r3.i + ip.i;
    r3.i = (uint32_t)r3.i << 3;
    r3.i = r2.i + r3.i;
    load_counter ++;
    ldr(&r2.i, &r3.i, 0, 4, false, true);
    ldr(&r3.i, &r3.i, 4, 4, false, true);
    ddiv();
    counters[84] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    store_counter ++;
    str(&r2.i, &fp.i, -28, 4, false, false);
    str(&r3.i, &fp.i, -24, 4, false, false);
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -16, 4, false, false);
    goto L41;
L42:
    counters[85] ++;
    r2.i = (SimplexTable & 0xffff);
    r2.i = r2.i | (((uint32_t)SimplexTable >> 16) << 16);
    load_counter ++;
    ldr(&r1.i, &fp.i, -20, 4, false, false);
    r3.i = r1.i;
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r3.i + r1.i;
    load_counter ++;
    ldr(&r1.i, &fp.i, -16, 4, false, false);
    r3.i = r3.i + r1.i;
    r3.i = (uint32_t)r3.i << 3;
    r3.i = r2.i + r3.i;
    load_counter ++;
    ldr(&r4.i, &r3.i, 0, 4, false, true);
    ldr(&r5.i, &r3.i, 4, 4, false, true);
    r2.i = (SimplexTable & 0xffff);
    r2.i = r2.i | (((uint32_t)SimplexTable >> 16) << 16);
    load_counter ++;
    ldr(&r1.i, &fp.i, -40, 4, false, false);
    r3.i = r1.i;
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r3.i + r1.i;
    load_counter ++;
    ldr(&r1.i, &fp.i, -16, 4, false, false);
    r3.i = r3.i + r1.i;
    r3.i = (uint32_t)r3.i << 3;
    r3.i = r2.i + r3.i;
    load_counter ++;
    ldr(&r0.i, &r3.i, 0, 4, false, true);
    ldr(&r1.i, &r3.i, 4, 4, false, true);
    load_counter ++;
    ldr(&r2.i, &fp.i, -28, 4, false, false);
    ldr(&r3.i, &fp.i, -24, 4, false, false);
    dmul();
    counters[86] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r4.i;
    r1.i = r5.i;
    dsub();
    counters[87] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r2.i;
    r1.i = r3.i;
    r2.i = (SimplexTable & 0xffff);
    r2.i = r2.i | (((uint32_t)SimplexTable >> 16) << 16);
    load_counter ++;
    ldr(&ip.i, &fp.i, -20, 4, false, false);
    r3.i = ip.i;
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r3.i + ip.i;
    load_counter ++;
    ldr(&ip.i, &fp.i, -16, 4, false, false);
    r3.i = r3.i + ip.i;
    r3.i = (uint32_t)r3.i << 3;
    r3.i = r2.i + r3.i;
    store_counter ++;
    str(&r0.i, &r3.i, 0, 4, false, true);
    str(&r1.i, &r3.i, 4, 4, false, true);
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false);
    r3.i = r3.i + 1;
    store_counter ++;
    str(&r3.i, &fp.i, -16, 4, false, false);
L41:
    counters[88] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -16, 4, false, false);
    tmp = r3.i - 4;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 4);
    v = (r3.i&0x80000000) != (4&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L42;
    }
L43:
    counters[89] ++;
    sp.i = fp.i - 12;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false);
    ldr(&fp.i, &sp.i, 2*4, 4, false, false);
    ldr(&pc.i, &sp.i, 3*4, 4, false, false);
    sp.i += 16;
    return;

}

void Exchange()
{
    counters[90] ++;
    store_counter ++;
    sp.i -= 28;
    str(&r4.i, &sp.i, 0*4, 4, false, false);
    str(&r5.i, &sp.i, 1*4, 4, false, false);
    str(&r6.i, &sp.i, 2*4, 4, false, false);
    str(&r7.i, &sp.i, 3*4, 4, false, false);
    str(&r8.i, &sp.i, 4*4, 4, false, false);
    str(&r9.i, &sp.i, 5*4, 4, false, false);
    str(&fp.i, &sp.i, 6*4, 4, false, false);
    fp.i = sp.i + 24;
    sp.i = sp.i - 28;
    store_counter ++;
    str(&r0.i, &fp.i, -40, 4, false, false);
    store_counter ++;
    str(&r1.i, &fp.i, -44, 4, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -40, 4, false, false);
    tmp = r3.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 1);
    v = (r3.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L45;
    }
    counters[91] ++;
    r3.i = 1;
    store_counter ++;
    str(&r3.i, &fp.i, -36, 4, false, false);
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -32, 4, false, false);
    goto L46;
L47:
    counters[92] ++;
    r2.i = (SimplexTable & 0xffff);
    r2.i = r2.i | (((uint32_t)SimplexTable >> 16) << 16);
    load_counter ++;
    ldr(&r1.i, &fp.i, -36, 4, false, false);
    r3.i = r1.i;
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r3.i + r1.i;
    load_counter ++;
    ldr(&r1.i, &fp.i, -32, 4, false, false);
    r3.i = r3.i + r1.i;
    r3.i = (uint32_t)r3.i << 3;
    r3.i = r2.i + r3.i;
    load_counter ++;
    ldr(&r2.i, &r3.i, 0, 4, false, true);
    ldr(&r3.i, &r3.i, 4, 4, false, true);
    store_counter ++;
    str(&r2.i, &fp.i, -52, 4, false, false);
    r3.i = r3.i ^ -2147483648;
    store_counter ++;
    str(&r3.i, &fp.i, -48, 4, false, false);
    r3.i = (TempState & 0xffff);
    r3.i = r3.i | (((uint32_t)TempState >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &fp.i, -32, 4, false, false);
    r2.i = (uint32_t)r2.i << 3;
    r3.i = r3.i + r2.i;
    load_counter ++;
    ldr(&r0.i, &fp.i, -52, 4, false, false);
    ldr(&r1.i, &fp.i, -48, 4, false, false);
    store_counter ++;
    str(&r0.i, &r3.i, 0, 4, false, true);
    str(&r1.i, &r3.i, 4, 4, false, true);
    load_counter ++;
    ldr(&r3.i, &fp.i, -32, 4, false, false);
    r3.i = r3.i + 1;
    store_counter ++;
    str(&r3.i, &fp.i, -32, 4, false, false);
L46:
    counters[93] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -32, 4, false, false);
    tmp = r3.i - 4;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 4);
    v = (r3.i&0x80000000) != (4&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L47;
    }
    counters[94] ++;
    r3.i = (TempState & 0xffff);
    r3.i = r3.i | (((uint32_t)TempState >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &r3.i, 32, 4, false, false);
    ldr(&r3.i, &r3.i, 36, 4, false, false);
    r8.i = r2.i;
    r9.i = r3.i ^ -2147483648;
    r3.i = (TempState & 0xffff);
    r3.i = r3.i | (((uint32_t)TempState >> 16) << 16);
    store_counter ++;
    str(&r8.i, &r3.i, 32, 4, false, false);
    str(&r9.i, &r3.i, 36, 4, false, false);
    goto L51;
L45:
    counters[95] ++;
    r3.i = 2;
    store_counter ++;
    str(&r3.i, &fp.i, -36, 4, false, false);
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -32, 4, false, false);
    goto L49;
L50:
    counters[96] ++;
    r2.i = (SimplexTable & 0xffff);
    r2.i = r2.i | (((uint32_t)SimplexTable >> 16) << 16);
    load_counter ++;
    ldr(&r1.i, &fp.i, -36, 4, false, false);
    r3.i = r1.i;
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r3.i + r1.i;
    load_counter ++;
    ldr(&r1.i, &fp.i, -32, 4, false, false);
    r3.i = r3.i + r1.i;
    r3.i = (uint32_t)r3.i << 3;
    r3.i = r2.i + r3.i;
    load_counter ++;
    ldr(&r2.i, &r3.i, 0, 4, false, true);
    ldr(&r3.i, &r3.i, 4, 4, false, true);
    r6.i = r2.i;
    r7.i = r3.i ^ -2147483648;
    r3.i = (TempState & 0xffff);
    r3.i = r3.i | (((uint32_t)TempState >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &fp.i, -32, 4, false, false);
    r2.i = (uint32_t)r2.i << 3;
    r3.i = r3.i + r2.i;
    store_counter ++;
    str(&r6.i, &r3.i, 0, 4, false, true);
    str(&r7.i, &r3.i, 4, 4, false, true);
    load_counter ++;
    ldr(&r3.i, &fp.i, -32, 4, false, false);
    r3.i = r3.i + 1;
    store_counter ++;
    str(&r3.i, &fp.i, -32, 4, false, false);
L49:
    counters[97] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -32, 4, false, false);
    tmp = r3.i - 4;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 4);
    v = (r3.i&0x80000000) != (4&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L50;
    }
    counters[98] ++;
    r3.i = (TempState & 0xffff);
    r3.i = r3.i | (((uint32_t)TempState >> 16) << 16);
    load_counter ++;
    ldr(&r2.i, &r3.i, 32, 4, false, false);
    ldr(&r3.i, &r3.i, 36, 4, false, false);
    r4.i = r2.i;
    r5.i = r3.i ^ -2147483648;
    r3.i = (TempState & 0xffff);
    r3.i = r3.i | (((uint32_t)TempState >> 16) << 16);
    store_counter ++;
    str(&r4.i, &r3.i, 32, 4, false, false);
    str(&r5.i, &r3.i, 36, 4, false, false);
L51:
    counters[99] ++;
    sp.i = fp.i - 24;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0*4, 4, false, false);
    ldr(&r5.i, &sp.i, 1*4, 4, false, false);
    ldr(&r6.i, &sp.i, 2*4, 4, false, false);
    ldr(&r7.i, &sp.i, 3*4, 4, false, false);
    ldr(&r8.i, &sp.i, 4*4, 4, false, false);
    ldr(&r9.i, &sp.i, 5*4, 4, false, false);
    ldr(&fp.i, &sp.i, 6*4, 4, false, false);
    sp.i += 28;
    return;

}

void ShowTable()
{
    counters[100] ++;
    store_counter ++;
    sp.i -= 8;
    str(&fp.i, &sp.i, 0*4, 4, false, false);
    str(&lr.i, &sp.i, 1*4, 4, false, false);
    fp.i = sp.i + 4;
    sp.i = sp.i - 16;
    r3.i = r0.i;
    store_counter ++;
    str(&r3.i, &fp.i, -14, 2, false, false);
    load_counter ++;
    ldr(&r3.i, &fp.i, -14, 4, false, false);
    r1.i = r3.i;
    r0.i = (LC5 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC5 >> 16) << 16);
    printf(malloc_0+r0.i, r1.i);
    counters[101] ++;
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false);
    goto L53;
L56:
    counters[102] ++;
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false);
    goto L54;
L55:
    counters[103] ++;
    r2.i = (SimplexTable & 0xffff);
    r2.i = r2.i | (((uint32_t)SimplexTable >> 16) << 16);
    load_counter ++;
    ldr(&r1.i, &fp.i, -8, 4, false, false);
    r3.i = r1.i;
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r3.i + r1.i;
    load_counter ++;
    ldr(&r1.i, &fp.i, -12, 4, false, false);
    r3.i = r3.i + r1.i;
    r3.i = (uint32_t)r3.i << 3;
    r3.i = r2.i + r3.i;
    load_counter ++;
    ldr(&r2.i, &r3.i, 0, 4, false, true);
    ldr(&r3.i, &r3.i, 4, 4, false, true);
    r0.i = (LC6 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC6 >> 16) << 16);
    printf(malloc_0+r0.i, r1.i);
    counters[104] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false);
    r3.i = r3.i + 1;
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false);
L54:
    counters[105] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false);
    tmp = r3.i - 4;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 4);
    v = (r3.i&0x80000000) != (4&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L55;
    }
    counters[106] ++;
    r0.i = 10;
    printf("%c", (char)r0.i);
    counters[107] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false);
    r3.i = r3.i + 1;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false);
L53:
    counters[108] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false);
    tmp = r3.i - 2;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 2);
    v = (r3.i&0x80000000) != (2&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L56;
    }
    counters[109] ++;
    sp.i = fp.i - 4;
    load_counter ++;
    ldr(&fp.i, &sp.i, 0*4, 4, false, false);
    ldr(&pc.i, &sp.i, 1*4, 4, false, false);
    sp.i += 8;
    return;

}

void Input()
{
    counters[110] ++;
    store_counter ++;
    sp.i -= 8;
    str(&fp.i, &sp.i, 0*4, 4, false, false);
    str(&lr.i, &sp.i, 1*4, 4, false, false);
    fp.i = sp.i + 4;
    sp.i = sp.i - 128;
    r3.i = (LC0 & 0xffff);
    r3.i = r3.i | (((uint32_t)LC0 >> 16) << 16);
    r0.i = fp.i - 132;
    r1.i = r3.i;
    r3.i = 120;
    r2.i = r3.i;
    memcpy_help();
    counters[111] ++;
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false);
    goto L58;
L61:
    counters[112] ++;
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false);
    goto L59;
L60:
    counters[113] ++;
    load_counter ++;
    ldr(&r2.i, &fp.i, -8, 4, false, false);
    r3.i = r2.i;
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r3.i + r2.i;
    load_counter ++;
    ldr(&r2.i, &fp.i, -12, 4, false, false);
    r3.i = r3.i + r2.i;
    r3.i = (uint32_t)r3.i << 3;
    r2.i = fp.i - 4;
    r3.i = r2.i + r3.i;
    r3.i = r3.i - 128;
    load_counter ++;
    ldr(&r0.i, &r3.i, 0, 4, false, true);
    ldr(&r1.i, &r3.i, 4, 4, false, true);
    r2.i = (SimplexTable & 0xffff);
    r2.i = r2.i | (((uint32_t)SimplexTable >> 16) << 16);
    load_counter ++;
    ldr(&ip.i, &fp.i, -8, 4, false, false);
    r3.i = ip.i;
    r3.i = (uint32_t)r3.i << 2;
    r3.i = r3.i + ip.i;
    load_counter ++;
    ldr(&ip.i, &fp.i, -12, 4, false, false);
    r3.i = r3.i + ip.i;
    r3.i = (uint32_t)r3.i << 3;
    r3.i = r2.i + r3.i;
    store_counter ++;
    str(&r0.i, &r3.i, 0, 4, false, true);
    str(&r1.i, &r3.i, 4, 4, false, true);
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false);
    r3.i = r3.i + 1;
    store_counter ++;
    str(&r3.i, &fp.i, -12, 4, false, false);
L59:
    counters[114] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -12, 4, false, false);
    tmp = r3.i - 4;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 4);
    v = (r3.i&0x80000000) != (4&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L60;
    }
    counters[115] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false);
    r3.i = r3.i + 1;
    store_counter ++;
    str(&r3.i, &fp.i, -8, 4, false, false);
L58:
    counters[116] ++;
    load_counter ++;
    ldr(&r3.i, &fp.i, -8, 4, false, false);
    tmp = r3.i - 2;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 2);
    v = (r3.i&0x80000000) != (2&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L61;
    }
    counters[117] ++;
    r0.i = 0;
    ShowTable();
    counters[118] ++;
    sp.i = fp.i - 4;
    load_counter ++;
    ldr(&fp.i, &sp.i, 0*4, 4, false, false);
    ldr(&pc.i, &sp.i, 1*4, 4, false, false);
    sp.i += 8;
    counter_summary();
    return;

}

