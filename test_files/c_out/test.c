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

reg r1, r5, r8, r0, r4, r9, r3, r2, r10, r7, r6;

int32_t LC1, LC2, LC3, LC4, LC5, LC6, LC7, LC8, LC0;

int load_counter = 0, store_counter = 0;
int counters[131] = { 0 };
int block_sizes[131] = {8,3,5,1,2,3,4,1,1,3,3,3,3,2,2,1,3,4,1,4,1,1,3,3,3,3,2,2,6,1,3,1,2,2,1,1,2,2,1,3,1,5,2,2,4,1,1,3,3,3,2,2,4,2,4,1,1,3,3,3,2,2,2,2,2,1,2,5,2,4,3,2,5,5,2,4,2,1,4,4,1,3,2,2,2,8,2,1,4,6,5,4,2,8,8,4,2,7,3,3,3,13,10,2,5,7,5,3,6,2,5,3,3,1,3,3,3,2,2,3,2,5,5,3,5,1,2,5,3,5,1};

void smull(int32_t *dest_lo, int32_t *dest_hi, int32_t *op1, int32_t *op2)
{
    uint64_t res = (uint64_t) (*op1) * (*op2);
    *dest_lo = (uint32_t) res;
    *dest_hi = (uint32_t) (res >> 32);
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
void idivmod()
{
    int32_t quot = r0.i / r1.i;
    int32_t rem = r0.i % r1.i;
    r0.i = quot;
    r1.i = rem;
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
void ldr4000(int32_t *target, int32_t *address, int32_t offset)
{
    *target = *((uint32_t*)(malloc_0+*address+offset));
    load_counter ++;
}
void idiv()
{
    r0.i = r0.i / r1.i;
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
        store_counter ++;
    }
    va_end(args);
}
void str4000(int32_t *target, int32_t *address, int32_t offset)
{
    *((uint32_t*)(malloc_0+*address+offset)) = *target;
    store_counter ++;
}
void rand_help()
{
    r0.i = rand();
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

void Millerpart0();
void mulmod();
void modulo();
void Miller();
void swap();
void heapify();
void heapSort();
void test();
void fib();
void main();

void Millerpart0()
{
    counters[0] ++;
    push(9, &r4.i, &r5.i, &r6.i, &r7.i, &r8.i, &r9.i, &r10.i, &fp.i, &lr.i);
    tmp = r0.i & 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    sp.i = sp.i - (12);
    r8.i = r0.i - (1);
    fp.i = r0.i;
    r9.i = r8.i;
    str4000(&r1.i, &sp.i, 4);
    if (z)
    {
        goto L2;
    }
L3:
    counters[1] ++;
    r9.i = r9.i >> 1;
    tmp = r9.i & 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    if (z)
    {
        goto L3;
    }
L2:
    counters[2] ++;
    ldr4000(&r3.i, &sp.i, 4);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z && n == v)
    {
        r3.i = 0;
    }
    if (!z && n == v)
    {
        str4000(&r3.i, &sp.i, 0);
    }
    if (z || n != v)
    {
        goto L14;
    }
L4:
    counters[3] ++;
    rand_help();
    counters[4] ++;
    r1.i = r8.i;
    idivmod();
    counters[5] ++;
    r6.i = r9.i;
    r5.i = 1;
    r4.i = r1.i + (1);
L7:
    counters[6] ++;
    tmp = r6.i & 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    r1.i = fp.i;
    r0.i = (r4.i) * (r5.i);
    if (z)
    {
        goto L6;
    }
    counters[7] ++;
    idivmod();
    counters[8] ++;
    r5.i = r1.i;
L6:
    counters[9] ++;
    r0.i = (r4.i) * (r4.i);
    r1.i = fp.i;
    idivmod();
    counters[10] ++;
    r6.i = r6.i >> 1;
    z = r6.i == 0;
    n = r6.i & 0x80000000;
    c = r6.i & (1 << 1 - 1);
    r4.i = r1.i;
    if (!z)
    {
        goto L7;
    }
    counters[11] ++;
    r0.i = r5.i;
    r1.i = fp.i;
    idivmod();
    counters[12] ++;
    tmp = r8.i - r9.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) r9.i);
    v = (r8.i&0x80000000) != (r9.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    r10.i = r1.i;
    if (z)
    {
        goto L18;
    }
    counters[13] ++;
    tmp = r1.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 1);
    v = (r1.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (z)
    {
        goto L19;
    }
    counters[14] ++;
    tmp = r8.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) r1.i);
    v = (r8.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    if (z)
    {
        goto L9;
    }
    counters[15] ++;
    r7.i = r9.i;
L13:
    counters[16] ++;
    r1.i = fp.i;
    r0.i = r10.i;
    idivmod();
    counters[17] ++;
    tmp = r10.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r10.i) >= ((uint32_t) 0);
    v = (r10.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r10.i&0x80000000);
    r7.i = (uint32_t)r7.i << 1;
    r4.i = r1.i;
    if (z || n != v)
    {
        goto L10;
    }
    counters[18] ++;
    r5.i = 0;
