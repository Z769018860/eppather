# include <bits/stdc++.h>

namespace lyre {
  using namespace std;
  constexpr size_t N(500'100);
  vector<int> F[N], H[N];
  set<int> G[N];
  vector<int> ans;
  int n, in[N];
  inline void insF(int u, int v) {
    if (u == v) return;
    F[u].push_back(v), F[v].push_back(u);
  }
  inline void insG(int u, int v) {
    if (u == v) return;
    G[u].insert(v), G[v].insert(u);
  }
  inline void eraG(int u, int v) {
    if (u == v) return;
    G[u].erase(v), G[v].erase(u);
  }
  inline void insH(int u, int v) {
    if (u == v) return;
    H[u].push_back(v);
  }
  void main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i(1); i < n; ++i) {
      int u, v;
      cin >> u >> v;
      insF(u, v), insG(u, v);
    }
    auto cnt(0);
    queue<int> q;
    for (int i(1); i <= n; ++i) {
      if (G[i].size() == 1)
        q.push(i);
    }
    while (!q.empty()) {
      auto u(q.front());
      q.pop();
      if (G[u].empty()) continue;
      auto v(*G[u].begin());
      ++cnt, eraG(u, v);
      for (auto w : F[u]) insH(v, w);
      for (auto w : F[v]) insH(u, w);
      auto const Gv(G[v]);
      for (auto w : Gv) {
        eraG(v, w);
        if (G[w].size() == 1) q.push(w);
      }
    }
    if (cnt * 2 < n) {
      cout << -1 << endl;
      return;
    }
    for (int i(1); i <= n; ++i) {
      sort(H[i].begin(), H[i].end());
      H[i].erase(unique(H[i].begin(), H[i].end()), H[i].end());
      for (auto j : H[i]) ++in[j];
    }
    priority_queue<int, vector<int>, greater<int>> heap;
    for (int i(1); i <= n; ++i)
      if (!in[i]) heap.push(i);
    while (!heap.empty()) {
      auto u(heap.top());
      heap.pop();
      ans.push_back(u);
      for (auto v : H[u]) {
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