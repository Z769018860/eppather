int factorize(int n[5], int f[5][5])
{
    int i[5];
    i[0] = 0;

    {
        int p[5];
        p[0] = 2;
        if (n[0] % p[0] == 0)
        {
            f[i[0]][0] = 1;
            while (n[0] % p[0] == 0)
            {
                f[i[0]][0] = f[i[0]][0] * p[0];
                n[0] = n[0] / p[0];
            }
            i[0] = i[0] + 1;
        }
    }

    {
        int p[5];
        p[0] = 3;
        if (n[0] % p[0] == 0)
        {
            f[i[0]][0] = 1;
            while (n[0] % p[0] == 0)
            {
                f[i[0]][0] = f[i[0]][0] * p[0];
                n[0] = n[0] / p[0];
            }
            i[0] = i[0] + 1;
        }
    }

    {
        int p[5];
        int inc[5];
        p[0] = 5;
        inc[0] = 4;
        for (; p[0] * p[0] <= n[0]; )
        {
            if (n[0] % p[0] == 0)
            {
                f[i[0]][0] = 1;
                while (n[0] % p[0] == 0)
                {
                    f[i[0]][0] = f[i[0]][0] * p[0];
                    n[0] = n[0] / p[0];
                }
                i[0] = i[0] + 1;
            }
            p[0] = p[0] + (inc[0] = 6 - inc[0]);
        }
    }

    if (n[0] > 1)
    {
        int p[5];
        p[0] = n[0];
        if (n[0] % p[0] == 0)
        {
            f[i[0]][0] = 1;
            while (n[0] % p[0] == 0)
            {
                f[i[0]][0] = f[i[0]][0] * p[0];
                n[0] = n[0] / p[0];
            }
            i[0] = i[0] + 1;
        }
    }

    return i[0];
}

int mul_inv(int a[5], int b[5])
{
    int b0[5];
    int t[5];
    int q[5];
    int x0[5];
    int x1[5];
    b0[0] = b[0];
    x0[0] = 0;
    x1[0] = 1;
    if (b[0] == 1)
    {
        return 1;
    }
    while (a[0] > 1)
    {
        q[0] = a[0] / b[0];
        t[0] = b[0];
        b[0] = a[0] % b[0];
        a[0] = t[0];
        t[0] = x0[0];
        x0[0] = x1[0] - q[0] * x0[0];
        x1[0] = t[0];
    }
    if (x1[0] < 0)
    {
        x1[0] = x1[0] + b0[0];
    }
    return x1[0];
}

int kaprekars(int base[5], int top[5], int out[5][5], int max_cnt[5])
{
    int f[5][5];
    int pb[5];
    int len[5];
    int cnt[5];
    cnt[0] = 0;

    {
        int a[5];
        int i[5];
        if (i[0] < len[0])
        {
            a[0] = a[0] * f[i[0]][0];
            i[0] = i[0] + 1;
            a[0] = a[0];
            i[0] = i[0] + 1;
            return;
        }
        {
            int x[5];
            x[0] = a[0] * mul_inv(a, (pb[0] - 1) / a[0]);
            if (x[0] > 1 && x[0] < top[0])
            {
                out[cnt[0]][0] = x[0];
                cnt[0] = cnt[0] + 1;
                if (cnt[0] >= max_cnt[0])
                {
                    return 0;
                }
            }
        }
    }

    out[cnt[0]][0] = 1;
    cnt[0] = cnt[0] + 1;

    for (pb[0] = base[0]; pb[0] <= top[0] * top[0] / base[0]; pb[0] = pb[0] * base[0])
    {
        len[0] = factorize(pb, f);
        if (f[len[0] - 1][0] <= top[0])
        {
            {
                int a[5];
                int i[5];
                a[0] = 1;
                i[0] = 0;
                if (i[0] < len[0])
                {
                    a[0] = a[0] * f[i[0]][0];
                    i[0] = i[0] + 1;
                    a[0] = a[0];
                    i[0] = i[0] + 1;
                    return;
                }
                {
                    int x[5];
                    x[0] = a[0] * mul_inv(a, (pb[0] - 1) / a[0]);
                    if (x[0] > 1 && x[0] < top[0])
                    {
                        out[cnt[0]][0] = x[0];
                        cnt[0] = cnt[0] + 1;
                        if (cnt[0] >= max_cnt[0])
                        {
                            return 0;
                        }
                    }
                }
            }
        }
    }
    return cnt[0];
}

void main()
{
    return;
}
