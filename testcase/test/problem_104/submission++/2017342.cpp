#include <bits/stdc++.h>
#define IL inline
#define LL long long
#define eb emplace_back
#define L(i, j, k) for (int i = (j); i <= (k); ++i)
#define R(i, j, k) for (int i = (j); i >= (k); --i)
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

constexpr int N = 1e5 + 9;

int rt, tot;

struct {
	int lc, rc, sz, v;
	unsigned p;
} tr[N];

#define ls(p) tr[p].lc
#define rs(p) tr[p].rc

IL int New (int v) {
	++tot;
	tr[tot] = {0, 0, 1, v, rng()};
	return tot;
} 

IL void pushup (int p) {
	tr[p].sz = tr[ls(p)].sz + tr[rs(p)].sz + 1;
}

IL void splits (int p, int k, int &x, int &y) {
	if (!p) {
		x = y = 0;
		return;
	}
	if (tr[ls(p)].sz + 1 <= k) {
		x = p;
		splits(rs(p), k - tr[ls(p)].sz - 1, rs(x), y);
	} else {
		y = p;
		splits(ls(p), k, x, ls(y));
	}
	pushup(p);
}

IL void splitv (int p, int k, int &x, int &y) {
	if (!p) {
		x = y = 0;
		return;
	}
	if (tr[p].v <= k) {
		x = p;
		splitv(rs(p), k, rs(x), y);
	} else {
		y = p;
		splitv(ls(p), k, x, ls(y));
	}
	pushup(p);
}

IL int merge (int x, int y) {
	if (!x || !y) {
		return x | y;
	}
	if (tr[x].p < tr[y].p) {
		rs(x) = merge(rs(x), y);
		pushup(x);
		return x;
	} else {
		ls(y) = merge(x, ls(y));
		pushup(y);
		return y;
	}
}

IL void ins (int k) {
	int x, y;
	splitv(rt, k, x, y);
	rt = merge(x, merge(New(k), y));
}

IL void era (int k) {
	int x, y, z;
	splitv(rt, k, x, y);
	splits(x, tr[x].sz - 1, x, z);
	if (tr[z].v == k) {
		rt = merge(x, y);
	} else {
		rt = merge(x, merge(z, y));
	}
}

IL int rk (int k) {
	int x, y;
	splitv(rt, k - 1, x, y);
	int r = tr[x].sz + 1;
	rt = merge(x, y);
	return r;
}

IL int kth (int k) {
	int x, y, z;
	splits(rt, k, x, y);
	splits(x, k - 1, x, z);
	int r = tr[z].v;
	rt = merge(x, merge(z, y));
	return r;
}

IL int nxt (int k) {
	int x, y, z;
	splitv(rt, k, x, y);
	splits(y, 1, z, y);
	int r = tr[z].v;
	rt = merge(x, merge(z, y));
	return r;
}

IL int pre (int k) {
	int x, y, z;
	splitv(rt, k - 1, x, y);
	splits(x, tr[x].sz - 1, x, z);
	int r = tr[z].v;
	rt = merge(x, merge(z, y));
	return r;
}

IL void dfs (int u) {
	if (ls(u)) {
		dfs(ls(u));
	}
	cout << tr[u].v << ' ';
	if (rs(u)) {
		dfs(rs(u));
	}
}

int main () {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	while (n--) {
		int o, x;
		cin >> o;
		switch (o) {
			case 1 : 
				cin >> x;
				ins(x);
				break;
			case 2 :
				cin >> x;
				era(x);
				break;
			case 3 :
				cin >> x;
				cout << rk(x) << '\n';
				break;
			case 4:
				cin >> x;
				cout << kth(x) << '\n';
				break;
			case 5:
				cin >> x;
				cout << pre(x) << '\n';
				break;
			case 6:
				cin >> x;
				cout << nxt(x) << '\n';
		}



	}
}

