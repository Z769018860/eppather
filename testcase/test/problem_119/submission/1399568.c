#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RN 1000005

typedef int I;
typedef char C;



typedef struct
{
	I nxt;
	I to;
	I len;
}
Edge;

Edge edge_pool[RN];
I    ecnt;

#define enode(x) edge_pool[x]
#define enxt(x)  enode(x).nxt
#define eto(x)   enode(x).to
#define elen(x)  enode(x).len



I head[RN], pq[RN * 3], dis[RN];

static inline void addEdge(I u, I v, I w)
{
	enode(++ecnt) = (Edge) { head[u], v, w };
	head[u] = ecnt;
}

void dijkstra(I n, I st)
{
	memset(dis, 0x3f, sizeof(I) * (n + 2));
	dis[st] = 0;
	I siz = 1;
	while (siz < n) siz <<= 1;
	siz--;
	for (I i = siz + st; i; i >>= 1) pq[i] = st;
	while (pq[1])
	{
		I u = pq[1];
		pq[siz + u] = 0;
		for (I i = siz + u; i >> 1; i >>= 1)
			pq[i >> 1] = dis[pq[i]] < dis[pq[i ^ 1]] ? pq[i] : pq[i ^ 1];
		for (I i = head[u]; i; i = enxt(i))
		{
			I v = eto(i);
			if (dis[v] > dis[u] + elen(i))
			{
				dis[v] = dis[u] + elen(i);
				pq[siz + v] = v;
				I it = siz + v;
				while (it >> 1 && dis[v] < dis[pq[it ^ 1]])
					pq[it >>= 1] = v;
			}
		}
	}
}



int main(void)
{
	I n, m, s, t;
	scanf("%d%d%d%d", &n, &m, &s, &t);
	for (I i = 1; i <= m; i++)
	{
		I u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		addEdge(u, v, w);
		addEdge(v, u, w);
	}
	dijkstra(n, s);
	printf("%d\n", dis[t]);
	return 0;
}
