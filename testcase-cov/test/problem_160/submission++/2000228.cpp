#include <bits/stdc++.h>

using namespace std;

int n, m, tot;
vector<int> v, w, siz, dfn;
vector<vector<int>> adj;
vector<vector<int>> f;

void dfs(int u) {
  siz[u] = 1;
  for (auto v : adj[u]) {
    dfs(v);
    siz[u] += siz[v];
  }
  dfn[++tot] = u;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;
  v.resize(n + 2);
  w.resize(n + 2);
  siz.resize(n + 2);
  adj.resize(n + 2);
  dfn.resize(n + 2);
  f.resize(n + 2, vector<int>(m + 2));
  for (int u = 1; u <= n; u++) {
    int v;
    cin >> v;
    adj[v].push_back(u);
  }
  for (int i = 1; i <= n; i++) {
    cin >> v[i];
  }
  for (int i = 1; i <= n; i++) {
    cin >> w[i];
  }
  dfs(0);
  n = tot;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= m; j++) {
      if (j >= v[dfn[i]]) {
        f[i][j] = max(f[i][j], max(f[i - 1][j - v[dfn[i]]] + w[dfn[i]], f[i - siz[dfn[i]]][j]));
      } else {
        f[i][j] = max(f[i][j], f[i - siz[dfn[i]]][j]);
      }
    }
  }
  cout << f[n][m] << "\n";

  return 0;
}
