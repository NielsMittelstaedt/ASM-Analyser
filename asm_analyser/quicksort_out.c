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

    _arm_reg r3, r0, r2, r4, r1;

    int32_t LC0;

    int load_counter, store_counter;
    int counters[21];
    int block_sizes[21];

    //BPDEFS
} _asm_analysis;

_asm_analysis _asm_analysis_ =
{
    .malloc_0 = 0, .load_counter = 0, .store_counter = 0,
    .counters = {0}, .block_sizes = {10,7,3,12,4,1,3,12,4,22,4,28,6,3,41,1,16,4,6,3,5},
    //BPINIT
};

void smull(int32_t *dest_lo, int32_t *dest_hi, int32_t *op1, int32_t *op2)
{
    uint64_t res = (uint64_t) (*op1) * (*op2);
    *dest_lo = (uint32_t) res;
    *dest_hi = (uint32_t) (res >> 32);
}
void str4000(int32_t *target, int32_t *address, int32_t offset)
{
    *((uint32_t*)(_asm_analysis_.malloc_0+*address+offset)) = *target;
    _asm_analysis_.store_counter ++;
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
void ldr4000(int32_t *target, int32_t *address, int32_t offset)
{
    *target = *((uint32_t*)(_asm_analysis_.malloc_0+*address+offset));
    _asm_analysis_.load_counter ++;
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
void rand_help()
{
    _asm_analysis_.r0.i = rand();
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
    _asm_analysis_.malloc_0 = (uint8_t*) malloc(100013);
    _asm_analysis_.sp.i = 99996;
    _asm_analysis_.fp = _asm_analysis_.sp;
    _asm_analysis_.LC0 = 100000;
    strcpy(_asm_analysis_.malloc_0+_asm_analysis_.LC0, "Sorted.\000");

}

void counter_summary()
{
    int basic_blocks = sizeof(_asm_analysis_.counters)/sizeof(_asm_analysis_.counters[0]);

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

    /* BPSTART
    int branch_count = sizeof(_asm_analysis_.cond_branches)/sizeof(_asm_analysis_.cond_branches[0]);

    for (int i=0; i < branch_count; i++){
        printf("%d ", _asm_analysis_.cond_branches[i]);
    }
    printf("\n");
    for (int i=0; i < branch_count; i++){
        printf("%d ", _asm_analysis_.mispredictions[i]);
    }
    printf("\n");
    BPEND */
}

void quicksort();
void main();

void quicksort()
{
    _asm_analysis_.counters[0] ++;
    push(2, &_asm_analysis_.fp.i, &_asm_analysis_.lr.i);
    _asm_analysis_.fp.i = _asm_analysis_.sp.i + (4);
    _asm_analysis_.sp.i = _asm_analysis_.sp.i - (32);
    str4000(&_asm_analysis_.r0.i, &_asm_analysis_.fp.i, -24);
    str4000(&_asm_analysis_.r1.i, &_asm_analysis_.fp.i, -28);
    str4000(&_asm_analysis_.r2.i, &_asm_analysis_.fp.i, -32);
    ldr4000(&_asm_analysis_.r2.i, &_asm_analysis_.fp.i, -28);
    ldr4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -32);
    _asm_analysis_.tmp = _asm_analysis_.r2.i - _asm_analysis_.r3.i;
    _asm_analysis_.z = _asm_analysis_.tmp == 0;
    _asm_analysis_.n = _asm_analysis_.tmp & 0x80000000;
    _asm_analysis_.c = ((uint32_t) _asm_analysis_.r2.i) >= ((uint32_t) _asm_analysis_.r3.i);
    _asm_analysis_.v = (_asm_analysis_.r2.i&0x80000000) != (_asm_analysis_.r3.i&0x80000000) && (_asm_analysis_.tmp&0x80000000) != (_asm_analysis_.r2.i&0x80000000);
    if (_asm_analysis_.n == _asm_analysis_.v)
    {
//BRANCHTAKEN
        goto L10;
    }
//BRANCHNOTTAKEN
    _asm_analysis_.counters[1] ++;
    ldr4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -28);
    str4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -16);
    ldr4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -28);
    str4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -8);
    ldr4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -32);
    str4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -12);
    goto L3;
