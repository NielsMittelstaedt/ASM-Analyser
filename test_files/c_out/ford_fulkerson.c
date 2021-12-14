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

reg r1, r2, r9, r4, r6, r0, r10, r7, r8, r5, r3;

int32_t LC0, q, tail, head, pred, color, flow, capacity, e, num;

int counters[37] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[37] = {3,14,14,9,5,28,7,10,3,9,3,1,2,14,8,5,5,2,3,8,6,4,11,1,13,1,2,2,3,3,8,4,5,2,43,5,2};

void str4100(int32_t *target, int32_t *address, int32_t offset)
{
    *((uint32_t*)(malloc_0+*address+offset)) = *target;
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
void ldr8000(int32_t *target1, int32_t *target2, int32_t *address, int32_t offset)
{
    *target1 = *((uint32_t*)(malloc_0+*address+offset));
    *target2 = *((uint32_t*)(malloc_0+*address+offset+4));
}
void memset_help()
{
    memset(malloc_0+r0.i, r1.i, r2.i);
}
void ldr4010(int32_t *target, int32_t *address, int32_t offset)
{
    *target = *((uint32_t*)(malloc_0+*address));
    *address += offset;
}
void str8000(int32_t *target1, int32_t *target2, int32_t *address, int32_t offset)
{
    *((uint32_t*)(malloc_0+*address+offset)) = *target1;
    *((uint32_t*)(malloc_0+*address+offset+4)) = *target2;
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
    malloc_0 = (uint8_t*) malloc(40646);
    sp.i = 19996;
    fp = sp;
    LC0 = 20000;
    strcpy(malloc_0+LC0, "Max Flow: %d\012\000");

    q = 20022;
    tail = 20230;
    head = 20234;
    pred = 20238;
    color = 20438;
    flow = 20638;
    capacity = 30638;
    e = 40638;
    num = 40642;
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
    ldr4000(&r4.i, &r3.i, 0);
    r5.i = r0.i;
    str4000(&r1.i, &sp.i, 16);
    tmp = r4.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 0);
    v = (r4.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (z || n != v)
    {
        goto L10;
    }
    r0.i = (color & 0xffff);
    r2.i = (uint32_t)r4.i << 2;
    r0.i = r0.i | (((uint32_t)color >> 16) << 16);
    r1.i = 0;
    memset_help();
L10:
    r3.i = (q & 0xffff);
    r1.i = (tail & 0xffff);
    r3.i = r3.i | (((uint32_t)q >> 16) << 16);
    r1.i = r1.i | (((uint32_t)tail >> 16) << 16);
    lr.i = (color & 0xffff);
    r8.i = (pred & 0xffff);
    lr.i = lr.i | (((uint32_t)color >> 16) << 16);
    r8.i = r8.i | (((uint32_t)pred >> 16) << 16);
    r9.i = 0;
    r2.i = 1;
    r7.i = r9.i;
    r10.i = r3.i;
    ip.i = r2.i;
    r0.i = r3.i;
    fp.i = r2.i;
    str4000(&r5.i, &r3.i, 0);
    str4000(&r2.i, &r1.i, 0);
    r3.i = ~0;
    str4000(&r2.i, &lr.i, ((uint32_t)r5.i << 2));
    r2.i = (flow & 0xffff);
    str4000(&r3.i, &r8.i, ((uint32_t)r5.i << 2));
    r2.i = r2.i | (((uint32_t)flow >> 16) << 16);
    r3.i = (capacity & 0xffff);
    str4000(&r1.i, &sp.i, 20);
    r3.i = r3.i | (((uint32_t)capacity >> 16) << 16);
    str4000(&lr.i, &sp.i, 4);
    str4000(&r3.i, &sp.i, 8);
    str4000(&r2.i, &sp.i, 12);
L9:
    ldr4010(&r5.i, &r0.i, 4);
    tmp = r4.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) 0);
    v = (r4.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    ldr4000(&r3.i, &sp.i, 4);
    r2.i = 2;
    r7.i = r7.i + (1);
    str4000(&r2.i, &r3.i, ((uint32_t)r5.i << 2));
    if (z || n != v)
    {
        goto L11;
    }
    r3.i = 200;
    ldr4000(&r1.i, &sp.i, 8);
    lr.i = (r3.i) * (r5.i);
    r2.i = (color & 0xffff);
    r2.i = r2.i | (((uint32_t)color >> 16) << 16);
    r3.i = 0;
    str4000(&r0.i, &sp.i, 0);
    r6.i = lr.i + (r1.i);
    ldr4000(&r1.i, &sp.i, 12);
    lr.i = lr.i + (r1.i);
L13:
    ldr4010(&r1.i, &r2.i, 4);
    tmp = r1.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 0);
    v = (r1.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!z)
    {
        goto L12;
    }
    ldr4000(&r1.i, &r6.i, ((uint32_t)r3.i << 2));
    ldr4000(&r0.i, &lr.i, ((uint32_t)r3.i << 2));
    r1.i = r1.i - (r0.i);
    tmp = r1.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r1.i) >= ((uint32_t) 0);
    v = (r1.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r1.i&0x80000000);
    if (!z && n == v)
    {
        str4000(&r3.i, &r10.i, ((uint32_t)ip.i << 2));
    }
    if (!z && n == v)
    {
        ip.i = ip.i + (1);
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
        str4000(&r5.i, &r8.i, ((uint32_t)r3.i << 2));
    }
