#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

const int maxn = 3162280;
const int p = 998244353;

i64 n, m;

int s, ans, tot, mu[maxn], pri[maxn];

bool vis[maxn];

int main()
{
    scanf("%lld%lld", &n, &m);
    if (n > m)
        swap(n, m);
    s = sqrt(n);
    mu[1] = 1;
    for (int i = 2; i <= s; ++i)
    {
        if (!vis[i])
            pri[++tot] = i, mu[i] = -1;
        for (int j = 1; j <= tot && i * pri[j] <= s; ++j)
        {
            vis[i * pri[j]] = 1;
            if (i % pri[j] == 0)
                break;
            mu[i * pri[j]] = -mu[i];
        }
    }
    for (int i = 1; i <= s; ++i)
    {
        if (mu[i])
            ans = (ans + (i64)(n / i / i % p) * (m / i / i % p) * mu[i]) % p;
    }
    printf("%d\n", (ans + p) % p);
    return 0;
}