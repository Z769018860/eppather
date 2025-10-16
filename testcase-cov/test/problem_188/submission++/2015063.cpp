#include <cstdio>
#include <cstdlib>
#include <iostream>
using std::cin, std::cout, std::endl;
int read()
{
    int f = 1, x = 0;
    char ch;
    do {
        ch = getchar();
        if (ch == '-')
            f = -1;
    } while (ch < '0' || ch > '9');
    do {
        x = x * 10 + ch - '0';
        ch = getchar();
    } while (ch >= '0' && ch <= '9');
    return f * x;
}
const int N = 1e5;

int n, m;
struct Heap {
    int rt[N + 1];
    struct Node {
        int val, ls, rs, fa, dis, del;
    } node[N + 1];
    void init()
    {
        for (int i = 1; i <= n; i++)
            rt[i] = i;
        return;
    }
    int findrt(int x)
    {
        if (rt[x] != x)
            rt[x] = findrt(rt[x]);
        return rt[x];
    }
    int merge(int x, int y)
    {
        if (!x || !y)
            return x + y;
        if (node[x].val > node[y].val)
            std::swap(x, y);
        node[x].rs = merge(node[x].rs, y);
        if (node[x].rs)
            node[node[x].rs].fa = x;
        if (node[node[x].ls].dis < node[node[x].rs].dis)
            std::swap(node[x].ls, node[x].rs);
        node[x].dis = node[node[x].rs].dis + 1;
        return x;
    }
    void merge_at(int x, int y)
    {
        if (node[x].del || node[y].del)
            return;
        x = findrt(x);
        y = findrt(y);
        if (x == y)
            return;
        int root = merge(x, y);
        rt[x] = rt[y] = root;
        return;
    }
    void pushup(int x)
    {
        if (!x)
            return;
        if (node[x].dis != node[node[x].rs].dis + 1) {
            node[x].dis = node[node[x].rs].dis + 1;
            pushup(node[x].fa);
        }
        return;
    }
    void del(int x)
    {
        node[x].del = 1;
        int root = merge(node[x].ls, node[x].rs);
        rt[x] = rt[node[x].ls] = rt[node[x].rs] = root;
        if (node[node[x].fa].ls == x)
            node[node[x].fa].ls = root;
        else
            node[node[x].fa].rs = root;
        node[root].fa = node[x].fa;
        pushup(node[root].fa);
        return;
    }
    int top(int x)
    {
        x = findrt(x);
        return node[x].val;
    }
} heap;

int main()
{
    n = read();
    m = read();
    heap.init();
    for (int i = 1; i <= n; i++)
        heap.node[i].val = read();

    for (int i = 1; i <= m; i++) {
        int opt = read();
        if (opt == 1) {
            int x = read(), y = read();
            heap.merge_at(x, y);
        } else {
            int x = read();
            if (heap.node[x].del) {
                printf("-1\n");
                continue;
            }
            printf("%d\n", heap.top(heap.findrt(x)));
            heap.del(heap.findrt(x));
        }
    }

    return 0;
}
