void rat_approx(int f_int_part, int f_frac_part, int md, int* num, int* denom)
{
    int a;
    int h[3] = {0, 1, 0};
    int k[3] = {1, 0, 0};
    int x;
    int d;
    int n = 1;
    int i;
    int neg = 0;
    int f = f_int_part * 1000000 + f_frac_part;

    if (md <= 1)
    {
        *denom = 1;
        *num = f_int_part;
        return;
    }

    if (f < 0)
    {
        neg = 1;
        f = -f;
    }

    while (f != (f / 1000000) * 1000000)
    {
        n = n * 2;
        f = f * 2;
    }
    d = f;

    for (i = 0; i < 64; i = i + 1)
    {
        a = n != 0 ? d / n : 0;
        if (i != 0 && a == 0)
        {
            break;
        }

        x = d;
        d = n;
        n = x % n;

        x = a;
        if (k[1] * a + k[0] >= md)
        {
            x = (md - k[0]) / k[1];
            if (x * 2 >= a || k[1] >= md)
            {
                i = 65;
            }
            else
            {
                break;
            }
        }

        h[2] = x * h[1] + h[0];
        h[0] = h[1];
        h[1] = h[2];
        k[2] = x * k[1] + k[0];
        k[0] = k[1];
        k[1] = k[2];
    }
    *denom = k[1];
    *num = neg != 0 ? -h[1] : h[1];
    return;
}
