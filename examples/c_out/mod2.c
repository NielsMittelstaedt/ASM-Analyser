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

reg f()
{
    sp += -1;
    stack[sp] = fp;
    fp = sp + 0;
    sp = sp - 3;
    stack[fp+(-2)] = r0.i;
    r3.i = stack[fp+(-2)];
    cond_reg = r3.i > 0 ? 1 : (r3.i < 0 ? -1 : 0);
    r3.i = r3.i & 1;
    r3.i = r3.i < 0 ? 0 - r3.i : r3.i;
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
    r0.i = 1;
    r0.i = f(r0).i;
    printf("%d", r0.i);
    r3.i = 0;
    r0.i = r3.i;
    fp = stack[sp];
    pc.i = stack[sp + 1];
    sp += 2;
    return r0;
}