L6:
    _asm_analysis_.counters[2] ++;
    ldr4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -8);
    _asm_analysis_.r3.i = _asm_analysis_.r3.i + (1);
    str4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -8);
L4:
    _asm_analysis_.counters[3] ++;
    ldr4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -8);
    _asm_analysis_.r3.i = (uint32_t)_asm_analysis_.r3.i << 2;
    ldr4000(&_asm_analysis_.r2.i, &_asm_analysis_.fp.i, -24);
    _asm_analysis_.r3.i = _asm_analysis_.r2.i + (_asm_analysis_.r3.i);
    ldr4000(&_asm_analysis_.r2.i, &_asm_analysis_.r3.i, 0);
    ldr4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -16);
    _asm_analysis_.r3.i = (uint32_t)_asm_analysis_.r3.i << 2;
    ldr4000(&_asm_analysis_.r1.i, &_asm_analysis_.fp.i, -24);
    _asm_analysis_.r3.i = _asm_analysis_.r1.i + (_asm_analysis_.r3.i);
    ldr4000(&_asm_analysis_.r3.i, &_asm_analysis_.r3.i, 0);
    _asm_analysis_.tmp = _asm_analysis_.r2.i - _asm_analysis_.r3.i;
    _asm_analysis_.z = _asm_analysis_.tmp == 0;
    _asm_analysis_.n = _asm_analysis_.tmp & 0x80000000;
    _asm_analysis_.c = ((uint32_t) _asm_analysis_.r2.i) >= ((uint32_t) _asm_analysis_.r3.i);
    _asm_analysis_.v = (_asm_analysis_.r2.i&0x80000000) != (_asm_analysis_.r3.i&0x80000000) && (_asm_analysis_.tmp&0x80000000) != (_asm_analysis_.r2.i&0x80000000);
    if (!_asm_analysis_.z && _asm_analysis_.n == _asm_analysis_.v)
    {
//BRANCHTAKEN
        goto L7;
    }
//BRANCHNOTTAKEN
    _asm_analysis_.counters[4] ++;
    ldr4000(&_asm_analysis_.r2.i, &_asm_analysis_.fp.i, -8);
    ldr4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -32);
    _asm_analysis_.tmp = _asm_analysis_.r2.i - _asm_analysis_.r3.i;
    _asm_analysis_.z = _asm_analysis_.tmp == 0;
    _asm_analysis_.n = _asm_analysis_.tmp & 0x80000000;
    _asm_analysis_.c = ((uint32_t) _asm_analysis_.r2.i) >= ((uint32_t) _asm_analysis_.r3.i);
    _asm_analysis_.v = (_asm_analysis_.r2.i&0x80000000) != (_asm_analysis_.r3.i&0x80000000) && (_asm_analysis_.tmp&0x80000000) != (_asm_analysis_.r2.i&0x80000000);
    if (_asm_analysis_.n != _asm_analysis_.v)
    {
//BRANCHTAKEN
        goto L6;
    }
//BRANCHNOTTAKEN
    _asm_analysis_.counters[5] ++;
    goto L7;
L8:
    _asm_analysis_.counters[6] ++;
    ldr4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -12);
    _asm_analysis_.r3.i = _asm_analysis_.r3.i - (1);
    str4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -12);
