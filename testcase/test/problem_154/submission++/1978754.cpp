#pragma GCC optimize("2", "3", "Ofast")
#define mmdxmqwq(x) <x>
#include mmdxmqwq(bits/stdc++.h)
#define all(x) x.begin(), x.end()
#define pb push_back
#define eb emplace_back
#define MP make_pair
#define MT make_tuple
#define IT iterator
#define fi first
#define se second
#define For(i, a, b) for (int i = (int)(a); i <= (int)(b); ++i)
#define Rep(i, a, b) for (int i = (int)(a); i >= (int)(b); --i)
#define CLR(a, v) memset(a, v, sizeof(a))
#define CPY(a, b) memcpy(a, b, sizeof(a))
#define debug cout << "ztxakking\n"
#define y0 ztxaknoi
#define y1 ztxakioi
using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
using uint = unsigned;
using pii = pair <int, int>;
using pll = pair <ll, ll>;
using vi = vector <int>;
template <typename T>
using V = vector <T>;
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
const int md = 998244353;
int n, m, k, fac[22], ifac[22], inv[22], cnt[1 << 21], f[1 << 21][22];
int qpow(int x, int p) {
  int ans = 1;
  for (; p; p /= 2, x = 1ll * x * x % md) {
    if (p & 1) ans = 1ll * ans * x % md;
  }
  return ans;
}
int add(int x, int y) { if (x + y >= md) return x + y - md; else return x + y; }
int sub(int x, int y) { if (x < y) return x - y + md; else return x - y; }
void Add(int &x, int y) { x = add(x, y); }
void Sub(int &x, int y) { x = sub(x, y); }
void Inv(int *A, int n) {
  static int B[22];
  B[0] = qpow(A[0], md - 2);
  For(i, 1, n) {
    int sum = 0;
    For(j, 1, i) Sub(sum, 1ll * A[j] * B[i - j] % md);
    B[i] = 1ll * sum * B[0] % md;
  }
  For(i, 0, n) A[i] = B[i];
}
void Ln(int *A, int n) {
  static int B[22];
  B[0] = 0;
  For(i, 1, n) {
    int &sum = B[i] = 1ll * A[i] * i % md;
    For(j, 1, i - 1) Sub(sum, 1ll * A[j] * B[i - j] % md);
  }
  For(i, 0, n) A[i] = 1ll * B[i] * inv[i] % md;
}
void Exp(int *A, int n) {
  static int B[22];
  B[0] = 1;
  For(i, 1, n) A[i] = 1ll * A[i] * i % md;
  For(i, 1, n) {
    int sum = 0;
    For(j, 0, i - 1) Add(sum, 1ll * B[j] * A[i - j] % md);
    B[i] = 1ll * sum * inv[i] % md;
  }
  For(i, 0, n) A[i] = B[i];
}
void Left(int *A, int n, int t) {
  For(i, 0, n - t) A[i] = A[i + t];
  For(i, max(0, n - t + 1), n) A[i] = 0;
}
void Right(int *A, int n, int t) {
  Rep(i, n, t) A[i] = A[i - t];
  For(i, 0, min(n, t - 1)) A[i] = 0;
}
void Power(int *A, int n, int k) {
  int pos = -1; For(i, 0, n) if (A[i]) { pos = i; break; } if (pos == -1) return ;
  int W = A[pos], I = qpow(W, md - 2); Left(A, n, pos); For(i, 0, n) A[i] = 1ll * A[i] * I % md;
  Ln(&A[0], n); For(i, 0, n) A[i] = 1ll * A[i] * k % md; Exp(&A[0], n);
  For(i, 0, n) A[i] = 1ll * A[i] * qpow(W, k) % md; Right(A, n, pos * k);
}
int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  fac[0] = 1; For(i, 1, 21) fac[i] = 1ll * fac[i - 1] * i % md;
  ifac[21] = qpow(fac[21], md - 2); Rep(i, 21, 1) ifac[i - 1] = 1ll * ifac[i] * i % md;
  For(i, 1, 22) inv[i] = 1ll * ifac[i] * fac[i - 1] % md;
  cin >> n >> m >> k;
  For(i, 1, (1 << n) - 1) cnt[i] = cnt[i >> 1] + (i & 1);
  For(i, 1, m) { int s; cin >> s; ++f[s][cnt[s]]; }
  For(j, 0, n - 1) For(i, 0, (1 << n) - 1) if (i >> j & 1) { For(x, 0, n) Add(f[i][x], f[i ^ 1 << j][x]); }
  For(i, 0, (1 << n) - 1) {
    static int A[22], B[22], C[22];
    For(j, 0, n) A[j] = f[i][j]; Power(A, n, k); For(j, 0, n) A[j] = 1ll * A[j] * ifac[k] % md;
    For(j, 0, n - 1) B[j] = 1ll * f[i][j + 1] * (j + 1) % md;
    int pw = 1, &sum = C[0] = 1; For(j, 1, k) pw = 1ll * pw * f[i][0] % md, Add(sum, 1ll * pw * ifac[j] % md);
    For(j, 0, n - 1) { int sum = 0; For(x, 0, j) Add(sum, 1ll * B[x] * sub(C[j - x], A[j - x]) % md); C[j + 1] = 1ll * sum * inv[j + 1] % md; }
    For(j, 0, n) f[i][j] = C[j];
  }
  For(j, 0, n - 1) For(i, 0, (1 << n) - 1) if (i >> j & 1) Sub(f[i][n], f[i ^ 1 << j][n]);
  cout << f[(1 << n) - 1][n] << '\n';
  return 0;
}