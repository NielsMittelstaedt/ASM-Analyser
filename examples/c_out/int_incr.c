#include <stdio.h>
char i;
char *sp = &i;
char *fp = &i;
int counter = 0;

int f(int r3)
{
    int r0;

    sp += -4;
    *sp = fp;
    fp = sp + 0;
    sp = sp - 12;
    *(fp+(-8)) = r0;
    r3 = *(fp+(-8));
    r3 = r3 + 1;
    r0 = r3;
    sp = fp + 0;
    fp = *sp;
    sp += 4;
    counter += 10;
    return r0;
}

float g(float r0)
{
    float r3;
    int r1;

    sp -= 4;
    *sp = fp;
    fp = sp + 4;
    sp = sp - 8;
    *(fp+(-8)) = r0;
    r1 = 1065353216;
    r0 = *(fp+(-8));
    r0 = __aeabi_fadd(r0);
    r3 = r0;
    r0 = r3;
    sp = fp - 4;
    fp = *sp;
    sp += 4;
    counter += 11;
    return r0;
}

int main()
{
    int r3;
    int r0;

    sp -= 4;
    *sp = fp;
    fp = sp + 4;
    r0 = 2;
    r0 = f(r0);
    r3 = 0;
    r0 = r3;
    fp = *sp;
    sp += 4;
    counter += 7;
    return r0;
}

