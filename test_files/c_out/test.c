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

reg r5, r7, r6, r0, r8, r10, r3, r9, r1, r4, r2;

int32_t LC1, LC2, LC3, LC4, LC5, LC6, LC7, LC8, LC0;

int load_counter = 0, store_counter = 0;
int counters[100] = { 0 };
int block_sizes[100] = {5,2,3,3,5,1,5,3,2,1,3,2,4,3,3,5,1,5,3,2,1,3,2,2,5,2,2,1,4,2,2,3,2,2,3,1,2,5,9,1,3,10,2,2,2,2,2,2,2,5,8,4,3,5,2,4,2,3,4,1,6,4,2,2,1,4,4,2,1,4,7,4,4,3,4,7,7,4,2,3,2,13,5,5,1,6,2,5,8,5,3,6,2,2,3,3,8,5,3,2};

void i2d()
{
    double result = (double) r0.i;
    uint64_t result_uint64 = *(uint64_t *)&result;
    r1.i = (uint32_t) (result_uint64 >> 32);
    r0.i = (uint32_t) result_uint64;
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
    }
    va_end(args);
    store_counter ++;
}
void ldr4100(int32_t *target, int32_t *address, int32_t offset)
{
    *target = *((uint32_t*)(malloc_0+*address+offset));
    *address += offset;
    load_counter ++;
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
    store_counter ++;
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
    load_counter ++;
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
    }
    va_end(args);
    load_counter ++;
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
void stm1(int32_t *address, int num, ...)
{
    va_list args;
    va_start(args, num);
    for (int i=0; i < num; i++)
    {
        int32_t *cur_arg = va_arg(args, int32_t *);
        *((uint32_t*) (malloc_0 + *address)) = *cur_arg;
        *address += 4;
    }
    va_end(args);
    store_counter ++;
}
void rand_help()
{
    r0.i = rand();
}
void str4000(int32_t *target, int32_t *address, int32_t offset)
{
    *((uint32_t*)(malloc_0+*address+offset)) = *target;
    store_counter ++;
}
void d2iz()
{
    uint64_t op_int = ((uint64_t)(uint32_t) r1.i) << 32 | ((uint64_t)(uint32_t) r0.i);
    r0.i = (int32_t) *(double *)&op_int;
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
    load_counter ++;
}
void idiv()
{
    r0.i = r0.i / r1.i;
}
void idivmod()
{
    int32_t quot = r0.i / r1.i;
    int32_t rem = r0.i % r1.i;
    r0.i = quot;
    r1.i = rem;
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
    push(6, &r4.i, &r5.i, &r6.i, &r7.i, &r8.i, &lr.i);
    r4.i = r1.i;
    r6.i = r2.i;
    r1.i = r2.i;
    idivmod();
    counters[1] ++;
    tmp = r4.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 0);
    v = (r4.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (z || n != v)
    {
        goto L5;
    }
    counters[2] ++;
    r5.i = r1.i;
    r7.i = 0;
    goto L4;
L3:
    counters[3] ++;
    r1.i = r6.i;
    r0.i = (uint32_t)r5.i << 1;
    idivmod();
    counters[4] ++;
    r5.i = r1.i;
    r3.i = r4.i + (((uint32_t)r4.i >> 31));
    r3.i = r3.i >> 1;
    tmp = r4.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 1);
    v = (r4.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (z || n != v)
    {
        goto L2;
    }
    counters[5] ++;
    r4.i = r3.i;
L4:
    counters[6] ++;
    tmp = r4.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 0);
    v = (r4.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    r3.i = r4.i & 1;
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
    counters[7] ++;
    r1.i = r6.i;
    r0.i = r7.i + (r5.i);
    idivmod();
    counters[8] ++;
    r7.i = r1.i;
    goto L3;
L5:
    counters[9] ++;
    r7.i = 0;
L2:
    counters[10] ++;
    r1.i = r6.i;
    r0.i = r7.i;
    idivmod();
    counters[11] ++;
    r0.i = r1.i;
    pop(6, &pc.i, &r8.i, &r7.i, &r6.i, &r5.i, &r4.i);
    return;

}

void modulo()
{
    counters[12] ++;
    push(6, &r4.i, &r5.i, &r6.i, &r7.i, &r8.i, &lr.i);
    r6.i = r2.i;
    r4.i = r1.i - (0);
    z = r4.i == 0;
    n = r4.i & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 0);
    v = (r1.i&0x80000000) != (0&0x80000000) && (r4.i&0x80000000) != (r1.i&0x80000000);
    if (z || n != v)
    {
        goto L12;
    }
    counters[13] ++;
    r5.i = r0.i;
    r7.i = 1;
    goto L11;
