int ackermann(int m, int n)
{
    int cache[8388608];
    int idx;
    int res;
    int i;
    for (i = 0; i < 8388608; i = i + 1)
    {
        cache[i] = 0;
    }
    if (m == 0)
    {
        res = n + 1;
        return res;
    }
    if (n >= 1048576)
    {
        idx = 0;
    }
    else
    {
        idx = (m << 20) + n;
        if (cache[idx] != 0)
        {
            return cache[idx];
        }
    }
    if (n == 0)
    {
        res = ackermann(m - 1, 1);
    }
    else
    {
        res = ackermann(m - 1, ackermann(m, n - 1));
    }
    if (idx != 0)
    {
        cache[idx] = res;
    }
    return res;
    return;
}
