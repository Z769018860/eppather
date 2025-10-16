#ifndef LOCAL
#define NDEBUG
#endif
#include <algorithm>
#include <cassert>
#include <cstring>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <queue>
#include <random>
#include <vector>

template <std::uint64_t P> struct ModInt64 {
public:
  using i32 = std::int32_t;
  using u32 = std::uint32_t;
  using i64 = std::int64_t;
  using u64 = std::uint64_t;
  using m64 = ModInt64;

private:
  u64 v;

  static constexpr u64 get_r() {
    u64 iv = P * (2ULL - P * P);
    return iv *= 2ULL - P * iv, iv *= 2ULL - P * iv, iv *= 2ULL - P * iv, iv * (2ULL - P * iv);
  }
  static constexpr u64 get_r2() {
    u64 iv = -u64(P) % P;
    for (u32 i = 0; i != 64; ++i)
      if (P <= (iv <<= 1)) iv -= P;
    return iv;
  }
  static constexpr u64 r = get_r(), r2 = get_r2();
  static_assert((P & 1) == 1);
  static_assert(r * P == 1);
  static_assert(P < (1ULL << 63));
  static constexpr std::pair<u64, u64> mul(u64 x, u64 y) {
    u64 a = x >> 32, b = u32(x), c = y >> 32, d = u32(y), ac = a * c, bd = b * d, ad = a * d,
        bc = b * c;
    return {ac + (ad >> 32) + (bc >> 32) + ((ad & -1U) + (bc & -1U) + (bd >> 32) >> 32),
            bd + (ad + bc << 32)};
  }
  static constexpr u64 mulhi(u64 x, u64 y) {
    u64 a = x >> 32, b = u32(x), c = y >> 32, d = u32(y), ac = a * c, bd = b * d, ad = a * d,
        bc = b * c;
    return ac + (ad >> 32) + (bc >> 32) + ((ad & -1U) + (bc & -1U) + (bd >> 32) >> 32);
  }
  static constexpr u64 reduce(const std::pair<u64, u64> &x) {
    u64 res = x.first - mulhi(x.second * r, P);
    return res + (P & -(res >> 63));
  }
  static constexpr u64 pow_mod(u64 x, u64 y) {
    u64 res = reduce({0, r2});
    for (x = reduce(mul(x, r2)); y != 0; y >>= 1, x = reduce(mul(x, x)))
      if (y & 1) res = reduce(mul(res, x));
    return reduce({0, res});
  }

public:
  static constexpr u64 get_pr() {
    u64 tmp[128] = {}, cnt = 0;
    const u64 phi = P - 1;
    u64 m = phi;
    for (u64 i = 2; i * i <= m; ++i)
      if (m % i == 0) {
        tmp[cnt++] = i;
        while (m % i == 0) m /= i;
      }
    if (m != 1) tmp[cnt++] = m;
    for (u64 res = 2; res != P; ++res) {
      bool flag = true;
      for (u32 i = 0; i != cnt && flag; ++i) flag &= pow_mod(res, phi / tmp[i]) != 1;
      if (flag) return res;
    }
    return 0;
  }
  ModInt64() = default;
  ~ModInt64() = default;
  constexpr ModInt64(u64 v) : v(reduce(mul(v, r2))) {}
  constexpr ModInt64(const m64 &) = default;
  constexpr u64 get() const { return reduce({0, v}); }
  explicit constexpr operator u64() const { return get(); }
  explicit constexpr operator i64() const { return i64(get()); }
  constexpr m64 inv() const {
    i64 x1 = 1, x3 = 0, a = get(), b = P;
    while (b != 0) {
      i64 q = a / b, x1_old = x1, a_old = a;
      x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q;
    }
    return m64(x1 + P);
  }
  constexpr m64 &operator=(const m64 &) = default;
  constexpr m64 operator-() const {
    m64 res;
    return res.v = (P & -(v != 0)) - v, res;
  }
  constexpr m64 &operator*=(const m64 &rhs) { return v = reduce(mul(v, rhs.v)), *this; }
  constexpr m64 &operator+=(const m64 &rhs) { return v += rhs.v - P, v += P & -(v >> 63), *this; }
  constexpr m64 &operator-=(const m64 &rhs) { return v -= rhs.v, v += P & -(v >> 63), *this; }
  constexpr m64 &operator/=(const m64 &rhs) { return this->operator*=(rhs.inv()); }
  friend m64 operator+(const m64 &lhs, const m64 &rhs) { return m64(lhs) += rhs; }
  friend m64 operator-(const m64 &lhs, const m64 &rhs) { return m64(lhs) -= rhs; }
  friend m64 operator*(const m64 &lhs, const m64 &rhs) { return m64(lhs) *= rhs; }
  friend m64 operator/(const m64 &lhs, const m64 &rhs) { return m64(lhs) /= rhs; }
  friend bool operator==(const m64 &lhs, const m64 &rhs) { return lhs.v == rhs.v; }
  friend bool operator!=(const m64 &lhs, const m64 &rhs) { return lhs.v != rhs.v; }
  friend std::istream &operator>>(std::istream &is, m64 &rhs) {
    return is >> rhs.v, rhs.v = reduce(mul(rhs.v, r2)), is;
  }
  friend std::ostream &operator<<(std::ostream &os, const m64 &rhs) { return os << rhs.get(); }
  constexpr m64 pow(i64 y) const {
    m64 res(1), x(*this);
    for (; y != 0; y >>= 1, x *= x)
      if (y & 1) res *= x;
    return res;
  }
};