L12:
    counters[19] ++;
    tmp = r10.i & 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    r0.i = r5.i + (r4.i);
    r1.i = fp.i;
    if (z)
    {
        goto L11;
    }
    counters[20] ++;
    idivmod();
    counters[21] ++;
    r5.i = r1.i;
L11:
    counters[22] ++;
    r0.i = (uint32_t)r4.i << 1;
    r1.i = fp.i;
    idivmod();
    counters[23] ++;
    r10.i = r10.i >> 1;
    z = r10.i == 0;
    n = r10.i & 0x80000000;
    c = r10.i & (1 << 1 - 1);
    r4.i = r1.i;
    if (!z)
    {
        goto L12;
    }
    counters[24] ++;
    r0.i = r5.i;
    r1.i = fp.i;
    idivmod();
    counters[25] ++;
    tmp = r8.i - r7.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) r7.i);
    v = (r8.i&0x80000000) != (r7.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    r10.i = r1.i;
    if (z)
    {
        goto L8;
    }
    counters[26] ++;
    tmp = r1.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 1);
    v = (r1.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (z)
    {
        goto L8;
    }
    counters[27] ++;
    tmp = r8.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) r1.i);
    v = (r8.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    if (!z)
    {
        goto L13;
    }
L9:
    counters[28] ++;
    ldr4000(&r3.i, &sp.i, 0);
    ldr4000(&r2.i, &sp.i, 4);
    r3.i = r3.i + (1);
    str4000(&r3.i, &sp.i, 0);
    tmp = r3.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r2.i);
    v = (r3.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L4;
    }
L14:
    counters[29] ++;
    r6.i = 1;
L1:
    counters[30] ++;
    r0.i = r6.i;
    sp.i = sp.i + (12);
    pop(9, &pc.i, &fp.i, &r10.i, &r9.i, &r8.i, &r7.i, &r6.i, &r5.i, &r4.i);
    return;
L41:
    counters[31] ++;
    r7.i = (uint32_t)r7.i << 1;
L10:
    counters[32] ++;
    tmp = r8.i - r7.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) r7.i);
    v = (r8.i&0x80000000) != (r7.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    if (!z)
    {
        goto L41;
    }
    counters[33] ++;
    tmp = r7.i & 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    if (!z)
    {
        goto L9;
    }
    counters[34] ++;
    goto L1;
L19:
    counters[35] ++;
    r7.i = r9.i;
L8:
    counters[36] ++;
    tmp = r8.i - r10.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) r10.i);
    v = (r8.i&0x80000000) != (r10.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    if (z)
    {
        goto L9;
    }
L42:
    counters[37] ++;
    tmp = r7.i & 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    if (!z)
    {
        goto L9;
    }
    counters[38] ++;
    goto L1;
L18:
    counters[39] ++;
    tmp = r8.i - r10.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) r10.i);
    v = (r8.i&0x80000000) != (r10.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    r7.i = r8.i;
    if (!z)
    {
        goto L42;
    }
    counters[40] ++;
    goto L9;
    return;
}

