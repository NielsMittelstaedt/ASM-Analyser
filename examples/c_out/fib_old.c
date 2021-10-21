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
void* label;

reg r6;
reg r4;
reg r5;
reg r0;

reg fib()
{
    sp -= 4;
    stack[sp] = r4.i;
    stack[sp] = r5.i;
    stack[sp] = r6.i;
    stack[sp] = lr.i;
    r4.i = r0.i;
    cond_reg = r0.i > 1 ? 1 : (r0.i < 1 ? -1 : 0);
    if (cond_reg <= 0)
    {
        r4.i = stack[sp];
        r5.i = stack[sp];
        r6.i = stack[sp];
        pc.i = stack[sp];
        sp += 4;
        goto *label;
    }
    r0.i = r0.i - 1;
    label = &&lbl1;
    r0.i = fib(r0).i;
    lbl1:
    r5.i = r0.i;
    r0.i = r4.i - 2;
    label = &&lbl2;
    r0.i = fib(r0).i;
    lbl2:
    r0.i = r5.i + r0.i;
    r4.i = stack[sp];
    r5.i = stack[sp];
    r6.i = stack[sp];
    pc.i = stack[sp];
    sp += 4;
    return r0;
}

reg main()
{
    sp -= 2;
    stack[sp] = r4.i;
    stack[sp] = lr.i;
    r0.i = 3;
    label = &&lbl3;
    r0.i = fib(r0).i;
    printf("%d",r0.i);
    lbl3:
    r0.i = 0;
    r4.i = stack[sp];
    pc.i = stack[sp];
    sp += 2;
    return r0;
}