L7:
    _asm_analysis_.counters[7] ++;
    ldr4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -12);
    _asm_analysis_.r3.i = (uint32_t)_asm_analysis_.r3.i << 2;
    ldr4000(&_asm_analysis_.r2.i, &_asm_analysis_.fp.i, -24);
    _asm_analysis_.r3.i = _asm_analysis_.r2.i + (_asm_analysis_.r3.i);
    ldr4000(&_asm_analysis_.r2.i, &_asm_analysis_.r3.i, 0);
    ldr4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -16);
    _asm_analysis_.r3.i = (uint32_t)_asm_analysis_.r3.i << 2;
    ldr4000(&_asm_analysis_.r1.i, &_asm_analysis_.fp.i, -24);
    _asm_analysis_.r3.i = _asm_analysis_.r1.i + (_asm_analysis_.r3.i);
    ldr4000(&_asm_analysis_.r3.i, &_asm_analysis_.r3.i, 0);
    _asm_analysis_.tmp = _asm_analysis_.r2.i - _asm_analysis_.r3.i;
    _asm_analysis_.z = _asm_analysis_.tmp == 0;
    _asm_analysis_.n = _asm_analysis_.tmp & 0x80000000;
    _asm_analysis_.c = ((uint32_t) _asm_analysis_.r2.i) >= ((uint32_t) _asm_analysis_.r3.i);
    _asm_analysis_.v = (_asm_analysis_.r2.i&0x80000000) != (_asm_analysis_.r3.i&0x80000000) && (_asm_analysis_.tmp&0x80000000) != (_asm_analysis_.r2.i&0x80000000);
    if (!_asm_analysis_.z && _asm_analysis_.n == _asm_analysis_.v)
    {
//BRANCHTAKEN
        goto L8;
    }
//BRANCHNOTTAKEN
    _asm_analysis_.counters[8] ++;
    ldr4000(&_asm_analysis_.r2.i, &_asm_analysis_.fp.i, -8);
    ldr4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -12);
    _asm_analysis_.tmp = _asm_analysis_.r2.i - _asm_analysis_.r3.i;
    _asm_analysis_.z = _asm_analysis_.tmp == 0;
    _asm_analysis_.n = _asm_analysis_.tmp & 0x80000000;
    _asm_analysis_.c = ((uint32_t) _asm_analysis_.r2.i) >= ((uint32_t) _asm_analysis_.r3.i);
    _asm_analysis_.v = (_asm_analysis_.r2.i&0x80000000) != (_asm_analysis_.r3.i&0x80000000) && (_asm_analysis_.tmp&0x80000000) != (_asm_analysis_.r2.i&0x80000000);
    if (_asm_analysis_.n == _asm_analysis_.v)
    {
//BRANCHTAKEN
        goto L3;
    }
//BRANCHNOTTAKEN
    _asm_analysis_.counters[9] ++;
    ldr4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -8);
    _asm_analysis_.r3.i = (uint32_t)_asm_analysis_.r3.i << 2;
    ldr4000(&_asm_analysis_.r2.i, &_asm_analysis_.fp.i, -24);
    _asm_analysis_.r3.i = _asm_analysis_.r2.i + (_asm_analysis_.r3.i);
    ldr4000(&_asm_analysis_.r3.i, &_asm_analysis_.r3.i, 0);
    str4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -20);
    ldr4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -12);
    _asm_analysis_.r3.i = (uint32_t)_asm_analysis_.r3.i << 2;
    ldr4000(&_asm_analysis_.r2.i, &_asm_analysis_.fp.i, -24);
    _asm_analysis_.r2.i = _asm_analysis_.r2.i + (_asm_analysis_.r3.i);
    ldr4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -8);
    _asm_analysis_.r3.i = (uint32_t)_asm_analysis_.r3.i << 2;
    ldr4000(&_asm_analysis_.r1.i, &_asm_analysis_.fp.i, -24);
    _asm_analysis_.r3.i = _asm_analysis_.r1.i + (_asm_analysis_.r3.i);
    ldr4000(&_asm_analysis_.r2.i, &_asm_analysis_.r2.i, 0);
    str4000(&_asm_analysis_.r2.i, &_asm_analysis_.r3.i, 0);
    ldr4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -12);
    _asm_analysis_.r3.i = (uint32_t)_asm_analysis_.r3.i << 2;
    ldr4000(&_asm_analysis_.r2.i, &_asm_analysis_.fp.i, -24);
    _asm_analysis_.r3.i = _asm_analysis_.r2.i + (_asm_analysis_.r3.i);
    ldr4000(&_asm_analysis_.r2.i, &_asm_analysis_.fp.i, -20);
    str4000(&_asm_analysis_.r2.i, &_asm_analysis_.r3.i, 0);
