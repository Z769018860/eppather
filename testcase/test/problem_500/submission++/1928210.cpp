
#include <bits/stdc++.h>
#define int long long
const int N=2e5+10, M=2e5+10, inf=1e9+10;
using namespace std;
int n, m;
int a[N], b[N], dp[200][200];
int chk( int x) {
	memset(dp, 128, sizeof dp);
	dp[0][0]=0;
	for ( int i=1; i<=n; i++)
		for ( int j=0; j<=m; j++)
			for ( int k=0; k<=j; k++)
				if (x-a[i]*(j-k)>=0) dp[i][j]=max(dp[i][j], dp[i-1][k]+(x-a[i]*(j-k))/b[i]);
	return dp[n][m]>=m;
}
#undef int
int main() {
#define int long long
	cin>>n>>m;
	for ( int i=1; i<=n; i++) cin>>a[i]>>b[i];
	int l=1, r=inf*inf, ans=0;
	while (l<=r) {
		int mid=l+r>>1;
		if (chk(mid)) ans=mid, r=mid-1;
		else l=mid+1;
	}
	cout<<ans;
}
