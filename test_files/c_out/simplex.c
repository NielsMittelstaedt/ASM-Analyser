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

reg r10, r6, r2, r5, r9, r3, r8, r1, r7, r0, r4;

int32_t LC0, LC1, LC2, LC3, LC4, LC5, LC6, LC7, LC8, LC9, LC10, LC11, LC12, L56, LC13, LC14, LC15, LC16, LC17, LC18, LC19, LC20, LC21, LC22, LC23, LC24, LC25, LC26, LC27, LC28, LC29, LC30, __PRETTY_FUNCTION__6810, __PRETTY_FUNCTION__6763, tab, counter6743;

int counters[158] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[158] = {9,2,8,3,6,4,2,4,13,2,8,3,3,5,3,2,3,10,3,3,3,7,3,4,4,2,3,9,7,1,4,5,6,4,4,1,15,2,4,8,4,3,1,6,7,2,4,14,3,3,6,5,5,3,5,2,7,7,6,4,4,4,5,6,5,5,2,10,3,16,1,2,3,5,4,7,5,7,5,2,1,3,6,2,8,3,3,3,5,8,2,9,4,4,9,4,4,2,1,4,8,3,3,9,6,7,1,2,1,2,9,3,9,4,5,3,3,9,4,7,1,2,4,7,4,2,10,1,8,8,2,9,4,5,4,2,4,5,6,2,2,5,3,2,5,4,3,4,2,6,5,5,4,2,1,7,2,2};

int check_b_positivepart;

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
    malloc_0 = (uint8_t*) malloc(1);
    uint8_t* stack_ptr = (uint8_t*) malloc(20000);
    sp.i = (int32_t) (stack_ptr - malloc_0) + 19996;
    fp = sp;

    int32_t malloc_total = (int32_t) ((uint8_t*) malloc(1007) - malloc_0);
    LC0 = malloc_total;
    strcpy(malloc_0+LC0, "../test_files/c_in/simplex.c\000");

    LC1 = malloc_total + 34;
    strcpy(malloc_0+LC1, "tab->mat[i][0] >= 0\000");

    LC2 = malloc_total + 59;
    strcpy(malloc_0+LC2, "\012%d. Tableau %s:\012\000");

    LC3 = malloc_total + 88;
    strcpy(malloc_0+LC3, "b[i]\000");

    LC4 = malloc_total + 98;
    strcpy(malloc_0+LC4, "col:\000");

    LC5 = malloc_total + 108;
    strcpy(malloc_0+LC5, "%-6s%5s\000");

    LC6 = malloc_total + 121;
    strcpy(malloc_0+LC6, "    x%d,\000");

    LC7 = malloc_total + 135;
    strcpy(malloc_0+LC7, "max:\000");

    LC8 = malloc_total + 145;
    strcpy(malloc_0+LC8, "b%d: \000");

    LC9 = malloc_total + 156;
    strcpy(malloc_0+LC9, " %6d\000");

    LC10 = malloc_total + 166;
    strcpy(malloc_0+LC10, " %6.2lf\000");

    LC11 = malloc_total + 179;
    strcpy(malloc_0+LC11, "pivot>0\000");

    LC12 = malloc_total + 192;
    strcpy(malloc_0+LC12, "equal(tab->mat[row][col], 1. )\000");

    LC13 = malloc_total + 228;
    strcpy(malloc_0+LC13, "Most negative column in row[0] is col %d = %g.\012\000");

    L56 = malloc_total + 284;
    int32_t arrayL56[] = {LC0};
    for(int i=0; i<1; i++) str(&arrayL56[i], &L56, i*4, 4, false, false, false);

    LC14 = malloc_total + 288;
    strcpy(malloc_0+LC14, "Ratios A[row_i,0]/A[row_i,%d] = [\000");

    LC15 = malloc_total + 327;
    strcpy(malloc_0+LC15, "%3.2lf, \000");

    LC16 = malloc_total + 341;
    strcpy(malloc_0+LC16, "].\000");

    LC17 = malloc_total + 349;
    strcpy(malloc_0+LC17, "Found pivot A[%d,%d], min positive ratio=%g in row=");

    LC18 = malloc_total + 402;
    strcpy(malloc_0+LC18, "%s at \000");

    LC19 = malloc_total + 414;
    strcpy(malloc_0+LC19, "x%d=%3.2lf, \000");

    LC20 = malloc_total + 432;
    strcpy(malloc_0+LC20, "x%d=0, \000");

    LC21 = malloc_total + 445;
    strcpy(malloc_0+LC21, "Padded with slack variables\000");

    LC22 = malloc_total + 478;
    strcpy(malloc_0+LC22, "Found optimal value=A[0,0]=%3.2lf (no negatives in ");

    LC23 = malloc_total + 531;
    strcpy(malloc_0+LC23, "Optimal vector\000");

    LC24 = malloc_total + 551;
    strcpy(malloc_0+LC24, "Entering variable x%d to be made basic, so pivot_co");

    LC25 = malloc_total + 604;
    strcpy(malloc_0+LC25, "unbounded (no pivot_row).\000");

    LC26 = malloc_total + 635;
    strcpy(malloc_0+LC26, "Leaving variable x%d, so pivot_row=%d\012\000");

    LC27 = malloc_total + 682;
    strcpy(malloc_0+LC27, "After pivoting\000");

    LC28 = malloc_total + 702;
    strcpy(malloc_0+LC28, "Basic feasible solution\000");

    LC29 = malloc_total + 731;
    strcpy(malloc_0+LC29, "Too many iterations > %d.\012\000");

    LC30 = malloc_total + 766;
    strcpy(malloc_0+LC30, "Initial\000");

    __PRETTY_FUNCTION__6810 = malloc_total + 779;
    strcpy(malloc_0+__PRETTY_FUNCTION__6810, "check_b_positive\000");

    __PRETTY_FUNCTION__6763 = malloc_total + 801;
    strcpy(malloc_0+__PRETTY_FUNCTION__6763, "pivot_on\000");

    tab = malloc_total + 815;
    int32_t arraytab[] = {4,5,0,0,0,-1075838976,0,-1073217536,0,-1074790400,0,-1072693248,120,0,1078198272,0,1072693248,0,1072693248,0,1072693248,0,1072693248,120,0,1076101120,0,-1073741824,0,-1074790400,0,1072693248,0,1072693248,120,0,1076101120,0,0,0,1072693248,0,0,0,-1074790400,120,2560};
    for(int i=0; i<47; i++) str(&arraytab[i], &tab, i*4, 4, false, false, false);

    counter6743 = malloc_total + 1003;
    counter6743 = (int32_t) ((uint8_t*) calloc(4, sizeof(int8_t)) - malloc_0);

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

