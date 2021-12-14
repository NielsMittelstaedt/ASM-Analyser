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

reg r6, r5, r8, r2, r4, r3, r0, r7, r1;

int32_t LC1, LC2, L8, SimplexTable, LC0;

int counters[11] = { 0 };
int load_counter = 0, store_counter = 0;
int block_sizes[11] = {7,3,1,4,2,3,2,1,7,34,3};

void ldr8000(int32_t *target1, int32_t *target2, int32_t *address, int32_t offset)
{
    *target1 = *((uint32_t*)(malloc_0+*address+offset));
    *target2 = *((uint32_t*)(malloc_0+*address+offset+4));
}
void str8000(int32_t *target1, int32_t *target2, int32_t *address, int32_t offset)
{
    *((uint32_t*)(malloc_0+*address+offset)) = *target1;
    *((uint32_t*)(malloc_0+*address+offset+4)) = *target2;
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
void ldr8010(int32_t *target1, int32_t *target2, int32_t *address, int32_t offset)
{
    *target1 = *((uint32_t*)(malloc_0+*address));
    *target2 = *((uint32_t*)(malloc_0+*address+4));
    *address += offset;
}
void ldr4000(int32_t *target, int32_t *address, int32_t offset)
{
    *target = *((uint32_t*)(malloc_0+*address+offset));
}
void memcpy_help()
{
    memcpy(malloc_0+r0.i, malloc_0+r1.i, r2.i);
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
    malloc_0 = (uint8_t*) malloc(20309);
    sp.i = 19996;
    fp = sp;
    LC1 = 20000;
    strcpy(malloc_0+LC1, "\012------------------Simplex Table Step = %d------");

    LC2 = 20053;
    strcpy(malloc_0+LC2, "%10lf \000");

    SimplexTable = 20065;
    L8 = 20185;
    int32_t arrayL8[] = {SimplexTable+40};
    for(int i=0; i<1; i++) str4000(&arrayL8[i], &L8, i*4);

    LC0 = 20189;
    int32_t arrayLC0[] = {0,1077739520,0,1078362112,0,0,0,0,0,0,0,1073741824,0,1075838976,0,1072693248,0,0,0,1078853632,0,1074790400,0,1074790400,0,0,0,1072693248,0,1078853632};
    for(int i=0; i<30; i++) str4000(&arrayLC0[i], &LC0, i*4);

}

void counter_summary()
{
    int basic_blocks = sizeof(counters)/sizeof(counters[0]);
    int total = 0;
    char filename[] = "print_test.c";

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

void ShowTable();
void main();

void ShowTable()
{
    push(6, &r4.i, &r5.i, &r6.i, &r7.i, &r8.i, &lr.i);
    r2.i = r0.i;
    r1.i = (LC1 & 0xffff);
    r0.i = 1;
    r1.i = r1.i | (((uint32_t)LC1 >> 16) << 16);
    ldr4000(&r5.i, &L8, 0);
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    r6.i = (LC2 & 0xffff);
    r7.i = r5.i + (120);
    r6.i = r6.i | (((uint32_t)LC2 >> 16) << 16);
L2:
    r4.i = r5.i - (40);
L3:
    ldr8010(&r2.i, &r3.i, &r4.i, 8);
    r1.i = r6.i;
    r0.i = 1;
    printf_help(malloc_0+r1.i, r2.i, r2.i, r3.i);
    tmp = r4.i - r5.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r4.i) >= ((uint32_t) r5.i);
    v = (r4.i&0x80000000) != (r5.i&0x80000000) && (tmp&0x80000000) != (r4.i&0x80000000);
    if (!z)
    {
        goto L3;
    }
    r5.i = r4.i + (40);
    r0.i = 10;
    printf_help("%c", r0.i, r1.i, r2.i);
    tmp = r5.i - r7.i;
    z = tmp == 0;
    n = tmp & 0x80000000;
    c = ((uint32_t) r5.i) >= ((uint32_t) r7.i);
    v = (r5.i&0x80000000) != (r7.i&0x80000000) && (tmp&0x80000000) != (r5.i&0x80000000);
    if (!z)
    {
        goto L2;
    }
    pop(6, &pc.i, &r8.i, &r7.i, &r6.i, &r5.i, &r4.i);
    return;

}

void main()
{
    malloc_start();
    push(3, &r4.i, &r5.i, &lr.i);
    sp.i = sp.i - (124);
    r2.i = 120;
    r1.i = (LC0 & 0xffff);
    r0.i = sp.i;
    r1.i = r1.i | (((uint32_t)LC0 >> 16) << 16);
    memcpy_help();
    ldr8000(&r2.i, &r3.i, &sp.i, 8);
    ldr8000(&r4.i, &r5.i, &sp.i, 16);
    ip.i = (SimplexTable & 0xffff);
    ip.i = ip.i | (((uint32_t)SimplexTable >> 16) << 16);
    ldr8000(&r0.i, &r1.i, &sp.i, 0);
    str8000(&r2.i, &r3.i, &ip.i, 8);
    str8000(&r4.i, &r5.i, &ip.i, 16);
    ldr8000(&r2.i, &r3.i, &sp.i, 24);
    ldr8000(&r4.i, &r5.i, &sp.i, 32);
    str8000(&r0.i, &r1.i, &ip.i, 0);
    r0.i = 10;
    str8000(&r2.i, &r3.i, &ip.i, 24);
    str8000(&r4.i, &r5.i, &ip.i, 32);
    ldr8000(&r2.i, &r3.i, &sp.i, 40);
    ldr8000(&r4.i, &r5.i, &sp.i, 48);
    str8000(&r2.i, &r3.i, &ip.i, 40);
    str8000(&r4.i, &r5.i, &ip.i, 48);
    ldr8000(&r2.i, &r3.i, &sp.i, 56);
    ldr8000(&r4.i, &r5.i, &sp.i, 64);
    str8000(&r2.i, &r3.i, &ip.i, 56);
    str8000(&r4.i, &r5.i, &ip.i, 64);
    ldr8000(&r2.i, &r3.i, &sp.i, 72);
    ldr8000(&r4.i, &r5.i, &sp.i, 80);
    str8000(&r2.i, &r3.i, &ip.i, 72);
    str8000(&r4.i, &r5.i, &ip.i, 80);
    ldr8000(&r2.i, &r3.i, &sp.i, 88);
    ldr8000(&r4.i, &r5.i, &sp.i, 96);
    str8000(&r2.i, &r3.i, &ip.i, 88);
    str8000(&r4.i, &r5.i, &ip.i, 96);
    ldr8000(&r2.i, &r3.i, &sp.i, 104);
    ldr8000(&r4.i, &r5.i, &sp.i, 112);
    str8000(&r2.i, &r3.i, &ip.i, 104);
    str8000(&r4.i, &r5.i, &ip.i, 112);
    ShowTable();
    r0.i = 0;
    sp.i = sp.i + (124);
    pop(3, &pc.i, &r5.i, &r4.i);
    counter_summary();
    return;

}

