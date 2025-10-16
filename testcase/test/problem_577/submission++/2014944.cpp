#include <bits/stdc++.h>



const int kMaxN = 55;

int n, p, q;
int a[kMaxN], pw[kMaxN][kMaxN], C[kMaxN][kMaxN], f[2][kMaxN][kMaxN * kMaxN * 2], g[2][100];

void prework() {
  C[0][0] = 1;
  for (int i = 1; i <= p - 1; ++i) {
    C[i][0] = 1;
    for (int j = 1; j <= i; ++j)
      C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % p;
  }
  for (int i = 0; i <= n; ++i) {
    pw[i][0] = 1;
    for (int j = 1; j <= p; ++j)
      pw[i][j] = pw[i][j - 1] * a[i] % p;
  }
  int o = 0;
  f[o][0][0] = 1;
  for (int i = 0; i <= n; ++i) {
    o ^= 1;
    memset(f[o], 0, sizeof(f[o]));
    for (int j = 0; j <= p - 1; ++j) {
      for (int k = 0; k <= p - 1 - j; ++k) {
        for (int s = 0; s <= i * p; ++s) {
          f[o][j + k][j * i + s] = (f[o][j + k][j * i + s] + f[o ^ 1][k][s] * pw[i][j] * C[j + k][j]) % p;
        }
      }
    }
  }
}

int solve(int64_t m, int64_t k) {
  static int a[100], b[100];
  int t = 0;
  for (; m || k; m /= p, k /= p) a[++t] = m % p, b[t] = k % p;
  memset(g, 0, sizeof(g));
  int o = 0;
  g[o][0] = 1;
  for (int i = 1; i <= t; ++i) {
    o ^= 1;
    memset(g[o], 0, sizeof(g[o]));
    for (int j = 0; j <= n; ++j) {
      for (int now = (b[i] - j % p + p) % p; now <= n * p; now += p) {
        int k = j + now;
        if (k % p != b[i]) continue;
        g[o][k / p] = (g[o][k / p] + g[o ^ 1][j] * f[~n & 1][a[i]][now]) % p;
      }
    }
  }
  return g[o][0];
}

void dickdreamer() {
  std::cin >> n >> p;
  for (int i = 0; i <= n; ++i) std::cin >> a[i];
  prework();
  std::cin >> q;
  for (int i = 1; i <= q; ++i) {
    int64_t m, k;
    std::cin >> m >> k;
    std::cout << solve(m, k) << '\n';
  }
}

int32_t main() {
#ifdef ORZXKR
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  std::ios::sync_with_stdio(0), std::cin.tie(0), std::cout.tie(0);
  int T = 1;
  
  while (T--) dickdreamer();
  
  return 0;
}