int self_desc(unsigned long long xx)
{
    int d;
    int x;
    int cnt[10];
    int dig[10];
    int i;
    for (i = 0; i < 10; i = i + 1)
    {
        cnt[i] = 0;
        dig[i] = 0;
    }
    d = 0;
    for (d = 0; xx > 4294967295; d = d + 1)
    {
        dig[d] = xx % 10;
        cnt[dig[d]] = cnt[dig[d]] + 1;
        xx = xx / 10;
    }
    x = xx;
    for (x = xx; x != 0; x = x / 10)
    {
        dig[d] = x % 10;
        cnt[dig[d]] = cnt[dig[d]] + 1;
        d = d + 1;
    }
    x = 0;
    for (; d != -1; d = d - 1)
    {
        if (dig[x] != cnt[d])
        {
            break;
        }
        x = x + 1;
    }
    if (d == -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    return;
}
