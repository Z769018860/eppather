#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

using Int = long long;

template <class T1, class T2> ostream &operator<<(ostream &os, const pair<T1, T2> &a) { return os << "(" << a.first << ", " << a.second << ")"; };
template <class T> ostream &operator<<(ostream &os, const vector<T> &as) { const int sz = as.size(); os << "["; for (int i = 0; i < sz; ++i) { if (i >= 256) { os << ", ..."; break; } if (i > 0) { os << ", "; } os << as[i]; } return os << "]"; }
template <class T> void pv(T a, T b) { for (T i = a; i != b; ++i) cerr << *i << " "; cerr << endl; }
template <class T> bool chmin(T &t, const T &f) { if (t > f) { t = f; return true; } return false; }
template <class T> bool chmax(T &t, const T &f) { if (t < f) { t = f; return true; } return false; }
#define COLOR(s) ("\x1b[" s "m")








template <class Map, class F, class T>
long long discreteLog(F f, T a, T b, long long n, bool injective) {
  if (n <= 0) return -1;
  const int m = ceill(sqrtl(n));
  Map rs;
  T bb = b;
  for (int r = 1; r <= m; ++r) rs[bb = f * bb] = r;
  const F fm = f.pow(m);
  int counter = 0;
  for (int q = 0; q < m; ++q) {
    const T aa = fm * a;
    auto it = rs.find(aa);
    if (it != rs.end()) {
      if (injective) {
        const long long e = static_cast<long long>(m) * q + (m - it->second);
        return (e < n) ? e : -1;
      } else {
        for (int r = 0; r < m; ++r) {
          if (a == b) {
            const long long e = static_cast<long long>(m) * q + r;
            return (e < n) ? e : -1;
          }
          a = f * a;
        }
        if (++counter >= 2) break;
      }
    }
    a = aa;
  }
  return -1;
}





struct ModLong {
  static unsigned long long M;
  static long double INV_M;
  static void setM(unsigned long long m) { M = m; INV_M = 1.0L / M; }
  unsigned long long x;
  ModLong() : x(0ULL) {}
  ModLong(unsigned x_) : x(x_ % M) {}
  ModLong(unsigned long long x_) : x(x_ % M) {}
  ModLong(int x_) : x(((x_ %= static_cast<long long>(M)) < 0) ? (x_ + static_cast<long long>(M)) : x_) {}
  ModLong(long long x_) : x(((x_ %= static_cast<long long>(M)) < 0) ? (x_ + static_cast<long long>(M)) : x_) {}
  ModLong &operator+=(const ModLong &a) { x = ((x += a.x) >= M) ? (x - M) : x; return *this; }
  ModLong &operator-=(const ModLong &a) { x = ((x -= a.x) >= M) ? (x + M) : x; return *this; }
  ModLong &operator*=(const ModLong &a) {
    
    
    const long long y = x * a.x - M * static_cast<unsigned long long>(INV_M * x * a.x);
    x = (y < 0LL) ? (y + M) : (y >= static_cast<long long>(M)) ? (y - M) : y;
    return *this;
  }
  ModLong &operator/=(const ModLong &a) { return (*this *= a.inv()); }
  ModLong pow(long long e) const {
    if (e < 0) return inv().pow(-e);
    ModLong a = *this, b = 1ULL; for (; e; e >>= 1) { if (e & 1) b *= a; a *= a; } return b;
  }
  ModLong inv() const {
    unsigned long long a = M, b = x; long long y = 0, z = 1;
    for (; b; ) { const unsigned long long q = a / b; const unsigned long long c = a - q * b; a = b; b = c; const long long w = y - static_cast<long long>(q) * z; y = z; z = w; }
    assert(a == 1ULL); return ModLong(y);
  }
  ModLong operator+() const { return *this; }
  ModLong operator-() const { ModLong a; a.x = x ? (M - x) : 0ULL; return a; }
  ModLong operator+(const ModLong &a) const { return (ModLong(*this) += a); }
  ModLong operator-(const ModLong &a) const { return (ModLong(*this) -= a); }
  ModLong operator*(const ModLong &a) const { return (ModLong(*this) *= a); }
  ModLong operator/(const ModLong &a) const { return (ModLong(*this) /= a); }
  template <class T> friend ModLong operator+(T a, const ModLong &b) { return (ModLong(a) += b); }
  template <class T> friend ModLong operator-(T a, const ModLong &b) { return (ModLong(a) -= b); }
  template <class T> friend ModLong operator*(T a, const ModLong &b) { return (ModLong(a) *= b); }
  template <class T> friend ModLong operator/(T a, const ModLong &b) { return (ModLong(a) /= b); }
  explicit operator bool() const { return x; }
  bool operator==(const ModLong &a) const { return (x == a.x); }
  bool operator!=(const ModLong &a) const { return (x != a.x); }
  friend std::ostream &operator<<(std::ostream &os, const ModLong &a) { return os << a.x; }
};
unsigned long long ModLong::M;
long double ModLong::INV_M;



using Mint = ModLong;






