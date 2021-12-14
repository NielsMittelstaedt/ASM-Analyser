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

reg r6, r5, r8, r2, r4, r3, r9, r0, r7, r1, r10;

int32_t LC0, LC1;

int counters[70] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[70] = {8,3,5,1,2,3,4,1,1,3,3,3,3,2,2,1,3,4,1,4,1,1,3,3,3,3,2,2,6,1,3,1,2,2,1,1,2,2,1,3,1,5,2,2,4,1,1,3,3,3,2,2,4,2,4,1,1,3,3,3,2,2,2,2,2,1,2,4,9,2};

void idivmod()
{
    int32_t quot = r0.i / r1.i;
    int32_t rem = r0.i % r1.i;
    r0.i = quot;
    r1.i = rem;
}
void str4000(int32_t *target, int32_t *address, int32_t offset)
{
    *((uint32_t*)(malloc_0+*address+offset)) = *target;
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
void ldr4000(int32_t *target, int32_t *address, int32_t offset)
{
    *target = *((uint32_t*)(malloc_0+*address+offset));
}
void rand_help()
{
    r0.i = rand();
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
    malloc_0 = (uint8_t*) malloc(20054);
    sp.i = 19996;
    fp = sp;
    LC0 = 20000;
    strcpy(malloc_0+LC0, "\012%d is prime\012\000");

    LC1 = 20025;
    strcpy(malloc_0+LC1, "\012%d is not prime\012\000");

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "miller_rabin.c";

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

void Millerpart0();
void mulmod();
void modulo();
void Miller();
void main();

void Millerpart0()
{
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
    r9.i = r9.i >> 1;
    tmp = r9.i & 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    if (z)
    {
        goto L3;
    }
L2:
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
    rand_help();
    r1.i = r8.i;
    idivmod();
    r6.i = r9.i;
    r5.i = 1;
    r4.i = r1.i + (1);
L7:
    tmp = r6.i & 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    r1.i = fp.i;
    r0.i = (r4.i) * (r5.i);
    if (z)
    {
        goto L6;
    }
    idivmod();
    r5.i = r1.i;
L6:
    r0.i = (r4.i) * (r4.i);
    r1.i = fp.i;
    idivmod();
    r6.i = r6.i >> 1;
    z = r6.i == 0;
    n = r6.i & 0x80000000;
    c = r6.i & (1 << 1 - 1);
    r4.i = r1.i;
    if (!z)
    {
        goto L7;
    }
    r0.i = r5.i;
    r1.i = fp.i;
    idivmod();
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
    tmp = r1.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 1);
    v = (r1.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (z)
    {
        goto L19;
    }
    tmp = r8.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) r1.i);
    v = (r8.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    if (z)
    {
        goto L9;
    }
    r7.i = r9.i;
L13:
    r1.i = fp.i;
    r0.i = r10.i;
    idivmod();
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
    r5.i = 0;
L12:
    tmp = r10.i & 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    r0.i = r5.i + (r4.i);
    r1.i = fp.i;
    if (z)
    {
        goto L11;
    }
    idivmod();
    r5.i = r1.i;
L11:
    r0.i = (uint32_t)r4.i << 1;
    r1.i = fp.i;
    idivmod();
    r10.i = r10.i >> 1;
    z = r10.i == 0;
    n = r10.i & 0x80000000;
    c = r10.i & (1 << 1 - 1);
    r4.i = r1.i;
    if (!z)
    {
        goto L12;
    }
    r0.i = r5.i;
    r1.i = fp.i;
    idivmod();
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
    tmp = r1.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 1);
    v = (r1.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (z)
    {
        goto L8;
    }
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
    r6.i = 1;
L1:
    r0.i = r6.i;
    sp.i = sp.i + (12);
    pop(9, &pc.i, &fp.i, &r10.i, &r9.i, &r8.i, &r7.i, &r6.i, &r5.i, &r4.i);
    return;
L41:
    r7.i = (uint32_t)r7.i << 1;
L10:
    tmp = r8.i - r7.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r8.i) >= ((uint32_t) r7.i);
    v = (r8.i&0x80000000) != (r7.i&0x80000000) && (tmp&0x80000000) != (r8.i&0x80000000);
    if (!z)
    {
        goto L41;
    }
    tmp = r7.i & 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    if (!z)
    {
        goto L9;
    }
    goto L1;
L19:
    r7.i = r9.i;
L8:
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
    tmp = r7.i & 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    if (!z)
    {
        goto L9;
    }
    goto L1;
L18:
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
    goto L9;
    return;
}

