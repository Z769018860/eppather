#include <stdio.h>
#include <vector>
#include <stack>
#include <algorithm>
#include <functional>
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

struct graph_vector
{
    std::vector<int> e;
    std::vector<int> ptr, cnt;
    bool directed;
    graph_vector() = default;
    
    graph_vector(int n, const std::vector<std::pair<int, int>>& edges, bool _dir)
    {
        directed = _dir;
        int m = edges.size();
        e.resize(directed ? m : (m << 1));
        ptr.resize(n + 1), cnt.resize(n + 1);
        for (int i = 0; i < m; ++i)
            ++cnt[edges[i].first];
        if (!directed)
            for (int i = 0; i < m; ++i)
                ++cnt[edges[i].second];
        for (int i = 2; i <= n; ++i)
            ptr[i] = ptr[i - 1] + cnt[i - 1];
        std::fill(cnt.begin(), cnt.end(), 0);
        for (int i = 0; i < m; ++i)
        {
            int u = edges[i].first;
            e[ptr[u] + cnt[u]] = edges[i].second, ++cnt[u];
        }
        if (!directed)
            for (int i = 0; i < m; ++i)
            {
                int u = edges[i].second;
                e[ptr[u] + cnt[u]] = edges[i].first, ++cnt[u];
            }
    }
};

template<typename T>
struct BIT
{
    int N;
    std::vector<T> a;
    BIT() = default;
    void init(int sz) { N = sz, a.resize(N + 1); }
    BIT(int sz) { init(sz); }
    void build()
    {
        for (int i = 1; i <= N; ++i)
        {
            int f = i + (i & (-i));
            if (f <= N)
                a[f] += a[i];
        }
    }
    void add(int k, T x)
    {
        for (; k <= N; k += (k & (-k)))
            a[k] += x;
    }
    
    T sum(int k) const
    {
        if (k <= 0)
            return T();
        T ret = T();
        for (; k; k -= (k & (-k)))
            ret += a[k];
        return ret;
    }
    
    T sum(int l, int r) const { return sum(r) - sum(l - 1); }
};



int main()
{
    int n = rd(), q = rd(), rt = rd();

    std::vector<int> a(n + 1), dfn(n + 1), rev_dfn(n + 1), sz(n + 1);

    for (int i = 1; i <= n; ++i)
        a[i] = rd();

    std::vector<std::pair<int, int>> edges(n - 1);
    for (int i = 0; i < n - 1; ++i)
        edges[i].first = rd(), edges[i].second = rd();
    graph_vector g = graph_vector(n, edges, 0);

    
    BIT<i64> bit_1 = BIT<i64>(n + 1), bit_2 = BIT<i64>(n + 1);
    std::function<void(int, int)> bit_add = [&](int k, int x)
    {
        bit_1.add(k, x), bit_2.add(k, 1ll * k * x);
    };
    std::function<i64(int)> bit_sum = [&](int k)
    {
        return bit_1.sum(k) * (k + 1) - bit_2.sum(k);
    };

    
    std::vector<bool> vis(n + 1);
    std::stack<int> s;
    std::vector<int> f(n + 1);
    int t = 0;
    
    
    
    s.push(rt);
    while (s.size())
    {
        int u = s.top();
        s.pop();
        vis[u] = 1, sz[u] = 1;
        dfn[u] = ++t, rev_dfn[t] = u;
        bit_1.a[t] += a[u], bit_2.a[t] += 1ll * t * a[u];
        bit_1.a[t + 1] -= a[u], bit_2.a[t + 1] -= 1ll * (t + 1) * a[u];
        for (int i = g.ptr[u] + g.cnt[u] - 1; i >= g.ptr[u]; --i)
        {
            int v = g.e[i];
            if (!vis[v])
                f[v] = u, s.push(v);
        }
    }
    for (int i = t; i; --i)
        sz[f[rev_dfn[i]]] += sz[rev_dfn[i]];

    
    bit_1.build(), bit_2.build();
    while (q--)
    {
        int op = rd(), u = rd(), x = 0;
        if (op & 1)
            x = rd(), bit_add(dfn[u], x), bit_add(dfn[u] + sz[u], -x);
        else
            wr(bit_sum(dfn[u] + sz[u] - 1) - bit_sum(dfn[u] - 1)), putchar('\n');
    }
}
