#pragma GCC optimize("Ofast")
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define ff first
#define ss second

#define typet typename T
#define typeu typename U
#define types typename... Ts

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) (void) 0
#endif  

using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using pii = std::pair<int, int>;
using vi = std::vector<int>;
using vl = std::vector<i64>;
using vs = std::vector<std::string>;
using vvi = std::vector<vi>;
using vp = std::vector<pii>;
template <typet> using Heap = std::priority_queue<T, std::vector<T>, std::greater<T>>;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>

template <typet, typeu, typename Comp = std::less<T>>
using ordered_map = __gnu_pbds::tree<T, U, Comp, __gnu_pbds::rb_tree_tag,
                                     __gnu_pbds::tree_order_statistics_node_update>;
template <typet, typeu = std::less<T>> using ordered_set = ordered_map<T, __gnu_pbds::null_type, U>;
template <typet> using ordered_multiset = ordered_set<T, std::less_equal<T>>;
template <typet, typeu = std::greater<T>>
using FastHeap = __gnu_pbds::priority_queue<T, U, __gnu_pbds::thin_heap_tag>;
template <typet, typeu = std::greater<T>>
using JoinHeap = __gnu_pbds::priority_queue<T, U, __gnu_pbds::pairing_heap_tag>;

#define range(x) std::begin(x), std::end(x)

template <typet> bool Min(T& x, const T& y) { return x > y ? x = y, true : false; }
template <typet> bool Max(T& x, const T& y) { return x < y ? x = y, true : false; }
template <typet> T lowbit(T x) { return x & -x; }


template <u32 P> struct Fp {
  u32 v = 0;

  template <typet = int> static constexpr T mod() { return P; }
  template <typet = int> constexpr T val() const { return v; }
  template <typet = int> constexpr operator T() const { return v; }

  constexpr Fp() = default;
  template <typet> constexpr Fp(T x) : v(x % mod()) {
    if constexpr (std::is_signed_v<T>)
      if (v >> 31) v += P;
  }

  friend std::istream& operator>>(std::istream& is, Fp& x) {
    i64 y;
    is >> y;
    x = y;
    return is;
  }
  friend std::ostream& operator<<(std::ostream& os, Fp x) { return os << x.v; }

  friend constexpr bool operator==(Fp lhs, Fp rhs) { return lhs.v == rhs.v; }
  friend constexpr bool operator!=(Fp lhs, Fp rhs) { return lhs.v != rhs.v; }

  constexpr Fp& operator+=(Fp rhs) {
    v += rhs.v;
    if (v >= P) v -= P;
    return *this;
  }
  constexpr Fp& operator-=(Fp rhs) {
    v -= rhs.v;
    if (v >= P) v += P;
    return *this;
  }
  constexpr Fp& operator*=(Fp rhs) {
    v = (u64) v * rhs.v % P;
    return *this;
  }
  constexpr Fp& operator/=(Fp rhs) { return *this *= ~rhs; }
  template <typet> constexpr Fp& operator^=(T rhs) {
    Fp u = *this;
    v = 1;
    u32 n = rhs % (mod() - 1);
    if constexpr (std::is_signed_v<T>)
      if (n >> 31) n += P - 1;
    for (; n; n /= 2) {
      if (n & 1) *this *= u;
      u *= u;
    }
    return *this;
  }
  friend constexpr Fp operator+(Fp lhs, Fp rhs) { return lhs += rhs; }
  friend constexpr Fp operator-(Fp lhs, Fp rhs) { return lhs -= rhs; }
  friend constexpr Fp operator*(Fp lhs, Fp rhs) { return lhs *= rhs; }
  friend constexpr Fp operator/(Fp lhs, Fp rhs) { return lhs /= rhs; }
  template <typet> friend constexpr Fp operator^(Fp lhs, T rhs) { return lhs ^= rhs; }
  constexpr Fp operator+() const { return *this; }
  constexpr Fp operator-() const { return Fp{} - *this; }
  constexpr Fp operator~() const { return *this ^ (mod() - 2); }
  template <typet> constexpr Fp pow(T exp) const { return *this ^ exp; }
};
constexpr u32 get_ntt_proot(u32 p) {
  if (p == 2) return 1;
  if (p == 998244353) return 3;
  for (u32 g = 2; g < p; g++) {
    u64 u = g, v = 1;
    for (u32 m = p / 2; m; m /= 2) {
      if (m & 1) v = v * u % p;
      u = u * u % p;
    }
    if (v != 1) return g;
  }
  return -1;
}
template <u32 P> int tonelli_shanks(Fp<P> x) {
  using Z = Fp<P>;
  if (P == 2 || x == 0 || x == 1) return x;
  if (x.pow(P / 2) != 1) return -1;
  if (P & 2) return x.pow(P / 4 + 1);
  int s = __builtin_ctz(P ^ 1), q = P >> s;
  Z c = 2;
  while (c.pow(P / 2) == 1) c += 1;
  c ^= q;
  Z r = x.pow(q / 2 + 1), t = x.pow(q);
  while (t != 1) {
    int i = 0;
    for (Z u = t; u != 1; i++) u *= u;
    for (s--; i < s; s--) c *= c;
    r *= c;
    c *= c;
    t *= c;
  }
  return r;
}

