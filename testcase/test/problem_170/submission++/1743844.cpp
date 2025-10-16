#include <bits/stdc++.h>
using namespace std;
const long long p = 1000391835649;
long long ig, W[2097152], iW[2097152], fac[2097152], ifac[2097152], inv[2097152], R[2097152], T, N, B, d, F[2097152], preS[2097152], sufS[2097152], invS, f[2097152], g[2097152], G[2097152];
inline long long mul(long long x, long long y)
{
    return ((((x >> 20) * y % p) << 20) + (x & 1048575) * y) % p;
}
inline long long add(long long x, long long y)
{
    return (x + y) >= p ? x + y - p : x + y;
}
inline long long ksm(long long a, long long k)
{
    long long ans = 1;
    while (k)
	{
        if (k & 1)
            ans = mul(ans, a);
        a = mul(a, a);
        k >>= 1;
    }
    return ans;
}
inline void NTT(long long d[], bool flg, long long n0)
{
    long long x = 1, len = 0;
    while (x < n0)
    {
        x <<= 1;
		len++;
	}
    for (long long i = 0; i < x; i++)
	{
        R[i] = (R[i >> 1] >> 1) | ((i & 1) << (len - 1));
        if (i < R[i])
            swap(d[i], d[R[i]]);
    }
    for (long long i = 1, l = 2097152 / (i << 1); i < x; i <<= 1, l >>= 1)
        for (long long j = 0; j < x; j += (i << 1))
            for (long long k = 0, u = 0; k < i; k++, u += l)
			{
                long long a0 = d[j | k], a1 = mul((flg ? iW[u] : W[u]), d[j | i | k]);
                d[j | k] = add(a0, a1);
                d[j | i | k] = add(a0, -a1 + p);
            }
    if (flg)
	{
        long long invx = ksm(x, p - 2);
        for (long long i = 0; i < x; i++)
            d[i] = mul(d[i], invx);
    }
}
inline void ADD1()
{
    for (long long k = 0; k <= d; k++)
        F[k] = mul(F[k], k * B + d + 1);
    F[d + 1] = 1;
    for (long long i = 1; i <= d + 1; i++)
        F[d + 1] = mul(F[d + 1], (d + 1) * B + i);
    d++;
}
inline void LIP(long long h[], long long ans[], long long k)
{
    long long x = 1;
    while (x < 2 * (d + 1))
        x <<= 1;
    for (long long i = 0; i < x; i++)
        f[i] = g[i] = 0;
    for (long long i = 0; i <= 2 * d; i++)
        g[i] = add(add(i, k), -d + p);
    preS[0] = g[0];
    for (long long i = 1; i <= 2 * d; i++)
        preS[i] = mul(preS[i - 1], g[i]);
    sufS[2 * d] = g[2 * d];
    for (long long i = 2 * d - 1; ~i; i--)
        sufS[i] = mul(sufS[i + 1], g[i]);
    invS = ksm(preS[2 * d], p - 2);
    for (long long i = 0; i <= 2 * d; i++)
	{
        g[i] = invS;
        if (i)
            g[i] = mul(g[i], preS[i - 1]);
        if (i != 2 * d)
            g[i] = mul(g[i], sufS[i + 1]);
    }
    for (long long i = 0; i <= d; i++)
	{
        f[i] = mul(mul(h[i], ifac[i]), ifac[d - i]);

        if ((d - i) & 1)
            f[i] = add(p, -f[i]);
    }
    NTT(f, 0, x);
    NTT(g, 0, x);
    for (long long i = 0; i < x; i++)
        ans[i] = mul(f[i], g[i]);
    NTT(ans, 1, x);
    NTT(g, 1, x);
    long long mul0 = preS[d];
    for (long long i = 0; i <= d; i++)
        ans[i] = mul(ans[i + d], mul0), mul0 = mul(mul(mul0, g[i]), i + 1 + k);
}
inline void MUL2()
{
    if (!d)
        return;
    LIP(F, F + d + 1, d + 1);
    F[2 * d + 1] = 0;
    d <<= 1;
    LIP(F, G, mul(d >> 1, ksm(B, p - 2)));
    for (long long i = 0; i <= d; i++)
        F[i] = mul(F[i], G[i]);
}
signed main()
{
    ig = ksm(7, p - 2);
    long long w = ksm(7, (p - 1) / 2097152), iw = ksm(ig, (p - 1) / 2097152);
    W[0] = iW[0] = 1;
    for (long long i = 1; i < 2097152; i++)
    {
        W[i] = mul(W[i - 1], w);
		iW[i] = mul(iW[i - 1], iw);
	}
    fac[0] = ifac[0] = fac[1] = ifac[1] = inv[1] = 1;
    for (long long i = 2; i < 2097152; i++)
    {
        fac[i] = mul(fac[i - 1], i);
		inv[i] = mul(p - p / i, inv[p % i]);
		ifac[i] = mul(ifac[i - 1], inv[i]);    	
	}
    N = 1000391835648LL;
    B = sqrt(N);
    d = 0;
    F[0] = 1;
    for (long long i = 20; ~i; i--)
	{
        MUL2();
        if ((B >> i) & 1)
            ADD1();
    }
    for (long long i = 1; i <= B; i++)
        F[i] = mul(F[i], F[i - 1]);
    scanf("%lld", &T);
    while (T--)
	{
        scanf("%lld", &N);
        long long k = N / B, ans;
        if (!k)
            ans = 1;
        else ans = F[k - 1];
        for (long long i = k * B + 1; i <= N; i++)
            ans = mul(ans, i);
        printf("%lld\n", ans);
    }
    return 0;
}