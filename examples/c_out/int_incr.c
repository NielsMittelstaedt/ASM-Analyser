#include <stdio.h>
int stack[200];
int sp = 199, fp = 199;
int counter = 0;
int r0;
int r3;

int f()
{
    sp += -1;
    stack[sp] = fp;
    fp = sp + 0;
    sp = sp - 3;
    stack[fp+(-2)] = r0;
    r3 = stack[fp+(-2)];
    r3 = r3 + 1;
    r0 = r3;
    sp = fp + 0;
    fp = stack[sp];
    sp += 1;
    counter += 10;
    return r0;
}

int main()
{
    sp -= 1;
    stack[sp] = fp;
    fp = sp + 1;
    r0 = 2;
    r0 = f(r0);
    printf("%d", r0);
    r3 = 0;
    r0 = r3;
    fp = stack[sp];
    sp += 1;
    counter += 7;
    return r0;
}

