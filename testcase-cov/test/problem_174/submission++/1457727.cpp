#line 1 "math\\binomial_convolution.hpp"



#line 1 "common.hpp"



#define LIB_DEBUG

#define LIB_BEGIN namespace lib {
#define LIB_END }
#define LIB ::lib::


#line 1 "modint\\long_montgomery_modint.hpp"



#line 5 "modint\\long_montgomery_modint.hpp"

#ifdef LIB_DEBUG
  #include <stdexcept>
#endif
#include <cstdint>
#include <iostream>
#include <type_traits>

LIB_BEGIN

template <std::uint64_t ModT>
class montgomery_modint63 {
  using u32 = std::uint32_t;
  using i64 = std::int64_t;
  using u64 = std::uint64_t;

  u64 v_{};

  static constexpr u64 get_r() {
    u64 t = 2, iv = MOD * (t - MOD * MOD);
    iv *= t - MOD * iv, iv *= t - MOD * iv, iv *= t - MOD * iv;
    return iv * (t - MOD * iv);
  }
  static constexpr u64 get_r2() {
    u64 iv = -MOD % MOD;
    for (int i = 0; i != 64; ++i)
      if ((iv <<= 1) >= MOD) iv -= MOD;
    return iv;
  }
  static constexpr u64 mul_high(u64 x, u64 y) {
    u64 a = x >> 32, b = static_cast<u32>(x), c = y >> 32, d = static_cast<u32>(y), ad = a * d,
        bc = b * c;
    return a * c + (ad >> 32) + (bc >> 32) +
           (((ad & 0xFFFFFFFF) + (bc & 0xFFFFFFFF) + (b * d >> 32)) >> 32);
  }
  static constexpr u64 redc_mul(u64 x, u64 y) {
    u64 res = mul_high(x, y) - mul_high(x * y * R, MOD);
    return res + (MOD & -(res >> 63));
  }
  static constexpr u64 norm(i64 x) { return x + (MOD & -(x < 0)); }

  static constexpr u64 MOD  = ModT;
  static constexpr u64 R    = get_r();
  static constexpr u64 R2   = get_r2();
  static constexpr i64 SMOD = static_cast<i64>(MOD);

  static_assert(MOD & 1);
  static_assert(R * MOD == 1);
  static_assert((MOD >> 63) == 0);
  static_assert(MOD != 1);

public:
  static constexpr u64 mod() { return MOD; }
  static constexpr i64 smod() { return SMOD; }
  constexpr montgomery_modint63() {}
  template <typename IntT, std::enable_if_t<std::is_integral_v<IntT>, int> = 0>
  constexpr montgomery_modint63(IntT v) : v_(redc_mul(norm(v % SMOD), R2)) {}
  constexpr u64 val() const {
    u64 res = -mul_high(v_ * R, MOD);
    return res + (MOD & -(res >> 63));
  }
  constexpr i64 sval() const { return val(); }
  constexpr bool is_zero() const { return v_ == 0; }
  template <typename IntT, std::enable_if_t<std::is_integral_v<IntT>, int> = 0>
  explicit constexpr operator IntT() const {
    return static_cast<IntT>(val());
  }
  constexpr montgomery_modint63 operator-() const {
    montgomery_modint63 res;
    res.v_ = (MOD & -(v_ != 0)) - v_;
    return res;
  }
  constexpr montgomery_modint63 inv() const {
    i64 x1 = 1, x3 = 0, a = sval(), b = SMOD;
    while (b != 0) {
      i64 q = a / b, x1_old = x1, a_old = a;
      x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q;
    }
#ifdef LIB_DEBUG
    if (a != 1) throw std::runtime_error("modular inverse error");
#endif
    return montgomery_modint63(x1);
  }
  constexpr montgomery_modint63 &operator+=(const montgomery_modint63 &rhs) {
    v_ += rhs.v_ - MOD, v_ += MOD & -(v_ >> 63);
    return *this;
  }
  constexpr montgomery_modint63 &operator-=(const montgomery_modint63 &rhs) {
    v_ -= rhs.v_, v_ += MOD & -(v_ >> 63);
    return *this;
  }
  constexpr montgomery_modint63 &operator*=(const montgomery_modint63 &rhs) {
    v_ = redc_mul(v_, rhs.v_);
    return *this;
  }
  constexpr montgomery_modint63 &operator/=(const montgomery_modint63 &rhs) {
    return operator*=(rhs.inv());
  }
  constexpr montgomery_modint63 pow(u64 e) const {
    for (montgomery_modint63 res(1), x(*this);; x *= x) {
      if (e & 1) res *= x;
      if ((e >>= 1) == 0) return res;
    }
  }
  constexpr void swap(montgomery_modint63 &rhs) {
    auto v = v_;
    v_ = rhs.v_, rhs.v_ = v;
  }
  friend constexpr montgomery_modint63 operator+(const montgomery_modint63 &lhs,
                                                 const montgomery_modint63 &rhs) {
    return montgomery_modint63(lhs) += rhs;
  }
  friend constexpr montgomery_modint63 operator-(const montgomery_modint63 &lhs,
                                                 const montgomery_modint63 &rhs) {
    return montgomery_modint63(lhs) -= rhs;
  }
  friend constexpr montgomery_modint63 operator*(const montgomery_modint63 &lhs,
                                                 const montgomery_modint63 &rhs) {
    return montgomery_modint63(lhs) *= rhs;
  }
  friend constexpr montgomery_modint63 operator/(const montgomery_modint63 &lhs,
                                                 const montgomery_modint63 &rhs) {
    return montgomery_modint63(lhs) /= rhs;
  }
  friend constexpr bool operator==(const montgomery_modint63 &lhs, const montgomery_modint63 &rhs) {
    return lhs.v_ == rhs.v_;
  }
  friend constexpr bool operator!=(const montgomery_modint63 &lhs, const montgomery_modint63 &rhs) {
    return lhs.v_ != rhs.v_;
  }
  friend std::istream &operator>>(std::istream &is, montgomery_modint63 &rhs) {
    i64 x;
    is >> x;
    rhs = montgomery_modint63(x);
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const montgomery_modint63 &rhs) {
    return os << rhs.val();
  }
};