template <typet> struct Combination {
  inline static std::vector<T> inv{0}, fac{1}, fiv{1};
  inline static int N = 1;
  static void fix(int n) {
    for (; N < n; N *= 2) {
      inv.resize(N * 2);
      fac.resize(N * 2);
      fiv.resize(N * 2);
      for (int i = N; i < N * 2; i++) {
        inv[i] = inv[T::mod() % i] * (T::mod() - T::mod() / i) + (i == 1);
        fac[i] = fac[i - 1] * i;
        fiv[i] = fiv[i - 1] * inv[i];
      }
    }
  }
  static T inverse(int n) {
    fix(n + 1);
    return inv[n];
  }
  static T factorial(int n) {
    fix(n + 1);
    return fac[n];
  }
  static T factinv(int n) {
    fix(n + 1);
    return fiv[n];
  }
  static T C(int n, int m) {
    fix(n + 1);
    return fac[n] * fiv[m] * fiv[n - m];
  }
};

template <u32 P> void reserve_fft_roots(std::vector<Fp<P>>& wn, int n) {
  int m = wn.size();
  if (n <= m) return;
  wn.resize(n);
  auto r = Fp<P>{get_ntt_proot(P)}.pow((P - 1) / n);
  wn[n / 2] = 1;
  for (int i = n / 2 + 1; i < n; i++) wn[i] = wn[i - 1] * r;
  for (int i = n / 2 - 1; i >= m; i--) wn[i] = wn[i * 2];
}
template <typet> void reserve_fft_roots(std::vector<std::complex<T>>& wn, int n) {
  int m = wn.size();
  if (n <= m) return;
  wn.resize(n);
  for (int i = 0; i < n / 2; i++) wn[n / 2 + i] = std::polar<T>(1, M_PI * 2 * i / n);
  for (int i = n / 2 - 1; i >= m; i--) wn[i] = wn[i * 2];
}

template <typet> void butterfly(T* a, int n) {
  static vi rev;
  if ((int) rev.size() != n) {
    rev.resize(n);
    for (int i = 0; i < n; i++) {
      rev[i] = rev[i / 2] / 2;
      if (i & 1) rev[i] |= n / 2;
    }
  }
  for (int i = 0; i < n; i++)
    if (i < rev[i]) std::swap(a[i], a[rev[i]]);
}