L10:
    counters[14] ++;
    r1.i = r6.i;
    r0.i = (r5.i) * (r5.i);
    idivmod();
    counters[15] ++;
    r5.i = r1.i;
    r3.i = r4.i + (((uint32_t)r4.i >> 31));
    r3.i = r3.i >> 1;
    tmp = r4.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 1);
    v = (r4.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (z || n != v)
    {
        goto L9;
    }
    counters[16] ++;
    r4.i = r3.i;
L11:
    counters[17] ++;
    tmp = r4.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 0);
    v = (r4.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    r3.i = r4.i & 1;
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
        goto L10;
    }
    counters[18] ++;
    r1.i = r6.i;
    r0.i = (r5.i) * (r7.i);
    idivmod();
    counters[19] ++;
    r7.i = r1.i;
    goto L10;
L12:
    counters[20] ++;
    r7.i = 1;
L9:
    counters[21] ++;
    r1.i = r6.i;
    r0.i = r7.i;
    idivmod();
    counters[22] ++;
    r0.i = r1.i;
    pop(6, &pc.i, &r8.i, &r7.i, &r6.i, &r5.i, &r4.i);
    return;

}

void Miller()
{
    counters[23] ++;
    tmp = r0.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 1);
    v = (r0.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (z || n != v)
    {
        goto L23;
    }
    counters[24] ++;
    push(8, &r4.i, &r5.i, &r6.i, &r7.i, &r8.i, &r9.i, &r10.i, &lr.i);
    r5.i = r0.i;
    r8.i = r1.i;
    tmp = r0.i - 2;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 2);
    v = (r0.i&0x80000000) != (2&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (z)
    {
        goto L24;
    }
    counters[25] ++;
    tmp = r0.i & 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    if (z)
    {
        goto L25;
    }
    counters[26] ++;
    r4.i = r0.i - (1);
    if (z)
    {
        goto L26;
    }
    counters[27] ++;
    r6.i = r4.i;
L18:
    counters[28] ++;
    r3.i = r6.i + (((uint32_t)r6.i >> 31));
    r6.i = r3.i >> 1;
    tmp = r3.i & 2;
    z = tmp == 0;
    n = tmp & 0x80000000;
    if (z)
    {
        goto L18;
    }
L17:
    counters[29] ++;
    tmp = r8.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) 0);
    v = (r8.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    if (z || n != v)
    {
        goto L27;
    }
    counters[30] ++;
    r7.i = 0;
    goto L22;
L24:
    counters[31] ++;
    r4.i = 1;
    r6.i = r4.i;
    goto L17;
L26:
    counters[32] ++;
    r6.i = r4.i;
    goto L17;
L28:
    counters[33] ++;
    r9.i = r6.i;
    goto L19;
L21:
    counters[34] ++;
    r7.i = r7.i + (1);
    tmp = r8.i - r7.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) r7.i);
    v = (r8.i&0x80000000) != (r7.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    if (z)
    {
        goto L37;
    }
L22:
    counters[35] ++;
    rand_help();
    counters[36] ++;
    r1.i = r4.i;
    idivmod();
    counters[37] ++;
    r0.i = r1.i;
    r2.i = r5.i;
    r1.i = r6.i;
    r0.i = r0.i + (1);
    modulo();
    counters[38] ++;
    tmp = r0.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 1);
    v = (r0.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        tmp = r4.i - r0.i;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r4.i) >= ((uint32_t) r0.i);
        v = (r4.i&0x80000000) != (r0.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    }
    if (!z)
    {
        r3.i = 1;
    }
    if (z)
    {
        r3.i = 0;
    }
    tmp = r4.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r6.i);
    v = (r4.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (z)
    {
        r3.i = 0;
    }
    if (!z)
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
        goto L28;
    }
    counters[39] ++;
    r9.i = r6.i;
