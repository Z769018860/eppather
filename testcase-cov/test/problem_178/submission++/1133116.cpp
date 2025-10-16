
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cctype>

#include <algorithm>
#include <random>
#include <bitset>
#include <queue>
#include <functional>
#include <set>
#include <map>
#include <vector>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <limits>
#include <numeric>

#define LOG(FMT...) fprintf(stderr, FMT)

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

using ui = unsigned int;
using ull = unsigned long long;

static ui MOD, INV, R2;

int mpow(int x, int k) {
  if (k == 0)return 1;
  int ret = mpow(x * (ull) x % MOD, k >> 1);
  if (k & 1)
    ret = ret * (ull) x % MOD;
  return ret;
}

static ui reduce(ull x) {
  ui y = ui(x >> 32) - ui((ull(ui(x) * INV) * MOD) >> 32);
  return int(y) < 0 ? y + MOD : y;
}

struct Mont {
  ui x_;
  Mont() : x_(0) {}
  Mont(ui x) : x_(reduce(ull(x) * R2)) {}
  Mont &operator+=(Mont rhs) {
    x_ += rhs.x_ - MOD;
    if (int(x_) < 0)x_ += MOD;
    return *this;
  }
  Mont operator+(Mont rhs) const { return Mont(*this) += rhs; }
  Mont &operator*=(Mont rhs) {
    x_ = reduce(ull(x_) * rhs.x_);
    return *this;
  }
  Mont operator*(Mont rhs) const { return Mont(*this) *= rhs; }
  Mont operator-=(Mont rhs) {
    x_ -= rhs.x_;
    if (int(x_) < 0)x_ += MOD;
    return *this;
  }
  ui get() const { return reduce(x_); }
};

void setMOD(ui p) {
  MOD = p;
  INV = MOD;
  for (int rep = 0; rep < 4; ++rep) INV *= 2 - INV * MOD;
  R2 = -ull(MOD) % MOD;
}

Mont pow(const Mont& x, ui k) {
  if (k == 0) return 1;
  Mont ret = pow(x * x, k >> 1);
  if (k & 1) ret *= x;
  return ret;
}

Mont inv(const Mont& x) { return pow(x, MOD - 2); }

using Poly = vector<Mont>;

Poly rem(Poly a, Poly b) {
  if (a.size() < b.size()) a.resize(b.size() - 1);
  Mont monic = inv(b.back());
  for (auto& x : b) x *= monic;
  while (a.size() >= b.size()) {
    for (int i = b.size(); i; --i)
      a[a.size() - i] -= a.back() * b[b.size() - i];
    a.pop_back();
  }
  return a;
}

Poly div(Poly a, Poly b) {
  if (a.size() < b.size()) a.resize(b.size() - 1);
  Poly ret;
  Mont monic = inv(b.back());
  for (auto& x : b) x *= monic;
  while (a.size() >= b.size()) {
    ret.push_back(a.back());
    for (int i = b.size(); i; --i)
      a[a.size() - i] -= a.back() * b[b.size() - i];
    a.pop_back();
  }
  reverse(ret.begin(), ret.end());
  return ret;
}

Poly mul(const Poly& a, const Poly& b) {
  int n = a.size() - 1, m = b.size() - 1;
  Poly ret(n + m + 1);
  for (int i = 0; i <= n + m; ++i) for (int j = max(0, i - m); j <= min(n, i); ++j)
    ret[i] += a[j] * b[i - j];
  return ret;
}

Poly pow(const Poly& a, const Poly& mod, ui k) {
  if (k == 0) return {1};
  Poly ret = pow(rem(mul(a, a), mod), mod, k >> 1);
  if (k & 1) ret = rem(mul(ret, a), mod);
  return ret;
}

Poly gcd(Poly a, Poly b) {
  while (true) {
    while (!b.empty() && !b.back().get()) b.pop_back();
    if (b.empty()) return a;
    a = rem(a, b);
    swap(a, b);
  }
}

int main() {
#ifdef ELEGIA
  freopen("test.in", "r", stdin);
  int nol_cl = clock();
#endif
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ui n, p; cin >> n >> p;
  setMOD(p);
  Poly a(n + 1);
  for (int i = 0; i <= n; ++i) {
    int x; cin >> x;
    a[i] = x;
  }
  queue<Poly> q;
  Poly x(2); x[1] = 1;
  x = rem(x, a);
  Poly xp = pow(x, a, p);
  for (int i = 0; i != n; ++i) xp[i] -= x[i];
  q.push(gcd(a, xp));
  vector<ui> roots;
  uniform_int_distribution<ui> uid(0, p - 1);
  while (!q.empty()) {
    a = q.front(); q.pop();
    if (a.size() == 1) continue;
    if (a.size() == 2) {
      Mont root = 0;
      root -= a[0] * inv(a[1]);
      roots.push_back(root.get());
      continue;
    }
    Poly rnd(a.size() - 1);
    for (auto& x : rnd) x = uid(rng);
    rnd = pow(rnd, a, (p - 1) / 2);
    rnd[0] -= 1;
    rnd = gcd(rnd, a);
    q.push(rnd); q.push(div(a, rnd));
  }
  sort(roots.begin(), roots.end());
  cout << roots.size() << '\n';
  for (int i = 0; i != roots.size(); ++i) cout << roots[i] << ' ';

#ifdef ELEGIA
  LOG("Time: %dms\n", int ((clock()
          -nol_cl) / (double)CLOCKS_PER_SEC * 1000));
#endif
  return 0;
}
