#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <regex.h>

typedef union
{
    int32_t i;
    float f;
} reg;

int32_t tmp;
reg sp, fp, lr, pc, ip;
bool z, n, c, v;
uint8_t* malloc_0 = 0;

reg r1, r7, r4, r5, r9, r10, r8, r2, r3, r6, r0;

int32_t LC2, LC3, LC0, LC1;

int counters[24] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[24] = {3,20,2,8,8,6,7,7,4,9,1,10,8,4,9,2,12,2,2,2,7,2,16,3};

void push(int num, ...)
{
    va_list args;
    va_start(args, num);
    for (int i=0; i < num; i++)
    {
        int32_t *cur_arg = va_arg(args, int32_t *);
        sp.i -= 4;
        *((uint32_t*) (malloc_0 + sp.i)) = *cur_arg;
    }
    va_end(args);
}
void ldm0(int32_t *address, int num, ...)
{
    va_list args;
    va_start(args, num);
    int32_t tmp = *address;
    for (int i=0; i < num; i++)
    {
        int32_t *cur_arg = va_arg(args, int32_t *);
        *cur_arg = *((uint32_t*) (malloc_0 + tmp));
        tmp += 4;
    }
    va_end(args);
}
void str4000(int32_t *target, int32_t *address, int32_t offset)
{
    *((uint32_t*)(malloc_0+*address+offset)) = *target;
}
void ldr4000(int32_t *target, int32_t *address, int32_t offset)
{
    *target = *((uint32_t*)(malloc_0+*address+offset));
}
void pop(int num, ...)
{
    va_list args;
    va_start(args, num);
    for (int i=0; i < num; i++)
    {
        int32_t *cur_arg = va_arg(args, int32_t *);
        *cur_arg = *((uint32_t*) (malloc_0 + sp.i));
        sp.i += 4;
    }
    va_end(args);
}
void stm0(int32_t *address, int num, ...)
{
    va_list args;
    va_start(args, num);
    int32_t tmp = *address;
    for (int i=0; i < num; i++)
    {
        int32_t *cur_arg = va_arg(args, int32_t *);
        *((uint32_t*) (malloc_0 + tmp)) = *cur_arg;
        tmp += 4;
    }
    va_end(args);
}

void printf_help(const char *format, int32_t arg1, int32_t arg2, int32_t arg3)
{
    regex_t reg;
    if (regcomp(&reg, "(%([0-9]*)lf)|(%f)", REG_EXTENDED | REG_NOSUB) != 0) return;
    if (regexec(&reg, format, 0, 0, 0) == 0)
    {
        uint64_t arg = ((uint64_t)(uint32_t) arg3) << 32 | ((uint64_t)(uint32_t) arg2);
        double d_arg = *(double *)&arg;
        printf(format, d_arg);
        return;
    }
    else if(strstr(format, "%s"))
    {
        printf(format, malloc_0+arg1);
    }
    else if(strstr(format, "%c"))
    {
        printf(format, arg1);
    }
    else
    {
        printf(format, arg1);
    }
    regfree(&reg);
}

// TODO clz nur laden wenn gebraucht
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

// Debugging purposes
/*void print_stack(int32_t start, int32_t bytes)
{
    int32_t size = bytes/4;
    int32_t cur_val = 0;

    for(int32_t i=0; i<size; i++){
        ldr4000(&cur_val, &start, i*4);
        printf("%d: %d\n", start+i*4, cur_val);
    }
}*/

