#include <bits/stdc++.h>
#define eb emplace_back
#define mp make_pair
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
bool Mbe;

mt19937 rnd(time(0));
const int N = 1e5 + 100;

namespace Treap {
	int tot, rt;
	struct T {
		int lc, rc, sz, vl, rd, rv;
		T () { }
		T (int _lc, int _rc, int _sz, int _vl, int _rd, int _rv) :
			lc(_lc), rc(_rc), sz(_sz), vl(_vl), rd(_rd), rv(_rv) { }
	} t[N];
	#define ls(x) t[x].lc
	#define rs(x) t[x].rc
	int mk(int k) { return t[++tot] = T(0, 0, 1, k, rnd(), 0), tot; }
	void pup(int x) { t[x].sz = t[ls(x)].sz + t[rs(x)].sz + 1; }
	void pdn(int x) { if (t[x].rv) t[x].rv = 0, swap(ls(x), rs(x)), t[ls(x)].rv ^= 1, t[rs(x)].rv ^= 1; }
	void spl(int p, int k, int &x, int &y) {
		if (!p) return x = y = 0, void(); pdn(p);
		if (k > t[ls(p)].sz) x = p, spl(rs(x), k - t[ls(p)].sz - 1, rs(x), y);
		else y = p, spl(ls(y), k, x, ls(y));
		pup(p);
	}
	int mrg(int x, int y) {
		if (!x || !y) return x | y;
		if (t[x].rd < t[y].rd) return pdn(x), rs(x) = mrg(rs(x), y), pup(x), x;
		else return pdn(y), ls(y) = mrg(x, ls(y)), pup(y), y;
	}
	void rev(int l, int r) {
		int x, y, z; 
		spl(rt, r, x, z), spl(x, l - 1, x, y);
		t[y].rv ^= 1, rt = mrg(mrg(x, y), z);
	}
	void out(int u) {
		if (!u) return;
		pdn(u);
		out(ls(u));
		cout << t[u].vl << ' ';
		out(rs(u));
	}
}
using namespace Treap;

int n, q;

void solve() {
	cin >> n >> q;
	for (int i = 1; i <= n; i++) rt = mrg(rt, mk(i));
	while (q--) { int l, r; cin >> l >> r, rev(l, r); }
	out(rt);
}

bool Med;
int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	#ifdef FILE
		freopen(".in", "r", stdin);
		freopen(".out", "w", stdout);
	#endif
	int T = 1;

	while (T--) solve();
	return 0;
}
