#include <bits/stdc++.h>
namespace solution
{
    typedef long long i64;
    const i64 INF = 1e15;
    const int MAXN = 1e6 + 5;
    i64 n, q, k;
    i64 s[MAXN];
    i64 a[MAXN];
    i64 max(i64 x, i64 y)
    {
        if (x == -1)
        {
            return y;
        }
        if (y == -1)
        {
            return x;
        }
        return a[x] >= a[y] ? x : y;
    }
    i64 min(i64 x, i64 y)
    {
        if (x == -1)
        {
            return y;
        }
        if (y == -1)
        {
            return x;
        }
        return a[x] <= a[y] ? x : y;
    }
    int main()
    {
        
        
        scanf("%lld", &n);
        for (int i = 1; i <= n; i++)
        {
            scanf("%lld", &s[i]);
        }
        scanf("%lld", &q);
        for (int i = 1; i <= q; i++)
        {
            i64 minpos = -1, maxpos = -1;
            scanf("%lld%lld%lld", &a[0], &a[1], &k);
            if (a[0] == 0 && a[1] == 0)
            {
                printf("%lld %lld\n", s[1], s[1]);
                continue;
            }
            for (int i = 2; i <= 300; i++)
            {
                a[i] = a[i - 1] * k + a[i - 2];
                if (a[i] < -INF)
                {
                    a[i] = -INF;
                }
                if (a[i] > INF)
                {
                    a[i] = INF;
                }
            }
            for (int i = 1; i <= n; i++)
            {
                if (s[i] <= 300)
                {
                    maxpos = max(maxpos, s[i]), minpos = min(minpos, s[i]);
                }
                else
                {
                    if (a[300] > 0)
                    {
                        maxpos = s[n];
                    }
                    else
                    {
                        minpos = s[n];
                    }
                    break;
                }
            }
            printf("%lld %lld\n", maxpos, minpos);
        }
        return 0;
    }
}
int main()
{
    solution::main();
    return 0;
}