template <typet> void dft2d(T* x, T* y) {
  T u = *x, v = *y;
  *x = u + v, *y = u - v;
}
template <typet> std::vector<T> fft_root;
template <typet> void dft(T* a, int n) {
  if (n == 1) return;
  auto& wn = fft_root<T>;
  reserve_fft_roots(wn, n);
  butterfly(a, n);
  for (int i = 1; i < n; i *= 2) {
    const T* w = wn.data() + i;
    for (T* b = a; b != a + n; b += i * 2) {
      dft2d(b, b + i);
      for (int j = 1; j < i; j++) {
        b[i + j] *= w[j];
        dft2d(b + j, b + i + j);
      }
    }
  }
}
template <u32 P> void idft(Fp<P>* a, int n) {
  std::reverse(a + 1, a + n);
  dft(a, n);
  Fp<P> x = P - (P - 1) / n;
  for (int i = 0; i < n; i++) a[i] *= x;
}
template <typet> void idft(std::complex<T>* a, int n) {
  std::reverse(a + 1, a + n);
  dft(a, n);
  T x = (T) 1 / n;
  for (int i = 0; i < n; i++) a[i] *= x;
}


template <typet> void cycle_conv_xxx(T* f, const T* g, int n) {
  dft(f, n);
  for (int i = 0; i < n; i++) f[i] *= g[i];
  idft(f, n);
}

template <typet> void cycle_conv(T* f, T* g, int n) {
  dft(g, n);
  cycle_conv_xxx(f, g, n);
}

template <typet> struct Poly;