L20:
    counters[40] ++;
    r2.i = r5.i;
    r1.i = r0.i;
    mulmod();
    counters[41] ++;
    r9.i = (uint32_t)r9.i << 1;
    tmp = r0.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 1);
    v = (r0.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        tmp = r4.i - r0.i;
        z = tmp == 0;
        n = tmp & 0x80000000;
        c = ((uint32_t) r4.i) >= ((uint32_t) r0.i);
        v = (r4.i&0x80000000) != (r0.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    }
    if (!z)
    {
        r3.i = 1;
    }
    if (z)
    {
        r3.i = 0;
    }
    tmp = r4.i - r9.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r9.i);
    v = (r4.i&0x80000000) != (r9.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (z)
    {
        r3.i = 0;
    }
    if (!z)
    {
        r3.i = r3.i & 1;
    }
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L20;
    }
L19:
    counters[42] ++;
    tmp = r4.i - r0.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r0.i);
    v = (r4.i&0x80000000) != (r0.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (z)
    {
        goto L21;
    }
    counters[43] ++;
    tmp = r9.i & 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    if (!z)
    {
        goto L21;
    }
    counters[44] ++;
    r0.i = 0;
    pop(8, &pc.i, &r10.i, &r9.i, &r8.i, &r7.i, &r6.i, &r5.i, &r4.i);
    return;
L37:
    counters[45] ++;
    r0.i = 1;
    pop(8, &pc.i, &r10.i, &r9.i, &r8.i, &r7.i, &r6.i, &r5.i, &r4.i);
    return;
L23:
    counters[46] ++;
    r0.i = 0;
    return;
L25:
    counters[47] ++;
    r0.i = 0;
    pop(8, &pc.i, &r10.i, &r9.i, &r8.i, &r7.i, &r6.i, &r5.i, &r4.i);
    return;
L27:
    counters[48] ++;
    r0.i = 1;
    pop(8, &pc.i, &r10.i, &r9.i, &r8.i, &r7.i, &r6.i, &r5.i, &r4.i);
    return;

}

void swap()
{
    counters[49] ++;
    ldr4000(&r3.i, &r0.i, ((uint32_t)r1.i << 2));
    ldr4000(&ip.i, &r0.i, ((uint32_t)r2.i << 2));
    str4000(&ip.i, &r0.i, ((uint32_t)r1.i << 2));
    str4000(&r3.i, &r0.i, ((uint32_t)r2.i << 2));
    return;

}

void heapify()
{
    counters[50] ++;
    push(4, &r4.i, &r5.i, &r6.i, &lr.i);
    r5.i = r0.i;
    r6.i = r1.i;
    r4.i = (uint32_t)r2.i << 1;
    r3.i = r4.i + (1);
    r4.i = r4.i + (2);
    tmp = r3.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r1.i);
    v = (r3.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (c)
    {
        goto L40;
    }
    counters[51] ++;
    ldr4000(&r0.i, &r0.i, ((uint32_t)r2.i << 2));
    ldr4000(&r1.i, &r5.i, ((uint32_t)r3.i << 2));
    tmp = r0.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) r1.i);
    v = (r0.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (c)
    {
        goto L40;
    }
    counters[52] ++;
    tmp = r4.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r6.i);
    v = (r4.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (c)
    {
        r4.i = r3.i;
    }
    if (c)
    {
        goto L41;
    }
    counters[53] ++;
    r0.i = r1.i;
    ldr4000(&r1.i, &r5.i, ((uint32_t)r4.i << 2));
    tmp = r0.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) r1.i);
    v = (r0.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (c)
    {
        r4.i = r3.i;
    }
    goto L41;
L40:
    counters[54] ++;
    tmp = r6.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) r4.i);
    v = (r6.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    if (!c || z)
    {
        pop(4, &pc.i, &r6.i, &r5.i, &r4.i);
        return;
    }
    counters[55] ++;
    ldr4000(&r1.i, &r5.i, ((uint32_t)r2.i << 2));
    ldr4000(&r3.i, &r5.i, ((uint32_t)r4.i << 2));
    tmp = r1.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r3.i);
    v = (r1.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (c)
    {
        pop(4, &pc.i, &r6.i, &r5.i, &r4.i);
        return;
    }
L41:
    counters[56] ++;
    tmp = r4.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r2.i);
    v = (r4.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (z)
    {
        pop(4, &pc.i, &r6.i, &r5.i, &r4.i);
        return;
    }
    counters[57] ++;
    r1.i = r4.i;
    r0.i = r5.i;
    swap();
    counters[58] ++;
    r2.i = r4.i;
    r1.i = r6.i;
    r0.i = r5.i;
    heapify();
    counters[59] ++;
    pop(4, &pc.i, &r6.i, &r5.i, &r4.i);
    return;

}

