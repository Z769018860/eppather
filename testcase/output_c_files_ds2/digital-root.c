int droot(int x[5], int base, int pers[5])
{
    int d[5];
    d[0] = 0;
    if (pers)
    {
        pers[0] = 0;
        for (; x[0] >= base; x[0] = d[0], pers[0] = pers[0] + 1)
        {
            d[0] = 0;
            for (; x[0]; d[0] = d[0] + x[0] % base, x[0] = x[0] / base)
            {
            }
        }
    }
    else
    {
        if (x[0] && !(d[0] = x[0] % (base - 1)))
        {
            d[0] = base - 1;
        }
    }
    return d[0];
}
