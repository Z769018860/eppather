#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e2+10;
const int mod = 998244353;
int	n,t,k,q,m;

bitset<N * N * N> bt[N];

void solve(){
	cin >> n;
	vector<int> aa(n + 1);
	bt[0][0] = 1;
	int a, b;
	for(int i = 1; i <= n; i ++) {
		cin >> a >> b;
		for(int j = a; j <= b; j ++) {
			bt[i] |= bt[i - 1] << (j * j);
		}
	}
	int ans = bt[n].count();
	cout << ans << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
		solve();
	return 0;
}