void malloc_start()
{
    malloc_0 = (uint8_t*) malloc(20045);
    sp.i = 19996;
    fp = sp;
    LC2 = 20000;
    strcpy(malloc_0+LC2, "%d\012\000");

    LC3 = 20012;
    strcpy(malloc_0+LC3, "%d \000");

    LC0 = 20021;
    int32_t arrayLC0[] = {60,100,120};
    for(int i=0; i<3; i++) str4000(&arrayLC0[i], &LC0, i*4);

    LC1 = 20033;
    int32_t arrayLC1[] = {10,20,30};
    for(int i=0; i<3; i++) str4000(&arrayLC1[i], &LC1, i*4);

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "knapsack.c";

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

void max();
void printknapSack();
void main();

void max()
{
    tmp = r1.i - r0.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r0.i);
    v = (r1.i&0x80000000) != (r0.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (n == v)
    {
        r0.i = r1.i;
    }
    return;

}

void printknapSack()
{
    push(9, &r4.i, &r5.i, &r6.i, &r7.i, &r8.i, &r9.i, &r10.i, &fp.i, &lr.i);
    r4.i = r0.i + (1);
    r5.i = r3.i - (0);
    z = r5.i == 0;
    n = r5.i & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (r5.i&0x80000000) != (r3.i&0x80000000);
    fp.i = sp.i + (32);
    r3.i = ((r3.i) * (r4.i)) + (r4.i);
    sp.i = sp.i - (36);
    ip.i = (uint32_t)r4.i << 2;
    str4000(&r0.i, &fp.i, -60);
    str4000(&ip.i, &fp.i, -56);
    ip.i = r4.i & ~-1073741824;
    str4000(&r1.i, &fp.i, -64);
    str4000(&r2.i, &fp.i, -68);
    r3.i = (uint32_t)r3.i << 2;
    str4000(&ip.i, &fp.i, -48);
    r3.i = r3.i + (7);
    r3.i = r3.i & ~7;
    sp.i = sp.i - (r3.i);
    r3.i = sp.i;
    str4000(&r3.i, &fp.i, -40);
    if (n != v)
    {
        goto L4;
    }
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (n != v)
    {
        goto L5;
    }
    str4000(&r3.i, &fp.i, -44);
    r9.i = r2.i - (4);
    r3.i = ~0;
    r6.i = r1.i - (4);
    r8.i = 0 - ip.i;
    str4000(&r5.i, &fp.i, -52);
    r7.i = 0;
    r5.i = r3.i;
L6:
    ldr4000(&r3.i, &fp.i, -48);
    lr.i = r5.i;
    ldr4000(&r2.i, &fp.i, -44);
    r5.i = r5.i + (1);
    z = r5.i == 0;
    n = r5.i & 0x80000000;
    c = ((uint32_t) r5.i) < ((uint32_t) r5.i);
    v = (r5.i&0x80000000) == (1&0x80000000) && (r5.i&0x80000000) != (r5.i&0x80000000);
    lr.i = (lr.i) * (r3.i);
    if (z)
    {
        ip.i = 1;
    }
    if (!z)
    {
        ip.i = 0;
    }
    r3.i = 0;
L10:
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        r1.i = ip.i;
    }
    if (z)
    {
        r1.i = 1;
    }
    tmp = r1.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 0);
    v = (r1.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!z)
    {
        str4000(&r7.i, &r2.i, 0);
    }
    if (!z)
    {
        goto L8;
    }
    ldr4000(&r10.i, &r6.i, 0);
    ldr4000(&r0.i, &r2.i, ((uint32_t)r8.i << 2));
    tmp = r10.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r10.i) >= ((uint32_t) r3.i);
    v = (r10.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r10.i&0x80000000);
    r1.i = r3.i - (r10.i);
    r1.i = lr.i + (r1.i);
    if (!z && n == v)
    {
        str4000(&r0.i, &r2.i, 0);
    }
    if (!z && n == v)
    {
        goto L8;
    }
    ldr4000(&r10.i, &fp.i, -40);
    ldr4000(&r1.i, &r10.i, ((uint32_t)r1.i << 2));
    ldr4000(&r10.i, &r9.i, 0);
    r1.i = r1.i + (r10.i);
    tmp = r1.i - r0.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r0.i);
    v = (r1.i&0x80000000) != (r0.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (n != v)
    {
        r1.i = r0.i;
    }
    str4000(&r1.i, &r2.i, 0);
L8:
    r3.i = r3.i + (1);
    r2.i = r2.i + (4);
    tmp = r3.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r4.i);
    v = (r3.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L10;
    }
    ldr4000(&r3.i, &fp.i, -52);
    r9.i = r9.i + (4);
    ldr4000(&r2.i, &fp.i, -56);
    r6.i = r6.i + (4);
    tmp = r3.i - r5.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r5.i);
    v = (r3.i&0x80000000) != (r5.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    ldr4000(&r3.i, &fp.i, -44);
    r3.i = r3.i + (r2.i);
    str4000(&r3.i, &fp.i, -44);
    if (!z)
    {
        goto L6;
    }
    ldr4000(&r5.i, &fp.i, -52);
L5:
    ldr4000(&r3.i, &fp.i, -48);
    r1.i = (LC2 & 0xffff);
    ldr4000(&r7.i, &fp.i, -60);
    r1.i = r1.i | (((uint32_t)LC2 >> 16) << 16);
    ldr4000(&r2.i, &fp.i, -40);
    r0.i = 1;
    r3.i = ((r3.i) * (r5.i)) + (r7.i);
    ldr4000(&r4.i, &r2.i, ((uint32_t)r3.i << 2));
    r2.i = r4.i;
    printf_help(malloc_0+r1.i, r2.i, r3.i, r4.i);
    tmp = r5.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) 0);
    v = (r5.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (!z && n == v)
    {
        r3.i = 1;
    }
    if (z || n != v)
    {
        r3.i = 0;
    }
    tmp = r4.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 0);
    v = (r4.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (z || n != v)
    {
        r3.i = 0;
    }
    if (!z && n == v)
    {
        r3.i = r3.i & 1;
    }
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L3;
    }
    ldr4000(&r8.i, &fp.i, -64);
    r6.i = (LC3 & 0xffff);
    ldr4000(&r9.i, &fp.i, -68);
    r6.i = r6.i | (((uint32_t)LC3 >> 16) << 16);
