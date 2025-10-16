
#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pii pair<int,int>
#define mp make_pair
#define pb push_back
const int mod=998244353;
const int inf=0x3f3f3f3f;
int Wei[1000005];
array<int,3> bl[1000005];
struct SolveTree
{
	vector<vector<int> > g;
	vector <int> dfn,R,t,lz,par,dep;
	int n,uid,tid,clk;
	map <int,int> ma;
	void dfs0(int u,int fa)
	{
		dfn[u]=R[u]=++clk,par[u]=fa;
		
		for(int i=0;i<g[u].size();i++)
		{
			int v=g[u][i];
			if(v==fa) continue;
			dep[v]=dep[u]+1;
			dfs0(v,u);
			R[u]=R[v];
		}
	}
	void pushdown(int id)
	{
		if(lz[id])
		{
			lz[id<<1]+=lz[id],lz[id<<1|1]+=lz[id];
			t[id<<1]+=lz[id],t[id<<1|1]+=lz[id];
			lz[id]=0;
		}
	}
	void update(int id,int l,int r,int x,int y,int d)
	{
		if(x<=l&&r<=y) 
		{
			t[id]+=d,lz[id]+=d;
			return;
		}
		pushdown(id);
		int mid=(l+r)>>1;
		if(x<=mid) update(id<<1,l,mid,x,y,d);
		if(y>mid) update(id<<1|1,mid+1,r,x,y,d);
		t[id]=max(t[id<<1],t[id<<1|1]);
	}
	int query(int id,int l,int r,int x,int y)
	{
		if(x<=l&&r<=y) return t[id];
		pushdown(id);
		int mid=(l+r)>>1,res=0;
		if(x<=mid) res=max(res,query(id<<1,l,mid,x,y));
		if(y>mid) res=max(res,query(id<<1|1,mid+1,r,x,y));
		return res;
	}
	void init(vector <array<int,4> > es)
	{
		n=es.size()+1;
		g.resize(n+5);
		t.resize(4*n+5),lz.resize(4*n+5);
		dfn.resize(n+5),R.resize(n+5),par.resize(n+5),dep.resize(n+5);
		for(int i=0;i<es.size();i++)
		{
			int u=es[i][0],v=es[i][1];
			if(!ma[u]) ma[u]=++uid;
			if(!ma[v]) ma[v]=++uid;
			u=ma[u],v=ma[v];
			g[u].pb(v);
			g[v].pb(u);
	
	
			bl[es[i][2]]={tid,v,u},bl[es[i][3]]={tid,u,v};
		}
		dfs0(1,-1);
	
	
	
		for(int i=0;i<es.size();i++)
		{
			int u=es[i][0],v=es[i][1];
			u=ma[u],v=ma[v];
			if(dep[u]>dep[v]) swap(u,v),swap(es[i][2],es[i][3]);
			update(1,1,n,dfn[v],R[v],Wei[es[i][2]]);
			if(dfn[v]>1) update(1,1,n,1,dfn[v]-1,Wei[es[i][3]]);
			if(R[v]<n) update(1,1,n,R[v]+1,n,Wei[es[i][3]]);
		}
	}	
	void upd(int eid,int val)
	{
		int u=bl[eid][1],v=bl[eid][2];
		if(dep[u]>dep[v]) update(1,1,n,dfn[u],R[u],val-Wei[eid]),Wei[eid]=val;
		else
		{
			if(dfn[v]>1) update(1,1,n,1,dfn[v]-1,val-Wei[eid]);
			if(R[v]<n) update(1,1,n,R[v]+1,n,val-Wei[eid]);
			Wei[eid]=val;
		}
	}
	int calc()
	{
		return query(1,1,n,1,n);
	}
}tr[500005];
struct SolveCycle
{
	vector <vector<array<int,3> > > g;
	vector <int> deg;
	int n,uid,cid;
	map <int,int> ma;
	int ans=0,sa=0,sb=0,cyclen=0;
	void init(vector <array<int,4> > es)
	{
		n=es.size()+1;
		g.resize(n+5);
		deg.resize(n+5);
		for(int i=0;i<es.size();i++)
		{
			int u=es[i][0],v=es[i][1];
			if(!ma[u]) ma[u]=++uid;
			if(!ma[v]) ma[v]=++uid;
			u=ma[u],v=ma[v];
			g[u].pb({v,es[i][2],es[i][3]});
			g[v].pb({u,es[i][3],es[i][2]});
		
			bl[es[i][2]]={-cid,-1,-1},bl[es[i][3]]={-cid,-1,-1};
		}
		for(int i=1;i<=n;i++) deg[i]=g[i].size();
		queue <int> q;
		while(q.size()) q.pop();
		for(int i=1;i<=n;i++) if(deg[i]==1) q.push(i);
		while(q.size())
		{
			int u=q.front();
			deg[u]=-1;
			q.pop();
			for(int i=0;i<g[u].size();i++)
			{
				int v=g[u][i][0];
				if(deg[v]<0) continue;
				deg[v]--;
				if(deg[v]==1) q.push(v);
				ans+=Wei[g[u][i][1]];
				bl[g[u][i][1]]={-cid,0,0};
			}
		}
		for(int s=1;s<=n;s++) if(deg[s]==2) cyclen++;
	
		for(int s=1;s<=n;s++) if(deg[s]==2)
		{
			int tmps=s,lst=-1;
			while(1)
			{
				bool Flg=0;
				for(int i=0;i<g[s].size();i++) if(deg[g[s][i][0]]==2&&g[s][i][1]!=lst&&g[s][i][2]!=lst)
				{
					int v=g[s][i][0];
			
					sa+=Wei[g[s][i][1]];
					bl[g[s][i][1]]={-cid,1,1};
					if(cyclen==1)
					{
						Flg=1;
						break;
					}
					sb+=Wei[g[s][i][2]];
					bl[g[s][i][2]]={-cid,2,2};
					if(v==tmps) Flg=1;
					lst=g[s][i][2],s=v;
					break;
				} 
				if(Flg) break;
			}
			break;
		}
	
	
	}
	void upd(int eid,int val)
	{

		if(bl[eid][1]==0) ans+=val-Wei[eid];
		if(bl[eid][1]==1) sa+=val-Wei[eid];
		if(bl[eid][1]==2) sb+=val-Wei[eid];
		Wei[eid]=val;

	}
	int calc()
	{
		return ans+max(sa,sb);
	}
}cy[500005];
int n,m,tp;
int A[500005],B[500005];
vector <array<int,3> > g[500005];
bool vis[500005],vise[1000005];
vector <array<int,4> > nw;
int cntu=0;
void dfs2(int u)
{
	vis[u]=1;
	cntu++;
	for(int i=0;i<g[u].size();i++)
	{
		int v=g[u][i][0];
		if(!vis[v]) dfs2(v);
		if(!vise[min(g[u][i][1],g[u][i][2])]) vise[min(g[u][i][1],g[u][i][2])]=1,nw.pb({u,v,g[u][i][1],g[u][i][2]});
	}
}
int ntr=0,ncy=0;
int query()
{
	int ans=0;
	for(int i=1;i<=ntr;i++) ans+=tr[i].calc();
	for(int i=1;i<=ncy;i++) ans+=cy[i].calc();
	return ans;
}
void solve()
{
	cin>>m>>n>>tp;
	for(int i=1;i<=m;i++) cin>>A[i];
	int cnt=0;
	for(int i=1;i<=m;i++) 
	{
		cin>>B[i];
		int u=(A[i]-B[i]+n)%n;
		int v=(A[i]+B[i])%n;
		if(u>v) swap(u,v);
		u++,v++;
	
		if(u==v) cnt++,g[u].pb({v,cnt,cnt}),g[v].pb({u,cnt,cnt});
		else g[u].pb({v,cnt+1,cnt+2}),g[v].pb({u,cnt+2,cnt+1}),cnt+=2;
	}
	for(int i=1;i<=cnt;i++) cin>>Wei[i];
	for(int i=1;i<=n;i++) if(!vis[i]) 
	{
		nw.clear(),cntu=0;
		dfs2(i);

		
		if(nw.size()+1==cntu) ntr++,tr[ntr].tid=ntr,tr[ntr].init(nw);
		else ncy++,cy[ncy].cid=ncy,cy[ncy].init(nw);
	
	}

	int lstans=query();
	cout<<lstans<<"\n";
	int q;
	cin>>q;
	while(q--)
	{
		int x,v;
		cin>>x>>v;
		x-=lstans*tp,v-=lstans*tp;
	
		if(bl[x][0]>=1) lstans-=tr[bl[x][0]].calc(),tr[bl[x][0]].upd(x,v),lstans+=tr[bl[x][0]].calc();
		else lstans-=cy[-bl[x][0]].calc(),cy[-bl[x][0]].upd(x,v),lstans+=cy[-bl[x][0]].calc();
		cout<<lstans<<"\n";
	}
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);


	int _=1;

	while(_--) solve();
	return 0;
}