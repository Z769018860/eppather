#include<bits/stdc++.h>
const int N = 500005;
using ll = long long;
using std::cin;
using std::cout;

struct pr {
	int cnt; ll sum, sumv;
	void ins(pr y) { cnt += y.cnt; sum += y.sum; }
	void del(pr y) { cnt -= y.cnt; sum -= y.sum; }
	pr v(int w) const { return {cnt, sum + (ll) cnt * w, w}; }
} vs[N];

pr operator + (const pr & x, const pr & y) {
	return {x.cnt + y.cnt, x.sum + y.sum + x.sumv * y.cnt, x.sumv + y.sumv};
}

pr sub[N][2];

int v[N];
int fa[N], son[N][2], rev[N];

int get(int x, int p = 1) {
	return son[fa[x]][p] == x;
}
int isroot(int x) {
	return !(get(x) || get(x, 0));
}

void update(int x) {
	sub[x][0] = sub[son[x][0]][0] + vs[x].v(v[x]) + sub[son[x][1]][0];
	sub[x][1] = sub[son[x][1]][1] + vs[x].v(v[x]) + sub[son[x][0]][1];
}
void put(int x) {
	if(!x) return ;
	std::swap(son[x][0], son[x][1]);
	std::swap(sub[x][0], sub[x][1]);
	rev[x] ^= 1;
}
void down(int x) {
	if(rev[x]) {
		put(son[x][0]);
		put(son[x][1]);
		rev[x] = 0;
	}
}
void rotate(int x) {
	int y = fa[x], z = fa[y], b = get(x);
	if(!isroot(y)) son[z][get(y)] = x;
	son[y][b] = son[x][!b], son[x][!b] = y;
	fa[son[y][b]] = y, fa[y] = x, fa[x] = z;
	update(y);
}
void downall(int x) {
	if(!isroot(x)) downall(fa[x]);
	down(x);
}
void splay(int x) {
	for(downall(x);!isroot(x);rotate(x)) if(!isroot(fa[x]))
		rotate(get(x) ^ get(fa[x]) ? x : fa[x]);
	update(x);
}
void access(int x) {
	for(int t = 0;x;) {
		splay(x);
		if(son[x][1]) vs[x].ins(sub[son[x][1]][0]);
		if(t) vs[x].del(sub[t][0]);
		son[x][1] = t, t = x, x = fa[x];
	}
}
void makeroot(int x) {
	access(x), splay(x), put(x);
}
void link(int x, int y) {
	makeroot(x); makeroot(y);
	fa[x] = y;
	vs[y].ins(sub[x][0]);
	update(y);
}
int n, m, k;
int col[N];
int main() {
	std::ios::sync_with_stdio(false), cin.tie(0);
	cin >> n >> m >> k;
	for(int i = 1, u, v, w;i <= m;++i) {
		cin >> u >> v >> w;
		::v[i + n] = w;
		update(i + n);
		link(u, i + n);
		link(v, i + n);
	}
	for(int i = 1;i <= k;++i) {
		char op;
		cin >> op;
		if(op == 'L') {
			int u, v, w;
			cin >> u >> v >> w;
			::v[i + n + m] = w;
			update(i + n + m);
			link(u, i + n + m);
			link(v, i + n + m);
		}
		if(op == 'C') {
			int x, y;
			cin >> x >> y;
			makeroot(x); access(y); splay(y);
			int d = son[y][0];
			if(d == x) d = son[d][1];
			splay(d);
			son[d][0] = son[d][1] = 0;
			fa[x] = fa[y] = 0;
			update(x);
			update(y);
		}
		if(op == 'F') {
			int x;
			cin >> x;
			makeroot(x);
			if(col[x] ^= 1) {
				vs[x].cnt += 1;
			} else {
				vs[x].cnt -= 1;
			}
			update(x);
		}
		if(op == 'Q') {
			int x;
			cin >> x;
			makeroot(x);
			cout << sub[x][0].sum << '\n';
		}
	}
}