template <std::uint64_t ModT>
using mm63 = montgomery_modint63<ModT>;

LIB_END


#line 1 "math\\convolution.hpp"



#line 1 "math\\truncated_fourier_transform.hpp"



#line 1 "math\\radix2_ntt.hpp"



#line 5 "math\\radix2_ntt.hpp"

#include <algorithm>
#include <array>
#include <cassert>
#line 10 "math\\radix2_ntt.hpp"
#include <vector>

LIB_BEGIN

namespace detail {

template <typename IntT>
constexpr std::enable_if_t<std::is_integral_v<IntT>, int> bsf(IntT v) {
  if (static_cast<std::make_signed_t<IntT>>(v) <= 0) return -1;
  int res = 0;
  for (; (v & 1) == 0; ++res) v >>= 1;
  return res;
}

template <typename ModIntT>
constexpr ModIntT quadratic_nonresidue_prime() {
  auto mod = ModIntT::mod();
  for (int i = 2;; ++i)
    if (ModIntT(i).pow(mod >> 1) == mod - 1) return ModIntT(i);
}

template <typename ModIntT>
constexpr ModIntT gen_of_sylow_2_subgroup() {
  auto mod = ModIntT::mod();
  return quadratic_nonresidue_prime<ModIntT>().pow(mod >> bsf(mod - 1));
}

template <typename ModIntT>
constexpr std::array<ModIntT, bsf(ModIntT::mod() - 1) - 1> root() {
  std::array<ModIntT, bsf(ModIntT::mod() - 1) - 1> rt; 
  rt.back() = gen_of_sylow_2_subgroup<ModIntT>();
  for (int i = bsf(ModIntT::mod() - 1) - 3; i >= 0; --i) rt[i] = rt[i + 1] * rt[i + 1];
  return rt;
}

template <typename ModIntT>
constexpr std::array<ModIntT, bsf(ModIntT::mod() - 1) - 1> iroot() {
  std::array<ModIntT, bsf(ModIntT::mod() - 1) - 1> irt;
  irt.back() = gen_of_sylow_2_subgroup<ModIntT>().inv();
  for (int i = bsf(ModIntT::mod() - 1) - 3; i >= 0; --i) irt[i] = irt[i + 1] * irt[i + 1];
  return irt;
}

} 



