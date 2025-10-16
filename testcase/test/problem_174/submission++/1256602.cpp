#line 1 "local_test\\test.cpp"
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

#line 1 "math\\formal_power_series\\egf.hpp"




#include <cstdint>

#line 1 "modint\\long_Montgomery_modint.hpp"




#line 11 "modint\\long_Montgomery_modint.hpp"
#include <tuple>
#include <type_traits>

namespace lib {

template <std::uint64_t mod>
class LongMontgomeryModInt {
public:
  using u32 = std::uint32_t;
  using i64 = std::int64_t;
  using u64 = std::uint64_t;
  using m64 = LongMontgomeryModInt;

  using value_type = u64;

  static constexpr u64 get_mod() { return mod; }

  static constexpr u64 get_primitive_root_prime() {
    u64 tmp[64]   = {};
    int cnt       = 0;
    const u64 phi = mod - 1;
    u64 m         = phi;
    for (u64 i = 2; i * i <= m; ++i) {
      if (m % i == 0) {
        tmp[cnt++] = i;
        do { m /= i; } while (m % i == 0);
      }
    }
    if (m != 1) tmp[cnt++] = m;
    for (m64 res = 2;; res += 1) {
      bool f = true;
      for (int i = 0; i < cnt && f; ++i) f &= res.pow(phi / tmp[i]) != 1;
      if (f) return u32(res);
    }
  }

  constexpr LongMontgomeryModInt() = default;
  ~LongMontgomeryModInt()          = default;

  template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
  constexpr LongMontgomeryModInt(T v) : v_(reduce(mul(norm(v % i64(mod)), r2))) {}

  constexpr LongMontgomeryModInt(const m64 &) = default;

  constexpr u64 get() const { return reduce({0, v_}); }

  template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
  explicit constexpr operator T() const {
    return T(get());
  }

  constexpr m64 operator-() const {
    m64 res;
    res.v_ = (mod & -(v_ != 0)) - v_;
    return res;
  }

  constexpr m64 inv() const {
    i64 x1 = 1, x3 = 0, a = get(), b = mod;
    while (b != 0) {
      i64 q = a / b, x1_old = x1, a_old = a;
      x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q;
    }
    return m64(x1);
  }

  constexpr m64 &operator=(const m64 &) = default;

  constexpr m64 &operator+=(const m64 &rhs) {
    v_ += rhs.v_ - mod;
    v_ += mod & -(v_ >> 63);
    return *this;
  }
  constexpr m64 &operator-=(const m64 &rhs) {
    v_ -= rhs.v_;
    v_ += mod & -(v_ >> 63);
    return *this;
  }
  constexpr m64 &operator*=(const m64 &rhs) {
    v_ = reduce(mul(v_, rhs.v_));
    return *this;
  }
  constexpr m64 &operator/=(const m64 &rhs) { return operator*=(rhs.inv()); }
  friend constexpr m64 operator+(const m64 &lhs, const m64 &rhs) { return m64(lhs) += rhs; }
  friend constexpr m64 operator-(const m64 &lhs, const m64 &rhs) { return m64(lhs) -= rhs; }
  friend constexpr m64 operator*(const m64 &lhs, const m64 &rhs) { return m64(lhs) *= rhs; }
  friend constexpr m64 operator/(const m64 &lhs, const m64 &rhs) { return m64(lhs) /= rhs; }
  friend constexpr bool operator==(const m64 &lhs, const m64 &rhs) { return lhs.v_ == rhs.v_; }
  friend constexpr bool operator!=(const m64 &lhs, const m64 &rhs) { return lhs.v_ != rhs.v_; }

  friend std::istream &operator>>(std::istream &is, m64 &rhs) {
    i64 x;
    is >> x;
    rhs = m64(x);
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const m64 &rhs) { return os << rhs.get(); }

  constexpr m64 pow(u64 y) const {
    m64 res(1), x(*this);
    for (; y != 0; y >>= 1, x *= x)
      if (y & 1) res *= x;
    return res;
  }

private:
  static constexpr std::pair<u64, u64> mul(u64 x, u64 y) {
#ifdef __GNUC__
    unsigned __int128 res = (unsigned __int128)x * y;
    return {u64(res >> 64), u64(res)};
#else
    u64 a = x >> 32, b = u32(x), c = y >> 32, d = u32(y), ad = a * d, bc = b * c;
    return {a * c + (ad >> 32) + (bc >> 32) +
                (((ad & ~UINT32_C(0)) + (bc & ~UINT32_C(0)) + (b * d >> 32)) >> 32),
            x * y};
#endif
  }

