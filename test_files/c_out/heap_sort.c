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

reg r4, r1, r0, r5, r3, r2, r6;

int32_t LC1, LC0;

int load_counter = 0, store_counter = 0;
int counters[24] = { 0 };
int block_sizes[24] = {5,2,4,2,2,2,5,6,8,1,3,1,4,1,3,2,4,8,2,1,18,4,2,3};

void str4000(int32_t *target, int32_t *address, int32_t offset)
{
    *((uint32_t*)(malloc_0+*address+offset)) = *target;
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
    }
    va_end(args);
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
    }
    va_end(args);
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
void ldr4000(int32_t *target, int32_t *address, int32_t offset)
{
    *target = *((uint32_t*)(malloc_0+*address+offset));
    load_counter ++;
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
void ldr4100(int32_t *target, int32_t *address, int32_t offset)
{
    *target = *((uint32_t*)(malloc_0+*address+offset));
    *address += offset;
    load_counter ++;
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
void ldr4010(int32_t *target, int32_t *address, int32_t offset)
{
    *target = *((uint32_t*)(malloc_0+*address));
    *address += offset;
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
    malloc_0 = (uint8_t*) malloc(20049);
    sp.i = 19996;
    fp = sp;
    LC1 = 20000;
    strcpy(malloc_0+LC1, "%d \000");

    LC0 = 20009;
    int32_t arrayLC0[] = {1,34,6,2,6,2,7,2,17,7};
    for(int i=0; i<10; i++) *((uint32_t*)(malloc_0+LC0+i*4)) = arrayLC0[i];

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "heap_sort.c";

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

void swap();
void heapify();
void heapSort();
void main();

void swap()
{
    counters[0] ++;
    ldr4000(&r3.i, &r0.i, ((uint32_t)r1.i << 2));
    ldr4000(&ip.i, &r0.i, ((uint32_t)r2.i << 2));
    str4000(&ip.i, &r0.i, ((uint32_t)r1.i << 2));
    str4000(&r3.i, &r0.i, ((uint32_t)r2.i << 2));
    return;

}

void heapify()
{
    counters[1] ++;
    push(3, &r4.i, &r5.i, &lr.i);
    goto L7;
L12:
    counters[2] ++;
    ldr4000(&r4.i, &r0.i, ((uint32_t)lr.i << 2));
    ldr4000(&r5.i, &r0.i, ((uint32_t)r2.i << 2));
    tmp = r5.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r4.i);
    v = (r5.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (c)
    {
        goto L4;
    }
    counters[3] ++;
    tmp = r1.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r3.i);
    v = (r1.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (c && !z)
    {
        goto L11;
    }
L9:
    counters[4] ++;
    ip.i = lr.i;
    r3.i = lr.i;
L5:
    counters[5] ++;
    tmp = r3.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r2.i);
    v = (r3.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z)
    {
        pop(3, &pc.i, &r5.i, &r4.i);
        return;
    }
L13:
    counters[6] ++;
    ldr4000(&r4.i, &r0.i, ((uint32_t)r2.i << 2));
    ldr4000(&lr.i, &r0.i, ((uint32_t)ip.i << 2));
    str4000(&r4.i, &r0.i, ((uint32_t)ip.i << 2));
    str4000(&lr.i, &r0.i, ((uint32_t)r2.i << 2));
    r2.i = r3.i;
L7:
    counters[7] ++;
    r3.i = (uint32_t)r2.i << 1;
    lr.i = r3.i + (1);
    r3.i = r3.i + (2);
    tmp = lr.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) r1.i);
    v = (lr.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    ip.i = r3.i;
    if (!c)
    {
        goto L12;
    }
L4:
    counters[8] ++;
    tmp = r1.i - r3.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r3.i);
    v = (r1.i&0x80000000) != (r3.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!c || z)
    {
        pop(3, &pc.i, &r5.i, &r4.i);
        return;
    }
    ldr4000(&r4.i, &r0.i, ((uint32_t)r2.i << 2));
    ldr4000(&lr.i, &r0.i, ((uint32_t)r3.i << 2));
    tmp = r4.i - lr.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) lr.i);
    v = (r4.i&0x80000000) != (lr.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (c)
    {
        pop(3, &pc.i, &r5.i, &r4.i);
        return;
    }
    tmp = r3.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r2.i);
    v = (r3.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L13;
    }
    counters[9] ++;
    pop(3, &pc.i, &r5.i, &r4.i);
    return;
