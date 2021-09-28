struct x {
   int a;
};

struct x f(struct x a)
{
    a.a = 1;
    return a;
}