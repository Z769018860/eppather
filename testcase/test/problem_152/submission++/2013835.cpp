#include <bit>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <type_traits>
#include <vector>

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



template <typename ModIntT>
void zeta_transform(std::vector<ModIntT> &x) {
  const int n = static_cast<int>(x.size());
  assert((n & (n - 1)) == 0);
  
  for (int i = 1; i < n; i <<= 1)
    for (int j = 0; j != n; ++j)
      if (j & i) x[j] += x[j ^ i];
}



template <typename ModIntT>
void moebius_transform(std::vector<ModIntT> &x) {
  const int n = static_cast<int>(x.size());
  assert((n & (n - 1)) == 0);
  
  for (int i = n >> 1; i != 0; i >>= 1)
    for (int j = 0; j != n; ++j)
      if (j & i) x[j] -= x[j ^ i];
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  using mint = mm30<1000000009>;

  int n;
  std::cin >> n;
  std::vector<mint> a(1 << n), b(1 << n);
  for (auto &&i : a) std::cin >> i;
  for (auto &&i : b) std::cin >> i;

  std::vector ranked_zeta_a(n + 1, std::vector<mint>(1 << n)),
      ranked_zeta_b(n + 1, std::vector<mint>(1 << n)), ranked_zeta_ab(n + 1, std::vector<mint>(1 << n));
  for (int i = 0; i != 1 << n; ++i) {
    ranked_zeta_a[std::popcount(static_cast<unsigned>(i))][i] = a[i];
    ranked_zeta_b[std::popcount(static_cast<unsigned>(i))][i] = b[i];
  }
  for (int i = 0; i <= n; ++i) {
    zeta_transform(ranked_zeta_a[i]);
    zeta_transform(ranked_zeta_b[i]);
  }
  for (int i = 0; i <= n; ++i)
    for (int j = i; j >= 0; --j)
      for (int k = 0; k != 1 << n; ++k)
        ranked_zeta_ab[i][k] += ranked_zeta_a[j][k] * ranked_zeta_b[i - j][k];

  for (int i = 0; i <= n; ++i) moebius_transform(ranked_zeta_ab[i]);

  for (int i = 0; i != 1 << n; ++i)
    std::cout << ranked_zeta_ab[std::popcount(static_cast<unsigned>(i))][i] << ' ';
}
