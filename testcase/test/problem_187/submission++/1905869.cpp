# include <bits/stdc++.h>

using namespace std;

namespace kh {
  template <typename T>
    constexpr T& cmin(T& a, T const& b)
    { return a = ::std::min(a, b); }
  template <typename T>
    constexpr T& cmax(T& a, T const& b)
    { return a = ::std::max(a, b); }
  constexpr int N(100);
  constexpr int M(500);
  constexpr int K(10);
  int n, m, k, u, s[K];
  int d[N + 1][N + 1];
  int f[1 << K][N + 1];
  void main() {
    cin >> n >> m >> k, u = (1 << k) - 1;
    for (int i(1); i <= n; ++i)
      for (int j(1); j <= n; ++j)
        d[i][j] = i == j ? 0 : INT_MAX >> 1;
    for (int i(0); i != m; ++i) {
      int u, v, w;
      cin >> u >> v >> w;
      cmin(d[u][v], w);
      cmin(d[v][u], w);
    }
    for (int i(1); i <= n; ++i)
      for (int j(1); j <= n; ++j)
        for (int k(1); k <= n; ++k)
          cmin(d[j][k], d[j][i] + d[i][k]);
    for (int i(0); i != k; ++i) cin >> s[i];
    memset(f, 0x3f, sizeof f);
    for (int i(0); i != k; ++i) f[1 << i][s[i]] = 0;
    for (int i(1); i != 1 << k; ++i) {
      for (int j(1); j <= n; ++j)
        for (int k(1); k <= n; ++k)
          cmin(f[i][k], f[i][j] + d[j][k]);
      for (int j(u ^ i); j; j = (j - 1) & ~i)
        for (int k(1); k <= n; ++k)
          cmin(f[i | j][k], f[i][k] + f[j][k]);
    }
    cout << *min_element(f[u] + 1, f[u] + n + 1) << endl;
  }
}

int main() { kh::main(); }