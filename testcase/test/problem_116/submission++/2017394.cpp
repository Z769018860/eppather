#include <bits/stdc++.h>
using namespace std;
const int inf = 0x3f3f3f3f;
const int N = 2e2 + 7, M = 2e4 + 7;

int n, m, S, T;

template <class T = int>
inline T read() {
	char c = getchar();
	bool sign = (c == '-');
	
	while (c < '0' || c > '9')
		c = getchar(), sign |= (c == '-');
	
	T x = 0;
	
	while ('0' <= c && c <= '9')
		x = (x << 1) + (x << 3) + (c & 15), c = getchar();
	
	return sign ? (~x + 1) : x;
}

namespace Dinic {
struct Edge {
	int nxt, v, f;
} e[M << 1];

int head[N], cur[N], dep[N];
bool vis[N];

int n, S, T, tot, maxflow;

inline void prework(const int _n, const int _S, const int _T) {
	n = _n, S = _S, T = _T, tot = 1;
	memset(head + 1, 0, sizeof(int) * n);
}

inline void insert(int u, int v, int f) {
	e[++tot] = (Edge) {head[u], v, f}, head[u] = tot;
	e[++tot] = (Edge) {head[v], u, 0}, head[v] = tot;
}

inline bool bfs() {
	memcpy(cur + 1, head + 1, sizeof(int) * n);
	memset(dep + 1, 0, sizeof(int) * n);
	memset(vis + 1, false, sizeof(bool) * n);
	queue<int> q;
	dep[S] = 1, q.emplace(S);

	while (!q.empty()) {
		int u = q.front();
		q.pop();

		for (int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].v, f = e[i].f;

			if (f && !dep[v])
				dep[v] = dep[u] + 1, q.emplace(v);
		}
	}

	return dep[T];
}

int dfs(int u, int flow) {
	if (u == T)
		return flow;

	vis[u] = true;
	int outflow = 0;

	for (int &i = cur[u]; i; i = e[i].nxt) {
		int v = e[i].v, f = e[i].f;

		if (f && dep[v] == dep[u] + 1 && !vis[v]) {
			int res = dfs(v, min(f, flow - outflow));
			e[i].f -= res, e[i ^ 1].f += res, outflow += res;

			if (outflow == flow)
				break;
		}
	}

	if (outflow == flow)
		vis[u] = false;

	return outflow;
}

inline int solve(const bool flag = true) {
	if (flag)
		maxflow = 0;

	while (bfs())
		maxflow += dfs(S, inf);

	return maxflow;
}
} 

namespace NSTFlow {
int d[N];

int n, S, T;

inline void prework(const int _n) {
	n = _n, S = n + 1, T = n + 2;
	memset(d + 1, 0, sizeof(int) * n);
	Dinic::prework(n + 2, S, T);
}

inline void insert(const int u, const int v, const int l, const int r) {
	Dinic::insert(u, v, r - l);
	d[v] += l, d[u] -= l;
}

inline bool solve() {
	int s = 0;

	for (int i = 1; i <= n; ++i)
		if (d[i] > 0)
			Dinic::insert(S, i, d[i]), s += d[i];
		else if (d[i] < 0)
			Dinic::insert(i, T, -d[i]);

	return Dinic::solve() == s;
}
} 

namespace YSTMaxFlow {
int n, S, T;

inline void prework(const int _n, const int _S, const int _T) {
	n = _n, S = _S, T = _T;
	NSTFlow::prework(n);
}

inline void insert(const int u, const int v, const int l, const int r) {
	NSTFlow::insert(u, v, l, r);
}

inline int solve() {
	NSTFlow::insert(T, S, 0, inf);

	if (!NSTFlow::solve())
		return -1;

	Dinic::S = S, Dinic::T = T;
	return Dinic::solve();
}
} 

signed main() {
	n = read(), m = read(), S = read(), T = read();
	YSTMaxFlow::prework(n, S, T);

	for (int i = 1; i <= m; ++i) {
		int u = read(), v = read(), l = read(), r = read();
		YSTMaxFlow::insert(u, v, l, r);
	}

	int ans = YSTMaxFlow::solve();

	if (ans == -1)
		puts("please go home to sleep");
	else
		printf("%d", ans);

	return 0;
}