
#include <cstdio>
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
namespace BinomialHeap
{
    
    const int maxn = 100010;
    
    struct BinomialNode
    {
        int Key, Degree; 
        bool mark;       
        
        BinomialNode *ch, *next;
        BinomialNode() {}
        BinomialNode(int Key) : Key(Key), Degree(1)
        {
            ch = next = NULL, mark = false;
        }
    } nodes[maxn];
    BinomialNode *a[20], *b[20], *last, *now;
    int atop, btop;
    int Node = 0;
    
    inline BinomialNode *merge(BinomialNode *a, BinomialNode *b)
    {
        if (a->Key > b->Key || (a->Key == b->Key && a > b))
            swap(a, b);
        b->next = a->ch;
        a->ch = b;
        a->Degree++;
        return a;
    }
    
    inline BinomialNode *unite(BinomialNode *x, BinomialNode *y)
    {
        if (!x || !y)
            return x ? x : y; 
        atop = btop = 0;
        BinomialNode *last = NULL, *now;
        for (BinomialNode *i = x; i; i = i->next)
            a[++atop] = i;
        for (BinomialNode *i = y; i; i = i->next)
            b[++btop] = i;
        while (atop || btop)
        {
            if (atop && (!btop || a[atop]->Degree <= b[btop]->Degree))
                now = a[atop--];
            else
                now = b[btop--];
            if (last && last->Degree == now->Degree)
            {
                BinomialNode *pre = last->next;
                last->next = NULL;
                now = merge(last, now);
                last = pre;
            }
            now->next = last, last = now;
        }
        return last;
    }
    inline BinomialNode *set(int key)
    {
        nodes[++Node] = BinomialNode(key);
        return &nodes[Node];
    }
    
    inline BinomialNode *top(BinomialNode *x)
    {
        BinomialNode *ans = NULL;
        for (BinomialNode *i = x; i; i = i->next)
            if (!ans || ans->Key > i->Key)
                ans = i;
        return ans;
    }
    inline int pop(int p);
}
namespace UnionSet
{
    
    const int maxn = 100010;
    int f[maxn];
    int F, Mv, Fa, Fx, Fy;
    inline int Getf(int i)
    {
        for (F = i; f[F] != F; F = f[F])
            ;
        for (Mv = i; f[Mv] != Mv; Mv = Fa)
            Fa = f[Mv], f[Mv] = F;
        return F;
    }
    inline bool Unite(int x, int y)
    {
        Fx = Getf(x), Fy = Getf(y);
        if (Fx == Fy)
            return false;
        f[Fy] = Fx;
        return true;
    }
    inline void Set(int Size)
    {
        for (int i = 1; i <= Size; i++)
            f[i] = i;
    }
}
int n, m;
int key;
int op, x, y, fx, fy;
BinomialHeap::BinomialNode *H[maxn], *vec[maxn];
inline int BinomialHeap::pop(int p)
{
    BinomialNode *x = H[p];
    BinomialNode *Min = BinomialHeap::top(x);
    Min->mark = true;
    if (Min == x)
        x = Min->next;
    else
    {
        BinomialNode *i;
        for (i = x; i->next != Min; i = i->next)
            ;
        i->next = Min->next;
    }
    H[p] = unite(x, Min->ch);
    return Min->Key;
}
int main()
{
    n = read(), m = read();
    for (int i = 1; i <= n; ++i)
        key = read(), vec[i] = H[i] = BinomialHeap::set(key);
    UnionSet::Set(n);
    while (m--)
    {
        op = read();
        if (op == 1)
        {
            x = read(), y = read();
            if (vec[x]->mark || vec[y]->mark)
                continue;
            fx = UnionSet::Getf(x), fy = UnionSet::Getf(y);
            if (fx == fy)
                continue;
            H[fx] = BinomialHeap::unite(H[fx], H[fy]);
            UnionSet::f[fy] = fx;
        }
        else
        {
            x = read();
            if (vec[x]->mark)
                puts("-1");
            else
                write(BinomialHeap::pop(UnionSet::Getf(x))), putchar('\n');
        }
    }
}