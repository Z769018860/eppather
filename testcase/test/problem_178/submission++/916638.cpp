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
#include <random>
#include <vector>

struct MontgomeryModInt32 {
public:
  using i32 = std::int32_t;
  using u32 = std::uint32_t;
  using i64 = std::int64_t;
  using u64 = std::uint64_t;

private:
  u32 v;

  static u32 get_r() {
    u32 iv = P;
    for (u32 i = 0; i != 4; ++i) iv *= 2U - P * iv;
    return -iv;
  }

  static inline u32 P, r, r2;

public:
  static void set_mod(u32 m) { P = m, r = get_r(), r2 = -u64(P) % P; }
  static u32 get_p() { return P; }

  MontgomeryModInt32() = default;
  ~MontgomeryModInt32() = default;
  MontgomeryModInt32(u32 v) : v(reduce(u64(v) * r2)) {}
  MontgomeryModInt32(const MontgomeryModInt32 &rhs) : v(rhs.v) {}
  static u32 reduce(u64 x) { return x + (u64(u32(x) * r) * P) >> 32; }
  static u32 norm(u32 x) { return x - (P & -(x >= P)); }
  u32 get() const {
    u32 res = reduce(v) - P;
    return res + (P & -(res >> 31));
  }
  explicit operator u32() const { return get(); }
  explicit operator i32() const { return i32(get()); }
  MontgomeryModInt32 &operator=(const MontgomeryModInt32 &rhs) { return v = rhs.v, *this; }
  MontgomeryModInt32 operator-() const {
    MontgomeryModInt32 res;
    return res.v = (P << 1 & -(v != 0)) - v, res;
  }
  MontgomeryModInt32 inv() const { return pow(-1); }
  MontgomeryModInt32 &operator+=(const MontgomeryModInt32 &rhs) {
    return v += rhs.v - (P << 1), v += P << 1 & -(v >> 31), *this;
  }
  MontgomeryModInt32 &operator-=(const MontgomeryModInt32 &rhs) {
    return v -= rhs.v, v += P << 1 & -(v >> 31), *this;
  }
  MontgomeryModInt32 &operator*=(const MontgomeryModInt32 &rhs) {
    return v = reduce(u64(v) * rhs.v), *this;
  }
  MontgomeryModInt32 &operator/=(const MontgomeryModInt32 &rhs) {
    return this->operator*=(rhs.inv());
  }
  friend MontgomeryModInt32 operator+(const MontgomeryModInt32 &lhs,
                                      const MontgomeryModInt32 &rhs) {
    return MontgomeryModInt32(lhs) += rhs;
  }
  friend MontgomeryModInt32 operator-(const MontgomeryModInt32 &lhs,
                                      const MontgomeryModInt32 &rhs) {
    return MontgomeryModInt32(lhs) -= rhs;
  }
  friend MontgomeryModInt32 operator*(const MontgomeryModInt32 &lhs,
                                      const MontgomeryModInt32 &rhs) {
    return MontgomeryModInt32(lhs) *= rhs;
  }
  friend MontgomeryModInt32 operator/(const MontgomeryModInt32 &lhs,
                                      const MontgomeryModInt32 &rhs) {
    return MontgomeryModInt32(lhs) /= rhs;
  }
  friend bool operator==(const MontgomeryModInt32 &lhs, const MontgomeryModInt32 &rhs) {
    return norm(lhs.v) == norm(rhs.v);
  }
  friend bool operator!=(const MontgomeryModInt32 &lhs, const MontgomeryModInt32 &rhs) {
    return norm(lhs.v) != norm(rhs.v);
  }
  friend std::istream &operator>>(std::istream &is, MontgomeryModInt32 &rhs) {
    return is >> rhs.v, rhs.v = reduce(u64(rhs.v) * r2), is;
  }
  friend std::ostream &operator<<(std::ostream &os, const MontgomeryModInt32 &rhs) {
    return os << rhs.get();
  }
  MontgomeryModInt32 pow(i64 y) const {
    if ((y %= P - 1) < 0) y += P - 1; 
    MontgomeryModInt32 res(1), x(*this);
    for (; y != 0; y >>= 1, x *= x)
      if (y & 1) res *= x;
    return res;
  }
};