int ntt_len(int n) {
  --n;
  n |= n >> 1, n |= n >> 2, n |= n >> 4, n |= n >> 8;
  return (n | n >> 16) + 1;
}



template <typename IterT>
void dft_n(IterT a, int n) {
  assert((n & (n - 1)) == 0);
  using T                  = typename std::iterator_traits<IterT>::value_type;
  static constexpr auto rt = detail::root<T>();
  static std::vector<T> root(1);
  if (int s = static_cast<int>(root.size()); s << 1 < n) {
    root.resize(n >> 1);
    for (int i = detail::bsf(s), j; 1 << i < n >> 1; ++i) {
      root[j = 1 << i] = rt[i];
      for (int k = j + 1; k < j << 1; ++k) root[k] = root[k - j] * root[j];
    }
  }
  for (int j = 0, l = n >> 1; j != l; ++j) {
    T u(a[j]), v(a[j + l]);
    a[j] = u + v, a[j + l] = u - v;
  }
  for (int i = n >> 1; i >= 2; i >>= 1) {
    for (int j = 0, l = i >> 1; j != l; ++j) {
      T u(a[j]), v(a[j + l]);
      a[j] = u + v, a[j + l] = u - v;
    }
    for (int j = i, l = i >> 1, m = 1; j != n; j += i, ++m)
      for (int k = j; k != j + l; ++k) {
        T u(a[k]), v(a[k + l] * root[m]);
        a[k] = u + v, a[k + l] = u - v;
      }
  }
}



template <typename IterT>
void idft_n(IterT a, int n) {
  assert((n & (n - 1)) == 0);
  using T                  = typename std::iterator_traits<IterT>::value_type;
  static constexpr auto rt = detail::iroot<T>();
  static std::vector<T> root(1);
  if (int s = static_cast<int>(root.size()); s << 1 < n) {
    root.resize(n >> 1);
    for (int i = detail::bsf(s), j; 1 << i < n >> 1; ++i) {
      root[j = 1 << i] = rt[i];
      for (int k = j + 1; k < j << 1; ++k) root[k] = root[k - j] * root[j];
    }
  }
  for (int i = 2; i < n; i <<= 1) {
    for (int j = 0, l = i >> 1; j != l; ++j) {
      T u(a[j]), v(a[j + l]);
      a[j] = u + v, a[j + l] = u - v;
    }
    for (int j = i, l = i >> 1, m = 1; j != n; j += i, ++m)
      for (int k = j; k != j + l; ++k) {
        T u(a[k]), v(a[k + l]);
        a[k] = u + v, a[k + l] = (u - v) * root[m];
      }
  }
  const T iv(T::mod() - T::mod() / n);
  for (int j = 0, l = n >> 1; j != l; ++j) {
    T u(a[j] * iv), v(a[j + l] * iv);
    a[j] = u + v, a[j + l] = u - v;
  }
}


template <typename ContainerT> void dft(ContainerT &&a) { dft_n(a.begin(), a.size()); }
template <typename ContainerT> void idft(ContainerT &&a) { idft_n(a.begin(), a.size()); }
template <typename IterT> void dft(IterT beg, IterT end) { dft_n(beg, end - beg); }
template <typename IterT> void idft(IterT beg, IterT end) { idft_n(beg, end - beg); }


template <typename ModIntT>
void dft_doubling(const std::vector<ModIntT> &a, std::vector<ModIntT> &dft_a) {
  static constexpr auto rt = detail::root<ModIntT>();
  int as = static_cast<int>(a.size()), n = static_cast<int>(dft_a.size());
  
  
  dft_a.resize(n << 1);
  auto it = dft_a.begin() + n;
  for (int i = 0, is_even = 0, j; i != as; ++i) {
    if ((j = i & (n - 1)) == 0) is_even ^= 1;
    it[j] += is_even ? a[i] : -a[i];
  }
  ModIntT r(n == 1 ? ModIntT(-1) : rt[detail::bsf(n) - 1]), v(1);
  for (int i = 0; i != n; ++i) it[i] *= v, v *= r;
  dft_n(it, n);
}