void equal();
void nl();
void print_tableau();
void pivot_on();
void find_pivot_column();
void find_pivot_row();
void add_slack_variables();
void check_b_positive();
void find_basis_variable();
void print_optimal_vector();
void simplex();
void main();

void dsub()
{
    uint64_t op1 = ((uint64_t)(uint32_t) r1.i) << 32 | ((uint64_t)(uint32_t) r0.i);
    uint64_t op2 = ((uint64_t)(uint32_t) r3.i) << 32 | ((uint64_t)(uint32_t) r2.i);
    double result = *(double *)&op1 - *(double *)&op2;
    uint64_t result_uint64 = *(uint64_t *)&result;
    r1.i = (uint32_t) (result_uint64 >> 32);
    r0.i = (uint32_t) result_uint64;
}
void dcmpgt()
{
    uint64_t op1 = ((uint64_t)(uint32_t) r1.i) << 32 | ((uint64_t)(uint32_t) r0.i);
    uint64_t op2 = ((uint64_t)(uint32_t) r3.i) << 32 | ((uint64_t)(uint32_t) r2.i);
    r0.i = *(double *)&op1 > *(double *)&op2;
}
void d2iz()
{
    uint64_t op_int = ((uint64_t)(uint32_t) r1.i) << 32 | ((uint64_t)(uint32_t) r0.i);
    r0.i = (int32_t) *(double *)&op_int;
}
void assert_help()
{
    __assert_fail(malloc_0+r0.i, malloc_0+r1.i, r2.i, malloc_0+r3.i);
}
void dcmpge()
{
    uint64_t op1 = ((uint64_t)(uint32_t) r1.i) << 32 | ((uint64_t)(uint32_t) r0.i);
    uint64_t op2 = ((uint64_t)(uint32_t) r3.i) << 32 | ((uint64_t)(uint32_t) r2.i);
    r0.i = *(double *)&op1 >= *(double *)&op2;
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
void dcmplt()
{
    uint64_t op1 = ((uint64_t)(uint32_t) r1.i) << 32 | ((uint64_t)(uint32_t) r0.i);
    uint64_t op2 = ((uint64_t)(uint32_t) r3.i) << 32 | ((uint64_t)(uint32_t) r2.i);
    r0.i = *(double *)&op1 < *(double *)&op2;
}
void i2d()
{
    double result = (double) r0.i;
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
void dcmpeq()
{
    uint64_t op1 = ((uint64_t)(uint32_t) r1.i) << 32 | ((uint64_t)(uint32_t) r0.i);
    uint64_t op2 = ((uint64_t)(uint32_t) r3.i) << 32 | ((uint64_t)(uint32_t) r2.i);
    r0.i = *(double *)&op1 == *(double *)&op2;
}

void equal()
{
    counters[1] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r6.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r4.i, &sp.i, 0, 4, false, false, false);
    dsub();
    counters[2] ++;
    r2.i = 35898;
    r3.i = 31118;
    r2.i = r2.i | (57904 << 16);
    r3.i = r3.i | (15941 << 16);
    r5.i = r1.i & ~-2147483648;
    r4.i = r0.i;
    r1.i = r5.i;
    dcmplt();
    counters[3] ++;
    r0.i = r0.i - (0);
    z = r0.i == 0;
    n = r0.i & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (r0.i&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        r0.i = 1;
    }
    load_counter ++;
    ldr(&r4.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&r6.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;

}

void nl()
{
    counters[4] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r6.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r4.i, &sp.i, 0, 4, false, false, false);
    r5.i = r0.i - (0);
    z = r5.i == 0;
    n = r5.i & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (r5.i&0x80000000) != (r0.i&0x80000000);
    r6.i = (stdout & 0xffff);
    r6.i = r6.i | (((uint32_t)stdout >> 16) << 16);
    if (!z && n == v)
    {
        r4.i = 0;
    }
    if (z || n != v)
    {
        goto L8;
    }
L9:
    counters[5] ++;
    load_counter ++;
    ldr(&r1.i, &r6.i, 0, 4, false, false, false);
    r4.i = r4.i + (1);
    r0.i = 45;
    printf("%c", (char)r0.i);
    counters[6] ++;
    tmp = r5.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r4.i);
    v = (r5.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (!z)
    {
        goto L9;
    }
L8:
    counters[7] ++;
    load_counter ++;
    ldr(&r1.i, &r6.i, 0, 4, false, false, false);
    r0.i = 10;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&r5.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&r6.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    printf("%c", (char)r0.i);
    return;

}

void print_tableau()
{
    counters[8] ++;
    ip.i = (LC1 & 0xffff);
    ip.i = ip.i | (((uint32_t)LC1 >> 16) << 16);
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
    r3.i = r1.i;
    load_counter ++;
    ldr(&r2.i, &ip.i, 0, 4, false, false, false);
    sp.i = sp.i - (20);
    r9.i = r0.i;
    r1.i = (LC2 & 0xffff);
    r2.i = r2.i + (1);
    r1.i = r1.i | (((uint32_t)LC2 >> 16) << 16);
    r0.i = 1;
    store_counter ++;
    str(&r2.i, &ip.i, 0, 4, false, false, false);
    printf(malloc_0+r1.i, r2.i);
    counters[9] ++;
    r0.i = 70;
    printf("\n");
    counters[10] ++;
    r3.i = (LC3 & 0xffff);
    r2.i = (LC4 & 0xffff);
    r3.i = r3.i | (((uint32_t)LC3 >> 16) << 16);
    r2.i = r2.i | (((uint32_t)LC4 >> 16) << 16);
    r1.i = (LC5 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC5 >> 16) << 16);
    printf(malloc_0+r1.i, r2.i);
    counters[11] ++;
    load_counter ++;
    ldr(&r3.i, &r9.i, 4, 4, false, false, false);
    tmp = r3.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 1);
    v = (r3.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L15;
    }
    counters[12] ++;
    r5.i = (LC6 & 0xffff);
    r5.i = r5.i | (((uint32_t)LC6 >> 16) << 16);
    r4.i = 1;
