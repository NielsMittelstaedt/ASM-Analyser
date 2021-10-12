#include <stdio.h>
#include <stdint.h>

typedef union
{
    int32_t i;
    float f;
} reg;

int32_t stack[200];
int32_t sp = 199, fp = 199;
int32_t cond_reg, counter = 0;
reg lr, pc;

reg r3;
reg r0;

reg main()
{
    sp += -1;
    stack[sp] = fp;
    fp = sp + 0;
    sp = sp - 5;
    r3.i = 2;
    stack[fp+(-4)] = r3.i;
    r3.i = 3;
    stack[fp+(-3)] = r3.i;
    r3.i = stack[fp+(-4)];
    stack[fp+(-2)] = r3.i;
    r3.i = stack[fp+(-3)];
    stack[fp+(-4)] = r3.i;
    r3.i = stack[fp+(-2)];
    stack[fp+(-3)] = r3.i;
    r3.i = 0;
    r0.i = r3.i;
    sp = fp + 0;
    fp = stack[sp];
    sp += 1;
    return r0;
}