namespace test {

using value_type = MontgomeryModInt32;
using poly = std::vector<value_type>;

std::int32_t deg(const poly &x) {
  std::int32_t n = std::int32_t(x.size()) - 1;
  value_type z(0);
  while (n >= 0 && x[n] == z) --n;
  return n;
}

poly &norm(poly &x) { return x.resize(std::max(1, deg(x) + 1)), x; }

poly norm(poly &&x) { return x.resize(std::max(1, deg(x) + 1)), x; }

poly add(const poly &x, const poly &y) { 
  using i32 = std::int32_t;
  poly res(std::max(x.size(), y.size()));
  for (i32 i = 0, e = std::min(x.size(), y.size()); i != e; ++i) res[i] = x[i] + y[i];
  if (x.size() < y.size())
    std::copy(y.begin() + x.size(), y.end(), res.begin() + x.size());
  else
    std::copy(x.begin() + y.size(), x.end(), res.begin() + y.size());
  return norm(res);
}

poly sub(const poly &x, const poly &y) { 
  using i32 = std::int32_t;
  poly res(std::max(x.size(), y.size()));
  for (i32 i = 0, e = std::min(x.size(), y.size()); i != e; ++i) res[i] = x[i] - y[i];
  if (x.size() < y.size())
    for (i32 i = x.size(), e = y.size(); i != e; ++i) res[i] = -y[i];
  else
    std::copy(x.begin() + y.size(), x.end(), res.begin() + y.size());
  return norm(res);
}

poly mul(const poly &x, const poly &y) {
  using i32 = std::int32_t;
  i32 n = deg(x) + 1, m = deg(y) + 1;
  if (n == 0 || m == 0) return {0};
  poly res(n + m - 1, 0);
  for (i32 i = 0; i != n; ++i)
    for (i32 j = 0; j != m; ++j) res[i + j] += x[i] * y[j];
  return res;
}

std::pair<poly, poly> quo_with_rem(poly x, poly y) {
  using i32 = std::int32_t;
  i32 n = deg(norm(x)), m = deg(norm(y));
  if (n < m) return {{0}, x};
  if (m == 0) return {mul(x, {y[0].inv()}), {0}};
  value_type lead(y[m]), lead_inv(lead.inv()); 
  for (i32 i = 0; i <= m; ++i) y[i] *= lead_inv;
  for (i32 i = 0; i <= n; ++i) x[i] *= lead_inv;
  poly res(n - m + 1, 0);
  for (i32 i = res.size() - 1; i >= 0; --i, --n)
    if ((res[i] = x[n]) != 0)
      for (i32 j = m, k = n; j >= 0; --j, --k) x[k] -= res[i] * y[j];
  return {res, mul(x, {lead})};
}

poly operator+(const poly &x, const poly &y) { return add(x, y); }
poly operator-(const poly &x, const poly &y) { return sub(x, y); }
poly operator*(const poly &x, const poly &y) { return mul(x, y); }
poly operator/(const poly &x, const poly &y) { return quo_with_rem(x, y).first; }
poly operator%(const poly &x, const poly &y) { return quo_with_rem(x, y).second; }

poly gcd(const poly &x, const poly &y) { return deg(y) == -1 ? x : gcd(y, x % y); }

poly pow_mod(poly x, std::uint32_t y, const poly &p) {
  poly res{1};
  x = x % p;
  for (; y != 0; y >>= 1, x = x * x % p)
    if (y & 1) res = res * x % p;
  return res;
}

poly random_poly(std::uint32_t d) {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_int_distribution<std::uint32_t> dis(1, value_type::get_p() - 1);
  using i32 = std::int32_t;
  poly res(d + 1);
  for (i32 i = 0; i <= d; ++i) res[i] = dis(gen);
  return res;
}

std::vector<int> ans;

void solve(const poly &x) { 
  using i32 = std::int32_t;
  i32 n = deg(x);
  if (n <= 0) return;
  if (n == 1) {
    ans.push_back(int(-x[0] / x[1]));
    return;
  }
  auto k = random_poly(n - 1);
  auto l = gcd(k, x);
  if (deg(l) > 0 && deg(l) != n) {
    solve(x / l), solve(l);
  } else {
    auto m = pow_mod(k, value_type::get_p() - 1 >> 1, x) - poly{1};
    l = gcd(m, x);
    if (deg(l) > 0 && deg(l) != n)
      solve(x / l), solve(l);
    else
      solve(x);
  }
}

} 

int main() {
#ifdef LOCAL
  std::freopen("..\\in", "r", stdin), std::freopen("..\\out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  using namespace test;
  int n, p, v;
  std::cin >> n >> p;

  MontgomeryModInt32::set_mod(p);

  poly a;
  for (int i = 0; i <= n; ++i) std::cin >> v, a.emplace_back(v);
  auto k = gcd(a, pow_mod(poly{0, 1}, p, a) - poly{0, 1});
  auto cnt = std::max(deg(k), 0);
  std::cout << cnt << '\n';
  if (cnt != 0) {
    solve(k);
    sort(ans.begin(), ans.end());
    for (auto i : ans) std::cout << i << ' ';
  }
  return 0;
}