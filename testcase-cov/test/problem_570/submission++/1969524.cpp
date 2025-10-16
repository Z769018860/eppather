#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
int n, m, k, ans, cnt[5000005];
int fpow(int x, int y) {
	int s = 1;
	while(y) {
		if(y & 1)
			s = 1ll * s * x % mod;
		x = 1ll * x * x % mod, y >>= 1;
	}
	return s;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m >> k;
	for(int i = 0, x; i < m; i++)
		cin >> x, cnt[x]++;
	for(int i = 0; i < n; i++)
		for(int j = 1; j < (1 << n); j++)
			if(j >> i & 1)
				cnt[j - (1 << i)] += cnt[j];
	for(int i = 1; i < (1 << n); i++)
		ans = (ans + (__builtin_popcount(i) & 1 ? 1ll : mod - 1ll) * fpow(cnt[i], k) % mod) % mod;
	cout << ans;
	return 0;
}