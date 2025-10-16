#include<bits/stdc++.h>
const int N = 1e2, K = 1 << 10;
int f[N][K];
std::vector<std::pair<int, int> > G[N];
int main() {
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1, x, y, z; i <= m; i++) {
		scanf("%d%d%d", &x, &y, &z), x--, y--;
		G[x].emplace_back(y, z), G[y].emplace_back(x, z);
	}
	memset(f, 0x3f, sizeof(f));
	for (int i = 0, x; i < k; i++) {
		scanf("%d", &x), x--;
		f[x][1 << i] = 0;
	}
	for (int s = 1; s < (1 << k); s++) {
		for (int t = s & (s - 1); t >= (s ^ t); t = s & (t - 1)) {
			for (int i = 0; i < n; i++) {
				f[i][s] = std::min(f[i][s], f[i][t] + f[i][s ^ t]);
			}
		}
		std::priority_queue<std::pair<int, int> > q;
		for (int i = 0; i < n; i++) {
			q.emplace(-f[i][s], i);
		}
		for (; ! q.empty(); ) {
			std::pair<int, int> now = q.top();
			int u = now.second;
			q.pop();
			if (-now.first > f[u][s]) {
				continue;
			}
			for (std::pair<int, int> i : G[u]) {
				int v = i.first, w = i.second;
				if (f[u][s] + w < f[v][s]) {
					f[v][s] = f[u][s] + w;
					q.emplace(-f[v][s], v);
				}
			}
		}
	}
	int ans = 0x3f3f3f3f;
	for (int i = 0; i < n; i++) {
		ans = std::min(ans, f[i][(1 << k) - 1]);
	}
	printf("%d\n", ans);
	return 0;
}