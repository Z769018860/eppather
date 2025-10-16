#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RN 250000

typedef int I;
typedef char C;
typedef long long L;

#define SWAP(T, a, b) { T t = a; a = b; b = t; }



typedef struct
{
    I nxt;
    I to;
    I cap;
    I cost;
}
Network;

Network net_pool[RN * 2];
I ncnt = 1;

#define nnode(x) net_pool[x]
#define nnxt(x)  nnode(x).nxt
#define nto(x)   nnode(x).to
#define ncap(x)  nnode(x).cap
#define ncost(x) nnode(x).cost



I head[RN], fa[RN], fe[RN], pi[RN], mark[RN], buf[RN];
I ti, nc;

static inline void addEdge(I u, I v, I f, I c)
{
    nnode(++ncnt) = (Network) { head[u], v, f, c };
    head[u] = ncnt;
    nnode(++ncnt) = (Network) { head[v], u, 0, -c };
    head[v] = ncnt;
}

void initTree(I x)
{
    nc++, mark[x] = 1;
    for (I i = head[x]; i; i = nnxt(i))
    {
        I v = nto(i);
        if (!mark[v])
        {
            pi[v] = pi[x] + ncost(i);
            fa[v] = x, fe[v] = i;
            initTree(v);
        }
    }
}

static inline I phi(I x)
{
    I top = 0;
    while (mark[x] != ti) mark[buf[top++] = x] = ti, x = fa[x];
    while (top--) x = buf[top], pi[x] = pi[fa[x]] + ncost(fe[x]);
    return pi[x];
}

void pushFlow(I e)
{
    I u = nto(e ^ 1), v = nto(e), l = nc, r = nc;
    ti++, buf[nc] = e;
    while (u)             buf[++r] = fe[u],     mark[u] = ti, u = fa[u];
    while (mark[v] != ti) buf[--l] = fe[v] ^ 1, mark[v] = ti, v = fa[v];

    I e2 = l, f = ncap(buf[l]);
    for (I i = l; buf[i] != fe[v]; i++)
    {
        if (ncap(buf[i]) < f) e2 = i, f = ncap(buf[i]);
    }
    for (I i = l; buf[i] != fe[v]; i++)
    {
        ncap(buf[i]) -= f, ncap(buf[i] ^ 1) += f;
    }
    if (e2 == nc) return;

    I x = e ^ (e2 < nc), y = nto(x), z = nto(x ^ 1);
    while (x != (buf[e2] ^ (e2 < nc)))
    {
        x ^= 1;
        pi[z] = pi[y] - ncost(x);
        SWAP(I, x, fe[z]);
        SWAP(I, y, fa[z]);
        SWAP(I, y, z);
    }
}

void simplex(I root)
{
    nc = fa[root] = 0, ti = 1;
    initTree(root);
    for (I i = 2, pre = ncnt; i != pre; i = i == ncnt ? 2 : i + 1)
    {
        if (ncap(i) && ncost(i) < phi(nto(i)) - phi(nto(i ^ 1)))
            pushFlow(pre = i);
    }
}



I delta[RN], low[RN];

int main(void)
{
    I n, m, s, t;
    I sum = 0;
    scanf("%d%d%d%d", &n, &m, &s, &t);
    for (I i = 1; i <= m; i++)
    {
        I u, v, mn, mx;
        scanf("%d%d%d%d", &u, &v, &mn, &mx);
        addEdge(u, v, mx - mn, 0);
        low[ncnt] = mn;
        delta[v] += mn, delta[u] -= mn;
    }
    for (I i = 1; i <= n; i++)
    {
        if (delta[i] > 0)
        {
            sum += delta[i];
            addEdge(n + 1, i, delta[i], 0);
        }
        else if (delta[i] < 0)
        {
            addEdge(i, n + 2, -delta[i], 0);
        }
    }
    addEdge(n + 2, n + 1, 0x7fffffff, -100000);
    addEdge(t, s, 0x7fffffff, 0);
    simplex(n + 2);
    if (ncap(ncnt - 2) < sum)
    {
        puts("please go home to sleep");
        return 0;
    }
    ncost(ncnt - 1) = -1000, ncost(ncnt) = 1000;
    memset(mark, 0, sizeof(mark));
    simplex(t);

    printf("%d\n", ncap(ncnt));
    return 0;
}