#include <stdio.h>
#include <stdlib.h>

typedef struct edge {
	int u;
	int v;
	int w;
} edge;
edge e[500010];

int link[200010];
int comp(const void *a, const void *b)
{
	return (*(edge*)a).w - (*(edge*)b).w;
}

int find(int k)
{
	return (link[k] == k) ? k : (link[k] = find(link[k]));
}

int main()
{
	int n, m;
	long long ans = 0;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++) {
		scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
	}
	qsort(e, m, sizeof(edge), comp);
	for (int i = 0; i < n; i++)
		link[i] = i;
	int num = 0;
	for (int i = 0; i < m && num < n; i++) {
		int u1 = find(e[i].u);
		int v1 = find(e[i].v);
		if (u1 != v1) {
			link[u1] = v1;
			ans += e[i].w;
			num++;
		}
	}
	printf("%lld", ans);
	return 0;
}
