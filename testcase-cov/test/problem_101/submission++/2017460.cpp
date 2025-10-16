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

const int N = 150;
const int M = 5e3 + 500;
const int inf = 1e18;

struct E { int to, nxt, w; } e[M << 1];
int n, m, s, t, tot, hd[N], cr[N], d[N];

void addE(int u, int v, int w) { e[++tot] = (E) { v, hd[u], w }, hd[u] = tot; }
void addF(int u, int v, int w) { addE(u, v, w), addE(v, u, 0); }

int bfs() {
	for (int i = 1; i <= n; i++) d[i] = 0;
	d[s] = 1; queue<int> q; q.push(s);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int i = hd[u]; i; i = e[i].nxt) {
			int v = e[i].to;
			if (!e[i].w || d[v]) continue;
			d[v] = d[u] + 1, q.push(v);
		}
	}
	return d[t];
}

int dfs(int u, int in) {
	if (u == t) return in;
	int out = 0;
	for (int &i = cr[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if (e[i].w && d[v] == d[u] + 1) {
			int res = dfs(v, min(e[i].w, in));
			in -= res, out += res;
			e[i].w -= res, e[i ^ 1].w += res;
		}
		if (!in) break;
	}
	if (!out) d[u] = 0;
	return out;
}

int mf() {
	int res = 0;
	while (bfs()) {
		for (int i = 1; i <= n; i++) cr[i] = hd[i];
		res += dfs(s, inf);
	}
	return res;
}

void solve() {
	cin >> n >> m >> s >> t, tot = 1;
	for (int i = 1, u, v, w; i <= m; i++) 
		cin >> u >> v >> w, addF(u, v, w);
	cout << mf() << '\n';
}

bool Med;
signed main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	#ifdef FILE
		freopen(".in", "r", stdin);
		freopen(".out", "w", stdout);
	#endif
	int T = 1;

	while (T--) solve();
	return 0;
}
