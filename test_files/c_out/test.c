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

reg r3, r2, r4, r0, r1;

int32_t LC1, LC2, LC3, LC4, LC5, LC6, LC7, LC8, LC0;

int load_counter = 0, store_counter = 0;
int counters[104] = { 0 };
int block_sizes[104] = {12,3,6,6,2,5,7,3,4,4,11,6,6,2,5,7,3,4,4,8,2,3,4,2,4,5,4,3,1,6,9,2,4,4,5,3,5,5,4,2,3,4,1,3,32,20,12,2,4,12,2,4,5,4,3,10,4,3,3,3,8,8,3,5,4,7,3,4,9,3,3,5,12,8,4,9,8,3,3,4,7,2,4,5,2,3,16,18,5,21,3,4,5,6,2,4,4,5,3,4,1,4,4,4};

void str4000(int32_t *target, int32_t *address, int32_t offset)
{
    *((uint32_t*)(malloc_0+*address+offset)) = *target;
    store_counter ++;
}
void ldm1(int32_t *address, int num, ...)
{
    va_list args;
    va_start(args, num);
    for (int i=0; i < num; i++)
    {
        int32_t *cur_arg = va_arg(args, int32_t *);
        *cur_arg = *((uint32_t*) (malloc_0 + *address));
        *address += 4;
        load_counter ++;
    }
    va_end(args);
}
void push(int num, ...)
{
    va_list args;
    va_start(args, num);
    for (int i=0; i < num; i++)
    {
        int32_t *cur_arg = va_arg(args, int32_t *);
        sp.i -= 4;
        *((uint32_t*) (malloc_0 + sp.i)) = *cur_arg;
        store_counter ++;
    }
    va_end(args);
}
void idiv()
{
    r0.i = r0.i / r1.i;
}
void stm1(int32_t *address, int num, ...)
{
    va_list args;
    va_start(args, num);
    for (int i=0; i < num; i++)
    {
        int32_t *cur_arg = va_arg(args, int32_t *);
        *((uint32_t*) (malloc_0 + *address)) = *cur_arg;
        *address += 4;
        store_counter ++;
    }
    va_end(args);
}
void rand_help()
{
    r0.i = rand();
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
        store_counter ++;
    }
    va_end(args);
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
        load_counter ++;
    }
    va_end(args);
}
void idivmod()
{
    int32_t quot = r0.i / r1.i;
    int32_t rem = r0.i % r1.i;
    r0.i = quot;
    r1.i = rem;
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
        load_counter ++;
    }
    va_end(args);
}
void str4100(int32_t *target, int32_t *address, int32_t offset)
{
    *((uint32_t*)(malloc_0+*address+offset)) = *target;
    *address += offset;
    store_counter ++;
}
void ldr4010(int32_t *target, int32_t *address, int32_t offset)
{
    *target = *((uint32_t*)(malloc_0+*address));
    *address += offset;
    load_counter ++;
}
void smull(int32_t *dest_lo, int32_t *dest_hi, int32_t *op1, int32_t *op2)
{
    uint64_t res = (uint64_t) (*op1) * (*op2);
    *dest_lo = (uint32_t) res;
    *dest_hi = (uint32_t) (res >> 32);
}
void ldr4000(int32_t *target, int32_t *address, int32_t offset)
{
    *target = *((uint32_t*)(malloc_0+*address+offset));
    load_counter ++;
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

    *dest = count;
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
    malloc_0 = (uint8_t*) malloc(20194);
    sp.i = 19996;
    fp = sp;
    LC1 = 20000;
    strcpy(malloc_0+LC1, "array[%d]: \000");

    LC2 = 20017;
    strcpy(malloc_0+LC2, "%d\012\000");

    LC3 = 20029;
    strcpy(malloc_0+LC3, "tmp: %d\012\000");

    LC4 = 20046;
    strcpy(malloc_0+LC4, "crossSum: %d\012\000");

    LC5 = 20068;
    strcpy(malloc_0+LC5, "tmp2: %d\012\000");

    LC6 = 20086;
    strcpy(malloc_0+LC6, "%d is prime\012\000");

    LC7 = 20107;
    strcpy(malloc_0+LC7, "%d is not prime\012\000");

    LC8 = 20132;
    strcpy(malloc_0+LC8, "Ergebnis: %d\012\000");

    LC0 = 20154;
    int32_t arrayLC0[] = {1,34,6,2,6,2,7,2,17,7};
    for(int i=0; i<10; i++) *((uint32_t*)(malloc_0+LC0+i*4)) = arrayLC0[i];

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);

    printf("__count_start__\n");
    printf("%d\n", basic_blocks);

    for (int i=0; i < basic_blocks; i++)
    {
        printf("%d ", block_sizes[i]);
    }
    printf("\n");

    for (int i=0; i < basic_blocks; i++)
    {
        printf("%d ", counters[i]);
    }
    printf("\n");
    printf("%d\n", load_counter);
    printf("%d\n", store_counter);
}

