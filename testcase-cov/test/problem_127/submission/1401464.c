#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RN 1000005

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
I       ncnt = 1;

#define nnode(x) net_pool[x]
#define nnxt(x)  nnode(x).nxt
#define nto(x)   nnode(x).to
#define ncap(x)  nnode(x).cap
#define ncost(x) nnode(x).cost



I head[RN], fa[RN], fe[RN], mark[RN], pi[RN], cyc[RN];
I ti;

static inline void addNet(I u, I v, I f1, I c1, I f2, I c2)
{
	nnode(++ncnt) = (Network) { head[u], v, f1, c1 };
	head[u] = ncnt;
	nnode(++ncnt) = (Network) { head[v], u, f2, c2 };
	head[v] = ncnt;
}

void initTree(I x)
{
	mark[x] = 1;
	for (I i = head[x]; i; i = nnxt(i))
	{
		I v = nto(i);
		if (!mark[v] && ncap(i))
		{
			fa[v] = x, fe[v] = i;
			initTree(v);
		}
	}
}

I phi(I x)
{
	if (mark[x] == ti) return pi[x];
	return mark[x] = ti, pi[x] = phi(fa[x]) - ncost(fe[x]);
}

void pushFlow(I e, L *cost)
{
	I pen = nto(e ^ 1), lca = nto(e);
	ti++;
	while (pen)              mark[pen] = ti, pen = fa[pen];
	while (mark[lca] != ti) mark[lca] = ti, lca = fa[lca];
	
	I e2 = 0, f = ncap(e), path = 2, clen = 0;
	for (I i = nto(e ^ 1); i != lca; i = fa[i])
	{
		cyc[++clen] = fe[i];
		if (ncap(fe[i]) < f) f = ncap(fe[e2 = i] ^ (path = 0));
	}
	for (I i = nto(e); i != lca; i = fa[i])
	{
		cyc[++clen] = fe[i] ^ 1;
		if (ncap(fe[i] ^ 1) <= f) f = ncap(fe[e2 = i] ^ (path = 1));
	}
	cyc[++clen] = e;
	
	for (I i = 1; i <= clen; i++)
	{
		ncap(cyc[i]) -= f, ncap(cyc[i] ^ 1) += f;
		*cost += 1ll * ncost(cyc[i]) * f;
	}
	if (path == 2) return;
	
	I laste = e ^ path, last = nto(laste), cur = nto(laste ^ 1);
	while (last != e2)
	{
		mark[cur]--;
		laste ^= 1;
		SWAP(I, laste, fe[cur]);
		SWAP(I, last, fa[cur]);
		SWAP(I, last, cur);
	}
}

I simplex(I st, I ed, L *cost)
{
	I lhead = head[st], lhead2 = head[ed];
	addNet(ed, st, 0x7fffffff, -0x3f3f3f3f, 0, 0x3f3f3f3f);
	initTree(ed);
	mark[ed] = ti = 2, fa[ed] = *cost = 0;
	for (I i = 3, pre = 2; i != pre; i = i == ncnt ? 2 : i + 1)
	{
		if (ncap(i) && mark[nto(i)] && mark[nto(i ^ 1)]
		 && ncost(i) < phi(nto(i ^ 1)) - phi(nto(i)))
			pushFlow(pre = i, cost);
	}
	head[st] = lhead, head[ed] = lhead2, ncnt -= 2;
	return ncap(ncnt + 2);
}

int main(void)
{
    I n, m, s, t;
    scanf("%d%d%d%d", &n, &m, &s, &t);
    for (I i = 1; i <= m; i++)
    {
        I u, v, f;
        scanf("%d%d%d", &u, &v, &f);
        addNet(u, v, f, 0, 0, 0);
    }
    L cost;
    printf("%d\n", simplex(s, t, &cost));
    return 0;
}