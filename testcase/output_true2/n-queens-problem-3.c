void solve(int n)
{
    int cnt[5] = {0};
    int full = -(1 << (32 - n));
    int bits;
    int pos;
    int d;
    int e;
    int b0;
    int b1;
    int l[32];
    int r[32];
    int c[32];
    int mm[33] = {0};
    int m[1];
    n = n - 3;
    for (b0 = 1 << (32 - n - 3); b0 != 0; b0 = b0 << 1)
    {
        for (b1 = b0 << 2; b1 != 0; b1 = b1 << 1)
        {
            d = n;
            c[n] = b0 | b1;
            l[n] = (b0 << 2) | (b1 << 1);
            r[n] = (b0 >> 2) | (b1 >> 1);
            bits = *(m = mm + 1) = full & ~(l[n] | r[n] | c[n]);
            while (bits != 0)
            {
                while (d != 0)
                {
                    pos = -bits & bits;
                    if ((bits = bits & ~pos) != 0)
                    {
                        *m = bits | d;
                        m = m + 1;
                    }
                    e = d;
                    d = d - 1;
                    l[d] = (l[e] | pos) << 1;
                    r[d] = (r[e] | pos) >> 1;
                    c[d] = c[e] | pos;
                    bits = full & ~(l[d] | r[d] | c[d]);
                    if (bits == 0)
                    {
                        break;
                    }
                    if (d == 0)
                    {
                        cnt[0] = cnt[0] + 1;
                        break;
                    }
                }
                d = (bits = *(m = m - 1)) & 31;
                bits = bits & ~31;
            }
        }
    }
    cnt[0] = cnt[0] * 2;
    return;
}