template <u32 P> struct Poly<Fp<P>> : std::vector<Fp<P>> {
  using Z = Fp<P>;
  using Super = std::vector<Z>;
  using Super::Super;

  Poly(const Super& vec) : Super(vec) {}
  Poly(Super&& vec) : Super(std::forward<Super>(vec)) {}

  void fix() {
    while (!Super::empty() && Super::back() == 0) Super::pop_back();
  }

  bool brute_mul(const Poly& rhs) {
    int n = Super::size(), m = rhs.size();
    if (n == 0 || m == 0) {
      Super::resize(0);
      return true;
    }
    if (n + m > 50 && std::min(n, m) > 32 - __builtin_clz(n + m)) return false;
    Super lhs(n + m - 1);
    Super::swap(lhs);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++) (*this)[i + j] += lhs[i] * rhs[j];
    return true;
  }

  Poly& operator+=(const Poly& rhs) {
    Super::resize(std::max(Super::size(), rhs.size()));
    for (int i = 0; i < (int) rhs.size(); i++) (*this)[i] += rhs[i];
    return *this;
  }
  Poly& operator-=(const Poly& rhs) {
    Super::resize(std::max(Super::size(), rhs.size()));
    for (int i = 0; i < (int) rhs.size(); i++) (*this)[i] -= rhs[i];
    return *this;
  }
  Poly& operator*=(Poly rhs) {
    if (!brute_mul(rhs)) {
      int n = 1 << (32 - __builtin_clz(Super::size() + rhs.size() - 2));
      Super::resize(n);
      rhs.resize(n);
      cycle_conv(Super::data(), rhs.data(), n);
      fix();
    }
    return *this;
  }

  friend Poly operator+(Poly lhs, const Poly& rhs) { return lhs += rhs; }
  friend Poly operator-(Poly lhs, const Poly& rhs) { return lhs -= rhs; }
  friend Poly operator*(Poly lhs, Poly rhs) { return lhs *= std::move(rhs); }

  Poly derivative() const {
    if (Super::size() <= 1) return {0};
    Poly f(Super::size() - 1);
    for (int i = 1; i < (int) Super::size(); i++) f[i - 1] = (*this)[i] * i;
    return f;
  }

  Poly integral() const {
    if (Super::empty()) return {0};
    Poly f(Super::size() + 1);
    f[1] = 1;
    for (int i = 2; i <= (int) Super::size(); i++) f[i] = f[P % i] * (P - P / i);
    for (int i = 1; i <= (int) Super::size(); i++) f[i] *= (*this)[i - 1];
    return f;
  }

  template <typename Func> Poly apply(Func func, int n = -1) const {
    if (n == -1) n = Super::size();
    int m = n;
    if (m > 2) m = 1 << (32 - __builtin_clz(m - 1));
    Poly f(m), g(m);
    std::copy_n(Super::data(), std::min<int>(n, Super::size()), f.data());
    func(f.data(), g.data(), m);
    g.resize(n);
    return g;
  }

  
  
  static void inv_impl(const Z* f, Z* g, int n) {
    int m = std::min(n, 16);
    std::fill_n(g, m, 0);
    g[0] = ~f[0];
    for (int i = 1; i < m; i++) {
      for (int j = 0; j < i; j++) g[i] -= f[i - j] * g[j];
      g[i] *= g[0];
    }
    Z* a = new Z[n * 2];
    for (; m < n; m *= 2) {
      std::copy_n(f, m * 2, a);
      std::copy_n(g, m, a + n);
      std::fill_n(a + n + m, m, 0);
      cycle_conv(a, a + n, m * 2);
      std::fill_n(a, m, 0);
      cycle_conv_xxx(a, a + n, m * 2);
      for (int i = m; i < m * 2; i++) g[i] = -a[i];
    }
    delete[] a;
  }
  Poly inv(int n = -1) const { return apply(inv_impl, n); }

  
  
  
  static void log_impl(const Z* f, Z* g, int n) {
    if (n <= 32) {
      std::fill_n(g, n, 0);
      for (int i = 1; i < n; i++) {
        for (int j = 1; j < i; j++) g[i] += g[j] * f[i - j] * j;
        g[i] = f[i] - g[i] * Combination<Z>::inverse(i);
      }
      return;
    }
    Z* a = new Z[n * 4];
    for (int i = 1; i < n; i++) a[i - 1] = f[i] * i;
    a[n - 1] = 0;
    std::fill_n(a + n, n, 0);
    inv_impl(f, a + n * 2, n);
    std::fill_n(a + n * 3, n, 0);
    cycle_conv(a, a + n * 2, n * 2);
    g[0] = 0;
    for (int i = 1; i < n; i++) g[i] = a[i - 1] * Combination<Z>::inverse(i);
    delete[] a;
  }
  Poly log(int n = -1) const { return apply(log_impl, n); }

  
  
  
  static void exp_impl(const Z* f, Z* g, int n) {
    if (n <= 32) {
      std::fill_n(g, n, 0);
      g[0] = 1;
      for (int i = 1; i < n; i++) {
        for (int j = 1; j <= i; j++) g[i] += g[i - j] * f[j] * j;
        g[i] *= Combination<Z>::inverse(i);
      }
      return;
    }
    Z *h = new Z[n * 4 + n / 2], *gt = h + n / 2, *ht = gt + n, *p = ht + n, *q = p + n;
    g[0] = gt[0] = h[0] = ht[0] = 1;
    for (int m = 1; m < n; m *= 2) {
      std::copy_n(g, m, gt);
      std::fill_n(gt + m, m, 0);
      dft(gt, m * 2);
      for (int i = 0; i < m; i++) p[i] = gt[i * 2] * ht[i];
      idft(p, m);
      std::fill_n(p, (m + 1) / 2, 0);
      dft(p, m);
      for (int i = 0; i < m; i++) p[i] *= -ht[i];
      idft(p, m);
      std::copy_n(p + (m + 1) / 2, m / 2, h + (m + 1) / 2);
      std::copy_n(h, m, ht);
      std::fill_n(ht + m, m, 0);
      dft(ht, m * 2);
      for (int i = 1; i < m; i++) p[i - 1] = f[i] * i;
      p[m - 1] = 0;
      dft(p, m);
      for (int i = 0; i < m; i++) q[i] = gt[i * 2] * p[i];
      idft(q, m);
      p[0] = p[m] = -q[m - 1];
      for (int i = 1; i < m; i++) p[i] = g[i] * i - q[i - 1];
      std::fill_n(p + m, m, 0);
      dft(p, m * 2);
      for (int i = 0; i < m * 2; i++) q[i] = ht[i] * p[i];
      idft(q, m * 2);
      for (int i = 0; i < m; i++) p[i] = f[m + i] - q[i] * Combination<Z>::inverse(m + i);
      std::fill_n(p + m, m, 0);
      dft(p, m * 2);
      for (int i = 0; i < m * 2; i++) q[i] = gt[i] * p[i];
      idft(q, m * 2);
      std::copy_n(q, m, g + m);
    }
    delete[] h;
  }
  Poly exp(int n = -1) const { return apply(exp_impl, n); }

  
  
  Poly pow(i64 k, int n = -1) const {
    if (n == -1) n = Super::size();
    if (k == 0) {
      Poly f(n);
      f[0] = 1;
      return f;
    }
    int h = std::find_if(range(*this), [](Z x) -> bool { return x; }) - Super::begin();
    if (h == (int) Super::size() || h > (n - 1) / k) return Poly(n);
    int n2 = n - h * k, m = n2;
    if (m > 2) m = 1 << (32 - __builtin_clz(m - 1));
    Poly f(m), g(m);
    std::copy_n(Super::data() + h, std::min<int>(n2, Super::size() - h), f.data());
    Z x = f[0].pow(k), y = ~x, z = k;
    for (Z& a : f) a *= y;
    log_impl(f.data(), g.data(), m);
    for (Z& a : g) a *= z;
    exp_impl(g.data(), f.data(), m);
    g.assign(n, 0);
    for (int i = 0; i < n2; i++) g[h * k + i] = f[i] * x;
    return g;
  }

  
  
  
  static void sqrt_impl(const Z* f, Z* g, int n) {
    int m = std::min(n, 32);
    std::copy_n(f, m, g);
    for (int i = 1; i < m; i++) {
      for (int j = 1; j * 2 < i; j++) g[i] -= g[j] * g[i - j] * 2;
      if (~i & 1) g[i] -= g[i / 2] * g[i / 2];
      g[i] *= P / 2 + 1;
    }
    if (m == n) return;
    Z *a = new Z[n * 4], *b = a + n, *c = b + n, *h = c + n;
    inv_impl(g, h, m);
    std::copy_n(g, m, a);
    for (dft(a, m);; m *= 2) {
      for (int i = 0; i < m; i++) a[i] *= a[i];
      idft(a, m);
      for (int i = 0; i < m; i++) a[i] -= f[i] + f[m + i];
      std::fill_n(a + m, m, 0);
      std::copy_n(h, m, b);
      std::fill_n(b + m, m, 0);
      cycle_conv(a, b, m * 2);
      for (int i = 0; i < m; i++) g[m + i] = a[i] * (P / 2);
      if (m * 2 == n) break;
      std::copy_n(g, m * 2, a);
      dft(a, m * 2);
      std::copy_n(a, m * 2, c);
      for (int i = 0; i < m * 2; i++) c[i] *= b[i];
      idft(c, m * 2);
      std::fill_n(c, m, 0);
      cycle_conv_xxx(c, b, m * 2);
      for (int i = m; i < m * 2; i++) h[i] = -c[i];
    }
    delete[] a;
  }
  Poly sqrt(int n = -1) {  
    if (n == -1) n = Super::size();
    int h = std::find_if(range(*this), [](Z x) -> bool { return x; }) - Super::begin();
    if (h == (int) Super::size()) return Poly(n);
    if (h & 1) return {};
    if (h / 2 >= n) return Poly(n);
    int x = tonelli_shanks((*this)[h]);
    if (x == -1) return {};
    x = std::min<int>(x, P - x);
    int n2 = n - h / 2, m = n2;
    if (m > 2) m = 1 << (32 - __builtin_clz(m - 1));
    Poly f(m), g(m);
    std::copy_n(Super::data() + h, std::min<int>(n2, Super::size() - h), f.data());
    if (x != 1) {
      Z t = Z{x}.pow(-2);
      for (Z& a : f) a *= t;
    }
    sqrt_impl(f.data(), g.data(), m);
    f.assign(n, 0);
    for (int i = 0; i < n2; i++) f[h / 2 + i] = g[i] * x;
    return f;
  }
};

