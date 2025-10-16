#include<cstdio>
#include<vector>
#define ll long long
using namespace std;
const int N = 1e6 + 7;
int n, m, root, tot;
vector<int>g[N];
int lx[N], rx[N];
int a[N], val[N];
struct node {
	int l, r;
	ll sum;
	ll add;
}t[N * 4];
void push_up(int p) {
	t[p].sum = t[p * 2].sum + t[p * 2 + 1].sum;
}
void push_add(int p, ll d) {
	t[p].add += d;
	t[p].sum += (t[p].r - t[p].l + 1) * d;
}
void push_down(int p) {
	if (t[p].add == 0)return;
	ll d = t[p].add;
	push_add(p * 2, d);
	push_add(p * 2 + 1, d);
	t[p].add = 0;
}
void build(int l, int r, int p) {
	t[p].l = l;
	t[p].r = r;
	if (l == r) {
		t[p].sum = val[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, p * 2);
	build(mid + 1, r, p * 2 + 1);
	push_up(p);
}
void add_t(int l, int r, int p, int d) {
	if (t[p].l >= l && t[p].r <= r) {
		push_add(p, d);
		return;
	}
	push_down(p);
	int mid = (t[p].l + t[p].r) >> 1;
	if (l <= mid) {
		add_t(l, r, p * 2, d);
	}
	if (r > mid) {
		add_t(l, r, p * 2 + 1, d);
	}
	push_up(p);
}
ll query(int l, int r, int p) {
	if (t[p].l >= l && t[p].r <= r) {
		return t[p].sum;
	}
	push_down(p);
	int mid = (t[p].l + t[p].r) >> 1;
	if (r <= mid) {
		return query(l, r, p * 2);
	}
	else {
		if (l > mid) {
			return query(l, r, p * 2 + 1);
		}
		else {
			return query(l, r, p * 2) + query(l, r, p * 2 + 1);
		}
	}
}
void add(int x, int y) {
	g[x].push_back(y);
	g[y].push_back(x);
}
void dfs(int u, int f) {
	lx[u] = ++tot;
	val[tot] = a[u];
	for (int i = 0; i < g[u].size(); i++) {
		int v;
		v = g[u][i];
		if (f == v)continue;
		dfs(v, u);
	}
	rx[u] = tot;
}
int main() {
	scanf("%d%d%d", &n, &m, &root);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	for (int i = 1; i < n; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		add(x, y);
	}
	dfs(root, 0);
	build(1, n, 1);
	while (m--) {
		int x;
		scanf("%d", &x);
		if (x == 1) {
			ll k, d;
			scanf("%d%d", &k, &d);
			add_t(lx[k], rx[k], 1, d);
		}
		else {
			ll k;
			scanf("%d", &k);
			printf("%lld\n", query(lx[k], rx[k], 1));
		}
	}
	return 0;
}