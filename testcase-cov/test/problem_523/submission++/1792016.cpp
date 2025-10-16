
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline","fast-math","unroll-loops","no-stack-protector")
#pragma GCC diagnostic error "-fwhole-program"
#pragma GCC diagnostic error "-fcse-skip-blocks"
#pragma GCC diagnostic error "-funsafe-loop-optimizations"
#include <bits/stdc++.h>
#define INF 1000000000
#define LINF 1000000000000000000
#define MOD 1000000007
#define mod 998244353
#define F first
#define S second
#define ll int
#define N 1500010
using namespace std;
struct SegT{
	ll lo[N<<1],hi[N<<1],val[N<<1],pd[N<<1];
	void build(ll x,ll l,ll r)
	{
		lo[x]=l,hi[x]=r,val[x]=pd[x]=0;
		if(l==r)
		{
			return;
		}
		ll mid=(l+r)>>1,a=x<<1;
		build(a,l,mid);
		build(a|1,mid+1,r);
		return;
	}
	void pushdown(ll x)
	{
		ll a=x<<1;
		val[a]+=pd[x],pd[a]+=pd[x];
		val[a|1]+=pd[x],pd[a|1]+=pd[x];
		pd[x]=0;
		return;
	}
	void update(ll x,ll l,ll r,ll v)
	{
		ll tl=lo[x],tr=hi[x];
		if(l<=tl&&tr<=r)
		{
			val[x]+=v;
			pd[x]+=v;
			return;
		}
		pushdown(x);
		ll mid=(tl+tr)>>1,a=x<<1;
		if(mid>=l)
		{
			update(a,l,r,v);
		}
		if(mid<r)
		{
			update(a|1,l,r,v);
		}
		val[x]=max(val[a],val[a|1]);
		return;
	}
	ll query(ll x,ll l,ll r)
	{
		ll tl=lo[x],tr=hi[x];
		if(l<=tl&&tr<=r)
		{
			return val[x];
		}
		pushdown(x);
		ll mid=(tl+tr)>>1,a=x<<1,ret=0;
		if(mid>=l)
		{
			ret=max(ret,query(a,l,r));
		}
		if(mid<r)
		{
			ret=max(ret,query(a|1,l,r));
		}
		return ret;
	}
}segt;
ll n,m,_T,a[N],b[N];
ll stk[N],stked[N],stktp=0;
ll ccnt=0,edcnt=0,dcnt=0,din[N],dout[N],pttp[N],edtp[N],bel[N],beled[N],res[N],edval[N],cycval[N][2],lor[N],hir[N],curans=0;
bool isbad[N],iscyc[N],vis[N],oncyc[N];
vector<pair<ll,ll> > vt[N];
vector<ll> pth,cyc,cyced,allrt;
void predfs(ll x,ll lst=-1)
{
	ll i,j;
	pth.push_back(x);
	stk[stktp]=x;
	stked[stktp++]=lst;
	vis[x]=true;
	for(i=0;i<vt[x].size();i++)
	{
		if(vt[x][i].S==lst||isbad[vt[x][i].S])
		{
			continue;
		}
		if(!vis[vt[x][i].F])
		{
			predfs(vt[x][i].F,vt[x][i].S);
		}
		else if(!oncyc[vt[x][i].F])
		{
			cyced.push_back(vt[x][i].S);
			for(j=stktp-1;j>=0;j--)
			{
				oncyc[stk[j]]=true;
				cyc.push_back(stk[j]);
				if(stk[j]==vt[x][i].F)
				{
					break;
				}
				cyced.push_back(stked[j]);
			}
			reverse(cyc.begin(),cyc.end());
			reverse(cyced.begin(),cyced.end());
		}
	}
	stktp--;
	return;
}
void dfstree(ll x,ll lst)
{
	ll i;
	for(i=0;i<vt[x].size();i++)
	{
		if(vt[x][i].S==lst||isbad[vt[x][i].S])
		{
			continue;
		}
		beled[vt[x][i].S]=ccnt;
		edtp[vt[x][i].S]=min(vt[x][i].F,x)*2+(x<m);
		dfstree(vt[x][i].F,vt[x][i].S);
	}
	return;
}
void dfstree2(ll x,ll lst)
{
	ll i;
	for(i=0;i<vt[x].size();i++)
	{
		if(vt[x][i].S==lst||isbad[vt[x][i].S])
		{
			continue;
		}
		beled[vt[x][i].S]=ccnt;
		if(x>=m)
		{
			isbad[vt[x][i].S]=true;
		}
		dfstree2(vt[x][i].F,vt[x][i].S);
	}
	return;
}
void dfsd(ll x,ll lst)
{
	if(x>=m)
	{
		din[x]=++dcnt;
	}
	ll i;
	for(i=0;i<vt[x].size();i++)
	{
		if(vt[x][i].S==lst||isbad[vt[x][i].S])
		{
			continue;
		}
		dfsd(vt[x][i].F,vt[x][i].S);
		if(x<m)
		{
			dout[x]=dout[vt[x][i].F];
			if(!din[x])
			{
				din[x]=din[vt[x][i].F];
			}
		}
	}
	if(x>=m)
	{
		dout[x]=++dcnt;
	}
	return;
}
void update(ll x,ll v)
{
	if(isbad[x])
	{
		return;
	}
	if(iscyc[x])
	{
		curans-=res[beled[x]];
		cycval[beled[x]][edtp[x]&1]+=v;
		res[beled[x]]=max(cycval[beled[x]][0],cycval[beled[x]][1]);
		curans+=res[beled[x]];
		return;
	}
	if(pttp[beled[x]]==2)
	{
		res[beled[x]]+=v;
		curans+=v;
		return;
	}
	ll l=lor[beled[x]],r=hir[beled[x]],y=edtp[x]/2;
	if(edtp[x]&1)
	{
		if(l<din[y])
		{
			segt.update(1,l,din[y]-1,v);
		}
		if(dout[y]<r)
		{
			segt.update(1,dout[y]+1,r,v);
		}
	}
	else
	{
		segt.update(1,din[y],dout[y],v);
	}
	curans-=res[beled[x]];
	res[beled[x]]=segt.query(1,l,r);
	curans+=res[beled[x]];
	return;
}
int main(){
	ll i,j,k,l,lastans;
	scanf("%d%d%d",&m,&n,&_T);
	for(i=0;i<m;i++)
	{
		scanf("%d",&a[i]);
	}
	for(i=0;i<m;i++)
	{
		scanf("%d",&b[i]);
		ll x=(a[i]+b[i])%n,y=(a[i]+n-b[i])%n;
		if(x>y)
		{
			swap(x,y);
		}
		vt[i].push_back(make_pair(x+m,edcnt));
		vt[x+m].push_back(make_pair(i,edcnt++));
		if(x!=y)
		{
			vt[i].push_back(make_pair(y+m,edcnt));
			vt[y+m].push_back(make_pair(i,edcnt++));
		}
	}
	for(i=0;i<m;i++)
	{
		if(!vis[i])
		{
			pth.clear();
			cyc.clear(),cyced.clear();
			predfs(i);
			if(!cyc.empty())
			{
				for(j=0;j<pth.size();j++)
				{
					vis[pth[j]]=false;
				}
				for(j=0;j<cyced.size();j++)
				{
					beled[cyced[j]]=ccnt;
					iscyc[cyced[j]]=true;
					edtp[cyced[j]]=j;
				}
				for(j=0;j<cyc.size();j++)
				{
					ll x=cyc[j];
					vis[x]=true;
					bel[x]=ccnt;
					for(k=0;k<vt[x].size();k++)
					{
						if(!iscyc[vt[x][k].S])
						{
							isbad[vt[x][k].S]=true;
						}
					}
				}
				pttp[ccnt++]=0;
				for(j=0;j<cyc.size();j++)
				{
					ll x=cyc[j];
					for(k=0;k<vt[x].size();k++)
					{
						if(isbad[vt[x][k].S])
						{
							pth.clear();
							predfs(vt[x][k].F,vt[x][k].S);
							for(l=0;l<pth.size();l++)
							{
								bel[pth[l]]=ccnt;
							}
							if(pth.size()&1)
							{
								for(l=0;l<pth.size();l++)
								{
									if(pth[l]>=m)
									{
										allrt.push_back(pth[l]);
										dfstree(pth[l],-1);
										break;
									}
								}
								pttp[ccnt++]=1;
							}
							else
							{
								dfstree2(pth[0],-1);
								pttp[ccnt++]=2;
							}
						}
					}
				}
			}
			else
			{
				for(l=0;l<pth.size();l++)
				{
					bel[pth[l]]=ccnt;
				}
				if(pth.size()&1)
				{
					for(l=0;l<pth.size();l++)
					{
						if(pth[l]>=m)
						{
							allrt.push_back(pth[l]);
							dfstree(pth[l],-1);
							break;
						}
					}
					pttp[ccnt++]=1;
				}
				else
				{
					for(l=0;l<pth.size();l++)
					{
						if(pth[l]<m&&vt[pth[l]].size()==1)
						{
							dfstree2(pth[l],-1);
							break;
						}
					}
					pttp[ccnt++]=2;
				}
			}
		}
	}
	for(i=0;i<allrt.size();i++)
	{
		lor[bel[allrt[i]]]=dcnt+1;
		dfsd(allrt[i],-1);
		hir[bel[allrt[i]]]=dcnt;
	}
	segt.build(1,0,dcnt);
	for(i=0;i<edcnt;i++)
	{
		scanf("%d",&edval[i]);
		update(i,edval[i]);
	}
	ll q;
	scanf("%d",&q);
	printf("%d\n",lastans=curans);
	while(q--)
	{
		scanf("%d%d",&i,&j);
		i-=lastans*_T,j-=lastans*_T;
		i--;
		update(i,j-edval[i]);
		edval[i]=j;
		printf("%d\n",lastans=curans);
	}
	return 0;
}