void mulmod();
void modulo();
void Miller();
void swap();
void heapify();
void heapSort();
void test();
void fib();
void main();

void mulmod()
{
    counters[0] ++;
    push(2, &fp.i, &lr.i);
    fp.i = sp.i + (4);
    sp.i = sp.i - (24);
    str4000(&r0.i, &fp.i, -16);
    str4000(&r1.i, &fp.i, -20);
    str4000(&r2.i, &fp.i, -24);
    r3.i = 0;
    str4000(&r3.i, &fp.i, -8);
    ldr4000(&r3.i, &fp.i, -16);
    ldr4000(&r1.i, &fp.i, -24);
    r0.i = r3.i;
    idivmod();
    counters[1] ++;
    r3.i = r1.i;
    str4000(&r3.i, &fp.i, -12);
    goto L2;
L4:
    counters[2] ++;
    ldr4000(&r3.i, &fp.i, -20);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    r3.i = r3.i & 1;
    if (n != v)
    {
        r3.i = 0 - r3.i;
    }
    tmp = r3.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 1);
    v = (r3.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L3;
    }
    counters[3] ++;
    ldr4000(&r2.i, &fp.i, -8);
    ldr4000(&r3.i, &fp.i, -12);
    r3.i = r2.i + (r3.i);
    ldr4000(&r1.i, &fp.i, -24);
    r0.i = r3.i;
    idivmod();
    counters[4] ++;
    r3.i = r1.i;
    str4000(&r3.i, &fp.i, -8);
L3:
    counters[5] ++;
    ldr4000(&r3.i, &fp.i, -12);
    r3.i = (uint32_t)r3.i << 1;
    ldr4000(&r1.i, &fp.i, -24);
    r0.i = r3.i;
    idivmod();
    counters[6] ++;
    r3.i = r1.i;
    str4000(&r3.i, &fp.i, -12);
    ldr4000(&r3.i, &fp.i, -20);
    r2.i = (uint32_t)r3.i >> 31;
    r3.i = r2.i + (r3.i);
    r3.i = r3.i >> 1;
    str4000(&r3.i, &fp.i, -20);
L2:
    counters[7] ++;
    ldr4000(&r3.i, &fp.i, -20);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z && n == v)
    {
        goto L4;
    }
    counters[8] ++;
    ldr4000(&r3.i, &fp.i, -8);
    ldr4000(&r1.i, &fp.i, -24);
    r0.i = r3.i;
    idivmod();
    counters[9] ++;
    r3.i = r1.i;
    r0.i = r3.i;
    sp.i = fp.i - (4);
    pop(2, &pc.i, &fp.i);
    return;

}

void modulo()
{
    counters[10] ++;
    push(2, &fp.i, &lr.i);
    fp.i = sp.i + (4);
    sp.i = sp.i - (24);
    str4000(&r0.i, &fp.i, -16);
    str4000(&r1.i, &fp.i, -20);
    str4000(&r2.i, &fp.i, -24);
    r3.i = 1;
    str4000(&r3.i, &fp.i, -8);
    ldr4000(&r3.i, &fp.i, -16);
    str4000(&r3.i, &fp.i, -12);
    goto L7;
L9:
    counters[11] ++;
    ldr4000(&r3.i, &fp.i, -20);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    r3.i = r3.i & 1;
    if (n != v)
    {
        r3.i = 0 - r3.i;
    }
    tmp = r3.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 1);
    v = (r3.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L8;
    }
    counters[12] ++;
    ldr4000(&r3.i, &fp.i, -8);
    ldr4000(&r2.i, &fp.i, -12);
    r3.i = (r2.i) * (r3.i);
    ldr4000(&r1.i, &fp.i, -24);
    r0.i = r3.i;
    idivmod();
    counters[13] ++;
    r3.i = r1.i;
    str4000(&r3.i, &fp.i, -8);
