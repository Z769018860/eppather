#include <cstdio>
#include <map>
using namespace std;
#define LL long long
const int N = 500010;
struct Edge {
	int u, v;
	bool operator < (const Edge &rhs) const {
		if(u != rhs.u) return u < rhs.u;
		return v < rhs.v;
	}
};
map<Edge, int> mp;
bool col[N], rev[N]; int stk[N];
LL suml[N], sumr[N], sum2[N], sval[N];
int ch[N][2], fa[N], val[N], cnt[N], cnt2[N];
int n, m, k, s;
inline void swap(int &x, int &y) {x ^= y; y ^= x; x ^= y;}
inline bool isroot(int x) {
	return ch[fa[x]][0] != x && ch[fa[x]][1] != x;
}
inline void pushup(int x) {
	sval[x] = val[x] + sval[ch[x][0]] + sval[ch[x][1]];
	cnt[x] = cnt[ch[x][0]] + cnt[ch[x][1]] + cnt2[x] + col[x];
	suml[x] = suml[ch[x][0]] + suml[ch[x][1]] + sum2[x] + 1ll * (sval[ch[x][0]] + val[x]) * (cnt[x] - cnt[ch[x][0]]);
	sumr[x] = sumr[ch[x][0]] + sumr[ch[x][1]] + sum2[x] + 1ll * (sval[ch[x][1]] + val[x]) * (cnt[x] - cnt[ch[x][1]]);
}
inline void pushrev(int x) {
	rev[x] = !rev[x];
	swap(ch[x][0], ch[x][1]);
	swap(suml[x], sumr[x]);
}
inline void pushdown(int x) {
	if(rev[x]) {
		if(ch[x][0]) pushrev(ch[x][0]);
		if(ch[x][1]) pushrev(ch[x][1]);
		rev[x] = false;
	}
}
inline void rotate(int x) {
	int y = fa[x]; int z = fa[y], k = (ch[y][1] == x); int w = ch[x][k ^ 1];
	if(!isroot(y)) ch[z][ch[z][1] == y] = x; ch[x][k ^ 1] = y; ch[y][k] = w;
	if(w) fa[w] = y; fa[y] = x; fa[x] = z;
	pushup(y); pushup(x);
}
inline void splay(int x) {
	int k = 1, y = x; stk[1] = x;
	while(!isroot(y)) stk[++k] = y = fa[y];
	while(k) pushdown(stk[k--]);
	while(!isroot(x)) {
		int y = fa[x]; int z = fa[y];
		if(!isroot(y)) rotate((ch[y][1] == x) ^ (ch[z][1] == y) ? x : y);
		rotate(x);
	}
}
inline void access(int x) {
	for(int y = 0; x; x = fa[y = x]) {
		splay(x);
		cnt2[x] += cnt[ch[x][1]] - cnt[y];
		sum2[x] += suml[ch[x][1]] - suml[y];
		ch[x][1] = y; pushup(x);
	}
}
inline void makeroot(int x) {
	access(x); splay(x);
	pushrev(x);
}
inline void split(int x, int y) {
	makeroot(x);
	access(y); splay(y);
}
inline void link0(int x, int y) {
	makeroot(x); makeroot(y);
	fa[x] = y;
	sum2[y] += suml[x]; cnt2[y] += cnt[x];
	pushup(y);
}
inline void cut0(int x, int y) {
	split(x, y);
	ch[y][0] = fa[x] = 0; pushup(y);
}
inline void link(int u, int v, int w) {
	if(u > v) swap(u, v);
	mp[(Edge){u, v}] = ++s;
	ch[s][0] = ch[s][1] = fa[s] = 0;
	val[s] = sval[s] = w; cnt[s] = cnt2[s] = 0;
	suml[s] = sumr[s] = sum2[s] = 0; col[s] = rev[s] = false;
	link0(u, s); link0(v, s);
}
inline void cut(int u, int v) {
	if(u > v) swap(u, v);
	int x = mp[(Edge){u, v}]; mp[(Edge){u, v}] = 0;
	cut0(u, x); cut0(v, x);
}
int main() {
	scanf("%d %d %d", &n, &m, &k); s = n;
	for(int x = 1; x <= n; ++x) {
		ch[x][0] = ch[x][1] = fa[x] = 0;
		val[x] = cnt[x] = cnt2[x] = 0;
		suml[x] = sumr[x] = sum2[x] = 0; col[x] = false;
	}
	for(int i = 1; i <= m; ++i) {
		int u, v, w; scanf("%d %d %d", &u, &v, &w);
		link(u, v, w);
	}
	while(k--) {
		char op[5]; int u, v, w;
		scanf("%s", op);
		if(op[0] == 'L') {
			scanf("%d %d %d", &u, &v, &w);
			link(u, v, w);
		} else if(op[0] == 'C') {
			scanf("%d %d", &u, &v);
			cut(u, v);
		} else if(op[0] == 'F') {
			scanf("%d", &u); makeroot(u);
			col[u] = !col[u]; pushup(u);
		} else {
			scanf("%d", &u); makeroot(u);
			printf("%lld\n", suml[u]);
		}
	}
	return 0;
}