L16:
    counters[13] ++;
    r2.i = r4.i;
    r0.i = 1;
    r1.i = r5.i;
    r4.i = r4.i + (r0.i);
    printf(malloc_0+r1.i, r2.i);
    counters[14] ++;
    load_counter ++;
    ldr(&r3.i, &r9.i, 4, 4, false, false, false);
    tmp = r3.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r4.i);
    v = (r3.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z && n == v)
    {
        goto L16;
    }
L15:
    counters[15] ++;
    r0.i = 10;
    printf("%c", (char)r0.i);
    counters[16] ++;
    load_counter ++;
    ldr(&r3.i, &r9.i, 0, 4, false, false, false);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L17;
    }
    counters[17] ++;
    r3.i = (LC8 & 0xffff);
    r2.i = (LC7 & 0xffff);
    r3.i = r3.i | (((uint32_t)LC8 >> 16) << 16);
    r2.i = r2.i | (((uint32_t)LC7 >> 16) << 16);
    store_counter ++;
    str(&r3.i, &sp.i, 8, 4, false, false, false);
    r3.i = r9.i + (8);
    store_counter ++;
    str(&r2.i, &sp.i, 12, 4, false, false, false);
    store_counter ++;
    str(&r3.i, &sp.i, 4, 4, false, false, false);
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &sp.i, 0, 4, false, false, false);
L25:
    counters[18] ++;
    load_counter ++;
    ldr(&r3.i, &sp.i, 0, 4, false, false, false);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L18;
    }
    counters[19] ++;
    load_counter ++;
    ldr(&r1.i, &sp.i, 12, 4, false, false, false);
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
L21:
    counters[20] ++;
    load_counter ++;
    ldr(&r3.i, &r9.i, 4, 4, false, false, false);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L20;
    }
    counters[21] ++;
    r10.i = (LC10 & 0xffff);
    fp.i = (LC9 & 0xffff);
    load_counter ++;
    ldr(&r8.i, &sp.i, 4, 4, false, false, false);
    r10.i = r10.i | (((uint32_t)LC10 >> 16) << 16);
    fp.i = fp.i | (((uint32_t)LC9 >> 16) << 16);
    r7.i = 0;
    goto L19;
L33:
    counters[22] ++;
    r2.i = r6.i;
    r1.i = fp.i;
    printf(malloc_0+r1.i, r2.i);
    counters[23] ++;
    load_counter ++;
    ldr(&r3.i, &r9.i, 4, 4, false, false, false);
    r7.i = r7.i + (1);
    tmp = r3.i - r7.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r7.i);
    v = (r3.i&0x80000000) != (r7.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L20;
    }
L19:
    counters[24] ++;
    load_counter ++;
    ldr(&r4.i, &r8.i, 8, 4, false, true, false);
    ldr(&r5.i, &r8.i, 12, 4, false, true, false);
    r1.i = r5.i;
    r0.i = r4.i;
    d2iz();
    counters[25] ++;
    r6.i = r0.i;
    i2d();
    counters[26] ++;
    r2.i = r4.i;
    r3.i = r5.i;
    dsub();
    counters[27] ++;
    r2.i = 35898;
    r3.i = 31118;
    r2.i = r2.i | (57904 << 16);
    r3.i = r3.i | (15941 << 16);
    ip.i = r0.i;
    lr.i = r1.i;
    r0.i = ip.i;
    r1.i = lr.i & ~-2147483648;
    dcmplt();
    counters[28] ++;
    r2.i = r4.i;
    r3.i = r5.i;
    r1.i = r10.i;
    ip.i = r0.i;
    tmp = ip.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) 0);
    v = (ip.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    r0.i = 1;
    if (!z)
    {
        goto L33;
    }
    counters[29] ++;
    printf(malloc_0+r1.i, r2.i);
    counters[30] ++;
    load_counter ++;
    ldr(&r3.i, &r9.i, 4, 4, false, false, false);
    r7.i = r7.i + (1);
    tmp = r3.i - r7.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r7.i);
    v = (r3.i&0x80000000) != (r7.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z && n == v)
    {
        goto L19;
    }
