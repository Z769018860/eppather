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

#define ll long long
const int P = 998244353;
struct mint {
  int d;
  mint() = default;
  mint(int x) : d(x < 0 ? x + P : x) {}
  mint(ll x) : d(int(x % P)) {}
  explicit operator int() { return d; }
  friend istream &operator>>(istream &x, mint &y) { return x >> y.d; }
  friend ostream &operator<<(ostream &x, mint y) { return x << y.d; }
  friend mint operator+(mint x, mint y) {
    return (x.d += y.d) < P ? x.d : x.d - P;
  }
  mint &operator+=(mint z) { return (d += z.d) < P ? d : d -= P, *this; }
  friend mint operator-(mint x, mint y) {
    return (x.d -= y.d) < 0 ? x.d + P : x.d;
  }
  mint &operator-=(mint z) { return (d -= z.d) < 0 ? d += P : d, *this; }
  friend mint operator*(mint x, mint y) { return int(1ll * x.d * y.d % P); }
  mint &operator*=(mint z) { return d = int(1ll * d * z.d % P), *this; }
  static mint qpow(int x, ll y = P - 2) {
    int z = 1;
    for (; y; y >>= 1, x = int(1ll * x * x % P))
      if (y & 1) z = int(1ll * x * z % P);
    return z;
  }
  friend mint operator/(mint x, mint y) { return x *= qpow(y.d); }
  mint &operator/=(mint z) { return (*this) *= qpow(z.d); }
  mint inv() { return qpow(d); }
  mint pow(mint z) { return qpow(d, z.d); }
  mint pow(int z) { return z >= 0 ? qpow(d, z) : 1 / qpow(d, -z); }
  mint operator+() { return d; }
  mint operator-() { return P - d; }
};
mint operator""_m(unsigned ll x) { return mint(int(x)); }

mt19937 rnd(114);

V<V<mint>> BM(V<mint> &f, int n) {
  V<V<mint>> r(n + 5, V<mint>(n + 5));
  Vi l(n + 5);
  V<mint> T(n + 5);
  r[0][0] = 1;
  int p = 0;
  For(i, 1, n) {
    For(j, 0, l[i - 1]) T[i] += r[i - 1][j] * f[i - j];
    if (!T[i].d)
      l[i] = l[i - 1], r[i] = r[i - 1];
    else {
      if (!p)
        r[i][0] = 1, l[i] = i;
      else {
        l[i] = max(l[i - 1], l[p - 1] + i - p);
        mint tmp = T[i] / T[p];
        For(j, 0, l[p - 1]) r[i][i - p + j] -= tmp * r[p - 1][j];
        For(j, 0, l[i - 1]) r[i][j] += r[i - 1][j];
      }
      p = i;
    }
  }
  For(i, 0, n) r[i].resize(l[i] + 1);
  return r;
}

int main() {
#ifndef ONLINE_JUDGE
  IO(1);
#endif
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

  int n;
  cin >> n;
  V<V<pair<int, mint>>> a(n + 5);
  V<mint> b(n + 5);

  For(i, 1, n) {
    for (int j = 1, x; j <= n; j++) {
      cin >> x;
      if (x) a[i].pb({j, x});
    }
    cin >> b[i];
  }

  V<V<mint>> pw(2 * n + 5, V<mint>(n + 5));
  For(i, 1, n) pw[1][i] = b[i];
  For(k, 2, 2 * n + 1) For(j, 1, n) for (auto i : a[j]) pw[k][j] +=
      pw[k - 1][i.fi] * i.se;

  V<mint> u(n + 5), f(2 * n + 5);
  For(i, 1, n) u[i] = (ll)rnd();
  For(i, 1, 2 * n + 1) For(j, 1, n) f[i] += pw[i][j] * u[j];
  V<mint> r = BM(f, 2 * n + 1)[2 * n + 1];

  int m = sz(r) - 1;
  mint s = 0;
  For(i, 0, m) s += r[i] * f[m - i];
  V<mint> g(m + 5);
  For(i, 1, m) For(j, 1, n) g[j] += pw[i][j] * r[m - i];
  mint Inv = (-r[m]).inv();
  For(i, 1, n) cout << g[i] * Inv << ' ';
}