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

reg r1;
reg r3;
reg r0;

reg f()
{
    sp -= 2;
    stack[sp] = fp;
    stack[sp+1] = lr.i;
    fp = sp + 1;
    sp = sp - 2;
    stack[fp+(-2)] = r0.i;
    r1.i = 1065353216;
    r0.i = stack[fp+(-2)];
    r0.f = r0.f + r1.f;
    r3.i = r0.i;
    r0.i = r3.i;
    sp = fp - 1;
    fp = stack[sp];
    pc.i = stack[sp + 1];
    sp += 2;
    return r0;
}

reg main()
{
    sp -= 2;
    stack[sp] = fp;
    stack[sp+1] = lr.i;
    fp = sp + 1;
    r0.i = 0;
    r0.i = (16512 << 16) | r0.i;
    r0.i = f(r0).i;
    printf("%f", r0.f);
    r3.i = 0;
    r0.i = r3.i;
    fp = stack[sp];
    pc.i = stack[sp + 1];
    sp += 2;
    return r0;
}

