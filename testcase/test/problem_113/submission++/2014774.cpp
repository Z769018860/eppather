
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
typedef tuple<LL, LL, LL> TLLL;
const int N = 1e6 + 5, mod = 1e9 + 7;
LL n, d[N];

void add(LL x) {
	for(int i = 50; i >= 0; --i) {
		if(x & (1LL << i)) {
			if(d[i])x ^= d[i];
			else {
				d[i] = x;
				return;
			}
		}
	}
}

void solve() {
	cin >> n;
	for(LL i = 1, x; i <= n; ++i) cin >> x, add(x);
	LL res = 0;
	for(int i = 50; i >= 0; --i) res = max(res, res ^ d[i]);
	cout << res << "\n";
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	int tt = 1;
	
	while(tt--) solve();
}
