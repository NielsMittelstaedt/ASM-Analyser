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

reg r5, r7, r1, r4, r8, r9, r2, r6, r10, r3, r0;

int32_t LC0, L49, q, tail, head, pred, color, flow, capacity, e, num;

int counters[39] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[39] = {3,14,14,13,3,26,6,10,3,9,3,1,3,14,8,8,1,3,3,3,8,6,4,11,1,13,1,2,2,3,3,8,6,1,3,3,56,5,2};

void str8000(int32_t *target1, int32_t *target2, int32_t *address, int32_t offset)
{
    *((uint32_t*)(malloc_0+*address+offset)) = *target1;
    *((uint32_t*)(malloc_0+*address+offset+4)) = *target2;
}
void str4100(int32_t *target, int32_t *address, int32_t offset)
{
    *((uint32_t*)(malloc_0+*address+offset)) = *target;
    *address += offset;
}
void ldr8000(int32_t *target1, int32_t *target2, int32_t *address, int32_t offset)
{
    *target1 = *((uint32_t*)(malloc_0+*address+offset));
    *target2 = *((uint32_t*)(malloc_0+*address+offset+4));
}
void str4010(int32_t *target, int32_t *address, int32_t offset)
{
    *((uint32_t*)(malloc_0+*address)) = *target;
    *address += offset;
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
void ldr4100(int32_t *target, int32_t *address, int32_t offset)
{
    *target = *((uint32_t*)(malloc_0+*address+offset));
    *address += offset;
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
void str4000(int32_t *target, int32_t *address, int32_t offset)
{
    *((uint32_t*)(malloc_0+*address+offset)) = *target;
}
void ldr4010(int32_t *target, int32_t *address, int32_t offset)
{
    *target = *((uint32_t*)(malloc_0+*address));
    *address += offset;
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
    malloc_0 = (uint8_t*) malloc(8032050);
    sp.i = 19996;
    fp = sp;
    LC0 = 20000;
    strcpy(malloc_0+LC0, "Max Flow: %d\012\000");

    L49 = 20022;
    int32_t arrayL49[] = {capacity};
    for(int i=0; i<1; i++) str4000(&arrayL49[i], &L49, i*4);

    q = 20026;
    tail = 24034;
    head = 24038;
    pred = 24042;
    color = 28042;
    flow = 32042;
    capacity = 4032042;
    e = 8032042;
    num = 8032046;
}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "ford_fulkerson.c";

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

void min();
void enqueue();
void dequeue();
void bfs();
void fordFulkerson();
void main();

void min()
{
    tmp = r1.i - r0.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) r0.i);
    v = (r1.i&0x80000000) != (r0.i&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (n != v)
    {
        r0.i = r1.i;
    }
    return;

}

void enqueue()
{
    r3.i = (tail & 0xffff);
    r3.i = r3.i | (((uint32_t)tail >> 16) << 16);
    r1.i = (q & 0xffff);
    r2.i = (color & 0xffff);
    ldr4000(&ip.i, &r3.i, 0);
    r1.i = r1.i | (((uint32_t)q >> 16) << 16);
    r2.i = r2.i | (((uint32_t)color >> 16) << 16);
    str4100(&lr.i, &sp.i, -4);
    lr.i = ip.i + (1);
    str4000(&r0.i, &r1.i, ((uint32_t)ip.i << 2));
    r1.i = 1;
    str4000(&lr.i, &r3.i, 0);
    str4000(&r1.i, &r2.i, ((uint32_t)r0.i << 2));
    ldr4010(&pc.i, &sp.i, 4);
    return;

}

void dequeue()
{
    r3.i = (head & 0xffff);
    r3.i = r3.i | (((uint32_t)head >> 16) << 16);
    r1.i = (q & 0xffff);
    r1.i = r1.i | (((uint32_t)q >> 16) << 16);
    ldr4000(&r0.i, &r3.i, 0);
    r2.i = (color & 0xffff);
    str4100(&lr.i, &sp.i, -4);
    lr.i = r0.i + (1);
    ldr4000(&r0.i, &r1.i, ((uint32_t)r0.i << 2));
    r2.i = r2.i | (((uint32_t)color >> 16) << 16);
    ip.i = 2;
    str4000(&lr.i, &r3.i, 0);
    str4000(&ip.i, &r2.i, ((uint32_t)r0.i << 2));
    ldr4010(&pc.i, &sp.i, 4);
    return;

}

void bfs()
{
    r3.i = (num & 0xffff);
    r3.i = r3.i | (((uint32_t)num >> 16) << 16);
    push(9, &r4.i, &r5.i, &r6.i, &r7.i, &r8.i, &r9.i, &r10.i, &fp.i, &lr.i);
    sp.i = sp.i - (28);
    ldr4000(&ip.i, &r3.i, 0);
    r3.i = (color & 0xffff);
    r3.i = r3.i | (((uint32_t)color >> 16) << 16);
    str4000(&r1.i, &sp.i, 16);
    tmp = ip.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) 0);
    v = (ip.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    str4000(&r3.i, &sp.i, 4);
    if (!z && n == v)
    {
        r1.i = r3.i + (((uint32_t)ip.i << 2));
    }
    if (!z && n == v)
    {
        r2.i = 0;
    }
    if (z || n != v)
    {
        goto L11;
    }
L10:
    str4010(&r2.i, &r3.i, 4);
    tmp = r3.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r1.i);
    v = (r3.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L10;
    }
