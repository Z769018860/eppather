int semiprime(int n)
{
    int p[5];
    int f[5];
    f[0] = 0;
    for (p[0] = 2; f[0] < 2 && p[0] * p[0] <= n; p[0] = p[0] + 1)
    {
        while (0 == n % p[0])
        {
            n = n / p[0];
            f[0] = f[0] + 1;
        }
    }
    if (f[0] + (n > 1) == 2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    return;
}
