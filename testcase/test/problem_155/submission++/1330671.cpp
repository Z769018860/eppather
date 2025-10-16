#include <bits/stdc++.h>
#ifdef __LOCAL
#define debug(x) std::cerr << __LINE__ << ": " << #x << " = " << (x) << '\n'
#define debugArray(x, n)                                      \
  std::cerr << __LINE__ << ": " << #x << " = {";              \
  for (long long hoge = 0; (hoge) < (long long)(n); ++(hoge)) \
    std::cerr << ((hoge) ? "," : "") << x[hoge];              \
  std::cerr << "}" << '\n'
#define debugMatrix(x, h, w)                                              \
  std::cerr << __LINE__ << ": " << #x << " =\n";                          \
  for (long long hoge = 0; (hoge) < (long long)(h); ++(hoge)) {           \
    std::cerr << ((hoge ? " {" : "{{"));                                  \
    for (long long fuga = 0; (fuga) < (long long)(w); ++(fuga))           \
      std::cerr << ((fuga ? ", " : "")) << x[hoge][fuga];                 \
    std::cerr << "}" << (hoge + 1 == (long long)(h) ? "}" : ",") << '\n'; \
  }
#else
#define debug(x) (void(0))
#define debugArray(x, n) (void(0))
#define debugMatrix(x, h, w) (void(0))
#endif

#define TEST(s)                                 \
  if (!(s)) {                                   \
    cout << __LINE__ << " " << #s << std::endl; \
    exit(-1);                                   \
  }
#include <ctime>
double tick() {
  static clock_t oldtick;
  clock_t newtick = clock();
  double diff = 1.0 * (newtick - oldtick) / CLOCKS_PER_SEC;
  oldtick = newtick;
  return diff;
}

template <typename T>
using RankedSPS = std::vector<std::array<T, 21>>;
template <typename T>
using EGF = std::array<T, 22>;

#define SUBSET_REP(i, j, n)                                 \
  for (int _ = 1; _ < (n); _ <<= 1)                         \
    for (int __ = 0, _2 = _ << 1, i, j; __ < (n); __ += _2) \
      for (int ___ = 0; ___ < _ && (i = (j = __ | ___) | _, 1); ___++)

template <typename T>
inline void zeta_trans(std::vector<T> &f) {
  const int n = f.size();
  SUBSET_REP(S, U, n) f[S] += f[U];
}

template <typename T>
inline void moebius_trans(std::vector<T> &f) {
  const int n = f.size();
  SUBSET_REP(S, U, n) f[S] -= f[U];
}

template <typename T>
inline RankedSPS<T> ranked_zeta_trans(const std::vector<T> &f) {
  const int n = f.size();
  RankedSPS<T> ret(n);
  for (int S = 0; S < n; S++) ret[S][__builtin_popcount(S)] = f[S];
  SUBSET_REP(S, U, n)
  for (int d = __builtin_popcount(S); d--;) ret[S][d] += ret[U][d];
  return ret;
}

template <typename T>
inline std::vector<T> ranked_moebius_trans(RankedSPS<T> &&mat) {
  const int n = mat.size(), D = __builtin_ctz(n);
  std::vector<T> ret(n);
  SUBSET_REP(S, U, n)
  for (int c = __builtin_popcount(S), d = std::min(2 * c, D); d >= c; d--)
    mat[S][d] -= mat[U][d];
  for (int S = n; S--;) ret[S] = mat[S][__builtin_popcount(S)];
  return ret;
}

template <typename T>
inline RankedSPS<T> multipliy(const RankedSPS<T> &F, const RankedSPS<T> &G) {
  const int n = F.size(), D = __builtin_ctz(n);
  RankedSPS<T> ret(n);
  for (int S = n, c, d, e; S--;)
    for (c = __builtin_popcount(S), d = std::min(2 * c, D); d >= c; d--)
      for (e = d - c; e <= c; e++) ret[S][d] += F[S][e] * G[S][d - e];
  return ret;
}

template <typename T>
inline std::vector<T> subset_conv_naive(const std::vector<T> &f,
                                        const std::vector<T> &g) {
  const int n = f.size();
  std::vector<T> ret(n);
  for (int s = n, t; s--;)
    for (ret[t = s] = f[0] * g[s]; t; (--t) &= s) ret[s] += f[t] * g[s ^ t];
  return ret;
}

template <class T>
inline std::vector<T> subset_convolution(std::vector<T> f, std::vector<T> g) {
  const int n = f.size(), D = __builtin_ctz(n);
  if (D <= 12) return subset_conv_naive(f, g);
  assert(__builtin_popcount(n) == 1 && f.size() == g.size());
  auto F = ranked_zeta_trans(f), G = ranked_zeta_trans(g);
  return ranked_moebius_trans(multipliy(F, G));
}