template <typename ModIntT>
void dft_doubling(std::vector<ModIntT> &dft_a) {
  static constexpr auto rt = detail::root<ModIntT>();
  int n                    = static_cast<int>(dft_a.size());
  dft_a.resize(n << 1);
  auto it = dft_a.begin() + n;
  std::copy_n(dft_a.cbegin(), n, it);
  idft_n(it, n);
  ModIntT r(n == 1 ? ModIntT(-1) : rt[detail::bsf(n) - 1]), v(1);
  for (int i = 0; i != n; ++i) it[i] *= v, v *= r;
  dft_n(it, n);
}

LIB_END


#line 6 "math\\truncated_fourier_transform.hpp"

#line 8 "math\\truncated_fourier_transform.hpp"
#include <utility>
#line 10 "math\\truncated_fourier_transform.hpp"

LIB_BEGIN

template <typename ContainerT>
void tft(ContainerT &&a) {
  using Container          = std::remove_cv_t<std::remove_reference_t<ContainerT>>;
  using T                  = typename Container::value_type;
  static constexpr auto rt = detail::root<T>();
  static std::vector<T> root(1);
  const int n = static_cast<int>(a.size());
  if ((n & (n - 1)) == 0) return dft(std::forward<ContainerT>(a));
  const int len = ntt_len(n);
  if (int s = static_cast<int>(root.size()); s << 1 < len) {
    root.resize(len >> 1);
    for (int i = detail::bsf(s), j; 1 << i < len >> 1; ++i) {
      root[j = 1 << i] = rt[i];
      for (int k = j + 1; k < j << 1; ++k) root[k] = root[k - j] * root[j];
    }
  }
  a.resize(len);
  for (int j = 0, l = len >> 1; j != l; ++j) {
    T u(a[j]), v(a[j + l]);
    a[j] = u + v, a[j + l] = u - v;
  }
  for (int i = len >> 1; i >= 2; i >>= 1) {
    for (int j = 0, l = i >> 1; j != l; ++j) {
      T u(a[j]), v(a[j + l]);
      a[j] = u + v, a[j + l] = u - v;
    }
    for (int j = i, l = i >> 1, m = 1; j < n && j != len; j += i, ++m)
      for (int k = j; k != j + l; ++k) {
        T u(a[k]), v(a[k + l] * root[m]);
        a[k] = u + v, a[k + l] = u - v;
      }
  }
  a.resize(n);
}

template <typename ContainerT>
void itft(ContainerT &&a) {
  using Container           = std::remove_cv_t<std::remove_reference_t<ContainerT>>;
  using T                   = typename Container::value_type;
  static constexpr auto rt  = detail::root<T>();
  static constexpr auto irt = detail::iroot<T>();
  static std::vector<T> root{T(1)}, iroot{T(1)};
  const int n = static_cast<int>(a.size());
  if ((n & (n - 1)) == 0) return idft(std::forward<ContainerT>(a));
  const int len = ntt_len(n);
  if (int s = static_cast<int>(root.size()); s << 1 < len) {
    root.resize(len >> 1);
    iroot.resize(len >> 1);
    for (int i = detail::bsf(s), j; 1 << i < len >> 1; ++i) {
      root[j = 1 << i] = rt[i], iroot[j] = irt[i];
      for (int k = j + 1; k < j << 1; ++k)
        root[k] = root[k - j] * root[j], iroot[k] = iroot[k - j] * iroot[j];
    }
  }
  a.resize(len);
  struct itft_rec {
    itft_rec(Container &a) : a_(a), i2_(T(2).inv()) {}
    
    void run(int head, int tail, int last) {
      if (head >= tail) return;
      if (int mid = (last - head) / 2 + head, len = mid - head; mid <= tail) {
        
        T i2p(1);
        for (int i = 1; i != len; i <<= 1, i2p *= i2_)
          for (int j = head, m = head / (i << 1); j != mid; j += i << 1, ++m)
            for (int k = j; k != j + i; ++k) {
              T u(a_[k]), v(a_[k + i]);
              a_[k] = u + v, a_[k + i] = (u - v) * iroot[m];
            }
        for (int i = head; i != mid; ++i) a_[i] *= i2p;
        
        T r(root[head / (len << 1)] * 2);
        for (int i = tail; i != last; ++i) a_[i] = a_[i - len] - a_[i] * r;
        run(mid, tail, last);
        
        r = iroot[head / (len << 1)] * i2_;
        for (int i = head; i != mid; ++i) {
          T u(a_[i]), v(a_[i + len]);
          a_[i] = (u + v) * i2_, a_[i + len] = (u - v) * r;
        }
      } else {
        T r(root[head / (len << 1)]);
        
        for (int i = tail; i != mid; ++i) a_[i] += a_[i + len] * r;
        run(head, tail, mid);
        
        for (int i = head; i != mid; ++i) a_[i] -= a_[i + len] * r;
      }
    }
    Container &a_;
    const T i2_;
  } rec(a);
  rec.run(0, n, len);
  a.resize(n);
}

