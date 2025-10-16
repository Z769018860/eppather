#include<bits/stdc++.h>
using namespace std;
long long n,k,a[1000010],v[1000010],dp[1000010],sum[1000010],maxs,mx[1000010],book[1000010],p=0;
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		mx[a[i]]=-1e18;
	}
	for(int i=1;i<=n;i++){
		cin>>v[i];
		sum[i]=sum[i-1]+v[i];
	}
	for(int i=1;i<=n;i++){
			dp[i]=max(sum[i]+mx[a[i]],p);
			mx[a[i]]=max(mx[a[i]],maxs-sum[i-1]);
			maxs=max(maxs,dp[i]);

	}
	cout<<maxs;
	return 0;
}