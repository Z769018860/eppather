#include <bits/stdc++.h>

const int N = 3e5;

int n, m;
int a[N + 5];

struct node {
	int child[2], fath, val, sum, rev;
} t[N + 5];

int get(int u) {
	int fath = t[u].fath;
	if (t[fath].child[0] == u) return 0;
	if (t[fath].child[1] == u) return 1;
	return -1;
}

bool isRoot(int u) {
	return get(u) == -1;
}

void spread(int u) {
	std::swap(t[u].child[0], t[u].child[1]);
	t[u].rev ^= 1;
}

void pushup(int u) {
	int L = t[u].child[0];
	int R = t[u].child[1];
	t[u].sum = t[L].sum ^ t[R].sum ^ t[u].val;
}

void pushdown(int u) {
	if (t[u].rev) {
		spread(t[u].child[0]);
		spread(t[u].child[1]);
		t[u].rev = 0;
	}
}

void dfs(int u) {
	if (!isRoot(u)) {
		dfs(t[u].fath);
	}
	pushdown(u);
}

void setChild(int u, int fath, int type) {
	if (u) {
		t[u].fath = fath;
	}
	if (fath && type != -1) {
		t[fath].child[type] = u;
	}
}

void rotate(int u) {
	int fa = t[u].fath;
	int gfa = t[fa].fath;
	int tu = get(u);
	int tfa = get(fa);
	int v = t[u].child[tu ^ 1];
	setChild(v, fa, tu);
	setChild(fa, u, tu ^ 1);
	setChild(u, gfa, tfa);
	pushup(fa);
	pushup(u);
	pushup(gfa);
}

void splay(int u) {
	dfs(u);
	while (!isRoot(u)) {
		int fa = t[u].fath;
		if (isRoot(fa)) {
			rotate(u);
		} else {
			if (get(u) == get(fa)) {
				rotate(fa);
				rotate(u);
			} else {
				rotate(u);
				rotate(u);
			}
		}
	}
}

void access(int u) {
	int v = 0;
	while (u) {
		splay(u);
		setChild(v, u, 1);
		pushup(u);
		v = u;
		u = t[u].fath;
	}
}

void setRoot(int u) {
	access(u);
	splay(u);
	spread(u);
}

int getRoot(int u) {
	access(u);
	splay(u);
	while (true) {
		pushdown(u);
		if (t[u].child[0]) {
			u = t[u].child[0];
		} else {
			break;
		}
	}
	splay(u);
	return u;
}

void split(int x, int y) {
	setRoot(x);
	access(y);
	splay(y);
}

int query(int x, int y) {
	split(x, y);
	return t[y].sum;
}

void link(int x, int y) {
	if (getRoot(x) == getRoot(y)) return ;
	setRoot(x);
	t[x].fath = y;
}

void cut(int x, int y) {
	if (getRoot(x) != getRoot(y)) return ;
	split(x, y);
	if (t[x].fath != y) return ;
	if (t[x].child[1] != 0) return ;
	t[x].fath = 0;
	t[y].child[0] = 0;
	pushup(y);
}

void upd(int x, int y) {
	splay(x);
	t[x].val = y;
	pushup(x);
}

int main() {
	#ifdef LOCAL
		freopen("data.in", "r", stdin);

	#endif
	
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	
	std::cin >> n >> m;
	
	for (int i = 1; i <= n; i++)
		std::cin >> a[i];
	
	for (int i = 1; i <= n; i++) {
		t[i].val = a[i];
		t[i].sum = a[i];
	}
	
	int opt, x, y;
	
	while (m--) {
		std::cin >> opt >> x >> y;
		if (opt == 0) std::cout << query(x, y) << "\n";
		if (opt == 1) link(x, y);
		if (opt == 2) cut(x, y);
		if (opt == 3) upd(x, y);
	}
	
	return 0;
}
