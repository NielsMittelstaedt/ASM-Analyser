int f(int n)
{
    int count, sum = 0;

    for (count = 1; count <= n; ++count)
    {
        sum += count;
    }

    return sum;
}

int main()
{
    f(5);
    return 0;
}