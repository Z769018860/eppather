#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;

int read(){
	int x = 0; char c = getchar();
	while(!isdigit(c))c = getchar();
	do{x = x * 10 + (c ^ 48); c = getchar();}while(isdigit(c));
	return x;
}
const int maxn = 2e5 + 55, mod = 998244353;
int qpow(int x, int y){
	int ans = 1;
	for(; y; y >>= 1, x = 1ll * x * x % mod)if(y & 1)ans = 1ll * ans * x % mod;
	return ans;
}
int inv6, n, m, q;
int calc(int x){return 1ll * x * (x + 1) % mod * (x + x + 1) % mod * inv6 % mod;}
void add(int &x, int y){x += y; if(x >= mod)x -= mod;}
int p[55], cnt;
void init(int x){
	for(int i = 1; i <= cnt; ++i)while(x % p[i] == 0)x /= p[i];
	for(int i = 2; i * i <= x; ++i)if(x % i == 0){
		p[++cnt] = i; while(x % i == 0)x /= i;
	}
	if(x != 1)p[++cnt] = x;
}
int a[maxn], tot;
void dfs(int pp, ll val){
	if(pp == cnt + 1){a[++tot] = val; return;}
	while(val <= n){dfs(pp + 1, val); val = val * p[pp];}
}
unordered_map<int, int>f, g;
int qry[maxn];
int pn[maxn], cp;
int main(){
	n = read(), m = read(), q = read(); inv6 = qpow(6, mod - 2);
	for(int i = 1; i <= m; ++i){
		int p = read(), x = read();
		add(f[p], x); init(p);
	}
	for(int i = 1; i <= q; ++i)init(qry[i] = read());
	dfs(1, 1); sort(a + 1, a + tot + 1);
	for(int l = 1, r; l <= n; l = r + 1){r = n / (n / l); pn[++cp] = n / l;}
	sort(pn + 1, pn + cp + 1);
	for(int i = 1; i <= cp; ++i)g[pn[i]] = calc(pn[i]);
	for(int i = 1; i <= cnt; ++i)
		for(int j = cp; j >= 1; --j)
			add(g[pn[j]], mod - (1ll * g[pn[j] / p[i]] * p[i] % mod * p[i] % mod));
	for(int i = 1; i <= cnt; ++i)
		for(int j = 1; j <= tot; ++j)if(a[j] % p[i] == 0)
			add(f[a[j]], 1ll * f[a[j] / p[i]] * p[i] % mod);
	for(int i = 1; i <= tot; ++i)f[a[i]] = 1ll * f[a[i]] * g[n / a[i]] % mod;
	for(int i = 1; i <= cnt; ++i)
		for(int j = tot; j >= 1; --j)if(1ll * a[j] * p[i] <= n)
			add(f[a[j]], 1ll * f[a[j] * p[i]] * p[i] % mod);
	for(int i = 1; i <= q; ++i)printf("%d\n",f[qry[i]]);
	return 0;
}