L8:
    counters[14] ++;
    ldr4000(&r3.i, &fp.i, -12);
    r3.i = (r3.i) * (r3.i);
    ldr4000(&r1.i, &fp.i, -24);
    r0.i = r3.i;
    idivmod();
    counters[15] ++;
    r3.i = r1.i;
    str4000(&r3.i, &fp.i, -12);
    ldr4000(&r3.i, &fp.i, -20);
    r2.i = (uint32_t)r3.i >> 31;
    r3.i = r2.i + (r3.i);
    r3.i = r3.i >> 1;
    str4000(&r3.i, &fp.i, -20);
L7:
    counters[16] ++;
    ldr4000(&r3.i, &fp.i, -20);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z && n == v)
    {
        goto L9;
    }
    counters[17] ++;
    ldr4000(&r3.i, &fp.i, -8);
    ldr4000(&r1.i, &fp.i, -24);
    r0.i = r3.i;
    idivmod();
    counters[18] ++;
    r3.i = r1.i;
    r0.i = r3.i;
    sp.i = fp.i - (4);
    pop(2, &pc.i, &fp.i);
    return;

}

void Miller()
{
    counters[19] ++;
    push(2, &fp.i, &lr.i);
    fp.i = sp.i + (4);
    sp.i = sp.i - (32);
    str4000(&r0.i, &fp.i, -32);
    str4000(&r1.i, &fp.i, -36);
    ldr4000(&r3.i, &fp.i, -32);
    tmp = r3.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 1);
    v = (r3.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z && n == v)
    {
        goto L12;
    }
    counters[20] ++;
    r3.i = 0;
    goto L13;
L12:
    counters[21] ++;
    ldr4000(&r3.i, &fp.i, -32);
    tmp = r3.i - 2;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 2);
    v = (r3.i&0x80000000) != (2&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L14;
    }
    counters[22] ++;
    ldr4000(&r3.i, &fp.i, -32);
    r3.i = r3.i & 1;
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L14;
    }
    counters[23] ++;
    r3.i = 0;
    goto L13;
L14:
    counters[24] ++;
    ldr4000(&r3.i, &fp.i, -32);
    r3.i = r3.i - (1);
    str4000(&r3.i, &fp.i, -12);
    goto L15;
L16:
    counters[25] ++;
    ldr4000(&r3.i, &fp.i, -12);
    r2.i = (uint32_t)r3.i >> 31;
    r3.i = r2.i + (r3.i);
    r3.i = r3.i >> 1;
    str4000(&r3.i, &fp.i, -12);
L15:
    counters[26] ++;
    ldr4000(&r3.i, &fp.i, -12);
    r3.i = r3.i & 1;
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L16;
    }
    counters[27] ++;
    r3.i = 0;
    str4000(&r3.i, &fp.i, -8);
    goto L17;
L22:
    counters[28] ++;
    rand_help();
    counters[29] ++;
    r2.i = r0.i;
    ldr4000(&r3.i, &fp.i, -32);
    r3.i = r3.i - (1);
    r1.i = r3.i;
    r0.i = r2.i;
    idivmod();
    counters[30] ++;
    r3.i = r1.i;
    r3.i = r3.i + (1);
    str4000(&r3.i, &fp.i, -24);
    ldr4000(&r3.i, &fp.i, -12);
    str4000(&r3.i, &fp.i, -16);
    ldr4000(&r2.i, &fp.i, -32);
    ldr4000(&r1.i, &fp.i, -16);
    ldr4000(&r0.i, &fp.i, -24);
    modulo();
    counters[31] ++;
    str4000(&r0.i, &fp.i, -20);
    goto L18;
