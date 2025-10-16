#include <bits/stdc++.h>
using i64 = long long;

constexpr int N = 3e5 + 10;
struct node {
	int ch[2], fa, siz;
	int v, sum;
	int rev;
	int &operator [](const int &x) {return ch[x];}
} tr[N];

inline int get(int x) {
	return tr[tr[x].fa][1] == x;
}

inline bool isRoot(int x) {return tr[tr[x].fa][0] != x && tr[tr[x].fa][1] != x;}
inline void pushup(int u) {
	auto &ls = tr[tr[u][0]], &rs = tr[tr[u][1]];
	tr[u].sum = ls.sum ^ rs.sum ^ tr[u].v;
	tr[u].siz = ls.siz + rs.sum + 1;
}

inline void rotate(const int &x) {
	int y = tr[x].fa, z = tr[y].fa;
	int d = get(x);
	if (!isRoot(y))
		tr[z][get(y)] = x;
	tr[y][d] = tr[x][d ^ 1];
	tr[tr[x][d ^ 1]].fa = y;
	tr[x][d ^ 1] = y;
	tr[y].fa = x;
	tr[x].fa = z;
	pushup(y), pushup(x);
}

inline void ApplyReverse(int u) {
	std::swap(tr[u][0], tr[u][1]);
	tr[u].rev ^= 1;
}

inline void pushdown(int u) {
	if (tr[u].rev) {
		if (tr[u][0])	ApplyReverse(tr[u][0]);
		if (tr[u][1])	ApplyReverse(tr[u][1]);
		tr[u].rev = 0;
	}
}

inline void DownLoad(const int &x) {
	if (!isRoot(x))	DownLoad(tr[x].fa);
	pushdown(x);
}


inline void splay(const int &x) {
	DownLoad(x);
	while (!isRoot(x)) {
		int y = tr[x].fa, z = tr[y].fa;
		if (!isRoot(y))
			get(x) == get(y) ? rotate(y) : rotate(x);
		rotate(x);
	}
}
inline int Access(int x) {
	int p;
	for (p = 0; x; p = x, x = tr[x].fa)
		splay(x), tr[x][1] = p, pushup(x);
	return p;
}


inline void MakeRoot(int x) {
	Access(x);
	splay(x);
	ApplyReverse(x);
}

inline int Find(int x) {
	Access(x), splay(x);
	while (tr[x][0])	pushdown(x), x = tr[x][0];
	splay(x);
	return x;
}

inline void split(int x, int y) {MakeRoot(x), Access(y), splay(y);}

inline void Link(int x, int y) {
	MakeRoot(x);
	if(Find(y) != x)	tr[x].fa = y;
}

inline void Cut(int x, int y) {
	MakeRoot(x);
	if (Find(y) == x && tr[y].fa == x && !tr[y][0])
		tr[y].fa = tr[x][1] = 0, pushup(x);
}

int main() {
#ifdef AckerlannaHeratino
	freopen("input.txt", "r", stdin);
#endif
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n, m;
	std::cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		std::cin >> tr[i].v;
		tr[i].siz = 1, tr[i].sum = tr[i].v;
	}
	for (int i = 1; i <= m; i++) {
		int op, x, y;
		std::cin >> op >> x >> y;
		if (op == 0) {
			split(x, y);
			std::cout << tr[y].sum << '\n';
		} else if (op == 1) {
			Link(x, y);
		} else if (op == 2) {
			Cut(x, y);
		} else {
			Access(x);
			splay(x);
			tr[x].v = y;
			pushup(x);
		}
	}
	return 0;
}