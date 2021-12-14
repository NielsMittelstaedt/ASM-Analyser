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

reg r3, r2, r5, r1, r0, r4;

int32_t LC1, LC0;

int load_counter = 0, store_counter = 0;
int counters[16] = { 0 };
int block_sizes[16] = {4,5,1,3,2,3,1,11,7,1,3,1,4,3,3,1};

void ldr4010(int32_t *target, int32_t *address, int32_t offset)
{
    *target = *((uint32_t*)(malloc_0+*address));
    *address += offset;
    load_counter ++;
}
void str4100(int32_t *target, int32_t *address, int32_t offset)
{
    *((uint32_t*)(malloc_0+*address+offset)) = *target;
    *address += offset;
    store_counter ++;
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
void str4000(int32_t *target, int32_t *address, int32_t offset)
{
    *((uint32_t*)(malloc_0+*address+offset)) = *target;
    store_counter ++;
}
void ldr4000(int32_t *target, int32_t *address, int32_t offset)
{
    *target = *((uint32_t*)(malloc_0+*address+offset));
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
    malloc_0 = (uint8_t*) malloc(20042);
    sp.i = 19996;
    fp = sp;
    LC1 = 20000;
    strcpy(malloc_0+LC1, "Ergebnis: %d\012\000");

    LC0 = 20022;
    int32_t arrayLC0[] = {2,3,4,10,40};
    for(int i=0; i<5; i++) *((uint32_t*)(malloc_0+LC0+i*4)) = arrayLC0[i];

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

void binarySearch();
void main();

void binarySearch()
{
    counters[0] ++;
    tmp = r1.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r2.i);
    v = (r1.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    str4100(&lr.i, &sp.i, -4);
    lr.i = r0.i;
    if (!z && n == v)
    {
        goto L8;
    }
L2:
    counters[1] ++;
    r0.i = r2.i - (r1.i);
    r0.i = r1.i + ((r0.i >> 1));
    ldr4000(&ip.i, &lr.i, ((uint32_t)r0.i << 2));
    tmp = ip.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) r3.i);
    v = (ip.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (z)
    {
        ldr4010(&pc.i, &sp.i, 4);
        return;
    }
    counters[2] ++;
    if (z || n != v)
    {
        goto L4;
    }
    counters[3] ++;
    r2.i = r0.i - (1);
    tmp = r2.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r1.i);
    v = (r2.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n == v)
    {
        goto L2;
    }
L8:
    counters[4] ++;
    r0.i = ~0;
    ldr4010(&pc.i, &sp.i, 4);
    return;
L4:
    counters[5] ++;
    r1.i = r0.i + (1);
    tmp = r1.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r2.i);
    v = (r1.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (z || n != v)
    {
        goto L2;
    }
    counters[6] ++;
    goto L8;
    return;
}

void main()
{
    malloc_start();
    counters[7] ++;
    push(3, &r4.i, &r5.i, &lr.i);
    r4.i = (LC0 & 0xffff);
    r4.i = r4.i | (((uint32_t)LC0 >> 16) << 16);
    sp.i = sp.i - (28);
    r5.i = sp.i + (4);
    ip.i = 0;
    ldm1(&r4.i, 4, &r0.i, &r1.i, &r2.i, &r3.i);
    lr.i = 4;
    ldr4000(&r4.i, &r4.i, 0);
    stm1(&r5.i, 4, &r0.i, &r1.i, &r2.i, &r3.i);
    str4000(&r4.i, &r5.i, 0);
L11:
    counters[8] ++;
    r2.i = lr.i - (ip.i);
    r3.i = sp.i + (24);
    r2.i = ip.i + ((r2.i >> 1));
    r3.i = r3.i + (((uint32_t)r2.i << 2));
    ldr4000(&r3.i, &r3.i, -20);
    tmp = r3.i - 40;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 40);
    v = (r3.i&0x80000000) != (40&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        goto L12;
    }
    counters[9] ++;
    if (z || n != v)
    {
        goto L13;
    }
    counters[10] ++;
    lr.i = r2.i - (1);
    tmp = lr.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) ip.i);
    v = (lr.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    if (n == v)
    {
        goto L11;
    }
L19:
    counters[11] ++;
    r2.i = ~0;
L12:
    counters[12] ++;
    r1.i = (LC1 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC1 >> 16) << 16);
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[13] ++;
    r0.i = 0;
    sp.i = sp.i + (28);
    pop(3, &pc.i, &r5.i, &r4.i);
    counter_summary();
    return;
L13:
    counters[14] ++;
    ip.i = r2.i + (1);
    tmp = ip.i - lr.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) lr.i);
    v = (ip.i&0x80000000) != (lr.i&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (z || n != v)
    {
        goto L11;
    }
    counters[15] ++;
    goto L19;
    return;
}