template <typet> Poly<T> refine(Poly<T> f) {
  f.fix();
  return f;
}

template <typet> std::pair<Poly<T>, Poly<T>> divmod(const Poly<T>& f, const Poly<T>& g) {
  int n = f.size(), m = g.size();
  if (n < m) return {{}, f};
  auto rf = f;
  auto rg = g;
  std::reverse(range(rf));
  std::reverse(range(rg));
  rf.resize(n - m + 1);
  rg.resize(n - m + 1);
  auto q = rf * rg.inv();
  q.resize(n - m + 1);
  std::reverse(range(q));
  q = refine(q);
  return {q, refine(f - q * g)};
}

template <typet> Poly<T> linear_rec(const Poly<T>& c, i64 n) {
  int d = c.size();
  Poly<T> f{1};
  auto fix = [&]() -> void {
    for (int i = f.size() - 1; i >= d; i--) {
      if (!f[i]) continue;
      for (int j = 0; j < d; j++) f[i + j - d] += f[i] * c[j];
      f[i] = 0;
    }
    f.fix();
  };
  for (int p = 62; p >= 0; p--) {
    f = f * f;
    fix();
    if (n >> p & 1) {
      f.insert(f.begin(), 0);
      fix();
    }
  }
  f.resize(d);
  return f;
}