LIB_END


#line 6 "math\\convolution.hpp"

#line 8 "math\\convolution.hpp"
#include <memory>
#line 10 "math\\convolution.hpp"

LIB_BEGIN

template <typename ModIntT>
std::vector<ModIntT> convolution(const std::vector<ModIntT> &lhs, const std::vector<ModIntT> &rhs) {
  int n = static_cast<int>(lhs.size()), m = static_cast<int>(rhs.size());
  if (n == 0 || m == 0) return {};
  if (std::min(n, m) <= 32) {
    std::vector<ModIntT> res(n + m - 1);
    for (int i = 0; i != n; ++i)
      for (int j = 0; j != m; ++j) res[i + j] += lhs[i] * rhs[j];
    return res;
  }
  int len = n + m - 1;
  std::vector<ModIntT> lhs_cpy(len);
  std::copy_n(lhs.cbegin(), n, lhs_cpy.begin());
  tft(lhs_cpy);
  if (std::addressof(lhs) != std::addressof(rhs)) {
    std::vector<ModIntT> rhs_cpy(len);
    std::copy_n(rhs.cbegin(), m, rhs_cpy.begin());
    tft(rhs_cpy);
    for (int i = 0; i != len; ++i) lhs_cpy[i] *= rhs_cpy[i];
  } else {
    for (int i = 0; i != len; ++i) lhs_cpy[i] *= lhs_cpy[i];
  }
  itft(lhs_cpy);
  return lhs_cpy;
}

LIB_END


#line 1 "math\\extended_gcd.hpp"



#line 5 "math\\extended_gcd.hpp"

#include <tuple>
#line 9 "math\\extended_gcd.hpp"

LIB_BEGIN



[[deprecated]] std::tuple<long long, long long, long long> ext_gcd(long long a, long long b) {
  long long x11 = 1, x12 = 0, x21 = 0, x22 = 1;
  while (b != 0) {
    long long q = a / b, x11_cpy = x11, x12_cpy = x12, a_cpy = a;
    x11 = x21, x21 = x11_cpy - q * x21;
    x12 = x22, x22 = x12_cpy - q * x22;
    a = b, b = a_cpy - q * b;
  }
  return std::make_tuple(x11, x12, a);
}



std::pair<long long, long long> inv_gcd(long long a, long long b) {
  long long x11 = 1, x21 = 0;
  while (b != 0) {
    long long q = a / b, x11_cpy = x11, a_cpy = a;
    x11 = x21, x21 = x11_cpy - q * x21;
    a = b, b = a_cpy - q * b;
  }
  return std::make_pair(x11, a);
}

namespace detail {

template <typename ModIntT>
class modular_inverse {
  std::vector<ModIntT> ivs{ModIntT()};

  enum : int { LIM = 1 << 20 };

public:
  modular_inverse() {}
  ModIntT operator()(int k) {
    
    if (k > LIM) return ModIntT(k).inv();
    
    if (int n = static_cast<int>(ivs.size()); n <= k) {
      int nn = n;
      while (nn <= k) nn <<= 1;
      ivs.resize(nn);
      ModIntT v(1);
      for (int i = n; i != nn; ++i) ivs[i] = v, v *= ModIntT(i);
      v = v.inv();
      for (int i = nn - 1; i >= n; --i) ivs[i] *= v, v *= ModIntT(i);
    }
    return ivs[k];
  }
};

} 

LIB_END


#line 8 "math\\binomial_convolution.hpp"

#line 11 "math\\binomial_convolution.hpp"

LIB_BEGIN


class binomial_convolution {
  using i32 = std::int32_t;
  using u32 = std::uint32_t;
  using i64 = std::int64_t;
  using u64 = std::uint64_t;

