#pragma GCC optimize("Ofast", "unroll-loops", "-ffmath")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define rep(i, f, t, ...) for (int i = f, ##__VA_ARGS__; i <= t; ++i)
#define red(i, f, t, ...) for (int i = f, ##__VA_ARGS__; i >= t; --i)
#define N 8562699
#define emb emplace_back
#define pb push_back
#define pii pair<int, int>
#define pii pair<int, int>
#define mkp make_pair
#define arr3 array<int, 3>
#define arr4 array<int, 4>

bool Mst;

using i7 = char;
using i16 = int16_t;
using u32 = uint32_t;

ll n, m, S;
i7 mu[N];
i16 Smu[N];
int prime[N / 12], Smu2[N];
u32 tot = 0;
bitset<N> vis;

unordered_map<ll, ll> Mp;

ll clc1(ll n) {
  if (n <= S)
    return static_cast<ll>(Smu[n]);
  if (Mp[n])
    return Mp[n];
  ll res = 1, l = 2, r, d;
  while (l <= n)
    d = n / l, res -= ((r = (n / d)) - l + 1) * clc1(d), l = r + 1;
  return Mp[n] = res;
}

ll clc2(ll x) {
  if (x <= S)
    return (ll)Smu2[x];
  ll res = 0, i = 1;
  for (; i * i * i <= x; ++i)
    res += mu[i] * (x / (i * i));
  ll tmp = clc1(i - 1);
  for (ll j = x / (i * i); j >= 1; --j)
    res += (clc1(sqrt(x / j)) - tmp);
  return res;
}

bool Med;

signed main() {
  scanf ("%lld%lld", &n, &m);
  S = min({n, m, (ll)pow(max(n, m), 3. / 7.)});
  
  mu[1] = Smu[1] = Smu2[1] = 1;
  rep(i, 2, S) {
    if (!vis[i])
      mu[prime[++tot] = i] = -1;
    for (int j = 1, t; j <= tot && i * prime[j] <= S; ++j) {
      vis[t = i * prime[j]] = true;
      if (i % prime[j] == 0)
        break;
      mu[t] = -mu[i];
    }
    Smu[i] = Smu[i - 1] + mu[i];
    Smu2[i] = Smu2[i - 1] + mu[i] * mu[i];
  }
  ll ans = 0, lst = 0, R = min(n, m);
  for (ll l = 1, r, d1, d2, nowsm; l <= R; l = r + 1) {
    d1 = sqrt(n / l);
    d2 = sqrt(m / l);
    r = min(n / (d1 * d1), m / (d2 * d2));
    nowsm = clc2(r);
    ans += (nowsm - lst) * d1 * d2;
    lst = nowsm;
    
  }
  printf ("%lld\n", ans);
#ifdef MACOS
  cerr << "Memory & Time Information : " << endl;
  cerr << "Memory : " << ((&Med) - (&Mst)) * 1. / 1024. / 1024. << "MB" << endl;
  cerr << "Time : " << clock() * 1. / CLOCKS_PER_SEC * 1000. << "ms" << endl;
#endif
  return 0;
}