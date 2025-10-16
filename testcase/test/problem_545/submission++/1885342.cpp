#include <bits/stdc++.h>
#define db double
#define il inline
#define re register
#define ll long long
#define ull unsigned ll
#define eb emplace_back
using namespace std;
namespace IO {
  #define iL (1 << 20)
  #define gc() iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, iL, stdin), iS == iT ? EOF : *iS++ : *iS++
  char ibuf[iL], *iS = ibuf + iL, *iT = ibuf + iL;
  template<class T> il void read(T &x) {
    char c = gc(); bool f = 0; x = 0;
    while(!isdigit(c)) {f |= c == '-'; c = gc();}
    while(isdigit(c)) {x = (x << 1) + (x << 3) + (c & 15); c = gc();}
    if(f) x = -x;
  }
  #undef iL
  #undef gc
}
using namespace IO;
#define N 1200005
#define M 35
struct Edge {int next, to, w, c;} E[N];
int k, S, T, cnt = 1, head[N];
il void add(int x, int y, int w, int c) {
  if(!w) return ;
  E[++cnt] = Edge {head[x], y, w, c}, head[x] = cnt;
  E[++cnt] = Edge {head[y], x, 0, -c}, head[y] = cnt;
}
int cur[N], dis[N]; bool vis[N]; ll maxf;
il bool bfs() {
  for(re int i = 0; i <= T; ++i) dis[i] = 1e9, cur[i] = head[i];
  queue<int> Q; Q.emplace(S), dis[S] = 0, vis[S] = 1;
  while(!Q.empty()) {
    int x = Q.front(); Q.pop(); vis[x] = 0;
    for(re int i = head[x]; i; i = E[i].next) {
      int y = E[i].to;
      if(E[i].w && dis[y] > dis[x] + E[i].c) {
        dis[y] = dis[x] + E[i].c;
        if(!vis[y]) Q.emplace(y), vis[y] = 1;
      }
    }
  }
  return dis[T] < 0;
}
il int dfs(int x, int flow) {
  if(x == T) return flow; int ans = 0; vis[x] = 1;
  for(re int i = cur[x]; i; i = E[i].next) {
    int y = E[i].to; cur[x] = i; if(vis[y]) continue;
    if(!E[i].w || dis[y] != dis[x] + E[i].c) continue;
    int w = dfs(y, min(flow, E[i].w));
    if(!w) {dis[y] = 1e9; continue;} ans += w, flow -= w;
    maxf += 1ll * w * E[i].c, E[i].w -= w, E[i ^ 1].w += w;
    if(!flow) break;
  }
  vis[x] = 0; return ans;
}
il int dinic() {
  int ans = 0, w;
  while(bfs()) while(w = dfs(S, k)) ans += w;
  return ans;
}
int n, m, in[M], out[M], v[M], L[M], R[M], a[N], b[N];
il int lowbit(int x) {return __builtin_ctz(x & -x);}
int main() {
  int _n, _m; read(_n); ll ans = 0;
  for(re int i = 1, x; i <= _n; ++i) {
    read(x); if(!x) continue;
    a[++n] = x, ++in[lowbit(x)], ans += x & -x;
  }
  read(_m);
  for(re int i = 1, x; i <= _m; ++i) {
    read(x); if(!x) continue;
    b[++m] = x, ++out[lowbit(x)];
  }
  read(k);
  sort(a + 1, a + 1 + n), sort(b + 1, b + 1 + m);
  for(re int i = 1, j = 1; i <= n; ++i) {
    while(j <= m && b[j] < a[i]) ++j; if(j > m) break;
    if(a[i] == b[j]) ++v[lowbit(a[i])], ++j;
  }
  for(re int i = 0; i < 30; ++i) {
    L[i] = ++T, R[i] = ++T;
    if(in[i] && out[i])
    add(L[i], R[i], v[i], -(1 << i));
    for(re int j = 0; j < i; ++j)
      if(in[i] && out[j])
      add(L[i], R[j], k, (1 << j) - (1 << i));
  }
  ++T, add(S, T, k, 0);
  for(re int i = 0; i < 30; ++i) add(T, L[i], in[i], 0), add(R[i], T + 1, out[i], 0);
  ++T, dinic(), cout << ans + maxf;
}