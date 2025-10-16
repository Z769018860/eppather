










#include<bits/stdc++.h>
using namespace std;
const int N = 1.3e8 + 7;
using i64 = long long;

int mu[N], sum[N];
i64 n, m, B, pr[N / 10];

void sieve () {
	int cnt = 0;
	mu[1] = 1;
	for (int i = 2; i <= B; i ++) {
		if (! sum[i]) pr[++ cnt] = i, mu[i] = -1;
		for (int j = 1; j <= cnt and 1ll * i * pr[j] <= B; j ++) {
			
			sum[i * pr[j]] = 1;
			if (i % pr[j] == 0) { mu[i * pr[j]] = 0; break; }
			mu[i * pr[j]] = -mu[i];
		}
	}	
	
	for (int i = 1; i <= B; i ++) sum[i] = sum[i - 1] + mu[i] * mu[i], mu[i] += mu[i - 1];
}

i64 getm (i64 k) {
	
	if (k <= B) return sum[k];
	i64 res = 0;
	i64 L = sqrt (k);
	for (int i = 1, j; 1ll * i * i <= k; i = j + 1) {
		
		
		
		i64 x = k / i / i;
		
		j = sqrt (k / x);
		
		
		res = res + 1ll * (mu[j] - mu[i - 1]) * x;
	}
	return res;
}

signed main () {
	cin >> n >> m;
	if (n > m) swap (n, m);
	B = sqrt (n);
	
	
	sieve ();
	
	i64 ans = 0, lst = 0;
	for (i64 i = 1, j; i <= n; i = j + 1) {
		i64 x = sqrt (n / i), y = sqrt (m / i);
		j = min (n / x / x, m / y / y);
		
		i64 res = getm (j);
		ans += 1ll * (res - lst) * x * y;
		lst = res;
	}
	
	cout << ans;
}