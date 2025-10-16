#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define db double
#define ldb long double
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define FR first
#define SE second
#define int long long
using namespace std;
inline int read() {
  int x = 0; bool op = 0;
  char c = getchar();
  while(!isdigit(c))op |= (c == '-'), c = getchar();
  while(isdigit(c))x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
  return op ? -x : x;
}
const int N = 1.2e6 + 10;
const int INF = 1e16;
int n, m, k, S, T;
int a[N], b[N], ca[N], cb[N];
int etot = 1;
const int M = 1e5 + 10;
int dis[M], inc[M], pre[M], vis[M];
int head[M], to[M], nxt[M], flow[M], edge[M];
void addedge(int u, int v, int f, int w) {
  to[++etot] = v; flow[etot] = f; edge[etot] = w;
  nxt[etot] = head[u]; head[u] = etot;
  return ;
}
void add(int u, int v, int f, int w) {
  addedge(u, v, f, w); addedge(v, u, 0, -w);
  return ;
}
bool spfa() {
  queue<int> q; q.push(S); 
  for(int i = S; i <= T; i++)dis[i] = INF;
  vis[S] = true; dis[S] = 0; inc[S] = INF;
  while(q.empty() == false) {
    int u = q.front(); q.pop(); vis[u] = false;
    for(int i = head[u]; i; i = nxt[i]) {
      
      if(!flow[i])continue;
      int v = to[i], w = edge[i];
      if(dis[v] > dis[u] + w) {
        dis[v] = dis[u] + w;
        pre[v] = i; inc[v] = min(inc[u], flow[i]);
        if(!vis[v])q.push(v), vis[v] = true;
      }
    }
  }
  return dis[T] < INF;
}
int ans, cnt;
bool update() {
  
  if(dis[T] >= 0)return false;
  ans += dis[T] * inc[T];
  for(int i = T; i != S; i = to[pre[i] ^ 1]) {
    flow[pre[i]] -= inc[T];
    flow[pre[i] ^ 1] += inc[T];
  }
  return true;
} 
signed main() { 
  n = read();
  for(int i = 1; i <= n; i++)a[i] = read();
  m = read();
  for(int i = 1; i <= m; i++)b[i] = read();
  k = read();
  unordered_map<int, int> ba, bb;
  for(int i = 1; i <= n; i++)if(a[i]) {
    int t = __builtin_ctz(a[i]);
    ca[t]++; ba[a[i]]++;
  }
  for(int i = 1; i <= m; i++)if(b[i]) {
    int t = __builtin_ctz(b[i]);
    cb[t]++; bb[b[i]]++;
  }
  S = 0; int s = 61; T = 62; add(S, s, k, 0);
  for(int i = 1; i <= 30; i++) {
    add(s, i, ca[i - 1], -(1 << (i - 1)));
    add(i + 30, T, cb[i - 1], (1 << (i - 1)));
  }
  for(int i = 1; i <= 30; i++) {
    for(int j = 1; j < i; j++) {
      add(i, j + 30, INF, 0);
    }
  }
  int pc[60] = {0};
  for(auto t : ba)if(bb.count(t.FR)) {
    int v = __builtin_ctz(t.FR);
    pc[v + 1] += min(t.SE, bb[t.FR]);
    
  }
  for(int i = 1; i <= 30; i++)add(i, i + 30, pc[i], -(1 << (i - 1)));
  while(spfa())if(!update())break;
  
  for(int i = 1; i <= n; i++)ans += (a[i] & -a[i]);
  printf("%lld\n", ans);
  return 0;
}