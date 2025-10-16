#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

const int maxn = (1 << 22) + 5;
const int maxm = (1 << 17) + 5;
const int p = 998244353;

int n, m, k, hsh[maxn], fac[maxm], ifac[maxm];

int read()
{
    int res = 0, ch = getchar();
    for (; !isdigit(ch); ch = getchar())
        ;
    for (; isdigit(ch); ch = getchar())
        res = (res << 3) + (res << 1) + (ch & 15);
    return res;
}

int qpow(int x, int y)
{
    int res = 1;
    while (y)
    {
        if (y & 1)
            res = (i64)res * x % p;
        x = (i64)x * x % p;
        y >>= 1;
    }
    return res;
}

int add(int x, int y)
{
    return x + y >= p ? x + y - p : x + y;
}

int sub(int x, int y)
{
    return x >= y ? x - y : x - y + p;
}

int C(int n, int m)
{
    if (n < m)
        return 0;
    return (i64)fac[n] * ifac[m] % p * ifac[n - m] % p;
}

int main()
{
    n = read(), m = read(), k = read();
    for (int i = 1; i <= m; ++i)
        ++hsh[read()];
    fac[0] = 1;
    for (int i = 1; i <= m; ++i)
        fac[i] = (i64)fac[i - 1] * i % p;
    ifac[m] = qpow(fac[m], p - 2);
    for (int i = m; i >= 1; --i)
        ifac[i - 1] = (i64)ifac[i] * i % p;
    for (int i = 0; i < n; ++i)
    {
        for (int s = 0; s < 1 << n; ++s)
        {
            if (s & 1 << i)
                hsh[s] += hsh[s ^ 1 << i];
        }
    }
    for (int i = 0; i < 1 << n; ++i)
    {
        int now = 0;
        for (int j = 1; j <= k; ++j)
            now = add(now, C(hsh[i], j));
        hsh[i] = now;
    }
    for (int i = 0; i < n; ++i)
    {
        for (int s = 0; s < 1 << n; ++s)
        {
            if (s & 1 << i)
                hsh[s] = sub(hsh[s], hsh[s ^ 1 << i]);
        }
    }
    printf("%d\n", hsh[(1 << n) - 1]);
    return 0;
}