template <typet> Poly<T> linear_rec_fast(const Poly<T>& c, i64 n) {
  int d = c.size();
  Poly<T> f{1}, g(d + 1);
  g[d] = 1;
  g -= c;
  for (int p = 62; p >= 0; p--) {
    f = divmod(f * f, g).ss;
    if (n >> p & 1) {
      f.insert(f.begin(), 0);
      for (int i = f.size() - 1; i >= d; i--) {
        if (!f[i]) continue;
        for (int j = 0; j < d; j++) f[i + j - d] += f[i] * c[j];
        f[i] = 0;
      }
      f.fix();
    }
  }
  f.resize(d);
  return f;
}

template <typet> std::vector<T> berlekamp_massey(const std::vector<T>& a) {
  int n = a.size();
  std::vector<T> b{-1}, c{-1};
  b.reserve(n + 1);
  c.reserve(n + 1);
  T y = 1;
  for (int e = 1; e <= n; e++) {
    int m = b.size(), l = c.size();
    T x = 0;
    for (int i = 0; i < l; i++) x += c[i] * a[e - l + i];
    b.push_back(0);
    m += 1;
    if (!x) continue;
    T z = x / y;
    if (l < m) {
      auto t = c;
      c.insert(c.begin(), m - l, 0);
      for (int i = 0; i < m; i++) c[m - 1 - i] -= z * b[m - 1 - i];
      b.swap(t);
      y = x;
    } else {
      for (int i = 0; i < m; i++) c[l - 1 - i] -= z * b[m - 1 - i];
    }
  }
  c.pop_back();
  return c;
}

template <typet> struct Lagrange {
  int n;
  std::vector<T> x, y, v;
  Lagrange(int deg, std::vector<T> x_, std::vector<T> y_) : n(deg), x(x_), y(y_), v(deg + 1, 1) {
    for (int i = 0; i <= n; i++) {
      for (int j = 0; j <= n; j++)
        if (i != j) v[i] *= x[i] - x[j];
      v[i] = y[i] / v[i];
    }
  }
  T at(T x0) const {
    std::vector<T> l(n + 1, 1), r(n + 1, 1);
    for (int i = 1; i <= n; i++) l[i] = l[i - 1] * (x0 - x[i - 1]);
    for (int i = n - 1; i >= 0; i--) r[i] = r[i + 1] * (x0 - x[i + 1]);
    T res = 0;
    for (int i = 0; i <= n; i++) res += l[i] * r[i] * v[i];
    return res;
  }
  std::vector<T> get_poly() const {
    std::vector<T> f(n + 1), g(n + 1, 1), h(n + 1, 1);
    for (int i = 0; i <= n; i++) {
      for (int j = i; j > 0; j--) g[j] = g[j - 1] - g[j] * x[i];
      g[0] *= -x[i];
    }
    for (int i = 0; i <= n; i++) {
      for (int j = n - 1; j >= 0; j--) h[j] = g[j + 1] + h[j + 1] * x[i];
      for (int j = 0; j <= n; j++) f[j] += h[j] * v[i];
    }
    return f;
  }
};

