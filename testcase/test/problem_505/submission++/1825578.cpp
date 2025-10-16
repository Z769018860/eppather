#include <bits/stdc++.h>
using namespace std;
const int N = 505, M = 1e6 + 5, INF = 2e9;

int T, n, m, d[N], now[N], s, t;
int head[N], nxt[M], to[M], w[M], tot;
bitset<N> vis;
queue<int> q;
struct node {
	int x, y, w, r;
} a[N], b[N];

void add(int x, int y, int z) {
	nxt[++tot] = head[x];
	to[tot] = y, w[tot] = z;
	head[x] = tot;
	nxt[++tot] = head[y];
	to[tot] = x, w[tot] = 0;
	head[y] = tot;
}

bool bfs() {
	memset(d, 0, sizeof(d));
	while (q.size()) q.pop();
	q.push(s);
	d[s] = 1;
	now[s] = head[s];
	while (q.size()) {
		int x = q.front(); q.pop();
		for (int i = head[x]; i; i = nxt[i]) {
			int y = to[i], z = w[i];
			if (z && !d[y]) {
				d[y] = d[x] + 1;
				now[y] = head[y];
				q.push(y);
				if (y == t) return true;
			}
		}
	}
	return false;
}

int dinic(int x, int flow) {
	if (x == t) return flow;
	int rest = flow, k, i;
	for (i = now[x]; i && rest; i = nxt[i]) {
		int y = to[i], z = w[i];
		if (z && d[y] == d[x] + 1) {
			k = dinic(y, min(rest, z));
			if (!k) d[y] = 0;
			w[i] -= k;
			w[i ^ 1] += k;
			rest -= k;
		}
	}
	now[x] = i;
	return flow - rest;
}

bool check(int i, int j) {
	return (a[i].x - b[j].x) * (a[i].x - b[j].x) + (a[i].y - b[j].y) * (a[i].y - b[j].y) <= a[i].r * a[i].r;
}
signed main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &m);
		for (int i = 0; i <= n + m; i++) head[i] = 0;
		tot = 1;
		vis.reset();
		for (int i = 1; i <= n; i++)
			scanf("%d %d %d %d", &a[i].x, &a[i].y, &a[i].w, &a[i].r);
		int sum = a[1].w, v = 0;
		for (int i = 1; i <= m; i++) {
			scanf("%d %d %d", &b[i].x, &b[i].y, &b[i].w);
			if (check(1, i)) sum += b[i].w, b[i].w = 0;
			else add(i + n, 0, b[i].w);
		}
		int maxflow = 0, flow;
		for (int i = 2; i <= n; i++) {
			if (a[i].w > sum) {
				puts("qaq");
				goto end;
			}
			add(1, i, sum - a[i].w);
			for (int j = 1; j <= m; j++) {
				
				if (check(i, j)) {
					add(i, j + n, 1e6);
					vis[j] = 1;
				}
			}
		}
		for (int i = 1; i <= m; i++)
			if (vis[i]) v += b[i].w;
		s = 1, t = 0;
		while (bfs())
			while ((flow = dinic(s, INF))) maxflow += flow;

		puts(maxflow == v ? "ZQC! ZQC!" : "qaq");
		end:;
	}
	return 0;
}