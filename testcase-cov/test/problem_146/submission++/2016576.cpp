


#include <iostream>
#include <cstdio>
#define main Main();signed main(){ios::sync_with_stdio(0);cin.tie(0);return Main();}signed Main
using namespace std;

namespace Fast{
	const int MAX = 1 << 24;
	
	#ifndef LOCAL
	inline char getchar(void){
		static char buf[MAX], *p1 = buf, *p2 = buf;
		return (p1 == p2) && (p2 = (p1 = buf) + fread(buf, 1, MAX, stdin), p1 == p2) ? EOF : *p1++;
	}
	#endif
	
	char obuf[MAX], *o = obuf;
	inline void flush(void){
		fwrite(obuf, 1, o - obuf, stdout), o = obuf;
	}
	inline void putchar(const char c){
		*o++ = c;
		if (o - obuf == MAX) flush();
	}
	
	template <typename T> constexpr inline T abs(T x) { return x > 0 ? x : -x; }
	template <typename T1, typename T2> constexpr inline auto max(T1 a, T2 b) { return a > b ? a : b; }
	template <typename T1, typename T2> constexpr inline auto min(T1 a, T2 b) { return a < b ? a : b; }
	template <typename T, typename... Types> constexpr inline auto max(T a, Types... b) { auto res = max(b...); return res > a ? res : a; }
	template <typename T, typename... Types> constexpr inline auto min(T a, Types... b) { auto res = min(b...); return res < a ? res : a; }
	constexpr inline bool isdigit(const char c) { return c >= '0' && c <= '9'; }
	constexpr inline bool empty(const char c){ return c == '\r' || c == '\n' || c == ' ' || c == '\t' || c == '\0' || c == EOF; }
	
	inline int read(){ return 0; } template <typename T, typename... Types>
	inline int read(T &x, Types&... args) {
		if constexpr (is_same<typename decay<T>::type, char>::value)
		{ for (x=getchar();empty(x);x=getchar()) if (x == EOF) return EOF; }
		else if constexpr (is_same<typename decay<T>::type, char*>::value){
		for (x[0]=0;empty(x[0]);x[0]=getchar()) if (x[0] == EOF) return x[0] = 0, EOF;
		for (unsigned i=0;;x[++i]=getchar()) if (empty(x[i])) return x[i] = 0, read(args...);
		} else { x = 0; char c = 0, f = 0;
	    for (;!isdigit(c);c=getchar()) if (f |= c == '-', c == EOF) return EOF;
	    for (; isdigit(c);c=getchar()) x = (x << 3) + (x << 1) + (c ^ 48);
	    f && (x = -x); } return read(args...);
	}
	
	inline void write(){} template <typename T, typename... Types>
	inline void write(T x, Types... args){
		if constexpr (is_same<typename decay<T>::type, char>::value)
		return putchar(x), write(args...);
		if constexpr (is_same<const char*, T>::value || is_same<char*, T>::value)
		{ for (unsigned i=0;x[i];putchar(x[i++])); } else
		{ (x < 0) && (putchar('-'), 5201314);
		static short Stack[50], top = 0;
		do Stack[++top] = x % 10, x /= 10; while (x);
	    while (top) putchar(abs(Stack[top--]) | 48); } write(args...);
	}
	
	#undef main
	#define main Main(); signed main() { return atexit(flush), Main(); } signed Main
}

using namespace Fast;

#include <vector>

const int N = 1000010;

int n, m, root;
int v[N];

struct node{
	int to, nxt;
} edge[N << 1];
int eid, head[N];
void add(int u, int v){
	edge[++eid] = node({v, head[u]});
	head[u] = eid;
}

int fa[N];
int find(int x){
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}

int L[N], R[N], timer;
int dpt[N];
int l[N];

int FFFFF[N][21];

int ans[N];
vector<pair<int, int> > qry[N];
int mark[N];
int F[N];

void dfs(int now, int faa){
	FFFFF[now][0] = faa;
	
	


	
	F[now] = faa;
	
	L[now] = ++timer, l[timer] = v[now];
	for (int i=head[now];i;i=edge[i].nxt){
		if (edge[i].to == faa) continue;
		dpt[edge[i].to] = dpt[now] + 1;
		dfs(edge[i].to, now);
	}
	R[now] = timer;
	
	


}

void tarjan(int now, int faa){
	mark[now] = 1;
	for (int i=head[now];i;i=edge[i].nxt){
		if (edge[i].to == faa) continue;
		tarjan(edge[i].to, now);
		fa[find(edge[i].to)] = find(now);
	}
	mark[now] = 2;
	for (auto [idx, b]: qry[now]) if (mark[b] == 2) ans[idx] = find(b);

}

constexpr inline int lowbit(int x){
	return x & -x;
}

struct Bit_Tree{
	long long tree[N];
	void modify(int p, long long v){
		if (!p) return;
		for (int i=p;i<=n;i+=lowbit(i)) tree[i] += v;
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

void modify(int a, int b, int v, int p){
	t1.modify(L[a],  v), t1.modify(L[b], v);
	t1.modify(L[p], -v), t1.modify(L[F[p]], -v);
	t2.modify(L[a],  v * 1ll * dpt[a]), t2.modify(L[b], 1ll * v * dpt[b]);
	t2.modify(L[p], -v * 1ll * dpt[p]), t2.modify(L[F[p]], -1ll * v * dpt[F[p]]);
}

long long query_point(int p){
	return t1.query(L[p], R[p]);
}

long long query_sum(int p){
	return t2.query(L[p], R[p]) - 1ll * t1.query(L[p], R[p]) * (dpt[p] - 1);
}

struct OP_QUESTION{
	int op, a, b, x;
} QQry[N];

int LLLLLLCA(int a, int b, int F[N][21]){
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

signed main() {


	
	read(n, m, root);
	for (int i=1;i<=n;++i) read(v[i]), fa[i] = i;
	for (int i=1;i<=n-1;++i){
		int u, v; read(u, v);
		add(u, v), add(v, u);
	}
	
	for (int i=1;i<=m;++i){
		int op, a, b, x; read(op);
		if (op == 1){
			read(a, b, x);
			qry[a].push_back({i, b});
			qry[b].push_back({i, a});
			QQry[i] = {1, a, b, x};

		} else if (op == 2){
			read(a), QQry[i] = {2, a, 0, 0};
		} else {
			read(a), QQry[i] = {3, a, 0, 0};
		}
	}
	
	dfs(root, 0);
	
	tarjan(root, 0);
	
	
	for (int k=1;k<=20;++k)
	for (int i=1;i<=n;++i)
		FFFFF[i][k] = FFFFF[FFFFF[i][k-1]][k-1];
	
	
	for (int i=1;i<=n;++i)
		modify(i, i, v[i], i);
	
	for (int i=1;i<=m;++i){
		if (QQry[i].op == 1){










			modify(QQry[i].a, QQry[i].b, QQry[i].x, ans[i]);
		} else if (QQry[i].op == 2){

			write(query_point(QQry[i].a), '\n');
		} else {
			write(query_sum(QQry[i].a), '\n');
		}
	}
	
	return 0;
}



