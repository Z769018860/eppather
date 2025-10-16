#include <stdio.h>

int main(int argc, char const *argv[]) {
	int n, m, s, t;
	scanf("%d%d%d%d", &n, &m, &s, &t);
	int cost[n][n], d[n], used[n];
	for(int i = 0; i < n; i++) {
		d[i] = 1e9 + 1;
		used[i] = 0;
		for(int j = 0; j < n; j++) {
			cost[i][j] = 1e9 + 1;
		}
	}
	s --, t --;
	d[s] = 0;
	for(int i = 0; i < m; i++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		u --, v --;
		cost[u][v] = cost[v][u] = w;
	}
	while(1) {
		int v = -1;
		for(int u = 0; u < n; u ++) {
			if (!used[u] && (v == -1 || d[u] < d[v])) {
				v = u;
			}
		}
		if (v == -1) break;
		used[v] = 1;
		for(int u = 0; u < n; u++) {
			if (d[v] + cost[v][u] < d[u]) 
				d[u] = d[v] + cost[v][u];
		}
	}
	printf("%d\n", d[t]);

	return 0;
}