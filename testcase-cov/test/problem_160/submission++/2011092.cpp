#include <bits/stdc++.h>
using namespace std;
struct Edge
{
  int u, v, nxt;
} e[50001];
int head[50001], pos;
void addEdge(int u, int v)
{
  e[++pos] = {u, v, head[u]};
  head[u] = pos;
}
int n, W, d[50001], w[50001], v[50001], cnt[50001], dp2[60001], pool[65000005];
int &dp(int x, int y)
{
  return pool[x * (W + 1) + y];
}
void dfs(int u)
{
  dp(u, w[u]) = v[u];
  cnt[u] = w[u];

  for (int i = head[u]; i; i = e[i].nxt)
  {
    int v = e[i].v;

    dfs(v);
    memset(dp2, 0, sizeof dp2);

    for (int k = min(cnt[u], W); k >= w[u]; k--)
      for (int l = 0; l <= min(cnt[v], W - k); l++)
        dp2[k + l] = max(dp2[k + l], dp(u, k) + dp(v, l));

    for (int k = 0; k <= W; k++)
      dp(u, k) = dp2[k];

    cnt[u] += cnt[v];
  }
}
int read()
{
  int x = 0, f = 1;
  char ch = getchar();

  while (ch < '0' || ch > '9')
  {
    if (ch == '-')
      f = -1;

    ch = getchar();
  }

  while (ch >= '0' && ch <= '9')
  {
    x = (x << 1) + (x << 3) + (ch ^ 48);
    ch = getchar();
  }

  return x * f;
}
int main()
{
#ifndef ONLINE_JUDGE
  freopen("data/data1.in", "r", stdin);
  
#endif
  n = read(), W = read();

  for (int i = 1; i <= n; i++)
    addEdge(read(), i);

  for (int i = 1; i <= n; i++)
    w[i] = read();

  for (int i = 1; i <= n; i++)
    v[i] = read();

  dfs(0);

  cout << dp(0, W);
}