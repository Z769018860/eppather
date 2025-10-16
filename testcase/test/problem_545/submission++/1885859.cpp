#include <bits/stdc++.h>
namespace IO {
#define iL (1 << 20)
char ibuf[iL], *iS = ibuf + iL, *iT = ibuf + iL;
#define gc() ((iS == iT) ? (iT = (iS = ibuf) + fread(ibuf, 1, iL, stdin), iS == iT ? EOF : *iS ++) : *iS ++)
template<class T> inline void read(T &x) {
  x = 0;int f = 0;char ch = gc();
  for (; !isdigit(ch); f |= ch == '-', ch = gc());
  for (; isdigit(ch); x = (x << 1) + (x << 3) + (ch ^ 48), ch = gc());
  x = (f == 1 ? ~ x + 1 : x);
}
template<class T, class... Args> inline void read(T &x, Args&... args) { read(x), read(args...); }
template<class T> inline void readch(T &x) { char ch = gc(); for (; !isalpha(ch); ch = gc()); x = ch; }
char Out[iL], *iter = Out;
#define flush() fwrite(Out, 1, iter - Out, stdout), iter = Out
template<class T> inline void write(T x, char ch = '\n') {
  T l, c[35];
  if (x < 0) *iter ++ = '-', x = ~ x + 1;
  for (l = 0; !l || x; c[l] = x % 10, l++, x /= 10);
  for (; l; -- l, *iter ++ = c[l] + '0');*iter ++ = ch;
  flush();
}
template<class T, class... Args> inline void write(T x, Args... args) { write(x, ' '), write(args...); }
} 
using namespace IO;
#define N 1200005
#define int ll 
#define ll long long
#define DEBUG
#define pii pair<int, int>
#define mp make_pair
#define fi first
#define se second
#define vi vector<int>
#define MOD 998244353
#define pb emplace_back
#define il inline
using namespace std;
inline int pls(int x, int y) { return x + y >= MOD ? x + y - MOD : x + y; }
inline int sub(int x, int y) { return x - y < 0 ? x - y + MOD : x - y; }
inline int prd(int x, int y) { return (1ll * x * y % MOD); }

int n, a[N], m, b[N], K;
int bucu[55], bucv[55], buc[55];

#define bit 31
il int low(int x) { return (x & -x); }
il int size(int x) { return __builtin_ctz(low(x)) + 1; }

namespace mf {
  #define iN 105
  #define iM 1000005
  
  struct edge { int x, y, c, w; }e[iM];
  int S, T, cnt = 1, head[iN], cur[iN], nxt[iM];

  il void ins(int x, int y, int c, int w) {
    e[++ cnt] = (edge){x, y, c, w}, nxt[cnt] = head[x], head[x] = cnt;
  }
  il void add(int x, int y, int c, int w) {
    ins(x, y, c, w), ins(y, x, 0, -w);
  }

  int inq[N]; ll dis[N];
  bool spfa() {
    for (int i = 1; i <= T; i++) 
      dis[i] = 1e18, inq[i] = 0, cur[i] = head[i];
    dis[S] = 0, inq[S] = 1; 
    queue<int> q; q.push(S);
    while (!q.empty()) {
      int x = q.front(); q.pop(); inq[x] = 0;
      for (int i = head[x]; i; i = nxt[i]) {
        int y = e[i].y;
        if (e[i].c > 0 && dis[y] > dis[x] + e[i].w) {
          dis[y] = dis[x] + e[i].w;
          if (!inq[y]) inq[y] = 1, q.push(y);
        }
      }
    }
    return (dis[T] < 0);
  }
  int dfs(int x, int flow, ll& wgh) {
    if (x == T || !flow) {
      wgh += 1ll * dis[x] * flow;
      
      return flow;
    }
    int res = 0; inq[x] = 1;
    for (int &i = cur[x]; i; i = nxt[i]) {
      int y = e[i].y;
      if (e[i].c > 0 && dis[y] == dis[x] + e[i].w && !inq[y]) {
        int temp = dfs(y, min(flow, e[i].c), wgh);
        e[i].c -= temp, e[i ^ 1].c += temp;
        flow -= temp, res += temp;
        if (!flow) break;
      }
    }
    if (!res) dis[x] = 1e18;
    inq[x] = 0; return res;
  }

  ll mcmf() {
    ll res = 0;
    while (spfa()) { ll re = 0; dfs(S, 1e9, re); res += re; }
    return res;
  }
}

signed main() {
#ifndef ONLINE_JUDGE
  freopen("test.in", "r", stdin); freopen("test.out", "w", stdout);
#endif
  read(n);
  for (int i = 1; i <= n; i++) read(a[i]), bucu[size(a[i])] ++;
  read(m);
  for (int i = 1; i <= m; i++) read(b[i]), bucv[size(b[i])] ++;
  read(K);

  sort(a + 1, a + 1 + n), sort(b + 1, b + 1 + m);
  for (int i = 1, j = 1; i <= n; i++) {
    while (j <= m && b[j] < a[i]) j ++; if (j > m) break;
    if (a[i] == b[j]) buc[size(a[i])] ++, j ++;
  }

  
  

  mf::S = bit * 2 + 1, mf::T = bit * 2 + 3;
  mf::add(mf::S, mf::S + 1, K, 0);
  
  for (int i = 1; i <= bit; i++) {
    mf::add(mf::S + 1, i, bucu[i], -(1 << i - 1));
    mf::add(i + bit, mf::T, bucv[i], (1 << i - 1));
    mf::add(i, i + bit, buc[i], -(1 << i - 1));
    for (int j = 1; j < i; j++) 
      mf::add(i, j + bit, 1e9, 0);
  }
  

  ll ans = 0;
  for (int i = 1; i <= n; i++) ans += low(a[i]);
  write(ans + mf::mcmf());
  return 0;
}
