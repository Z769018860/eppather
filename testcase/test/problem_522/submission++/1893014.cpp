#include<bits/stdc++.h>
#define int long long
#define rep(i,l,r) for(int i=l;i<=r;i++)
#define per(i,l,r) for(int i=r;i>=l;i--)
using namespace std;
const int N=3e5+5;
struct node{int x,r,v,id;}a[N];
vector<int>e[N];
map<int,int>mp[N];
int n,dp[N],rd[N],ans[N],mx,p=998244353;
inline void dfs(int x,int sum,int lst)
{
	if(dp[x]-min(p,mx*mx*2)>=sum||(mp[x].count(lst)&&mp[x][lst]>=sum))return;
	dp[x]=max(dp[x],sum),mp[x][lst]=sum;
	for(auto y:e[x])
	{
		dfs(y,sum+((a[lst].v^a[y].v)+a[lst].v*a[y].v)%p,y);
		dfs(y,sum,lst);
	}
}
signed main()
{
	ios::sync_with_stdio(false);cin.tie(0);
	cin>>n;
	rep(i,1,n)cin>>a[i].x;
	rep(i,1,n)cin>>a[i].r;
	rep(i,1,n)cin>>a[i].v,mx=max(mx,a[i].v);
	rep(i,1,n)a[i].id=i;
	sort(a+1,a+n+1,[](node x,node y){return x.x<y.x;});
	rep(i,1,n)
	{
		int l=a[i].x-a[i].r,r=a[i].x+a[i].r;
		per(j,1,i-1)
		{
			if(a[j].x<l)break;
			e[i].push_back(j);
			rd[j]++;
		}
		rep(j,i+1,n)
		{
			if(a[j].x>r)break;
			e[i].push_back(j);
			rd[j]++;
		}
	}
	rep(i,1,n)if(!rd[i])dfs(i,0,i);
	rep(i,1,n)ans[a[i].id]=dp[i];
	rep(i,1,n)cout<<ans[i]<<'\n';
	return 0;
}