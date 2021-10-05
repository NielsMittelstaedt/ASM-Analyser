#include <stdio.h>
int stack[200];
int sp = 199, fp = 199;
int counter = 0;

int f(int r3)
{
    int r0;

    sp += -4;
    stack[sp] = fp;
    fp = sp + 0;
    sp = sp - 12;
    stack[fp+(-8)] = r0;
    r3 = stack[fp+(-8)];
    r3 = r3 + 1;
    r0 = r3;
    sp = fp + 0;
    fp = stack[sp];
    sp += 4;
    counter += 10;
    return r0;
}

float g(float r0)
{
    float r1;
    float r3;

    sp -= 4;
    stack[sp] = fp;
    fp = sp + 4;
    sp = sp - 8;
    stack[fp+(-8)] = r0;
    r1 = 1.0;
    r0 = stack[fp+(-8)];
    r0 = r0 + r1;
    r3 = r0;
    r0 = r3;
    sp = fp - 4;
    fp = stack[sp];
    sp += 4;
    counter += 11;
    return r0;
}

int main()
{
    int r0;
    int r3;

    sp -= 4;
    stack[sp] = fp;
    fp = sp + 4;
    r0 = 2;
    r0 = f(r0);
    r3 = 0;
    r0 = r3;
    fp = stack[sp];
    sp += 4;
    counter += 7;
    return r0;
}

