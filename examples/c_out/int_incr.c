int f()
{
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

}

int main()
{
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

}

