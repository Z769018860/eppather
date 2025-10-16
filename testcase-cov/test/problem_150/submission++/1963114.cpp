#include <bits/stdc++.h>



const int kMaxN = 4e5 + 5, kMod = 998244353;

constexpr int qpow(int bs, int64_t idx = kMod - 2) {
  int ret = 1;
  for (; idx; idx >>= 1, bs = (int64_t)bs * bs % kMod)
    if (idx & 1)
      ret = (int64_t)ret * bs % kMod;
  return ret;
}

inline int add(int x, int y) { return (x + y >= kMod ? x + y - kMod : x + y); }
inline int sub(int x, int y) { return (x >= y ? x - y : x - y + kMod); }
inline void inc(int &x, int y) { (x += y) >= kMod ? x -= kMod : x; }
inline void dec(int &x, int y) { (x -= y) < 0 ? x += kMod : x; }

namespace POLY {
constexpr int kR = 3, kB = __builtin_ctz(kMod - 1), kG = qpow(kR, (kMod - 1) >> kB);

int polyg[kMaxN];
bool inited;

int bsgs(int a, int b) {
  a = (a % kMod + kMod) % kMod, b = (b % kMod + kMod) % kMod;
  int t = sqrt(kMod) + 1;
  std::unordered_map<int, int> mp;
  for (int i = 0, m = b; i <= t; ++i, m = (int64_t)m * a % kMod)
    mp[m] = i;
  int aa = qpow(a, t);
  for (int i = t, m = aa;; i += t, m = (int64_t)m * aa % kMod)
    if (mp.count(m))
      return i - mp[m];
  assert(0);
}

int getsqrt(int x) {
  x = (x % kMod + kMod) % kMod;
  if (x == 0 || x == 1) return x;
  int a = bsgs(kR, x);
  assert(a % 2 == 0);
  int ret = qpow(kR, a / 2);
  return std::min(ret, kMod - ret);
}

void prework(int n = (kMaxN - 5) / 2) {
  inited = 1;
  int c = 0;
  for (; (1 << c) <= n; ++c) {}
  c = std::min(c - 1, kB - 2);
  polyg[0] = 1, polyg[1 << c] = qpow(kG, 1 << (kB - 2 - c));
  for (int i = c; i; --i)
    polyg[1 << i - 1] = (int64_t)polyg[1 << i] * polyg[1 << i] % kMod;
  for (int i = 1; i < (1 << c); ++i) 
    polyg[i] = (int64_t)polyg[i & (i - 1)] * polyg[i & -i] % kMod;
}

int getlen(int n) {
  int len = 1;
  for (; len <= n; len <<= 1) {}
  return len;
}

struct Poly : std::vector<int> {
  using vector::vector;
  using vector::operator [];

