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
        int q = 2;
        for (; q * q <= p; q = q + 1)
        {
            if (p % q == 0)
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
    int S = 2;
    int p = 2;
    int ofs;
    int bit = -1;
    if (n < 256 * 2)
    {
        ofs = n / 2;
        bit = 1 << ((n & (2 - 1)) >> 1);
        if (cache[ofs] & bit)
        {
            return 1;
        }
    }
    do
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
    } while (p);
    if (bit != -1)
    {
        cache[ofs] = cache[ofs] | bit;
    }
    return 1;
}

int decompose(int n, int out[5])
{
    int i = 0;
    int p = 2;
    while (n > p * p)
    {
        while (n % p == 0)
        {
            out[i] = p;
            i = i + 1;
            n = n / p;
        }
        p = next_prime(p);
        if (!p)
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

void combined_function(int n, int out[5])
{
    int p = 2;
    if (p == 2)
    {
        p = 3;
    }
    p = p + 2;
    for (; p > 1; p = p + 2)
    {
        int is_p_prime = 1;
        int q = 2;
        for (; q * q <= p; q = q + 1)
        {
            if (p % q == 0)
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
        p = 0;
    }
    int cache[256] = {0};
    int S = 2;
    int ofs;
    int bit = -1;
    if (n < 256 * 2)
    {
        ofs = n / 2;
        bit = 1 << ((n & (2 - 1)) >> 1);
        if (cache[ofs] & bit)
        {
            return;
        }
    }
    do
    {
        if (n % p == 0)
        {
            return;
        }
        if (p * p > n)
        {
            break;
        }
        p = next_prime(p);
    } while (p);
    if (bit != -1)
    {
        cache[ofs] = cache[ofs] | bit;
    }
    int i = 0;
    p = 2;
    while (n > p * p)
    {
        while (n % p == 0)
        {
            out[i] = p;
            i = i + 1;
            n = n / p;
        }
        p = next_prime(p);
        if (!p)
        {
            break;
        }
    }
    if (n > 1)
    {
        out[i] = n;
        i = i + 1;
    }
    return;
}