template <int maxc> struct PAM {
  std::vector<std::array<int, maxc>> ch;
  vi len, fa, s;
  int n = 0, las = 0;

  PAM(int pool) : ch(pool), len(pool), fa(pool), s(pool) { init(); }
  void init() {
    ch.resize(0);
    len.resize(0);
    fa.resize(0);
    new_node(0, 1);
    new_node(-1, 0);
    s[n = las = 0] = -1;
  }
  void new_node(int l, int f) {
    ch.push_back({});
    len.push_back(l);
    fa.push_back(f);
  }
  void flush() { n = las = 0; }

  int get_fail(int x) {
    while (s[n - len[x] - 1] != s[n]) x = fa[x];
    return x;
  }
  void add(int c) {
    s[++n] = c;
    int p = get_fail(las);
    if (!ch[p][c]) {
      new_node(len[p] + 2, ch[get_fail(fa[p])][c]);
      ch[p][c] = ch.size() - 1;
    }
    las = ch[p][c];
  }
};

template <int maxc> struct ACAM {
  std::vector<std::array<int, maxc>> ch;
  vi fa;
  int sz = 0;

  ACAM(int pool) : ch(pool), fa(pool) { init(); }
  void init() {
    ch.resize(1);
    fa.resize(1);
    sz = 1;
  }
  int new_node() {
    ch.push_back({});
    fa.push_back(0);
    return sz++;
  }

  void insert(const std::string& s) {
    int p = 0;
    for (char c : s) {
      if (!ch[p][c - 'a']) ch[p][c - 'a'] = new_node();
      p = ch[p][c - 'a'];
    }
  }

  vi build() {
    vi q(sz);
    int h = 1, t = 1;
    for (int i = 0; i < maxc; i++)
      if (ch[0][i]) q[t++] = ch[0][i];
    while (h < t) {
      int p = q[h++];
      for (int i = 0; i < maxc; i++) {
        if (ch[p][i]) {
          fa[ch[p][i]] = ch[fa[p]][i];
          q[t++] = ch[p][i];
        } else {
          ch[p][i] = ch[fa[p]][i];
        }
      }
    }
    return q;
  }
};

template <typet> std::basic_string<T> mincyc(std::basic_string<T> s) {
  s += s;
  int n = s.size(), p = 0;
  for (int i = 0, j, k; i < n / 2;) {
    p = i;
    for (j = i + 1, k = i; j < n && s[k] <= s[j]; j++) s[k] == s[j] ? k++ : k = i;
    while (i <= k) i += j - k;
  }
  return s.substr(p, n / 2);
}

template <typet> std::vector<std::basic_string<T>> duval(const std::basic_string<T>& s) {
  std::vector<std::basic_string<T>> lyndon;
  for (int i = 0, j, k, n = s.size(); i < n;) {
    for (j = i + 1, k = i; j < n && s[k] <= s[j]; j++) s[k] == s[j] ? k++ : k = i;
    for (; i <= k; i += j - k) lyndon.push_back(s.substr(i, j - k));
  }
  return lyndon;
}

template <typet> struct PairLCS {
  vvi ih, iv;
  int n = 0, m = 0;
  PairLCS(T s, T t) : n(s.size()), m(t.size()) {
    ih = iv = vvi(n + 1, vi(m + 1));
    std::iota(range(ih[0]), 0);
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        if (s[i - 1] == t[j - 1]) {
          ih[i][j] = iv[i][j - 1];
          iv[i][j] = ih[i - 1][j];
        } else {
          ih[i][j] = std::max(ih[i - 1][j], iv[i][j - 1]);
          iv[i][j] = std::min(ih[i - 1][j], iv[i][j - 1]);
        }
      }
    }
  }
  int query(int a, int b, int c) const {
    int res = 0;
    for (int i = b + 1; i <= c; i++) res += ih[a][i] <= b;
    return res;
  }  
};

