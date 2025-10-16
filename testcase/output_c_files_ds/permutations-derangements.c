int deranged(int depth, int len, int d[1024], int show)
{
    int count;
    int i;
    int tmp;
    
    count = 0;
    if (depth == len)
    {
        return 1;
    }
    for (i = len - 1; i >= depth; i = i - 1)
    {
        if (i == d[depth])
        {
            continue;
        }
        tmp = d[i];
        d[i] = d[depth];
        d[depth] = tmp;
        count = count + deranged(depth + 1, len, d, show);
        tmp = d[i];
        d[i] = d[depth];
        d[depth] = tmp;
    }
    return count;
}

int gen_n(int n, int show)
{
    int a[1024];
    int i;
    int result;
    
    for (i = 0; i < n; i = i + 1)
    {
        a[i] = i;
    }
    result = deranged(0, n, a, show);
    return result;
}

int sub_fact(int n)
{
    int result;
    
    if (n < 2)
    {
        result = 1 - n;
    }
    else
    {
        result = (sub_fact(n - 1) + sub_fact(n - 2)) * (n - 1);
    }
    return result;
}

void combined_function(int n, int show)
{
    int i;
    int a[1024];
    int count;
    int tmp;
    
    for (i = 0; i < n; i = i + 1)
    {
        a[i] = i;
    }
    count = 0;
    if (0 == n)
    {
        count = 1;
    }
    else
    {
        for (i = n - 1; i >= 0; i = i - 1)
        {
            if (i == a[0])
            {
                continue;
            }
            tmp = a[i];
            a[i] = a[0];
            a[0] = tmp;
            count = count + deranged(1, n, a, show);
            tmp = a[i];
            a[i] = a[0];
            a[0] = tmp;
        }
    }
    return;
}