L12:
    r3.i = r3.i + (1);
    tmp = r3.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r3.i) >= ((uint32_t) r4.i);
    v = (r3.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r3.i&0x80000000);
    if (!z)
    {
        goto L13;
    }
    ldr4000(&r0.i, &sp.i, 0);
L11:
    tmp = r7.i - ip.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r7.i) >= ((uint32_t) ip.i);
    v = (r7.i&0x80000000) != (ip.i&0x80000000) && (tmp&0x80000000) != (r7.i&0x80000000);
    if (!z)
    {
        goto L9;
    }
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
    r6.i = (num & 0xffff);
    r6.i = r6.i | (((uint32_t)num >> 16) << 16);
    sp.i = sp.i - (12);
    ldr4000(&r5.i, &r6.i, 0);
    str8000(&r0.i, &r1.i, &sp.i, 0);
    tmp = r5.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) 0);
    v = (r5.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (z || n != v)
    {
        goto L22;
    }
    r4.i = (flow & 0xffff);
    r4.i = r4.i | (((uint32_t)flow >> 16) << 16);
    r3.i = 200;
    r7.i = (uint32_t)r5.i << 2;
    r5.i = ((r3.i) * (r5.i)) + (r4.i);
L23:
    r0.i = r4.i;
    r2.i = r7.i;
    r4.i = r4.i + (200);
    r1.i = 0;
    memset_help();
    tmp = r5.i - r4.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r4.i);
    v = (r5.i&0x80000000) != (r4.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (!z)
    {
        goto L23;
    }
L22:
    ldr8000(&r0.i, &r1.i, &sp.i, 0);
    r5.i = (pred & 0xffff);
    bfs();
    r4.i = (flow & 0xffff);
    r7.i = (capacity & 0xffff);
    r5.i = r5.i | (((uint32_t)pred >> 16) << 16);
    r4.i = r4.i | (((uint32_t)flow >> 16) << 16);
    r7.i = r7.i | (((uint32_t)capacity >> 16) << 16);
    r8.i = 0;
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (z)
    {
        goto L34;
    }
L28:
    ldr4000(&ip.i, &r6.i, 0);
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
        goto L29;
    }
    r3.i = r3.i | (15258 << 16);
    r10.i = ip.i;
    r0.i = r2.i;
    fp.i = 50;
L26:
    r9.i = ((fp.i) * (r0.i)) + (r10.i);
    ldr4000(&lr.i, &r5.i, ((uint32_t)r0.i << 2));
    r10.i = r0.i;
    r0.i = lr.i;
    ldr4000(&r1.i, &r7.i, ((uint32_t)r9.i << 2));
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
        goto L26;
    }
    lr.i = 50;
L27:
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
        goto L27;
    }
    r8.i = r8.i + (r3.i);
L35:
    ldr8000(&r0.i, &r1.i, &sp.i, 0);
    bfs();
    tmp = r0.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r0.i) >= ((uint32_t) 0);
    v = (r0.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r0.i&0x80000000);
    if (!z)
    {
        goto L28;
    }