void mulmod()
{
    push(6, &r4.i, &r5.i, &r6.i, &r7.i, &r8.i, &lr.i);
    r5.i = r1.i;
    r1.i = r2.i;
    r7.i = r2.i;
    idivmod();
    tmp = r5.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) 0);
    v = (r5.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (z || n != v)
    {
        goto L47;
    }
    r4.i = r1.i;
    r6.i = 0;
L46:
    tmp = r5.i & 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    r0.i = r6.i + (r4.i);
    r1.i = r7.i;
    if (z)
    {
        goto L45;
    }
    idivmod();
    r6.i = r1.i;
L45:
    r0.i = (uint32_t)r4.i << 1;
    r1.i = r7.i;
    idivmod();
    r5.i = r5.i >> 1;
    z = r5.i == 0;
    n = r5.i & 0x80000000;
    c = r5.i & (1 << 1 - 1);
    r4.i = r1.i;
    if (!z)
    {
        goto L46;
    }
    r1.i = r7.i;
    r0.i = r6.i;
    idivmod();
    r0.i = r1.i;
    pop(6, &pc.i, &r8.i, &r7.i, &r6.i, &r5.i, &r4.i);
    return;
L47:
    r0.i = 0;
    pop(6, &pc.i, &r8.i, &r7.i, &r6.i, &r5.i, &r4.i);
    return;

}

void modulo()
{
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
    r4.i = r0.i;
    r6.i = 1;
L56:
    tmp = r5.i & 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    r1.i = r7.i;
    r0.i = (r4.i) * (r6.i);
    if (z)
    {
        goto L55;
    }
    idivmod();
    r6.i = r1.i;
L55:
    r0.i = (r4.i) * (r4.i);
    r1.i = r7.i;
    idivmod();
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
    r1.i = r7.i;
    r0.i = r6.i;
    idivmod();
    r0.i = r1.i;
    pop(6, &pc.i, &r8.i, &r7.i, &r6.i, &r5.i, &r4.i);
    return;
L57:
    r6.i = 1;
    goto L54;
    return;
}

void Miller()
{
    tmp = r0.i - 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 1);
    v = (r0.i&0x80000000) != (1&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (z || n != v)
    {
        goto L63;
    }
    tmp = r0.i - 2;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 2);
    v = (r0.i&0x80000000) != (2&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (z)
    {
        goto L65;
    }
    tmp = r0.i & 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    if (z)
    {
        goto L63;
    }
L65:
    Millerpart0();
    return;
L63:
    r0.i = 0;
    return;

}

void main()
{
    malloc_start();
    r1.i = 5;
    r0.i = 347;
    push(2, &r4.i, &lr.i);
    Millerpart0();
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    r0.i = 1;
    if (!z)
    {
        r1.i = (LC0 & 0xffff);
    }
    if (z)
    {
        r1.i = (LC1 & 0xffff);
    }
    if (!z)
    {
        r1.i = r1.i | (((uint32_t)LC0 >> 16) << 16);
    }
    if (z)
    {
        r1.i = r1.i | (((uint32_t)LC1 >> 16) << 16);
    }
    if (!z)
    {
        r2.i = 347;
    }
    if (z)
    {
        r2.i = 347;
    }
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    r0.i = 0;
    pop(2, &pc.i, &r4.i);
    counter_summary();
    return;

}

