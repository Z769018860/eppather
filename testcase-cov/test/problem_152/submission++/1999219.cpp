#include<bits/stdc++.h>
#define popcount __builtin_popcount
using i64 = long long;
const i64 mod = 1e9 + 9;
const int maxm = 22, maxn = (1 << 20) + 2;
namespace FWT {
    const i64 Bitor[2][2] = {{1, 1}, {1, 0}}, IBitor[2][2] = {{0, 1}, {1, mod - 1}};
    inline void FWT(i64 *a, const i64 B[2][2], int n) {
        for (int i = 0; (1 << i) < n; i++)
            for (int s = 0; s < n; s += 2 << i)
                for (int p = s, ed = s + (1 << i); p < ed; p++) {
                    i64 x = a[p], y = a[p + (1 << i)];
                    a[p] = (B[0][0] * x + B[0][1] * y) % mod, a[p + (1 << i)] = (B[1][0] * x + B[1][1] * y) % mod;
                }
    }
};
i64 a[maxm][maxn], b[maxm][maxn], c[maxm][maxn];
int main() {
    int m; scanf("%d", &m);
    int n = 1 << m;
    for (int i = 0; i < n; i++) scanf("%lld", &a[popcount(i)][i]);
    for (int i = 0; i < n; i++) scanf("%lld", &b[popcount(i)][i]);
    for (int i = 0; i <= m; i++) FWT::FWT(a[i], FWT::Bitor, n);
    for (int i = 0; i <= m; i++) FWT::FWT(b[i], FWT::Bitor, n);
    for (int s = 0; s < n; s++) for (int i = 0; i <= m; i++)
        for (int j = 0; j <= i; j++) (c[i][s] += a[j][s] * b[i - j][s]) %= mod;
    for (int i = 0; i <= m; i++) FWT::FWT(c[i], FWT::IBitor, n);
    for (int i = 0; i < n; i++) printf("%lld ", c[popcount(i)][i]);
    return 0;
}