int deranged(int depth, int len, int d[5], int show)
{
    int i;
    int tmp;
    int count[5];
    count[0] = 0;

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
        count[0] = count[0] + deranged(depth + 1, len, d, show);
        tmp = d[i];
        d[i] = d[depth];
        d[depth] = tmp;
    }
    return count[0];
}

int gen_n(int n, int show)
{
    int i;
    int a[5];
    int count[5];
    count[0] = 0;

    for (i = 0; i < n; i = i + 1)
    {
        a[i] = i;
    }
    count[0] = deranged(0, n, a, show);
    return count[0];
}

int sub_fact(int n)
{
    int result[5];
    if (n < 2)
    {
        result[0] = 1 - n;
    }
    else
    {
        result[0] = (sub_fact(n - 1) + sub_fact(n - 2)) * (n - 1);
    }
    return result[0];
}

void merged_function()
{
    int i;
    int d[5];
    int a[5];
    int count[5];
    int result[5];
    int tmp;
    int n;
    int show;
    int depth;
    int len;

    for (i = 0; i < 5; i = i + 1)
    {
        d[i] = 0;
        a[i] = 0;
        count[i] = 0;
        result[i] = 0;
    }
    tmp = 0;
    n = 0;
    show = 0;
    depth = 0;
    len = 0;

    return;
}