L3:
    _asm_analysis_.counters[10] ++;
    ldr4000(&_asm_analysis_.r2.i, &_asm_analysis_.fp.i, -8);
    ldr4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -12);
    _asm_analysis_.tmp = _asm_analysis_.r2.i - _asm_analysis_.r3.i;
    _asm_analysis_.z = _asm_analysis_.tmp == 0;
    _asm_analysis_.n = _asm_analysis_.tmp & 0x80000000;
    _asm_analysis_.c = ((uint32_t) _asm_analysis_.r2.i) >= ((uint32_t) _asm_analysis_.r3.i);
    _asm_analysis_.v = (_asm_analysis_.r2.i&0x80000000) != (_asm_analysis_.r3.i&0x80000000) && (_asm_analysis_.tmp&0x80000000) != (_asm_analysis_.r2.i&0x80000000);
    if (_asm_analysis_.n != _asm_analysis_.v)
    {
//BRANCHTAKEN
        goto L4;
    }
//BRANCHNOTTAKEN
    _asm_analysis_.counters[11] ++;
    ldr4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -16);
    _asm_analysis_.r3.i = (uint32_t)_asm_analysis_.r3.i << 2;
    ldr4000(&_asm_analysis_.r2.i, &_asm_analysis_.fp.i, -24);
    _asm_analysis_.r3.i = _asm_analysis_.r2.i + (_asm_analysis_.r3.i);
    ldr4000(&_asm_analysis_.r3.i, &_asm_analysis_.r3.i, 0);
    str4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -20);
    ldr4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -12);
    _asm_analysis_.r3.i = (uint32_t)_asm_analysis_.r3.i << 2;
    ldr4000(&_asm_analysis_.r2.i, &_asm_analysis_.fp.i, -24);
    _asm_analysis_.r2.i = _asm_analysis_.r2.i + (_asm_analysis_.r3.i);
    ldr4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -16);
    _asm_analysis_.r3.i = (uint32_t)_asm_analysis_.r3.i << 2;
    ldr4000(&_asm_analysis_.r1.i, &_asm_analysis_.fp.i, -24);
    _asm_analysis_.r3.i = _asm_analysis_.r1.i + (_asm_analysis_.r3.i);
    ldr4000(&_asm_analysis_.r2.i, &_asm_analysis_.r2.i, 0);
    str4000(&_asm_analysis_.r2.i, &_asm_analysis_.r3.i, 0);
    ldr4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -12);
    _asm_analysis_.r3.i = (uint32_t)_asm_analysis_.r3.i << 2;
    ldr4000(&_asm_analysis_.r2.i, &_asm_analysis_.fp.i, -24);
    _asm_analysis_.r3.i = _asm_analysis_.r2.i + (_asm_analysis_.r3.i);
    ldr4000(&_asm_analysis_.r2.i, &_asm_analysis_.fp.i, -20);
    str4000(&_asm_analysis_.r2.i, &_asm_analysis_.r3.i, 0);
    ldr4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -12);
    _asm_analysis_.r3.i = _asm_analysis_.r3.i - (1);
    _asm_analysis_.r2.i = _asm_analysis_.r3.i;
    ldr4000(&_asm_analysis_.r1.i, &_asm_analysis_.fp.i, -28);
    ldr4000(&_asm_analysis_.r0.i, &_asm_analysis_.fp.i, -24);
    quicksort();
    _asm_analysis_.counters[12] ++;
    ldr4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -12);
    _asm_analysis_.r3.i = _asm_analysis_.r3.i + (1);
    ldr4000(&_asm_analysis_.r2.i, &_asm_analysis_.fp.i, -32);
    _asm_analysis_.r1.i = _asm_analysis_.r3.i;
    ldr4000(&_asm_analysis_.r0.i, &_asm_analysis_.fp.i, -24);
    quicksort();