L11:
    r3.i = (q & 0xffff);
    r3.i = r3.i | (((uint32_t)q >> 16) << 16);
    r1.i = (tail & 0xffff);
    r8.i = (pred & 0xffff);
    r10.i = r3.i;
    r4.i = r3.i;
    str4000(&r0.i, &r3.i, 0);
    r1.i = r1.i | (((uint32_t)tail >> 16) << 16);
    ldr4000(&r3.i, &sp.i, 4);
    r8.i = r8.i | (((uint32_t)pred >> 16) << 16);
    r9.i = 0;
    r2.i = 1;
    r7.i = r9.i;
    lr.i = r2.i;
    str4000(&r2.i, &r3.i, ((uint32_t)r0.i << 2));
    fp.i = r2.i;
    r3.i = ~0;
    str4000(&r2.i, &r1.i, 0);
    str4000(&r3.i, &r8.i, ((uint32_t)r0.i << 2));
    r2.i = (flow & 0xffff);
    r3.i = (capacity & 0xffff);
    r2.i = r2.i | (((uint32_t)flow >> 16) << 16);
    r3.i = r3.i | (((uint32_t)capacity >> 16) << 16);
    str4000(&r1.i, &sp.i, 20);
    str4000(&r3.i, &sp.i, 8);
    str4000(&r2.i, &sp.i, 12);
L9:
    ldr4000(&r3.i, &sp.i, 4);
    tmp = ip.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) 0);
    v = (ip.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    r2.i = 2;
    r7.i = r7.i + (1);
    str4000(&r2.i, &r3.i, ((uint32_t)r0.i << 2));
    if (z || n != v)
    {
        goto L12;
    }
    r3.i = 4000;
    ldr4000(&r1.i, &sp.i, 8);
    r5.i = (r3.i) * (r0.i);
    r2.i = (color & 0xffff);
    r2.i = r2.i | (((uint32_t)color >> 16) << 16);
    r3.i = 0;
    str4000(&r4.i, &sp.i, 0);
    r6.i = r5.i + (r1.i);
    ldr4000(&r1.i, &sp.i, 12);
    r5.i = r5.i + (r1.i);
L14:
    ldr4010(&r1.i, &r2.i, 4);
    tmp = r1.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 0);
    v = (r1.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!z)
    {
        goto L13;
    }
    ldr4000(&r1.i, &r6.i, ((uint32_t)r3.i << 2));
    ldr4000(&r4.i, &r5.i, ((uint32_t)r3.i << 2));
    r1.i = r1.i - (r4.i);
    tmp = r1.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 0);
    v = (r1.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!z && n == v)
    {
        str4000(&r3.i, &r10.i, ((uint32_t)lr.i << 2));
    }
    if (!z && n == v)
    {
        lr.i = lr.i + (1);
    }
    if (!z && n == v)
    {
        str4000(&fp.i, &r2.i, -4);
    }
    if (!z && n == v)
    {
        r9.i = 1;
    }
    if (!z && n == v)
    {
        str4000(&r0.i, &r8.i, ((uint32_t)r3.i << 2));
    }
L13:
    r3.i = r3.i + (1);
    tmp = r3.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) ip.i);
    v = (r3.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L14;
    }
    ldr4000(&r4.i, &sp.i, 0);
L12:
    tmp = r7.i - lr.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r7.i) >= ((uint32_t) lr.i);
    v = (r7.i&0x80000000) != (lr.i&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
    if (!z)
    {
        ldr4100(&r0.i, &r4.i, 4);
    }
    if (!z)
    {
        goto L9;
    }
L15:
    tmp = r9.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r9.i) >= ((uint32_t) 0);
    v = (r9.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r9.i&0x80000000);
    r3.i = (head & 0xffff);
    r3.i = r3.i | (((uint32_t)head >> 16) << 16);
    ldr4000(&r2.i, &sp.i, 16);
    str4000(&r7.i, &r3.i, 0);
    if (!z)
    {
        ldr4000(&r3.i, &sp.i, 20);
    }
    if (!z)
    {
        str4000(&r7.i, &r3.i, 0);
    }
    ldr4000(&r3.i, &sp.i, 4);
    ldr4000(&r0.i, &r3.i, ((uint32_t)r2.i << 2));
    r0.i = r0.i - (2);
    clz(&r0.i, &r0.i);
    r0.i = (uint32_t)r0.i >> 5;
    sp.i = sp.i + (28);
    pop(9, &pc.i, &fp.i, &r10.i, &r9.i, &r8.i, &r7.i, &r6.i, &r5.i, &r4.i);
    return;

}

