#include <stdio.h>
#include <stdint.h>
typedef union
{
    int32_t i;
    float f;
} reg;
reg stack[200];
reg sp = {.i = 199}, fp = {.i = 199};
reg lr, pc, cond_reg;
int32_t counter = 0;

int32_t r4;
int32_t r0;
int32_t r3;

int32_t fib()
{
    sp -= 3;
    stack[sp] = r4;
    stack[sp+1] = fp;
    stack[sp+2] = lr;
    fp = sp + 2;
    sp = sp - 3;
    stack[fp+(-4)] = r0;
    r3 = stack[fp+(-4)];
    cond_reg = r3 > 1 ? 1 : (r3 < 1 ? -1 : 0);
    if (cond_reg == 1)
    {
        r3 = stack[fp+(-4)];
        r3 = r3 - 1;
        r0 = r3;
        r0 = fib(r0);
        r4 = r0;
        r3 = stack[fp+(-4)];
        r3 = r3 - 2;
        r0 = r3;
        r0 = fib(r0);
        r3 = r0;
        r3 = r4 + r3;
    }
    else
    {
        r3 = stack[fp+(-4)];
    }
    r0 = r3;
    sp = fp - 2;
    r4 = stack[sp];
    fp = stack[sp + 1];
    pc = stack[sp + 2];
    sp += 3;
    return r0;
}

int32_t main()
{
    sp -= 2;
    stack[sp] = fp;
    stack[sp+1] = lr;
    fp = sp + 1;
    r0 = 3;
    r0 = fib(r0);
    r3 = 0;
    r0 = r3;
    fp = stack[sp];
    pc = stack[sp + 1];
    sp += 2;
    return r0;
}