L10:
    _asm_analysis_.counters[13] ++;
    _asm_analysis_.sp.i = _asm_analysis_.fp.i - (4);
    pop(2, &_asm_analysis_.pc.i, &_asm_analysis_.fp.i);
    return;

}

void main()
{
    malloc_start();
    _asm_analysis_.counters[14] ++;
    push(3, &_asm_analysis_.r4.i, &_asm_analysis_.fp.i, &_asm_analysis_.lr.i);
    _asm_analysis_.fp.i = _asm_analysis_.sp.i + (8);
    _asm_analysis_.sp.i = _asm_analysis_.sp.i - (20);
    _asm_analysis_.r3.i = _asm_analysis_.sp.i;
    _asm_analysis_.r4.i = _asm_analysis_.r3.i;
    _asm_analysis_.r3.i = 16960;
    _asm_analysis_.r3.i = _asm_analysis_.r3.i | (15 << 16);
    str4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -20);
    ldr4000(&_asm_analysis_.ip.i, &_asm_analysis_.fp.i, -20);
    _asm_analysis_.r3.i = _asm_analysis_.ip.i - (1);
    str4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -24);
    _asm_analysis_.r3.i = _asm_analysis_.ip.i;
    _asm_analysis_.r0.i = _asm_analysis_.r3.i;
    _asm_analysis_.r1.i = 0;
    _asm_analysis_.r2.i = 0;
    _asm_analysis_.r3.i = 0;
    _asm_analysis_.r3.i = (uint32_t)_asm_analysis_.r1.i << 5;
    _asm_analysis_.r3.i = _asm_analysis_.r3.i | ((uint32_t)_asm_analysis_.r0.i >> 27);
    _asm_analysis_.r2.i = (uint32_t)_asm_analysis_.r0.i << 5;
    _asm_analysis_.r3.i = _asm_analysis_.ip.i;
    _asm_analysis_.r0.i = _asm_analysis_.r3.i;
    _asm_analysis_.r1.i = 0;
    _asm_analysis_.r2.i = 0;
    _asm_analysis_.r3.i = 0;
    _asm_analysis_.r3.i = (uint32_t)_asm_analysis_.r1.i << 5;
    _asm_analysis_.r3.i = _asm_analysis_.r3.i | ((uint32_t)_asm_analysis_.r0.i >> 27);
    _asm_analysis_.r2.i = (uint32_t)_asm_analysis_.r0.i << 5;
    _asm_analysis_.r3.i = _asm_analysis_.ip.i;
    _asm_analysis_.r3.i = (uint32_t)_asm_analysis_.r3.i << 2;
    _asm_analysis_.r3.i = _asm_analysis_.r3.i + (7);
    _asm_analysis_.r3.i = (uint32_t)_asm_analysis_.r3.i >> 3;
    _asm_analysis_.r3.i = (uint32_t)_asm_analysis_.r3.i << 3;
    _asm_analysis_.sp.i = _asm_analysis_.sp.i - (_asm_analysis_.r3.i);
    _asm_analysis_.r3.i = _asm_analysis_.sp.i;
    _asm_analysis_.r3.i = _asm_analysis_.r3.i + (3);
    _asm_analysis_.r3.i = (uint32_t)_asm_analysis_.r3.i >> 2;
    _asm_analysis_.r3.i = (uint32_t)_asm_analysis_.r3.i << 2;
    str4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -28);
    _asm_analysis_.r3.i = 0;
    str4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -16);
    goto L12;
