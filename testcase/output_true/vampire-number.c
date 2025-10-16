int fangs(int x, int f[16], int tens[20])
{
    int n = 0;
    int nd = 0;
    int x1 = x;
    for (nd = 0; x1 != 0; nd = nd + 1)
    {
        x1 = x1 / 10;
    }
    if ((nd & 1) != 0)
    {
        return 0;
    }
    nd = nd / 2;
    
    int lo = 0;
    int hi = 0;
    int temp1 = tens[nd];
    int temp2 = tens[nd - 1];
    if (temp2 > ((x + temp1 - 2) / (temp1 - 1)))
    {
        lo = temp2;
    }
    else
    {
        lo = (x + temp1 - 2) / (temp1 - 1);
    }
    
    int sqrt_x = 0;
    for (sqrt_x = 0; sqrt_x * sqrt_x <= x; sqrt_x = sqrt_x + 1) {}
    sqrt_x = sqrt_x - 1;
    
    if ((x / lo) < sqrt_x)
    {
        hi = x / lo;
    }
    else
    {
        hi = sqrt_x;
    }
    
    int t = 0;
    int x2 = x;
    while (x2 != 0)
    {
        t = t + (1 << ((x2 % 10) * 6));
        x2 = x2 / 10;
    }
    
    for (int a = lo; a <= hi; a = a + 1)
    {
        int b = x / a;
        if (a * b == x && ((a % 10) != 0 || (b % 10) != 0))
        {
            int t_a = 0;
            int a1 = a;
            while (a1 != 0)
            {
                t_a = t_a + (1 << ((a1 % 10) * 6));
                a1 = a1 / 10;
            }
            
            int t_b = 0;
            int b1 = b;
            while (b1 != 0)
            {
                t_b = t_b + (1 << ((b1 % 10) * 6));
                b1 = b1 / 10;
            }
            
            if (t == t_a + t_b)
            {
                f[n] = a;
                n = n + 1;
            }
        }
    }
    return n;
}

void show_fangs(int x, int f[16], int cnt)
{
    int x_arr[5] = {x, 0, 0, 0, 0};
    int f_arr[5][16] = {{0}};
    for (int i = 0; i < 16; i = i + 1)
    {
        f_arr[0][i] = f[i];
    }
    
    int i = 0;
    for (i = 0; i < cnt; i = i + 1)
    {
        int temp = x_arr[0] / f_arr[0][i];
    }
    return;
}
