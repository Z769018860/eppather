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

struct ModInt32 {
public:
  using i32 = std::int32_t;
  using u32 = std::uint32_t;
  using i64 = std::int64_t;
  using u64 = std::uint64_t;
  using m32 = ModInt32;

private:
  u32 v;

  static inline u32 P, r, r2;

  static u32 get_r() {
    u32 iv = P;
    for (u32 i = 0; i != 4; ++i) iv *= 2U - P * iv;
    return -iv;
  }
  static u32 pow_mod(u32 x, u64 y) {
    u32 res = 1;
    for (; y != 0; y >>= 1, x = u64(x) * x % P)
      if (y & 1) res = u64(res) * x % P;
    return res;
  }
  static u32 reduce(u64 x) { return x + u64(u32(x) * r) * P >> 32; }
  static u32 norm(u32 x) { return x - (P & -(x >= P)); }

public:
  static void set_mod(u32 m) { P = m, r = get_r(), r2 = -u64(P) % P; }
  static u32 get_mod() { return P; }
  static u32 get_pr() {
    u32 tmp[32] = {}, cnt = 0;
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
  ModInt32() = default;
  ~ModInt32() = default;
  ModInt32(u32 v) : v(reduce(u64(v) * r2)) {}
  ModInt32(const m32 &rhs) : v(rhs.v) {}
  u32 get() const { return norm(reduce(v)); }
  explicit operator u32() const { return get(); }
  explicit operator i32() const { return i32(get()); }
  m32 &operator=(const m32 &rhs) { return v = rhs.v, *this; }
  m32 operator-() const {
    m32 res;
    return res.v = (P << 1 & -(v != 0)) - v, res;
  }
  m32 inv() const { return pow(P - 2); } 
  m32 &operator+=(const m32 &rhs) { return v += rhs.v - (P << 1), v += P << 1 & -(v >> 31), *this; }
  m32 &operator-=(const m32 &rhs) { return v -= rhs.v, v += P << 1 & -(v >> 31), *this; }
  m32 &operator*=(const m32 &rhs) { return v = reduce(u64(v) * rhs.v), *this; }
  m32 &operator/=(const m32 &rhs) { return this->operator*=(rhs.inv()); }
  friend m32 operator+(const m32 &lhs, const m32 &rhs) { return m32(lhs) += rhs; }
  friend m32 operator-(const m32 &lhs, const m32 &rhs) { return m32(lhs) -= rhs; }
  friend m32 operator*(const m32 &lhs, const m32 &rhs) { return m32(lhs) *= rhs; }
  friend m32 operator/(const m32 &lhs, const m32 &rhs) { return m32(lhs) /= rhs; }
  friend bool operator==(const m32 &lhs, const m32 &rhs) { return norm(lhs.v) == norm(rhs.v); }
  friend bool operator!=(const m32 &lhs, const m32 &rhs) { return norm(lhs.v) != norm(rhs.v); }
  friend std::istream &operator>>(std::istream &is, m32 &rhs) {
    return is >> rhs.v, rhs.v = reduce(u64(rhs.v) * r2), is;
  }
  friend std::ostream &operator<<(std::ostream &os, const m32 &rhs) { return os << rhs.get(); }
  m32 pow(i64 y) const {
    if ((y %= P - 1) < 0) y += P - 1; 
    m32 res(1), x(*this);
    for (; y != 0; y >>= 1, x *= x)
      if (y & 1) res *= x;
    return res;
  }
};

namespace Polynomials {

using poly = std::vector<ModInt32>;

int deg(const poly &x) { 
  int n = int(x.size()) - 1;
  const ModInt32 ZERO(0);
  while (n >= 0 && x[n] == ZERO) --n;
  return n;
}

poly &norm(poly &x) { return x.resize(std::max(deg(x) + 1, 1)), x; }

poly norm(poly &&x) { return x.resize(std::max(deg(x) + 1, 1)), x; }

poly add(const poly &x, const poly &y) {
  poly res(std::max(x.size(), y.size()));
  for (int i = 0, e = std::min(x.size(), y.size()); i != e; ++i) res[i] = x[i] + y[i];
  if (x.size() < y.size())
    std::copy(y.begin() + x.size(), y.end(), res.begin() + x.size());
  else
    std::copy(x.begin() + y.size(), x.end(), res.begin() + y.size());
  return norm(res);
}

poly sub(const poly &x, const poly &y) {
  poly res(std::max(x.size(), y.size()));
  for (int i = 0, e = std::min(x.size(), y.size()); i != e; ++i) res[i] = x[i] - y[i];
  if (x.size() < y.size())
    for (int i = x.size(), e = y.size(); i != e; ++i) res[i] = -y[i];
  else
    std::copy(x.begin() + y.size(), x.end(), res.begin() + y.size());
  return norm(res);
}

poly mul(const poly &x, const poly &y) {
  int n = deg(x) + 1, m = deg(y) + 1;
  if (n == 0 || m == 0) return {0};
  poly res(n + m - 1, ModInt32(0));
  for (int i = 0; i != n; ++i)
    for (int j = 0; j != m; ++j) res[i + j] += x[i] * y[j];
  return res;
}

std::pair<poly, poly> quo_with_rem(poly x, poly y) {
  int n = deg(norm(x)), m = deg(norm(y));
  if (n < m) return {{0}, x};
  if (m == 0) return {mul(x, {y[0].inv()}), {0}};
  ModInt32 lead(y[m]), lead_inv(lead.inv()); 
  for (int i = 0; i <= m; ++i) y[i] *= lead_inv;
  for (int i = 0; i <= n; ++i) x[i] *= lead_inv;
  poly res(n - m + 1, 0);
  for (int i = res.size() - 1; i >= 0; --i, --n)
    if ((res[i] = x[n]) != 0)
      for (int j = m, k = n; j >= 0; --j, --k) x[k] -= res[i] * y[j];
  return {res, mul(x, {lead})};
}

poly operator+(const poly &x, const poly &y) { return add(x, y); }
poly operator-(const poly &x, const poly &y) { return sub(x, y); }
poly operator*(const poly &x, const poly &y) { return mul(x, y); }
poly operator/(const poly &x, const poly &y) { return quo_with_rem(x, y).first; }
poly operator%(const poly &x, const poly &y) { return quo_with_rem(x, y).second; }

poly gcd(poly x, poly y) {
  while (deg(y) != -1) {
    poly r = x % y;
    x = y, y = r; 
  }
  return x;
}

poly pow_mod(poly x, int y, const poly &p) {
  poly res{1};
  x = x % p;
  for (; y != 0; y >>= 1, x = x * x % p)
    if (y & 1) res = res * x % p;
  return res;
}

poly random_poly(int d) {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_int_distribution<std::uint32_t> dis(1, ModInt32::get_mod() - 1);
  poly res(d + 1);
  for (int i = 0; i <= d; ++i) res[i] = dis(gen);
  return res;
}

poly solve(const poly &x) { 
  int d = deg(x);
  if (d <= 0) return {};
  if (d == 1) return {-x[0] / x[1]};
  poly y = random_poly(d - 1);
  poly z = gcd(x, y);
  if (deg(z) <= 0) z = gcd(x, pow_mod(y, ModInt32::get_mod() - 1 >> 1, x) - poly{1});
  poly x1 = solve(x / z), x2 = solve(z);
  x1.insert(x1.end(), x2.begin(), x2.end());
  return x1;
}

} 

using namespace Polynomials;

int main() {
#ifdef LOCAL
  std::freopen("..\\in", "r", stdin), std::freopen("..\\out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int n, p;
  std::cin >> n >> p;
  ModInt32::set_mod(p);
  poly a(n + 1);
  for (auto &i : a) std::cin >> i;
  auto b = gcd(a, pow_mod(poly{0, 1}, p, a) - poly{0, 1}); 
  int cnt = std::max(deg(b), 0);
  std::cout << cnt << '\n';
  if (cnt != 0) {
    auto ans = solve(b);
    std::vector<int> res;
    for (auto i : ans) res.push_back(int(i));
    std::sort(res.begin(), res.end());
    for (auto i : res) std::cout << i << ' ';
  }
  return 0;
}