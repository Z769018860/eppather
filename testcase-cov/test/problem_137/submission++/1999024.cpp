#include <bits/stdc++.h>
using namespace std;
namespace lgh {

const int N = 2e5 + 5, M = 1e5 + 5;

int n, m;
int w[N];

struct Side {
	int u, v, w;
};
Side s[M];

struct Edge {
	int to, pre;
};
Edge e1[N * 2];
int i1 = 1, h1[N];
void add1(int u, int v) {
	e1[++i1] = {v, h1[u]};
	h1[u] = i1;
}

int bel[N];
int getbel(int x) {
	if (x == bel[x]) return bel[x];
	return bel[x] = getbel(bel[x]);
}

int tn;
void exkru() {
	for (int i = 1; i <= 2 * n - 1; ++i) bel[i] = i;
	sort(s + 1, s + m + 1, [](Side a, Side b) { return a.w < b.w; });
	tn = n;
	for (int i = 1; i <= m; ++i) {
		int fu = getbel(s[i].u), fv = getbel(s[i].v);
		if (fu != fv) {
			bel[fu] = bel[fv] = ++tn;
			w[tn] = s[i].w;
			add1(tn, fu), add1(fu, tn);
			add1(tn, fv), add1(fv, tn);
			if (tn == 2 * n - 1) break;
		}
	}
}

int dep[N], dfn[N], rnk[N * 2], idx;
void dfs(int u, int lst) {
	rnk[++idx] = u, dfn[u] = idx;
	for (int i = h1[u]; i; i = e1[i].pre) {
		int v = e1[i].to;
		if (v == lst) continue;
		dep[v] = dep[u] + 1;
		dfs(v, u);
		rnk[++idx] = u;
	}
}
int lg[20], st[N * 2][20], mch[N * 2][20];
void init() {
	lg[0] = -1;
	for (int i = 1; i <= idx; ++i) {
		lg[i] = lg[i >> 1] + 1;
		st[i][0] = dep[rnk[i]];
		mch[i][0] = rnk[i];
	}
	for (int k = 1; k <= lg[idx]; ++k) {
		for (int i = 1; i + (1 << k) - 1 <= idx; ++i) {
			if (st[i][k - 1] < st[i + (1 << (k - 1))][k - 1]) {
				st[i][k] = st[i][k - 1];
				mch[i][k] = mch[i][k - 1];
			}
			else {
				st[i][k] = st[i + (1 << (k - 1))][k - 1];
				mch[i][k] = mch[i + (1 << (k - 1))][k - 1];
			}
		}
	}
}
int getlca(int x, int y) {
	int l = dfn[x], r = dfn[y];
	if (l > r) swap(l, r);
	int k = lg[r - l + 1];
	return st[l][k] < st[r - (1 << k) + 1][k] ? mch[l][k] : mch[r - (1 << k) + 1][k];
}

int A,B,C,P;
inline int rnd(){return A=(A*B+C)%P;}

void main() {
	scanf(" %d %d", &n, &m);
	for (int i = 1; i <= m; ++i) scanf(" %d %d %d", &s[i].u, &s[i].v, &s[i].w);
	exkru();
	dfs(getbel(1), 0), init();
	long long ans = 0;
	int Q; scanf(" %d %d %d %d %d", &Q, &A, &B, &C, &P); while (Q--) {
		int u=rnd()%n+1, v=rnd()%n+1;
		ans += w[getlca(u, v)];
	}
	printf("%lld\n", ans % 1000000007);
}
}
main() {
	
	return lgh::main(), 0;
}