namespace BinomialConvolution {


std::uint64_t get_len(std::uint64_t n) { 
  return --n, n |= n >> 1, n |= n >> 2, n |= n >> 4, n |= n >> 8, n |= n >> 16, n |= n >> 32, ++n;
}

template <typename T, typename S = std::make_signed_t<T>>
std::enable_if_t<std::is_integral_v<T>, std::tuple<T, S, S>> exgcd(T a, T b) {
  S a_p = a, b_p = b, x1 = 1, x2 = 0, x3 = 0, x4 = 1;
  while (b_p != 0) {
    S q = a_p / b_p;
    std::tie(x1, x2, x3, x4, a_p, b_p) =
        std::make_tuple(x3, x4, x1 - x3 * q, x2 - x4 * q, b_p, a_p - b_p * q);
  }
  return std::make_tuple(static_cast<T>(a_p), x1, x2);
}

template <typename T> std::enable_if_t<std::is_integral_v<T>, T> inv_mod(T x, T mod) {
  using S = std::make_signed_t<T>;
  S a = x, b = mod, x1 = 1, x3 = 0;
  while (b != 0) {
    S q = a / b;
    std::tie(x1, x3, a, b) = std::make_tuple(x3, x1 - x3 * q, b, a - b * q);
  }
  assert(a == 1 && "inv_mod_error");
  return static_cast<T>(x1 < 0 ? x1 + mod : x1);
}

template <std::uint64_t P> std::pair<const ModInt64<P> *, const ModInt64<P> *> init(int n) {
  static int lim = 0;
  static constexpr ModInt64<P> G(ModInt64<P>::get_pr());
  static ModInt64<P> ROOT[1 << 20], IROOT[1 << 20];
  if (lim == 0) {
    ROOT[0] = IROOT[0] = 1;
    ROOT[1 << 19] = G.pow(P - 1 >> 21), IROOT[1 << 19] = G.pow(P - 1 - (P - 1 >> 21));
    for (int i = 18; i != -1; --i)
      ROOT[1 << i] = ROOT[1 << i + 1] * ROOT[1 << i + 1],
                IROOT[1 << i] = IROOT[1 << i + 1] * IROOT[1 << i + 1];
    lim = 1;
  }
  while ((lim << 1) < n) {
    for (int i = lim + 1, e = lim << 1; i < e; ++i)
      ROOT[i] = ROOT[i - lim] * ROOT[lim], IROOT[i] = IROOT[i - lim] * IROOT[lim];
    lim <<= 1;
  }
  return {ROOT, IROOT};
}

template <std::uint64_t P> void dft(int n, ModInt64<P> x[], const ModInt64<P> *ROOT) {
  for (int j = 0, l = n >> 1; j != l; ++j) {
    ModInt64<P> u = x[j], v = x[j + l];
    x[j] = u + v, x[j + l] = u - v;
  }
  for (int i = n >> 1; i >= 2; i >>= 1) {
    for (int j = 0, l = i >> 1; j != l; ++j) {
      ModInt64<P> u = x[j], v = x[j + l];
      x[j] = u + v, x[j + l] = u - v;
    }
    for (int j = i, l = i >> 1, m = 1; j != n; j += i, ++m) {
      ModInt64<P> root = ROOT[m];
      for (int k = 0; k != l; ++k) {
        ModInt64<P> u = x[j + k], v = x[j + k + l] * root;
        x[j + k] = u + v, x[j + k + l] = u - v;
      }
    }
  }
}

template <std::uint64_t P> void idft(int n, ModInt64<P> x[], const ModInt64<P> *ROOT) {
  for (int i = 2; i < n; i <<= 1) {
    for (int j = 0, l = i >> 1; j != l; ++j) {
      ModInt64<P> u = x[j], v = x[j + l];
      x[j] = u + v, x[j + l] = u - v;
    }
    for (int j = i, l = i >> 1, m = 1; j != n; j += i, ++m) {
      ModInt64<P> root = ROOT[m];
      for (int k = 0; k != l; ++k) {
        ModInt64<P> u = x[j + k], v = x[j + k + l];
        x[j + k] = u + v, x[j + k + l] = (u - v) * root;
      }
    }
  }
  ModInt64<P> iv(P - (P - 1) / n);
  for (int j = 0, l = n >> 1; j != l; ++j) {
    ModInt64<P> u = x[j] * iv, v = x[j + l] * iv;
    x[j] = u + v, x[j + l] = u - v;
  }
}

template <std::uint64_t P> void dft(int n, ModInt64<P> x[]) { dft(n, x, init<P>(n).first); }

template <std::uint64_t P> void idft(int n, ModInt64<P> x[]) { idft(n, x, init<P>(n).second); }

std::vector<std::uint32_t>
binomial_convolution_modulo_prime_power(const std::vector<std::uint32_t> &a,
                                        const std::vector<std::uint32_t> &b, std::uint32_t p,
                                        std::uint32_t pq) {
  
  using u32 = std::uint32_t;
  using u64 = std::uint64_t;
  static constexpr u64 P1 = 0x3f9a000000000001;
  static constexpr u64 P2 = 0x3fc6000000000001;
  using mod1 = ModInt64<P1>;
  using mod2 = ModInt64<P2>;
  static mod1 x1[1 << 21], y1[1 << 21], p_pow1[1 << 21], ip_pow1[1 << 21];
  static mod2 x2[1 << 21], y2[1 << 21], p_pow2[1 << 21], ip_pow2[1 << 21];
  static u32 fac[1 << 21], ifac[1 << 21], v[1 << 21];
  const int n = a.size(), m = b.size(), len = n + m - 1;
  int radix_p[32];
  const mod1 p1 = p, ip1 = p1.inv();
  const mod2 p2 = p, ip2 = p2.inv();
  { 
    static u32 p_pow[1 << 21];
    p_pow1[0] = ip_pow1[0] = 1;
    p_pow2[0] = ip_pow2[0] = 1;
    int sum = v[0] = 0;
    p_pow[0] = fac[0] = ifac[0] = 1;
    std::fill(radix_p, radix_p + 32, 0);
    { 
      int v_max = 0;
      for (int i = len / p; i; i /= p) v_max += i;
      for (int i = 1; i <= v_max; ++i) {
        p_pow[i] = p_pow[i - 1] * p; 
        p_pow1[i] = p_pow1[i - 1] * p1;
        p_pow2[i] = p_pow2[i - 1] * p2;
        ip_pow1[i] = ip_pow1[i - 1] * ip1;
        ip_pow2[i] = ip_pow2[i - 1] * ip2;
      }
    }
    for (int i = 1; i < len; ++i) {
      { 
        for (int j = 0; ++sum, ++radix_p[j] == p; ++j, sum -= p) radix_p[j] = 0;
        v[i] = (i - sum) / (p - 1);
      }
      int d = v[i] - v[i - 1];
      fac[i] = u64(fac[i - 1]) * (i / p_pow[d]) % pq;
      ifac[i] = u64(fac[i]) * ifac[i - 1] % pq;
    }
    {
      u32 ivpq = inv_mod(ifac[len - 1], pq);
      for (int i = len - 1; i > 0; --i)
        ifac[i] = u64(ivpq) * ifac[i - 1] % pq, ivpq = u64(ivpq) * fac[i] % pq;
    }
  }
  std::vector<u32> res(len);
  std::function<u32(mod1, mod2)> crt2modpq = [pq](mod1 x, mod2 y) {
    static mod1 ip2(mod1(P2).inv());
    static u64 P2modpq = P2 % pq;
    return u32((u64((x - u64(y)) * ip2) % pq * P2modpq + u64(y)) % pq);
  };
  for (int i = 0; i != n; ++i) {
    u64 a_hat = u64(a[i]) * ifac[i] % pq;
    x1[i] = a_hat * ip_pow1[v[i]];
    x2[i] = a_hat * ip_pow2[v[i]];
  }
  for (int i = 0; i != m; ++i) {
    u64 b_hat = u64(b[i]) * ifac[i] % pq;
    y1[i] = b_hat * ip_pow1[v[i]];
    y2[i] = b_hat * ip_pow2[v[i]];
  }
  int con_len = get_len(len);
  std::fill(x1 + n, x1 + con_len, mod1(0));
  std::fill(y1 + m, y1 + con_len, mod1(0));
  std::fill(x2 + n, x2 + con_len, mod2(0));
  std::fill(y2 + m, y2 + con_len, mod2(0));
  dft(con_len, x1), dft(con_len, y1), dft(con_len, x2), dft(con_len, y2);
  for (int i = 0; i != con_len; ++i) x1[i] *= y1[i], x2[i] *= y2[i];
  idft(con_len, x1), idft(con_len, x2);
  for (int i = 0; i != len; ++i)
    res[i] = u64(crt2modpq(x1[i] * p_pow1[v[i]], x2[i] * p_pow2[v[i]])) * fac[i] % pq;
  return res;
}

std::vector<std::uint32_t>
binomial_convolution_modulo_composite(const std::vector<std::uint32_t> &a,
                                      const std::vector<std::uint32_t> &b, std::uint32_t p) {
  int len = a.size() + b.size() - 1;
  std::uint32_t m = 1;
  std::vector<std::uint32_t> res(len, 0);
  std::function<void(std::uint32_t, std::vector<std::uint32_t> &, std::uint32_t,
                     const std::vector<std::uint32_t> &)>
      crt = [](std::uint32_t m, std::vector<std::uint32_t> &x, std::uint32_t m2,
               const std::vector<std::uint32_t> &y) {
        int len = x.size();
        std::uint32_t im1 = inv_mod(m, m2);
        for (int i = 0; i != len; ++i)
          x[i] += std::uint64_t((y[i] + m2 - x[i] % m2) % m2) * im1 % m2 * m;
      };
  for (int i = 2; i * i <= p; ++i) {
    if (p % i == 0) {
      int p_old = p;
      while (p % i == 0) p /= i;
      std::uint32_t m2 = p_old / p;
      crt(m, res, m2, binomial_convolution_modulo_prime_power(a, b, i, m2));
      m *= m2;
    }
  }
  if (p != 1) crt(m, res, p, binomial_convolution_modulo_prime_power(a, b, p, p));
  return res;
}

} 

using namespace BinomialConvolution;

int main() {
#ifdef LOCAL
  std::freopen("..\\in", "r", stdin), std::freopen("..\\out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int n, m, p;
  std::cin >> n >> m >> p;
  std::vector<std::uint32_t> a(n + 1), b(m + 1);
  for (auto &i : a) std::cin >> i;
  for (auto &i : b) std::cin >> i;
  auto res = binomial_convolution_modulo_composite(a, b, p);
  for (auto i : res) std::cout << i << ' ';
  return 0;
}