void fordFulkerson()
{
    push(9, &r4.i, &r5.i, &r6.i, &r7.i, &r8.i, &r9.i, &r10.i, &fp.i, &lr.i);
    r8.i = (num & 0xffff);
    r8.i = r8.i | (((uint32_t)num >> 16) << 16);
    sp.i = sp.i - (12);
    ldr4000(&r3.i, &r8.i, 0);
    str8000(&r0.i, &r1.i, &sp.i, 0);
    tmp = r3.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) 0);
    v = (r3.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (z || n != v)
    {
        goto L24;
    }
    r2.i = (flow & 0xffff);
    r2.i = r2.i | (((uint32_t)flow >> 16) << 16);
    ip.i = (uint32_t)r3.i << 2;
    r0.i = 4004;
    r0.i = ((r0.i) * (r3.i)) + (r2.i);
    r2.i = r2.i + (ip.i);
    ip.i = 0 - ip.i;
    r1.i = 0;
L26:
    r3.i = r2.i + (ip.i);
L25:
    str4010(&r1.i, &r3.i, 4);
    tmp = r3.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r2.i);
    v = (r3.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L25;
    }
    r2.i = r2.i + (4000);
    tmp = r2.i - r0.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) r0.i);
    v = (r2.i&0x80000000) != (r0.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z)
    {
        goto L26;
    }
L24:
    ldr8000(&r0.i, &r1.i, &sp.i, 0);
    r5.i = (pred & 0xffff);
    bfs();
    r4.i = (flow & 0xffff);
    r6.i = (capacity & 0xffff);
    r5.i = r5.i | (((uint32_t)pred >> 16) << 16);
    r4.i = r4.i | (((uint32_t)flow >> 16) << 16);
    r6.i = r6.i | (((uint32_t)capacity >> 16) << 16);
    r7.i = 0;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (z)
    {
        goto L38;
    }
L31:
    ldr4000(&ip.i, &r8.i, 0);
    r3.i = 51712;
    ip.i = ip.i - (1);
    ldr4000(&r2.i, &r5.i, ((uint32_t)ip.i << 2));
    tmp = r2.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) 0);
    v = (r2.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (n != v)
    {
        goto L32;
    }
    r3.i = r3.i | (15258 << 16);
    r10.i = ip.i;
    r0.i = r2.i;
    fp.i = 1000;
L29:
    r9.i = ((fp.i) * (r0.i)) + (r10.i);
    ldr4000(&lr.i, &r5.i, ((uint32_t)r0.i << 2));
    r10.i = r0.i;
    r0.i = lr.i;
    ldr4000(&r1.i, &r6.i, ((uint32_t)r9.i << 2));
    ldr4000(&r9.i, &r4.i, ((uint32_t)r9.i << 2));
    r1.i = r1.i - (r9.i);
    tmp = r3.i - r1.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r1.i);
    v = (r3.i&0x80000000) != (r1.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (n == v)
    {
        r3.i = r1.i;
    }
    tmp = lr.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) lr.i) >= ((uint32_t) 0);
    v = (lr.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (lr.i&0x80000000);
    if (n == v)
    {
        goto L29;
    }
    lr.i = 1000;
L30:
    r9.i = ((lr.i) * (r2.i)) + (ip.i);
    ldr4000(&r1.i, &r5.i, ((uint32_t)r2.i << 2));
    r0.i = ((lr.i) * (ip.i)) + (r2.i);
    tmp = r1.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 0);
    v = (r1.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    ip.i = r2.i;
    r2.i = r1.i;
    ldr4000(&r1.i, &r4.i, ((uint32_t)r9.i << 2));
    r1.i = r1.i + (r3.i);
    str4000(&r1.i, &r4.i, ((uint32_t)r9.i << 2));
    ldr4000(&r1.i, &r4.i, ((uint32_t)r0.i << 2));
    r1.i = r1.i - (r3.i);
    str4000(&r1.i, &r4.i, ((uint32_t)r0.i << 2));
    if (n == v)
    {
        goto L30;
    }
    r7.i = r7.i + (r3.i);
L39:
    ldr8000(&r0.i, &r1.i, &sp.i, 0);
    bfs();
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        goto L31;
    }
