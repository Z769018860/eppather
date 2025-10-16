#include <bits/stdc++.h>

const int mod = 998244353;
const int maxn = 3005;

void add(int& x,int y) {
	x += y;
	if(x >= mod)
		x -= mod;
	return ;
}

void sub(int& x,int y) {
	x -= y;
	if(x < 0)
		x += mod;
	return ;
}

int power(int x,int y) {
	int ans = 1;
	for(;y;y >>= 1) {
		if(y & 1)
			ans = 1ll * ans * x % mod;
		x = 1ll * x * x % mod;
	}
	return ans;
}

int n,m,f[maxn],sum[maxn],suf[maxn];
struct node {
	int x,y;
	node() {
		x = y = 0;
	}
	node(int x,int y):x(x),y(y){}
} a[maxn];

int main() {
	scanf("%d",&n);
	while(n --) {
		int op;
		scanf("%d",&op);
		if(op == 1) {
			++ m;
			scanf("%d %d",&a[m].x,&a[m].y);
			f[m] = a[m].y;
			for(int i = 1;i < m;++ i)
				f[m] = 1ll * f[m] * power((a[m].x - a[i].x + mod) % mod , mod - 2) % mod,
				f[i] = 1ll * f[i] * power((a[i].x - a[m].x + mod) % mod , mod - 2) % mod;
		}
		else {
			int x,ans = 0;
			scanf("%d",&x);
			sum[0] = suf[m + 1] = 1;
			for(int i = 1;i <= m;++ i)
				sum[i] = 1ll * sum[i - 1] * (x - a[i].x + mod) % mod;
			for(int i = m;i >= 1;-- i)
				suf[i] = 1ll * suf[i + 1] * (x - a[i].x + mod) % mod;
			for(int i = 1;i <= m;++ i)
				add(ans , 1ll * f[i] * sum[i - 1] % mod * suf[i + 1] % mod);
			printf("%d\n",ans);
		}
	}
	return 0;
}
