#include <bits/stdc++.h>
using namespace std;
const int inf = 0x3f3f3f3f;
const int N = 6e4 + 7, M = 1e6 + 7;

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

inline void reset(int _n, int _S, int _T) {
	n = _n, S = _S, T = _T, tot = 1;
}

inline void insert(int u, int v, int f) {
	e[++tot] = (Edge) {head[u], v, f}, head[u] = tot;
	e[++tot] = (Edge) {head[v], u, 0}, head[v] = tot;
}

inline bool bfs() {
	memset(dep + 1, 0, sizeof(int)*n);
	memset(vis + 1, false, sizeof(bool)*n);
	memcpy(cur + 1, head + 1, sizeof(int)*n);
	queue<int> q;
	dep[S] = 1, q.push(S);
	
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		
		for (int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].v;
			
			if (e[i].f && !dep[v]) {
				dep[v] = dep[u] + 1;
				
				if (v == T)
					return true;
				
				q.push(v);
			}
		}
	}
	
	return false;
}

int dfs(int u, int flow) {
	if (u == T)
		return flow;
	
	int outflow = 0;
	vis[u] = true;
	
	for (int &i = cur[u]; i; i = e[i].nxt) {
		int v = e[i].v;
		
		if (e[i].f && !vis[v] && dep[v] == dep[u] + 1) {
			int res = dfs(v, min(e[i].f, flow - outflow));
			e[i].f -= res, e[i ^ 1].f += res, outflow += res;
			
			if (outflow == flow)
				break;
		}
	}
	
	if (outflow == flow)
		vis[u] = false;
	
	return outflow;
}

inline void solve(bool flag = true) {
	if (flag)
		maxflow = 0;
	
	while (bfs())
		maxflow += dfs(S, inf);
}
} 

namespace NSTFlow {
int d[N];

int n, S, T, s;

inline void reset(int _n) {
	n = _n, S = n + 1, T = n + 2;
	memset(d + 1, 0, sizeof(int)*n);
	Dinic::reset(n + 2, S, T);
}

inline void insert(int u, int v, int l, int r) {
	Dinic::insert(u, v, r - l);
	d[v] += l, d[u] -= l;
}

inline bool solve() {
	s = 0;
	
	for (int i = 1; i <= n; ++i)
		if (d[i] > 0)
			Dinic::insert(S, i, d[i]), s += d[i];
		else if (d[i] < 0)
			Dinic::insert(i, T, -d[i]);
	
	Dinic::solve();
	return Dinic::maxflow == s;
}
} 

namespace YSTMinFlow {
int n, S, T;

inline void reset(int _n, int _S, int _T) {
	n = _n, S = _S, T = _T;
	NSTFlow::reset(n);
}

inline void insert(int u, int v, int l, int r) {
	NSTFlow::insert(u, v, l, r);
}

inline bool solve() {
	NSTFlow::solve();
	NSTFlow::insert(T, S, 0, inf);
	Dinic::solve(false);
	return Dinic::maxflow == NSTFlow::s;
}
} 

signed main() {
	n = read(), m = read(), S = read(), T = read();
	YSTMinFlow::reset(n, S, T);
	
	for (int i = 1; i <= m; ++i) {
		int u = read(), v = read(), l = read(), r = read();
		YSTMinFlow::insert(u, v, l, r);
	}
	
	if (!YSTMinFlow::solve())
		return puts("please go home to sleep"), 0;
	
	printf("%d", Dinic::e[Dinic::tot].f);	
	return 0;
}