template <typet> struct Fenwick {
  std::vector<T> a;
  int n = 0;
  Fenwick(int n_ = 0) : a(n_), n(n_) {}
  void add(int p, T x) {
    for (int i = p; i < n; i += lowbit(i)) a[i] += x;
  }
  T pre_sum(int p) {
    T res = 0;
    for (int i = p; i; i ^= lowbit(i)) res += a[i];
    return res;
  }  
  T query(int l, int r) {
    if (l > r) return 0;
    return pre_sum(r) - pre_sum(l - 1);
  }  
};

template <typet> struct FenwickSSR {
  std::vector<T> a, b;
  int n = 0;
  FenwickSSR(int n_ = 0) : a(n_), b(n_), n(n_) {}
  void add_suf(int p, T x) {
    T y = x * p;
    for (int i = p; i < n; i += lowbit(i)) a[i] += x, b[i] += y;
  }  
  T pre_sum(int p) {
    T res = 0;
    for (int i = p++; i; i ^= lowbit(i)) res += a[i] * p - b[i];
    return res;
  }  
  void add(int l, int r, T x) {
    if (l > r) return;
    add_suf(l, x);
    add_suf(r + 1, -x);
  }  
  T query(int l, int r) {
    if (l > r) return 0;
    return pre_sum(r) - pre_sum(l - 1);
  }  
};
vi unit_monge_mul(const vi& a, const vi& rb) {
  int n = a.size();
  if (n == 1) return a;
  int m = n / 2;
  auto split = [&](const vi& v) -> std::tuple<vi, vi, vi, vi> {
    vi L, LR, R, RR;
    for (int i = 0; i < n; i++) {
      if (v[i] < m) {
        L.push_back(v[i]);
        LR.push_back(i);

      } else {
        R.push_back(v[i] - m);
        RR.push_back(i);
      }
    }
    return {L, R, LR, RR};
  };
  auto [al, ar, ral, rar] = split(a);
  auto [bl, br, rbl, rbr] = split(rb);
  vi cl = unit_monge_mul(al, bl);
  vi cr = unit_monge_mul(ar, br);
  vi ret(n), iret(n), msk(n);
  for (int i = 0; i < m; i++) {
    ret[ral[i]] = rbl[cl[i]];
    msk[ral[i]] |= 1;
    msk[rbl[i]] |= 2;
  }
  for (int i = 0; i < n - m; i++) ret[rar[i]] = rbr[cr[i]];
  for (int i = 0; i < n; i++) iret[ret[i]] = i;
  auto right_delta = [&](int x, int y) -> int { return ((msk[y] & 2) == 2) ^ (iret[y] < x); };
  auto up_delta = [&](int x, int y) -> int { return ((msk[x] & 1) == 1) ^ (ret[x] < y); };
  for (int i = 0, j = n, sum = 0; i < n; i++) {
    int rd = j > 0 ? right_delta(i, j - 1) : 0;
    while (j > 0 && sum >= rd) {
      sum -= rd;
      j--;
      rd = j > 0 ? right_delta(i, j - 1) : 0;
    }
    int new_sum = sum + up_delta(i, j);
    if (j > 0 && sum == 0 && new_sum > 0) ret[i] = j - 1;
    sum = new_sum;
  }
  return ret;
}


void initialize() {
  std::cin.tie(0)->sync_with_stdio(0);
  std::cout << std::fixed << std::setprecision(10);
}


int cas;

void solution() {
  int n;
  std::cin >> n;
  vi a(n), b(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
    a[i]--;
  }
  for (int i = 0; i < n; i++) {
    std::cin >> b[i];
    b[i]--;
  }

  vi rb(n);
  for (int i = 0; i < n; i++) rb[b[i]] = i;
  vi c = unit_monge_mul(a, rb);
  for (int i = 0; i < n; i++) {
    std::cout << c[i] + 1 << " \n"[i == n - 1];
  }
}


int main() {
  initialize();

  int T = 1;
  
  for (cas = 1; cas <= T; cas++) solution();

  return 0;
}
