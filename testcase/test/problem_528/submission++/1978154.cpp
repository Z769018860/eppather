#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

const int maxn = 3162280;
const int p = 998244353;

i64 n, m;

int ans, tot, pri[maxn];

bool vis[maxn];

void sieve(int n)
{
    for (int i = 2; i <= n; ++i)
    {
        if (!vis[i])
            pri[++tot] = i;
        for (int j = 1; j <= tot && i * pri[j] <= n; ++j)
        {
            vis[i * pri[j]] = 1;
            if (i % pri[j] == 0)
                break;
        }
    }
}

void dfs(int step, i64 n, i64 m, int w)
{
    if (step > tot || (i64)pri[step] * pri[step] > n)
    {
        ans = (ans + (n % p) * (m % p) * w) % p;
        return;
    }
    dfs(step + 1, n, m, w);
    dfs(step + 1, n / pri[step] / pri[step], m / pri[step] / pri[step], -w);
}

int main()
{
    scanf("%lld%lld", &n, &m);
    if (n > m)
        swap(n, m);
    sieve(sqrt(n));
    dfs(1, n, m, 1);
    printf("%d\n", (ans + p) % p);
    return 0;
}