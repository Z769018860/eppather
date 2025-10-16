#include <bits/stdc++.h>

using namespace std;

const int N = 21, MOD = 998244353;
inline int Plus(int a, int b) {return a + b >= MOD ? a + b - MOD : a + b; }
inline int Minus(int a, int b) {return a - b < 0 ? a - b + MOD : a - b; }
inline int ksm(long long a, int b) {
    long long r = 1;
    for(; b; b >>= 1, a = a * a % MOD)
        if(b & 1) r = r * a % MOD;
    return r;
}
int n, m, k, f[N + 1][1 << N], g[N + 1][1 << N];
int inv[N + 10], fac[N + 1], ifac[N + 1];

inline void FWT(int A[], int n, int type) {
    for(int h = 2; h <= n; h <<= 1)
        for(int i = 0; i < n; i += h)
            for(int j = i; j < i + (h >> 1); j ++) {
                if(type == 1) A[j + (h >> 1)] = Plus(A[j + (h >> 1)], A[j]);
                else A[j + (h >> 1)] = Minus(A[j + (h >> 1)], A[j]);
            }
}

inline void exp(int f[], int g[], int n) {
    for(int i = 0; i <= n; i ++) g[i] = 0;
    g[0] = 1;
    for(int i = 1; i <= n; i ++) {
        for(int j = 1; j <= i; j ++)
            g[i] = Plus(g[i], 1ll * f[j] * j % MOD * g[i - j] % MOD);
        g[i] = 1ll * g[i] * inv[i] % MOD;   
    }
}
inline void ln(int f[], int g[], int n) {
    for(int i = 0; i <= n; i ++) g[i] = 0;
    for(int i = 1; i <= n; i ++) {
        for(int j = 1; j < i; j ++)
            g[i] = Plus(g[i], 1ll * g[j] * j % MOD * f[i - j] % MOD);
        g[i] = Minus(f[i], 1ll * g[i] * inv[i] % MOD); 
    }
}

inline void power(int f[], int n, int k) {
    static int g[N];
    for(int i = 0; i <= n; i ++) g[i] = 0;
    int pos = 0;
    while(pos <= n && f[pos] == 0) pos ++;
    if(pos > n || pos * k > n) {
        for(int i = 0; i <= n; i ++) f[i] = 0;
        return;
    }
    int d = f[pos], id = ksm(d, MOD - 2);
    for(int i = 0; i <= n; i ++)
        if(i + pos <= n) f[i] = 1ll * f[i + pos] * id % MOD;
        else f[i] = 0;
    ln(f, g, n - pos);
    for(int i = 0; i <= n - pos; i ++)
        f[i] = 1ll * g[i] * k % MOD;
    exp(f, g, n - pos);
    for(int i = n, mul = ksm(d, k); i >= 0; i --)
        if(i - pos * k >= 0) f[i] = 1ll * g[i - pos * k] * mul % MOD;
        else f[i] = 0;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0);

    cin >> n >> m >> k;
    inv[1] = 1;
    for(int i = 2; i <= n; i ++)
        inv[i] = Minus(0, 1ll * (MOD / i) * inv[MOD % i] % MOD);
    fac[0] = 1; for(int i = 1; i <= n; i ++) fac[i] = 1ll * fac[i - 1] * i % MOD;
    ifac[n] = ksm(fac[n], MOD - 2); for(int i = n; i >= 1; i --) ifac[i - 1] = 1ll * ifac[i] * i % MOD;
    while(m --) {
        int x; cin >> x;
        f[__builtin_popcount(x)][x] ++;
    }

    const int Lim = (1 << n);
    for(int i = 0; i <= n; i ++)
        FWT(f[i], 1 << n, 1);
    for(int mask = 0; mask < Lim; mask ++) {
        static int F[N + 1], G[N + 1], H[N + 1];
        for(int i = 0; i <= n; i ++)
            H[i] = F[i] = f[i][mask], G[i] = 0;
        power(H, n, k);
        for(int i = 0; i <= n; i ++)
            H[i] = 1ll * H[i] * ifac[k] % MOD;
        for(int i = 0, mul = 1; i <= k; i ++) {
            G[0] = Plus(G[0], 1ll * mul * ifac[i] % MOD);
            mul = 1ll * mul * F[0] % MOD;
        }
        for(int i = 1; i <= n; i ++) {
            for(int j = 1; j <= i; j ++)
                G[i] = Plus(G[i], 1ll * j * F[j] % MOD * Minus(G[i - j], H[i - j]) % MOD);
            G[i] = 1ll * G[i] * inv[i] % MOD;
        }
        for(int i = 0; i <= n; i ++) g[i][mask] = G[i];
    }
    FWT(g[n], Lim, - 1);
    cout << g[n][Lim - 1] << '\n';

    return 0;
}