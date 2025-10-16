#include<bits/stdc++.h>
#define int long long
#define inf 1000000000000000100LL
using namespace std;
inline int read()
{
	int n=0,f=1,ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		n=n*10+ch-'0';
		ch=getchar();
	}
	return n*f;
}
set<int>se;
int xz[1000005];
int sc[1000005];
vector<int>v[1000005];
void change(int x,int y)
{
	if(xz[x]==1)
	{
		sc[x]--;
		for(int i=0;i<v[x].size();i++)
		{
			sc[v[x][i]]--;
		}
	}
	else if(xz[x]==-1)
	{
		sc[x]--;
	}
	xz[x]=y;
	if(xz[x]==1)
	{
		sc[x]++;
		for(int i=0;i<v[x].size();i++)
		{
			sc[v[x][i]]++;
		}
	}
	else if(xz[x]==-1)
	{
		sc[x]++;
	}
	if(sc[x]>0)se.erase(x);
	else se.insert(x);
	for(int i=0;i<v[x].size();i++)
	{
		if(sc[v[x][i]]>0)se.erase(v[x][i]);
		else se.insert(v[x][i]);
	}
}
bool vis[1000005];
int dp[1000005][2];
void dfs(int x,int f)
{
	if(sc[x]>0)return;
	vis[x]=true;
	dp[x][0]=1;
	dp[x][1]=1;
	for(int i=0;i<v[x].size();i++)
	{
		if(sc[v[x][i]]>0||v[x][i]==f)continue;
		dfs(v[x][i],x);
		if(dp[x][0]>inf/(dp[v[x][i]][0]+dp[v[x][i]][1]))dp[x][0]=inf;
		else dp[x][0]*=(dp[v[x][i]][0]+dp[v[x][i]][1]);
		if(dp[x][1]>inf/dp[v[x][i]][0])dp[x][1]=inf;
		else dp[x][1]*=dp[v[x][i]][0];
	}
}
int solve()
{
	if(se.size()>110)return inf;
	int ans=1;
	for(auto x:se)
	{
		if(vis[x])continue;
		dfs(x,0);
		if(dp[x][0]+dp[x][1]>inf/ans)
		{
			ans=inf;
			break; 
		} 
		else ans*=(dp[x][0]+dp[x][1]);
	}
	for(auto x:se)vis[x]=false;
	return ans;
}
int tx[1000005],ty[1000005];
int dls[1000005];
signed main()
{
	int n,k;
	n=read();
	k=read();
	for(int i=1;i<=n-1;i++)tx[i]=read()+1;
	for(int i=1;i<=n-1;i++)
	{
		ty[i]=read()+1;
		v[tx[i]].push_back(ty[i]);
		v[ty[i]].push_back(tx[i]);
	}
	for(int i=1;i<=n;i++)
	{
		xz[i]=-1;
		sc[i]=1;
	}
	int ssiz;
	ssiz=read(); 
	for(int i=1;i<=ssiz;i++)dls[i]=read()+1,change(dls[i],1);
	sort(dls+1,dls+ssiz+1);
	for(int i=dls[ssiz]+1;i<=n;i++)change(i,0);
	int nans=solve()-1;
	
	if(k<=nans)
	{
		for(int i=dls[ssiz]+1;i<=n;i++)
		{
			if(sc[i]>0)continue;
			change(i,1);
			nans=solve();
			if(nans==0)
			{
				change(i,-1);
				continue;
			}
			if(k==1)break;
			if(k>nans)
			{
				k-=nans;
				change(i,-1);
			}
			else k--;
		}
		for(int i=1;i<=n;i++)if(xz[i]==1)printf("%lld ",i-1);
		printf("\n");
		return 0;
	}
	else k-=nans;
	int now=-1;
	dls[ssiz+1]=n;
	for(int i=ssiz-1;i>=0;i--)
	{
		change(dls[i],1);
		for(int j=dls[i]+1;j<=dls[i+1];j++)
		{
			change(j,-1); 
		} 
		for(int j=dls[i+1]+1;j<=dls[i+2];j++)
		{
			change(j,0); 
		}
		int nans=solve()-1;
		
		if(k<=nans)
		{
			now=i;
			break;
		}
		else k-=nans;
	}
	if(now==-1)return 0;
	for(int j=dls[now+1]+1;j<=n;j++)
	{
		if(sc[j]>0)continue;
		change(j,1);
		
		
		int nans=solve();
		
		if(nans==0)
		{
			change(j,-1);
			continue;
		}
		if(k==1)break;
		if(k>nans)
		{
			k-=nans;
			change(j,-1);
		}
		else k--;
	}
	for(int i=1;i<=n;i++)if(xz[i]==1)printf("%lld ",i-1);
	printf("\n");
	return 0;
}
