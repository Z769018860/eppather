


#include <iostream>
#include <cstdio>
#define debug(a) cerr<<"Line: "<<__LINE__<<" "#a<<endl

#define file(a) freopen(#a".in","r",stdin);freopen(#a".out","w",stdout)
#define main Main();signed main(){ios::sync_with_stdio(0);cin.tie(0);return Main();}signed Main
using namespace std;

namespace IO {
#define ll long long
	const int MAX = 1 << 24;
	char buf[MAX], *p1 = buf, *p2 = buf;
	char obuf[MAX], *o = obuf;
#ifdef LOCAL
#define gc() getchar()
#else
#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<23,stdin),p1==p2)?EOF:*p1++)
#endif
	template<typename T=int>
	inline T read() {
		T res = 0;
		int f = 1;
		char c = gc();
		while (!isdigit(c)) {
			if (c == '-') f = -1;
			c = gc();
		}
		while (isdigit(c)) {
			res = (res << 3) + (res << 1) + (c ^ 48);
			c = gc();
		}
		return res * f;
	}
	void print(ll x) {
		if (x > 9) print(x / 10);
		*o++ = (x % 10) + '0';
	}
	void pc(char c) {
		*o++ = c;
	}
	void flush() {
		fwrite(obuf, o - obuf, 1, stdout);
	}
	void write(ll x, char __ed) {
		if (x < 0) *o++ = '-', x = -x;
		print(x);
		pc(__ed);
	}
#undef ll
}
using namespace IO;

int n, m, root;
int v[1000010];

const int N = 1000010;
struct node{
	int to, nxt;
} edge[N << 1];
int eid, head[N];
void add(int u, int v){
	edge[++eid] = node({v, head[u]});
	head[u] = eid;
}

int F[N][21];

int L[N], R[N], timer;
int dpt[N];
int l[N];
void dfs(int now, int fa){
	L[now] = ++timer, l[timer] = v[now];
	for (int i=head[now];i;i=edge[i].nxt){
		if (edge[i].to == fa) continue;
		dpt[edge[i].to] = dpt[now] + 1;
		F[edge[i].to][0] = now;
		dfs(edge[i].to, now);
	}
	R[now] = timer;
}

constexpr inline int lowbit(int x){
	return x & -x;
}

int lca(int a, int b){
	if (a == b) return a;
	if (dpt[a] < dpt[b]) swap(a, b);
	for (int k=20;k>=0;--k){
		if (F[a][k] && dpt[F[a][k]] >= dpt[b]) a = F[a][k];
	}
	if (a == b) return a;
	for (int k=20;k>=0;--k){
		if (F[a][k] && F[b][k] && F[a][k] != F[b][k]) a = F[a][k], b = F[b][k];
	}
	return F[a][0];
}

struct Bit_Tree{
	long long tree[N];
	void modify(int p, long long v){
		if (!p) return;
		for (int i=p;i<=n;i+=lowbit(i)) tree[i] += v;
	}
	void modify(int l, int r, long long v){
		modify(l, v), modify(r + 1, -v);
	}
	long long query(int p){
		long long res = 0;
		for (int i=p;i;i^=lowbit(i)) res += tree[i];
		return res;
	}
	long long query(int l, int r){
		return query(r) - query(l - 1);
	}
} t1, t2;

long long query(int x){
	if (!x) return 0;
	return t1.query(L[x]) + 1ll * t2.query(L[x]) * (dpt[x] + 1);
}

signed main() {
		
	n = read(), m = read(), root = read();
	for (int i=1;i<=n;++i) v[i] = read();
	for (int i=1;i<=n-1;++i){
		int u = read(), v = read();
		add(u, v), add(v, u);
	}
	dfs(root, 0);
	
	for (int k=1;k<=20;++k)
	for (int i=1;i<=n;++i)
		F[i][k] = F[F[i][k-1]][k-1];
	
	for (int i=1;i<=n;++i) t1.modify(L[i], R[i], v[i]);
	
	for (int i=1;i<=m;++i){
		int op = read(), a, b, x;
		if (op == 1){
			a = read(), x = read();
			t1.modify(L[a], R[a], x);
		} else if (op == 2){
			a = read(), x = read();
			t1.modify(L[a], R[a], -1ll * dpt[a] * x);
			t2.modify(L[a], R[a], x);
		} else {
			a = read(), b = read();
			int p = lca(a, b);
			write(query(a) - query(p) + query(b) - query(F[p][0]), '\n');
		}
	}
	
	flush();
	return 0;
}