void mulmod()
{
    counters[41] ++;
    push(6, &r4.i, &r5.i, &r6.i, &r7.i, &r8.i, &lr.i);
    r5.i = r1.i;
    r1.i = r2.i;
    r7.i = r2.i;
    idivmod();
    counters[42] ++;
    tmp = r5.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) 0);
    v = (r5.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (z || n != v)
    {
        goto L47;
    }
    counters[43] ++;
    r4.i = r1.i;
    r6.i = 0;
L46:
    counters[44] ++;
    tmp = r5.i & 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    r0.i = r6.i + (r4.i);
    r1.i = r7.i;
    if (z)
    {
        goto L45;
    }
    counters[45] ++;
    idivmod();
    counters[46] ++;
    r6.i = r1.i;
L45:
    counters[47] ++;
    r0.i = (uint32_t)r4.i << 1;
    r1.i = r7.i;
    idivmod();
    counters[48] ++;
    r5.i = r5.i >> 1;
    z = r5.i == 0;
    n = r5.i & 0x80000000;
    c = r5.i & (1 << 1 - 1);
    r4.i = r1.i;
    if (!z)
    {
        goto L46;
    }
    counters[49] ++;
    r1.i = r7.i;
    r0.i = r6.i;
    idivmod();
    counters[50] ++;
    r0.i = r1.i;
    pop(6, &pc.i, &r8.i, &r7.i, &r6.i, &r5.i, &r4.i);
    return;
L47:
    counters[51] ++;
    r0.i = 0;
    pop(6, &pc.i, &r8.i, &r7.i, &r6.i, &r5.i, &r4.i);
    return;

}

void modulo()
{
    counters[52] ++;
    push(6, &r4.i, &r5.i, &r6.i, &r7.i, &r8.i, &lr.i);
    r5.i = r1.i - (0);
    z = r5.i == 0;
    n = r5.i & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 0);
    v = (r1.i&0x80000000) != (0&0x80000000) && (r5.i&0x80000000) != (r1.i&0x80000000);
    r7.i = r2.i;
    if (z || n != v)
    {
        goto L57;
    }
    counters[53] ++;
    r4.i = r0.i;
    r6.i = 1;
L56:
    counters[54] ++;
    tmp = r5.i & 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    r1.i = r7.i;
    r0.i = (r4.i) * (r6.i);
    if (z)
    {
        goto L55;
    }
    counters[55] ++;
    idivmod();
    counters[56] ++;
    r6.i = r1.i;
L55:
    counters[57] ++;
    r0.i = (r4.i) * (r4.i);
    r1.i = r7.i;
    idivmod();
    counters[58] ++;
    r5.i = r5.i >> 1;
    z = r5.i == 0;
    n = r5.i & 0x80000000;
    c = r5.i & (1 << 1 - 1);
    r4.i = r1.i;
    if (!z)
    {
        goto L56;
    }
L54:
    counters[59] ++;
    r1.i = r7.i;
    r0.i = r6.i;
    idivmod();
    counters[60] ++;
    r0.i = r1.i;
    pop(6, &pc.i, &r8.i, &r7.i, &r6.i, &r5.i, &r4.i);
    return;
L57:
    counters[61] ++;
    r6.i = 1;
    goto L54;
    return;
}

void Miller()
{
    counters[62] ++;
    tmp = r0.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 1);
    v = (r0.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (z || n != v)
    {
        goto L63;
    }
    counters[63] ++;
    tmp = r0.i - 2;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 2);
    v = (r0.i&0x80000000) != (2&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (z)
    {
        goto L65;
    }
    counters[64] ++;
    tmp = r0.i & 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    if (z)
    {
        goto L63;
    }
L65:
    counters[65] ++;
    Millerpart0();
    return;
L63:
    counters[66] ++;
    r0.i = 0;
    return;

}

void swap()
{
    counters[67] ++;
    ldr4000(&r3.i, &r0.i, ((uint32_t)r1.i << 2));
    ldr4000(&ip.i, &r0.i, ((uint32_t)r2.i << 2));
    str4000(&ip.i, &r0.i, ((uint32_t)r1.i << 2));
    str4000(&r3.i, &r0.i, ((uint32_t)r2.i << 2));
    return;

}

