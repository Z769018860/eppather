#include <cmath>
#include <vector>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
#define rep(i, l, r) for (int i = l; i <= r; ++i)
#define dep(i, l, r) for (int i = r; i >= l; --i)
typedef long long ll; 
typedef double db; 
const int Mod = 65537; 
ll n, m; 

int inc (int a, int b) { return (a += b) >= Mod ? a - Mod : a; }
int dec (int a, int b) { return (a -= b) < 0 ? a + Mod : a; }
int mul (int a, int b) { return 1ll * a * b % Mod; }
int fpow (int a, ll b) { int ans = 1; for ( ; b; a = mul(a, a), b >>= 1ll) if(b & 1ll) ans = mul(ans, a); return ans; }

namespace S1 {
  const int N = 1e7 + 5; 
  int pw[N], fac[N], inv[N]; 

  int C (ll n, ll m) {
    if(n < m) return 0; 
    if(!n) return 1; 
    int nx = n % Mod, mx = m % Mod; 
    if(nx < mx) return 0; 
    return mul(C(n / Mod, m / Mod), mul(fac[nx], mul(inv[mx], inv[nx - mx]))); 
  }
  int calc (ll n) {
    if(n < 0) return 0; 
    int ans = 0, L = n / (m + 1), res = fpow(fpow(2, m + 1), Mod - 2); 
    pw[0] = fpow(2, n); rep(i, 1, L) pw[i] = mul(pw[i - 1], res); 
    rep(i, 0, L) {
      if(i & 1) ans = dec(ans, mul(C(n - i * m, i), pw[i]));
      else ans = inc(ans, mul(C(n - i * m, i), pw[i])); 
    }
    return ans; 
  }
  void solve () {
    fac[0] = inv[0] = 1; 
    rep(i, 1, Mod - 1) fac[i] = mul(fac[i - 1], i); 
    inv[Mod - 1] = fpow(fac[Mod - 1], Mod - 2); 
    dep(i, 1, Mod - 2) inv[i] = mul(inv[i + 1], i + 1); 
    printf("%d", dec(calc(n), calc(n - m))); 
  }
}

namespace S2 {
  const int N = 65536 + 5, M = 20;
  int ans, pw[N]; 

  namespace Poly {
    int L, E, r[N], A[N], B[N], suf[N], inv[N], G[M][N][2]; 
  
    void NTT (int L, int E, int *a, int type) {
      rep(i, 0, L - 1) r[i] = (r[i >> 1] >> 1) + (i & 1) * (1 << (E - 1));
      rep(i, 0, L - 1) if(i < r[i]) swap(a[i], a[r[i]]);
      for (int k = 1, t = 0; k < L; k <<= 1, ++t) 
        for (int i = 0; i < L; i += (k << 1))
          for (int j = i; j < i + k; ++j) {
            int ll = a[j], rr = mul(G[t + 1][j - i][type], a[j + k]);
            a[j] = inc(ll, rr), a[j + k] = dec(ll, rr);
          }
      if(type == 1) {
        int Inv = fpow(L, Mod - 2);
        rep(i, 0, L - 1) a[i] = mul(a[i], Inv); 
      }
    }
    struct poly { 
      vector <int> f; 
  
      friend poly operator + (const poly &a, const poly &b) {
        poly c; c.f.resize(max(a.f.size(), b.f.size()));
        for (auto i = 0; i < c.f.size(); ++i) {
          if(i < a.f.size()) c.f[i] = inc(c.f[i], a.f[i]); 
          if(i < b.f.size()) c.f[i] = inc(c.f[i], b.f[i]); 
        }
        return c; 
      }
      friend poly operator - (const poly &a, const poly &b) {
        poly c; c.f.resize(max(a.f.size(), b.f.size()));
        for (auto i = 0; i < c.f.size(); ++i) {
          if(i < a.f.size()) c.f[i] = inc(c.f[i], a.f[i]); 
          if(i < b.f.size()) c.f[i] = dec(c.f[i], b.f[i]); 
        }
        return c; 
      }
      friend poly operator * (const poly &a, const poly &b) {
        int len = a.f.size() + b.f.size(), L, E; len -= 2; 
        poly c; c.f.resize(len + 1); 
        if(len <= 30) {
          rep(i, 0, a.f.size() - 1) rep(j, 0, b.f.size() - 1)
            c.f[i + j] = inc(c.f[i + j], mul(a.f[i], b.f[j])); 
         return c; 
        }
        for (L = 1, E = 0; L <= len; L <<= 1, ++E) ;
        rep(i, 0, L - 1) A[i] = B[i] = 0; 
        for (auto i = 0; i < a.f.size(); ++i) A[i] = a.f[i]; 
        for (auto i = 0; i < b.f.size(); ++i) B[i] = b.f[i]; 
        NTT(L, E, A, 0), NTT(L, E, B, 0); 
        rep(i, 0, L - 1) A[i] = mul(A[i], B[i]); 
        NTT(L, E, A, 1); 
        rep(i, 0, len) c.f[i] = A[i]; 
        return c; 
      }
    } ;
    poly operator % (poly a, poly b) {
      if(a.f.size() < m) return a; 
      for (int i = a.f.size() - 1; ~i; --i) {
        a.f[i] = inc(a.f[i], dec(suf[i + 1], suf[i + m + 1]));
        suf[i] = suf[i + 1]; 
        if(i >= m) suf[i] = inc(suf[i], a.f[i]), a.f[i] = 0; 
      }
      for (int i = 0; i < a.f.size(); ++i) suf[i] = 0; 
      a.f.resize(m); for ( ; a.f.size() && !a.f.back(); a.f.pop_back()) ;  
      return a; 
    } 
    void init (int n) {
      rep(i, 1, n) inv[i] = fpow(i, Mod - 2); 
      rep(i, 1, 16) { 
        G[i][0][0] = G[i][0][1] = 1; 
        G[i][1][0] = fpow(3, (Mod - 1) / (1 << i)); 
        G[i][1][1] = fpow(21846, (Mod - 1) / (1 << i)); 
        rep(j, 2, (1 << i) - 1) rep(k, 0, 1) 
          G[i][j][k] = mul(G[i][j - 1][k], G[i][1][k]); 
      }
    }
  }
  using Poly :: poly; 

  poly fpow (ll n, poly c) {
    poly a, b; a.f.resize(2), a.f[1] = 1, b.f.push_back(1); 
    for ( ; n; n >>= 1ll, a = a * a % c) if(n & 1ll) b = b * a % c;  
    return b; 
  }
  void solve () {
    Poly :: init(m); 
    pw[0] = 1; rep(i, 1, m - 1) pw[i] = mul(pw[i - 1], 2); 
    poly G; G.f.resize(m + 1); 
    G.f[m] = 1; rep(i, 1, m) G.f[m - i] = Mod - 1;
    poly R = fpow(n, G); 
    for (int i = 0; i < R.f.size(); ++i) ans = inc(ans, mul(R.f[i], pw[i])); 
    printf("%d", ans); 
  }
}

int main () {
  cin >> n >> m;
  db need = 1.0 * m * log2(1.0 * m) * log2(1.0 * n); 
  if(1.0 * n / (m + 1) <= need * 1.5) S1 :: solve(); 
  else S2 :: solve(); 
  return 0; 
}