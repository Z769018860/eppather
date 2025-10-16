#include <bits/stdc++.h>

using namespace std;

const int N = 1000005;
const int mod = 998244353;

typedef long long ll;

namespace BIT {
  int a[N];
  void add(int x, int val) {
    while (x < N) {
      a[x] += val;
      x += x & -x;
    }
  }
  int ask(int x) {
    int sum = 0;
    while (x) {
      sum += a[x];
      x -= x & -x;
    }
    return sum;
  }
}

int fac[N];

int main() {
  int n;
  scanf("%d", &n);
  fac[0] = 1;
  for (int i = 1; i <= n; i++) {
    fac[i] = 1ll * fac[i - 1] * i % mod;
  }
  int ans = 1;
  for (int i = 1; i <= n; i++) {
    int x;
    scanf("%d", &x);
    ans = (ans + 1ll * (x - 1 - BIT::ask(x - 1)) * fac[n - i]) % mod;
    BIT::add(x, 1);
  }
  printf("%d\n", ans);
}