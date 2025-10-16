#include <bits/stdc++.h>
using namespace std;
#define IC isdigit(c)
#define GC c=getchar()
void rd(auto &x) { char GC; bool f = 0; x = 0;
	for (; !IC; GC) if (c == '-') f = 1;
	for (; IC; GC) x = x * 10 + c - 48;
	if (f) x = -x;
}
void rd(auto &x, auto &...y) { rd(x); rd(y...); }
#define U(i,l,r) for (int i(l),END##i(r); i<=END##i; ++i)
#define D(i,l,r) for (int i(l),END##i(r); i>=END##i; --i)
using ll = long long;

const int N = 100005;
int n, m; vector<int> g[N], dir[N];
#define rk(u) make_pair(g[u].size(), u)

int main() {
	rd(n, m);
	U (i, 1, m) {
		int u, v; rd(u, v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	U (u, 1, n) for (int v : g[u])
		if (rk(u) < rk(v))
			dir[u].push_back(v);
	
	ll cnt[N] {}, ans = 0;
	U (u, 1, n) {
		for (int v : g[u]) {
			for (int w : dir[v]) if (rk(u) < rk(w))
				ans += cnt[w];
			for (int w : dir[v]) if (rk(u) < rk(w))
				++cnt[w];
		}
		for (int v : g[u]) for (int w : dir[v])
			cnt[w] = 0;
	}
	cout << ans << endl;
}