

































































































































#include <iostream>

const int N = 5e3 + 2, INF = 0x3f3f3f3f;

int n, m, S, T;
int to[N << 1], nxt[N << 1], f[N << 1], hd[N], tot = 1;
int d[N], cur[N], q[N];

void edge(int u, int v, int w)
{
    to[ ++ tot] = v, nxt[tot] = hd[u], f[tot] = w, hd[u] = tot;
    to[ ++ tot] = u, nxt[tot] = hd[v], hd[v] = tot;
}

bool bfs()
{
    int hh = 0, tt = 0;
    std::fill(d + 1, d + n + 1, -1);
    d[S] = 0, q[0] = S, cur[S] = hd[S];
    while (hh <= tt)
    {
        int u = q[hh ++ ];
        for (int j = hd[u]; j; j = nxt[j])
        {
            if (d[to[j]] == -1 && f[j])
            {
                d[to[j]] = d[u] + 1;
                cur[to[j]] = hd[to[j]];
                if (to[j] == T) return true;
                q[ ++ tt] = to[j];
            }
        }
    }
    return false;
}

int find(int u, int limit)
{
    if (u == T) return limit;
    int flow = 0;
    for (int j = cur[u]; j && flow < limit; j = nxt[j])
    {
        cur[u] = j;
        if (d[to[j]] == d[u] + 1 && f[j])
        {
            int t = find(to[j], std::min(f[j], limit - flow));
            if (!t) d[to[j]] = -1;
            f[j] -= t, f[j ^ 1] += t, flow += t;
        }
    }
    return flow;
}

long long dinic()
{
    long long res = 0;
    int flow;
    while (bfs()) while ((flow = find(S, INF))) res += flow;
    return res;
}

int main()
{
    scanf("%d%d%d%d", &n, &m, &S, &T);
    for (int i = 1; i <= m; ++ i)
    {
        int u, v, c; scanf("%d%d%d", &u, &v, &c);
        edge(u, v, c);
    }
    printf("%lld\n", dinic());
    return 0;
}