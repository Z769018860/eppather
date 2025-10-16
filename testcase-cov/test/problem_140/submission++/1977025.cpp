#include <bits/stdc++.h>
#define V vector
#define Vi vector<int>
#define sz(a) ((int)a.size())
#define fi first
#define se second
#define Int pair<int, int>
#define Inf ((int)1e9)
#define pb push_back
#define ins insert
#define For(i, x, y) for (int i = (x); i <= (y); i++)
#define Rep(i, x, y) for (int i = (x); i >= (y); i--)
#define seg int p, int l, int r
#define lid p << 1, l, mid
#define all(a) a.begin(), a.end()
#define rid p << 1 | 1, mid + 1, r
#define mid ((l + r) / 2)
#define Ceil(x, y) (((x) + (y)-1) / (y))
#define cmax(a, b) a = max(a, b)
#define cmin(a, b) a = min(a, b)
#define IO(x) freopen(#x ".in", "r", stdin), freopen(#x ".out", "w", stdout);
using namespace std;

struct Edge {
  int x, y, z;
};

int main() {
#ifndef ONLINE_JUDGE
  IO(1);
#endif
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

  int n, m, rt;
  cin >> n >> m >> rt;
  V<Edge> a(m + 5);
  For(i, 1, m) cin >> a[i].x >> a[i].y >> a[i].z;

  int Ans = 0;
  while (1) {
    Vi mn(n + 5, Inf), pre(n + 5);
    mn[rt] = 0;
    For(i, 1, m) if (mn[a[i].y] > a[i].z && a[i].x != a[i].y) {
      mn[a[i].y] = a[i].z, pre[a[i].y] = a[i].x;
    }
    For(i, 1, n) if (i != rt && !pre[i]) return cout << "-1\n", 0;
    pre[rt] = rt;
    Vi id(n + 5), vis(n + 5);
    int cnt = 0;
    For(i, 1, n) {
      Ans += mn[i];
      int t = i;
      for (; !id[t] && vis[t] != i; t = pre[t]) vis[t] = i;
      if (t != rt && !id[t]) {
        id[t] = ++cnt;
        for (int y = pre[t]; y != t; y = pre[y]) id[y] = cnt;
      }
    }
    if (!cnt) return cout << Ans << '\n', 0;
    For(i, 1, n) if (!id[i]) id[i] = ++cnt;
    For(i, 1, m) {
      if (id[a[i].x] != id[a[i].y]) a[i].z -= mn[a[i].y];
      a[i].x = id[a[i].x], a[i].y = id[a[i].y];
    }
    n = cnt, rt = id[rt];
  }
}