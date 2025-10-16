#include <iostream>
#include <map>

const int mod = 998244353, N = 3e3 + 2;

int tot = 0;

std::pair<int, int> pt[N];
std::map<int, int> app;
long long frc[N];

int gtpw(int a, int b)
{
    int res = 1;
    for (; b; b >>= 1, a = 1ll * a * a % mod)
        if (b & 1) res = 1ll * a * res % mod;
    return res;
}

void add()
{
    int x, y; scanf("%d%d", &x, &y);
    frc[ ++ tot] = 1;
    pt[tot] = {x, y};
    for (int i = 1; i < tot; ++ i)
    {
        (frc[i] *= (pt[i].first - x)) %= mod;
        (frc[tot] *= (x - pt[i].first)) %= mod;
    }
    app[x] = y;
}

int solve()
{
    int k; scanf("%d", &k);
    if (app.count(k)) return app[k];
    long long tmp = 1;
    for (int i = 1; i <= tot; ++ i)
        (tmp *= (k - pt[i].first)) %= mod;
    long long res = 0;
    for (int i = 1; i <= tot; ++ i)
        res += 1ll * pt[i].second * gtpw(frc[i], mod - 2) % mod * gtpw(k - pt[i].first, mod - 2) % mod;
    return (res % mod * tmp % mod + mod) % mod;
}

int main()
{
    int n; scanf("%d", &n);
    while (n -- )
    {
        int opt; scanf("%d", &opt);
        if (opt == 1) add();
        else printf("%d\n" ,solve());
    }

    return 0;
}