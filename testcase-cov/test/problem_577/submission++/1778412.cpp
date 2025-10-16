#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,p;
int c[55][55];
int dp[55][2505];
int a[55];
map<pair<int,int>,int> mp; 
int sol(int x,int y)
{
	
	if(y<0)		return 0;
	if(x<p)		return dp[x][y];
	if(mp[{x,y}])	return mp[{x,y}]-p;
	int re=0;
	for(int i=0;i<n;i++)
		if(dp[x%p][i*p+y%p])	re=(re+dp[x%p][i*p+y%p]*sol(x/p,y/p-i))%p;
	mp[{x,y}]=re+p;
	return re;
}
signed main()
{
	scanf("%lld%lld",&n,&p);
	for(int i=0;i<=p;i++)
	{
		c[i][0]=1;
		for(int j=1;j<=i;j++)
			c[i][j]=(c[i-1][j-1]+c[i-1][j])%p;
	}
	for(int i=0;i<=n;i++)	scanf("%lld",&a[i]);
	dp[0][0]=1;
	for(int i=0;i<=n;i++)
		for(int j=p-1;j>=0;j--)
			for(int k=n*(p-1);k>=0;k--)
			{
				int tm=a[i];
				for(int l=1;l<=j&&i*l<=k;l++)
					(dp[j][k]+=dp[j-l][k-i*l]*tm*c[j][l])%=p,tm=tm*a[i]%p;
			}
	int T;
	cin>>T;
	while(T--)
	{
		int x,y;
		cin>>x>>y;
		int ans=1;
		cout<<sol(x,y)<<'\n';
	}
	return 0;
}
