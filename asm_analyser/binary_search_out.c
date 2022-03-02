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
} _arm_reg;

typedef struct
{
    int32_t tmp;
    _arm_reg sp, fp, lr, pc, ip;
    bool z, n, c, v;
    uint8_t* malloc_0;

    _arm_reg r1, r3, r2, r4, r0;

    int32_t LC1, LC0;

    int load_counter, store_counter;
    int counters[13];
    int block_sizes[13];

    uint8_t branch_bits[3];
    int cond_branches[3];
    int mispredictions[3];
} _asm_analysis;

_asm_analysis _asm_analysis_ =
{
    .malloc_0 = 0, .load_counter = 0, .store_counter = 0,
    .counters = {0}, .block_sizes = {11,18,2,8,6,2,6,2,1,3,21,5,4},
    .branch_bits = {0}, .cond_branches = {0}, .mispredictions = {0}
};

void stm1(int32_t *address, int num, ...)
{
    va_list args;
    va_start(args, num);
    for (int i=0; i < num; i++)
    {
        int32_t *cur_arg = va_arg(args, int32_t *);
        *((uint32_t*) (_asm_analysis_.malloc_0 + *address)) = *cur_arg;
        *address += 4;
        _asm_analysis_.store_counter ++;
    }
    va_end(args);
}
void ldr4000(int32_t *target, int32_t *address, int32_t offset)
{
    *target = *((uint32_t*)(_asm_analysis_.malloc_0+*address+offset));
    _asm_analysis_.load_counter ++;
}
void ldm1(int32_t *address, int num, ...)
{
    va_list args;
    va_start(args, num);
    for (int i=0; i < num; i++)
    {
        int32_t *cur_arg = va_arg(args, int32_t *);
        *cur_arg = *((uint32_t*) (_asm_analysis_.malloc_0 + *address));
        *address += 4;
        _asm_analysis_.load_counter ++;
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
        *cur_arg = *((uint32_t*) (_asm_analysis_.malloc_0 + _asm_analysis_.sp.i));
        _asm_analysis_.sp.i += 4;
        _asm_analysis_.load_counter ++;
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
        _asm_analysis_.sp.i -= 4;
        *((uint32_t*) (_asm_analysis_.malloc_0 + _asm_analysis_.sp.i)) = *cur_arg;
        _asm_analysis_.store_counter ++;
    }
    va_end(args);
}
void str4000(int32_t *target, int32_t *address, int32_t offset)
{
    *((uint32_t*)(_asm_analysis_.malloc_0+*address+offset)) = *target;
    _asm_analysis_.store_counter ++;
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
        printf(format, _asm_analysis_.malloc_0+arg1);
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

// Debugging purposes
/*
void print_stack(int32_t start, int32_t bytes)
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
    _asm_analysis_.malloc_0 = (uint8_t*) malloc(10040);
    _asm_analysis_.sp.i = 9996;
    _asm_analysis_.fp = _asm_analysis_.sp;
    _asm_analysis_.LC1 = 10000;
    strcpy(_asm_analysis_.malloc_0+_asm_analysis_.LC1, "Result: %d\012\000");

    _asm_analysis_.LC0 = 10020;
    int32_t arrayLC0[] = {2,3,4,10,40};
    for(int i=0; i<5; i++) *((uint32_t*)(_asm_analysis_.malloc_0+_asm_analysis_.LC0+i*4)) = arrayLC0[i];

}

void counter_summary()
{
    int basic_blocks = sizeof(_asm_analysis_.counters)/sizeof(_asm_analysis_.counters[0]);
    int branch_count = sizeof(_asm_analysis_.cond_branches)/sizeof(_asm_analysis_.cond_branches[0]);

    printf("\n__count_start__\n");
    printf("%d\n", basic_blocks);

    for (int i=0; i < basic_blocks; i++)
    {
        printf("%d ", _asm_analysis_.block_sizes[i]);
    }
    printf("\n");

    for (int i=0; i < basic_blocks; i++)
    {
        printf("%d ", _asm_analysis_.counters[i]);
    }
    printf("\n");
    printf("%d\n", _asm_analysis_.load_counter);
    printf("%d\n", _asm_analysis_.store_counter);
    for (int i=0; i < branch_count; i++)
    {
        printf("%d ", _asm_analysis_.cond_branches[i]);
    }
    printf("\n");
    for (int i=0; i < branch_count; i++)
    {
        printf("%d ", _asm_analysis_.mispredictions[i]);
    }
    printf("\n");
}

void binarySearch();
void main();

void binarySearch()
{
    _asm_analysis_.counters[0] ++;
    push(2, &_asm_analysis_.fp.i, &_asm_analysis_.lr.i);
    _asm_analysis_.fp.i = _asm_analysis_.sp.i + (4);
    _asm_analysis_.sp.i = _asm_analysis_.sp.i - (24);
    str4000(&_asm_analysis_.r0.i, &_asm_analysis_.fp.i, -16);
    str4000(&_asm_analysis_.r1.i, &_asm_analysis_.fp.i, -20);
    str4000(&_asm_analysis_.r2.i, &_asm_analysis_.fp.i, -24);
    str4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -28);
    ldr4000(&_asm_analysis_.r2.i, &_asm_analysis_.fp.i, -24);
    ldr4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -20);
    _asm_analysis_.tmp = _asm_analysis_.r2.i - _asm_analysis_.r3.i;
    _asm_analysis_.z = _asm_analysis_.tmp == 0;
    _asm_analysis_.n = _asm_analysis_.tmp & 0x80000000;
    _asm_analysis_.c = ((uint32_t) _asm_analysis_.r2.i) >= ((uint32_t) _asm_analysis_.r3.i);
    _asm_analysis_.v = (_asm_analysis_.r2.i&0x80000000) != (_asm_analysis_.r3.i&0x80000000) && (_asm_analysis_.tmp&0x80000000) != (_asm_analysis_.r2.i&0x80000000);
    if (_asm_analysis_.n != _asm_analysis_.v)
    {
        _asm_analysis_.cond_branches[0]++;
        if(_asm_analysis_.branch_bits[0] == 0)
        {
            _asm_analysis_.mispredictions[0]++;
            _asm_analysis_.branch_bits[0] = 1;
        }
        goto L2;
    }
    _asm_analysis_.cond_branches[0]++;
    if(_asm_analysis_.branch_bits[0] == 1)
    {
        _asm_analysis_.mispredictions[0]++;
        _asm_analysis_.branch_bits[0] = 0;
    }
    _asm_analysis_.counters[1] ++;
    ldr4000(&_asm_analysis_.r2.i, &_asm_analysis_.fp.i, -24);
    ldr4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -20);
    _asm_analysis_.r3.i = _asm_analysis_.r2.i - (_asm_analysis_.r3.i);
    _asm_analysis_.r2.i = (uint32_t)_asm_analysis_.r3.i >> 31;
    _asm_analysis_.r3.i = _asm_analysis_.r2.i + (_asm_analysis_.r3.i);
    _asm_analysis_.r3.i = _asm_analysis_.r3.i >> 1;
    _asm_analysis_.r2.i = _asm_analysis_.r3.i;
    ldr4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -20);
    _asm_analysis_.r3.i = _asm_analysis_.r3.i + (_asm_analysis_.r2.i);
    str4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -8);
    ldr4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -8);
    _asm_analysis_.r3.i = (uint32_t)_asm_analysis_.r3.i << 2;
    ldr4000(&_asm_analysis_.r2.i, &_asm_analysis_.fp.i, -16);
    _asm_analysis_.r3.i = _asm_analysis_.r2.i + (_asm_analysis_.r3.i);
    ldr4000(&_asm_analysis_.r3.i, &_asm_analysis_.r3.i, 0);
    ldr4000(&_asm_analysis_.r2.i, &_asm_analysis_.fp.i, -28);
    _asm_analysis_.tmp = _asm_analysis_.r2.i - _asm_analysis_.r3.i;
    _asm_analysis_.z = _asm_analysis_.tmp == 0;
    _asm_analysis_.n = _asm_analysis_.tmp & 0x80000000;
    _asm_analysis_.c = ((uint32_t) _asm_analysis_.r2.i) >= ((uint32_t) _asm_analysis_.r3.i);
    _asm_analysis_.v = (_asm_analysis_.r2.i&0x80000000) != (_asm_analysis_.r3.i&0x80000000) && (_asm_analysis_.tmp&0x80000000) != (_asm_analysis_.r2.i&0x80000000);
    if (!_asm_analysis_.z)
    {
        _asm_analysis_.cond_branches[1]++;
        if(_asm_analysis_.branch_bits[1] == 0)
        {
            _asm_analysis_.mispredictions[1]++;
            _asm_analysis_.branch_bits[1] = 1;
        }
        goto L3;
    }
    _asm_analysis_.cond_branches[1]++;
    if(_asm_analysis_.branch_bits[1] == 1)
    {
        _asm_analysis_.mispredictions[1]++;
        _asm_analysis_.branch_bits[1] = 0;
    }
    _asm_analysis_.counters[2] ++;
    ldr4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -8);
    goto L4;
L3:
    _asm_analysis_.counters[3] ++;
    ldr4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -8);
    _asm_analysis_.r3.i = (uint32_t)_asm_analysis_.r3.i << 2;
    ldr4000(&_asm_analysis_.r2.i, &_asm_analysis_.fp.i, -16);
    _asm_analysis_.r3.i = _asm_analysis_.r2.i + (_asm_analysis_.r3.i);
    ldr4000(&_asm_analysis_.r3.i, &_asm_analysis_.r3.i, 0);
    ldr4000(&_asm_analysis_.r2.i, &_asm_analysis_.fp.i, -28);
    _asm_analysis_.tmp = _asm_analysis_.r2.i - _asm_analysis_.r3.i;
    _asm_analysis_.z = _asm_analysis_.tmp == 0;
    _asm_analysis_.n = _asm_analysis_.tmp & 0x80000000;
    _asm_analysis_.c = ((uint32_t) _asm_analysis_.r2.i) >= ((uint32_t) _asm_analysis_.r3.i);
    _asm_analysis_.v = (_asm_analysis_.r2.i&0x80000000) != (_asm_analysis_.r3.i&0x80000000) && (_asm_analysis_.tmp&0x80000000) != (_asm_analysis_.r2.i&0x80000000);
    if (_asm_analysis_.n == _asm_analysis_.v)
    {
        _asm_analysis_.cond_branches[2]++;
        if(_asm_analysis_.branch_bits[2] == 0)
        {
            _asm_analysis_.mispredictions[2]++;
            _asm_analysis_.branch_bits[2] = 1;
        }
        goto L5;
    }
    _asm_analysis_.cond_branches[2]++;
    if(_asm_analysis_.branch_bits[2] == 1)
    {
        _asm_analysis_.mispredictions[2]++;
        _asm_analysis_.branch_bits[2] = 0;
    }
    _asm_analysis_.counters[4] ++;
    ldr4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -8);
    _asm_analysis_.r2.i = _asm_analysis_.r3.i - (1);
    ldr4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -28);
    ldr4000(&_asm_analysis_.r1.i, &_asm_analysis_.fp.i, -20);
    ldr4000(&_asm_analysis_.r0.i, &_asm_analysis_.fp.i, -16);
    binarySearch();
    _asm_analysis_.counters[5] ++;
    _asm_analysis_.r3.i = _asm_analysis_.r0.i;
    goto L4;
L5:
    _asm_analysis_.counters[6] ++;
    ldr4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -8);
    _asm_analysis_.r1.i = _asm_analysis_.r3.i + (1);
    ldr4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -28);
    ldr4000(&_asm_analysis_.r2.i, &_asm_analysis_.fp.i, -24);
    ldr4000(&_asm_analysis_.r0.i, &_asm_analysis_.fp.i, -16);
    binarySearch();
    _asm_analysis_.counters[7] ++;
    _asm_analysis_.r3.i = _asm_analysis_.r0.i;
    goto L4;
L2:
    _asm_analysis_.counters[8] ++;
    _asm_analysis_.r3.i = ~0;
L4:
    _asm_analysis_.counters[9] ++;
    _asm_analysis_.r0.i = _asm_analysis_.r3.i;
    _asm_analysis_.sp.i = _asm_analysis_.fp.i - (4);
    pop(2, &_asm_analysis_.pc.i, &_asm_analysis_.fp.i);
    return;

}

void main()
{
    malloc_start();
    _asm_analysis_.counters[10] ++;
    push(2, &_asm_analysis_.fp.i, &_asm_analysis_.lr.i);
    _asm_analysis_.fp.i = _asm_analysis_.sp.i + (4);
    _asm_analysis_.sp.i = _asm_analysis_.sp.i - (32);
    _asm_analysis_.r3.i = (_asm_analysis_.LC0 & 0xffff);
    _asm_analysis_.r3.i = _asm_analysis_.r3.i | (((uint32_t)_asm_analysis_.LC0 >> 16) << 16);
    _asm_analysis_.ip.i = _asm_analysis_.fp.i - (32);
    _asm_analysis_.lr.i = _asm_analysis_.r3.i;
    ldm1(&_asm_analysis_.lr.i, 4, &_asm_analysis_.r0.i, &_asm_analysis_.r1.i, &_asm_analysis_.r2.i, &_asm_analysis_.r3.i);
    stm1(&_asm_analysis_.ip.i, 4, &_asm_analysis_.r0.i, &_asm_analysis_.r1.i, &_asm_analysis_.r2.i, &_asm_analysis_.r3.i);
    ldr4000(&_asm_analysis_.r3.i, &_asm_analysis_.lr.i, 0);
    str4000(&_asm_analysis_.r3.i, &_asm_analysis_.ip.i, 0);
    _asm_analysis_.r3.i = 6;
    str4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -8);
    _asm_analysis_.r3.i = 40;
    str4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -12);
    ldr4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -8);
    _asm_analysis_.r2.i = _asm_analysis_.r3.i - (1);
    _asm_analysis_.r0.i = _asm_analysis_.fp.i - (32);
    ldr4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -12);
    _asm_analysis_.r1.i = 0;
    binarySearch();
    _asm_analysis_.counters[11] ++;
    _asm_analysis_.r3.i = _asm_analysis_.r0.i;
    _asm_analysis_.r1.i = _asm_analysis_.r3.i;
    _asm_analysis_.r0.i = (_asm_analysis_.LC1 & 0xffff);
    _asm_analysis_.r0.i = _asm_analysis_.r0.i | (((uint32_t)_asm_analysis_.LC1 >> 16) << 16);
    printf_help(_asm_analysis_.malloc_0+_asm_analysis_.r0.i, _asm_analysis_.r1.i, _asm_analysis_.r2.i, _asm_analysis_.r3.i);
    _asm_analysis_.counters[12] ++;
    _asm_analysis_.r3.i = 0;
    _asm_analysis_.r0.i = _asm_analysis_.r3.i;
    _asm_analysis_.sp.i = _asm_analysis_.fp.i - (4);
    pop(2, &_asm_analysis_.pc.i, &_asm_analysis_.fp.i);
    counter_summary();
    return;

}