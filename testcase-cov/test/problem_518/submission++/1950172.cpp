#include <cstdio>
#include <set>
#include <map>

const int mod = 19260817;
inline int qpow(int a, int b) {
	int ret = 1;
	while (b) {
		if (b & 1) ret = 1ll * ret * a % mod;
		a = 1ll * a * a % mod, b >>= 1;
	}
	return ret;
}
int val[4000005], ls[4000005], rs[4000005], pre[100005], preinv[100005], tot;
std::map<int, int> rt;
int query(int p, int l, int r) {return p ? val[p] : 1ll * pre[r] * preinv[l - 1] % mod;}
void update(int &p, int l, int r, int x, int v) {
	if (!p) p = ++ tot;
	if (l == r) {val[p] = v; return;}
	int mid = l + r >> 1;
	x <= mid ? update(ls[p], l, mid, x, v) : update(rs[p], mid + 1, r, x, v);
	val[p] = 1ll * query(ls[p], l, mid) * query(rs[p], mid + 1, r) % mod;
}
int len[100005], n, types, ans;
std::map<int, std::set<int> > s[100005];
std::map<int, int> prod[100005];
inline int calc(int n) {return (1ll * n * (n + 1) >> 1) % mod;}
void insert(int i, int x, int j) {
	if (!rt[x]) ++ types;
	else ans = (ans + query(rt[x], 1, n)) % mod;
	auto it = s[i][x].insert(j).first;
	int pr = (it == s[i][x].begin() ? 0 : *std::prev(it)), nx = (it == -- s[i][x].end() ? len[i] + 1 : *std::next(it));
	if (!prod[i].count(x)) prod[i][x] = calc(nx - pr - 1);
	prod[i][x] = (1ll * prod[i][x] - 1ll * calc(nx - pr - 1) + 1ll * calc(j - pr - 1) + 1ll * calc(nx - j - 1)) % mod;
	prod[i][x] = (prod[i][x] + mod) % mod;
	update(rt[x], 1, n, i, prod[i][x]), ans = (ans - query(rt[x], 1, n) + mod) % mod;
}
void erase(int i, int x, int j) {
	ans = (ans + query(rt[x], 1, n)) % mod;
	auto it = s[i][x].find(j);
	int pr = (it == s[i][x].begin() ? 0 : *std::prev(it)), nx = (it == -- s[i][x].end() ? len[i] + 1 : *std::next(it));
	prod[i][x] = (1ll * prod[i][x] + 1ll * calc(nx - pr - 1) - 1ll * calc(j - pr - 1) - 1ll * calc(nx - j - 1)) % mod;
	prod[i][x] = (prod[i][x] + mod) % mod;
	s[i][x].erase(it);
	update(rt[x], 1, n, i, prod[i][x]), ans = (ans - query(rt[x], 1, n) + mod) % mod;
}
int *a[100005];

int main() {
	int q; scanf("%d%d", &n, &q);
	pre[0] = preinv[0] = 1;
	for (int i = 1; i <= n; ++ i) {
		scanf("%d", len + i), a[i] = new int[len[i] + 1];
		preinv[i] = qpow(pre[i] = 1ll * pre[i - 1] * calc(len[i]) % mod, mod - 2);
	}
	for (int i = 1; i <= n; ++ i)
		for (int j = 1, x; j <= len[i]; ++ j) scanf("%d", &x), a[i][j] = x, insert(i, x, j);
	int res = (1ll * pre[n] * types + ans) % mod;
	printf("%d\n", res);
	while (q --) {
		int i, j, x; scanf("%d%d%d", &i, &j, &x);
		erase(i, a[i][j], j), insert(i, a[i][j] = x, j);
		res = (1ll * pre[n] * types + ans) % mod;
		printf("%d\n", res);
	}
	return 0;
}