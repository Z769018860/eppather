
#include <bits/stdc++.h>

#define rep(i, l, r) for (int i = l, rep##i = r; i <= rep##i; ++i)
#define per(i, r, l) for (int i = r, per##i = l; i >= per##i; --i)

typedef long long LL;

const int MAXC = 1e6, MOD = 1e9 + 7;
int a, b, c, x0, cir, ref[MAXC + 5], cnt[2][MAXC + 5];
LL L1, R1, L2, R2;

inline int mul(const int u, const int v) { return 1ll * u * v % MOD; }
inline void subeq(int& u, const int v) { (u -= v) < 0 && (u += MOD); }
inline int sub(int u, const int v) { return (u -= v) < 0 ? u + MOD : u; }
inline void addeq(int& u, const int v) { (u += v) >= MOD && (u -= MOD); }
inline int add(int u, const int v) { return (u += v) < MOD ? u : u - MOD; }
inline int mpow(int u, int v) {
    int ret = 1;
    for (; v; u = mul(u, u), v >>= 1) ret = mul(ret, v & 1 ? u : 1);
    return ret;
}

int main() {
    scanf("%d %d %d %d", &a, &b, &c, &x0);
    scanf("%lld %lld %lld %lld", &L1, &R1, &L2, &R2), --L1, --L2;

    memset(ref, 0xff, c + 1 << 2), ref[x0] = 0;
    while (++cir) {
        x0 = (1ll * a * x0 + b) % c + 1;
        if (~ref[x0]) break;
        ref[x0] = cir;
    }
    int lead = ref[x0];

    auto calc = [&](const LL r, const int v)->LL {
        if (!~ref[v] || r < ref[v]) return 0;
        if (ref[v] < lead) return 1;
        return (r - ref[v]) / (cir - lead) + 1;
    };

    rep (i, 1, c) {
        cnt[0][i] = (calc(R1, i) - calc(L1, i)) % MOD;
        cnt[1][i] = (calc(R2, i) - calc(L2, i)) % MOD;
    }

    int ans = 0;
    rep (i, 1, c) addeq(ans, mul(2, mul(cnt[0][i], cnt[1][i])));
    rep (i, 1, c) {
        addeq(cnt[0][i], cnt[0][i - 1]);
        addeq(cnt[1][i], cnt[1][i - 1]);
    }
    rep (i, 1, c) {
        int xl = i, k = 2;
        while (++k, xl < c) {
            int xr = std::min((LL)c,
              (LL)floor(i * (k + sqrt(1ll * k * k - 4)) / 2));
            addeq(ans, mul(k, mul(sub(cnt[0][i], cnt[0][i - 1]),
              sub(cnt[1][xr], cnt[1][xl]))));
            addeq(ans, mul(k, mul(sub(cnt[1][i], cnt[1][i - 1]),
              sub(cnt[0][xr], cnt[0][xl]))));
            
            xl = xr;
        }
    }
    printf("%d\n", ans);
    return 0;
}