void heapSort()
{
    counters[60] ++;
    push(4, &r4.i, &r5.i, &r6.i, &lr.i);
    r6.i = r0.i;
    r4.i = r1.i;
    r5.i = (uint32_t)r1.i >> 1;
    r5.i = r5.i - (1);
    z = r5.i == 0;
    n = r5.i & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) 1);
    v = (r5.i&0x80000000) != (1&0x80000000) && (r5.i&0x80000000) != (r5.i&0x80000000);
    if (n)
    {
        goto L47;
    }
L48:
    counters[61] ++;
    r2.i = r5.i;
    r1.i = r4.i;
    r0.i = r6.i;
    heapify();
    counters[62] ++;
    r5.i = r5.i - (1);
    z = r5.i == 0;
    n = r5.i & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) 1);
    v = (r5.i&0x80000000) != (1&0x80000000) && (r5.i&0x80000000) != (r5.i&0x80000000);
    if (!n)
    {
        goto L48;
    }
L47:
    counters[63] ++;
    r4.i = r4.i - (1);
    z = r4.i == 0;
    n = r4.i & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 1);
    v = (r4.i&0x80000000) != (1&0x80000000) && (r4.i&0x80000000) != (r4.i&0x80000000);
    if (z)
    {
        pop(4, &pc.i, &r6.i, &r5.i, &r4.i);
        return;
    }
    counters[64] ++;
    r5.i = 0;
L50:
    counters[65] ++;
    r2.i = r4.i;
    r1.i = r5.i;
    r0.i = r6.i;
    swap();
    counters[66] ++;
    r2.i = r5.i;
    r1.i = r4.i;
    r0.i = r6.i;
    heapify();
    counters[67] ++;
    r4.i = r4.i - (1);
    z = r4.i == 0;
    n = r4.i & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 1);
    v = (r4.i&0x80000000) != (1&0x80000000) && (r4.i&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        goto L50;
    }
    counters[68] ++;
    pop(4, &pc.i, &r6.i, &r5.i, &r4.i);
    return;

}

void test()
{
    counters[69] ++;
    push(8, &r4.i, &r5.i, &r6.i, &r7.i, &r8.i, &r9.i, &r10.i, &lr.i);
    r6.i = r0.i;
    r1.i = 10;
    heapSort();
    counters[70] ++;
    r7.i = r6.i - (4);
    r4.i = 0;
    r9.i = (LC1 & 0xffff);
    r9.i = r9.i | (((uint32_t)LC1 >> 16) << 16);
    r5.i = 1;
    r8.i = (LC2 & 0xffff);
    r8.i = r8.i | (((uint32_t)LC2 >> 16) << 16);
L55:
    counters[71] ++;
    r2.i = r4.i;
    r1.i = r9.i;
    r0.i = r5.i;
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[72] ++;
    ldr4100(&r2.i, &r7.i, 4);
    r1.i = r8.i;
    r0.i = r5.i;
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[73] ++;
    r4.i = r4.i + (1);
    tmp = r4.i - 10;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 10);
    v = (r4.i&0x80000000) != (10&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        goto L55;
    }
    counters[74] ++;
    r3.i = 0;
    r0.i = r3.i;
    r1.i = 21846;
    r1.i = r1.i | (21845 << 16);
L56:
    counters[75] ++;
    tmp = r3.i & 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    ldr4000(&r2.i, &r6.i, ((uint32_t)r3.i << 2));
    if (z)
    {
        r0.i = r0.i + (r2.i);
    }
    if (!z)
    {
        r0.i = r0.i - (r2.i);
    }
    r3.i = r3.i + (1);
    tmp = r3.i - 10;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 10);
    v = (r3.i&0x80000000) != (10&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        pop(8, &pc.i, &r10.i, &r9.i, &r8.i, &r7.i, &r6.i, &r5.i, &r4.i);
        return;
    }
    counters[76] ++;
    smull(&ip.i, &r2.i, &r1.i, &r3.i);
    r2.i = r2.i - ((r3.i >> 31));
    r2.i = r2.i + (((uint32_t)r2.i << 1));
    tmp = r3.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r2.i);
    v = (r3.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        ldr4000(&r2.i, &r6.i, ((uint32_t)r3.i << 2));
    }
    if (!z)
    {
        r0.i = (r2.i) * (r0.i);
    }
    goto L56;
    return;
}