L11:
    ldr4000(&r3.i, &fp.i, -48);
    r5.i = r5.i - (1);
    ldr4000(&r2.i, &fp.i, -40);
    r1.i = r6.i;
    r0.i = 1;
    r3.i = ((r3.i) * (r5.i)) + (r7.i);
    ldr4000(&r3.i, &r2.i, ((uint32_t)r3.i << 2));
    tmp = r3.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r4.i);
    v = (r3.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L13;
    }
    ldr4000(&r2.i, &r8.i, ((uint32_t)r5.i << 2));
    printf_help(malloc_0+r1.i, r2.i, r3.i, r4.i);
    ldr4000(&r3.i, &r9.i, ((uint32_t)r5.i << 2));
    tmp = r5.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) 0);
    v = (r5.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    ldr4000(&r2.i, &r8.i, ((uint32_t)r5.i << 2));
    r4.i = r4.i - (r3.i);
    if (!z && n == v)
    {
        r3.i = 1;
    }
    if (z || n != v)
    {
        r3.i = 0;
    }
    tmp = r4.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 0);
    v = (r4.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    r7.i = r7.i - (r2.i);
    if (!z && n == v)
    {
        r3.i = r3.i & 1;
    }
    if (z || n != v)
    {
        r3.i = 0;
    }
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L11;
    }
L3:
    sp.i = fp.i - (32);
    pop(9, &pc.i, &fp.i, &r10.i, &r9.i, &r8.i, &r7.i, &r6.i, &r5.i, &r4.i);
    return;
L13:
    tmp = r5.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) 0);
    v = (r5.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (!z && n == v)
    {
        goto L11;
    }
    sp.i = fp.i - (32);
    pop(9, &pc.i, &fp.i, &r10.i, &r9.i, &r8.i, &r7.i, &r6.i, &r5.i, &r4.i);
    return;
L4:
    r5.i = ((ip.i) * (r5.i)) + (r0.i);
    ldr4000(&r3.i, &fp.i, -40);
    r1.i = (LC2 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC2 >> 16) << 16);
    ldr4000(&r2.i, &r3.i, ((uint32_t)r5.i << 2));
    printf_help(malloc_0+r1.i, r2.i, r3.i, r4.i);
    sp.i = fp.i - (32);
    pop(9, &pc.i, &fp.i, &r10.i, &r9.i, &r8.i, &r7.i, &r6.i, &r5.i, &r4.i);
    return;

}

void main()
{
    malloc_start();
    r3.i = (LC0 & 0xffff);
    r3.i = r3.i | (((uint32_t)LC0 >> 16) << 16);
    push(2, &r4.i, &lr.i);
    sp.i = sp.i - (24);
    ldm0(&r3.i, 3, &r0.i, &r1.i, &r2.i);
    r4.i = r3.i + (12);
    lr.i = sp.i;
    ip.i = sp.i + (12);
    r3.i = 3;
    stm0(&lr.i, 3, &r0.i, &r1.i, &r2.i);
    ldm0(&r4.i, 3, &r0.i, &r1.i, &r2.i);
    stm0(&ip.i, 3, &r0.i, &r1.i, &r2.i);
    r2.i = lr.i;
    r1.i = ip.i;
    r0.i = 50;
    printknapSack();
    r0.i = 0;
    sp.i = sp.i + (24);
    pop(2, &pc.i, &r4.i);
    return;

}

