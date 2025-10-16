
#include <stdio.h>
#include <string.h>
#include <algorithm>
#define getchar getchar_unlocked
#define putchar putchar_unlocked
int rd()
{
    int k = 0, f = 1;
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
void wr(int x)
{
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        wr(x / 10);
    putchar((x % 10) ^ '0');
}
namespace leftlist_heap
{
    const int N = 100010;
    struct key 
    {
        int val, id;
        bool operator< (const key& x) { return (val ^ x.val) ? val < x.val : id < x.id; }
    };
    struct node
    {
        
        int ch[2], fa, npl;
        
        key k;
    };
    node tr[N];
    int rt[N];                
    int cnt;                  
    int recycle[N], stk_top; 

    bool node_exist[N];

    void init(int n) { stk_top = cnt = 0, memset(rt, 0, (n + 1) << 2), memset(node_exist, 0, n + 1); }
    void clear(int u) { tr[u].ch[0] = tr[u].ch[1] = tr[u].fa = 0, tr[u].npl = 1; }
    void recycle_node(int u) { recycle[++stk_top] = u; }
    int new_node(int val, int id)
    {
        int ret = stk_top ? recycle[stk_top--] : ++cnt;
        return clear(ret), tr[ret].k.val = val, tr[ret].k.id = id, ret;
    }

    int _merge(int x, int y)
    {
        if (!x || !y)
            return x | y;
        if (tr[y].k < tr[x].k)
            std::swap(x, y);
        tr[x].ch[1] = _merge(tr[x].ch[1], y);
        tr[y].fa = x;

        if (tr[tr[x].ch[1]].npl > tr[tr[x].ch[0]].npl)
            std::swap(tr[x].ch[0], tr[x].ch[1]);
        tr[x].npl = tr[tr[x].ch[1]].npl + 1;
        return x;
    }
    
    void merge_heap(int u, int f) { rt[f] = _merge(rt[f], rt[u]); }
    void insert(int i, int val, int id) 
    { 
        rt[i] = _merge(rt[i], new_node(val, id)); 
        node_exist[id] = 1;
    }
    bool isemptyheap(int i) { return !rt[i]; }
    bool isexist(int id) { return node_exist[id]; }
    key top(int i) { return tr[rt[i]].k; }
    void pop(int i) 
    { 
        recycle_node(rt[i]);
        node_exist[tr[rt[i]].k.id] = 0;
        rt[i] = _merge(tr[rt[i]].ch[0], tr[rt[i]].ch[1]);
        tr[rt[i]].fa = 0;
    }
}
namespace union_find
{
    const int N = 100010;
    int f[N];
    void init(int n)
    {
        for (int i = 1; i <= n; ++i)
            f[i] = i;
    }
    void insert(int i) { f[i] = i; }
    int getf(int x) { return f[x] = (f[x] == x) ? x : getf(f[x]); }
    void setf(int u, int fa) { f[u] = fa; }
}
int main()
{
    int n = rd(), m = rd();
    for (int i = 1; i <= n; ++i)
        leftlist_heap::insert(i, rd(), i), union_find::insert(i);
    while (m--)
    {
        int op = rd(), x = rd(), y = 0;
        if (op & 1)
        {
            y = rd();
            if (!leftlist_heap::isexist(x) || !leftlist_heap::isexist(y))
                continue;
            int fx = union_find::getf(x), fy = union_find::getf(y);
            if (fx ^ fy)
                union_find::setf(fx, fy), leftlist_heap::merge_heap(fx, fy);
        }
        else
        {
            if (!leftlist_heap::isexist(x))
                wr(-1);
            else
            {
                int fx = union_find::getf(x);
                wr(leftlist_heap::top(fx).val);
                leftlist_heap::pop(fx);
            }
            putchar('\n');
        }
    }
}