L20:
    counters[32] ++;
    ldr4000(&r2.i, &fp.i, -32);
    ldr4000(&r1.i, &fp.i, -20);
    ldr4000(&r0.i, &fp.i, -20);
    mulmod();
    counters[33] ++;
    str4000(&r0.i, &fp.i, -20);
    ldr4000(&r3.i, &fp.i, -16);
    r3.i = (uint32_t)r3.i << 1;
    str4000(&r3.i, &fp.i, -16);
L18:
    counters[34] ++;
    ldr4000(&r3.i, &fp.i, -32);
    r3.i = r3.i - (1);
    ldr4000(&r2.i, &fp.i, -16);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (z)
    {
        goto L19;
    }
    counters[35] ++;
    ldr4000(&r3.i, &fp.i, -20);
    tmp = r3.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 1);
    v = (r3.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L19;
    }
    counters[36] ++;
    ldr4000(&r3.i, &fp.i, -32);
    r3.i = r3.i - (1);
    ldr4000(&r2.i, &fp.i, -20);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z)
    {
        goto L20;
    }
L19:
    counters[37] ++;
    ldr4000(&r3.i, &fp.i, -32);
    r3.i = r3.i - (1);
    ldr4000(&r2.i, &fp.i, -20);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (z)
    {
        goto L21;
    }
    counters[38] ++;
    ldr4000(&r3.i, &fp.i, -16);
    r3.i = r3.i & 1;
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L21;
    }
    counters[39] ++;
    r3.i = 0;
    goto L13;
L21:
    counters[40] ++;
    ldr4000(&r3.i, &fp.i, -8);
    r3.i = r3.i + (1);
    str4000(&r3.i, &fp.i, -8);
L17:
    counters[41] ++;
    ldr4000(&r2.i, &fp.i, -8);
    ldr4000(&r3.i, &fp.i, -36);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n != v)
    {
        goto L22;
    }
    counters[42] ++;
    r3.i = 1;
L13:
    counters[43] ++;
    r0.i = r3.i;
    sp.i = fp.i - (4);
    pop(2, &pc.i, &fp.i);
    return;

}

void swap()
{
    counters[44] ++;
    str4100(&fp.i, &sp.i, -4);
    fp.i = sp.i + (0);
    sp.i = sp.i - (28);
    str4000(&r0.i, &fp.i, -16);
    str4000(&r1.i, &fp.i, -20);
    str4000(&r2.i, &fp.i, -24);
    ldr4000(&r3.i, &fp.i, -20);
    r3.i = (uint32_t)r3.i << 2;
    ldr4000(&r2.i, &fp.i, -16);
    r3.i = r2.i + (r3.i);
    ldr4000(&r3.i, &r3.i, 0);
    str4000(&r3.i, &fp.i, -8);
    ldr4000(&r3.i, &fp.i, -24);
    r3.i = (uint32_t)r3.i << 2;
    ldr4000(&r2.i, &fp.i, -16);
    r2.i = r2.i + (r3.i);
    ldr4000(&r3.i, &fp.i, -20);
    r3.i = (uint32_t)r3.i << 2;
    ldr4000(&r1.i, &fp.i, -16);
    r3.i = r1.i + (r3.i);
    ldr4000(&r2.i, &r2.i, 0);
    str4000(&r2.i, &r3.i, 0);
    ldr4000(&r3.i, &fp.i, -24);
    r3.i = (uint32_t)r3.i << 2;
    ldr4000(&r2.i, &fp.i, -16);
    r3.i = r2.i + (r3.i);
    ldr4000(&r2.i, &fp.i, -8);
    str4000(&r2.i, &r3.i, 0);
    sp.i = fp.i + (0);
    ldr4010(&fp.i, &sp.i, 4);
    return;

}

