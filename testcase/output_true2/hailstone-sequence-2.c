int hailstone(int n, int cs, int cache[10000000])
{
    int x[5];
    if (n == 1)
    {
        x[0] = 1;
        return x[0];
    }
    if (n < cs)
    {
        if (cache[n] != 0)
        {
            x[0] = cache[n];
            return x[0];
        }
    }
    
    if ((n & 1) != 0)
    {
        x[0] = 3 * n + 1;
    }
    else
    {
        x[0] = n / 2;
    }
    x[1] = hailstone(x[0], cs, cache);
    x[2] = 1 + x[1];
    
    if (n < cs)
    {
        cache[n] = x[2];
    }
    x[0] = x[2];
    return x[0];
}

int find_max_hailstone(int n, int cs, int cache[10000000])
{
    int i[5];
    int l[5];
    int max[5];
    int mi[5];
    max[0] = 0;
    mi[0] = 0;
    
    for (i[0] = 1; i[0] < n; i[0] = i[0] + 1)
    {
        l[0] = hailstone(i[0], cs, cache);
        if (l[0] > max[0])
        {
            max[0] = l[0];
            mi[0] = i[0];
        }
    }
    return mi[0];
}

void combined_function(int n, int cs, int cache[10000000])
{
    int mi[5];
    mi[0] = find_max_hailstone(n, cs, cache);
    return;
}