L20:
    counters[31] ++;
    load_counter ++;
    ldr(&r3.i, &sp.i, 0, 4, false, false, false);
    r0.i = 10;
    r4.i = r3.i + (1);
    store_counter ++;
    str(&r4.i, &sp.i, 0, 4, false, false, false);
    printf("%c", (char)r0.i);
    counters[32] ++;
    load_counter ++;
    ldr(&r3.i, &r9.i, 0, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &sp.i, 4, 4, false, false, false);
    tmp = r3.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r4.i);
    v = (r3.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    r2.i = r2.i + (160);
    store_counter ++;
    str(&r2.i, &sp.i, 4, 4, false, false, false);
    if (!z && n == v)
    {
        goto L25;
    }
L17:
    counters[33] ++;
    r0.i = 70;
    sp.i = sp.i + (20);
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
    ldr(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    printf("\n");
    return;
L18:
    counters[34] ++;
    load_counter ++;
    ldr(&r2.i, &sp.i, 0, 4, false, false, false);
    r0.i = 1;
    load_counter ++;
    ldr(&r1.i, &sp.i, 8, 4, false, false, false);
    printf(malloc_0+r1.i, r2.i);
    counters[35] ++;
    goto L21;
    return;
}

void pivot_on()
{
    counters[36] ++;
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
    r5.i = 20;
    r5.i = (r5.i) * (r1.i);
    r9.i = r2.i;
    sp.i = sp.i - (28);
    r2.i = 0;
    r3.i = 0;
    r8.i = r0.i;
    r10.i = r9.i + (r5.i);
    store_counter ++;
    str(&r1.i, &sp.i, 0, 4, false, false, false);
    r10.i = r0.i + (((uint32_t)r10.i << 3));
    load_counter ++;
    ldr(&r6.i, &r10.i, 8, 4, false, false, false);
    ldr(&r7.i, &r10.i, 12, 4, false, false, false);
    r0.i = r6.i;
    r1.i = r7.i;
    dcmpgt();
    counters[37] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (z)
    {
        goto L53;
    }
    counters[38] ++;
    load_counter ++;
    ldr(&r3.i, &r8.i, 4, 4, false, false, false);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    store_counter ++;
    str(&r3.i, &sp.i, 8, 4, false, false, false);
    if (z || n != v)
    {
        goto L38;
    }
    counters[39] ++;
    load_counter ++;
    ldr(&r3.i, &sp.i, 8, 4, false, false, false);
    r4.i = 160;
    r5.i = r3.i + (r5.i);
    load_counter ++;
    ldr(&r3.i, &sp.i, 0, 4, false, false, false);
    r4.i = ((r4.i) * (r3.i)) + (r8.i);
    r3.i = r8.i + (8);
    r5.i = r3.i + (((uint32_t)r5.i << 3));
    r4.i = r4.i + (8);
L39:
    counters[40] ++;
    load_counter ++;
    ldr(&r0.i, &r4.i, 0, 4, false, false, false);
    ldr(&r1.i, &r4.i, 4, 4, false, false, false);
    r2.i = r6.i;
    r3.i = r7.i;
    ddiv();
    counters[41] ++;
    store_counter ++;
    str(&r0.i, &r4.i, 8, 4, false, true, false);
    str(&r1.i, &r4.i, 12, 4, false, true, false);
    tmp = r4.i - r5.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r5.i);
    v = (r4.i&0x80000000) != (r5.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        goto L39;
    }
    counters[42] ++;
    load_counter ++;
    ldr(&r6.i, &r10.i, 8, 4, false, false, false);
    ldr(&r7.i, &r10.i, 12, 4, false, false, false);
L38:
    counters[43] ++;
    r2.i = 0;
    r0.i = r6.i;
    r1.i = r7.i;
    r3.i = 0;
    r3.i = r3.i | (16368 << 16);
    dsub();
    counters[44] ++;
    r2.i = 35898;
    r3.i = 31118;
    r2.i = r2.i | (57904 << 16);
    r3.i = r3.i | (15941 << 16);
    r5.i = r1.i & ~-2147483648;
    r1.i = r5.i;
    dcmplt();
    counters[45] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (z)
    {
        goto L54;
    }
    counters[46] ++;
    load_counter ++;
    ldr(&r3.i, &r8.i, 0, 4, false, false, false);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    store_counter ++;
    str(&r3.i, &sp.i, 4, 4, false, false, false);
    if (z || n != v)
    {
        goto L34;
    }
    counters[47] ++;
    load_counter ++;
    ldr(&r2.i, &sp.i, 0, 4, false, false, false);
    r3.i = 160;
    r10.i = r8.i + (8);
    fp.i = 0;
    r8.i = ((r3.i) * (r2.i)) + (r8.i);
    load_counter ++;
    ldr(&r3.i, &sp.i, 8, 4, false, false, false);
    r2.i = (uint32_t)r9.i << 3;
    store_counter ++;
    str(&r2.i, &sp.i, 16, 4, false, false, false);
    r3.i = (uint32_t)r3.i << 3;
    r10.i = r10.i + (r3.i);
    r3.i = 0 - r3.i;
    store_counter ++;
    str(&r3.i, &sp.i, 20, 4, false, false, false);
    r3.i = r8.i + (8);
    store_counter ++;
    str(&r3.i, &sp.i, 12, 4, false, false, false);
L44:
    counters[48] ++;
    load_counter ++;
    ldr(&r3.i, &sp.i, 0, 4, false, false, false);
    tmp = r3.i - fp.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) fp.i);
    v = (r3.i&0x80000000) != (fp.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L46;
    }
    counters[49] ++;
    load_counter ++;
    ldr(&r3.i, &sp.i, 8, 4, false, false, false);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L46;
    }
    counters[50] ++;
    load_counter ++;
    ldr(&r3.i, &sp.i, 16, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &sp.i, 20, 4, false, false, false);
    r3.i = r10.i + (r3.i);
    load_counter ++;
    ldr(&r5.i, &sp.i, 12, 4, false, false, false);
    r4.i = r10.i + (r2.i);
    load_counter ++;
    ldr(&r8.i, &r3.i, r2.i, 4, false, false, false);
    ldr(&r9.i, &r3.i, r2.i, 4, false, false, false);
L47:
    counters[51] ++;
    load_counter ++;
    ldr(&r0.i, &r5.i, 8, 4, false, true, false);
    ldr(&r1.i, &r5.i, 12, 4, false, true, false);
    r2.i = r8.i;
    r3.i = r9.i;
    load_counter ++;
    ldr(&r6.i, &r4.i, 0, 4, false, false, false);
    ldr(&r7.i, &r4.i, 4, 4, false, false, false);
    dmul();
    counters[52] ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r6.i;
    r1.i = r7.i;
    dsub();
    counters[53] ++;
    store_counter ++;
    str(&r0.i, &r4.i, 8, 4, false, true, false);
    str(&r1.i, &r4.i, 12, 4, false, true, false);
    tmp = r4.i - r10.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r10.i);
    v = (r4.i&0x80000000) != (r10.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        goto L47;
    }
L46:
    counters[54] ++;
    load_counter ++;
    ldr(&r3.i, &sp.i, 4, 4, false, false, false);
    fp.i = fp.i + (1);
    r10.i = r10.i + (160);
    tmp = fp.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) fp.i) >= ((uint32_t) r3.i);
    v = (fp.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (fp.i&0x80000000);
    if (!z)
    {
        goto L44;
    }
L34:
    counters[55] ++;
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
L53:
    counters[56] ++;
    r1.i = (LC0 & 0xffff);
    r0.i = (LC11 & 0xffff);
    load_counter ++;
    ldr(&r3.i, &L56, 0, 4, false, false, false);
    r1.i = r1.i | (((uint32_t)LC0 >> 16) << 16);
    r0.i = r0.i | (((uint32_t)LC11 >> 16) << 16);
    r2.i = 91;
    assert_help();
L54:
    counters[57] ++;
    r1.i = (LC0 & 0xffff);
    r0.i = (LC12 & 0xffff);
    load_counter ++;
    ldr(&r3.i, &L56, 0, 4, false, false, false);
    r1.i = r1.i | (((uint32_t)LC0 >> 16) << 16);
    r0.i = r0.i | (((uint32_t)LC12 >> 16) << 16);
    r2.i = 94;
    assert_help();
    return;
}