void heapify()
{
    counters[68] ++;
    push(2, &r4.i, &lr.i);
    goto L77;
L82:
    counters[69] ++;
    ldr4000(&lr.i, &r0.i, ((uint32_t)ip.i << 2));
    ldr4000(&r4.i, &r0.i, ((uint32_t)r2.i << 2));
    tmp = r4.i - lr.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) lr.i);
    v = (r4.i&0x80000000) != (lr.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (c)
    {
        goto L74;
    }
    counters[70] ++;
    tmp = r1.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r3.i);
    v = (r1.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!c || z)
    {
        r3.i = ip.i;
    }
    if (c && !z)
    {
        goto L81;
    }
L75:
    counters[71] ++;
    tmp = r3.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r2.i);
    v = (r3.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        pop(2, &pc.i, &r4.i);
        return;
    }
L83:
    counters[72] ++;
    ldr4000(&lr.i, &r0.i, ((uint32_t)r2.i << 2));
    ldr4000(&ip.i, &r0.i, ((uint32_t)r3.i << 2));
    str4000(&lr.i, &r0.i, ((uint32_t)r3.i << 2));
    str4000(&ip.i, &r0.i, ((uint32_t)r2.i << 2));
    r2.i = r3.i;
L77:
    counters[73] ++;
    r3.i = (uint32_t)r2.i << 1;
    ip.i = r3.i + (1);
    r3.i = r3.i + (2);
    tmp = ip.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r1.i);
    v = (ip.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (!c)
    {
        goto L82;
    }
L74:
    counters[74] ++;
    tmp = r1.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r3.i);
    v = (r1.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!c || z)
    {
        pop(2, &pc.i, &r4.i);
        return;
    }
    counters[75] ++;
    ldr4000(&lr.i, &r0.i, ((uint32_t)r2.i << 2));
    ldr4000(&ip.i, &r0.i, ((uint32_t)r3.i << 2));
    tmp = lr.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) ip.i);
    v = (lr.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    if (c)
    {
        pop(2, &pc.i, &r4.i);
        return;
    }
    counters[76] ++;
    tmp = r3.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r2.i);
    v = (r3.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L83;
    }
    counters[77] ++;
    pop(2, &pc.i, &r4.i);
    return;
L81:
    counters[78] ++;
    ldr4000(&r4.i, &r0.i, ((uint32_t)r3.i << 2));
    tmp = lr.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) r4.i);
    v = (lr.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    if (c)
    {
        r3.i = ip.i;
    }
    goto L75;
    return;
}

void heapSort()
{
    counters[79] ++;
    push(4, &r4.i, &r5.i, &r6.i, &lr.i);
    r4.i = (uint32_t)r1.i >> 1;
    tmp = r4.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 0);
    v = (r4.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (z)
    {
        goto L85;
    }
    counters[80] ++;
    r4.i = r4.i - (1);
L86:
    counters[81] ++;
    r2.i = r4.i;
    r4.i = r4.i - (1);
    heapify();
    counters[82] ++;
    tmp = r4.i + 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) tmp) < ((uint32_t) r4.i);
    v = (r4.i&0x80000000) == (1&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        goto L86;
    }
L85:
    counters[83] ++;
    r5.i = r1.i - (1);
    z = r5.i == 0;
    n = r5.i & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 1);
    v = (r1.i&0x80000000) != (1&0x80000000) && (r5.i&0x80000000) != (r1.i&0x80000000);
    if (z)
    {
        pop(4, &pc.i, &r6.i, &r5.i, &r4.i);
        return;
    }
    counters[84] ++;
    r4.i = r0.i + (((uint32_t)r1.i << 2));
    r6.i = r0.i + (4);
L88:
    counters[85] ++;
    ldr4100(&ip.i, &r4.i, -4);
    r1.i = r5.i;
    ldr4000(&r3.i, &r0.i, 0);
    r2.i = 0;
    r5.i = r5.i - (1);
    str4000(&ip.i, &r0.i, 0);
    str4000(&r3.i, &r4.i, 0);
    heapify();
    counters[86] ++;
    tmp = r6.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) r4.i);
    v = (r6.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    if (!z)
    {
        goto L88;
    }
    counters[87] ++;
    pop(4, &pc.i, &r6.i, &r5.i, &r4.i);
    return;

}