  friend Poly operator -(Poly a) {
    static Poly c;
    c.resize(a.size());
    for (int i = 0; i < c.size(); ++i)
      c[i] = sub(0, c[i]);
    return c;
  }
  friend Poly operator +(Poly a, Poly b) {
    static Poly c;
    c.resize(std::max(a.size(), b.size()));
    for (int i = 0; i < c.size(); ++i)
      c[i] = add((i < a.size() ? a[i] : 0), (i < b.size() ? b[i] : 0));
    return c;
  }
  friend Poly operator -(Poly a, Poly b) {
    static Poly c;
    c.resize(std::max(a.size(), b.size()));
    for (int i = 0; i < c.size(); ++i)
      c[i] = sub((i < a.size() ? a[i] : 0), (i < b.size() ? b[i] : 0));
    return c;
  }
  friend void dif(Poly &a, int len) {
    if (a.size() < len) a.resize(len);
    for (int l = len; l != 1; l >>= 1) {
      int m = l / 2;
      for (int i = 0, k = 0; i < len; i += l, ++k) {
        for (int j = 0; j < m; ++j) {
          int tmp = (int64_t)a[i + j + m] * polyg[k] % kMod;
          a[i + j + m] = sub(a[i + j], tmp);
          inc(a[i + j], tmp);
        }
      }
    }
  }
  friend void dit(Poly &a, int len) {
    if (a.size() < len) a.resize(len);
    for (int l = 2; l <= len; l <<= 1) {
      int m = l / 2;
      for (int i = 0, k = 0; i < len; i += l, ++k) {
        for (int j = 0; j < m; ++j) {
          int tmp = a[i + j + m];
          a[i + j + m] = (int64_t)sub(a[i + j], tmp) * polyg[k] % kMod;
          inc(a[i + j], tmp);
        }
      }
    }
    int invl = qpow(len);
    for (int i = 0; i < len; ++i)
      a[i] = (int64_t)a[i] * invl % kMod;
    std::reverse(a.begin() + 1, a.begin() + len);
  }
  friend Poly operator *(Poly a, Poly b) {
    if (!inited) prework();
    int n = a.size() + b.size() - 1, len = getlen(n);
    a.resize(len), b.resize(len);
    dif(a, len), dif(b, len);
    for (int i = 0; i < len; ++i)
      a[i] = (int64_t)a[i] * b[i] % kMod;
    dit(a, len);
    a.resize(n);
    return a;
  }
  friend Poly operator *(Poly a, int b) {
    static Poly c;
    c = a;
    for (auto &x : c) x = (int64_t)x * b % kMod;
    return c;
  }
  friend Poly operator *(int a, Poly b) {
    static Poly c;
    c = b;
    for (auto &x : c) x = (int64_t)x * a % kMod;
    return c;
  }
  friend void operator *=(Poly &a, Poly b) {
    if (!inited) prework();
    int n = a.size() + b.size() - 1, len = getlen(n);
    a.resize(len), b.resize(len);
    dif(a, len), dif(b, len);
    for (int i = 0; i < len; ++i)
      a[i] = (int64_t)a[i] * b[i] % kMod;
    dit(a, len);
    a.resize(n);
  }
  friend Poly Int(Poly a) {
    Poly b(a.size() + 1);
    for (int i = 0; i < a.size(); ++i)
      b[i + 1] = (int64_t)a[i] * qpow(i + 1) % kMod;
    return b;
  }
  friend Poly Der(Poly a) {
    Poly b(a.size() - 1);
    for (int i = 1; i < a.size(); ++i)
      b[i - 1] = (int64_t)a[i] * i % kMod;
    return b;
  }
  friend Poly Inv(Poly a) {
    Poly G = {qpow(a[0])}, H;
    std::vector<int> vec;
    for (int i = a.size(); i != 1; i = (i + 1) / 2) vec.emplace_back(i);
    vec.emplace_back(1);
    std::reverse(vec.begin(), vec.end());
    for (auto n : vec) {
      auto tmp = a;
      tmp.resize(n);
      H = G, G = 2 * H;
      G.resize(n);
      int len = getlen(n * 2 + 2);
      if (!inited) prework();
      dif(tmp, len), dif(H, len);
      for (int i = 0; i < len; ++i)
        H[i] = (int64_t)tmp[i] * H[i] % kMod * H[i] % kMod;
      dit(H, len);
      for (int i = 0; i < n; ++i)
        G[i] = sub(G[i], H[i]);
    }
    return G;
  }
  friend Poly Sqrt(Poly a) {
    Poly G = {getsqrt(a[0])}, H;
    std::vector<int> vec;
    for (int i = a.size(); i != 1; i = (i + 1) / 2) vec.emplace_back(i);
    vec.emplace_back(1);
    std::reverse(vec.begin(), vec.end());
    for (auto n : vec) {
      H = G;
      auto tmp = a + H * H;
      tmp.resize(n);
      for (auto &x : H) inc(x, x);
      H.resize(n);
      tmp *= Inv(H), tmp.resize(n);
      G = tmp;
    }
    return G;
  }
  friend Poly Ln(Poly a) {
    assert(a[0] == 1);
    int n = a.size();
    Poly b, c, tmp;
    if (n == 1) {
      b.resize(a.size());
      return b;
    }
    b.resize(n - 1);
    for (int i = 1; i < n; ++i)
      b[i - 1] = (int64_t)i * a[i] % kMod;
    tmp = Inv(a);
    b = b * tmp;
    c.resize(n);
    for (int i = 0; i < n - 1; ++i)
      c[i + 1] = (int64_t)b[i] * qpow(i + 1) % kMod;
    return c;
  }
  friend Poly Exp(Poly a) {
    assert(!a[0]);
    int n = a.size();
    Poly B = {1};
    std::vector<int> v;
    for (int i = n; i != 1; i = (i + 1) / 2) v.emplace_back(i);
    std::reverse(v.begin(), v.end());
    for (auto x : v) {
      B.resize(x);
      B = B * (a - Ln(B) + (Poly){1});
    }
    B.resize(n);
    return B;
  }
  friend Poly _Pow(Poly a, int k) {
    assert(a[0] == 1);
    int n = a.size();
    a = Ln(a);
    for (auto &x : a) x = (int64_t)x * k % kMod;
    a = Exp(a);
    return a;
  }
  friend Poly Pow(Poly a, int k) {
    int k1 = k % kMod, k2 = k % (kMod - 1), dv = (k >= kMod);
    if (a[0] == 1) {
      return _Pow(a, k1);
    } else {
      int n = a.size(), p = n - 1;
      for (int i = 0; i < n; ++i) {
        if (a[i]) {
          p = i;
          break;
        }
      }
      if (dv && p || (int64_t)k1 * p >= n) return (Poly)(0, n);
      Poly b;
      int vv = qpow(a[p]);
      for (int i = p; i < n - (k1 - 1) * p; ++i)
        b.emplace_back((int64_t)a[i] * vv % kMod);
      b = _Pow(b, k1);
      int v = qpow(a[p], k2);
      Poly c(k1 * p, 0);
      for (int i = 0; i < n - k1 * p; ++i)
        c.emplace_back((int64_t)b[i] * v % kMod);
      return c;
    }
  }
  friend Poly Pow(Poly a, std::string s) {
    int k1 = 0, k2 = 0, dv = 0;
    for (auto c : s) {
      if (10ll * k1 + c - '0' >= kMod) dv = 1;
      k1 = (10ll * k1 + c - '0') % kMod;
      k2 = (10ll * k2 + c - '0') % (kMod - 1);
    }
    if (a[0] == 1) {
      return _Pow(a, k1);
    } else {
      int n = a.size(), p = n - 1;
      for (int i = 0; i < n; ++i) {
        if (a[i]) {
          p = i;
          break;
        }
      }
      if (dv && p || (int64_t)k1 * p >= n) return (Poly)(0, n);
      Poly b;
      int vv = qpow(a[p]);
      for (int i = p; i < n - (k1 - 1) * p; ++i)
        b.emplace_back((int64_t)a[i] * vv % kMod);
      b = _Pow(b, k1);
      int v = qpow(a[p], k2);
      Poly c(k1 * p, 0);
      for (int i = 0; i < n - k1 * p; ++i)
        c.emplace_back((int64_t)b[i] * v % kMod);
      return c;
    }
  }
};
} 

using POLY::Poly;

void dickdreamer() {
  int n, k;
  std::cin >> n >> k;
  Poly F(n + 1);
  for (auto &x : F) std::cin >> x;
  Poly G = Der(Pow((Poly){1} + Ln((Poly){2} + F - (Poly){F[0]} - Exp(Int(Inv(Sqrt(F))))), k));
  G.resize(n);
  for (auto &x : G) std::cout << x << ' ';
}

int32_t main() {
#ifdef ORZXKR
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  std::ios::sync_with_stdio(0), std::cin.tie(0), std::cout.tie(0);
  int T = 1;
  
  while (T--) dickdreamer();
  
  return 0;
}