  static constexpr u64 mulh(u64 x, u64 y) {
#ifdef __GNUC__
    return u64((unsigned __int128)x * y >> 64);
#else
    u64 a = x >> 32, b = u32(x), c = y >> 32, d = u32(y), ad = a * d, bc = b * c;
    return a * c + (ad >> 32) + (bc >> 32) +
           (((ad & ~UINT32_C(0)) + (bc & ~UINT32_C(0)) + (b * d >> 32)) >> 32);
#endif
  }

  static constexpr u64 get_r() {
    u64 two = 2, iv = mod * (two - mod * mod);
    iv *= two - mod * iv;
    iv *= two - mod * iv;
    iv *= two - mod * iv;
    return iv * (two - mod * iv);
  }

  static constexpr u64 get_r2() {
    u64 iv = -u64(mod) % mod;
    for (int i = 0; i != 64; ++i)
      if ((iv <<= 1) >= mod) iv -= mod;
    return iv;
  }

  static constexpr u64 reduce(const std::pair<u64, u64> &x) {
    u64 res = x.first - mulh(x.second * r, mod);
    return res + (mod & -(res >> 63));
  }

  static constexpr u64 norm(i64 x) { return x + (mod & -(x < 0)); }

  u64 v_;

  static constexpr u64 r  = get_r();
  static constexpr u64 r2 = get_r2();

  static_assert((mod & 1) == 1, "mod % 2 == 0\n");
  static_assert(r * mod == 1, "???\n");
  static_assert((mod & (1ULL << 63)) == 0, "mod >= (1ULL << 63)\n");
  static_assert(mod != 1, "mod == 1\n");
};

template <std::uint64_t mod>
using LongMontModInt = LongMontgomeryModInt<mod>;

} 


#line 1 "math\\basic\\exgcd.hpp"




#line 12 "math\\basic\\exgcd.hpp"

#line 1 "traits\\base.hpp"




#line 11 "traits\\base.hpp"

namespace lib {

template <typename Type>
struct promote_integral;
template <>
struct promote_integral<std::int32_t> {
  using type = std::int64_t;
};
template <>
struct promote_integral<std::uint32_t> {
  using type = std::uint64_t;
};


template <typename Type>
using promote_integral_t = typename promote_integral<Type>::type;

template <typename T, typename U>
using longer_integral_t =
    std::conditional_t<(sizeof(T) > sizeof(U) || (sizeof(T) == sizeof(U) && std::is_signed_v<T>)),
                       T, U>;

} 


#line 14 "math\\basic\\exgcd.hpp"

namespace lib::internal {

template <typename T>
std::enable_if_t<std::is_integral_v<T>, T> gcd(T a, T b) {
  while (b != 0) std::tie(a, b) = std::make_tuple(b, a % b);
  return a;
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

template <typename T>
std::enable_if_t<std::is_integral_v<T>, T> inv_mod(T x, T mod) {
  using S = std::make_signed_t<T>;
  S a = x < mod ? x : x % mod, b = mod, x1 = 1, x3 = 0;
  while (b != 0) {
    S q                    = a / b;
    std::tie(x1, x3, a, b) = std::make_tuple(x3, x1 - x3 * q, b, a - b * q);
  }
  assert(a == 1 && "inv_mod_error");
  return static_cast<T>(x1 < 0 ? x1 + mod : x1);
}

} 

namespace lib {

template <typename T1, typename T2, typename T = longer_integral_t<T1, T2>>
std::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>, T> gcd(T1 a, T2 b) {
  return internal::gcd<T>(a, b);
}

template <typename T1, typename T2, typename T = longer_integral_t<T1, T2>,
          typename S = std::make_signed_t<T>>
std::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>, std::tuple<T, S, S>>
exgcd(T1 a, T2 b) {
  return internal::exgcd<T, S>(a, b);
}

template <typename T1, typename T2, typename T = longer_integral_t<T1, T2>>
std::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>, T> inv_mod(T1 x, T2 mod) {
  return internal::inv_mod<T>(x, mod);
}

} 


#line 1 "math\\formal_power_series\\radix_2_NTT.hpp"




#line 13 "math\\formal_power_series\\radix_2_NTT.hpp"

#line 1 "traits\\modint.hpp"




namespace lib {

template <typename mod_t>
struct modint_traits {
  using type = typename mod_t::value_type;
  static constexpr type get_mod() { return mod_t::get_mod(); }
  static constexpr type get_primitive_root_prime() { return mod_t::get_primitive_root_prime(); }
};

} 


#line 15 "math\\formal_power_series\\radix_2_NTT.hpp"

namespace lib {

template <typename mod_t>
class NTT {
public:
  NTT() = delete;