L38:
    r0.i = r7.i;
    sp.i = sp.i + (12);
    pop(9, &pc.i, &fp.i, &r10.i, &r9.i, &r8.i, &r7.i, &r6.i, &r5.i, &r4.i);
    return;
L32:
    r3.i = r3.i | (15258 << 16);
    r7.i = r7.i + (r3.i);
    goto L39;
    return;
}

void main()
{
    malloc_start();
    push(4, &r4.i, &r5.i, &r6.i, &lr.i);
    r5.i = (num & 0xffff);
    r5.i = r5.i | (((uint32_t)num >> 16) << 16);
    r0.i = (capacity & 0xffff);
    r0.i = r0.i | (((uint32_t)capacity >> 16) << 16);
    ldr4000(&ip.i, &r5.i, 0);
    tmp = ip.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) ip.i) >= ((uint32_t) 0);
    v = (ip.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (ip.i&0x80000000);
    if (z || n != v)
    {
        goto L41;
    }
    r3.i = 4004;
    lr.i = (uint32_t)ip.i << 2;
    ip.i = ((r3.i) * (ip.i)) + (r0.i);
    r2.i = r0.i + (lr.i);
    lr.i = 0 - lr.i;
    r1.i = 0;
L43:
    r3.i = r2.i + (lr.i);
L42:
    str4010(&r1.i, &r3.i, 4);
    tmp = r3.i - r2.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r2.i);
    v = (r3.i&0x80000000) != (r2.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L42;
    }
    r2.i = r2.i + (4000);
    tmp = r2.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r2.i) >= ((uint32_t) ip.i);
    v = (r2.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r2.i&0x80000000);
    if (!z)
    {
        goto L43;
    }
L41:
    ldr4000(&r3.i, &L49, 0);
    r4.i = 1;
    str4000(&r4.i, &r0.i, 4);
    r2.i = (e & 0xffff);
    r1.i = r3.i + (4096);
    ip.i = r3.i + (20480);
    str4000(&r4.i, &r0.i, 8);
    lr.i = r3.i + (24576);
    str4000(&r4.i, &r1.i, 3840);
    r2.i = r2.i | (((uint32_t)e >> 16) << 16);
    str4000(&r4.i, &r1.i, 3848);
    str4000(&r4.i, &r1.i, 3856);
    r1.i = r3.i + (28672);
    str4000(&r4.i, &r0.i, 12);
    str4000(&r4.i, &r0.i, 16);
    str4000(&r4.i, &r0.i, 20);
    str4000(&r4.i, &r0.i, 24);
    str4000(&r4.i, &r0.i, 28);
    str4000(&r4.i, &r0.i, 4036);
    str4000(&r4.i, &r0.i, 4052);
    r0.i = r3.i + (32768);
    str4000(&r4.i, &ip.i, 3476);
    ip.i = r3.i + (36864);
    str4000(&r4.i, &r1.i, 3292);
    r1.i = r3.i + (8192);
    str4000(&r4.i, &r0.i, 3196);
    r0.i = r3.i + (12288);
    str4000(&r4.i, &r3.i, 3940);
    str4000(&r4.i, &r3.i, 3948);
    str4000(&r4.i, &lr.i, 3388);
    lr.i = r3.i + (40960);
    str4000(&r4.i, &ip.i, 3100);
    ip.i = 33;
    str4000(&ip.i, &r2.i, 0);
    r2.i = r3.i + (16384);
    ip.i = r3.i + (45056);
    r3.i = r3.i + (49152);
    str4000(&r4.i, &r1.i, 3744);
    str4000(&r4.i, &r1.i, 3752);
    str4000(&r4.i, &r1.i, 3760);
    r1.i = 15;
    str4000(&r4.i, &r0.i, 3652);
    str4000(&r4.i, &r0.i, 3660);
    str4000(&r4.i, &r0.i, 3668);
    r0.i = 0;
    str4000(&r4.i, &r2.i, 3560);
    str4000(&r4.i, &r2.i, 3564);
    str4000(&r4.i, &r2.i, 3568);
    str4000(&r4.i, &r2.i, 3572);
    str4000(&r4.i, &r2.i, 3576);
    r2.i = 16;
    str4000(&r2.i, &r5.i, 0);
    str4000(&r4.i, &lr.i, 3004);
    str4000(&r4.i, &ip.i, 2908);
    str4000(&r4.i, &r3.i, 2812);
    fordFulkerson();
    r1.i = (LC0 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC0 >> 16) << 16);
    r2.i = r0.i;
    r0.i = r4.i;
    printf_help(malloc_0+r1.i, r2.i, r3.i, r4.i);
    r0.i = 0;
    pop(4, &pc.i, &r6.i, &r5.i, &r4.i);
    return;

}