void heapify()
{
    counters[45] ++;
    push(2, &fp.i, &lr.i);
    fp.i = sp.i + (4);
    sp.i = sp.i - (32);
    str4000(&r0.i, &fp.i, -24);
    str4000(&r1.i, &fp.i, -28);
    str4000(&r2.i, &fp.i, -32);
    ldr4000(&r3.i, &fp.i, -32);
    str4000(&r3.i, &fp.i, -8);
    ldr4000(&r3.i, &fp.i, -32);
    r3.i = (uint32_t)r3.i << 1;
    r3.i = r3.i + (1);
    str4000(&r3.i, &fp.i, -12);
    ldr4000(&r3.i, &fp.i, -32);
    r3.i = r3.i + (1);
    r3.i = (uint32_t)r3.i << 1;
    str4000(&r3.i, &fp.i, -16);
    ldr4000(&r3.i, &fp.i, -12);
    ldr4000(&r2.i, &fp.i, -28);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!c || z)
    {
        goto L25;
    }
    counters[46] ++;
    ldr4000(&r3.i, &fp.i, -8);
    r3.i = (uint32_t)r3.i << 2;
    ldr4000(&r2.i, &fp.i, -24);
    r3.i = r2.i + (r3.i);
    ldr4000(&r2.i, &r3.i, 0);
    ldr4000(&r3.i, &fp.i, -12);
    r3.i = (uint32_t)r3.i << 2;
    ldr4000(&r1.i, &fp.i, -24);
    r3.i = r1.i + (r3.i);
    ldr4000(&r3.i, &r3.i, 0);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (c)
    {
        goto L25;
    }
    counters[47] ++;
    ldr4000(&r3.i, &fp.i, -12);
    str4000(&r3.i, &fp.i, -8);
L25:
    counters[48] ++;
    ldr4000(&r3.i, &fp.i, -16);
    ldr4000(&r2.i, &fp.i, -28);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!c || z)
    {
        goto L26;
    }
    counters[49] ++;
    ldr4000(&r3.i, &fp.i, -8);
    r3.i = (uint32_t)r3.i << 2;
    ldr4000(&r2.i, &fp.i, -24);
    r3.i = r2.i + (r3.i);
    ldr4000(&r2.i, &r3.i, 0);
    ldr4000(&r3.i, &fp.i, -16);
    r3.i = (uint32_t)r3.i << 2;
    ldr4000(&r1.i, &fp.i, -24);
    r3.i = r1.i + (r3.i);
    ldr4000(&r3.i, &r3.i, 0);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (c)
    {
        goto L26;
    }
    counters[50] ++;
    ldr4000(&r3.i, &fp.i, -16);
    str4000(&r3.i, &fp.i, -8);
L26:
    counters[51] ++;
    ldr4000(&r2.i, &fp.i, -8);
    ldr4000(&r3.i, &fp.i, -32);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (z)
    {
        goto L28;
    }
    counters[52] ++;
    ldr4000(&r3.i, &fp.i, -8);
    ldr4000(&r2.i, &fp.i, -32);
    r1.i = r3.i;
    ldr4000(&r0.i, &fp.i, -24);
    swap();
    counters[53] ++;
    ldr4000(&r2.i, &fp.i, -8);
    ldr4000(&r1.i, &fp.i, -28);
    ldr4000(&r0.i, &fp.i, -24);
    heapify();
L28:
    counters[54] ++;
    sp.i = fp.i - (4);
    pop(2, &pc.i, &fp.i);
    return;

}

void heapSort()
{
    counters[55] ++;
    push(2, &fp.i, &lr.i);
    fp.i = sp.i + (4);
    sp.i = sp.i - (16);
    str4000(&r0.i, &fp.i, -16);
    str4000(&r1.i, &fp.i, -20);
    ldr4000(&r3.i, &fp.i, -20);
    r3.i = (uint32_t)r3.i >> 1;
    r3.i = r3.i - (1);
    str4000(&r3.i, &fp.i, -8);
    goto L30;
L31:
    counters[56] ++;
    ldr4000(&r2.i, &fp.i, -8);
    ldr4000(&r1.i, &fp.i, -20);
    ldr4000(&r0.i, &fp.i, -16);
    heapify();
    counters[57] ++;
    ldr4000(&r3.i, &fp.i, -8);
    r3.i = r3.i - (1);
    str4000(&r3.i, &fp.i, -8);
L30:
    counters[58] ++;
    ldr4000(&r3.i, &fp.i, -8);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (n == v)
    {
        goto L31;
    }
    counters[59] ++;
    r3.i = 0;
    str4000(&r3.i, &fp.i, -12);
    goto L32;
L33:
    counters[60] ++;
    ldr4000(&r3.i, &fp.i, -12);
    ldr4000(&r2.i, &fp.i, -20);
    r3.i = r2.i - (r3.i);
    r3.i = r3.i - (1);
    r2.i = r3.i;
    r1.i = 0;
    ldr4000(&r0.i, &fp.i, -16);
    swap();
    counters[61] ++;
    ldr4000(&r3.i, &fp.i, -12);
    ldr4000(&r2.i, &fp.i, -20);
    r3.i = r2.i - (r3.i);
    r3.i = r3.i - (1);
    r2.i = 0;
    r1.i = r3.i;
    ldr4000(&r0.i, &fp.i, -16);
    heapify();
    counters[62] ++;
    ldr4000(&r3.i, &fp.i, -12);
    r3.i = r3.i + (1);
    str4000(&r3.i, &fp.i, -12);
L32:
    counters[63] ++;
    ldr4000(&r3.i, &fp.i, -20);
    r2.i = r3.i - (1);
    ldr4000(&r3.i, &fp.i, -12);
    tmp = r2.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r3.i);
    v = (r2.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (c && !z)
    {
        goto L33;
    }
    counters[64] ++;
    sp.i = fp.i - (4);
    pop(2, &pc.i, &fp.i);
    return;

}

