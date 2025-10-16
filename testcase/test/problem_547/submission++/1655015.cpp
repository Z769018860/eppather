#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 65537;

char buf[1 << 23], *p1 = buf, *p2 = buf;
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1 ++)
ll read() {
    ll s = 0, w = 1; char ch = getchar();
    while(!isdigit(ch)) { if(ch == '-') w = -1; ch = getchar(); }
    while(isdigit(ch)) s = s * 10 + (ch ^ 48), ch = getchar();
    return s * w;
}
void inc(int &a, int b) { a = a >= mod - b ? a - mod + b : a + b; }
void dec(int &a, int b) { a = a >= b ? a - b : a + mod - b; }
int add(int a, int b) { return a >= mod - b ? a - mod + b : a + b; }
int del(int a, int b) { return a >= b ? a - b : a + mod - b; }
int mul(int a, int b) { return 1ll * a * b % mod; }
int ksm(int a, ll b) {
    int res = 1;
    while(b) {
        if(b & 1) res = mul(res, a);
        a = mul(a, a), b >>= 1;
    }
    return res;
}

ll n, m;

namespace Solve1 {
    

    int f[mod], g[mod], h[mod], tmp[mod << 1];

    void Mul(int f[], int g[], int h[]) {
        for(int i = 0; i <= m; ++ i)
            for(int j = 0; j <= m; ++ j)
                inc(tmp[i + j], mul(f[i], g[j]));
        
        for(int i = 2 * m; i >= m; -- i) if(tmp[i]) {
            int cur = tmp[i];
            for(int j = 0; j <= m; ++ j)
                dec(tmp[i - j], mul(cur, h[m - j]));
        }

        for(int i = 0; i <= m; ++ i)
            f[i] = tmp[i], tmp[i] = 0;
    }

    void solve() { 
        f[0] = 1, g[1] = 1, h[m] = 1;
        for(int i = 0; i < m; ++ i) h[i] = mod - 1;
        while(n) {
            if(n & 1) Mul(f, g, h);
            Mul(g, g, h), n >>= 1;
        }

        int ans = 0;
        for(int i = 0; i < m; ++ i)
            inc(ans, mul(ksm(2, i), f[i]));
        printf("%d\n", ans);
    }
};

namespace Solve2 {
    int fac[mod], inv[mod];

    int C(int n, int m) {
        if(n < 0 || n < m) return 0;
        return mul(fac[n], mul(inv[m], inv[n - m]));
    }
    int lucas(ll n, ll m) {
        if(n <= m) return n == m;
        return mul(lucas(n / mod, m / mod), C(n % mod, m % mod));
    }
    void init() {
        fac[0] = inv[0] = inv[1] = 1;
        for(int i = 2; i < mod; ++ i) inv[i] = mul(inv[mod % i], (mod - mod / i));
        for(int i = 1; i < mod; ++ i) inv[i] = mul(inv[i], inv[i - 1]);
        for(int i = 1; i < mod; ++ i) fac[i] = mul(fac[i - 1], i);
    }
    int solve(ll n) {
        int ans = 0, fg = 1, pw = ksm(2, n), iv = ksm(inv[2], m + 1);
        for(int i = 0; i <= n / (m + 1); ++ i)
            inc(ans, mul(fg, mul(pw, lucas(n - i * m, i)))),
            fg = mod - fg, pw = mul(pw, iv);
        return ans;
    }
};

signed main() {
    n = read(), m = read();
    if(m == 1) return puts("1"), 0;
    if(m <= 2000) Solve1::solve();
    else Solve2::init(),printf("%d\n", del(Solve2::solve(n + 1), Solve2::solve(n)));
    return 0;
}