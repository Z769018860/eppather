#include<bits/stdc++.h>
#define maxn 200005
#define mp(x,y) make_pair(x,y)
#define ll long long
using namespace std;
const int mod=19260817;
struct node{int x,y,z;}a[maxn];
ll ans,tak=1;
ll u(ll x){return x*(x+1)/2%mod;}
int n,m,cnt,len[maxn],ys[maxn],b[maxn];
set<pair<int,int> > s[maxn];
set<pair<int,int> >::iterator tl,tr;
vector<int> v[maxn];

int tot,rt[maxn],lc[maxn*36],rc[maxn*36],sum[maxn*36];
void pushup(int v){sum[v]=1ll*(lc[v]?sum[lc[v]]:1)*(rc[v]?sum[rc[v]]:1)%mod;}
void cov(int &v,int l,int r,int p,int k)
{
	++tot;lc[tot]=lc[v],rc[tot]=rc[v],sum[tot]=sum[v];
	v=tot;
	if(l==r){sum[v]=(k+mod)%mod;return;}
	int mid=(l+r)>>1;
	if(p<=mid)cov(lc[v],l,mid,p,k);
	else cov(rc[v],mid+1,r,p,k);
	pushup(v);
}
int que(int v,int l,int r,int p)
{
	if(l==r)return sum[v];
	int mid=(l+r)>>1;
	if(p<=mid)return que(lc[v],l,mid,p);
	else return que(rc[v],mid+1,r,p); 
}

void del(int x,int y,int z)
{
	s[z].erase(mp(x,y));b[z]--;if(!b[z])ans=(ans-tak+mod)%mod;
	tl=tr=s[z].lower_bound(mp(x,y));--tl;
	int l=tl->second,r=tr->second;
	ans=(ans+sum[rt[z]])%mod;
	cov(rt[z],1,n,x,que(rt[z],1,n,x)+u(r-l-1)-u(y-l-1)-u(r-y-1));
	if(b[z])ans=(ans-sum[rt[z]]+mod)%mod;
}
void upd(int x,int y,int z)
{
	if(!b[z])ans=(ans+tak)%mod;b[z]++;
	tl=tr=s[z].lower_bound(mp(x,y));--tl;
	int l=tl->second,r=tr->second;
	if(b[z]>1)ans=(ans+sum[rt[z]])%mod;
	cov(rt[z],1,n,x,que(rt[z],1,n,x)-u(r-l-1)+u(y-l-1)+u(r-y-1));
	s[z].insert(mp(x,y));
	ans=(ans-sum[rt[z]]+mod)%mod;
}

int main()
{
	int x,y;
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&len[i]),tak=tak*u(len[i])%mod;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=len[i];j++)scanf("%d",&x),ys[++cnt]=x,v[i].push_back(x);
	}
	for(int i=1;i<=m;i++)scanf("%d %d %d",&a[i].x,&a[i].y,&a[i].z),ys[++cnt]=a[i].z;
	sort(ys+1,ys+cnt+1);
	cnt=unique(ys+1,ys+cnt+1)-ys-1;
	for(int i=1;i<=n;i++)cov(rt[0],1,n,i,u(len[i]));
	for(int i=1;i<=cnt;i++)rt[i]=rt[0];
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<v[i].size();j++)
		{
			x=v[i][j]=lower_bound(ys+1,ys+cnt+1,v[i][j])-ys;
			s[x].insert(mp(i,0)),s[x].insert(mp(i,len[i]+1));
			upd(i,j+1,x);
		}
	}
	printf("%lld\n",ans);
	for(int i=1;i<=m;i++)
	{
		a[i].z=lower_bound(ys+1,ys+cnt+1,a[i].z)-ys;
		x=a[i].x,y=a[i].y;
		del(x,y,v[x][y-1]);v[x][y-1]=a[i].z;
		s[a[i].z].insert(mp(x,0)),s[a[i].z].insert(mp(x,len[x]+1));
		upd(x,y,v[x][y-1]);
		printf("%lld\n",ans);
	}
	return 0;
}