void test()
{
    counters[65] ++;
    push(2, &fp.i, &lr.i);
    fp.i = sp.i + (4);
    sp.i = sp.i - (24);
    str4000(&r0.i, &fp.i, -24);
    r1.i = 10;
    ldr4000(&r0.i, &fp.i, -24);
    heapSort();
    counters[66] ++;
    r3.i = 0;
    str4000(&r3.i, &fp.i, -8);
    goto L35;
L36:
    counters[67] ++;
    ldr4000(&r1.i, &fp.i, -8);
    r0.i = (LC1 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC1 >> 16) << 16);
    printf_help(malloc_0+r0.i, r1.i, r2.i, r3.i);
    counters[68] ++;
    ldr4000(&r3.i, &fp.i, -8);
    r3.i = (uint32_t)r3.i << 2;
    ldr4000(&r2.i, &fp.i, -24);
    r3.i = r2.i + (r3.i);
    ldr4000(&r3.i, &r3.i, 0);
    r1.i = r3.i;
    r0.i = (LC2 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC2 >> 16) << 16);
    printf_help(malloc_0+r0.i, r1.i, r2.i, r3.i);
    counters[69] ++;
    ldr4000(&r3.i, &fp.i, -8);
    r3.i = r3.i + (1);
    str4000(&r3.i, &fp.i, -8);
L35:
    counters[70] ++;
    ldr4000(&r3.i, &fp.i, -8);
    tmp = r3.i - 9;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 9);
    v = (r3.i&0x80000000) != (9&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L36;
    }
    counters[71] ++;
    r3.i = 0;
    str4000(&r3.i, &fp.i, -12);
    r3.i = 0;
    str4000(&r3.i, &fp.i, -16);
    goto L37;
L41:
    counters[72] ++;
    ldr4000(&r1.i, &fp.i, -16);
    r3.i = 21846;
    r3.i = r3.i | (21845 << 16);
    smull(&r3.i, &r2.i, &r3.i, &r1.i);
    r3.i = r1.i >> 31;
    r2.i = r2.i - (r3.i);
    r3.i = r2.i;
    r3.i = (uint32_t)r3.i << 1;
    r3.i = r3.i + (r2.i);
    r2.i = r1.i - (r3.i);
    tmp = r2.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) 0);
    v = (r2.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (z)
    {
        goto L38;
    }
    counters[73] ++;
    ldr4000(&r3.i, &fp.i, -16);
    r3.i = (uint32_t)r3.i << 2;
    ldr4000(&r2.i, &fp.i, -24);
    r3.i = r2.i + (r3.i);
    ldr4000(&r2.i, &r3.i, 0);
    ldr4000(&r3.i, &fp.i, -12);
    r3.i = (r2.i) * (r3.i);
    str4000(&r3.i, &fp.i, -12);
L38:
    counters[74] ++;
    ldr4000(&r3.i, &fp.i, -16);
    r3.i = r3.i & 1;
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L39;
    }
    counters[75] ++;
    ldr4000(&r3.i, &fp.i, -16);
    r3.i = (uint32_t)r3.i << 2;
    ldr4000(&r2.i, &fp.i, -24);
    r3.i = r2.i + (r3.i);
    ldr4000(&r3.i, &r3.i, 0);
    ldr4000(&r2.i, &fp.i, -12);
    r3.i = r2.i + (r3.i);
    str4000(&r3.i, &fp.i, -12);
    goto L40;