template <class T>
inline std::vector<T> subset_composite(const std::vector<T> &f,
                                       const EGF<T> &F) {
  const int sz = f.size(), m = __builtin_ctz(sz);
  assert(sz == 1 << m);
  assert(f.at(0) == 0);
  std::vector<T> h[m + 1], c;
  for (int i = 0; i <= m; i++) h[i].reserve(1 << i), h[i] = {F[i]};
  for (int k = 1, l = 1, l2 = 2; k <= m; k++, l <<= 1, l2 = l << 1)
    for (int j = 0; j <= m - k; j++) {
      c = subset_convolution(h[j + 1], {f.begin() + l, f.begin() + l2});
      std::copy(c.begin(), c.end(), std::back_inserter(h[j]));
    }
  return h[0];
}


template <class T>
inline std::vector<T> subset_exp(const std::vector<T> &f) {
  const int sz = f.size();
  assert(sz == 1 << __builtin_ctz(sz));
  assert(f.at(0) == 0);
  std::vector<T> ret{T(1)}, c;
  ret.reserve(sz);
  for (int l = 1, l2 = 2; l < sz; l <<= 1, l2 = l << 1) {
    c = subset_convolution(ret, {f.begin() + l, f.begin() + l2});
    std::copy(c.begin(), c.end(), std::back_inserter(ret));
  }
  return ret;
}


template <class T>
inline std::vector<T> subset_log(std::vector<T> f) {
  const int sz = f.size(), m = __builtin_ctz(sz);
  assert(sz == 1 << m);
  assert(f.at(0) == T(1));
  static EGF<T> F = {0, 1};
  for (int i = 2; i <= m; i++) F[i] = -F[i - 1] * (i - 1);
  return f[0] = 0, subset_composite(f, F);
}


template <class T>
inline std::vector<T> subset_pow(std::vector<T> f, std::uint64_t k) {
  const int sz = f.size(), m = __builtin_ctz(sz);
  assert(sz == 1 << m);
  EGF<T> F = {1};
  int i = 1, ed = std::min<std::uint64_t>(m, k);
  for (; i <= ed; i++) F[i] = F[i - 1] * (k - i + 1);
  T pw = 1, bs = f[0];
  for (auto e = k - --i; e; e >>= 1, bs *= bs)
    if (e & 1) pw *= bs;
  for (; i >= 0; i--, pw *= f[0]) F[i] *= pw;
  return f[0] = 0, subset_composite(f, F);
}

template <class T>
T tutte_polynomial(const std::vector<std::vector<int>> &adj, T x, T y) {
  const int n = adj.size(), N = 1 << n;
  assert(int(adj[0].size()) == n);
  int sum[N], s, ed, t, used[n] = {0}, lim = 2, i, j;
  T ret, fun_[112345] = {0, 1};
  auto fun = [&](int m) {
    for (; lim <= m; lim++) fun_[lim] = fun_[lim - 1] * y + 1;
    return fun_[m];
  };
  auto dfs = [&](auto self, int v) -> void {
    for (int u = n; u--;)
      if (adj[v][u] > 0 && !used[u]) used[u] = true, self(self, u);
  };
  std::vector<T> g = {0}, h;
  for (g.reserve(N), h.reserve(N), i = 0; i < n; i++) {
    for (sum[0] = j = 0; j < i; j++)
      for (ed = (s = t = 1 << j) << 1; s < ed; s++)
        sum[s] = sum[s ^ t] + adj[i][j];
    for (h.resize(s = 1 << i); s--;) h[s] = g[s] * fun(sum[s]);
    h = subset_exp(h), std::copy(h.begin(), h.end(), std::back_inserter(g));
  }
  for (t = ~0, i = n; i--;)
    if (!used[i]) t ^= 1 << i, used[i] = true, dfs(dfs, i);
  for (x -= 1, s = N; --s &= t;) g[s] *= x;
  for (t = 0, i = n; i--;) t += adj[i][i];
  for (ret = subset_exp(g)[N - 1]; t; t >>= 1, y *= y)
    if (t & 1) ret *= y;
  return ret;
}

