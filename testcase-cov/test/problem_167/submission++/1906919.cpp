#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int mod = 998244353;
ll n, fac[1000005], tree[1000005];
 
void update(int x, int val) {
	for(int i = x; i <= n; i += i & -i) 
		tree[i] += val;
} 
int query(int x) {
	int ans = 0;
	for(int i = x; i > 0; i -= i & -i) 
		ans += tree[i];
	return ans;
}

signed main() {
	scanf("%lld", &n); 
	fac[0] = 1;
	for(int i = 1; i <= n; i++) {
		fac[i] = fac[i - 1] * i % mod;
		update(i, 1);
	}
	ll ans = 0;
	for(int i = 1, x; i <= n; i++) {
		scanf("%d", &x);
		ans = (ans + query(x - 1) % mod * fac[n - i] % mod) % mod;
		update(x, -1);
	}
	printf("%lld", ans + 1);
	return 0;
}