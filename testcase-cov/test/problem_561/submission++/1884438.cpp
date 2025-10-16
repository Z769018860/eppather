#include <iostream>
#include <cstdio>
#include <algorithm>
#include <unordered_map>
#define int long long
using namespace std;
const int maxn = 1e6 + 5, mod = 998244353;
int n, m, q, p, cnt, x, k[maxn], s[maxn], prime[55], fb[maxn], sum, fnum;
unordered_map <int, int> f, mp, b, g, ans;
int fpow(int x, int y) {
    int s = x;
    x = 1;

    while (y) {
        if (y & 1)
            x = x * s % mod;

        s = s * s % mod;
        y >>= 1;
    }

    return x;
}
void dfs(int i, int val) { 
    if (i > cnt) {
        s[++sum] = val;
        return ;
    }

    while (val <= n) {
        dfs(i + 1, val);
        val *= prime[i];
    }
}
signed main() {
    scanf("%lld%lld%lld", &n, &m, &q);

    for (int i = 1; i <= m; ++i) {
        scanf("%lld%lld", &p, &x);

        if (!b[p]) {
            int num = p;

            for (int j = 1; j <= cnt; ++j) 
                while (num % prime[j] == 0)
                    num /= prime[j];

            for (int j = 2; j * j <= n && num != 1; ++j) 
                if (num % j == 0) {
                    prime[++cnt] = j; 

                    while (num % j == 0)
                        num /= j;
                }

            if (num != 1)
                prime[++cnt] = num;
        }

        b[p] = (b[p] + x) % mod;
    }

    for (int i = 1; i <= q; ++i) {
        scanf("%lld", &k[i]);
        int num = k[i];

        for (int j = 1; j <= cnt; ++j)
            while (num % prime[j] == 0)
                num /= prime[j];

        for (int j = 2; j * j <= n && num != 1; ++j)
            if (num % j == 0) {
                prime[++cnt] = j;

                while (num % j == 0)
                    num /= j;
            }

        if (num != 1)
            prime[++cnt] = num; 
    }

    dfs(1, 1);

    for (auto num = b.begin(); num != b.end(); ++num) 
        num->second = num->second * fpow(num->first, mod - 2) % mod; 

    sort(s + 1, s + sum + 1);

    for (int i = 1; i * i <= n; ++i) { 
        fb[++fnum] = i;

        if (i != n / i)
            fb[++fnum] = n / i;
    }

    sort(fb + 1, fb + fnum + 1);

    for (int i = 1; i <= fnum; ++i) {
        int num = fb[i];
        f[num] = num * (num + 1) % mod * (2 * num + 1) % mod * fpow(6,
                 mod - 2) % mod; 
    }

    for (int i = 1; i <= cnt; ++i)
        for (int j = fnum; j >= 1; --j) {
            int num = fb[j];
            f[num] = (f[num] - (f[num / prime[i]] * prime[i] % mod * prime[i] % mod) + mod) % mod;
        }

    for (int i = 1; i <= sum; ++i)
        g[s[i]] = b[s[i]]; 

    for (int i = 1; i <= cnt; ++i)
        for (int j = 1; j <= sum; ++j) { 
            int num = s[j];

            if (num % prime[i] == 0)
                g[num] = (g[num] + g[num / prime[i]]) % mod; 
        }

    for (int i = 1; i <= sum; ++i) {
        int num = s[i];
        ans[num] = num * num % mod * f[n / num] % mod * g[num] % mod;
    }

    for (int i = 1; i <= cnt; ++i)
        for (int j = sum; j >= 1; --j)
            if (1ll * s[j]*prime[i] <= n)
                ans[s[j]] = (ans[s[j]] + ans[s[j] * prime[i]]) % mod;

    for (int i = 1; i <= q; ++i)
        printf("%lld\n", ans[k[i]]*fpow(k[i], mod - 2) % mod);

    fclose(stdin);
    fclose(stdout);
    return 0;
}