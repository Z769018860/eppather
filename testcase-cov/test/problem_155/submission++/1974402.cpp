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
  mint(int x) : d(x) {}
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

V<mint> Inv(25);

struct poly : V<mint> {
  poly(int n) : V<mint>(n + 5) {}
  friend poly operator+(poly &a, poly &b) {
    if (sz(a) > sz(b)) a.swap(b);
    auto c = b;
    For(i, 0, sz(a) - 1) c[i] += a[i];
    return c;
  }
  friend poly operator-(poly &a, poly &b) {
    int ff = 0;
    if (sz(a) < sz(b)) a.swap(b), ff = 1;
    auto c = a;
    For(i, 0, sz(b) - 1) c[i] -= b[i];
    if (ff)
      for (auto &x : c) x = -x;
    return c;
  }
};

void Exp(mint *A, int n) {
  poly B(n);
  B[0] = 1;
  For(i, 1, n) {
    For(j, 1, i) B[i] += j * A[j] * B[i - j];
    B[i] *= Inv[i];
  }
  For(i, 0, n) A[i] = B[i];
}

struct set_poly : V<poly> {
  set_poly(int n) : V<poly>(1 << n, poly(n)) {}
};

void FMT(poly *A, int n, int ff) {
  For(j, 0, n - 1) For(i, 1, (1 << n) - 1) if ((i >> j) & 1) A[i] =
      ff ? A[i] + A[i - (1 << j)] : A[i] - A[i - (1 << j)];
}

struct Ace_taffy {
  Ace_taffy(int n) : f(n + 5) { For(i, 1, n) f[i] = i; }
  int get(int k) { return f[k] == k ? k : f[k] = get(f[k]); }
  void merge(int x, int y) { f[get(x)] = get(y); }
  Vi f;
};

int main() {
#ifndef ONLINE_JUDGE
  IO(1);
#endif
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

  int n;
  cin >> n;
  For(i, 1, n) Inv[i] = 1_m / i;
  Vi d(n + 5);
  Ace_taffy dsu(n);
  For(i, 0, n - 1) for (int j = 0, x; j < n; j++) {
    cin >> x, d[i] |= x << j;
    if (x) dsu.merge(i, j);
  }

  mint X, Y;
  cin >> X >> Y;

  V<mint> C(n + 5);
  mint t = 1;
  For(i, 1, n) C[i] = C[i - 1] + t, t *= Y;

  Vi cnt(1 << n);
  For(i, 1, (1 << n) - 1) cnt[i] = cnt[i >> 1] + (i & 1);

  set_poly f(n);
  f[0][0] = 1;
  For(i, 0, n - 1) {
    For(j, 0, (1 << i) - 1) For(k, 0, n - 1) f[j + (1 << i)][k + 1] =
        f[j][k] * C[cnt[d[i] & j]];
    FMT(&f[1 << i], i, 1);
    For(j, (1 << i), (1 << (i + 1)) - 1) Exp(&f[j][1], n);
    FMT(&f[1 << i], i, 0);
  }

  int S = 0;
  For(i, 0, n - 1) if (dsu.get(i) == i) S |= 1 << i;
  For(i, 0, (1 << n) - 1) if (!(i & S)) For(j, 0, n) f[i][j] *= X - 1;
  FMT(&f[0], n, 1);
  For(i, 0, (1 << n) - 1) Exp(&f[i][0], n);
  FMT(&f[0], n, 0);

  cout << f[(1 << n) - 1][n] << '\n';
}