  using mint0 = mm63<0x3F9A000000000001>;
  using mint1 = mm63<0x3FC6000000000001>;

  struct factor_info {
    const u32 p_, e_, pe_; 
    mutable std::vector<mint0> pp0_, ipp0_;
    mutable std::vector<mint1> pp1_, ipp1_;
    mutable std::vector<u32> nu_{0}, fact_{1}, ifact_{1}; 
    factor_info(u32 p, u32 e, u32 pe)
        : p_(p), e_(e), pe_(pe), pp0_{mint0(1), mint0(p)}, ipp0_{mint0(1), mint0(p).inv()},
          pp1_{mint1(1), mint1(p)}, ipp1_{mint1(1), mint1(p).inv()} {}
    void preprocess(int n) const {
      int os = static_cast<int>(nu_.size());
      if (os >= n) return;
      nu_.resize(n);
      fact_.resize(n);
      ifact_.resize(n);
      for (int i = os; i != n; ++i) {
        auto j = static_cast<u32>(i);
        auto v = nu_[i - 1];
        for (; j % p_ == 0; j /= p_) ++v;
        nu_[i]    = v;
        fact_[i]  = static_cast<u64>(fact_[i - 1]) * j % pe_;
        ifact_[i] = static_cast<u64>(fact_[i]) * ifact_[i - 1] % pe_;
      }
      {
        auto iv = [](u32 a, u32 b) -> u64 {
          auto v = inv_gcd(a, b).first ;
          return v < 0 ? v + b : v;
        }(ifact_.back(), pe_);
        for (int i = n - 1; i >= os; --i)
          ifact_[i] = ifact_[i - 1] * iv % pe_, iv = iv * fact_[i] % pe_;
      }
      if (int maxnu = static_cast<int>(nu_.back()), pos = static_cast<int>(pp0_.size());
          pos <= maxnu) {
        pp0_.resize(maxnu + 1);
        ipp0_.resize(maxnu + 1);
        pp1_.resize(maxnu + 1);
        ipp1_.resize(maxnu + 1);
        mint0 p0(pp0_[1]), ip0(ipp0_[1]);
        mint1 p1(pp1_[1]), ip1(ipp1_[1]);
        for (int i = pos; i <= maxnu; ++i) {
          pp0_[i]  = pp0_[i - 1] * p0;
          ipp0_[i] = ipp0_[i - 1] * ip0;
          pp1_[i]  = pp1_[i - 1] * p1;
          ipp1_[i] = ipp1_[i - 1] * ip1;
        }
      }
    }
  };

  std::vector<u32> convolution(const std::vector<u32> &a, const std::vector<u32> &b,
                               const factor_info &info) const;

  const u32 modular_;
  std::vector<factor_info> info_;

public:
  explicit binomial_convolution(u32 modular) : modular_(modular) {
    for (u32 i = 2; i * i <= modular; ++i)
      if (modular % i == 0) {
        int e        = 0;
        const u32 mm = modular;
        do { modular /= i, ++e; } while (modular % i == 0);
        info_.emplace_back(i, e, mm / modular);
      }
    if (modular != 1) info_.emplace_back(modular, 1, modular);
  }
  u32 mod() const { return modular_; }
  template <typename IntT>
  std::enable_if_t<std::is_integral_v<IntT>, std::vector<IntT>>
  operator()(const std::vector<IntT> &a, const std::vector<IntT> &b) const;
};