void fib()
{
    counters[77] ++;
    push(4, &r4.i, &r5.i, &r6.i, &lr.i);
    r4.i = r0.i;
    tmp = r0.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 1);
    v = (r0.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (z || n != v)
    {
        pop(4, &pc.i, &r6.i, &r5.i, &r4.i);
        return;
    }
    counters[78] ++;
    r0.i = r0.i - (1);
    fib();
    counters[79] ++;
    r5.i = r0.i;
    r0.i = r4.i - (2);
    fib();
    counters[80] ++;
    r0.i = r5.i + (r0.i);
    pop(4, &pc.i, &r6.i, &r5.i, &r4.i);
    return;

}

void main()
{
    malloc_start();
    counters[81] ++;
    push(3, &r4.i, &r5.i, &lr.i);
    sp.i = sp.i - (44);
    lr.i = sp.i;
    ip.i = (LC0 & 0xffff);
    ip.i = ip.i | (((uint32_t)LC0 >> 16) << 16);
    ldm1(&ip.i, 4, &r0.i, &r1.i, &r2.i, &r3.i);
    stm1(&lr.i, 4, &r0.i, &r1.i, &r2.i, &r3.i);
    ldm1(&ip.i, 4, &r0.i, &r1.i, &r2.i, &r3.i);
    stm1(&lr.i, 4, &r0.i, &r1.i, &r2.i, &r3.i);
    ldm0(&ip.i, 2, &r0.i, &r1.i);
    stm0(&lr.i, 2, &r0.i, &r1.i);
    r0.i = sp.i;
    test();
    counters[82] ++;
    r3.i = (r0.i) * (r0.i);
    r3.i = (r3.i) * (r0.i);
    r3.i = (r3.i) * (r3.i);
    r0.i = (r0.i) * (r3.i);
    i2d();
    counters[83] ++;
    r2.i = 18350;
    r2.i = r2.i | (31457 << 16);
    r3.i = 44564;
    r3.i = r3.i | (16371 << 16);
    dadd();
    counters[84] ++;
    d2iz();
    counters[85] ++;
    r5.i = r0.i;
    r2.i = r0.i;
    r1.i = (LC3 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC3 >> 16) << 16);
    r0.i = 1;
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[86] ++;
    tmp = r5.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) 0);
    v = (r5.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (z)
    {
        goto L73;
    }
    counters[87] ++;
    r3.i = r5.i;
    r4.i = 0;
    ip.i = 26215;
    ip.i = ip.i | (26214 << 16);
    r0.i = 10;
L70:
    counters[88] ++;
    smull(&r2.i, &r1.i, &ip.i, &r3.i);
    r2.i = r3.i >> 31;
    r2.i = (r1.i >> 2) - r2.i;
    r3.i = r3.i - ((r0.i) * (r2.i));
    r4.i = r4.i + (r3.i);
    r3.i = r2.i;
    tmp = r2.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) 0);
    v = (r2.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z)
    {
        goto L70;
    }
L69:
    counters[89] ++;
    r2.i = r4.i;
    r1.i = (LC4 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC4 >> 16) << 16);
    r0.i = 1;
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[90] ++;
    r1.i = (r4.i) * (r4.i);
    r0.i = r5.i;
    idiv();
    counters[91] ++;
    r5.i = r0.i;
    r2.i = r0.i;
    r1.i = (LC5 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC5 >> 16) << 16);
    r0.i = 1;
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[92] ++;
    r0.i = r4.i;
    fib();
    counters[93] ++;
    r1.i = r4.i;
    idiv();
    counters[94] ++;
    r1.i = r0.i;
    r0.i = r5.i;
    idiv();
    counters[95] ++;
    r4.i = r0.i;
    r1.i = 10;
    Miller();
    counters[96] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    r2.i = r4.i;
    if (!z)
    {
        r1.i = (LC6 & 0xffff);
    }
    if (!z)
    {
        r1.i = r1.i | (((uint32_t)LC6 >> 16) << 16);
    }
    if (z)
    {
        r1.i = (LC7 & 0xffff);
    }
    if (z)
    {
        r1.i = r1.i | (((uint32_t)LC7 >> 16) << 16);
    }
    r0.i = 1;
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[97] ++;
    r2.i = r4.i;
    r1.i = (LC8 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC8 >> 16) << 16);
    r0.i = 1;
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[98] ++;
    r0.i = 0;
    sp.i = sp.i + (44);
    pop(3, &pc.i, &r5.i, &r4.i);
    counter_summary();
    return;
L73:
    counters[99] ++;
    r4.i = r5.i;
    goto L69;
    return;
}

