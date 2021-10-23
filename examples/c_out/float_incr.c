#include <stdio.h>
#include <stdint.h>

typedef union
{
    int32_t i;
    float f;
} reg;

int32_t stack[200];
int32_t sp = 199, fp = 199;
int32_t cond_reg;
reg lr, pc;

reg r3;
reg r2;
reg r0;
reg r1;

int counter0, counter1, counter2, counter3, counter4, counter5, counter6, counter7;

void dmul()
{
    int64_t op1 = ((int64_t) r1.i) << 32 | ((int64_t) r0.i);
    int64_t op2 = ((int64_t) r3.i) << 32 | ((int64_t) r2.i);
    double result = *(double *)&op1 * *(double *)&op2;
    int64_t result_int64 = *(int64_t *)&result;
    r1.i = (int32_t) (result_int64 >> 32);
    r0.i = (int32_t) result_int64;
}

void ddiv()
{
    int64_t op1 = ((int64_t) r1.i) << 32 | ((int64_t) r0.i);
    int64_t op2 = ((int64_t) r3.i) << 32 | ((int64_t) r2.i);
    double result = *(double *)&op1 / *(double *)&op2;
    int64_t result_int64 = *(int64_t *)&result;
    r1.i = (int32_t) (result_int64 >> 32);
    r0.i = (int32_t) result_int64;
}

void d2f()
{
    int64_t int64_t_val = ((int64_t) r1.i) << 32 | ((int64_t) r0.i);
    double double_val = *(double *)&int64_t_val;
    r0.f = (float) double_val;
}

void f2d()
{
    double double_val = (double) r0.f;
    int64_t int64_t_val = *(int64_t *)&double_val;
    r1.i = (int32_t) (int64_t_val >> 32);
    r0.i = (int32_t) int64_t_val;
}

void dadd()
{
    int64_t op1 = ((int64_t) r1.i) << 32 | ((int64_t) r0.i);
    int64_t op2 = ((int64_t) r3.i) << 32 | ((int64_t) r2.i);
    double result = *(double *)&op1 + *(double *)&op2;
    int64_t result_int64 = *(int64_t *)&result;
    r1.i = (int32_t) (result_int64 >> 32);
    r0.i = (int32_t) result_int64;
}

reg f()
{
    sp -= 2;
    stack[sp+0] = fp;
    stack[sp+1] = lr.i;
    fp = sp + 1;
    sp = sp - 2;
    stack[fp+(-2)] = r0.i;
    r0.i = stack[fp+(-2)];
    f2d();
    counter0 ++;
    r2.i = 0;
    r3.i = 1073741824;
    dadd();
    counter1 ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r2.i;
    r1.i = r3.i;
    r2.i = 0;
    r3.i = 0;
    r3.i = (16400 << 16) | r3.i;
    dmul();
    counter2 ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r2.i;
    r1.i = r3.i;
    r2.i = 0;
    r3.i = 0;
    r3.i = (16408 << 16) | r3.i;
    ddiv();
    counter3 ++;
    r2.i = r0.i;
    r3.i = r1.i;
    r0.i = r2.i;
    r1.i = r3.i;
    d2f();
    counter4 ++;
    r3.i = r0.i;
    r0.i = r3.i;
    sp = fp - 1;
    fp = stack[sp+0];
    pc.i = stack[sp+1];
    sp += 2;
    counter5 ++;
    return r0;
}

reg main()
{
    sp -= 2;
    stack[sp+0] = fp;
    stack[sp+1] = lr.i;
    fp = sp + 1;
    r0.i = 0;
    r0.i = (16512 << 16) | r0.i;
    r0.i = f(r0).i;
    printf("%f\n", r0.f);
    counter6 ++;
    r3.i = 0;
    r0.i = r3.i;
    fp = stack[sp+0];
    pc.i = stack[sp+1];
    sp += 2;
    counter7 ++;
    return r0;
}

