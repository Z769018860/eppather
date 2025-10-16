#include <bits/stdc++.h>
using namespace std;
long long c[1000010],b[1000010],a[1000010],dp[1000010],s[1000010];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	long long n,k,h,i;
	cin>>n>>k;
	for(i=1;i<=n;i++)
	{
		cin>>h;
		if(c[h])
			b[i]=c[h];
		c[h]=i;
	}
	for(i=1;i<=n;i++)
	{
		cin>>a[i];
		s[i]=s[i-1]+a[i];
	}
	for(i=1;i<=n;i++)
	{
		if(b[i])
			dp[i]=max(dp[i-1],max(dp[b[i]-1]+s[i]-s[b[i]-1],dp[b[i]]+s[i]-s[b[i]]));
		else
			dp[i]=dp[i-1];
	}
	cout<<dp[n];
	return 0;
}