L39:
    counters[76] ++;
    ldr4000(&r3.i, &fp.i, -16);
    r3.i = (uint32_t)r3.i << 2;
    ldr4000(&r2.i, &fp.i, -24);
    r3.i = r2.i + (r3.i);
    ldr4000(&r3.i, &r3.i, 0);
    ldr4000(&r2.i, &fp.i, -12);
    r3.i = r2.i - (r3.i);
    str4000(&r3.i, &fp.i, -12);
L40:
    counters[77] ++;
    ldr4000(&r3.i, &fp.i, -16);
    r3.i = r3.i + (1);
    str4000(&r3.i, &fp.i, -16);
L37:
    counters[78] ++;
    ldr4000(&r3.i, &fp.i, -16);
    tmp = r3.i - 9;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 9);
    v = (r3.i&0x80000000) != (9&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L41;
    }
    counters[79] ++;
    ldr4000(&r3.i, &fp.i, -12);
    r0.i = r3.i;
    sp.i = fp.i - (4);
    pop(2, &pc.i, &fp.i);
    return;

}

void fib()
{
    counters[80] ++;
    push(3, &r4.i, &fp.i, &lr.i);
    fp.i = sp.i + (8);
    sp.i = sp.i - (12);
    str4000(&r0.i, &fp.i, -16);
    ldr4000(&r3.i, &fp.i, -16);
    tmp = r3.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 1);
    v = (r3.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z && n == v)
    {
        goto L44;
    }
    counters[81] ++;
    ldr4000(&r3.i, &fp.i, -16);
    goto L45;
L44:
    counters[82] ++;
    ldr4000(&r3.i, &fp.i, -16);
    r3.i = r3.i - (1);
    r0.i = r3.i;
    fib();
    counters[83] ++;
    r4.i = r0.i;
    ldr4000(&r3.i, &fp.i, -16);
    r3.i = r3.i - (2);
    r0.i = r3.i;
    fib();
    counters[84] ++;
    r3.i = r0.i;
    r3.i = r4.i + (r3.i);
L45:
    counters[85] ++;
    r0.i = r3.i;
    sp.i = fp.i - (8);
    pop(3, &pc.i, &fp.i, &r4.i);
    return;

}

void main()
{
    malloc_start();
    counters[86] ++;
    push(2, &fp.i, &lr.i);
    fp.i = sp.i + (4);
    sp.i = sp.i - (56);
    r3.i = (LC0 & 0xffff);
    r3.i = r3.i | (((uint32_t)LC0 >> 16) << 16);
    ip.i = fp.i - (56);
    lr.i = r3.i;
    ldm1(&lr.i, 4, &r0.i, &r1.i, &r2.i, &r3.i);
    stm1(&ip.i, 4, &r0.i, &r1.i, &r2.i, &r3.i);
    ldm1(&lr.i, 4, &r0.i, &r1.i, &r2.i, &r3.i);
    stm1(&ip.i, 4, &r0.i, &r1.i, &r2.i, &r3.i);
    ldm0(&lr.i, 2, &r0.i, &r1.i);
    stm0(&ip.i, 2, &r0.i, &r1.i);
    r3.i = fp.i - (56);
    r0.i = r3.i;
    test();
    counters[87] ++;
    str4000(&r0.i, &fp.i, -16);
    ldr4000(&r3.i, &fp.i, -16);
    r3.i = (r3.i) * (r3.i);
    ldr4000(&r2.i, &fp.i, -16);
    r3.i = (r2.i) * (r3.i);
    ldr4000(&r2.i, &fp.i, -16);
    r3.i = (r2.i) * (r3.i);
    ldr4000(&r2.i, &fp.i, -16);
    r3.i = (r2.i) * (r3.i);
    ldr4000(&r2.i, &fp.i, -16);
    r2.i = (r2.i) * (r3.i);
    ldr4000(&r3.i, &fp.i, -16);
    r3.i = (r2.i) * (r3.i);
    str4000(&r3.i, &fp.i, -16);
    ldr4000(&r1.i, &fp.i, -16);
    r0.i = (LC3 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC3 >> 16) << 16);
    printf_help(malloc_0+r0.i, r1.i, r2.i, r3.i);
    counters[88] ++;
    r3.i = 0;
    str4000(&r3.i, &fp.i, -8);
    ldr4000(&r3.i, &fp.i, -16);
    str4000(&r3.i, &fp.i, -12);
    goto L47;
