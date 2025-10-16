#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
template <typename T> inline void read(T &x){
	static char c = getchar(); bool f = 0; x = 0;
	for (; c > 57 || c < 48; c = getchar()) f |= c == '-';
	for (; c >= 48 && c <= 57; c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
	if (f) x = -x;
}
template <typename T, typename ...Args> inline void read(T &x, Args &...args){
	read(x), read(args...);
}

const int N = 3e5 + 5;
const ll mod = 998244353;
int n;
vector <int> e[N], g[N]; 
struct Boom{
	ll x, r, v; int id;
}a[N];
int in[N], vis[N], Bl[N];
ll val[N], ans[N], tmp[N];
ll f(int x, int y){
	return ((a[x].v ^ a[y].v) + (a[x].v * a[y].v % mod)) % mod;
}

void dfs(int u, int rt){
	if(Bl[u] == rt) return ;
	if(u != rt) val[rt] = max(val[rt], val[u] + f(rt, u));
	Bl[u] = rt;
	for (auto v : g[u]) if(vis[v]){
		dfs(v, rt);
	}
}

void bfs()
{
	queue <int> q;
	
	for(int i = 1; i <= n; i++) if(!in[i]) q.emplace(i); 
	while(!q.empty()){
		int u = q.front(); q.pop();
		dfs(u, u);
		vis[u] = 1;
		ans[a[u].id] = val[u];
		for (auto v : e[u]){
			in[v]--;
			if(!in[v]) q.emplace(v);
		}
	}
}

signed main()
{
	read(n);
	for (int i = 1; i <= n; i++) read(a[i].x);
	for (int i = 1; i <= n; i++) read(a[i].r);
	for (int i = 1; i <= n; i++) read(a[i].v);
	for (int i = 1; i <= n; i++) a[i].id = i;

	sort(a + 1, a + 1 + n, [&] (Boom a, Boom b){
		if(a.x != b.x) return a.x < b.x;
		if(a.r != b.r) return a.r < b.r;
		return a.v < b.v;
	});
	
	for (int i = 1; i <= n; i++) tmp[i] = a[i].x;
	tmp[n + 1] = LONG_LONG_MAX / 2;
	for (int i = 1; i <= n; i++){
		int l = lower_bound(tmp + 1, tmp + 1 + n, a[i].x - a[i].r) - tmp;
		int r = upper_bound(tmp + 1, tmp + 1 + n + 1, a[i].x + a[i].r) - tmp - 1;
		for (int j = l; j <= r; j++) if(i != j) {
			e[i].emplace_back(j), in[j]++;
			g[j].emplace_back(i);	
		}
	}
	
	bfs();	
	
	for (int i = 1; i <= n; i++) cout << ans[i] << "\n";

	return 0;
}