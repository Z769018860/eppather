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


template <unsigned M_> struct ModInt {
  static constexpr unsigned M = M_;
  unsigned x;
  constexpr ModInt() : x(0U) {}
  constexpr ModInt(unsigned x_) : x(x_ % M) {}
  constexpr ModInt(unsigned long long x_) : x(x_ % M) {}
  constexpr ModInt(int x_) : x(((x_ %= static_cast<int>(M)) < 0) ? (x_ + static_cast<int>(M)) : x_) {}
  constexpr ModInt(long long x_) : x(((x_ %= static_cast<long long>(M)) < 0) ? (x_ + static_cast<long long>(M)) : x_) {}
  ModInt &operator+=(const ModInt &a) { x = ((x += a.x) >= M) ? (x - M) : x; return *this; }
  ModInt &operator-=(const ModInt &a) { x = ((x -= a.x) >= M) ? (x + M) : x; return *this; }
  ModInt &operator*=(const ModInt &a) { x = (static_cast<unsigned long long>(x) * a.x) % M; return *this; }
  ModInt &operator/=(const ModInt &a) { return (*this *= a.inv()); }
  ModInt pow(long long e) const {
    if (e < 0) return inv().pow(-e);
    ModInt a = *this, b = 1U; for (; e; e >>= 1) { if (e & 1) b *= a; a *= a; } return b;
  }
  ModInt inv() const {
    unsigned a = M, b = x; int y = 0, z = 1;
    for (; b; ) { const unsigned q = a / b; const unsigned c = a - q * b; a = b; b = c; const int w = y - static_cast<int>(q) * z; y = z; z = w; }
    assert(a == 1U); return ModInt(y);
  }
  ModInt operator+() const { return *this; }
  ModInt operator-() const { ModInt a; a.x = x ? (M - x) : 0U; return a; }
  ModInt operator+(const ModInt &a) const { return (ModInt(*this) += a); }
  ModInt operator-(const ModInt &a) const { return (ModInt(*this) -= a); }
  ModInt operator*(const ModInt &a) const { return (ModInt(*this) *= a); }
  ModInt operator/(const ModInt &a) const { return (ModInt(*this) /= a); }
  template <class T> friend ModInt operator+(T a, const ModInt &b) { return (ModInt(a) += b); }
  template <class T> friend ModInt operator-(T a, const ModInt &b) { return (ModInt(a) -= b); }
  template <class T> friend ModInt operator*(T a, const ModInt &b) { return (ModInt(a) *= b); }
  template <class T> friend ModInt operator/(T a, const ModInt &b) { return (ModInt(a) /= b); }
  explicit operator bool() const { return x; }
  bool operator==(const ModInt &a) const { return (x == a.x); }
  bool operator!=(const ModInt &a) const { return (x != a.x); }
  friend std::ostream &operator<<(std::ostream &os, const ModInt &a) { return os << a.x; }
};


constexpr unsigned MO = 998244353;
using Mint = ModInt<MO>;


vector<Mint> findLinearRecurrence(const vector<Mint> &as) {
  const int n = as.size();
  int d = 0, m = 0;
  vector<Mint> cs(n + 1, 0), bs(n + 1, 0);
  cs[0] = bs[0] = 1;
  Mint invBef = 1;
  for (int i = 0; i < n; ++i) {
    ++m;
    Mint dif = as[i];
    for (int j = 1; j < d + 1; ++j) dif += cs[j] * as[i - j];
    if (dif.x != 0) {
      auto csDup = cs;
      const Mint r = dif * invBef;
      for (int j = m; j < n; ++j) cs[j] -= r * bs[j - m];
      if (2 * d <= i) {
        d = i + 1 - d;
        m = 0;
        bs = csDup;
        invBef = dif.inv();
      }
    }
  }
  cs.resize(d + 1);
  return cs;
}


#include <chrono>
#ifdef LOCAL
mt19937_64 rng(58);
#else
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
#endif


int N;
Mint A[2510][2510];

int main() {
  for (; ~scanf("%d", &N); ) {
    for (int i = 0; i < N; ++i) for (int j = 0; j <= N; ++j) {
      scanf("%u", &A[i][j].x);
    }
    
    vector<pair<pair<int, int>, Mint>> es;
    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) if (A[i][j]) {
      es.emplace_back(make_pair(i, j), A[i][j]);
    }
    
    for (; ; ) {
      vector<Mint> us(N), vs(N);
      for (int i = 0; i < N; ++i) us[i] = (unsigned long long)rng();
      for (int i = 0; i < N; ++i) vs[i] = (unsigned long long)rng();
      vector<Mint> seq(2 * N, 0);
      for (int h = 0; h < 2 * N; ++h) {
        for (int i = 0; i < N; ++i) seq[h] += us[i] * vs[i];
        vector<Mint> vvs(N, 0);
        for (const auto &e : es) vvs[e.first.first] += e.second * vs[e.first.second];
        vs.swap(vvs);
      }
      const auto cs = findLinearRecurrence(seq);

      const int d = (int)cs.size() - 1;
      
      if (!cs[d]) continue;
      vector<Mint> bs(N);
      {
        const Mint t = -cs[d].inv();
        for (int i = 0; i < N; ++i) bs[i] = t * A[i][N];
      }
      vector<Mint> ans(N, 0);
      for (int h = 1; h <= d; ++h) {
        for (int i = 0; i < N; ++i) ans[i] += cs[d - h] * bs[i];
        vector<Mint> bbs(N, 0);
        for (const auto &e : es) bbs[e.first.first] += e.second * bs[e.first.second];
        bs.swap(bbs);
      }
      vector<Mint> judge(N, 0);
      for (const auto &e : es) judge[e.first.first] += e.second * ans[e.first.second];
      bool ok = true;
      for (int i = 0; i < N; ++i) ok = ok && (judge[i] == A[i][N]);
      if (ok) {
        for (int i = 0; i < N; ++i) {
          if (i) printf(" ");
          printf("%u", ans[i].x);
        }
        puts("");
        break;
      }
    }
  }
  return 0;
}
