int kprime(int n, int k)
{
    int p;
    int f[5];
    f[0] = 0;
    for (p = 2; f[0] < k && p * p <= n; p = p + 1)
    {
        while (0 == n % p)
        {
            n = n / p;
            f[0] = f[0] + 1;
        }
    }
    if (n > 1)
    {
        f[0] = f[0] + 1;
    }
    if (f[0] == k)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    return;
}