L48:
    counters[89] ++;
    ldr4000(&r2.i, &fp.i, -12);
    r3.i = 26215;
    r3.i = r3.i | (26214 << 16);
    smull(&r1.i, &r3.i, &r3.i, &r2.i);
    r1.i = r3.i >> 2;
    r3.i = r2.i >> 31;
    r3.i = r1.i - (r3.i);
    r1.i = 10;
    r3.i = (r1.i) * (r3.i);
    r3.i = r2.i - (r3.i);
    ldr4000(&r2.i, &fp.i, -8);
    r3.i = r2.i + (r3.i);
    str4000(&r3.i, &fp.i, -8);
    ldr4000(&r2.i, &fp.i, -12);
    r3.i = 26215;
    r3.i = r3.i | (26214 << 16);
    smull(&r1.i, &r3.i, &r3.i, &r2.i);
    r1.i = r3.i >> 2;
    r3.i = r2.i >> 31;
    r3.i = r1.i - (r3.i);
    str4000(&r3.i, &fp.i, -12);
L47:
    counters[90] ++;
    ldr4000(&r3.i, &fp.i, -12);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L48;
    }
    counters[91] ++;
    ldr4000(&r1.i, &fp.i, -8);
    r0.i = (LC4 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC4 >> 16) << 16);
    printf_help(malloc_0+r0.i, r1.i, r2.i, r3.i);
    counters[92] ++;
    ldr4000(&r3.i, &fp.i, -8);
    r3.i = (r3.i) * (r3.i);
    r1.i = r3.i;
    ldr4000(&r0.i, &fp.i, -16);
    idiv();
    counters[93] ++;
    r3.i = r0.i;
    str4000(&r3.i, &fp.i, -16);
    ldr4000(&r1.i, &fp.i, -16);
    r0.i = (LC5 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC5 >> 16) << 16);
    printf_help(malloc_0+r0.i, r1.i, r2.i, r3.i);
    counters[94] ++;
    ldr4000(&r0.i, &fp.i, -8);
    fib();
    counters[95] ++;
    r3.i = r0.i;
    ldr4000(&r1.i, &fp.i, -8);
    r0.i = r3.i;
    idiv();
    counters[96] ++;
    r3.i = r0.i;
    r1.i = r3.i;
    ldr4000(&r0.i, &fp.i, -16);
    idiv();
    counters[97] ++;
    r3.i = r0.i;
    str4000(&r3.i, &fp.i, -16);
    r1.i = 10;
    ldr4000(&r0.i, &fp.i, -16);
    Miller();
    counters[98] ++;
    r3.i = r0.i;
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L49;
    }
    counters[99] ++;
    ldr4000(&r1.i, &fp.i, -16);
    r0.i = (LC6 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC6 >> 16) << 16);
    printf_help(malloc_0+r0.i, r1.i, r2.i, r3.i);
    counters[100] ++;
    goto L50;
L49:
    counters[101] ++;
    ldr4000(&r1.i, &fp.i, -16);
    r0.i = (LC7 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC7 >> 16) << 16);
    printf_help(malloc_0+r0.i, r1.i, r2.i, r3.i);
L50:
    counters[102] ++;
    ldr4000(&r1.i, &fp.i, -16);
    r0.i = (LC8 & 0xffff);
    r0.i = r0.i | (((uint32_t)LC8 >> 16) << 16);
    printf_help(malloc_0+r0.i, r1.i, r2.i, r3.i);
    counters[103] ++;
    r3.i = 0;
    r0.i = r3.i;
    sp.i = fp.i - (4);
    pop(2, &pc.i, &fp.i);
    counter_summary();
    return;

}

