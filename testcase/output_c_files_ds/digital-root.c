int droot(long long int x, int base, int *pers)
{
    int d = 0;
    if (pers != 0)
    {
        *pers = 0;
        for (; x >= base; )
        {
            d = 0;
            for (; x != 0; )
            {
                d = d + x % base;
                x = x / base;
            }
            x = d;
            *pers = *pers + 1;
        }
    }
    else
    {
        if (x != 0)
        {
            d = x % (base - 1);
            if (d == 0)
            {
                d = base - 1;
            }
        }
    }
    return d;
}
