#include <cstdio>
#include <algorithm>

using std::swap;

struct LCT {
	int ch[300005][2], fa[300005], sum[300005], a[300005], stk[300005];
	bool tag[300005];
	void flip(int x) {swap(ch[x][0], ch[x][1]), tag[x] ^= 1;}
	void pushdown(int x) {
		if (tag[x]) flip(ch[x][0]), flip(ch[x][1]), tag[x] = 0;
	}
	void pushup(int x) {sum[x] = sum[ch[x][0]] ^ sum[ch[x][1]] ^ a[x];}
	int typ(int x) {return ch[fa[x]][1] == x;}
	bool isroot(int x) {return ch[fa[x]][0] != x && ch[fa[x]][1] != x;}
	void rotate(int x) {
		int y = fa[x], z = fa[y], d = typ(x), d2 = (isroot(y) ? -1 : typ(y));
		ch[y][d] = ch[x][!d]; if (ch[x][!d]) fa[ch[x][!d]] = y;
		ch[x][!d] = y, fa[y] = x, fa[x] = z; if (d2 != -1) ch[z][d2] = x;
		pushup(y), pushup(x);
	}
	void splay(int x) {
		int y = x, top = 0; while (x) stk[++ top] = x, x = (isroot(x) ? 0 : fa[x]);
		while (top) pushdown(stk[top --]);
		x = y;
		for (int f; f = (isroot(x) ? 0 : fa[x]); rotate(x))
			if (!isroot(f)) rotate(typ(x) == typ(f) ? f : x);
	}
	void access(int x) {for (int y = 0; x; y = x, x = fa[x]) splay(x), ch[x][1] = y, pushup(x);}
	void makeroot(int x) {access(x), splay(x), flip(x);}
	int find(int x) {access(x), splay(x); while (ch[x][0]) pushdown(x), x = ch[x][0]; splay(x); return x;}
	void link(int u, int v) {makeroot(u); if (find(v) != u) fa[u] = v;}
	void split(int u, int v) {makeroot(u), access(v), splay(v);}
	void cut(int u, int v) {
		if (find(u) != find(v)) return;
		split(u, v); if (ch[v][0] == u && !ch[u][1]) ch[v][0] = fa[u] = 0, pushup(v);
	}
	int query(int u, int v) {split(u, v); return sum[v];}
	void change(int x, int y) {splay(x), a[x] = y, pushup(x);}
} lct;

int main() {
	int n, q; scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; ++ i) scanf("%d", lct.a + i);
	while (q --) {
		int op, x, y; scanf("%d%d%d", &op, &x, &y);
		if (op == 0) printf("%d\n", lct.query(x, y));
		else if (op == 1) lct.link(x, y);
		else if (op == 2) lct.cut(x, y);
		else lct.change(x, y);
	}
}