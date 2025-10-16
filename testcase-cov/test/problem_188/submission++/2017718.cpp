
#include <stdio.h>
#include <algorithm>
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
    putchar((x % 10) ^ '0');
}
const int N = 100010;
const i64 offset = 1ll << 31;
namespace seg_tree_forest_compress
{
    
    int log_interval; 

    struct node
    {
        int ch[2]; 
        i64 l, r;  
        int sum;   
    } tr[N << 1];
    int rt[N];                
    int cnt;                  
    int recycle[N << 1], top; 

    
    
    
    std::pair<i64, i64> lca(i64 u, i64 v)
    {
        if (u == v)
            return std::make_pair(u, u);
        int log_len = 64 - __builtin_clzll(u ^ v);
        i64 len = 1ll << log_len;
        i64 l = (u >> log_len) << log_len;
        return std::make_pair(l, l | (len - 1));
    }

    void clear(int u) { tr[u].sum = tr[u].ch[0] = tr[u].ch[1] = tr[u].l = tr[u].r = 0; }
    
    void recycle_node(int u) { recycle[++top] = u; }

    int new_node()
    {
        int ret = top ? recycle[top--] : ++cnt;
        return clear(ret), ret;
    }
    
    
    void init(int _lg_interval, int n)
    {
        log_interval = _lg_interval;
        cnt = top = 0;
        for (int i = 1; i <= n; ++i)
            rt[i] = new_node(), tr[rt[i]].l = 0, tr[rt[i]].r = (1ll << log_interval) - 1;
    }

    void pushup(int u) { tr[u].sum = tr[tr[u].ch[0]].sum + tr[tr[u].ch[1]].sum; }

    
    
    
    
    bool handle(int u, int son, i64 pos, int val)
    {
        bool ret = true;
        
        if (!tr[u].ch[son])
        {
            int v = new_node();
            tr[u].ch[son] = v; 
            tr[v].sum += val;  
            tr[v].l = tr[v].r = pos;
            pushup(u);
        }
        
        else if (tr[tr[u].ch[son]].l == tr[tr[u].ch[son]].r)
        {
            
            if (tr[tr[u].ch[son]].l == pos)
                tr[tr[u].ch[son]].sum += val, pushup(u);
            
            else
            {
                std::pair<i64, i64> _lca = lca(pos, tr[tr[u].ch[son]].l);

                int f = new_node();
                tr[f].l = _lca.first, tr[f].r = _lca.second;

                int v = new_node();
                tr[v].sum += val, tr[v].l = tr[v].r = pos;

                
                tr[f].ch[0] = pos < tr[tr[u].ch[son]].l ? v : tr[u].ch[son];
                tr[f].ch[1] = (v ^ tr[u].ch[son]) ^ tr[f].ch[0];
                tr[u].ch[son] = f;

                pushup(f), pushup(u);
            }
        }
        
        else if (pos < tr[tr[u].ch[son]].l || pos > tr[tr[u].ch[son]].r)
        {
            std::pair<i64, i64> _lca = lca(pos, tr[tr[u].ch[son]].l);
            
            int f = new_node();
            tr[f].l = _lca.first, tr[f].r = _lca.second;

            int v = new_node();
            tr[v].sum += val, tr[v].l = tr[v].r = pos;

            
            tr[f].ch[0] = pos < tr[tr[u].ch[son]].l ? v : tr[u].ch[son];
            tr[f].ch[1] = (v ^ tr[u].ch[son]) ^ tr[f].ch[0];
            tr[u].ch[son] = f;

            pushup(f), pushup(u);
        }
        
        else
            ret = false; 
        return ret;
    }

    void _add(int u, i64 pos, int val)
    {
        i64 m = (tr[u].l + tr[u].r) >> 1;
        if (pos <= m)
        {
            bool ret = handle(u, 0, pos, val);
            if (!ret)
                _add(tr[u].ch[0], pos, val), pushup(u);
        }
        else
        {
            bool ret = handle(u, 1, pos, val);
            if (!ret)
                _add(tr[u].ch[1], pos, val), pushup(u);
        }
    }
    void add(int i, i64 pos, int val) { _add(rt[i], pos, val); }

