#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

using Int = long long;

template <class T1, class T2> ostream &operator<<(ostream &os, const pair<T1, T2> &a) { return os << "(" << a.first << ", " << a.second << ")"; };
template <class T> ostream &operator<<(ostream &os, const vector<T> &as) { const int sz = as.size(); os << "["; for (int i = 0; i < sz; ++i) { if (i >= 256) { os << ", ..."; break; } if (i > 0) { os << ", "; } os << as[i]; } return os << "]"; }
template <class T> void pv(T a, T b) { for (T i = a; i != b; ++i) cerr << *i << " "; cerr << endl; }
template <class T> bool chmin(T &t, const T &f) { if (t > f) { t = f; return true; } return false; }
template <class T> bool chmax(T &t, const T &f) { if (t < f) { t = f; return true; } return false; }
#define COLOR(s) ("\x1b[" s "m")


constexpr int INF = 1001001001;

int N, X;
vector<int> P, W, V;

vector<vector<int>> graph;

vector<int> dfs(int u, vector<int> fs) {
  for (int x = X; x >= 0; --x) fs[x] = (x >= W[u]) ? (fs[x - W[u]] + V[u]) : -INF;
  for (const int v : graph[u]) {
    const auto res = dfs(v, fs);
    for (int x = 0; x <= X; ++x) chmax(fs[x], res[x]);
  }
  return fs;
}

int main() {
  for (; ~scanf("%d%d", &N, &X); ) {
    P.assign(N + 1, -1); for (int u = 1; u <= N; ++u) scanf("%d", &P[u]);
    W.assign(N + 1, 0); for (int u = 1; u <= N; ++u) scanf("%d", &W[u]);
    V.assign(N + 1, 0); for (int u = 1; u <= N; ++u) scanf("%d", &V[u]);
    
    graph.assign(N + 1, {});
    for (int u = 1; u <= N; ++u) {
      graph[P[u]].push_back(u);
    }
    const auto ans = dfs(0, vector<int>(X + 1, 0));
    printf("%d\n", ans[X]);
  }
  return 0;
}
