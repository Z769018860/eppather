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
const int P = 1e9 + 7;
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

const int N = 11, M = 10;
int K1, K2;
mint C[N][N];
struct node {
  node() { memset(a, 0, sizeof(a)), A = B = 0; }
  mint A, B, a[N][N];
};

node operator*(node x, node y) {
  node res = x;
  res.A += y.A, res.B += y.B;
  V<mint> pw1(K1 + 1, 1), pw2(K2 + 1, 1);
  For(i, 1, K1) pw1[i] = pw1[i - 1] * x.A;
  For(i, 1, K2) pw2[i] = pw2[i - 1] * x.B;
  For(i, 0, K1) For(j, 0, K2) For(l, 0, i) For(r, 0, j) res.a[i][j] +=
      C[i][l] * C[j][r] * y.a[l][r] * pw1[i - l] * pw2[j - r];
  return res;
}

node qp(node a, ll b) {
  node ans;
  for (; b; b >>= 1, a = a * a)
    if (b & 1) ans = ans * a;
  return ans;
}

node solve(int A, int B, int C, int n, node R, node U) {
  ll m = (1ll * A * n + B) / C;
  if (!m) return qp(R, n);
  if (max(A, B) >= C)
    return qp(U, B / C) * solve(A % C, B % C, C, n, qp(U, A / C) * R, U);
  return qp(R, (C - B - 1) / A) * U *
         solve(C, (C - B - 1) % A, A, m - 1, U, R) *
         qp(R, n - (1ll * m * C - B - 1) / A);
}

int main() {
#ifndef ONLINE_JUDGE
  IO(1);
#endif
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  For(i, 0, M) {
    C[i][0] = 1;
    For(j, 1, i) C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
  }
  int _;
  for (cin >> _; _--;) {
    int n, A, B, C;
    cin >> n >> A >> B >> C >> K1 >> K2;
    node U, R;
    R.A = 1, U.B = 1;
    For(i, 0, K1) R.a[i][0] = 1;
    mint ans = solve(A, B, C, n, R, U).a[K1][K2];
    if (!K1) {
      mint t = 1;
      For(i, 1, K2) t *= B / C;
      ans += t;
    }
    cout << ans << '\n';
  }
}