    int _query_sum(int u, i64 l, i64 r)
    {
        if (!u)
            return 0;
        i64 L = tr[u].l, R = tr[u].r;
        if (L > r || R < l)
            return 0;
        if (l <= L && R <= r)
            return tr[u].sum;
        return _query_sum(tr[u].ch[0], l, r) + _query_sum(tr[u].ch[1], l, r);
    }
    int query_sum(int i, i64 l, i64 r) { return (l > r) ? 0 : _query_sum(rt[i], l, r); }

    i64 _find_kth(int u, int rk)
    {
        if (tr[u].l == tr[u].r)
            return tr[u].l;
        if (tr[tr[u].ch[0]].sum >= rk)
            return _find_kth(tr[u].ch[0], rk);
        else
            return _find_kth(tr[u].ch[1], rk - tr[tr[u].ch[0]].sum);
    }
    i64 find_kth(int i, int rk) { return _find_kth(rt[i], rk); }

    int sz(int i) { return tr[rt[i]].sum; }

    int _merge(int a, int b)
    {
        if (!a || !b)
            return a | b;
        
        if (tr[a].r - tr[a].l + 1 < tr[b].r - tr[b].l + 1)
            std::swap(a, b);
        
        if (tr[a].l == tr[b].l && tr[a].r == tr[b].r)
        {
            
            if (tr[a].l == tr[a].r)
            {
                tr[a].sum += tr[b].sum, recycle_node(b);
                return a;
            }
            
            else
            {
                int ls = tr[b].ch[0], rs = tr[b].ch[1];
                recycle_node(b); 
                tr[a].ch[0] = _merge(tr[a].ch[0], ls);
                tr[a].ch[1] = _merge(tr[a].ch[1], rs);
                pushup(a);
                return a;
            }
        }
        
        else if (tr[a].l <= tr[b].l && tr[b].r <= tr[a].r)
        {
            i64 m = (tr[a].l + tr[a].r) >> 1;
            if (tr[b].r <= m)
                tr[a].ch[0] = _merge(tr[a].ch[0], b);
            else
                tr[a].ch[1] = _merge(tr[a].ch[1], b);
            std::pair<i64, i64> _lca = lca(tr[tr[a].ch[0]].l, tr[tr[a].ch[1]].l);
            tr[a].l = _lca.first, tr[a].r = _lca.second;
            pushup(a);
            return a;
        }
        
        else
        {
            
            if (tr[a].l > tr[b].l)
                std::swap(a, b);
            int f = new_node();
            std::pair<i64, i64> _lca = lca(tr[a].l, tr[b].l);
            tr[f].l = _lca.first, tr[f].r = _lca.second;
            tr[f].ch[0] = a, tr[f].ch[1] = b;
            pushup(f);
            return f;
        }
    }
    
    void merge(int u, int f) { rt[f] = _merge(rt[f], rt[u]); }
}
namespace union_find
{
    int f[N];
    void init(int n)
    {
        for (int i = 1; i <= n; ++i)
            f[i] = i;
    }
    int getf(int x) { return f[x] = (f[x] == x) ? x : getf(f[x]); }
    void setf(int u, int fa) { f[u] = fa; }
}
bool exist[N];
int main()
{
    int n = rd(), m = rd();
    i64 x = 0;
    seg_tree_forest_compress::init(49, n);
    union_find::init(n);
    for (int i = 1; i <= n; ++i)
        x = rd(), seg_tree_forest_compress::add(i, ((x + offset) << 17) | i, 1), exist[i] = 1;
    while (m--)
    {
        int op = rd(), u = rd(), v = 0;
        if (op & 1)
        {
            v = rd();
            if (!exist[u] || !exist[v])
                continue;
            int fu = union_find::getf(u), fv = union_find::getf(v);
            if (fu ^ fv)
                union_find::setf(fu, fv), seg_tree_forest_compress::merge(fu, fv);
        }
        else
        {
            if (!exist[u])
                wr(-1);
            else
            {
                int fu = union_find::getf(u);
                i64 ans = seg_tree_forest_compress::find_kth(fu, 1);
                wr((ans >> 17) - offset);
                seg_tree_forest_compress::add(fu, ans, -1);
                exist[ans & ((1 << 17) - 1)] = 0;
            }
            putchar('\n');
        }
    }
}