L34:
    r0.i = r8.i;
    sp.i = sp.i + (12);
    pop(9, &pc.i, &fp.i, &r10.i, &r9.i, &r8.i, &r7.i, &r6.i, &r5.i, &r4.i);
    return;
L29:
    r3.i = r3.i | (15258 << 16);
    r8.i = r8.i + (r3.i);
    goto L35;
    return;
}

void main()
{
    malloc_start();
    push(6, &r4.i, &r5.i, &r6.i, &r7.i, &r8.i, &lr.i);
    r8.i = (num & 0xffff);
    r8.i = r8.i | (((uint32_t)num >> 16) << 16);
    r4.i = (capacity & 0xffff);
    r4.i = r4.i | (((uint32_t)capacity >> 16) << 16);
    ldr4000(&r6.i, &r8.i, 0);
    tmp = r6.i - 0;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r6.i) >= ((uint32_t) 0);
    v = (r6.i&0x80000000) != (0&0x80000000) && (tmp&0x80000000) != (r6.i&0x80000000);
    if (z || n != v)
    {
        goto L37;
    }
    r3.i = 200;
    r7.i = (uint32_t)r6.i << 2;
    r6.i = ((r3.i) * (r6.i)) + (r4.i);
    r5.i = r4.i;
L38:
    r0.i = r5.i;
    r2.i = r7.i;
    r5.i = r5.i + (200);
    r1.i = 0;
    memset_help();
    tmp = r5.i - r6.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r6.i);
    v = (r5.i&0x80000000) != (r6.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (!z)
    {
        goto L38;
    }
L37:
    r3.i = (e & 0xffff);
    r3.i = r3.i | (((uint32_t)e >> 16) << 16);
    r1.i = 15;
    r0.i = 0;
    r5.i = 1;
    r2.i = 33;
    str4000(&r5.i, &r4.i, 4);
    str4000(&r2.i, &r3.i, 0);
    r3.i = 16;
    str4000(&r5.i, &r4.i, 8);
    str4000(&r3.i, &r8.i, 0);
    str4000(&r5.i, &r4.i, 12);
    str4000(&r5.i, &r4.i, 16);
    str4000(&r5.i, &r4.i, 20);
    str4000(&r5.i, &r4.i, 24);
    str4000(&r5.i, &r4.i, 28);
    str4000(&r5.i, &r4.i, 236);
    str4000(&r5.i, &r4.i, 252);
    str4000(&r5.i, &r4.i, 436);
    str4000(&r5.i, &r4.i, 444);
    str4000(&r5.i, &r4.i, 632);
    str4000(&r5.i, &r4.i, 640);
    str4000(&r5.i, &r4.i, 648);
    str4000(&r5.i, &r4.i, 832);
    str4000(&r5.i, &r4.i, 840);
    str4000(&r5.i, &r4.i, 848);
    str4000(&r5.i, &r4.i, 1036);
    str4000(&r5.i, &r4.i, 1044);
    str4000(&r5.i, &r4.i, 1052);
    str4000(&r5.i, &r4.i, 1240);
    str4000(&r5.i, &r4.i, 1244);
    str4000(&r5.i, &r4.i, 1248);
    str4000(&r5.i, &r4.i, 1252);
    str4000(&r5.i, &r4.i, 1256);
    str4000(&r5.i, &r4.i, 1452);
    str4000(&r5.i, &r4.i, 1660);
    str4000(&r5.i, &r4.i, 1860);
    str4000(&r5.i, &r4.i, 2060);
    str4000(&r5.i, &r4.i, 2260);
    str4000(&r5.i, &r4.i, 2460);
    str4000(&r5.i, &r4.i, 2660);
    str4000(&r5.i, &r4.i, 2860);
    fordFulkerson();
    r1.i = (LC0 & 0xffff);
    r1.i = r1.i | (((uint32_t)LC0 >> 16) << 16);
    r2.i = r0.i;
    r0.i = r5.i;
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    r0.i = 0;
    pop(6, &pc.i, &r8.i, &r7.i, &r6.i, &r5.i, &r4.i);
    counter_summary();
    return;

}

