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
    I to;
    I cap;
    I base;
    L cost;
}
Network;

Network net_pool[RN * 20];
I ncnt = 1;

#define nnode(x) net_pool[x]
#define nto(x)   nnode(x).to
#define ncap(x)  nnode(x).cap
#define nbase(x) nnode(x).base
#define ncost(x) nnode(x).cost



I fa[RN], fe[RN], mk[RN], _buf[2 * RN];
L pi[RN];
I ti, *buf = _buf + RN;

static inline void addSupply(I x, I v)
{
    if (!mk[x])
    {
        nnode(++ncnt) = (Network) { 0, 0, 0, 0x3f3f3f3f };
        nnode(++ncnt) = (Network) { x, 0, 0, -0x3f3f3f3f };
        mk[x] = 1, fa[x] = 0, fe[x] = ncnt;
    }
    if ((ncap(fe[x] | 1) += fe[x] & 1 ? v : -v) < 0)
    {
        ncap(fe[x] | 1) = -ncap(fe[x] | 1), fe[x] ^= 1;
        SWAP(I, nto(fe[x]), nto(fe[x] ^ 1));
    }
}

static inline void addEdge(I u, I v, I f, I b, L c)
{
    addSupply(u, -b), addSupply(v, b);
    nnode(++ncnt) = (Network) { v, f - b, 0, c };
    nnode(++ncnt) = (Network) { u, 0, b, -c };
}

void pushFlow(I e)
{
    I u = nto(e ^ 1), v = nto(e), l = 0, r = 0;
    buf[0] = e;
    while (~u)         buf[++r] = fe[u],     mk[u] = e, u = fa[u];
    while (mk[v] != e) buf[--l] = fe[v] ^ 1, mk[v] = e, v = fa[v];

    I e2 = l, f = ncap(buf[l]);
    for (I i = l; buf[i] != fe[v]; i++)
    {
        if (ncap(buf[i]) < f) e2 = i, f = ncap(buf[i]);
    }
    for (I i = l; buf[i] != fe[v]; i++)
    {
        ncap(buf[i]) -= f, ncap(buf[i] ^ 1) += f;
    }
    if (!e2) return;

    I x = e ^ (e2 < 0), y = nto(x), z = nto(x ^ 1);
    while (x != (buf[e2] ^ (e2 < 0)))
    {
        x ^= 1, mk[z] = 1;
        SWAP(I, x, fe[z]);
        SWAP(I, y, fa[z]);
        SWAP(I, y, z);
    }
}

static inline L phi(I x)
{
    I top = 0;
    while (mk[x] != ti) mk[buf[top++] = x] = ti, x = fa[x];
    while (top--) x = buf[top], pi[x] = pi[fa[x]] + ncost(fe[x]);
    return pi[x];
}

void simplex(void)
{
    ti = ncnt, fa[0] = -1;
    for (I i = 2; i != ti; i = i == ncnt ? 2 : i + 1)
    {
        if (ncap(i) && ncost(i) < phi(nto(i)) - phi(nto(i ^ 1)))
            pushFlow(ti = i);
    }
}



int main(void)
{
    I n, m, s, t;
    scanf("%d%d%d%d", &n, &m, &s, &t);
    I sum = 0;
    for (I i = 1; i <= m; i++)
    {
        I u, v, mn, mx;
        scanf("%d%d%d%d", &u, &v, &mn, &mx);
        addEdge(u, v, mx, mn, 0);
        if (u == s) sum += mn;
    }
    addEdge(t, s, 0x7fffffff, 0, 1);
    simplex();
    for (I i = 3; i <= ncnt; i += 2)
    {
        if ((!nto(i) || !nto(i ^ 1))
         && (nto(i) != s && nto(i ^ 1) != s)
         && (nto(i) != t && nto(i ^ 1) != t)
         && ncap(i))
        {
            puts("please go home to sleep");
            return 0;
        }
    }
    printf("%d\n", ncap(ncnt));
    return 0;
}