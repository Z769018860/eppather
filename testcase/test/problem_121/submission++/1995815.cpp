#include<bits/stdc++.h>
#define P pair<int,int>
#define mp make_pair
#define fi first
#define se second
#define N 5010
#define M 500100
using namespace std;

int n,m,tt;
bool ans[M];
struct Node
{
	int ls,rs;
	vector<int>A,B;
	vector<int>queA,queB,id;
	inline void add(int u,int v)
	{
		A.push_back(u);
		B.push_back(v);
	}
	inline void add_que(int u,int v,int w)
	{
		queA.push_back(u);
		queB.push_back(v);
		id.push_back(w);
	}
}node[M<<1];
struct Op
{
	int type,u,v;
}op[M];
struct Bcj
{
	int fa[N],sz[N],top;
	P sta[N];
	int ff(int u){return u==fa[u]?u:ff(fa[u]);}
	inline void init()
	{
		for(int i=1;i<=n;i++)
		{
			fa[i]=i;
			sz[i]=1;
		}
	}
	inline void mg(int u,int v)
	{
		u=ff(u),v=ff(v);
		if(u==v) return;
		if(sz[u]>sz[v]) swap(u,v);
		sta[++top]=mp(u,fa[u]);
		fa[u]=v,sz[v]+=sz[u];
	}
	inline void del(int u)
	{
		for(;top>u;top--)
		{
			int t=sta[top].fi;
			sz[fa[t]]-=sz[t];
			fa[t]=sta[top].se;
		}
	}
	inline bool ask(int u,int v){return ff(u)==ff(v);}
}bcj;
map<P,int>ti;

void build(int now,int l,int r)
{
	if(l==r) return;
	int mid=((l+r)>>1);
	node[now].ls=++tt;
	build(node[now].ls,l,mid);
	node[now].rs=++tt;
	build(node[now].rs,mid+1,r);
}

void add(int now,int l,int r,int u,int v,int p,int q)
{
	if(u<=l && r<=v)
	{
		node[now].add(p,q);
		return;
	}
	int mid=((l+r)>>1);
	if(u<=mid) add(node[now].ls,l,mid,u,v,p,q);
	if(mid<v) add(node[now].rs,mid+1,r,u,v,p,q);
}

void add_que(int now,int l,int r,int u,int p,int q,int id)
{
	if(l==r)
	{
		node[now].add_que(p,q,id);
		return;
	}
	int mid=((l+r)>>1);
	if(u<=mid) add_que(node[now].ls,l,mid,u,p,q,id);
	else add_que(node[now].rs,mid+1,r,u,p,q,id);
}

void dfs(int now,int l,int r)
{
	int t=bcj.top;
	for(int i=0;i<node[now].A.size();i++)
	{
		int a=node[now].A[i];
		int b=node[now].B[i];
		bcj.mg(a,b);
	}
	if(l==r)
	{
		for(int i=0;i<node[now].id.size();i++)
		{
			int a=node[now].queA[i];
			int b=node[now].queB[i];
			ans[node[now].id[i]]=bcj.ask(a,b);
		}
		bcj.del(t);
		return;
	}
	int mid=((l+r)>>1);
	dfs(node[now].ls,l,mid);
	dfs(node[now].rs,mid+1,r);
	bcj.del(t);
}

int main()
{
	int Q=0;
	cin>>n>>m;
	build(tt=1,1,m);
	for(int i=1;i<=m;i++)
	{
		int o,p,q;
		scanf("%d%d%d",&o,&p,&q);
		if(p>q) swap(p,q);
		if(o==2) add_que(1,1,m,i,p,q,++Q);
		else if(!o) ti[mp(p,q)]=i;
		else
		{
			add(1,1,m,ti[mp(p,q)],i,p,q);
			ti.erase(mp(p,q));
		}
	}
	for(auto t:ti) add(1,1,m,t.se,m,t.fi.fi,t.fi.se);
	
	bcj.init();
	dfs(1,1,m);
	for(int i=1;i<=Q;i++) printf("%c\n",ans[i]?'Y':'N');
}