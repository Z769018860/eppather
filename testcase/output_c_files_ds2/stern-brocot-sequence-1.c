int f(int n)
{
    if (n < 2)
    {
        return n;
    }
    else
    {
        if ((n & 1) != 0)
        {
            return f(n / 2) + f(n / 2 + 1);
        }
        else
        {
            return f(n / 2);
        }
    }
}

int gcd(int a, int b)
{
    if (a != 0)
    {
        if (a < b)
        {
            return gcd(b % a, a);
        }
        else
        {
            return gcd(a % b, b);
        }
    }
    else
    {
        return b;
    }
}

void find(int from, int to)
{
    int n[5];
    int found[5];
    found[0] = 0;
    n[0] = from;
    for (; n[0] <= to; n[0] = n[0] + 1)
    {
        int i;
        for (i = 1; found[0] == 0; i = i + 1)
        {
            if (f(i) == n[0])
            {
                found[0] = i;
            }
        }
        found[0] = 0;
    }
    return;
}

void combined()
{
    int n[5];
    for (n[0] = 1; n[0] < 16; n[0] = n[0] + 1)
    {
        f(n[0]);
    }
    find(1, 10);
    find(100, 0);
    for (n[0] = 1; n[0] < 1000 && gcd(f(n[0]), f(n[0] + 1)) == 1; n[0] = n[0] + 1)
    {
    }
    return;
}
