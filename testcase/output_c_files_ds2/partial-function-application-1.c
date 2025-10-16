void partial(int fin, int x[5], int y[5], int idx[5], int i[5], int j[5], int k[5], int l[5], int m[5], int n[5], int o[5], int p[5], int q[5], int r[5], int s[5], int t[5], int u[5], int v[5], int w[5], int z[5])
{
    for (i[0] = 0; i[0] < 5; i[0] = i[0] + 1)
    {
        if (fin == 0)
        {
            x[i[0]] = x[i[0]] * x[i[0]];
        }
        else
        {
            x[i[0]] = x[i[0]] + x[i[0]];
        }
    }
    for (j[0] = 0; j[0] < 5; j[0] = j[0] + 1)
    {
        if (fin == 0)
        {
            y[j[0]] = y[j[0]] * y[j[0]];
        }
        else
        {
            y[j[0]] = y[j[0]] + y[j[0]];
        }
    }
    return;
}