L13:
    _asm_analysis_.counters[15] ++;
    rand_help();
    _asm_analysis_.counters[16] ++;
    _asm_analysis_.r2.i = _asm_analysis_.r0.i;
    _asm_analysis_.r3.i = 35757;
    _asm_analysis_.r3.i = _asm_analysis_.r3.i | (26843 << 16);
    smull(&_asm_analysis_.r1.i, &_asm_analysis_.r3.i, &_asm_analysis_.r3.i, &_asm_analysis_.r2.i);
    _asm_analysis_.r1.i = _asm_analysis_.r3.i >> 12;
    _asm_analysis_.r3.i = _asm_analysis_.r2.i >> 31;
    _asm_analysis_.r3.i = _asm_analysis_.r1.i - (_asm_analysis_.r3.i);
    _asm_analysis_.r1.i = 10000;
    _asm_analysis_.r3.i = (_asm_analysis_.r1.i) * (_asm_analysis_.r3.i);
    _asm_analysis_.r3.i = _asm_analysis_.r2.i - (_asm_analysis_.r3.i);
    ldr4000(&_asm_analysis_.r2.i, &_asm_analysis_.fp.i, -28);
    ldr4000(&_asm_analysis_.r1.i, &_asm_analysis_.fp.i, -16);
    str4000(&_asm_analysis_.r3.i, &_asm_analysis_.r2.i, ((uint32_t)_asm_analysis_.r1.i << 2));
    ldr4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -16);
    _asm_analysis_.r3.i = _asm_analysis_.r3.i + (1);
    str4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -16);
L12:
    _asm_analysis_.counters[17] ++;
    ldr4000(&_asm_analysis_.r2.i, &_asm_analysis_.fp.i, -16);
    ldr4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -20);
    _asm_analysis_.tmp = _asm_analysis_.r2.i - _asm_analysis_.r3.i;
    _asm_analysis_.z = _asm_analysis_.tmp == 0;
    _asm_analysis_.n = _asm_analysis_.tmp & 0x80000000;
    _asm_analysis_.c = ((uint32_t) _asm_analysis_.r2.i) >= ((uint32_t) _asm_analysis_.r3.i);
    _asm_analysis_.v = (_asm_analysis_.r2.i&0x80000000) != (_asm_analysis_.r3.i&0x80000000) && (_asm_analysis_.tmp&0x80000000) != (_asm_analysis_.r2.i&0x80000000);
    if (_asm_analysis_.n != _asm_analysis_.v)
    {
//BRANCHTAKEN
        goto L13;
    }
//BRANCHNOTTAKEN
    _asm_analysis_.counters[18] ++;
    ldr4000(&_asm_analysis_.r3.i, &_asm_analysis_.fp.i, -20);
    _asm_analysis_.r3.i = _asm_analysis_.r3.i - (1);
    _asm_analysis_.r2.i = _asm_analysis_.r3.i;
    _asm_analysis_.r1.i = 0;
    ldr4000(&_asm_analysis_.r0.i, &_asm_analysis_.fp.i, -28);
    quicksort();
    _asm_analysis_.counters[19] ++;
    _asm_analysis_.r0.i = (_asm_analysis_.LC0 & 0xffff);
    _asm_analysis_.r0.i = _asm_analysis_.r0.i | (((uint32_t)_asm_analysis_.LC0 >> 16) << 16);
    printf_help("%s\n", _asm_analysis_.r0.i, _asm_analysis_.r1.i, _asm_analysis_.r2.i);
    _asm_analysis_.counters[20] ++;
    _asm_analysis_.r3.i = 0;
    _asm_analysis_.sp.i = _asm_analysis_.r4.i;
    _asm_analysis_.r0.i = _asm_analysis_.r3.i;
    _asm_analysis_.sp.i = _asm_analysis_.fp.i - (8);
    pop(3, &_asm_analysis_.pc.i, &_asm_analysis_.fp.i, &_asm_analysis_.r4.i);
    counter_summary();
    return;

}

