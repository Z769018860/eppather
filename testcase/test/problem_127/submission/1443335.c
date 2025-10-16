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
    nnode(++ncnt) = (Network){ head[u], v, f, c };
    head[u] = ncnt;
    nnode(++ncnt) = (Network){ head[v], u, 0, -c };
    head[v] = ncnt;
}

void initTree(I x)
{
    nc++, mark[x] = 1;
    for (I i = head[x]; i; i = nnxt(i))
    {
        I v = nto(i);
        if (!mark[v] && ncap(i))
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
    ti++;
    while (u)             buf[++r] = fe[u], mark[u] = ti, u = fa[u];
    while (mark[v] != ti) buf[--l] = fe[v] ^ 1, mark[v] = ti, v = fa[v];
    buf[nc] = e;

    I e2 = l;
    for (I i = l; buf[i] != fe[v]; i++)
    {
        if (ncap(buf[e2]) > ncap(buf[i])) e2 = i;
    }
    I f = ncap(buf[e2]);
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



int main(void)
{
	I n, m, s, t;
	scanf("%d%d%d%d", &n, &m, &s, &t);
	for (I i = 1; i <= m; i++)
	{
		I u, v, f, c;
		scanf("%d%d%d", &u, &v, &f);
		addEdge(u, v, f, 0);
	}
	addEdge(t, s, 0x7fffffff, -0x3f3f3f3f);
	simplex(t);
	printf("%d\n", ncap(ncnt));
	return 0;
}