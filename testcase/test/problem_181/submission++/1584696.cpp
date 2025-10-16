#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ul = unsigned long long;
using L = __uint128_t;
void exgcd(int a, int b, int &x, int &y) {
    b ? (exgcd(b, a % b, y, x), y -= a / b * x) : (x = 1, y = 0);
}
int o;
struct FastMod {
    ul b, m;
    void in(ul x) {
        b = x, m = (ul)((L(1) << 64) / x);
    }
    int operator()(ul a) {
        ul q = (ul)((L(m) * a) >> 64), r = a - q * b;
        return r >= b ? r - b : r;
    }
};
struct P {
    int p, pk, u, phi;
    basic_string<int>s, pw;
    FastMod f;
    int inv(int a) {
        int x, y;
        exgcd(a, pk, x, y);
        return f(x + pk);
    }
    pair<int, ll>wk(ll n) {
        if (!n)
            return{1, 0};

        auto o = wk(n / p);

        return {f(f(o.first * 1ll * pw[(n / pk) % phi]) * 1ll * s[f(n)]), o.second + n / p};
    }
    int qp(int a, int b) {
        int r = 1;

        for (; b; b >>= 1, a = f(a * 1ll * a))
            if (b & 1)
                r = f(r * 1ll * a);

        return r;
    }
    int get(ll n, ll m) {
        auto a = wk(n), b = wk(m), c = wk(n - m);
        return f(f(f(a.first * 1ll * inv(b.first)) * 1ll * inv(c.first)) * 1ll * qp(p,
                 a.second - b.second - c.second));
    }
    void in(int x, int y) {
        p = x, pk = y, u = o / y * 1ll * inv(o / y) % o, s.resize(pk + 1), s[0] = 1, f.in(pk), phi = pk / p * (p - 1);

        for (int i = 1; i <= pk; ++i)
            if (i % p)
                s[i] = f(s[i - 1] * 1ll * i);
            else
                s[i] = s[i - 1];

        pw.resize(phi), pw[0] = 1;

        for (int i = 1; i < phi; ++i)
            pw[i] = f(pw[i - 1] * 1ll * s[pk]);
    }
} p[13];
int main() {
    int T, x, i, j, t = 0;
    ll n, m;

    for (scanf("%d%d", &T, &o), x = o, i = 2; i * i <= x; ++i)
        if (x % i == 0) {
            for (j = 1; j *= i, x /= i, x % i == 0;);

            p[++t].in(i, j);
        }

    if (x > 1)
        p[++t].in(x, x);

    for (; T--; printf("%d\n", x)) {
        scanf("%lld%lld", &n, &m), x = 0;

        for (i = 1; i <= t; ++i)
            x = (x + p[i].get(n, m) * 1ll * p[i].u) % o;
    }

    return 0;
}