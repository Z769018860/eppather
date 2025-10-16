#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005, P = 998244353;
int n, m, q;
int p[MAXN], x[MAXN], k[MAXN];
vector<int> fac, s;
int qpow(int a, int b) {
    int ans = 1;
    while (b) {
        if (b & 1) ans = 1ll * ans * a % P;
        a = 1ll * a * a % P;
        b >>= 1;
    }
    return ans;
}
const int INV6 = qpow(6, P - 2);
void dfs(int i, int x) {
    if (i == fac.size())
        s.push_back(x);
    else {
        for (long long k = 1; x * k <= n; k *= fac[i]) {
            dfs(i + 1, x * k);
        }
    }
}
unordered_map<int, int> a, b, c;
int f(int x) {
    x %= P;
    return 1ll * x * (x + 1) % P * (2 * x + 1) % P * INV6 % P;
}
int main() {
    
    scanf("%d%d%d", &n, &m, &q);
    auto factor = [&](int x) {
        for (int i : fac) {
            while (x % i == 0) x /= i;
        }
        if (x != 1) {
            for (int i = 2; i * i <= x; i++) {
                if (x % i == 0) {
                    fac.push_back(i);
                    while (x % i == 0) x /= i;
                }
            }
            if (x != 1) {
                fac.push_back(x);
            }
        }
    };
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &p[i], &x[i]);
        factor(p[i]);
    }
    for (int i = 1; i <= q; i++) {
        scanf("%d", &k[i]);
        factor(k[i]);
    }
    dfs(0, 1);
    for (int i = 1; i <= m; i++) {
        a[p[i]] = (a[p[i]] + x[i]) % P;
    }
    sort(fac.begin(), fac.end());
    sort(s.begin(), s.end());
    for (int x : s) {
        a[x] = 1ll * a[x] * qpow(x, P - 2) % P;
    }
    for (int pri : fac) {
        for (int x : s) if (1ll * x * pri <= n) {
            a[x * pri] = (a[x * pri] + a[x]) % P;
        }
    }
    for (int x : s) {
        int m = n / x;
        if (b.count(m)) continue;
        for (int t = 0; t < (1 << fac.size()); t++) {
            int mul = 1;
            for (int i = 0; i < fac.size(); i++) if (t >> i & 1) {
                if (1ll * mul * fac[i] > m) {
                    mul = 0;
                    break;
                }
                mul *= fac[i];
            }
            if (!mul) continue;
            b[m] = (b[m] + 1ll * ((__builtin_popcount(t) & 1) ? P - 1ll : 1ll) * mul % P * mul % P * f(m / mul)) % P;
        }
    }
    reverse(s.begin(), s.end());
    for (int x : s) {
        c[x] = 1ll * b[n / x] * x % P * x % P * a[x] % P;
    }
    for (int pri : fac) {
        for (int x : s) if (x % pri == 0) {
            c[x / pri] = (c[x / pri] + c[x]) % P;
        }
    }
    for (int x : s) {
        c[x] = 1ll * c[x] * qpow(x, P - 2) % P;
    }
    for (int i = 1; i <= q; i++) {
        printf("%d\n", c[k[i]]);
    }
    return 0;
}