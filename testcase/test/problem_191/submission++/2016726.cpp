#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <vector>
using namespace std;
const int N = 2e5 + 9;
typedef long long ll;

vector<int> G[N], H[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie();
  cout.tie(0);
  int n, m;
  cin >> n >> m;
  for (int i = 1, u, v; i <= m; ++i) {
    cin >> u >> v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  auto cmp = [=](int u, int v) {
    return G[u].size() > G[v].size() || (G[u].size() == G[v].size() && u > v);
  };
  for (int u = 1; u <= n; u++) {
    for (int v : G[u]) {
      if (cmp(u, v)) {
        H[u].push_back(v);
        
      }
    }
  }
  long long ans = 0;
  vector<int> cnt(n + 1);
  for (int u = 1; u <= n; u++) {
    for (int v : H[u]) {
      for (int w : G[v]) {
        if (cmp(u, w)) {
          ans += cnt[w]++;
        }
      }
    }
    for (int v : H[u]) {
      for (int w : G[v]) {
        cnt[w] = 0;
      }
    }
  }
  cout << ans << '\n';
  return 0;
}
