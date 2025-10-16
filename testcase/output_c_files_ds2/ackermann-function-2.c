int ackermann(int m, int n, int m_bits, int n_bits, int cache[33554432])
{
    int idx;
    int res;
    if (m == 0)
    {
        res = n + 1;
        return res;
    }

    if (n >= 1 << n_bits)
    {
        idx = 0;
    }
    else
    {
        idx = (m << n_bits) + n;
        if (cache[idx] != 0)
        {
            return cache[idx];
        }
    }

    if (n == 0)
    {
        res = ackermann(m - 1, 1, m_bits, n_bits, cache);
    }
    else
    {
        res = ackermann(m - 1, ackermann(m, n - 1, m_bits, n_bits, cache), m_bits, n_bits, cache);
    }

    if (idx != 0)
    {
        cache[idx] = res;
    }
    return res;
}