void find_pivot_column()
{
    counters[58] ++;
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
    sp.i = sp.i - (12);
    load_counter ++;
    ldr(&r10.i, &r0.i, 4, 4, false, false, false);
    load_counter ++;
    ldr(&r8.i, &r0.i, 16, 4, false, false, false);
    ldr(&r9.i, &r0.i, 20, 4, false, false, false);
    tmp = r10.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r10.i) >= ((uint32_t) 1);
    v = (r10.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r10.i&0x80000000);
    if (z || n != v)
    {
        goto L66;
    }
    counters[59] ++;
    r4.i = 1;
    r5.i = r0.i + (16);
    fp.i = r4.i;
    goto L60;
L63:
    counters[60] ++;
    load_counter ++;
    ldr(&r6.i, &r5.i, 8, 4, true, false, false);
    ldr(&r7.i, &r5.i, 12, 4, true, false, false);
    r0.i = r6.i;
    r1.i = r7.i;
    dcmplt();
    counters[61] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        r8.i = r6.i;
    }
    if (!z)
    {
        r9.i = r7.i;
    }
    if (!z)
    {
        fp.i = r4.i;
    }
L60:
    counters[62] ++;
    r4.i = r4.i + (1);
    r2.i = r8.i;
    tmp = r4.i - r10.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r10.i);
    v = (r4.i&0x80000000) != (r10.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    r3.i = r9.i;
    if (!z)
    {
        goto L63;
    }
L59:
    counters[63] ++;
    r2.i = fp.i;
    store_counter ++;
    str(&r8.i, &sp.i, 0, 4, false, false, false);
    str(&r9.i, &sp.i, 4, 4, false, false, false);
    r1.i = (LC13 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC13 >> 16) << 16);
    printf(malloc_0+r1.i, r2.i);
    counters[64] ++;
    r0.i = r8.i;
    r1.i = r9.i;
    r2.i = 0;
    r3.i = 0;
    dcmpge();
    counters[65] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (z)
    {
        r0.i = fp.i;
    }
    if (!z)
    {
        r0.i = ~0;
    }
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
L66:
    counters[66] ++;
    fp.i = 1;
    goto L59;
    return;
}

void find_pivot_row()
{
    counters[67] ++;
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
    sp.i = sp.i - (36);
    r8.i = r0.i;
    r2.i = r1.i;
    store_counter ++;
    str(&r1.i, &sp.i, 28, 4, false, false, false);
    r4.i = r1.i;
    r0.i = 1;
    r1.i = (LC14 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC14 >> 16) << 16);
    printf(malloc_0+r1.i, r2.i);
    counters[68] ++;
    load_counter ++;
    ldr(&r3.i, &r8.i, 0, 4, false, false, false);
    tmp = r3.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 1);
    v = (r3.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L71;
    }
    counters[69] ++;
    r9.i = (LC15 & 0xffff);
    r9.i = r9.i | (((uint32_t)LC15 >> 16) << 16);
    r3.i = (uint32_t)r4.i << 3;
    fp.i = 0;
    r3.i = r3.i + (168);
    store_counter ++;
    str(&r3.i, &sp.i, 20, 4, false, false, false);
    r3.i = 0;
    store_counter ++;
    str(&r3.i, &sp.i, 24, 4, false, false, false);
    r3.i = r9.i;
    r6.i = r8.i;
    r9.i = r8.i;
    fp.i = fp.i | (49136 << 16);
    r10.i = 0;
    r7.i = 1;
    r8.i = r3.i;
    goto L75;
L85:
    counters[70] ++;
    dcmplt();
    counters[71] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (z)
    {
        goto L72;
    }
L78:
    counters[72] ++;
    r10.i = r4.i;
    fp.i = r5.i;
    store_counter ++;
    str(&r7.i, &sp.i, 24, 4, false, false, false);
L74:
    counters[73] ++;
    load_counter ++;
    ldr(&r3.i, &r9.i, 0, 4, false, false, false);
    r7.i = r7.i + (1);
    r6.i = r6.i + (160);
    tmp = r3.i - r7.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r7.i);
    v = (r3.i&0x80000000) != (r7.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L84;
    }
L75:
    counters[74] ++;
    load_counter ++;
    ldr(&r3.i, &sp.i, 20, 4, false, false, false);
    load_counter ++;
    ldr(&r0.i, &r6.i, 168, 4, false, false, false);
    ldr(&r1.i, &r6.i, 172, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &r3.i, r6.i, 4, false, false, false);
    ldr(&r3.i, &r3.i, r6.i, 4, false, false, false);
    ddiv();
    counters[75] ++;
    r4.i = r0.i;
    r5.i = r1.i;
    r2.i = r4.i;
    r1.i = r8.i;
    r3.i = r5.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[76] ++;
    r2.i = 0;
    r3.i = 0;
    r1.i = r5.i;
    r0.i = r4.i;
    dcmpgt();
    counters[77] ++;
    r2.i = r10.i;
    r3.i = fp.i;
    r1.i = r5.i;
    ip.i = r0.i;
    tmp = ip.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) 0);
    v = (ip.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    r0.i = r4.i;
    if (!z)
    {
        goto L85;
    }
L72:
    counters[78] ++;
    r2.i = 0;
    r3.i = 0;
    r0.i = r10.i;
    r1.i = fp.i;
    dcmplt();
    counters[79] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (z)
    {
        goto L74;
    }
    counters[80] ++;
    goto L78;
L84:
    counters[81] ++;
    r0.i = (LC16 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC16 >> 16) << 16);
    printf("%s\n", malloc_0+r0.i);
    counters[82] ++;
    r2.i = 0;
    r3.i = 0;
    r0.i = r10.i;
    r3.i = r3.i | (49136 << 16);
    r1.i = fp.i;
    dcmpeq();
    counters[83] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        goto L83;
    }
    counters[84] ++;
    load_counter ++;
    ldr(&r2.i, &sp.i, 24, 4, false, false, false);
    r1.i = (LC17 & 0xffff);
    load_counter ++;
    ldr(&r3.i, &sp.i, 28, 4, false, false, false);
    r1.i = r1.i | (((uint32_t)LC17 >> 16) << 16);
    r0.i = 1;
    store_counter ++;
    str(&r10.i, &sp.i, 0, 4, false, false, false);
    str(&fp.i, &sp.i, 4, 4, false, false, false);
    store_counter ++;
    str(&r2.i, &sp.i, 8, 4, false, false, false);
    printf(malloc_0+r1.i, r2.i);
L70:
    counters[85] ++;
    load_counter ++;
    ldr(&r0.i, &sp.i, 24, 4, false, false, false);
    sp.i = sp.i + (36);
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
L71:
    counters[86] ++;
    r0.i = (LC16 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC16 >> 16) << 16);
    printf("%s\n", malloc_0+r0.i);