std::vector<typename binomial_convolution::u32>
binomial_convolution::convolution(const std::vector<u32> &a, const std::vector<u32> &b,
                                  const factor_info &info) const {
  const int n = static_cast<int>(a.size()), m = static_cast<int>(b.size()), len = n + m - 1;
  info.preprocess(len);
  std::vector<mint0> a0(len), b0(len);
  std::vector<mint1> a1(len), b1(len);
  const auto pe = info.pe_;
  for (int i = 0; i != n; ++i) {
    u64 a_hat = static_cast<u64>(a[i]) * info.ifact_[i] % pe;
    auto j    = info.nu_[i];
    a0[i] = a_hat * info.ipp0_[j], a1[i] = a_hat * info.ipp1_[j];
  }
  for (int i = 0; i != m; ++i) {
    u64 b_hat = static_cast<u64>(b[i]) * info.ifact_[i] % pe;
    auto j    = info.nu_[i];
    b0[i] = b_hat * info.ipp0_[j], b1[i] = b_hat * info.ipp1_[j];
  }
  tft(a0), tft(b0), tft(a1), tft(b1);
  for (int i = 0; i != len; ++i) a0[i] *= b0[i], a1[i] *= b1[i];
  itft(a0), itft(a1);
  
  auto cra = [pe, ip1 = mint0(mint1::mod()).inv(), p1_mod_pe = mint1::mod() % pe](mint0 a,
                                                                                  mint1 b) -> u64 {
    auto bv = b.val();
    return (static_cast<u64>((a - bv) * ip1) % pe * p1_mod_pe + bv) % pe;
  };
  std::vector<u32> res(len);
  for (int i = 0; i != len; ++i) {
    int j  = info.nu_[i];
    res[i] = cra(a0[i] * info.pp0_[j], a1[i] * info.pp1_[j]) * info.fact_[i] % pe;
  }
  return res;
}

template <typename IntT>
std::enable_if_t<std::is_integral_v<IntT>, std::vector<IntT>>
binomial_convolution::operator()(const std::vector<IntT> &a, const std::vector<IntT> &b) const {
  const int n = static_cast<int>(a.size()), m = static_cast<int>(b.size()), len = n + m - 1;
  std::vector<u32> a_cpy(n), b_cpy(m);
  for (int i = 0; i != n; ++i) a_cpy[i] = static_cast<u32>(a[i]);
  for (int i = 0; i != m; ++i) b_cpy[i] = static_cast<u32>(b[i]);
  u32 modular = 1;
  std::vector<u32> res(len);
  {
    auto cra = [len](std::vector<u32> &a, u32 &m, const std::vector<u32> &b, u32 m0) {
      auto im_mod_m0 = [](u32 a, u32 b) -> i64 {
        auto v = inv_gcd(a, b).first ;
        return v < 0 ? v + b : v;
      }(m, m0);
      for (int i = 0; i != len; ++i) {
        auto v = static_cast<i32>((static_cast<i64>(b[i]) - a[i]) * im_mod_m0 % m0);
        a[i] += (v < 0 ? v + m0 : v) * m;
      }
      m *= m0;
    };
    for (auto &&i : info_) cra(res, modular, convolution(a_cpy, b_cpy, i), i.pe_);
  }
  return std::vector<IntT>(res.cbegin(), res.cend());
}

using bin_conv = binomial_convolution;

LIB_END


#line 1 "modint\\montgomery_modint.hpp"



#line 5 "modint\\montgomery_modint.hpp"

#ifdef LIB_DEBUG
  #include <stdexcept>
#endif
#line 12 "modint\\montgomery_modint.hpp"

LIB_BEGIN

template <std::uint32_t ModT>
class montgomery_modint30 {
  using i32 = std::int32_t;
  using u32 = std::uint32_t;
  using u64 = std::uint64_t;

  u32 v_{};

  static constexpr u32 get_r() {
    u32 t = 2, iv = MOD * (t - MOD * MOD);
    iv *= t - MOD * iv, iv *= t - MOD * iv;
    return iv * (MOD * iv - t);
  }
  static constexpr u32 redc(u64 x) {
    return (x + static_cast<u64>(static_cast<u32>(x) * R) * MOD) >> 32;
  }
  static constexpr u32 norm(u32 x) { return x - (MOD & -((MOD - 1 - x) >> 31)); }

  static constexpr u32 MOD  = ModT;
  static constexpr u32 MOD2 = MOD << 1;
  static constexpr u32 R    = get_r();
  static constexpr u32 R2   = -static_cast<u64>(MOD) % MOD;
  static constexpr i32 SMOD = static_cast<i32>(MOD);

