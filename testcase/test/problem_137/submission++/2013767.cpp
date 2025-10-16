#include <stdio.h>
#include <vector>
#include <stack>
#include <algorithm>
#include <functional>
#define fread fread_unlocked
#define fwrite fwrite_unlocked
namespace FastIO
{
    const int BUFF_SZ = 1 << 20;
    char buf[BUFF_SZ], *p1 = buf, *p2 = buf;
    inline char nc() { return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, BUFF_SZ, stdin), p1 == p2) ? EOF : *p1++; }
    int rd()
    {
        int ret = 0, f = 1;
        char ch = nc();

        while (ch < '0' || ch > '9')
        {
            if (ch == '-')
                f = -1;
            ch = nc();
        }
        while (ch >= '0' && ch <= '9')
        {
            ret = (ret << 1) + (ret << 3) + (ch ^ 48);
            ch = nc();
        }

        return f == 1 ? ret : -ret;
    }
    char Buf[BUFF_SZ], out[20];
    int P, out_size;
    void flush() { Buf[out_size] = '\0', fwrite(Buf, 1, out_size, stdout), out_size = 0; }
    void wr(int x, char ch = '\n')
    {
        if (out_size >= (BUFF_SZ >> 1))
            flush();

        if (x < 0)
            Buf[out_size++] = 45, x = -x;

        do
            out[++P] = (x % 10) ^ 48;
        while (x /= 10);

        do
            Buf[out_size++] = out[P];
        while (--P);
        Buf[out_size++] = ch;
    }
    struct IOFlush
    {
        ~IOFlush() { flush(); }
    } tail;
}
struct union_find
{
    int n;
    std::vector<int> f;
    union_find(int _n = 0) : n(_n)
    {
        f.resize(n + 1);
        for (int i = 1; i <= n; ++i)
            f[i] = i;
    }
    int getf(int x) { return f[x] == x ? x : f[x] = getf(f[x]); }
    bool check(int x, int y)
    {
        int a = getf(x), b = getf(y);
        return a == b;
    }
    
    void merge(int x, int y)
    {
        int a = getf(x), b = getf(y);
        if (a == b)
            return;
        f[a] = b;
    }
    bool is_root(int x) { return x == f[x]; }
};


struct graph_list
{
    std::vector<int> to, nxt, head;
    int cnt;
    graph_list() = default;
    graph_list(int n, int m)
    {
        to.resize(m + 1), nxt.resize(m + 1);
        head.resize(n + 1), cnt = 0;
    }
    void add_edge(int u, int v) { to[++cnt] = v, nxt[cnt] = head[u], head[u] = cnt; }
};
struct edge
{
    int u, v, w;
    bool operator<(const edge &o) const { return w < o.w; }
};

template <typename T>
struct rmq
{
    static const int b = 4, all_mask = 65535, B = 16;
    int n; 
    std::vector<T> a; 
    std::vector<std::vector<int>> st; 
    std::vector<int> masks; 

    
    bool f(const T& a, const T& b) { return a < b; } 
    int op(int x, int y) { return f(a[x], a[y]) ? x : (a[x] == a[y]) ? std::min(x, y) : y; }
    
    int lsb(int x) { return x & (-x); }
    int msb_index(int x) { return 31 ^ __builtin_clz(x); }

    rmq(int _n = 0) : n(_n), a(n), masks(n) {}

    void build()
    {
        if (!n)
            return;
        int lim = n >> b;
        
        int cur_mask = 0;
        for (int i = 0; i < n; ++i)
        {
            
            cur_mask = (cur_mask << 1) & all_mask;
            while (cur_mask > 0 && op(i, i - msb_index(lsb(cur_mask))) == i)
                cur_mask ^= lsb(cur_mask);
            cur_mask |= 1;
            masks[i] = cur_mask;
        }
        
        st.resize(lim ? 32 - __builtin_clz(lim) : 1);
        st[0].resize(lim);
        for (int i = 0; i < lim; ++i)
            st[0][i] = query_small(i << b, (i << b) | (B - 1));    
        for (int k = 1, pw = 1; (pw << 1) <= lim; pw <<= 1, ++k)
        {
            st[k].resize(lim - (pw << 1) + 1);
            for (size_t j = 0; j < st[k].size(); ++j)
                st[k][j] = op(st[k - 1][j], st[k - 1][j + pw]);
        }
    }
    
    int query_small(int l, int r)
    {
        int dist_from_r = msb_index(masks[r] & ((1 << (r - l + 1)) - 1));
        return r - dist_from_r;
    }

    
    int query(int l, int r)
    {
        if (r - l + 1 <= B)
            return query_small(l, r);
        int ret = op(query_small(l, l + B - 1), query_small(r - B + 1, r));
        int belong_l = (l >> b) + 1, belong_r = (r >> b);
        if (belong_l < belong_r)
        {
            int dep = msb_index(belong_r - belong_l);
            ret = op(ret, op(st[dep][belong_l], st[dep][belong_r - (1 << dep)]));
        }
        return ret;
    }
};