void test()
{
    counters[88] ++;
    push(6, &r4.i, &r5.i, &r6.i, &r7.i, &r8.i, &lr.i);
    r1.i = 10;
    r5.i = r0.i;
    heapSort();
    counters[89] ++;
    r8.i = (LC1 & 0xffff);
    r7.i = (LC2 & 0xffff);
    r8.i = r8.i | (((uint32_t)LC1 >> 16) << 16);
    r7.i = r7.i | (((uint32_t)LC2 >> 16) << 16);
    r4.i = 0;
    r6.i = r0.i - (4);
L99:
    counters[90] ++;
    r2.i = r4.i;
    r1.i = r8.i;
    r0.i = 1;
    r4.i = r4.i + (r0.i);
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[91] ++;
    ldr4100(&r2.i, &r6.i, 4);
    r1.i = r7.i;
    r0.i = 1;
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[92] ++;
    tmp = r4.i - 10;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 10);
    v = (r4.i&0x80000000) != (10&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        goto L99;
    }
    counters[93] ++;
    ldr4000(&r1.i, &r5.i, 0);
    r3.i = 0;
    lr.i = 43691;
    r4.i = 21845;
    lr.i = lr.i | (43690 << 16);
    r4.i = r4.i | (21845 << 16);
    r0.i = r3.i;
    r2.i = r5.i;
L100:
    counters[94] ++;
    tmp = r3.i & 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    r3.i = r3.i + (1);
    if (!z)
    {
        r0.i = r0.i - (r1.i);
    }
    if (z)
    {
        ldr4000(&r1.i, &r2.i, 0);
    }
    ip.i = (lr.i) * (r3.i);
    if (z)
    {
        r0.i = r0.i + (r1.i);
    }
    tmp = r3.i - 10;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 10);
    v = (r3.i&0x80000000) != (10&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        pop(6, &pc.i, &r8.i, &r7.i, &r6.i, &r5.i, &r4.i);
        return;
    }
    counters[95] ++;
    ldr4100(&r1.i, &r2.i, 4);
    tmp = ip.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r4.i);
    v = (ip.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (c && !z)
    {
        r0.i = (r1.i) * (r0.i);
    }
    goto L100;
    return;
}

void fib()
{
    counters[96] ++;
    tmp = r0.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 1);
    v = (r0.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (z || n != v)
    {
        return;
    }
    counters[97] ++;
    push(6, &r4.i, &r5.i, &r6.i, &r7.i, &r8.i, &lr.i);
    r7.i = r0.i - (2);
    r6.i = r0.i - (3);
    r3.i = r7.i & ~1;
    r5.i = r0.i - (1);
    r6.i = r6.i - (r3.i);
    r4.i = 0;
L110:
    counters[98] ++;
    r0.i = r5.i;
    r5.i = r5.i - (2);
    fib();
    counters[99] ++;
    tmp = r5.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r6.i);
    v = (r5.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    r4.i = r4.i + (r0.i);
    if (!z)
    {
        goto L110;
    }
    counters[100] ++;
    r0.i = r7.i & 1;
    r0.i = r0.i + (r4.i);
    pop(6, &pc.i, &r8.i, &r7.i, &r6.i, &r5.i, &r4.i);
    return;

}

