#include <iostream>

const int N = 1e6 + 2, INF = 0x3f3f3f3f;

int n, m, S, T, tot = 1, max_flow = 0;
int hd[N], to[N << 1], nxt[N << 1], f[N << 1];
int out[N], dn[N];
int d[N], q[N], cur[N];

void edge(int u, int v, int w)
{
    to[ ++ tot] = v, nxt[tot] = hd[u], hd[u] = tot, f[tot] = w;
    to[ ++ tot] = u, nxt[tot] = hd[v], hd[v] = tot;
}

bool bfs()
{
    int hh = 1, tt = 0;
    std::fill(d, d + n + 2, -1);
    cur[S] = hd[S], q[ ++ tt] = S, d[S] = 0;
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
            int r = find(to[j], std::min(limit - flow, f[j]));
            if (!r) d[to[j]] = -1;
            f[j] -= r, f[j ^ 1] += r, flow += r;
        }
    }
    return flow;
}

int dinic()
{
    int res = 0, flow;
    while (bfs()) while ((flow = find(S, INF))) res += flow;
    return res;
}

int main()
{
    scanf("%d%d", &n, &m); T = n + 1;
    for (int i = 1; i <= m; ++ i)
    {
        int s, t, lower, upper;
        scanf("%d%d%d%d", &s, &t, &lower, &upper);
        edge(s, t, upper - lower);
        dn[i] = lower, out[s] -= lower, out[t] += lower;
    }
    for (int i = 1; i <= n; ++ i)
    {
        if (out[i] > 0) max_flow += out[i], edge(S, i, out[i]);
        else if (out[i] < 0) edge(i, T, -out[i]);
    }

    if (dinic() != max_flow) puts("NO");

    else 
    {
        puts("YES");

        for (int i = 1; i <= m; ++ i)
            printf("%d\n", f[2 * i + 1] + dn[i]);
    }
    return 0;
}