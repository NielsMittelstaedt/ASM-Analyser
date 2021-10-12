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

reg r0;
reg r3;
reg r4;

reg fib()
{
    sp -= 3;
    stack[sp] = r4.i;
    stack[sp+1] = fp;
    stack[sp+2] = lr.i;
    fp = sp + 2;
    sp = sp - 3;
    stack[fp+(-4)] = r0.i;
    r3.i = stack[fp+(-4)];
    cond_reg = r3.i > 1 ? 1 : (r3.i < 1 ? -1 : 0);
    if (cond_reg == 1)
    {
        r3.i = stack[fp+(-4)];
        r3.i = r3.i - 1;
        r0.i = r3.i;
        r0.i = fib(r0).i;
        r4.i = r0.i;
        r3.i = stack[fp+(-4)];
        r3.i = r3.i - 2;
        r0.i = r3.i;
        r0.i = fib(r0).i;
        r3.i = r0.i;
        r3.i = r4.i + r3.i;
    }
    else
    {
        r3.i = stack[fp+(-4)];
    }
    r0.i = r3.i;
    sp = fp - 2;
    r4.i = stack[sp];
    fp = stack[sp + 1];
    pc.i = stack[sp + 2];
    sp += 3;
    return r0;
}

reg main()
{
    sp -= 2;
    stack[sp] = fp;
    stack[sp+1] = lr.i;
    fp = sp + 1;
    r0.i = 8;
    r0.i = fib(r0).i;
    printf("%d", r0.i);
    r3.i = 0;
    r0.i = r3.i;
    fp = stack[sp];
    pc.i = stack[sp + 1];
    sp += 2;
    return r0;
}