  static int deBruijn_log2(std::uint64_t n) {
    static constexpr std::uint64_t deBruijn = 0x022fdd63cc95386d;
    static constexpr int convert[64]        = {
        0,  1,  2,  53, 3,  7,  54, 27, 4,  38, 41, 8,  34, 55, 48, 28, 62, 5,  39, 46, 44, 42,
        22, 9,  24, 35, 59, 56, 49, 18, 29, 11, 63, 52, 6,  26, 37, 40, 33, 47, 61, 45, 43, 21,
        23, 58, 17, 10, 51, 25, 36, 32, 60, 20, 57, 16, 50, 31, 19, 15, 30, 14, 13, 12};
    return convert[n * deBruijn >> 58];
  }

    static int bsf(std::uint64_t n) { return deBruijn_log2(n & ~(n - 1)); }

  static void set_root() {
    if (!dw_.empty()) return;
    static constexpr mod_t g(modint_traits<mod_t>::get_primitive_root_prime());
    auto mod = modint_traits<mod_t>::get_mod();
    int lv   = bsf(mod - 1);
    rt_.resize(lv - 1), irt_.resize(lv - 1), dw_.resize(lv - 1), idw_.resize(lv - 1);
    rt_.back() = g.pow(mod >> lv);
    for (int i = lv - 3; i >= 0; --i) rt_[i] = rt_[i + 1] * rt_[i + 1];
    mod_t v(1);
    irt_.back() = v / rt_.back();
    for (int i = lv - 3; i >= 0; --i) irt_[i] = irt_[i + 1] * irt_[i + 1];
    for (int i = 0; i < lv - 1; ++i) dw_[i] = v * rt_[i], v *= irt_[i];
    v = mod_t(1);
    for (int i = 0; i < lv - 1; ++i) idw_[i] = v * irt_[i], v *= rt_[i];
  }

  static void dft(int n, mod_t *x) {
    set_root();
    for (int j = 0, l = n >> 1; j != l; ++j) {
      mod_t u = x[j], v = x[j + l];
      x[j] = u + v, x[j + l] = u - v;
    }
    for (int i = n >> 1; i >= 2; i >>= 1) {
      for (int j = 0, l = i >> 1; j != l; ++j) {
        mod_t u = x[j], v = x[j + l];
        x[j] = u + v, x[j + l] = u - v;
      }
      mod_t root(dw_[0]);
      for (int j = i, l = i >> 1, m = 1; j != n; j += i) {
        for (int k = j; k != j + l; ++k) {
          mod_t u = x[k], v = x[k + l] * root;
          x[k] = u + v, x[k + l] = u - v;
        }
        root *= dw_[bsf(++m)];
      }
    }
  }

  static void idft(int n, mod_t *x) {
    set_root();
    for (int i = 2; i < n; i <<= 1) {
      for (int j = 0, l = i >> 1; j != l; ++j) {
        mod_t u = x[j], v = x[j + l];
        x[j] = u + v, x[j + l] = u - v;
      }
      mod_t root(idw_[0]);
      for (int j = i, l = i >> 1, m = 1; j != n; j += i) {
        for (int k = j; k != j + l; ++k) {
          mod_t u = x[k], v = x[k + l];
          x[k] = u + v, x[k + l] = (u - v) * root;
        }
        root *= idw_[bsf(++m)];
      }
    }
    const mod_t iv(mod_t(n).inv());
    for (int j = 0, l = n >> 1; j != l; ++j) {
      mod_t u = x[j] * iv, v = x[j + l] * iv;
      x[j] = u + v, x[j + l] = u - v;
    }
  }

  static void even_dft(int n, mod_t *x) {
    static constexpr mod_t IT(mod_t(2).inv());
    for (int i = 0, j = 0; i != n; i += 2, ++j) x[j] = IT * (x[i] + x[i + 1]);
  }

