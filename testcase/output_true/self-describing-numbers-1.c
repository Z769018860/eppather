int self_desc(int xx, int n1, int n2)
{
    int d[5] = {0};
    int x[5] = {0};
    int cnt[10] = {0};
    int dig[10] = {0};
    int i;

    for (i = 0; i < 5; i = i + 1)
    {
        if (xx > n1)
        {
            dig[d[0]] = xx % 10;
            cnt[dig[d[0]]] = cnt[dig[d[0]]] + 1;
            d[0] = d[0] + 1;
            xx = xx / 10;
        }
    }

    x[0] = xx;
    for (i = 0; i < 5; i = i + 1)
    {
        if (x[0])
        {
            dig[d[0]] = x[0] % 10;
            cnt[dig[d[0]]] = cnt[dig[d[0]]] + 1;
            d[0] = d[0] + 1;
            x[0] = x[0] / 10;
        }
    }

    x[0] = 0;
    for (i = 0; i < 5; i = i + 1)
    {
        if (d[0])
        {
            d[0] = d[0] - 1;
            if (dig[x[0]] == cnt[d[0]])
            {
                x[0] = x[0] + 1;
            }
        }
    }

    if (d[0] == -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    return;
}
