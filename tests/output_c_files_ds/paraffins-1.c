int rooted[33] = {1, 1, 0};
int unrooted[33] = {1, 1, 0};

int choose(int m, int k)
{
    int i;
    int r;
    if (k == 1)
    {
        return m;
    }
    r = m;
    for (i = 1; i < k; i = i + 1)
    {
        r = r * (m + i) / (i + 1);
    }
    return r;
}

void tree(int br, int n, int cnt, int sum, int l)
{
    int b;
    int c;
    int m;
    int s;
    for (b = br + 1; b <= 4; b = b + 1)
    {
        s = sum + (b - br) * n;
        if (s >= 33)
        {
            return;
        }
        c = choose(rooted[n], b - br) * cnt;
        if (l * 2 < s)
        {
            unrooted[s] = unrooted[s] + c;
        }
        if (b == 4)
        {
            return;
        }
        rooted[s] = rooted[s] + c;
        for (m = n - 1; m > 0; m = m - 1)
        {
            tree(b, m, c, s, l);
        }
    }
    return;
}

void bicenter(int s)
{
    if (s & 1)
    {
        return;
    }
    unrooted[s] = unrooted[s] + rooted[s/2] * (rooted[s/2] + 1) / 2;
    return;
}