  static void odd_dft(int n, mod_t *x) {
    static constexpr mod_t IT(mod_t(2).inv());
    mod_t root(1);
    for (int i = 0, j = 0; i != n; i += 2, ++j)
      x[j] = IT * root * (x[i] - x[i + 1]), root *= idw_[bsf(~static_cast<std::uint64_t>(j))];
  }

  static void dft_doubling(int n, mod_t *x) {
    static constexpr mod_t g(modint_traits<mod_t>::get_primitive_root_prime());
    std::copy_n(x, n, x + n);
    idft(n, x + n);
    mod_t k(1), t(g.pow((modint_traits<mod_t>::get_mod() - 1) / (n << 1)));
    for (int i = 0; i != n; ++i) x[n + i] *= k, k *= t;
    dft(n, x + n);
  }

private:
  static inline std::vector<mod_t> rt_, irt_, dw_, idw_;
};

std::uint32_t get_ntt_len(std::uint32_t n) {
  --n;
  n |= n >> 1;
  n |= n >> 2;
  n |= n >> 4;
  n |= n >> 8;
  return (n | n >> 16) + 1;
}

template <typename mod_t>
void dft(int n, mod_t *x) {
  NTT<mod_t>::dft(n, x);
}

template <typename mod_t>
void idft(int n, mod_t *x) {
  NTT<mod_t>::idft(n, x);
}

template <typename mod_t>
void dft(std::vector<mod_t> &x) {
  NTT<mod_t>::dft(x.size(), x.data());
}

template <typename mod_t>
void idft(std::vector<mod_t> &x) {
  NTT<mod_t>::idft(x.size(), x.data());
}

} 


#line 14 "math\\formal_power_series\\egf.hpp"

namespace lib {

class ExponentialGeneratingFunction {
public:
  using i32 = std::int32_t;
  using u32 = std::uint32_t;
  using i64 = std::int64_t;
  using u64 = std::uint64_t;

  using value_type = u32;

  using mod1 = LongMontModInt<0x3f9a000000000001>;
  using mod2 = LongMontModInt<0x3fc6000000000001>;

  ExponentialGeneratingFunction(u32 mod) : current_mod_(mod) {
    for (u32 i = 2; i * i <= mod; ++i)
      if (mod % i == 0) {
        int e       = 0;
        u32 mod_old = mod;
        do { mod /= i, ++e; } while (mod % i == 0);
        fact_.emplace_back(i, e, mod_old / mod);
      }
    if (mod != 1) fact_.emplace_back(mod, 1, mod);
  }

  struct FactorInfo {
    u32 p, e, pe; 
    std::vector<mod1> p_pow1, ip_pow1;
    std::vector<mod2> p_pow2, ip_pow2;
    std::vector<u32> v, fac, ifac; 
    FactorInfo(u32 p, u32 e, u32 pe)
        : p(p), e(e), pe(pe), p_pow1{mod1(1), mod1(p)}, ip_pow1{mod1(1), mod1(p).inv()},
          p_pow2{mod2(1), mod2(p)}, ip_pow2{mod2(1), mod2(p).inv()}, v{0}, fac{1}, ifac{1} {}
    ~FactorInfo() = default;
    void preprocess(int n) {
      {
        int old_size = v.size();
        if (old_size < n) {
          v.resize(n);
          fac.resize(n);
          ifac.resize(n);
        }
        for (int i = old_size; i < n; ++i) {
          v[i]  = v[i - 1];
          int j = i;
          for (; j % p == 0; j /= p) ++v[i];
          fac[i]  = static_cast<u64>(fac[i - 1]) * j % pe;
          ifac[i] = inv_mod(fac[i], pe);
        }
      }
      {
        int old_size = p_pow1.size();
        if (old_size < n) {
          p_pow1.resize(n);
          ip_pow1.resize(n);
          p_pow2.resize(n);
          ip_pow2.resize(n);
        }
        for (int i = old_size; i < n; ++i) {
          p_pow1[i]  = p_pow1[i - 1] * p_pow1[1];
          ip_pow1[i] = ip_pow1[i - 1] * ip_pow1[1];
          p_pow2[i]  = p_pow2[i - 1] * p_pow2[1];
          ip_pow2[i] = ip_pow2[i - 1] * ip_pow2[1];
        }
      }
    }
  };

