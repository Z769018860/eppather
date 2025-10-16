#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <algorithm>
using namespace std;

const int BufferSize = 1 << 16;
char buffer[BufferSize], *Head, *Tail;
inline char Getchar()
{
    if (Head == Tail)
    {
        int l = fread(buffer, 1, BufferSize, stdin);
        Tail = (Head = buffer) + l;
    }
    return *Head++;
}
int read()
{
    int x = 0, f = 1;
    char c = Getchar();
    while (!isdigit(c))
    {
        if (c == '-')
            f = -1;
        c = Getchar();
    }
    while (isdigit(c))
    {
        x = x * 10 + c - '0';
        c = Getchar();
    }
    return x * f;
}

#define maxn 1000010

int n, fa[maxn];

struct Graph
{
    int m, head[maxn], nxt[maxn], to[maxn];
    Graph() : m(0) { memset(head, 0, sizeof(head)); }
    void AddEdge(int a, int b)
    {
        to[++m] = b;
        nxt[m] = head[a];
        head[a] = m;
        return;
    }
} gr, tr;

bool vis[maxn], is_cyc[maxn], has_tr[maxn], win[maxn];
int St[maxn], top, cps[maxn], cntc;
bool findcyc(int u)
{
    if (vis[u])
    {
        while (St[top] != u)
            is_cyc[cps[++cntc] = St[top--]] = 1;
        is_cyc[cps[++cntc] = u] = 1;
        return 1;
    }
    St[++top] = u;
    vis[u] = 1;
    for (int e = gr.head[u]; e; e = gr.nxt[e])
        if (findcyc(gr.to[e]))
            return 1;
    return 0;
}
void dp(int u)
{
    win[u] = 0;
    for (int e = tr.head[u]; e; e = tr.nxt[e])
        if (!is_cyc[tr.to[e]])
        {
            has_tr[u] = 1;
            dp(tr.to[e]);
            if (!win[tr.to[e]])
                win[u] = 1;
        }
    return;
}

int cid[maxn], pid[maxn], near[maxn];
bool winc[maxn], hastrc[maxn];
int Pre(int x)
{
    return x - 1 ? x - 1 : cntc;
}
int Nxt(int x)
{
    return x + 1 <= cntc ? x + 1 : 1;
}
int Dis(int a, int b)
{ 
    if (a >= b)
        return a - b;
    else
        return a + cntc - b;
}
bool canwin(int a, int brk)
{
    if (!near[a])
        return (a == brk ? cntc : Dis(a, brk)) - 1 & 1;
    if (a == brk)
        return min(Dis(a, near[a]), cntc) - 1 & 1;
    return min(Dis(a, near[a]), Dis(a, brk)) - 1 & 1;
}

int main()
{
    n = read();
    int q = read();
    for (int i = 1; i <= n; i++)
        fa[i] = read(), tr.AddEdge(fa[i], i), gr.AddEdge(i, fa[i]);

    findcyc(1);
    
    bool oncyc = 0;
    for (int i = 1; i <= cntc; i++)
    {
        dp(cps[i]);
        if (cps[i] == 1)
            oncyc = 1;
    }
    if (!oncyc)
    {
        while (q--)
        {
            read();
            read();
            printf("%d\n", win[1]);
        }
        return 0;
    }
    
    int onep, cnt = 0, ntr = -1;
    for (int i = cntc; i; i--)
        if (cps[i] == 1)
        {
            onep = i;
            break;
        }
    for (int i = onep; i; i--)
        cid[cps[i]] = ++cnt, pid[cnt] = cps[i], winc[cnt] = win[cps[i]], hastrc[cnt] = has_tr[cps[i]];
    for (int i = cntc; i > onep; i--)
        cid[cps[i]] = ++cnt, pid[cnt] = cps[i], winc[cnt] = win[cps[i]], hastrc[cnt] = has_tr[cps[i]];
    
    for (int i = 1;; i = Nxt(i))
    {
        if (hastrc[i] && winc[i])
            ntr = i;
        if (ntr >= 0)
            near[i] = ntr;
        if (Nxt(i) == 1)
            break;
    }
    for (int i = 1;; i = Nxt(i))
    {
        if (hastrc[i] && winc[i])
            ntr = i;
        if (ntr >= 0)
            near[i] = ntr;
        if (Nxt(i) == 1)
            break;
    }
    
    for (int kase = 1; kase <= q; kase++)
    {
        int u = read(), v = read();
        u = cid[u];
        v = cid[v];
        if (u < v)
        {
            if (winc[1])
            {
                puts("1");
                continue;
            }
            if (near[1] >= v)
            {
                puts((Dis(1, near[1]) & 1) ? "0" : "1");
                continue;
            }
            if (winc[v] | canwin(v, u))
            {
                puts((Dis(1, v) & 1) ? "0" : "1");
                continue;
            }
            if (1 < near[u] && near[u] <= u)
            {
                puts((Dis(1, v) + 1 + Dis(u, near[u]) & 1) ? "0" : "1");
                continue;
            }
            puts("2");
            continue;
        }
        if (v == 1)
        {
            if (winc[1] | canwin(1, u))
                puts("1");
            else if (1 < near[u] && near[u] <= u)
                puts((Dis(u, near[u]) + 1 & 1) ? "0" : "1");
            else
                puts("2");
            continue;
        }
        if (winc[1] | canwin(1, u))
            puts("1");
        else
            puts("0");
    }

    return 0;
}