struct static_lca
{
    rmq<int> min_query;
    std::vector<int> dfn, rev_dfn;
    std::vector<int> dfn_f;
    std::vector<int> f;
    std::vector<int> dp;
    int t;

    std::vector<int> dep, sz;

    void build_dp(int n)
    {
        min_query = rmq<int>(n);
        dp.resize(n + 1);
        for (int u = n; u; --u)
        {
            int f = dfn_f[u];
            dp[f] += dp[u] + 1;
        }
        for (int u = 2; u <= n; ++u)
        {
            int f = dfn_f[u];
            int tmp = dp[f] - dp[u] - 1;
            dp[u] = dp[f], dp[f] = tmp;
        }
        for (int u = 2; u <= n; ++u)
            min_query.a[dp[u]] = dfn_f[u];
        min_query.build();
    }
    

    static_lca() = default;

    static_lca(int n, int rt, const graph_list& g) : t(0)
    {
        std::vector<bool> vis(n + 1);
        std::stack<int> s;
        f.resize(n + 1);
        dfn.resize(n + 1), rev_dfn.resize(n + 1);  
        dep.resize(n + 1), sz.resize(n + 1);

        s.push(rt), dep[rt] = 1;
        while (s.size())
        {
            int u = s.top();
            s.pop();
            vis[u] = 1, sz[u] = 1, dfn[u] = ++t, rev_dfn[t] = u;
            for (int i = g.head[u]; i; i = g.nxt[i])
            {
                int v = g.to[i];
                if (!vis[v])
                    f[v] = u, dep[v] = dep[u] + 1, s.push(v);
            }
        }
        dfn_f.resize(n + 1);
        for (int i = 1; i <= n; ++i)
            dfn_f[dfn[i]] = dfn[f[rev_dfn[dfn[i]]]];
        for (int i = n; i; --i)
            sz[f[rev_dfn[i]]] += sz[rev_dfn[i]];
        build_dp(n);
    }

    int lca(int u, int v)
    {
        if (!(u ^ v))
            return u;
        u = dfn[u], v = dfn[v];
        int x = dp[u], y = dp[v];
        if (x > y)
            std::swap(x, y);
        return rev_dfn[min_query.a[min_query.query(x + 1, y)]];
    }
};

struct kruskal_reconstruct_tree
{
    int real_sz;
    union_find uf;
    graph_list g;
    static_lca lca;
    std::vector<int> val;
    kruskal_reconstruct_tree() = default;
    kruskal_reconstruct_tree(int n, std::vector<edge>& e)
    {
        real_sz = n;
        uf = union_find(n << 1), g = graph_list(n << 1, ((n << 1) - 1) << 1);
        val.resize((n << 1) + 1);
        std::sort(e.begin(), e.end());
        int connect = 0;
        for (size_t i = 0; i < e.size(); ++i)
        {
            int fu = uf.getf(e[i].u), fv = uf.getf(e[i].v);
            if (fu ^ fv)
            {
                ++real_sz, ++connect;
                uf.merge(fu, real_sz), uf.merge(fv, real_sz);
                g.add_edge(fu, real_sz), g.add_edge(fv, real_sz);
                g.add_edge(real_sz, fu), g.add_edge(real_sz, fv);
                val[real_sz] = e[i].w;
            }
            if (connect == n - 1)
                break;
        }
        real_sz++, val[real_sz] = -1;
        for (int i = 1; i < real_sz; ++i)
            if (uf.is_root(i))
                uf.merge(i, real_sz), g.add_edge(i, real_sz), g.add_edge(real_sz, i);
        lca = static_lca(real_sz, real_sz, g);
    }
    int bottleneck_road(int u, int v) { return val[lca.lca(u, v)]; }
};

namespace gen
{
    int A, B, C, P;
    inline int rnd() { return A = (A * B + C) % P; }
}

const int mod = 1000000007;
int trim(int x) {  return ((0 <= x) && (x < mod)) ? x : (x >= 0) ? (x % mod) : (mod - (((-x) % mod) ? ((-x) % mod) : mod)); }
int add(int a, int b) { return (a + b >= mod) ? (a + b - mod) : (a + b); }

int main()
{
    int n = FastIO::rd(), m = FastIO::rd();
    std::vector<edge> e(m);
    for (int i = 0; i < m; ++i)
        e[i].u = FastIO::rd(), e[i].v = FastIO::rd(), e[i].w = FastIO::rd();
    kruskal_reconstruct_tree sol(n, e);
    int q = FastIO::rd();
    gen::A = FastIO::rd(), gen::B = FastIO::rd(), gen::C = FastIO::rd(), gen::P = FastIO::rd();
    int ans = 0;
    while (q--)
    {
        int u = gen::rnd() % n + 1, v = gen::rnd() % n + 1;
        ans = add(ans, trim(sol.bottleneck_road(u, v)));
    }
    FastIO::wr(ans);
}