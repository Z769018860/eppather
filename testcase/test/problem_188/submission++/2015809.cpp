
#include <cstdio>
#include <cmath>
#include <algorithm>
#define getchar getchar_unlocked
#define putchar putchar_unlocked
using namespace std;
const int maxn = 100010;
inline void write(int x)
{
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + 48);
}
inline int read()
{
    int k = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9')
    {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        k = (k << 1) + (k << 3) + c - 48;
        c = getchar();
    }
    return k * f;
}

struct FibNode
{
    int key, degree;   
    int left, right;   
    int fa, child, id; 
    bool marked;       
    FibNode()
    {
        key = degree = left = right = 0;
        fa = child = 0;
        marked = false;
    }
} nodes[maxn];
struct FibHeap
{
    int min, size; 
    FibHeap()
    {
        size = min = 0;
    }
} heaps[maxn];
int cons[25]; 

inline void remove(int x)
{
    nodes[nodes[x].left].right = nodes[x].right;
    nodes[nodes[x].right].left = nodes[x].left;
}

inline void add(int x, int y)
{
    nodes[x].left = nodes[y].left;
    nodes[nodes[y].left].right = x;
    nodes[x].right = y;
    nodes[y].left = x;
}

inline int new_node(int key, int id)
{
    static int cnt = 0;
    nodes[++cnt].key = key, nodes[cnt].id = id;
    nodes[cnt].left = nodes[cnt].right = cnt;
    return cnt;
}

inline void _insert(FibHeap &heap, int x)
{
    if (heap.size == 0)
        heap.min = x;
    else
    {
        add(x, heap.min); 
        nodes[x].fa = 0;
        
        if (nodes[x].key < nodes[heap.min].key)
            heap.min = x;
    }
    ++heap.size;
}

inline void insert(FibHeap &heap, int key, int id)
{
    _insert(heap, new_node(key, id));
}

inline void connect(int x, int y)
{
    int z = nodes[x].right;
    nodes[x].right = nodes[y].right;
    nodes[nodes[y].right].left = x;
    nodes[y].right = z;
    nodes[z].left = y;
}

FibHeap merge(FibHeap &H1, FibHeap H2)
{
    if (H1.size == 0)
        return H1 = H2;
    if (H2.size == 0)
        return H1;
    
    
    if (H1.min == 0)
        H1.min = H2.min, H1.size = H2.size;
    else if (H1.min && H2.min)
    {
        connect(H1.min, H2.min);
        if (nodes[H1.min].key > nodes[H2.min].key)
            H1.min = H2.min;
        else if (nodes[H1.min].key == nodes[H2.min].key && nodes[H2.min].id <
                                                               nodes[H1.min].id)
            H1.min = H2.min;
        H1.size += H2.size;
    }
    return H1; 
}

inline int delete_min(FibHeap &heap)
{
    int x = heap.min;
    
    if (heap.min == nodes[x].right)
        heap.min = 0;
    else
        remove(x), heap.min = nodes[x].right;
    
    nodes[x].left = nodes[x].right = x;
    return x;
}

inline void link(FibHeap &heap, int x, int y)
{
    remove(x);
    if (nodes[y].child == 0)
        nodes[y].child = x;
    else
        add(x, nodes[y].child);
    nodes[x].fa = y;
    nodes[y].degree++;
    nodes[x].marked = false;
}

inline void adjust(FibHeap &heap)
{
    int deg, deg_lim, x = 0, y = 0;
    deg_lim = (int)log2(heap.size) + 1;
    
    while (heap.min)
    {
        x = delete_min(heap);
        deg = nodes[x].degree;
        
        while (cons[deg])
        {
            y = cons[deg];
            if (nodes[x].key > nodes[y].key)
                swap(x, y);
            else if (nodes[x].key == nodes[y].key && nodes[y].id < nodes[x].id)
                swap(x, y);
            link(heap, y, x); 
            cons[deg] = 0;
            deg++; 
        }
        cons[deg] = x;
        
    }
    heap.min = 0; 
    for (int i = 0; i < deg_lim; ++i)
    {
        if (cons[i])
        {
            if (heap.min == 0)
                heap.min = cons[i];
            else
            {
                add(cons[i], heap.min);
                if (nodes[cons[i]].key < nodes[heap.min].key)
                    heap.min = cons[i];
                else if (nodes[cons[i]].key == nodes[heap.min].key &&
                         nodes[cons[i]].id < nodes[heap.min].id)
                    heap.min = cons[i];
            }
            cons[i] = 0;
        }
    }
}

inline int pop(FibHeap &heap)
{
    int x = 0, z = heap.min;
    if (z)
    {
        while (nodes[z].child)
        {
            x = nodes[z].child;
            remove(x);
            if (nodes[x].right == x)
                nodes[z].child = 0;
            else
                nodes[z].child = nodes[x].right;
            add(x, z);
            nodes[x].fa = 0;
        }
        remove(z);
        if (nodes[z].right == z)
            heap.min = 0;
        else
            heap.min = nodes[z].right, adjust(heap);
        --heap.size;
    }
    return z;
}

void redegree(int fa, int degree)
{
    nodes[fa].degree -= degree;
    if (nodes[fa].fa)
        redegree(nodes[fa].fa, degree);
}

inline void cut(FibHeap &heap, int x, int y)
{
    remove(x), redegree(y, nodes[x].degree);
    if (x == nodes[x].right)
        nodes[y].child = 0;
    else
        nodes[y].child = nodes[x].right;
    nodes[x].left = nodes[y].left = x;
    nodes[x].fa = 0;
    nodes[x].marked = false;
    add(x, heap.min);
}

void cascading_cut(FibHeap &heap, int y)
{
    int z = nodes[y].fa;
    if (z)
    {
        if (nodes[y].marked == 0)
            nodes[y].marked = true;
        else
            cut(heap, y, z), cascading_cut(heap, z);
    }
}

inline void decrease(FibHeap &heap, int x, int key)
{
    int y = nodes[x].fa;
    nodes[x].key = key;
    if (y && nodes[x].key < nodes[y].key)
        cut(heap, x, y), cascading_cut(heap, y);
    if (nodes[x].key < nodes[heap.min].key)
        heap.min = x;
}

inline void delete_node(FibHeap &heap, int x)
{
    decrease(heap, 1, -(1 << 30));
    adjust(heap);
}
int n, m;
int op, x, y;
int a[maxn], fa[maxn];
bool isdelete[maxn];
inline int getf(int x)
{
    return x == fa[x] ? x : fa[x] = getf(fa[x]);
}
int main()
{
    n = read(), m = read();
    for (int i = 1; i <= n; ++i)
    {
        a[i] = read();
        insert(heaps[i], a[i], i);
        fa[i] = i;
    }
    while (m--)
    {
        op = read();
        if (op == 1)
        {
            x = read(), y = read();
            if (isdelete[x] || isdelete[y])
                continue;
            int fx = getf(x), fy = getf(y);
            if (fx == fy)
                continue;
            merge(heaps[fx], heaps[fy]);
            fa[fy] = fx;
            adjust(heaps[fx]);
        }
        else
        {
            x = read();
            if (isdelete[x])
                puts("-1");
            else
            {
                int fx = getf(x);
                write(nodes[heaps[fx].min].key);
                putchar('\n');
                isdelete[heaps[fx].min] = true;
                pop(heaps[fx]);
            }
        }
    }
}