#pragma GCC target("popcnt")
#pragma GCC optimize("Ofast","-funroll-loops")
#pragma GCC target("sse4.1","sse4.2","ssse3","sse3","sse2","sse","avx2","avx","popcnt","tune=native")
#include <bits/stdc++.h>
#define popcnt __builtin_popcount

using namespace std;

using ll = long long;
using L = __int128_t;

const int mod = 998244353;
void add(int &x, int y) { if ((x += y - mod) < 0) x += mod; }
void sub(int &x, int y) { if ((x -= y) < 0) x += mod; }
int mpow(int a, int b) {
  int ret = 1;
  for (; b; b >>= 1) {
    if (b & 1) ret = (ll)ret * a % mod;
    a = (ll)a * a % mod;
  }
  return ret;
}

const int LG = 21;
const int N = 1 << LG;
int lg, n;
int e[LG + 1];
int f[N], g[N], t[N];
int x, y;

namespace Set {
  int fac[LG + 1], ifac[LG + 1], inv[LG + 1];
  void init() {
    fac[0] = 1;
    for (int i = 1; i <= LG; ++i) fac[i] = (ll)fac[i - 1] * i % mod;
    ifac[LG] = mpow(fac[LG], mod - 2);
    for (int i = LG; i; --i) ifac[i - 1] = (ll)ifac[i] * i % mod;
    for (int i = 1; i <= LG; ++i) inv[i] = (ll)ifac[i] * fac[i - 1] % mod;
  }
  template<class T>
  void fmt(T a, int lg, int type) {
    auto func = type == 1 ? add : sub;
    for (int w = 2, m = 1; w <= (1 << lg); w <<= 1, m <<= 1)
      for (int i = 0; i < (1 << lg); i += w)
        for (int j = 0; j < m; ++j)
          for (int k = 0; k <= lg; ++k)
            func(a[i | j | m][k], a[i | j][k]);
  }
  int t1[N][LG + 1];
  void exp(int *g, int *h, int lg) {
    int n = 1 << lg;
    for (int i = 0; i < n; ++i) memset(t1[i], 0, sizeof(int) * (lg + 1));
    for (int i = 0; i < n; ++i) t1[i][popcnt(i)] = g[i];
    fmt(t1, lg, 1);
    for (int s = 0; s < n; ++s) {
      static int tt[LG + 1];
      memcpy(tt, t1[s], sizeof tt);
      t1[s][0] = 1;
      for (int i = 1; i <= lg; ++i) {
        L v = 0;
        for (int j = 1; j <= i; ++j)
          v += (L)tt[j] * j * t1[s][i - j];
        t1[s][i] = (ll)(v % mod) * inv[i] % mod;
      }
    }
    fmt(t1, lg, -1);
    for (int i = 0; i < n; ++i) h[i] = t1[i][popcnt(i)];
  }
}
int vis[LG + 1], crit[N], coe[LG + 1];
void dfs(int p) {
  vis[p] = 1;
  for (int i = 0; i < lg; ++i)
    if (((e[p] >> i) & 1) && !vis[i])
      dfs(i);
}
int main() {
  Set::init();
  scanf("%d", &lg), n = 1 << lg;
  for (int i = 0; i < lg; ++i)
    for (int j = 0; j < lg; ++j) {
      int x;
      scanf("%d", &x), e[i] |= x << j;
    }
  scanf("%d%d", &x, &y), sub(x, 1);
  for (int i = 0; i < lg; ++i)
    if (!vis[i]) {
      dfs(i);
      for (int s = 0; s < n; ++s)
        if ((s >> i) & 1)
          crit[s] = 1;
    }
  for (int i = 1; i <= lg; ++i)
    coe[i] = ((ll)coe[i - 1] * y + 1) % mod;
  for (int i = 0; i < lg; ++i) {
    for (int s = 0; s < (1 << i); ++s)
      t[s] = (ll)g[s] * coe[popcnt(e[i] & s)] % mod;
    Set::exp(t, g + (1 << i), i);
  }
  for (int s = 1; s < n; ++s)
    if (!crit[s]) g[s] = (ll)g[s] * x % mod;
  Set::exp(g, f, lg - 1);
  L ans = 0;
  for (int s = 0; s < (1 << (lg - 1)); ++s)
    ans += (ll)g[(n - 1) ^ s] * f[s];
  printf("%d\n", (int)(ans % mod));
}