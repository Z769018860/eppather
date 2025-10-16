int next_prime(int p)
{
    if (p == 2)
    {
        return 3;
    }
    p = p + 2;
    for (; p > 1; p = p + 2)
    {
        int is_p_prime = 1;
        int n = p;
        int i;
        for (i = 2; i * i <= n; i = i + 1)
        {
            if (n % i == 0)
            {
                is_p_prime = 0;
                break;
            }
        }
        if (is_p_prime)
        {
            break;
        }
    }
    if (p == 1)
    {
        return 0;
    }
    return p;
}

int is_prime(int n)
{
    int cache[256] = {0};
    int S = sizeof(int) * 2;
    int p = 2;
    int ofs;
    int bit = -1;
    if (n < 256 * S)
    {
        ofs = n / S;
        bit = 1 << ((n & (S - 1)) >> 1);
        if (cache[ofs] & bit)
        {
            return 1;
        }
    }
    for (;;)
    {
        if (n % p == 0)
        {
            return 0;
        }
        if (p * p > n)
        {
            break;
        }
        p = next_prime(p);
        if (p == 0)
        {
            break;
        }
    }
    if (bit != -1)
    {
        cache[ofs] = cache[ofs] | bit;
    }
    return 1;
}

int decompose(int n, int out[100])
{
    int i = 0;
    int p = 2;
    for (; n > p * p;)
    {
        for (; n % p == 0;)
        {
            out[i] = p;
            i = i + 1;
            n = n / p;
        }
        p = next_prime(p);
        if (p == 0)
        {
            break;
        }
    }
    if (n > 1)
    {
        out[i] = n;
        i = i + 1;
    }
    return i;
}

void main()
{
    return;
}
