#include <bits/stdc++.h>

template<unsigned P>
class modint {
  static_assert(1 <= P, "P must be a positive integer");

  using mint = modint<P>;

protected:
  unsigned v;

public:
  constexpr modint() : v() {}

  template<typename T,
           typename std::enable_if<std::is_integral<T>::value &&
                                       std::is_signed<T>::value,
                                   bool>::type = true>
  constexpr modint(T t_v) : v() {
    long long tmp = t_v % static_cast<long long>(P);
    if (tmp < 0) {
      tmp += P;
    }
    v = tmp;
  }

  template<typename T,
           typename std::enable_if<std::is_integral<T>::value &&
                                       std::is_unsigned<T>::value,
                                   bool>::type = true>
  constexpr modint(T t_v) : v() {
    v = t_v % P;
  }

  constexpr unsigned val() const {
    return v;
  }

  static constexpr unsigned mod() {
    return P;
  }

  static constexpr mint raw(unsigned v) {
    mint res;
    res.v = v;
    return res;
  }

  constexpr mint &operator+=(const mint &rhs) {
    v < P - rhs.v ? v += rhs.v : v -= P - rhs.v;
    return *this;
  }

  constexpr mint &operator++() {
    v + 1 < P ? ++v : v = 0;
    return *this;
  }

  constexpr mint operator++(int) {
    mint tmp = *this;
    v + 1 < P ? ++v : v = 0;
    return tmp;
  }

  constexpr mint &operator-=(const mint &rhs) {
    v < rhs.v ? v += P - rhs.v : v -= rhs.v;
    return *this;
  }

  constexpr mint &operator--() {
    v ? --v : v = P - 1;
    return *this;
  }
  
  constexpr mint operator--(int) {
    mint tmp = *this;
    v ? --v : v = P - 1;
    return tmp;
  }

  constexpr mint operator-() const {
    mint res;
    res.v = v ? P - v : 0;
    return res;
  }

  constexpr mint &operator*=(const mint &rhs) {
    v = static_cast<unsigned long long>(v) * rhs.v % P;
    return *this;
  }

  constexpr mint pow(unsigned long long b) const {
    mint a(*this), s(1);
    for (; b; b >>= 1) {
      if (b & 1) {
        s *= a;
      }
      a *= a;
    }
    return s;
  }

  constexpr mint inv() const {
    return pow(P - 2);
  }

  constexpr friend mint operator+(const mint &lhs, const mint &rhs) {
    return mint(lhs) += rhs;
  }                                                                              
                                                                                 
  constexpr friend mint operator-(const mint &lhs, const mint &rhs) {            
    return mint(lhs) -= rhs;                                                     
  }

  constexpr friend mint operator*(const mint &lhs, const mint &rhs) {
    return mint(lhs) *= rhs;
  }

  constexpr friend bool operator==(const mint &lhs, const mint &rhs) {
    return lhs.v == rhs.v;
  }

  constexpr friend bool operator!=(const mint &lhs, const mint &rhs) {
    return lhs.v != rhs.v;
  }

  friend std::istream &operator>>(std::istream &in, mint &x) {
    return in >> x.v;
  }

  friend std::ostream &operator<<(std::ostream &out, const mint &x) {
    return out << x.v;
  }
};

using mint = modint<998244353>;

auto operator*(const std::vector<mint> &x, const mint &v) {
  auto res = x;

  for (auto &y : res) {
    y *= v;
  }

  return res;
}

auto operator+(const std::vector<mint> &x, const std::vector<mint> &y) {
  std::vector<mint> res(std::max(x.size(), y.size()));

  for (int i = 0; i < (int)res.size(); ++i) {
    if (i < (int)x.size()) {
      res[i] += x[i];
    }

    if (i < (int)y.size()) {
      res[i] += y[i];
    }
  }

  return res;
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n ;
  std::cin >> n;

  std::vector<std::vector<std::pair<int, mint>>> a(n);
  std::vector<mint> b(n);

  for (int i = 0; i < n; ++i) {
    a[i].reserve(20);

    for (int j = 0; j < n; ++j) {
      int w;
      std::cin >> w;

      if (w > 0) {
        a[i].emplace_back(j, w);
      }
    }

    std::cin >> b[i];
  }

  std::vector<std::vector<mint>> f(n * 2 + 2, std::vector<mint>(n));
  f[0] = b;

  for (int i = 1; i < n * 2 + 2; ++i) {
    for (int j = 0; j < n; ++j) {
      for (auto [k, w] : a[j]) {
        f[i][j] += f[i - 1][k] * w;
      }
    }
  }

  std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
  std::vector<mint> rnd(n);

  for (int i = 0; i < n; ++i) {
    rnd[i] = mint(gen());
  }

  std::vector<mint> g(n * 2 + 2);

  for (int i = 0; i < n * 2 + 2; ++i) {
    for (int j = 0; j < n; ++j) {
      g[i] += rnd[j] * f[i][j];
    }
  }

  auto berlekampMassey = [&](const auto &s) {
    std::vector<mint> r{1}, r_{1};
    int p = -1;
    mint t_ = 1;

    for (int i = 0; i < (int)s.size(); ++i) {
      mint t = 0;

      for (int j = 0; j < (int)r.size(); ++j) {
        t += r[j] * s[i - j];
      }

      if (t == 0) {
        continue;
      }

      if (p == -1) {
        r.insert(r.end(), i + 1, 0);
        p = i;
        t_ = t;
      } else {
        auto temp = r_ * (-t * t_.inv());
        temp.insert(temp.begin(), i - p, 0);
        auto nr = r + temp;

        if (nr.size() > r.size()) {
          p = i;
          r_ = r;
          t_ = t;
        }

        r = nr;
      }
    }

    return r;
  };
  auto r = berlekampMassey(g);
  int m = r.size();

  std::vector<mint> res(n);

  for (int i = 1; i < m; ++i) {
    res = res + f[i - 1] * (-r[m - 1 - i]);
  }

  mint inv = r[m - 1].inv();

  for (int i = 0; i < n; ++i) {
    res[i] *= inv;
    std::cout << res[i] << " \n"[i + 1 == n];
  }
}