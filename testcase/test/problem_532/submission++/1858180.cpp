#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("avx2,fma")
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#define LL long long
#define int long long
#define pii pair<int, int>
#define ULL unsigned long long
#define mp(x, y) make_pair(x, y)
#define all(v) (v).begin(), (v).end()
using namespace std;
const int MAXN = 2e6 + 5;
const int Mod = 1e9 + 7;

template <typename T>
inline void read(T& x) {
  x = 0; int f = 1; char c = getchar(); while (c < '0' || c > '9') { if (c == '-') f = -f; c = getchar(); }
  while (c >= '0' && c <= '9') { x = (x << 3) + (x << 1) + (c ^ 48), c = getchar(); } x *= f;
}
template <typename T, typename... Args>
inline void read (T &x, Args&... Arg) { read (x), read (Arg...); }
template <typename T>
inline T Abs(T x) { return x < 0 ? -x : x; }
template <typename T>
inline T Max(T x, T y) { return x > y ? x : y; }
template <typename T>
inline T Min(T x, T y) { return x < y ? x : y; }

int n, ed;
LL A, B, C, l1, r1, l2, r2, res, a[MAXN], ind[MAXN], pre1[MAXN], pre2[MAXN], val1[MAXN], val2[MAXN];
bool vis[MAXN];



inline LL querypre(LL pos, LL val) { 
  if (pos <= ed) return 0;
  LL sum = 0;
  sum += (pos - ed) / (n - ed) % Mod;
  if (ind[val] - ed <= (pos - ed) % (n - ed)) sum++;
  return sum % Mod;
}
inline LL tot(LL l, LL r, LL val) {
  if (!ind[val]) return 0;
  if (!vis[val]) return l <= ind[val]; 
  return querypre(r, val) - querypre(l - 1, val);
}
inline LL findpos(double x, double k) {
  
  
  
  return Min(C, (LL)floor(x * (k + sqrt(k * k - 4)) / 2));
}

signed main() {

  read(A, B, C, a[0], l1, r1, l2, r2);
  for (n = 1; ; n++) {
    a[n] = (a[n - 1] * A + B) % C + 1;
    if (ind[a[n]]) break;
    ind[a[n]] = n;
  }
  ed = ind[a[n--]] - 1;

  
  
  
  

  
  
  for (int i = ed + 1; i <= n; i++) vis[a[i]] = 1;
  for (int i = 1; i <= C; i++) val1[i] = tot(l1, r1, i);
  for (int i = 1; i <= C; i++) pre1[i] = (pre1[i - 1] + val1[i]) % Mod;
  for (int i = 1; i <= C; i++) val2[i] = tot(l2, r2, i);
  for (int i = 1; i <= C; i++) pre2[i] = (pre2[i - 1] + val2[i]) % Mod;

  
  
  

  for (int i = 1; i <= C; i++) res = (res + val1[i] * val2[i] % Mod) % Mod;
  res = (res * 2ll) % Mod;

  for (int i = 1; i <= C; i++) {
    for (int k = 3; k <= C + 1; k++) {
      LL now = findpos(i, k), pre = findpos(i, k - 1);
      LL delta = 0;
      delta = (delta + (pre1[now] - pre1[pre] + Mod) % Mod * val2[i] % Mod) % Mod;
      delta = (delta + (pre2[now] - pre2[pre] + Mod) % Mod * val1[i] % Mod) % Mod;
      delta = (delta * k) % Mod;
      res = (res + delta) % Mod;
      
      
      if (now == C) break;
    }
  }
  printf("%lld\n", (res + Mod) % Mod);

  return 0;
}