void main()
{
    malloc_start();
    counters[101] ++;
    ip.i = (LC0 & 0xffff);
    ip.i = ip.i | (((uint32_t)LC0 >> 16) << 16);
    push(5, &r4.i, &r5.i, &r6.i, &r7.i, &lr.i);
    sp.i = sp.i - (44);
    ldm1(&ip.i, 4, &r0.i, &r1.i, &r2.i, &r3.i);
    lr.i = sp.i;
    stm1(&lr.i, 4, &r0.i, &r1.i, &r2.i, &r3.i);
    ldm1(&ip.i, 4, &r0.i, &r1.i, &r2.i, &r3.i);
    stm1(&lr.i, 4, &r0.i, &r1.i, &r2.i, &r3.i);
    ldm0(&ip.i, 2, &r0.i, &r1.i);
    stm0(&lr.i, 2, &r0.i, &r1.i);
    r0.i = sp.i;
    test();
    counters[102] ++;
    r1.i = (LC3 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC3 >> 16) << 16);
    r6.i = (r0.i) * (r0.i);
    r3.i = r0.i;
    r0.i = 1;
    r6.i = (r6.i) * (r3.i);
    r6.i = (r6.i) * (r6.i);
    r6.i = (r3.i) * (r6.i);
    r2.i = r6.i;
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[103] ++;
    tmp = r6.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) 0);
    v = (r6.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    if (z)
    {
        goto L118;
    }
    counters[104] ++;
    r1.i = 26215;
    r1.i = r1.i | (26214 << 16);
    r4.i = r6.i;
    r5.i = 0;
    r0.i = 10;
L119:
    counters[105] ++;
    smull(&r3.i, &r2.i, &r1.i, &r4.i);
    r3.i = r4.i >> 31;
    r3.i = (r2.i >> 2) - r3.i;
    r2.i = r4.i - ((r0.i) * (r3.i));
    r4.i = r3.i - (0);
    z = r4.i == 0;
    n = r4.i & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (r4.i&0x80000000) != (r3.i&0x80000000);
    r5.i = r5.i + (r2.i);
    if (!z)
    {
        goto L119;
    }
    counters[106] ++;
    r2.i = r5.i;
    r1.i = (LC4 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC4 >> 16) << 16);
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[107] ++;
    r1.i = (r5.i) * (r5.i);
    r0.i = r6.i;
    idiv();
    counters[108] ++;
    r1.i = (LC5 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC5 >> 16) << 16);
    r2.i = r0.i;
    r6.i = r0.i;
    r0.i = 1;
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[109] ++;
    tmp = r5.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) 1);
    v = (r5.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (z || n != v)
    {
        goto L141;
    }
    counters[110] ++;
    r7.i = r5.i - (2);
    r1.i = r5.i - (3);
    r3.i = r7.i & ~1;
    r2.i = r5.i - (1);
    r1.i = r1.i - (r3.i);
L123:
    counters[111] ++;
    r0.i = r2.i;
    r2.i = r2.i - (2);
    fib();
    counters[112] ++;
    tmp = r2.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r1.i);
    v = (r2.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    r4.i = r4.i + (r0.i);
    if (!z)
    {
        goto L123;
    }
    counters[113] ++;
    r0.i = r7.i & 1;
L124:
    counters[114] ++;
    r0.i = r4.i + (r0.i);
    r1.i = r5.i;
    idiv();
    counters[115] ++;
    r1.i = r0.i;
    r0.i = r6.i;
    idiv();
    counters[116] ++;
    tmp = r0.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 1);
    v = (r0.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    r4.i = r0.i;
    if (z || n != v)
    {
        goto L121;
    }
    counters[117] ++;
    tmp = r0.i - 2;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 2);
    v = (r0.i&0x80000000) != (2&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (z)
    {
        goto L125;
    }
    counters[118] ++;
    tmp = r0.i & 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    if (z)
    {
        goto L121;
    }
L125:
    counters[119] ++;
    r1.i = 10;
    r0.i = r4.i;
    Millerpart0();
    counters[120] ++;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        goto L142;
    }
L121:
    counters[121] ++;
    r1.i = (LC7 & 0xffff);
    r2.i = r4.i;
    r1.i = r1.i | (((uint32_t)LC7 >> 16) << 16);
    r0.i = 1;
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
L126:
    counters[122] ++;
    r2.i = r4.i;
    r1.i = (LC8 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC8 >> 16) << 16);
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[123] ++;
    r0.i = 0;
    sp.i = sp.i + (44);
    pop(5, &pc.i, &r7.i, &r6.i, &r5.i, &r4.i);
    counter_summary();
    return;
L142:
    counters[124] ++;
    r1.i = (LC6 & 0xffff);
    r2.i = r4.i;
    r1.i = r1.i | (((uint32_t)LC6 >> 16) << 16);
    r0.i = 1;
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[125] ++;
    goto L126;
L141:
    counters[126] ++;
    r0.i = r5.i;
    goto L124;
L118:
    counters[127] ++;
    r2.i = r6.i;
    r1.i = (LC4 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC4 >> 16) << 16);
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[128] ++;
    r1.i = r6.i;
    r0.i = r6.i;
    idiv();
    counters[129] ++;
    r1.i = (LC5 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC5 >> 16) << 16);
    r2.i = r0.i;
    r0.i = 1;
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[130] ++;
    return;
}

