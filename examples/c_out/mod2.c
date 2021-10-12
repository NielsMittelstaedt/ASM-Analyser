#include <stdio.h>
#include <stdint.h>
int32_t stack[200];
int32_t sp = 199, fp = 199;
int32_t lr, pc, cond_reg;
int32_t counter = 0;

int32_t r3;
int32_t r0;

int32_t f()
{
    sp += -1;
    stack[sp] = fp;
    fp = sp + 0;
    sp = sp - 3;
    stack[fp+(-2)] = r0;
    r3 = stack[fp+(-2)];
    cond_reg = r3 > 0 ? 1 : (r3 < 0 ? -1 : 0);
    r3 = r3 & 1;
    r3 = r3 < 0 ? 0 - r3 : r3;
    r0 = r3;
    sp = fp + 0;
    fp = stack[sp];
    sp += 1;
    return r0;
}

int32_t main()
{
    sp -= 2;
    stack[sp] = fp;
    stack[sp+1] = lr;
    fp = sp + 1;
    r0 = 3;
    r0 = f(r0);
    r3 = 0;
    r0 = r3;
    fp = stack[sp];
    pc = stack[sp + 1];
    sp += 2;
    return r0;
}

