#include <stdio.h>
#include <algorithm>
#define getchar getchar_unlocked
#define putchar putchar_unlocked
int rd()
{
    int k = 0;
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
    {
        k = (k << 1) + (k << 3) + (c ^ 48);
        c = getchar();
    }
    return k;
}
void wr(int x)
{
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        wr(x / 10);
    putchar((x % 10) ^ '0');
}
namespace dynamic_seg_tree_compress
{
    const int N = 1100010;
    int log_interval; 

    struct node
    {
        int ch[2]; 
        int l, r;  
        int sum;   
    } tr[N << 1];

    int cnt, rt;              
    int recycle[N << 1], top; 

    
    
    
    std::pair<int, int> lca(int u, int v)
    {
        if (u == v)
            return std::make_pair(u, u);
        int log_len = 32 - __builtin_clz(u ^ v);
        int len = 1 << log_len;
        int l = (u >> log_len) << log_len;
        return std::make_pair(l, l | (len - 1));
    }

    void clear(int u) { tr[u].sum = tr[u].ch[0] = tr[u].ch[1] = tr[u].l = tr[u].r = 0; }

    void remove_node(int u) { clear(u), recycle[++top] = u; }

    int new_node()
    {
        int ret = 0;
        if (top)
            ret = recycle[top--];
        else
            ret = ++cnt;
        return ret;
    }
    
    void init(int _lg_interval)
    {
        log_interval = _lg_interval;
        cnt = top = 0;
        rt = new_node();
        tr[rt].l = 0, tr[rt].r = (1 << log_interval) - 1;
    }

    void pushup(int u) { tr[u].sum = tr[tr[u].ch[0]].sum + tr[tr[u].ch[1]].sum; }

    
    
    
    
    bool handle(int u, int son, int pos, int val)
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
                std::pair<int, int> _lca = lca(pos, tr[tr[u].ch[son]].l);

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
            std::pair<int, int> _lca = lca(pos, tr[tr[u].ch[son]].l);
            
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

    void _add(int u, int pos, int val)
    {
        int m = (tr[u].l + tr[u].r) >> 1;
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
    void add(int pos, int val) { _add(rt, pos, val); }

    int _query_sum(int u, int l, int r)
    {
        if (!u)
            return 0;
        int L = tr[u].l, R = tr[u].r;
        if (L > r || R < l)
            return 0;
        if (l <= L && R <= r)
            return tr[u].sum;
        return _query_sum(tr[u].ch[0], l, r) + _query_sum(tr[u].ch[1], l, r);
    }
    int query_sum(int l, int r) { return (l > r) ? 0 : _query_sum(rt, l, r); }

    int find_kth(int u, int rk)
    {
        if (tr[u].l == tr[u].r)
            return tr[u].l;
        if (tr[tr[u].ch[0]].sum >= rk)
            return find_kth(tr[u].ch[0], rk);
        else
            return find_kth(tr[u].ch[1], rk - tr[tr[u].ch[0]].sum);
    }

    
    
    void insert(int val) { add(val, 1); }
    void remove(int val) { add(val, -1); }
    int get_rank(int val) { return query_sum(0, val - 1) + 1; }
    int kth(int rk) { return find_kth(rt, rk); }
    int min_element() { return kth(1); }
    int max_element() { return kth(tr[rt].sum); }
    
    int predecessor(int val) { return ((!tr[rt].sum) || val <= min_element()) ? -1 : kth(get_rank(val) - 1); }
    
    int successor(int val) { return ((!tr[rt].sum) || val >= max_element()) ? -1 : kth(get_rank(val + 1)); }
}
int main()
{
    dynamic_seg_tree_compress::init(30);
    
    int n = rd();
    int op = 0, x = 0;
    while (n--) 
    {
        op = rd(), x = rd();
        switch (op) 
        {
        case 0:
            dynamic_seg_tree_compress::insert(x);
            break;
        case 1:
            dynamic_seg_tree_compress::remove(x);
            break;
        case 3:
            wr(dynamic_seg_tree_compress::get_rank(x) - 1), putchar('\n');
            break;
        case 2:
            wr(dynamic_seg_tree_compress::kth(x)), putchar('\n');
            break;
        case 4:
            wr(dynamic_seg_tree_compress::predecessor(x)), putchar('\n');
            break;
        case 5:
            wr(dynamic_seg_tree_compress::successor(x)), putchar('\n');
            break;
        default:
            puts("Invalid Instruction."), n++;
            break;
        }
    }
}
