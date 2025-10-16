#include <bits/stdc++.h>
#define eb emplace_back
#define mp make_pair
#define fi first
#define se second
#define int long long

using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
bool Mbe;

const int N = 450;
const int M = 3e4 + 300;
const int inf = 1e12;

struct E { int to, nxt, w, c; } e[M];
int n, m, s, t, tot, hd[N], cr[N], vs[N], d[N];

void addE(int u, int v, int w, int c) { e[++tot] = (E) { v, hd[u], w, c }, hd[u] = tot; }
void addF(int u, int v, int w, int c) { addE(u, v, w, c), addE(v, u, 0, -c); }

bool bfs() {
	for (int i = 1; i <= n; i++) d[i] = inf;
	d[s] = 0; queue<int> q; q.push(s), vs[s] = 1;
	while (!q.empty()) {
		int u = q.front(); q.pop(), vs[u] = 0;
		for (int i = hd[u]; i; i = e[i].nxt) {
			int v = e[i].to;
			if (e[i].w && d[v] > d[u] + e[i].c) {
				d[v] = d[u] + e[i].c;
				if (!vs[v]) q.push(v), vs[v] = 1;
			} 
		}
	}
	return d[t] != inf;
}

int dfs(int u, int in) {
	if (u == t) return in;
	vs[u] = 1; int out = 0; 
	for (int &i = cr[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if (e[i].w && !vs[v] && d[v] == d[u] + e[i].c) {
			int res = dfs(v, min(in, e[i].w));
			in -= res, out += res;
			e[i].w -= res, e[i ^ 1].w += res;
		}
		if (!in) break;
	}
	vs[u] = 0;
	if (!out) d[u] = inf;
	return out;
}

pi mcmf() {
	pi res = mp(0, 0);
	while (bfs()) {
		for (int i = 1; i <= n; i++) cr[i] = hd[i];
		int tp = dfs(s, inf);
		res.fi += tp, res.se += tp * d[t];
	}
	return res;
}

void solve() {
	cin >> n >> m, s = tot = 1, t = n;
	for (int i = 1, u, v, w, c; i <= m; i++)
		cin >> u >> v >> w >> c, addF(u, v, w, c);
	pi res = mcmf();
	cout << res.fi << ' ' << res.se << '\n';
}

bool Med;
signed main() {

	#ifdef FILE
		freopen(".in", "r", stdin);
		freopen(".out", "w", stdout);
	#endif
	int T = 1;

	while (T--) solve();
	return 0;
}
