#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e6 + 10;
int n, m, r;
int v[MAXN];
int c[MAXN];
int dfn[MAXN];
int tot;
vector<int> edge[MAXN];
int summ[MAXN];
int siz[MAXN];

int lowbit(int x) {
	return x & (-x);
}

void add(int pos, int x) {
	while (pos <= n) {
		c[pos] += x;
		pos += lowbit(pos);
	}
}

int sum(int pos) {
	int ans = 0;
	while (pos != 0) {
		ans += c[pos];
		pos -= lowbit(pos);
	}
	return ans;
}

void dfs(int u, int fa) {
	dfn[u] = ++tot;
	add(tot, v[u]);
	siz[u] = 1;
	for (int v : edge[u]) {
		if (v == fa)
			continue;
		dfs(v, u);
		siz[u] += siz[v];
	}
}

signed main() {
	cin >> n >> m >> r;
	for (int i = 1; i <= n; i++) {
		cin >> v[i];
		
	}
	for (int i = 1; i <= n - 1; i++) {
		int u, v;
		cin >> u >> v;
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	dfs(r, 0);
	for (int i = 1; i <= m; i++) {
		int op;
		cin >> op;
		if (op == 1) {
			int a, x;
			cin >> a >> x;
			add(dfn[a], x);
		} else {
			int a;
			cin >> a;
			cout << sum(dfn[a] + siz[a] - 1) - sum(dfn[a] - 1) << endl;
		}
	}
}