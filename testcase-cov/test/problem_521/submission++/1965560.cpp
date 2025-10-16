# include <bits/stdc++.h>

namespace lyre {
  using namespace std;
  constexpr size_t N(500'100);
  vector<int> F[N], G[N];
  vector<int> ans;
  int n, size[N], in[N];
  bool vis[N];
  inline void insF(int u, int v) {
    if (u == v) return;
    F[u].push_back(v), ++size[u];
    F[v].push_back(u), ++size[v];
  }
  inline void insG(int u, int v) {
    if (u == v) return;
    G[u].push_back(v);
  }
  void main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i(1); i < n; ++i) {
      int u, v;
      cin >> u >> v;
      insF(u, v);
    }
    auto cnt(0);
    queue<int> q;
    for (int i(1); i <= n; ++i)
      if (size[i] == 1) q.push(i);
    while (!q.empty()) {
      auto u(q.front());
      q.pop();
      if (!size[u]) continue;
      auto v(0);
      for (auto t : F[u]) if (!vis[t]) v = t;
      size[u] = size[v] = 0;
      ++cnt, vis[u] = vis[v] = true;
      for (auto w : F[u]) insG(v, w);
      for (auto w : F[v]) insG(u, w);
      for (auto w : F[v]) {
        if (vis[w]) continue;
        if (--size[w] == 1) q.push(w);
      }
    }
    if (cnt * 2 < n) {
      cout << -1 << endl;
      return;
    }
    for (int i(1); i <= n; ++i) {
      sort(G[i].begin(), G[i].end());
      G[i].erase(unique(G[i].begin(), G[i].end()), G[i].end());
      for (auto j : G[i]) ++in[j];
    }
    priority_queue<int, vector<int>, greater<int>> heap;
    for (int i(1); i <= n; ++i)
      if (!in[i]) heap.push(i);
    while (!heap.empty()) {
      auto u(heap.top());
      heap.pop();
      ans.push_back(u);
      for (auto v : G[u]) {
        if (!--in[v]) heap.push(v);
      }
    }
    if (int(ans.size()) < n) {
      cout << -1 << endl;
    } else {
      for (int i(0); i < n; ++i)
        cout << ans[i] << " \n"[i == n - 1];
    }
  }
}

int main() { lyre::main(); }