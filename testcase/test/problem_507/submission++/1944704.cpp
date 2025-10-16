#include <bits/stdc++.h>
using namespace std;
long long n,k,c[1000005],v[1000005],dp[1000005],a[1000005];
int main(){
	cin >> n >> k;
	for(int i = 1;i <= n;i++) cin >> c[i];
	for(int i = 1;i <= n;i++){
		cin >> v[i];
		v[i] += v[i - 1];
	}
	for(int i = 1;i <= n;i++){
		dp[i] = dp[i - 1];
		if(a[c[i]]) dp[i] = max(dp[i],dp[a[c[i]] - 1] + v[i] - v[a[c[i]] - 1]);
		if(!a[c[i]]) a[c[i]] = i;
		else if(dp[i - 1] > dp[a[c[i]] - 1] + v[i - 1] - v[a[c[i]] - 1]) a[c[i]] = i;
	}
	cout << dp[n];
	return 0;
}