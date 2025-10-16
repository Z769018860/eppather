#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned ui;
ui mod;
ui INV, R2;
inline void setMod(ui p) {
    mod = p;
    R2 = -(ull)p % p;
    INV = p;
    for (int i = 0; i < 4; i++) INV *= 2 - INV * p;
}
inline ui reduce(ull x) {
    ui ans = (x >> 32) - (ull((ui)x * INV) * mod >> 32);
    return (int)ans < 0 ? ans + mod : ans;
}
inline ui Mod(ui x) {
    if (x >= mod) return x - mod;
    return x;
}
inline void Add(ui &x, ui y) {
    if ((x += y) >= mod) x -= mod;
}
struct mint {
    ui x;
    inline mint(): x(0) {}
    inline mint(ui x): x(reduce((ull)x * R2)) {}
    inline mint& operator += (mint b) { Add(x, b.x); return *this; }
    inline mint& operator -= (mint b) { Add(x, mod - b.x); return *this; }
    inline mint& operator *= (mint b) { x = reduce((ull)x * b.x); return *this; }
    inline mint operator + (mint b) { return mint(*this) += b; }
    inline mint operator - (mint b) { return mint(*this) -= b; }
    inline mint operator * (mint b) { return mint(*this) *= b; }
    inline mint operator - () { return mint() -= *this; }
    inline int operator == (const mint &b) { return x == b.x; }
    inline int operator != (const mint &b) { return x != b.x; }
    inline int operator < (const mint &a) { return x < a.x; }
    inline int operator <= (const mint &a) { return x <= a.x; }
    inline int operator > (const mint &a) { return x > a.x; }
    inline int operator >= (const mint &a) { return x >= a.x; }
    inline mint inv();
    inline ui get() { return reduce(x); }
    explicit inline operator int () { return get(); }
};
inline mint power(mint res, int b) {
    mint ans = 1;
    for (; b; b >>= 1, res = res * res) if (b & 1) ans = ans * res;
    return ans;
}
inline mint mint :: inv() {
    return power(*this, mod - 2);
}
inline int power(int a, int b) {
    long long res = a, ans = 1;
    for (; b; b >>= 1, res = res * res % mod) if (b & 1) ans = ans * res % mod;
    return ans;
}
typedef vector < mint > poly;
inline poly operator + (poly a, poly b) {
    a.resize(max(a.size(), b.size()));
    for (int i = 0; i < b.size(); i++) a[i] += b[i];
    return a;
}
inline poly operator - (poly a, poly b) {
    a.resize(max(a.size(), b.size()));
    for (int i = 0; i < b.size(); i++) a[i] -= b[i];
    return a;
}
inline poly operator * (poly a, poly b) {
    poly c = poly(a.size() + b.size() - 1);
    for (int i = 0; i < a.size(); i++)
        for (int j = 0; j < b.size(); j++) c[i + j] += a[i] * b[j];
    return c;
}
inline poly Div(poly a, poly b) {
    poly ans(max(0, (int)a.size() - (int)b.size() + 1));
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    mint qwq = b[0].inv();
    for (int i = 0; i < ans.size(); i++) {
        ans[i] = a[i] * qwq;
        for (int j = 0; j < b.size(); j++) a[i + j] -= ans[i] * b[j];
    }
    reverse(ans.begin(), ans.end());
    return ans;
}
inline poly Mod(poly a, poly b) {
    a.resize(max(a.size(), b.size() - 1));
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    mint qwq = b[0].inv();
    for (int i = 0, i_end = a.size() - b.size() + 1; i < i_end; i++) {
        mint cur = a[i] * qwq;
        for (int j = 0; j < b.size(); j++) a[i + j] -= cur * b[j];
    }
    reverse(a.begin(), a.end());
    a.resize(b.size() - 1);
    return a;
}
inline poly gcd(poly a, poly b) {
    while (1) {
        while (b.size() && b.back().get() == 0) b.pop_back();
        if (b.empty()) return a;
        a = Mod(a, b);
        swap(a, b);
    }
}
inline poly power(const poly& a, const poly& mod, int b) {
    if (b == 0) return {1};
    if (b & 1) return Mod(power(Mod(a * a, mod), mod, b / 2) * a, mod);
    else return power(Mod(a * a, mod), mod, b / 2);
}
int n;
mt19937 rnd((random_device())());
int main() {
    scanf("%d%d", &n, &mod);
    setMod(mod);
    poly a(n + 1);
    for (int i = 0; i <= n; i++) {
        int x;
        scanf("%d", &x);
        a[i] = mint(x);
    }
    poly x{0, 1};
    x = Mod(x, a);
    poly xp = power(x, a, mod) - x;
    vector < poly > q;
    q.push_back(gcd(xp, a));
    vector < int > ans;
    while (q.size()) {
        poly cur = q.back();
        q.pop_back();
        if (cur.size() == 1) continue;
        if (cur.size() == 2) {
            ans.push_back((int)(-cur[0] * cur[1].inv()));
            continue;
        }
        poly rndp(cur.size() - 1);
        for (auto &i : rndp) i = rnd() % mod;
        rndp = power(rndp, cur, (mod - 1) / 2);
        rndp[0] -= 1;
        rndp = gcd(rndp, cur);
        q.push_back(rndp);
        q.push_back(Div(cur, rndp));
    }
    sort(ans.begin(), ans.end());
    ans.resize(unique(ans.begin(), ans.end()) - ans.begin());
    printf("%d\n", (int)ans.size());
    for (int i = 0; i < ans.size(); i++) printf("%d%c", ans[i], " \n"[i == ans.size() - 1]);
}