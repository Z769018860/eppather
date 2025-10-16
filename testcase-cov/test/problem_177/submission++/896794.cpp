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
#include <limits>
#include <numeric>

#define LOG(FMT...) fprintf(stderr, FMT)

using namespace std;

typedef long long ll;
typedef unsigned long long ull;



template<class T>
istream &operator>>(istream &is, vector<T> &v) {
  for (T &x : v)
    is >> x;
  return is;
}

template<class T>
ostream &operator<<(ostream &os, const vector<T> &v) {
  if (!v.empty()) {
    os << v.front();
    for (int i = 1; i < v.size(); ++i)
      os << ' ' << v[i];
  }
  return os;
}

typedef vector<int> Perm;

Perm operator*(const Perm &p, const Perm &q) {
  int n = p.size();
  Perm r(n);
  for (int i = 0; i < n; ++i)
    r[i] = q[p[i]];
  return r;
}

Perm inv(const Perm &p) {
  int n = p.size();
  Perm q(n);
  for (int i = 0; i < n; ++i)
    q[p[i]] = i;
  return q;
}

Perm id(int n) {
  Perm p(n);
  iota(p.begin(), p.end(), 0);
  return p;
}

Perm trunc(const Perm &p) {
  return Perm(p.begin(), p.end() - 1);
}

const int K = 110, PREC = 4, L = K / PREC, BASE = 10000;

struct Int {
  int val[L];

  Int() { memset(val, 0, sizeof(val)); }

  void operator*=(int x) {
    for (int i = 0; i < L; ++i)
      val[i] *= x;
    for (int i = 0; i < L - 1; ++i) {
      val[i + 1] += val[i] / BASE;
      val[i] %= BASE;
    }
  }

  void otp() {
    bool vis = false;
    for (int i = L - 1; i >= 0; --i)
      if (vis)
        printf("%04d", val[i]);
      else if (val[i]) {
        printf("%d", val[i]);
        vis = true;
      }
    putchar('\n');
  }
} ans;

const int N = 55;
int pwr[N];

struct SchreierSims {
  int n, cnt;
  vector<Perm> transerval, generator;
  SchreierSims *sub;

  void init(int n) {
    SchreierSims::n = n;
    cnt = 1;
    transerval.resize(n);
    transerval.back() = id(n);
  }

  bool test(const Perm &p) {
    if (n == 1) return true;
    int pos = p.back();
    if (transerval[pos].empty()) return false;
    return sub->test(trunc(p * transerval[pos]));
  }

  void insertGenerator(const Perm &);

  void insertTranserval(const Perm &p) {
    if (n == 1) return;
    int pos = p.back();
    if (transerval[pos].empty()) {
      --pwr[cnt];
      ++pwr[++cnt];
      transerval[pos] = inv(p);
      for (int i = 0; i < generator.size(); ++i)
        insertTranserval(p * generator[i]);
    } else {
      sub->insertGenerator(trunc(p * transerval[pos]));
    }
  }
};

void SchreierSims::insertGenerator(const Perm &p) {
  if (!test(p)) {
    generator.push_back(p);
    for (int i = 0; i < n; ++i)
      if (!transerval[i].empty())
        insertTranserval(inv(transerval[i]) * p);
  }
}


SchreierSims chain[N];

int main() {
#ifdef ELEGIA
  freopen("test.in", "r", stdin);
  int nol_cl = clock();
#endif
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;
  ans.val[0] = 1;
  for (int i = 1; i <= n; ++i) {
    chain[i].init(i);
    if (i > 1) chain[i].sub = &chain[i - 1];
  }
  while (m--) {
    Perm ins(n);
    cin >> ins;
    for (int &x : ins) --x;
    chain[n].insertGenerator(ins);
  }
  for (int i = 2; i <= n; ++i)
    while (pwr[i]--)
      ans *= i;
  ans.otp();

#ifdef ELEGIA
  LOG("Time: %dms\n", int ((clock()
          -nol_cl) / (double)CLOCKS_PER_SEC * 1000));
#endif
  return 0;
}

