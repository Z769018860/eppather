#include <bits/stdc++.h>
#define F first
#define S second
#define ll int
#define N 100010
#define B 320
using namespace std;
ll n,m,val[N],ans[N],ord[N],ql,qr,fa[N],sz[N],vsz[N];
vector<pair<ll,pair<ll,ll> > > vt[N];
bool isq[N];
pair<ll,ll> qry[N];
ll getf(ll x){return x==fa[x]?x:getf(fa[x]);}
bool cmp(ll x,ll y)
{
	return val[x]<val[y];
}
void dfs(ll x)
{
	ll i;
	if(isq[x]&&ans[x]==-1)
	{
		ll y=getf(qry[x].F);
		if(qry[x].S>vsz[y])
		{
			qry[x].S-=vsz[y];
		}
		else
		{
			for(i=ql;i<=qr&&qry[x].S;i++)
			{
				if(getf(ord[i])==y)
				{
					ans[x]=val[ord[i]];
					qry[x].S--;
				}
			}
		}
	}
	for(i=0;i<vt[x].size();i++)
	{
		ll qx=-1,qy=-1;
		if(vt[x][i].S.F!=-1)
		{
			qx=getf(vt[x][i].S.F);
			qy=getf(vt[x][i].S.S);
			if(qx==qy)
			{
				qx=qy=-1;
			}
			else
			{
				if(sz[qx]>sz[qy])
				{
					swap(qx,qy);
				}
				sz[qy]+=sz[qx];
				fa[qx]=qy;
				vsz[qy]+=vsz[qx];
			}
		}
		dfs(vt[x][i].F);
		if(qx!=-1)
		{
			sz[qy]-=sz[qx];
			vsz[qy]-=vsz[qx];
			fa[qx]=qx;
		}
	}
	return;
}
void solve()
{
	ll i;
	for(i=0;i<n;i++)
	{
		vsz[i]=0;
		sz[i]=1;
		fa[i]=i;
	}
	for(i=ql;i<=qr;i++)
	{
		vsz[ord[i]]=1;
	}
	dfs(0);
	return;
}
int main(){
	ll i,tp,x,y;
	scanf("%d%d",&n,&m);
	for(i=0;i<n;i++)
	{
		scanf("%d",&val[i]);
		ord[i]=i;
	}
	sort(ord,ord+n,cmp);
	for(i=1;i<=m;i++)
	{
		scanf("%d",&tp);
		if(tp==1)
		{
			scanf("%d%d",&x,&y);
			x--,y--;
			vt[i-1].push_back(make_pair(i,make_pair(x,y)));
		}
		else if(tp==2)
		{
			scanf("%d",&x);
			vt[x].push_back(make_pair(i,make_pair(-1,-1)));
		}
		else
		{
			isq[i]=true;
			ans[i]=-1;
			scanf("%d%d",&qry[i].F,&qry[i].S);
			qry[i].F--;
			vt[i-1].push_back(make_pair(i,make_pair(-1,-1)));
		}
	}
	for(i=0;i<n;i+=B)
	{
		ql=i,qr=min(n-1,i+B-1);
		solve();
	}
	for(i=1;i<=m;i++)
	{
		if(isq[i])
		{
			printf("%d\n",ans[i]);
		}
	}
	return 0;
}