#include <stdio.h>
#include <stdint.h>

typedef union
{
    int32_t i;
    float f;
} reg;

int32_t stack[200];
int32_t sp = 199, fp = 199;
int32_t counter = 0;
reg lr, pc, cond_reg;

reg r3;
reg r2;
reg r0;
reg r1;

reg addition()
{
    sp += -1;
    stack[sp] = fp;
    fp = sp + 0;
    sp = sp - 5;
    stack[fp+(-4)] = r0.i;
    stack[fp+(-5)] = r1.i;
    r2.i = stack[fp+(-4)];
    r3.i = stack[fp+(-5)];
    r3.i = r2.i + r3.i;
    stack[fp+(-2)] = r3.i;
    r3.i = stack[fp+(-2)];
    r0.i = r3.i;
    sp = fp + 0;
    fp = stack[sp];
    sp += 1;
    return r0;
}

reg main()
{
    sp -= 2;
    stack[sp] = fp;
    stack[sp+1] = lr.i;
    fp = sp + 1;
    r1.i = 3;
    r0.i = 6;
    r0.i = addition(r0).i;
    printf("%d", r0.i);
    r3.i = 0;
    r0.i = r3.i;
    fp = stack[sp];
    pc.i = stack[sp + 1];
    sp += 2;
    return r0;
}