  static_assert(MOD & 1);
  static_assert(-R * MOD == 1);
  static_assert((MOD >> 30) == 0);
  static_assert(MOD != 1);

public:
  static constexpr u32 mod() { return MOD; }
  static constexpr i32 smod() { return SMOD; }
  constexpr montgomery_modint30() {}
  template <typename IntT, std::enable_if_t<std::is_integral_v<IntT>, int> = 0>
  constexpr montgomery_modint30(IntT v) : v_(redc(static_cast<u64>(v % SMOD + SMOD) * R2)) {}
  constexpr u32 val() const { return norm(redc(v_)); }
  constexpr i32 sval() const { return norm(redc(v_)); }
  constexpr bool is_zero() const { return v_ == 0 || v_ == MOD; }
  template <typename IntT, std::enable_if_t<std::is_integral_v<IntT>, int> = 0>
  explicit constexpr operator IntT() const {
    return static_cast<IntT>(val());
  }
  constexpr montgomery_modint30 operator-() const {
    montgomery_modint30 res;
    res.v_ = (MOD2 & -(v_ != 0)) - v_;
    return res;
  }
  constexpr montgomery_modint30 inv() const {
    i32 x1 = 1, x3 = 0, a = sval(), b = SMOD;
    while (b != 0) {
      i32 q = a / b, x1_old = x1, a_old = a;
      x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q;
    }
#ifdef LIB_DEBUG
    if (a != 1) throw std::runtime_error("modular inverse error");
#endif
    return montgomery_modint30(x1);
  }
  constexpr montgomery_modint30 &operator+=(const montgomery_modint30 &rhs) {
    v_ += rhs.v_ - MOD2, v_ += MOD2 & -(v_ >> 31);
    return *this;
  }
  constexpr montgomery_modint30 &operator-=(const montgomery_modint30 &rhs) {
    v_ -= rhs.v_, v_ += MOD2 & -(v_ >> 31);
    return *this;
  }
  constexpr montgomery_modint30 &operator*=(const montgomery_modint30 &rhs) {
    v_ = redc(static_cast<u64>(v_) * rhs.v_);
    return *this;
  }
  constexpr montgomery_modint30 &operator/=(const montgomery_modint30 &rhs) {
    return operator*=(rhs.inv());
  }
  constexpr montgomery_modint30 pow(u64 e) const {
    for (montgomery_modint30 res(1), x(*this);; x *= x) {
      if (e & 1) res *= x;
      if ((e >>= 1) == 0) return res;
    }
  }
  constexpr void swap(montgomery_modint30 &rhs) {
    auto v = v_;
    v_ = rhs.v_, rhs.v_ = v;
  }
  friend constexpr montgomery_modint30 operator+(const montgomery_modint30 &lhs,
                                                 const montgomery_modint30 &rhs) {
    return montgomery_modint30(lhs) += rhs;
  }
  friend constexpr montgomery_modint30 operator-(const montgomery_modint30 &lhs,
                                                 const montgomery_modint30 &rhs) {
    return montgomery_modint30(lhs) -= rhs;
  }
  friend constexpr montgomery_modint30 operator*(const montgomery_modint30 &lhs,
                                                 const montgomery_modint30 &rhs) {
    return montgomery_modint30(lhs) *= rhs;
  }
  friend constexpr montgomery_modint30 operator/(const montgomery_modint30 &lhs,
                                                 const montgomery_modint30 &rhs) {
    return montgomery_modint30(lhs) /= rhs;
  }
  friend constexpr bool operator==(const montgomery_modint30 &lhs, const montgomery_modint30 &rhs) {
    return norm(lhs.v_) == norm(rhs.v_);
  }
  friend constexpr bool operator!=(const montgomery_modint30 &lhs, const montgomery_modint30 &rhs) {
    return norm(lhs.v_) != norm(rhs.v_);
  }
  friend std::istream &operator>>(std::istream &is, montgomery_modint30 &rhs) {
    i32 x;
    is >> x;
    rhs = montgomery_modint30(x);
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const montgomery_modint30 &rhs) {
    return os << rhs.val();
  }
};

template <std::uint32_t ModT>
using mm30 = montgomery_modint30<ModT>;

LIB_END


#line 3 "temp\\a.cpp"

#line 6 "temp\\a.cpp"

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n, m, M;
  std::cin >> n >> m >> M;
  ++n, ++m;
  lib::bin_conv bc(M);
  std::vector<int> a(n), b(m);
  for (auto &&i : a) std::cin >> i;
  for (auto &&i : b) std::cin >> i;
  for (auto i : bc(a, b)) std::cout << i << ' ';
  return 0;
}
