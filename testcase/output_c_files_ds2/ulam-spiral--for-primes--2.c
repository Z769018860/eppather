int isprime(int n)
{
    int p[5];
    for (p[0] = 2; p[0] * p[0] <= n; p[0] = p[0] + 1)
    {
        if (n % p[0] == 0)
        {
            return 0;
        }
    }
    return n > 2;
}

int spiral(int w, int h, int x, int y)
{
    if (y != 0)
    {
        return w + spiral(h - 1, w, y - 1, w - x - 1);
    }
    else
    {
        return x;
    }
}

void combined(int w, int h, int s)
{
    int i[5];
    int j[5];
    int result[5];
    for (i[0] = 0; i[0] < 5; i[0] = i[0] + 1)
    {
        for (j[0] = 0; j[0] < 5; j[0] = j[0] + 1)
        {
            result[0] = w * h + s - 1 - spiral(w, h, j[0], i[0]);
            result[1] = isprime(result[0]);
            result[2] = result[1] != 0 ? 1 : 0;
        }
    }
    return;
}
