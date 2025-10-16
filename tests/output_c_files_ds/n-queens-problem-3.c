void solve(int n)
{
    int cnt = 0;
    unsigned int full = 0;
    unsigned int bits = 0;
    unsigned int pos = 0;
    unsigned int d = 0;
    unsigned int e = 0;
    unsigned int b0 = 0;
    unsigned int b1 = 0;
    unsigned int l[32] = {0};
    unsigned int r[32] = {0};
    unsigned int c[32] = {0};
    unsigned int mm[33] = {0};
    unsigned int m = 0;
    
    full = -(int)(1 << (32 - n));
    n = n - 3;
    
    for (b0 = 1U << (32 - n - 3); b0 != 0; b0 = b0 << 1)
    {
        for (b1 = b0 << 2; b1 != 0; b1 = b1 << 1)
        {
            d = n;
            c[n] = b0 | b1;
            l[n] = (b0 << 2) | (b1 << 1);
            r[n] = (b0 >> 2) | (b1 >> 1);
            bits = full & ~(l[n] | r[n] | c[n]);
            m = 1;
            mm[m] = bits;
            
            while (bits != 0)
            {
                while (d != 0)
                {
                    pos = -(int)bits & bits;
                    
                    if ((bits = bits & ~pos) != 0)
                    {
                        m = m + 1;
                        mm[m] = bits | d;
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
                        cnt = cnt + 1;
                        break;
                    }
                }
                d = (bits = mm[m]) & 31U;
                bits = bits & ~31U;
                m = m - 1;
            }
        }
    }
    return;
}
