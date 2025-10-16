#include <stdio.h>
#define getchar getchar_unlocked
#define putchar putchar_unlocked
typedef long long i64;
i64 rd()
{
    i64 k = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9')
    {
        if (c == '-')
            f = 0;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        k = (k << 1) + (k << 3) + (c ^ 48);
        c = getchar();
    }
    return f ? k : -k;
}
void wr(i64 x)
{
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        wr(x / 10);
    putchar(x % 10 + '0');
}



int to[2000010], nxt[2000010], head[2000010];
int g_cnt;
void add_edge(int u, int v) { to[++g_cnt] = v, nxt[g_cnt] = head[u], head[u] = g_cnt; }

int N;
i64 bit_a[1000010];
void build()
{
    for (int i = 1; i <= N; ++i)
    {
        int f = i + (i & (-i));
        if (f <= N)
            bit_a[f] += bit_a[i];
    }
}
i64 _sum(int k)
{
    if (k <= 0)
        return 0;
    i64 ret = 0;
    for (; k; k -= (k & (-k)))
        ret += bit_a[k];
    return ret;
}
void add(int k, i64 x)
{
    for (; k <= N; k += (k & (-k)))
        bit_a[k] += x;
}
i64 sum(int l, int r) { return _sum(r) - _sum(l - 1); }


int a[1000010], dfn[1000010], sz[1000010];
int t;
void dfs (int u, int f)
{
    sz[u] = 1, dfn[u] = ++t, bit_a[t] = a[u];
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v ^ f)
            dfs(v, u), sz[u] += sz[v];
    }
}

int main()
{
    int n = rd(), q = rd(), rt = rd();
    
    
    
    N = n;

    for (int i = 1; i <= n; ++i)
        a[i] = rd();
    
    
    for (int i = 0; i < n - 1; ++i)
    {
        int u = rd(), v = rd();
        add_edge(u, v), add_edge(v, u);
    }

    
    dfs(rt, 0);
    build();
    while (q--)
    {
        int op = rd(), u = rd();
        if (op & 1)
            add(dfn[u], rd());
        else
            wr(sum(dfn[u], dfn[u] + sz[u] - 1)), putchar('\n');
    }
}