namespace internal {
template <std::uint64_t mod, std::uint64_t prim_root, class ModInt>
struct ModIntImpl {
  static constexpr std::uint64_t modulo() { return mod; }
  static constexpr std::uint64_t pr_rt() { return prim_root; }
  friend std::ostream &operator<<(std::ostream &os, const ModInt &rhs) {
    return os << rhs.val();
  }
};
}  
template <std::uint64_t mod, std::uint64_t prim_root = 0>
class ModInt
    : public internal::ModIntImpl<mod, prim_root, ModInt<mod, prim_root>> {
  using u64 = std::uint64_t;
  static constexpr u64 mul_inv(u64 n, int e = 6, u64 x = 1) {
    return e == 0 ? x : mul_inv(n, e - 1, x * (2 - x * n));
  }
  static constexpr u64 inv = mul_inv(mod, 6, 1), r2 = -__uint128_t(mod) % mod;
  static constexpr u64 init(u64 w) { return reduce(__uint128_t(w) * r2); }
  static constexpr u64 reduce(const __uint128_t w) {
    return u64(w >> 64) + mod - ((__uint128_t(u64(w) * inv) * mod) >> 64);
  }
  u64 x;

 public:
  constexpr ModInt() : x(0) {}
  constexpr ModInt(std::int64_t n) : x(init(n < 0 ? mod - (-n) % mod : n)) {}
  static constexpr u64 norm(u64 w) { return w - (mod & -(w >= mod)); }
  constexpr ModInt operator-() const {
    ModInt ret;
    return ret.x = ((mod << 1) & -(x != 0)) - x, ret;
  }
  constexpr ModInt &operator+=(const ModInt &rhs) {
    return x += rhs.x - (mod << 1), x += (mod << 1) & -(x >> 63), *this;
  }
  constexpr ModInt &operator-=(const ModInt &rhs) {
    return x -= rhs.x, x += (mod << 1) & -(x >> 63), *this;
  }
  constexpr ModInt &operator*=(const ModInt &rhs) {
    return this->x = reduce(__uint128_t(this->x) * rhs.x), *this;
  }
  constexpr ModInt &operator/=(const ModInt &rhs) {
    return this->operator*=(rhs.inverse());
  }
  ModInt operator+(const ModInt &rhs) const { return ModInt(*this) += rhs; }
  ModInt operator-(const ModInt &rhs) const { return ModInt(*this) -= rhs; }
  ModInt operator*(const ModInt &rhs) const { return ModInt(*this) *= rhs; }
  ModInt operator/(const ModInt &rhs) const { return ModInt(*this) /= rhs; }
  bool operator==(const ModInt &rhs) const { return norm(x) == norm(rhs.x); }
  bool operator!=(const ModInt &rhs) const { return !(*this == rhs); }
  constexpr ModInt pow(std::uint64_t k) const {
    ModInt ret = ModInt(1);
    for (ModInt base = *this; k; k >>= 1, base *= base)
      if (k & 1) ret *= base;
    return ret;
  }
  constexpr ModInt inverse() const { return pow(mod - 2); }
  constexpr ModInt sqrt() const {
    if (*this == ModInt(0) || mod == 2) return *this;
    if (pow((mod - 1) >> 1) != 1) return ModInt(0);  
    ModInt ONE = 1, b(2), w(b * b - *this);
    while (w.pow((mod - 1) >> 1) == ONE) b += ONE, w = b * b - *this;
    auto mul = [&](std::pair<ModInt, ModInt> u, std::pair<ModInt, ModInt> v) {
      ModInt a = (u.first * v.first + u.second * v.second * w);
      ModInt b = (u.first * v.second + u.second * v.first);
      return std::make_pair(a, b);
    };
    std::uint64_t e = (mod + 1) >> 1;
    auto ret = std::make_pair(ONE, ModInt(0));
    for (auto bs = std::make_pair(b, ONE); e; e >>= 1, bs = mul(bs, bs))
      if (e & 1) ret = mul(ret, bs);
    return ret.first.val() * 2 < mod ? ret.first : -ret.first;
  }
  constexpr u64 val() const {
    u64 ret = reduce(x) - mod;
    return ret + (mod & -(ret >> 63));
  }
  friend std::istream &operator>>(std::istream &is, ModInt &rhs) {
    return is >> rhs.x, rhs.x = init(rhs.x), is;
  }
};
template <std::uint64_t pr_rt>
struct ModInt<2, pr_rt> : internal::ModIntImpl<2, pr_rt, ModInt<2, pr_rt>> {
  constexpr ModInt(std::int64_t n = 0) : x(n & 1) {}
  constexpr ModInt operator-() const { return *this; }
  constexpr ModInt &operator+=(const ModInt &rhs) { return x ^= rhs.x, *this; }
  constexpr ModInt &operator-=(const ModInt &rhs) { return x ^= rhs.x, *this; }
  constexpr ModInt &operator*=(const ModInt &rhs) { return x &= rhs.x, *this; }
  constexpr ModInt &operator/=(const ModInt &rhs) { return x &= rhs.x, *this; }
  ModInt operator+(const ModInt &rhs) const { return ModInt(*this) += rhs; }
  ModInt operator-(const ModInt &rhs) const { return ModInt(*this) -= rhs; }
  ModInt operator*(const ModInt &rhs) const { return ModInt(*this) *= rhs; }
  ModInt operator/(const ModInt &rhs) const { return ModInt(*this) /= rhs; }
  bool operator==(const ModInt &rhs) const { return x == rhs.x; }
  bool operator!=(const ModInt &rhs) const { return !(*this == rhs); }
  constexpr ModInt pow(std::uint64_t k) const { return !k ? ModInt(1) : *this; }
  constexpr ModInt sqrt() const { return *this; }
  constexpr ModInt inverse() const { return *this; }
  constexpr std::uint64_t val() const { return x; }
  friend std::istream &operator>>(std::istream &is, ModInt &rhs) {
    return is >> rhs.x, is;
  }

 private:
  bool x;
};

using namespace std;
signed LOJ155() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  using Mint = ModInt<998244353>;
  int n;
  cin >> n;
  vector<vector<int>> G(n, vector<int>(n));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) cin >> G[i][j];
  Mint x, y;
  cin >> x >> y;
  cout << tutte_polynomial(G, x, y) << '\n';
  return 0;
}

signed main() {
  LOJ155();
  return 0;
}