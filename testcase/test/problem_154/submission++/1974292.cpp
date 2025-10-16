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

V<mint> Inv(25), jie(25, 1), ni(25);

struct poly : V<mint> {
  poly(int n) : V<mint>(n + 1) {}
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
      for (auto &x : c) x *= P - 1;
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

void Ln(mint *A, int n) {
  poly B(n);
  For(i, 1, n) {
    For(j, 1, i - 1) B[i] -= j * B[j] * A[i - j];
    B[i] = A[i] + B[i] * Inv[i];
  }
  For(i, 0, n) A[i] = B[i];
}

void K_Exp(mint *a, int n, int K) {
  int t = n + 1;
  For(i, 0, n) if (a[i].d) {
    t = i;
    break;
  }
  if (t > n) return;

  mint II = a[t].inv();
  poly b(n);
  For(i, t, n) b[i - t] = a[i] * II;
  Ln(&b[0], n);
  For(i, 0, n) b[i] *= K;
  Exp(&b[0], n);
  II = II.inv().pow(K);
  Rep(i, n, 0) b[i] = i >= K * t ? b[i - K * t] * II * ni[K] : 0;

  mint s = 1;
  poly f(n);
  For(i, 0, K) f[0] += s * ni[i], s *= a[0];
  For(i, 1, n) {
    For(j, 0, i - 1) f[i] += (i - j) * a[i - j] * (f[j] - b[j]);
    f[i] *= Inv[i];
  }
  For(i, 0, n) a[i] = f[i];
}

struct set_poly : V<poly> {
  set_poly(int n) : V<poly>(1 << n, poly(n)) {}
  friend void FMT(set_poly &A, int n, int ff) {
    For(j, 0, n - 1) For(i, 1, (1 << n) - 1) if ((i >> j) & 1) A[i] =
        ff ? A[i] + A[i - (1 << j)] : A[i] - A[i - (1 << j)];
  }
};

int main() {
#ifndef ONLINE_JUDGE
  IO(1);
#endif
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

  int n, m, K;
  cin >> n >> m >> K;
  For(i, 1, n) Inv[i] = 1_m / i;

  For(i, 1, n) jie[i] = jie[i - 1] * i;
  ni[n] = jie[n].inv();
  Rep(i, n, 1) ni[i - 1] = ni[i] * i;

  Vi cnt(1 << n);
  For(i, 0, (1 << n) - 1) cnt[i] = cnt[i >> 1] + (i & 1);

  set_poly f(n);
  for (int i = 1, x; i <= m; i++) cin >> x, f[x][cnt[x]] += 1;
  FMT(f, n, 1);
  For(i, 0, (1 << n) - 1) K_Exp(&f[i][0], n, K);
  FMT(f, n, 0);

  cout << f[(1 << n) - 1][n] << '\n';
}