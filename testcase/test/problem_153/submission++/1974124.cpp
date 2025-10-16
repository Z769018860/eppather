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
int main() {
#ifndef ONLINE_JUDGE
  IO(1);
#endif
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

  int n, m, K;
  cin >> n >> m >> K;

  Vi a(1 << n);
  for (int i = 1, x; i <= m; i++) cin >> x, a[x]++;
  For(j, 0, n - 1) For(i, 1, (1 << n) - 1) if ((i >> j) & 1) a[i] +=
      a[i - (1 << j)];

  V<mint> jie(m + 5, 1), ni(m + 5), s(m + 5);
  For(i, 1, m) jie[i] = jie[i - 1] * i;
  ni[m] = jie[m].inv();
  Rep(i, m, 1) ni[i - 1] = ni[i] * i;
  For(i, 0, m) For(j, 0, min(i, K)) s[i] += jie[i] * ni[i - j] * ni[j];

  V<mint> f(1 << n);
  For(i, 0, (1 << n) - 1) f[i] = s[a[i]];
  For(j, 0, n - 1) For(i, 1, (1 << n) - 1) if ((i >> j) & 1) f[i] -=
      f[i - (1 << j)];
  cout << f[(1 << n) - 1] << '\n';
}