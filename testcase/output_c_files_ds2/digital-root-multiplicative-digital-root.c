void _mdr(int *rmdr, int *rmp, long long n)
{
    int r[5];
    r[0] = n ? 1 : 0;
    for (; n; n = n / 10)
    {
        r[0] = r[0] * (n % 10);
    }
    *rmp = *rmp + 1;
    if (r[0] >= 10)
    {
        _mdr(rmdr, rmp, r[0]);
    }
    else
    {
        *rmdr = r[0];
    }
    return;
}

void mdr(int *rmdr, int *rmp, long long n)
{
    *rmp = 0;
    _mdr(rmdr, rmp, n);
    return;
}