L83:
    counters[87] ++;
    r3.i = ~0;
    store_counter ++;
    str(&r3.i, &sp.i, 24, 4, false, false, false);
    goto L70;
    return;
}

void add_slack_variables()
{
    counters[88] ++;
    load_counter ++;
    ldr(&ip.i, &r0.i, 0, 4, false, false, false);
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
    tmp = ip.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) 1);
    v = (ip.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    load_counter ++;
    ldr(&r10.i, &r0.i, 4, 4, false, false, false);
    if (z || n != v)
    {
        goto L91;
    }
    counters[89] ++;
    lr.i = r0.i + (((uint32_t)r10.i << 3));
    r9.i = 0;
    lr.i = lr.i + (160);
    r9.i = r9.i | (16368 << 16);
    r8.i = 0;
    r6.i = 0;
    r7.i = 0;
    r1.i = 1;
L90:
    counters[90] ++;
    r2.i = lr.i;
    r3.i = 1;
L89:
    counters[91] ++;
    tmp = r1.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r3.i);
    v = (r1.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    r3.i = r3.i + (1);
    r4.i = r6.i;
    r5.i = r7.i;
    if (z)
    {
        r4.i = r8.i;
    }
    if (z)
    {
        r5.i = r9.i;
    }
    tmp = r3.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) ip.i);
    v = (r3.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    store_counter ++;
    str(&r4.i, &r2.i, 8, 4, true, false, false);
    str(&r5.i, &r2.i, 12, 4, true, false, false);
    if (!z)
    {
        goto L89;
    }
    counters[92] ++;
    r1.i = r1.i + (1);
    lr.i = lr.i + (160);
    tmp = r1.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) ip.i);
    v = (r1.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!z)
    {
        goto L90;
    }
L91:
    counters[93] ++;
    ip.i = ip.i - (1);
    r10.i = ip.i + (r10.i);
    store_counter ++;
    str(&r10.i, &r0.i, 4, 4, false, false, false);
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

void check_b_positive()
{
    if (check_b_positivepart == -1)
    {
        counters[94] ++;
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
        load_counter ++;
        ldr(&r8.i, &r0.i, 0, 4, false, false, false);
        tmp = r8.i - 1;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r8.i) >= ((uint32_t) 1);
        v = (r8.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
        load_counter ++;
        if (z || n != v)
        {
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
        r4.i = r0.i;
        r6.i = 0;
        r7.i = 0;
        r5.i = 1;
        goto L100;
L99:
        counters[95] ++;
        r5.i = r5.i + (1);
        r4.i = r4.i + (160);
        tmp = r5.i - r8.i;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r5.i) >= ((uint32_t) r8.i);
        v = (r5.i&0x80000000) != (r8.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
        load_counter ++;
        if (z)
        {
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
L100:
        counters[96] ++;
        load_counter ++;
        ldr(&r0.i, &r4.i, 168, 4, false, false, false);
        ldr(&r1.i, &r4.i, 172, 4, false, false, false);
        r2.i = r6.i;
        r3.i = r7.i;
        dcmpge();
        counters[97] ++;
        tmp = r0.i - 0;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r0.i) >= ((uint32_t) 0);
        v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
        if (!z)
        {
            goto L99;
        }
        counters[98] ++;
        check_b_positivepart = 0;
        check_b_positive();
        goto check_b_positivepart0;
    }
    if (check_b_positivepart == 0)
    {
check_b_positivepart0:
        counters[0] ++;
        r3.i = (LC0 & 0xffff);
        r1.i = (LC0 & 0xffff);
        r0.i = (LC1 & 0xffff);
        r3.i = r3.i | (((uint32_t)LC0 >> 16) << 16);
        r1.i = r1.i | (((uint32_t)LC0 >> 16) << 16);
        r0.i = r0.i | (((uint32_t)LC1 >> 16) << 16);
        r2.i = 155;
        store_counter ++;
        sp.i -= 4;
        str(&lr.i, &sp.i, 0, 4, false, false, false);
        sp.i -= 4;
        str(&r4.i, &sp.i, 0, 4, false, false, false);
        assert_help();
    }
    return;
}

void find_basis_variable()
{
    counters[99] ++;
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
    sp.i -= 4;
    str(&r3.i, &sp.i, 0, 4, false, false, false);
    load_counter ++;
    ldr(&fp.i, &r0.i, 0, 4, false, false, false);
    tmp = fp.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) fp.i) >= ((uint32_t) 1);
    v = (fp.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (fp.i&0x80000000);
    if (z || n != v)
    {
        goto L116;
    }
    counters[100] ++;
    r6.i = 35898;
    r7.i = 31118;
    r6.i = r6.i | (57904 << 16);
    r7.i = r7.i | (15941 << 16);
    r4.i = r0.i + (((uint32_t)r1.i << 3));
    r10.i = ~0;
    r5.i = 1;
    goto L109;
L118:
    counters[101] ++;
    tmp = r10.i + 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) tmp) < ((uint32_t) r10.i);
    v = (r10.i&0x80000000) == (1&0x80000000) && (tmp&0x80000000) != (r10.i&0x80000000);
    r10.i = r5.i;
    if (!z)
    {
        goto L116;
    }
L107:
    counters[102] ++;
    r5.i = r5.i + (1);
    tmp = r5.i - fp.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) fp.i);
    v = (r5.i&0x80000000) != (fp.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (z)
    {
        goto L103;
    }
L109:
    counters[103] ++;
    load_counter ++;
    ldr(&r8.i, &r4.i, 172, 4, false, false, false);
    r2.i = 0;
    load_counter ++;
    ldr(&r9.i, &r4.i, 168, 4, false, false, false);
    r3.i = 0;
    r3.i = r3.i | (16368 << 16);
    r4.i = r4.i + (160);
    r1.i = r8.i;
    r0.i = r9.i;
    dsub();
    counters[104] ++;
    r2.i = 35898;
    r3.i = 31118;
    r2.i = r2.i | (57904 << 16);
    r3.i = r3.i | (15941 << 16);
    r1.i = r1.i & ~-2147483648;
    dcmplt();
    counters[105] ++;
    r1.i = r8.i & ~-2147483648;
    r2.i = r6.i;
    r3.i = r7.i;
    ip.i = r0.i;
    tmp = ip.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) 0);
    v = (ip.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    r0.i = r9.i;
    if (!z)
    {
        goto L118;
    }
    counters[106] ++;
    dcmplt();
    counters[107] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        goto L107;
    }
