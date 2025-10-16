#include<stdio.h>
long long p = 998244352;
long long stt(long long a, long long b, long long mod);
long long stt(long long a, long long b, long long mod)
{
    long long res = 1;
    a = a % mod;
    while (b)
    {
        if (b & 1)res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
int main()
{
    long long x, n, c;
    scanf("%lld %lld", &x, &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%lld", &c);
        printf("%lld ", stt(x, c, p));

    }
    return 0;
}
