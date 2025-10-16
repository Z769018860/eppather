int kprime(int n, int k)
{
    int p;
    int f;
    f = 0;
    for (p = 2; f < k && p * p <= n; p = p + 1)
    {
        while (0 == n % p)
        {
            n = n / p;
            f = f + 1;
        }
    }
    if (n > 1)
    {
        return (f + 1) == k;
    }
    else
    {
        return f == k;
    }
    return;
}