L116:
    counters[108] ++;
    r10.i = ~0;
L103:
    counters[109] ++;
    r0.i = r10.i;
    load_counter ++;
    ldr(&r3.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
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

void print_optimal_vector()
{
    counters[110] ++;
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
    sp.i = sp.i - (28);
    r2.i = r1.i;
    r4.i = r0.i;
    store_counter ++;
    str(&r0.i, &sp.i, 16, 4, false, false, false);
    r1.i = (LC18 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC18 >> 16) << 16);
    printf(malloc_0+r1.i, r2.i);
    counters[111] ++;
    load_counter ++;
    ldr(&r3.i, &r4.i, 4, 4, false, false, false);
    tmp = r3.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 1);
    v = (r3.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L121;
    }
    counters[112] ++;
    r6.i = 35898;
    r7.i = 31118;
    r6.i = r6.i | (57904 << 16);
    r7.i = r7.i | (15941 << 16);
    r3.i = (LC20 & 0xffff);
    r3.i = r3.i | (((uint32_t)LC20 >> 16) << 16);
    store_counter ++;
    str(&r3.i, &sp.i, 20, 4, false, false, false);
    r3.i = 1;
    store_counter ++;
    str(&r3.i, &sp.i, 12, 4, false, false, false);
L120:
    counters[113] ++;
    load_counter ++;
    ldr(&r3.i, &sp.i, 16, 4, false, false, false);
    load_counter ++;
    ldr(&fp.i, &r3.i, 0, 4, false, false, false);
    tmp = fp.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) fp.i) >= ((uint32_t) 1);
    v = (fp.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (fp.i&0x80000000);
    if (z || n != v)
    {
        goto L125;
    }
    counters[114] ++;
    load_counter ++;
    ldr(&r2.i, &sp.i, 12, 4, false, false, false);
    ldr(&r3.i, &sp.i, 16, 4, false, false, false);
    r10.i = ~0;
    r5.i = 1;
    r4.i = r3.i + (((uint32_t)r2.i << 3));
    goto L127;
L140:
    counters[115] ++;
    tmp = r10.i + 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) tmp) < ((uint32_t) r10.i);
    v = (r10.i&0x80000000) == (1&0x80000000) && (tmp&0x80000000) != (r10.i&0x80000000);
    r10.i = r5.i;
    if (!z)
    {
        goto L125;
    }
L124:
    counters[116] ++;
    r5.i = r5.i + (1);
    tmp = r5.i - fp.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) fp.i);
    v = (r5.i&0x80000000) != (fp.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (z)
    {
        goto L139;
    }
L127:
    counters[117] ++;
    load_counter ++;
    ldr(&r8.i, &r4.i, 172, 4, false, false, false);
    r2.i = 0;
    load_counter ++;
    ldr(&r9.i, &r4.i, 168, 4, false, false, false);
    r3.i = 0;
    r3.i = r3.i | (16368 << 16);
    r4.i = r4.i + (160);
    r1.i = r8.i;
    r0.i = r9.i;
    dsub();
    counters[118] ++;
    r2.i = r6.i;
    r3.i = r7.i;
    r1.i = r1.i & ~-2147483648;
    dcmplt();
    counters[119] ++;
    r1.i = r8.i & ~-2147483648;
    r2.i = r6.i;
    r3.i = r7.i;
    ip.i = r0.i;
    tmp = ip.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) 0);
    v = (ip.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    r0.i = r9.i;
    if (!z)
    {
        goto L140;
    }
    counters[120] ++;
    dcmplt();
    counters[121] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        goto L124;
    }
L125:
    counters[122] ++;
    load_counter ++;
    ldr(&r2.i, &sp.i, 12, 4, false, false, false);
    r0.i = 1;
    load_counter ++;
    ldr(&r1.i, &sp.i, 20, 4, false, false, false);
    printf(malloc_0+r1.i, r2.i);
L128:
    counters[123] ++;
    load_counter ++;
    ldr(&r3.i, &sp.i, 16, 4, false, false, false);
    load_counter ++;
    ldr(&r2.i, &sp.i, 12, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &r3.i, 4, 4, false, false, false);
    r2.i = r2.i + (1);
    store_counter ++;
    str(&r2.i, &sp.i, 12, 4, false, false, false);
    tmp = r3.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r2.i);
    v = (r3.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z && n == v)
    {
        goto L120;
    }
L121:
    counters[124] ++;
    r0.i = 10;
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
    ldr(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    printf("%c", (char)r0.i);
    return;
L139:
    counters[125] ++;
    tmp = r10.i + 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) tmp) < ((uint32_t) r10.i);
    v = (r10.i&0x80000000) == (1&0x80000000) && (tmp&0x80000000) != (r10.i&0x80000000);
    if (z)
    {
        goto L125;
    }
    counters[126] ++;
    load_counter ++;
    ldr(&r2.i, &sp.i, 16, 4, false, false, false);
    r3.i = 160;
    r1.i = (LC19 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC19 >> 16) << 16);
    r10.i = ((r3.i) * (r10.i)) + (r2.i);
    load_counter ++;
    ldr(&r2.i, &sp.i, 12, 4, false, false, false);
    load_counter ++;
    ldr(&r4.i, &r10.i, 8, 4, false, false, false);
    ldr(&r5.i, &r10.i, 12, 4, false, false, false);
    store_counter ++;
    str(&r4.i, &sp.i, 0, 4, false, false, false);
    str(&r5.i, &sp.i, 4, 4, false, false, false);
    printf(malloc_0+r1.i, r2.i);
    counters[127] ++;
    goto L128;
    return;
}

