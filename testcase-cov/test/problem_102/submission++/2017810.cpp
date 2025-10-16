#include <iostream>

const int N = 1e5 + 2, INF = 0x3f3f3f3f;

int n, m, S, T, tot = 1;
int hd[N], to[N], nxt[N], f[N], w[N];
int q[N], d[N], incf[N], pre[N];
bool st[N];
void edge(int a, int b, int c, int d)
{
    to[ ++ tot] = b, nxt[tot] = hd[a], hd[a] = tot, f[tot] = c, w[tot] = d;
    to[ ++ tot] = a, nxt[tot] = hd[b], hd[b] = tot, w[tot] = -d;
}
bool spfa()
{
    int hh = 0, tt = 1;
    std::fill(d + 1, d + n + 1, INF);
    std::fill(incf + 1, incf + n + 1, 0);
    incf[S] = INF, d[S] = 0, q[0] = S;
    while (hh != tt)
    {
        int u = q[hh ++ ]; st[u] = 0;
        if (hh == N) hh = 0;
        for (int j = hd[u]; j; j = nxt[j])
        {
            if (f[j] && d[to[j]] > d[u] + w[j])
            {
                d[to[j]] = d[u] + w[j];
                pre[to[j]] = j;
                incf[to[j]] = std::min(f[j], incf[u]);
                if (!st[to[j]])
                {
                    st[to[j]] = 1, q[tt ++ ] = to[j];
                    if (tt == N) tt = 0;
                }
            }
        }
    }
    return incf[T] > 0;
}

void EK(int &flow, int &cost)
{
    flow = cost = 0;
    while (spfa())
    {
        int t = incf[T];
        flow += t, cost += t * d[T];
        for (int i = T; i != S; i = to[pre[i] ^ 1])
            f[pre[i]] -= t, f[pre[i] ^ 1] += t;
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    S = 1, T = n;
    for (int i = 1; i <= m; ++ i)
    {
        int a, b, c, d;
        scanf("%d%d%d%d", &a, &b, &c, &d);
        edge(a, b, c, d);
    }
    int flow, cost; EK(flow, cost);
    printf("%d %d\n", flow, cost);
    return 0;
}