struct Ell {
  static Mint A, B;
  static void setCurve(Mint a, Mint b) { A = a; B = b; }
  Mint x, y;
  bool z;
  Ell() : x(0), y(1), z(0) {}
  Ell(Mint x_, Mint y_) : x(x_), y(y_), z(1) {}
  friend ostream &operator<<(ostream &os, const Ell &p) {
    return os << "(" << p.x << ":" << p.y << ":" << p.z << ")";
  }
  bool isOn() const {
    return z ? (y*y == x*x*x + A*x + B) : (x == 0 && y == 1);
  }
  bool operator==(const Ell &p) const {
    return (x == p.x && y == p.y && z == p.z);
  }
  friend Ell operator*(const Ell &p, const Ell &q) {
    if (!p.z) return q;
    if (!q.z) return p;
    if (p.x == q.x && -p.y == q.y) return Ell();
    const Mint s = (p.x == q.x) ? ((3*p.x*p.x + A) / (2 * p.y)) : ((q.y - p.y) / (q.x - p.x));
    const Mint x = s*s - p.x - q.x;
    return Ell(x, -(p.y + s * (x - p.x)));
  }
  Ell pow(long long e) const {
    Ell p = *this, q;
    for (; ; p = p * p) {
      if (e & 1) q = q * p;
      if (!(e >>= 1)) return q;
    }
  }
};
Mint Ell::A, Ell::B;


#include <ext/pb_ds/assoc_container.hpp>
using __gnu_pbds::gp_hash_table;


#include <chrono>
struct Hash {
  static uint64_t splitmix64(uint64_t x) {
    
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
  size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
  }
  size_t operator()(const pair<int, int> &a) const {
    return operator()((uint64_t)a.first << 32 | a.second);
  }
  size_t operator()(const Ell &p) const {
    return operator()(p.x.x) ^ operator()(p.y.x);
  }
};
template <class K, class V> using Map = gp_hash_table<K, V, Hash>;


#include <chrono>
#ifdef LOCAL
mt19937_64 rng(58);
#else
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
#endif


vector<Mint> modSqrt(Mint a) {
  if (!a) return {0};
  if (Mint::M == 2) return {1};
  if (a.pow((Mint::M - 1) / 2).x != 1) return {};
  Mint b, d;
  for (; ; ) {
    b = (unsigned long long)rng();
    d = b * b - a;
    if (d.pow((Mint::M - 1) / 2).x != 1) break;
  }
  auto mul = [&](const pair<Mint, Mint> &f, const pair<Mint, Mint> &g) -> pair<Mint, Mint> {
    return make_pair(f.first * g.first + d * f.second * g.second, f.first * g.second + f.second * g.first);
  };
  pair<Mint, Mint> f(b, 1), g(1, 0);
  for (Int e = (Mint::M + 1) / 2; ; f = mul(f, f)) {
    if (e & 1) g = mul(g, f);
    if (!(e >>= 1)) break;
  }
  vector<Mint> ret{g.first, -g.first};
  if (ret[0].x > ret[1].x) swap(ret[0], ret[1]);
  return ret;
}

Int solve(Int P, Int A_, Int B_) {
  Mint::setM(P);
  const Mint A = A_, B = B_;
  Ell::setCurve(A, B);
  if (P < 10'000) {
    Int n = 1;
    for (Int x = 0; x < P; ++x) n += (int)modSqrt(Mint(x)*x*x + A*x + B).size();
    return n;
  }
  const Int lb = max(P + 1 - (Int)(2 * sqrtl(P)), 1LL);
  const Int ub = P + 1 + (Int)(2 * sqrtl(P));
  for (; ; ) {
    const Mint x = (unsigned long long)rng();
    const auto ys = modSqrt(x*x*x + A*x + B);
    if (ys.size()) {
      const Ell p(x, ys[0]);
      const Int s = discreteLog<Map<Ell, int>>(p, p.pow(lb), Ell(), ub - lb + 1, true);
      assert(~s);
      const Int n = lb + s;
      if (!~discreteLog<Map<Ell, int>>(p, p.pow(n + 1), Ell(), ub - (n + 1) + 1, true)) {
        return n;
      }
    }
  }
}

void stress() {
  for (const Int P : {2, 3, 5, 7, 11, 13, 17, 19}) {
    Mint::setM(P);
    vector<vector<Mint>> xss(P);
    for (Int x = 0; x < P; ++x) xss[(x*x) % P].push_back(x);
    for (Int y = 0; y < P; ++y) assert(xss[y] == modSqrt(y));
  }
  for (const Int P : {5, 7, 11, 101, 1009, 10007, 100003, 1000003}) {
    Mint::setM(P);
    const Int lb = max(P + 1 - (Int)(2 * sqrtl(P)), 1LL);
    const Int ub = P + 1 + (Int)(2 * sqrtl(P));
    for (int caseId = 0; caseId < 100; ++caseId) {
      const Mint A = (unsigned long long)rng();
      const Mint B = (unsigned long long)rng();
      if (Mint(4)*A*A*A + Mint(27)*B*B) {
        Int n = 1;
        for (Int x = 0; x < P; ++x) n += (int)modSqrt(Mint(x)*x*x + Mint(A)*x + B).size();
        cerr << P << " " << A << " " << B << ": " << n << " " << "[" << lb << ", " << ub << "]" << endl;
        assert(lb <= n); assert(n <= ub);
        const Int ans = solve(P, A.x, B.x);
        if (n != ans) {
          cerr << "FAIL " << P << " " << A << " " << B << ": " << n << " " << ans << endl;
        }
        assert(n == ans);
      }
    }
  }
}

int main() {
  
  
  Int P, A, B;
  for (; ~scanf("%lld%lld%lld", &P, &A, &B); ) {
    const Int ans = solve(P, A, B);
    printf("%lld\n", ans);
  }
  return 0;
}
