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
		int lc, rc, sz, vl, rd;
		T () { }
		T (int _lc, int _rc, int _sz, int _vl, int _rd) :
			lc(_lc), rc(_rc), sz(_sz), vl(_vl), rd(_rd) { }
	} t[N];
	#define ls(x) t[x].lc
	#define rs(x) t[x].rc
	int mk(int k) { return t[++tot] = T(0, 0, 1, k, rnd()), tot; }
	void pup(int x) { t[x].sz = t[ls(x)].sz + t[rs(x)].sz + 1; }
	void spl(int p, int k, int &x, int &y) {
		if (!p) return x = y = 0, void();
		if (t[p].vl <= k) x = p, spl(rs(x), k, rs(x), y);
		else y = p, spl(ls(y), k, x, ls(y));
		pup(p);
	}
	int mrg(int x, int y) {
		if (!x || !y) return x | y;
		if (t[x].rd < t[y].rd) return rs(x) = mrg(rs(x), y), pup(x), x;
		else return ls(y) = mrg(x, ls(y)), pup(y), y;
	}
	void ins(int k) {
		int x, y; spl(rt, k, x, y);
		rt = mrg(mrg(x, mk(k)), y);
	}
	void del(int k) {
		int x, y, z; 
		spl(rt, k - 1, x, y), spl(y, k, y, z);
		y = mrg(ls(y), rs(y)), rt = mrg(x, mrg(y, z));
	}
	int rk(int k) {
		int x, y, res; spl(rt, k - 1, x, y);
		res = t[x].sz + 1, rt = mrg(x, y);
		return res;
	}
	int id(int u, int k) {
		int x = u;
		while (1) {
			if (k <= t[ls(x)].sz) x = ls(x);
			else if (k == t[ls(x)].sz + 1) return t[x].vl;
			else k -= t[ls(x)].sz + 1, x = rs(x);
		}
	}
	int pr(int k) {
		int x, y, res; spl(rt, k - 1, x, y);
		res = id(x, t[x].sz), rt = mrg(x, y);
		return res;
	}
	int nx(int k) {
		int x, y, res; spl(rt, k, x, y);
		res = id(y, 1), rt = mrg(x, y);
		return res;
	}
}

void solve() {
	int n; cin >> n;
	while (n--) {
		int op, x; cin >> op >> x;
		if (op == 1) Treap::ins(x);
		else if (op == 2) Treap::del(x);
		else if (op == 3) cout << Treap::rk(x) << '\n';
		else if (op == 4) cout << Treap::id(Treap::rt, x) << '\n';
		else if (op == 5) cout << Treap::pr(x) << '\n';
		else cout << Treap::nx(x) << '\n';
	}
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