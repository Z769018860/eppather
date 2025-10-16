int isprime(int n)
{
    int p;
    for (p = 2; p * p <= n; p = p + 1)
    {
        if (n % p == 0)
        {
            return 0;
        }
    }
    if (n > 2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
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

void generate_spiral_primes(int w, int h, int s, int output[50][50])
{
    int i;
    int j;
    int value;
    for (i = 0; i < h; i = i + 1)
    {
        for (j = 0; j < w; j = j + 1)
        {
            value = w * h + s - 1 - spiral(w, h, j, i);
            if (isprime(value) != 0)
            {
                output[i][j] = 1;
            }
            else
            {
                output[i][j] = 0;
            }
        }
    }
    return;
}
