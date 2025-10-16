#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#define rep(i, a, b) for (int i = (a); i <= (b); i ++ )
#define dep(i, a, b) for (int i = (a); i >= (b); i -- )

using namespace std;

typedef pair<int, int> PII;
const int N = 100010;
struct P { int a, b, c; }p[N];
vector<PII> E[N];
int fa[N][21], mx[N][21], F[N], dep[N], n, m, q;
int find(int x) { return x == F[x] ? x : F[x] = find(F[x]); }
void add(int a, int b, int c) { 
	E[a].push_back({b, c}); E[b].push_back({a, c}); 
}
void dfs(int u, int f) {
	fa[u][0] = f, dep[u] = dep[f] + 1;
	for (auto [v, w] : E[u]) if (v ^ f) mx[v][0] = w, dfs(v, u);
}
int ask(int u, int v, int s = 0) {
	if (find(u) ^ find(v)) return -1;
	if (dep[u] < dep[v]) swap(u, v);
	dep(i, 20, 0) if (dep[fa[u][i]] >= dep[v]) 
		s = max(s, mx[u][i]), u = fa[u][i];
	if (u == v) return s;
	dep(i, 20, 0) if (fa[u][i] != fa[v][i])
		s = max({s, mx[u][i], mx[v][i]}),
		u = fa[u][i], v = fa[v][i];
	s = max({s, mx[u][0], mx[v][0]}); return s;
}
int main() {
	scanf("%d%d%d", &n, &m, &q);
	rep(i, 1, m) scanf("%d%d%d", &p[i].a, &p[i].b, &p[i].c);
	sort(p + 1, p + m + 1, [&](P a, P b) { return a.c < b.c; });
	rep(i, 1, n) F[i] = i;
	rep(i, 1, m) if (find(p[i].a) ^ find(p[i].b))
		add(p[i].a, p[i].b, p[i].c),
		F[find(p[i].a)] = find(p[i].b);
	rep(i, 1, n) if (!dep[i]) dfs(i, 0);
	rep(j, 1, 20) rep(i, 1, n) 
		fa[i][j] = fa[fa[i][j - 1]][j - 1];
	rep(j, 1, 20) rep(i, 1, n) 
		mx[i][j] = max(mx[i][j - 1], mx[fa[i][j - 1]][j - 1]);
	rep(i, 1, q) {
		int s, t; scanf("%d%d", &s, &t);
		printf("%d\n", ask(s, t));
	} return 0;
}