void simplex()
{
    counters[128] ++;
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
    r5.i = r0.i;
    load_counter ++;
    ldr(&r4.i, &r0.i, 0, 4, false, false, false);
    load_counter ++;
    ldr(&r3.i, &r0.i, 4, 4, false, false, false);
    tmp = r4.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 1);
    v = (r4.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    r10.i = r4.i - (1);
    r10.i = r10.i + (r3.i);
    if (z || n != v)
    {
        goto L142;
    }
    counters[129] ++;
    r3.i = r0.i + (((uint32_t)r3.i << 3));
    r1.i = 0;
    r9.i = r3.i + (160);
    r1.i = r1.i | (16368 << 16);
    r8.i = 1;
    r0.i = 0;
    r6.i = 0;
    r7.i = 0;
L143:
    counters[130] ++;
    lr.i = r9.i;
    ip.i = 1;
L145:
    counters[131] ++;
    tmp = ip.i - r8.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r8.i);
    v = (ip.i&0x80000000) != (r8.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    ip.i = ip.i + (1);
    if (!z)
    {
        r2.i = r6.i;
    }
    if (!z)
    {
        r3.i = r7.i;
    }
    if (z)
    {
        r2.i = r0.i;
    }
    if (z)
    {
        r3.i = r1.i;
    }
    tmp = ip.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r4.i);
    v = (ip.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    store_counter ++;
    str(&r2.i, &lr.i, 8, 4, true, false, false);
    str(&r3.i, &lr.i, 12, 4, true, false, false);
    if (!z)
    {
        goto L145;
    }
    counters[132] ++;
    r8.i = r8.i + (1);
    r9.i = r9.i + (160);
    tmp = r8.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) r4.i);
    v = (r8.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    if (!z)
    {
        goto L143;
    }
    counters[133] ++;
    r6.i = r5.i;
    r7.i = 1;
    r8.i = 0;
    r9.i = 0;
    store_counter ++;
    str(&r10.i, &r5.i, 4, 4, false, false, false);
L148:
    counters[134] ++;
    load_counter ++;
    ldr(&r0.i, &r6.i, 168, 4, false, false, false);
    ldr(&r1.i, &r6.i, 172, 4, false, false, false);
    r2.i = r8.i;
    r3.i = r9.i;
    dcmpge();
    counters[135] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (z)
    {
        goto L160;
    }
    counters[136] ++;
    r7.i = r7.i + (1);
    r6.i = r6.i + (160);
    tmp = r7.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r7.i) >= ((uint32_t) r4.i);
    v = (r7.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
    if (!z)
    {
        goto L148;
    }
L153:
    counters[137] ++;
    r1.i = (LC21 & 0xffff);
    r0.i = r5.i;
    r1.i = r1.i | (((uint32_t)LC21 >> 16) << 16);
    r8.i = (LC24 & 0xffff);
    print_tableau();
    counters[138] ++;
    r10.i = (LC26 & 0xffff);
    r9.i = (LC27 & 0xffff);
    r8.i = r8.i | (((uint32_t)LC24 >> 16) << 16);
    r10.i = r10.i | (((uint32_t)LC26 >> 16) << 16);
    r9.i = r9.i | (((uint32_t)LC27 >> 16) << 16);
    r7.i = 21;
L149:
    counters[139] ++;
    r0.i = r5.i;
    find_pivot_column();
    counters[140] ++;
    r4.i = r0.i - (0);
    z = r4.i == 0;
    n = r4.i & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (r4.i&0x80000000) != (r0.i&0x80000000);
    if (n != v)
    {
        goto L161;
    }
    counters[141] ++;
    r3.i = r4.i;
    r2.i = r4.i;
    r1.i = r8.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[142] ++;
    r1.i = r4.i;
    r0.i = r5.i;
    find_pivot_row();
    counters[143] ++;
    r6.i = r0.i - (0);
    z = r6.i == 0;
    n = r6.i & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (r6.i&0x80000000) != (r0.i&0x80000000);
    if (n != v)
    {
        goto L162;
    }
    counters[144] ++;
    r3.i = r6.i;
    r2.i = r6.i;
    r1.i = r10.i;
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    counters[145] ++;
    r2.i = r4.i;
    r1.i = r6.i;
    r0.i = r5.i;
    pivot_on();
    counters[146] ++;
    r1.i = r9.i;
    r0.i = r5.i;
    print_tableau();
    counters[147] ++;
    r1.i = (LC28 & 0xffff);
    r0.i = r5.i;
    r1.i = r1.i | (((uint32_t)LC28 >> 16) << 16);
    print_optimal_vector();
    counters[148] ++;
    r7.i = r7.i - (1);
    z = r7.i == 0;
    n = r7.i & 0x80000000;
    c = ((uint32_t) r7.i) >= ((uint32_t) 1);
    v = (r7.i&0x80000000) != (1&0x80000000) && (r7.i&0x80000000) != (r7.i&0x80000000);
    if (!z)
    {
        goto L149;
    }
    counters[149] ++;
    r1.i = (LC29 & 0xffff);
    r2.i = 21;
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
    ldr(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    r1.i = r1.i | (((uint32_t)LC29 >> 16) << 16);
    r0.i = 1;
    printf(malloc_0+r1.i, r2.i);
    return;
L161:
    counters[150] ++;
    load_counter ++;
    ldr(&r2.i, &r5.i, 8, 4, false, false, false);
    ldr(&r3.i, &r5.i, 12, 4, false, false, false);
    r1.i = (LC22 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC22 >> 16) << 16);
    printf(malloc_0+r1.i, r2.i);
    counters[151] ++;
    r0.i = r5.i;
    r1.i = (LC23 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC23 >> 16) << 16);
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
    ldr(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    print_optimal_vector();
    return;
L162:
    counters[152] ++;
    r0.i = (LC25 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC25 >> 16) << 16);
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
    ldr(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    printf("%s\n", malloc_0+r0.i);
    return;
L142:
    counters[153] ++;
    store_counter ++;
    str(&r10.i, &r0.i, 4, 4, false, false, false);
    goto L153;
L160:
    counters[154] ++;
    check_b_positivepart = 0;
    check_b_positive();
    return;
}

void main()
{
    malloc_start();
    counters[155] ++;
    store_counter ++;
    sp.i -= 4;
    str(&lr.i, &sp.i, 0, 4, false, false, false);
    sp.i -= 4;
    str(&r4.i, &sp.i, 0, 4, false, false, false);
    r4.i = (LC2 & 0xffff);
    r4.i = r4.i | (((uint32_t)LC2 >> 16) << 16);
    r1.i = (LC30 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC30 >> 16) << 16);
    r0.i = r4.i;
    print_tableau();
    counters[156] ++;
    r0.i = r4.i;
    simplex();
    counters[157] ++;
    r0.i = 0;
    load_counter ++;
    ldr(&r4.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    ldr(&pc.i, &sp.i, 0, 4, false, false, false);
    sp.i += 4;
    return;

}

