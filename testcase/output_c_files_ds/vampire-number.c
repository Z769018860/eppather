int fangs(int x, int f[16])
{
    int n;
    int nd;
    int temp;
    int nd_half;
    int lo;
    int hi;
    int a;
    int b;
    int t;
    int t_a;
    int t_b;
    int tens[20];
    int i;
    int x_copy;
    int a_copy;
    int b_copy;
    
    tens[0] = 1;
    for (i = 1; i < 20; i = i + 1)
    {
        tens[i] = tens[i - 1] * 10;
    }
    
    nd = 0;
    x_copy = x;
    while (x_copy)
    {
        nd = nd + 1;
        x_copy = x_copy / 10;
    }
    
    if (nd & 1)
    {
        return 0;
    }
    nd_half = nd / 2;
    
    temp = x + tens[nd_half] - 2;
    if (temp < tens[nd_half] - 1)
    {
        lo = tens[nd_half - 1];
    }
    else
    {
        lo = temp / (tens[nd_half] - 1);
    }
    if (tens[nd_half - 1] > lo)
    {
        lo = tens[nd_half - 1];
    }
    
    hi = x / lo;
    temp = 0;
    for (i = 1; i * i <= x; i = i + 1)
    {
        if (i * i == x)
        {
            temp = i;
        }
    }
    if (temp < hi)
    {
        hi = temp;
    }
    
    t = 0;
    x_copy = x;
    while (x_copy)
    {
        t = t + (1 << ((x_copy % 10) * 6));
        x_copy = x_copy / 10;
    }
    
    n = 0;
    for (a = lo; a <= hi; a = a + 1)
    {
        b = x / a;
        if (a * b == x)
        {
            if ((a % 10) || (b % 10))
            {
                t_a = 0;
                a_copy = a;
                while (a_copy)
                {
                    t_a = t_a + (1 << ((a_copy % 10) * 6));
                    a_copy = a_copy / 10;
                }
                t_b = 0;
                b_copy = b;
                while (b_copy)
                {
                    t_b = t_b + (1 << ((b_copy % 10) * 6));
                    b_copy = b_copy / 10;
                }
                if (t == t_a + t_b)
                {
                    f[n] = a;
                    n = n + 1;
                }
            }
        }
    }
    return n;
}
