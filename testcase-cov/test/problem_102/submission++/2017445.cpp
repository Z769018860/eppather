







#include <bits/stdc++.h>
#define pb emplace_back
#define mt make_tuple
#define mp make_pair
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef tuple<int, int, int> tu;
bool Mbe;

struct Flow {
	const int inf = 0x3f3f3f3f;
	int n, s, t, tot;
	struct edge { int to, nxt, w, c; };
	vector<int> hd, cr, d, vs;
	vector<edge> e;
	Flow (int _n) : n(_n), tot(-1) { hd.resize(n + 5, -1), d.resize(n + 5), vs.resize(n + 5), e.clear(); }
	void add_edge(int u, int v, int w, int c) { e.pb((edge) { v, hd[u], w, c }), hd[u] = ++tot; }
	void add_flow(int u, int v, int w, int c) { add_edge(u, v, w, c), add_edge(v, u, 0, -c); }
	bool spfa() {
		fill(d.begin(), d.end(), inf);
		queue<int> q; q.push(s), d[s] = 0;
		while (!q.empty()) {
			int u = q.front(); q.pop(), vs[u] = 0;
			for (int i = hd[u]; ~i; i = e[i].nxt) {
				int v = e[i].to;
				if (!e[i].w) continue;
				if (d[v] > d[u] + e[i].c) {
					d[v] = d[u] + e[i].c;
					if (!vs[v]) q.push(v), vs[v] = 1;
				}
			}
		}
		return d[t] != inf;
	}
	int dfs(int u, int in) {
		if (u == t) return in;
		int out = 0;
		vs[u] = 1;
		for (int &i = cr[u]; ~i; i = e[i].nxt) {
			int v = e[i].to;
			if (e[i].w && !vs[v] && d[v] == d[u] + e[i].c) {
				int res = dfs(v, min(in, e[i].w));
				e[i].w -= res, e[i ^ 1].w += res;
				in -= res, out += res;
			}
			if (!in) break;
		}
		vs[u] = 0;
		return out;
	}
	pi dinic() {
		int mc = 0, mf = 0;
		while (spfa()) {
			cr = hd;
			int res = dfs(1, inf);
			mc += res * d[t], mf += res;
		}
		return mp(mf, mc);
	}
};

void solve() {
	int n, m; 
	cin >> n >> m; Flow G(n); G.s = 1, G.t = n;
	for (int i = 1, u, v, w, c; i <= m; i++)
		cin >> u >> v >> w >> c, G.add_flow(u, v, w, c);
	pi res = G.dinic();
	cout << res.fi << ' ' << res.se << '\n';
}

bool Med;
int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cerr << (&Mbe - &Med) / 1048576.0 << " MB\n";
	#ifdef FILE
		freopen("1.in", "r", stdin);
		freopen("1.out", "w", stdout);
	#endif
	int T = 1;
	
	while (T--) solve();
	cerr << (int)(1e3 * clock() / CLOCKS_PER_SEC) << " ms\n";
	return 0;
}