L11:
    counters[10] ++;
    ldr4000(&r5.i, &r0.i, ((uint32_t)r3.i << 2));
    tmp = r4.i - r5.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r5.i);
    v = (r4.i&0x80000000) != (r5.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (c)
    {
        goto L9;
    }
    counters[11] ++;
    goto L5;
    return;
}

void heapSort()
{
    counters[12] ++;
    push(4, &r4.i, &r5.i, &r6.i, &lr.i);
    r4.i = (uint32_t)r1.i >> 1;
    tmp = r4.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 0);
    v = (r4.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (z)
    {
        goto L15;
    }
    counters[13] ++;
    r4.i = r4.i - (1);
L16:
    counters[14] ++;
    r2.i = r4.i;
    r4.i = r4.i - (1);
    heapify();
    counters[15] ++;
    tmp = r4.i + 1;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) tmp) < ((uint32_t) r4.i);
    v = (r4.i&0x80000000) == (1&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        goto L16;
    }
L15:
    counters[16] ++;
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
    r4.i = r0.i + (((uint32_t)r1.i << 2));
    r6.i = r0.i + (4);
L18:
    counters[17] ++;
    ldr4100(&ip.i, &r4.i, -4);
    r1.i = r5.i;
    ldr4000(&r3.i, &r0.i, 0);
    r2.i = 0;
    r5.i = r5.i - (1);
    str4000(&ip.i, &r0.i, 0);
    str4000(&r3.i, &r4.i, 0);
    heapify();
    counters[18] ++;
    tmp = r6.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) r4.i);
    v = (r6.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    if (!z)
    {
        goto L18;
    }
    counters[19] ++;
    pop(4, &pc.i, &r6.i, &r5.i, &r4.i);
    return;

}

void main()
{
    malloc_start();
    counters[20] ++;
    ip.i = (LC0 & 0xffff);
    ip.i = ip.i | (((uint32_t)LC0 >> 16) << 16);
    push(4, &r4.i, &r5.i, &r6.i, &lr.i);
    sp.i = sp.i - (40);
    ldm1(&ip.i, 4, &r0.i, &r1.i, &r2.i, &r3.i);
    lr.i = sp.i;
    r5.i = (LC1 & 0xffff);
    r6.i = sp.i + (40);
    r5.i = r5.i | (((uint32_t)LC1 >> 16) << 16);
    r4.i = sp.i;
    stm1(&lr.i, 4, &r0.i, &r1.i, &r2.i, &r3.i);
    ldm1(&ip.i, 4, &r0.i, &r1.i, &r2.i, &r3.i);
    stm1(&lr.i, 4, &r0.i, &r1.i, &r2.i, &r3.i);
    ldm0(&ip.i, 2, &r0.i, &r1.i);
    stm0(&lr.i, 2, &r0.i, &r1.i);
    r0.i = sp.i;
    r1.i = 10;
    heapSort();
L29:
    counters[21] ++;
    ldr4010(&r2.i, &r4.i, 4);
    r1.i = r5.i;
    r0.i = 1;
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    counters[22] ++;
    tmp = r4.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r6.i);
    v = (r4.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        goto L29;
    }
    counters[23] ++;
    r0.i = 0;
    sp.i = sp.i + (40);
    pop(4, &pc.i, &r6.i, &r5.i, &r4.i);
    counter_summary();
    return;

}

