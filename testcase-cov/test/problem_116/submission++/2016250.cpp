

#include <queue>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#define eputchar(c) putc(c, stderr)
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#define eputs(str) fputs(str, stderr), putc('\n', stderr)
using namespace std;

const long long inf = 0x3f3f3f3f3f3f3f3f;

int n, m, s, t, in[50015], out[50015];
struct flow {
	int s, t;
	struct graph {
		int tot, hd[50015];
		int nxt[350025], to[350025];
		long long flw[350025];

		graph(): tot(1) {}
		void add(int u, int v, long long f) {
			nxt[++tot] = hd[u];
			hd[u] = tot;
			to[tot] = v;
			flw[tot] = f;
			return ;
		}
	} g;
	int dis[50015], cur[50015];

	void add_edge(int u, int v, long long f) {g.add(u, v, f), g.add(v, u, 0); return ;}
	int bfs() {
		memset(dis, -1, sizeof(dis));
		queue<int> q;
		dis[s] = 0, q.push(s);
		while (!q.empty()) {
			int now = q.front();
			q.pop();
			cur[now] = g.hd[now];
			for (int i = g.hd[now]; i; i = g.nxt[i])
				if (g.flw[i] && dis[g.to[i]] == -1) dis[g.to[i]] = dis[now] + 1, q.push(g.to[i]);
		}
		return dis[t] != -1;
	}
	long long dinic(int now, long long flow) {
		if (now == t) return flow;
		long long used = 0;
		for (int i = cur[now]; i && used < flow; i = g.nxt[i])
			if (g.flw[i] && dis[g.to[i]] == dis[now] + 1) {
				long long f = dinic(g.to[i], min(flow - used, g.flw[i]));
				g.flw[i] -= f, g.flw[i ^ 1] += f;
				used += f;
				cur[now] = i;
			}
		if (used == 0) dis[now] = 0;
		return used;
	}
	long long solve() {
		long long res = 0;
		while (bfs()) res += dinic(s, inf);
		return res;
	}
} f;

int main() {
	
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m >> s >> t;
	for (int i = 1; i <= m; i++) {
		int u, v, l, r;
		cin >> u >> v >> l >> r;
		in[v] += l;
		out[u] += l;
		f.add_edge(u, v, r - l);
	}
	int sum = 0;
	for (int i = 1; i <= n; i++)
		if (in[i] > out[i]) f.add_edge(n + 1, i, in[i] - out[i]), sum += in[i] - out[i];
		else if (out[i] > in[i]) f.add_edge(i, n + 2, out[i] - in[i]);
	f.add_edge(t, s, inf);
	f.s = n + 1, f.t = n + 2;
	if (sum > f.solve()) {cout << "please go home to sleep\n"; return 0;}
	long long ans = f.g.flw[f.g.tot];
	f.s = s, f.t = t;
	ans = f.solve();
	cout << ans << '\n';
	return 0;
}