  template <typename Type>
  std::vector<Type> &shrink(std::vector<Type> &x) {
    Type ZERO(0);
    while (x.back() == ZERO) x.pop_back();
    if (x.empty()) x.emplace_back(ZERO);
    return x;
  }

  template <typename Type>
  std::vector<Type> binom_convolve(const std::vector<Type> &x, const std::vector<Type> &y) {
    int n = x.size(), m = y.size();
    std::vector<u32> x_cpy(n), y_cpy(m);
    for (int i = 0; i < n; ++i) x_cpy[i] = static_cast<u32>(x[i]);
    for (int i = 0; i < m; ++i) y_cpy[i] = static_cast<u32>(y[i]);
    int res_len = n + m - 1;
    u32 mod     = 1;
    std::vector<u32> res(res_len, 0);
    auto crt = [res_len](std::vector<u32> &x, u32 m, const std::vector<u32> &y, u32 m2) {
      u32 im1 = inv_mod(m, m2);
      for (int i = 0; i != res_len; ++i)
        x[i] += static_cast<u64>((y[i] + m2 - x[i] % m2) % m2) * im1 % m2 * m;
    };
    for (int i = 0, e = fact_.size(); i < e; ++i) {
      crt(res, mod, convolve(x_cpy, y_cpy, i), fact_[i].pe);
      mod *= fact_[i].pe;
    }
    return std::vector<Type>(res.begin(), res.end());
  }

private:
  std::vector<FactorInfo> fact_;
  const u32 current_mod_;

  std::vector<u32> convolve(const std::vector<u32> &x, const std::vector<u32> &y, int idx) {
    int n = x.size(), m = y.size(), res_len = n + m - 1, len = get_ntt_len(res_len);
    fact_[idx].preprocess(res_len + 1);
    const auto &fact = fact_[idx];
    const auto pe    = fact.pe;
    std::vector<mod1> x1(len), y1(len);
    std::vector<mod2> x2(len), y2(len);
    for (int i = 0; i < n; ++i) {
      u64 x_hat = static_cast<u64>(x[i]) * fact.ifac[i] % pe;
      x1[i]     = x_hat * fact.ip_pow1[fact.v[i]];
      x2[i]     = x_hat * fact.ip_pow2[fact.v[i]];
    }
    for (int i = 0; i < m; ++i) {
      u64 y_hat = static_cast<u64>(y[i]) * fact.ifac[i] % pe;
      y1[i]     = y_hat * fact.ip_pow1[fact.v[i]];
      y2[i]     = y_hat * fact.ip_pow2[fact.v[i]];
    }
    std::fill(x1.begin() + n, x1.end(), mod1(0)), std::fill(y1.begin() + m, y1.end(), mod1(0)),
        std::fill(x2.begin() + n, x2.end(), mod2(0)), std::fill(y2.begin() + m, y2.end(), mod2(0));
    dft(x1), dft(y1), dft(x2), dft(y2);
    for (int i = 0; i != len; ++i) x1[i] *= y1[i], x2[i] *= y2[i];
    idft(x1), idft(x2);
    auto crt_mod_pe = [pe](mod1 x, mod2 y) -> u64 {
      static mod1 ip2(mod1(mod2::get_mod()).inv());
      static u64 p2_mod_pe = mod2::get_mod() % pe;
      u64 uy               = static_cast<u64>(y);
      return (static_cast<u64>((x - uy) * ip2) % pe * p2_mod_pe + uy) % pe;
    };
    std::vector<u32> res(res_len);
    for (int i = 0; i != res_len; ++i)
      res[i] = crt_mod_pe(x1[i] * fact.p_pow1[fact.v[i]], x2[i] * fact.p_pow2[fact.v[i]]) *
               fact.fac[i] % pe;
    return res;
  }
};

using EGF = ExponentialGeneratingFunction;

} 


#line 13 "local_test\\test.cpp"

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int n, m, mod;
  std::cin >> n >> m >> mod;
  lib::EGF egf(mod);
  std::vector<int> A(n + 1), B(m + 1);
  for (auto &i : A) std::cin >> i;
  for (auto &i : B) std::cin >> i;
  auto res = egf.binom_convolve(A, B);
  for (auto i : res) std::cout << i << ' ';
  return 0;
}
