#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 1100000;
const int q = 768906335;
const int r = 19190506;
const int mod = 998244353;
const int period = 917504;

int f[N], g[N], fac[N], ifac[N];

int add(int x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
  return x;
}

int mul(int x, int y) {
  return (ll)x * y % mod;
}

int power(int x, int y) {
  int result = 1;
  while (y) {
    if (y & 1) {
      result = mul(result, x);
    }
    x = mul(x, x);
    y >>= 1;
  }
  return result;
}

int binom(int n, int m) {
  return mul(fac[n], mul(ifac[m], ifac[n - m]));
}

int fact(int n, int m) {
  return mul(f[n], mul(g[m], g[n - m]));
}

int main() {
#ifdef wxh010910
  freopen("input.txt", "r", stdin);
#endif
  f[0] = g[0] = 1;
  for (int i = 1, coef = 1; i < period; ++i) {
    coef = mul(coef, q);
    f[i] = mul(f[i - 1], coef - 1);
    g[i] = mul(g[i - 1], power(coef - 1, mod - 2));
  }
  fac[0] = ifac[0] = fac[1] = ifac[1] = 1;
  int limit = (1000000000000ll + period - 1) / period;
  for (int i = 2; i <= limit; ++i) {
    fac[i] = mul(fac[i - 1], i);
    ifac[i] = mul(mod - mod / i, ifac[mod % i]);
  }
  for (int i = 2; i <= limit; ++i) {
    ifac[i] = mul(ifac[i - 1], ifac[i]);
  }
  int T;
  scanf("%d", &T);
  while (T--) {
    ll n, m;
    scanf("%lld %lld", &n, &m);
    if (n / period != m / period + (n - m) / period) {
      puts("0");
      continue;
    }
    int p = ((n - m) % period) * (m % period) % period;
    int answer = power(r, p);
    answer = mul(answer, binom(n / period, m / period));
    answer = mul(answer, fact(n % period, m % period));
    printf("%d\n", answer);
  }
  return 0;
}