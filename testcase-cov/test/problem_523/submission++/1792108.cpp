#include<bits/stdc++.h>
#define int long long
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
vector<int>v[500005];
int dy[1000005],dd[1000005],cnt;
int bu[1000005],bv[1000005],wu[1000005],wv[1000005],tmp;
vector<int>bh[500005];
int fa[1000005],siz[1000005],bs[1000005];
int findf(int n)
{
	if(fa[n]==n)return n;
	return fa[n]=findf(fa[n]);
}
bool vis[1000005],inh[1000005];
bool xzu[1000005];
int fb[1000005];
int hz[1000005],ttt;
int dz[1000005],ttop;
bool dfs1(int x,int rb)
{
	if(vis[x])return false;
	vis[x]=true;
	fb[x]=rb;
	for(int i=0;i<v[x].size();i++)
	{
		if(v[x][i]==rb)continue;
		int sth=bu[v[x][i]]+bv[v[x][i]]-x;
		if(vis[sth])
		{
			int now=x;
			ttt=0;
			ttop=0;
			while(now!=sth)
			{
				dz[++ttop]=now;
				hz[++ttt]=fb[now];
				now=bu[fb[now]]+bv[fb[now]]-now;
			}
			dz[++ttop]=sth;
			hz[++ttt]=v[x][i];
			return true;
		}
		if(dfs1(sth,v[x][i]))return true;
	}
	return false;
}
int nans;
void dfs2(int x,int rb)
{
	for(int i=0;i<v[x].size();i++)
	{
		if(v[x][i]==rb)continue;
		int sth=bu[v[x][i]]+bv[v[x][i]]-x; 
		if(bu[v[x][i]]==x)nans+=wv[v[x][i]];
		else nans+=wu[v[x][i]];
		dfs2(sth,v[x][i]);
	}
}
int fat[1000005],sizt[1000005],dfnt[1000005],cans[1000005],zs;
int tl[1000005],tr[1000005];
int maxn;
void dfs3(int x,int rb)
{
	fat[x]=bu[rb]+bv[rb]-x;
	sizt[x]=1;
	dfnt[x]=++zs;
	
	if(rb!=0)
	{
		if(bu[rb]==x)nans=nans-wu[rb]+wv[rb];
		else nans=nans-wv[rb]+wu[rb];
	}
	cans[dfnt[x]]=nans; 
	maxn=max(maxn,nans);
	for(int i=0;i<v[x].size();i++)
	{
		if(v[x][i]==rb)continue;
		int sth=bu[v[x][i]]+bv[v[x][i]]-x;
		dfs3(sth,v[x][i]);
		sizt[x]+=sizt[sth];
	}
	if(rb!=0)
	{
		if(bu[rb]!=x)nans=nans-wu[rb]+wv[rb];
		else nans=nans-wv[rb]+wu[rb];
	}
}
void dfs4(int x,int rb)
{
	for(int i=0;i<v[x].size();i++)
	{
		if(v[x][i]==rb)continue;
		int sth=bu[v[x][i]]+bv[v[x][i]]-x; 
		if(inh[x]&&inh[sth])continue;
		if(bu[v[x][i]]==x)nans+=wv[v[x][i]];
		else nans+=wu[v[x][i]],xzu[v[x][i]]=true;
		dfs4(sth,v[x][i]);
	}
}
int aa[1000005],b[1000005];
int h1[1000005],h2[1000005];
struct tree
{
	int l,r,maxn,laz;
}a[4000004];
void build(int l,int r,int k)
{
	a[k].l=l;
	a[k].r=r;
	a[k].laz=0;
	if(l==r)
	{
		a[k].maxn=cans[l];
		return;
	}
	build(l,(l+r)>>1,k<<1);
	build(((l+r)>>1)+1,r,k<<1|1);
	a[k].maxn=max(a[k<<1].maxn,a[k<<1|1].maxn);
}
void change(int l,int r,int k,int x)
{
	if(l>r)return;
	if(a[k].l>r||a[k].r<l)return;
	if(a[k].l>=l&&a[k].r<=r)
	{
		a[k].maxn+=x;
		a[k].laz+=x;
		return;
	}
	if(a[k].laz!=0)
	{
		a[k<<1].maxn+=a[k].laz;
		a[k<<1].laz+=a[k].laz;
		a[k<<1|1].maxn+=a[k].laz;
		a[k<<1|1].laz+=a[k].laz;
		a[k].laz=0;
	}
	change(l,r,k<<1,x);
	change(l,r,k<<1|1,x);
	a[k].maxn=max(a[k<<1].maxn,a[k<<1|1].maxn);
}
int query(int l,int r,int k)
{
	if(a[k].l>r||a[k].r<l)return 0;
	if(a[k].l>=l&&a[k].r<=r)return a[k].maxn;
	if(a[k].laz!=0)
	{
		a[k<<1].maxn+=a[k].laz;
		a[k<<1].laz+=a[k].laz;
		a[k<<1|1].maxn+=a[k].laz;
		a[k<<1|1].laz+=a[k].laz;
		a[k].laz=0; 
	}
	return max(query(l,r,k<<1),query(l,r,k<<1|1)); 
}
signed main()
{
	int m,n,T;
	m=read();
	n=read();
	T=read();
	for(int i=1;i<=m;i++)
	{
		aa[i]=read();
	}
	for(int i=1;i<=m;i++)b[i]=read(); 
	for(int i=1;i<=m;i++)
	{
		int x1=(aa[i]+b[i])%n+1,x2=(aa[i]+n-b[i])%n+1;
		if(x1>x2)swap(x1,x2);
		
		v[i].push_back(x1);
		if(x2!=x1)v[i].push_back(x2);
	}
	for(int i=1;i<=m;i++)
	{
		if(v[i].size()==1)
		{
			bu[++tmp]=v[i][0];
			bv[tmp]=v[i][0];
			cnt++;
			dy[cnt]=tmp;
			dd[cnt]=0;
			wu[tmp]=read();
			wv[tmp]=wu[tmp];
			continue;
		}
		bu[++tmp]=v[i][0];
		bv[tmp]=v[i][1];
		cnt++;
		dy[cnt]=tmp;
		dd[cnt]=-1;
		wu[tmp]=read();
		cnt++;
		dy[cnt]=tmp;
		dd[cnt]=1;
		wv[tmp]=read();
	}
	
	for(int i=1;i<=n;i++)fa[i]=i,siz[i]=1,bs[i]=0,v[i].clear();
	for(int i=1;i<=tmp;i++)
	{
		v[bu[i]].push_back(i);
		v[bv[i]].push_back(i);
		int x=findf(bu[i]),y=findf(bv[i]);
		
		if(x!=y)
		{
			siz[y]+=siz[x];
			bs[y]+=bs[x];
			fa[x]=y;
			bs[x]=0;
			siz[x]=0;
		}
		bs[y]++;
	}
	int ans=0;
	for(int i=1;i<=n;i++)vis[i]=false,inh[i]=false;
	for(int i=1;i<=n;i++)
	{
		if(findf(i)!=i)continue;
		if(bs[i]==siz[i])
		{
			dfs1(i,0);
			for(int i=1;i<=ttt;i++)
			{
				inh[bu[hz[i]]]=inh[bv[hz[i]]]=true;
			}
			for(int i=1;i<=ttt;i++)
			{
				nans=0;
				dfs4(dz[i],0);
				ans+=nans;
			}
			int he1=0,he2=0;
			for(int i=1;i<=ttt;i++)
			{
				if(bu[hz[i]]==dz[i])he1+=wu[hz[i]],he2+=wv[hz[i]],xzu[hz[i]]=true;
				else he1+=wv[hz[i]],he2+=wu[hz[i]];
			}
			h1[i]=he1;
			h2[i]=he2;
			ans+=max(he1,he2);
		}
		else
		{
			tl[i]=zs+1; 
			nans=0;
			dfs2(i,0);
			maxn=nans;
			dfs3(i,0);
			ans+=maxn;
			tr[i]=zs;
		}
	}
	build(1,n,1);
	printf("%lld\n",ans);
	int q=read(),la=ans,x,y;
	for(int i=1;i<=q;i++)
	{
		x=read();
		y=read();
		x-=T*la;
		y-=T*la;
		if(bs[findf(bu[dy[x]])]==siz[findf(bu[dy[x]])])
		{
			
			int sth=findf(bu[dy[x]]);
			if(inh[bu[dy[x]]]&&inh[bv[dy[x]]])
			{
				
				ans-=max(h1[sth],h2[sth]); 
				if(dd[x]==0)h1[sth]+=y-wu[dy[x]],h2[sth]+=y-wv[dy[x]];
				else if(dd[x]==-1&&xzu[dy[x]]==true)h1[sth]+=y-wu[dy[x]];
				else if(dd[x]==1&&xzu[dy[x]]==false)h1[sth]+=y-wv[dy[x]];
				else if(dd[x]==-1)h2[sth]+=y-wu[dy[x]];
				else if(dd[x]==1)h2[sth]+=y-wv[dy[x]]; 
				ans+=max(h1[sth],h2[sth]);
			}
			else
			{
				if(dd[x]==-1&&xzu[dy[x]]==true)ans+=y-wu[dy[x]];
				else if(dd[x]==1&&xzu[dy[x]]==false)ans+=y-wv[dy[x]];
			}
			if(dd[x]==0)
			{
				wu[dy[x]]=wv[dy[x]]=y;
			}
			else if(dd[x]==-1)wu[dy[x]]=y;
			else wv[dy[x]]=y;
			printf("%lld\n",la=ans);
			continue;
		}
		
		int sth=findf(bu[dy[x]]);
		ans-=query(tl[sth],tr[sth],1);
		if(dd[x]==-1)
		{
			if(bu[dy[x]]==fat[bv[dy[x]]])
			{
				change(dfnt[bv[dy[x]]],dfnt[bv[dy[x]]]+sizt[bv[dy[x]]]-1,1,y-wu[dy[x]]);
			}
			else
			{
				change(tl[sth],dfnt[bu[dy[x]]]-1,1,y-wu[dy[x]]);
				change(dfnt[bu[dy[x]]]+sizt[bu[dy[x]]],tr[sth],1,y-wu[dy[x]]);
			}
		}
		else
		{
			if(bv[dy[x]]==fat[bu[dy[x]]])
			{
				change(dfnt[bu[dy[x]]],dfnt[bu[dy[x]]]+sizt[bu[dy[x]]]-1,1,y-wv[dy[x]]);
			}
			else
			{
				change(tl[sth],dfnt[bv[dy[x]]]-1,1,y-wv[dy[x]]);
				change(dfnt[bv[dy[x]]]+sizt[bv[dy[x]]],tr[sth],1,y-wv[dy[x]]);
			}
		}
		ans+=query(tl[sth],tr[sth],1);
		if(dd[x]==0)
		{
			wu[dy[x]]=wv[dy[x]]=y;
		}
		else if(dd[x]==-1)wu[dy[x]]=y;
		else wv[dy[x]]=y;
		printf("%lld\n",la=ans);
	}
	return 0;
}