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

mt19937 rnd(time(0));

int main() {
#ifndef ONLINE_JUDGE
  IO(1);
#endif
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

  int n, D;
  cin >> n >> D;

  V<Vi> a(n + 5, Vi(D));
  For(i, 1, n) For(j, 0, D - 1) cin >> a[i][j];
  Vi p(n + 5);
  For(i, 1, n) p[i] = i;
  shuffle(&p[1], &p[n + 1], rnd);

  Vi mat(n + 5), vis(n + 5);
  For(i, 1, n) {
    int x = p[i];
    Vi sta;
    for (;; x = mat[x]) {
      x = a[x][rnd() % D];
      while (vis[x]) vis[sta.back()] = 0, sta.pop_back();
      sta.pb(x), vis[x] = 1;
      if (!mat[x]) break;
    }
    int las = p[i];
    for (int y : sta) swap(las, mat[y]), vis[y] = 0;
  }

  Vi res(n + 5);
  For(i, 1, n) res[mat[i]] = i;
  For(i, 1, n) cout << res[i] << ' ';
  cout << '\n';
}