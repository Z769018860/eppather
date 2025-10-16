
#include <bits/stdc++.h>

#define rep(i, l, r) for (int i = l, rep##i = r; i <= rep##i; ++i)
#define per(i, r, l) for (int i = r, per##i = l; i >= per##i; --i)

typedef std::vector<int> Poly;

inline char fgc() {
    static char buf[1 << 17], *p = buf, *q = buf;
    return p == q && (q = buf + fread(p = buf, 1, 1 << 17, stdin), p == q) ?
      EOF : *p++;
}

template <typename Tp = int>
inline Tp rint() {
    Tp x = 0, s = fgc(), f = 1;
    for (; s < '0' || '9' < s; s = fgc()) f = s == '-' ? -f : f;
    for (; '0' <= s && s <= '9'; s = fgc()) x = x * 10 + (s ^ '0');
    return x * f;
}

template <typename Tp>
inline void wint(Tp x) {
    if (x < 0) putchar('-'), x = -x;
    if (9 < x) wint(x / 10);
    putchar(x % 10 ^ '0');
}

const int MOD = 998244353;

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

namespace POLY {

const int MAXW = 19, MAXL = 1 << MAXW, G = 3;

int omega[MAXW + 1][MAXL];

inline void init() {
    rep (i, 1, MAXW) {
        int* const wi = omega[i];
        wi[0] = 1, wi[1] = mpow(G, MOD - 1 >> i);
        rep (j, 2, (1 << i) - 1) wi[j] = mul(wi[j - 1], wi[1]);
    }
}

inline void dif(const int len, Poly& u) {
    for (int stp = len >> 1, i = 31 - __builtin_clz(len); i; stp >>= 1, --i) {
        int* const wi = omega[i];
        for (int j = 0; j < len; j += stp << 1) {
            rep (k, j, j + stp - 1) {
                int x = u[k], y = u[k + stp];
                u[k] = add(x, y), u[k + stp] = mul(wi[k - j], sub(x, y));
            }
        }
    }
}

inline void dit(const int len, Poly& u) {
    for (int i = 1, stp = 1; stp < len; ++i, stp <<= 1) {
        int* const wi = omega[i];
        for (int j = 0; j < len; j += stp << 1) {
            rep (k, j, j + stp - 1) {
                int x = u[k], y = mul(wi[k - j], u[k + stp]);
                u[k] = add(x, y), u[k + stp] = sub(x, y);
            }
        }
    }
    int inv = MOD - (MOD - 1) / len;
    rep (i, 0, len - 1) u[i] = mul(u[i], inv);
    std::reverse(u.begin() + 1, u.end());
}

} 

inline Poly operator * (Poly u, Poly v) {
    int res = u.size() + v.size() - 1;
    if (u.size() * v.size() <= 64) {
        Poly ret(res);
        rep (i, 0, int(u.size()) - 1) {
            rep (j, 0, int(v.size()) - 1) {
                addeq(ret[i + j], mul(u[i], v[j]));
            }
        }
        return ret;
    } else {
        int len = 1;
        while (len < res) len <<= 1;
        u.resize(len), v.resize(len);
        POLY::dif(len, u), POLY::dif(len, v);
        rep (i, 0, len - 1) u[i] = mul(u[i], v[i]);
        POLY::dit(len, u);
        return u.resize(res), u;
    }
}

const int MAXN = 2e5 + 20;
int n, m;
std::vector<Poly> ext[MAXN];

inline Poly product(const int id, const int l, const int r) {
    if (l == r) return ext[id][l];
    int mid = l + r >> 1;
    return product(id, l, mid) * product(id, mid + 1, r);
}

int main() {
    POLY::init();
    n = rint(), m = rint();
    rep (i, 1, m) {
        int a = rint(), x = rint(), y = rint(), p = mul(x, mpow(y, MOD - 2));
        ext[a].push_back({ { sub(1, p), p } });
    }

    int ans = 0;
    Poly cur = { { 1 } };
    rep (i, 0, n + 18) {
        if (ext[i].size()) cur = cur * product(i, 0, int(ext[i].size()) - 1);
        rep (j, 1, int(cur.size()) - 1) {
            addeq(ans, mul(j, cur[j]));
            addeq(cur[j >> 1], cur[j]), cur[j] = 0;
        }
        cur.resize((int(cur.size()) - 1 >> 1) + 1);
    }
    wint(ans), putchar('\n');
    return 0;
}
