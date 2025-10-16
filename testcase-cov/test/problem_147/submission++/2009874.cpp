#include<iostream>
#include<vector>
using namespace std;
#define ll long long
#define endl '\n'
#define N 1000005
int n,m,r;
int a[N];
struct BIT{
	#define lowbit(x) (x&(-x))
	ll c[N],c2[N];
	void add(int x,ll k){
		for(int i=x;i<=n;i+=lowbit(i))
			c[i]+=k,c2[i]+=k*x;
	}
	void update(int x,int y,ll k){
		add(x,k);
		add(y+1,-k);
	}
	ll sum(int x){
		ll res1=0,res2=0;
		for(int i=x;i;i-=lowbit(i))
			res1+=c[i],res2+=c2[i];
		return res1*(x+1)-res2;
	}
	ll query(int x,int y){
		return sum(y)-sum(x-1);
	}
}B;
vector<int> e[N];
int dfn[N],siz[N],top[N],fa[N],dep[N],son[N];
void dfs1(int u,int f){
	siz[u]=1,dep[u]=dep[f]+1;
	for(int v:e[u]){
		if(v==f) continue;
		dfs1(v,u);
		siz[u]+=siz[v],fa[v]=u;
		if(siz[v]>siz[son[u]]) son[u]=v;
	}
}
void dfs2(int u,int t){
	top[u]=t,dfn[u]=++dfn[0];
	if(son[u]) dfs2(son[u],t);
	for(int v:e[u]) if(v!=fa[u]&&v!=son[u]) dfs2(v,v);
}
ll query(int x,int y){
	ll ans=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]]) swap(x,y);
		ans+=B.query(dfn[top[y]],dfn[y]);
		y=fa[top[y]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	ans+=B.query(dfn[x],dfn[y]);
	return ans;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>n>>m>>r;
	for(int i=1;i<=n;++i) cin>>a[i];
	for(int i=1,x,y;i<n;++i){
		cin>>x>>y;
		e[x].push_back(y);
		e[y].push_back(x);
	}
	dfs1(r,0);
	dfs2(r,r);
	for(int i=1;i<=n;++i) B.update(dfn[i],dfn[i],a[i]);
	int op,x,y;
	while(m--){
		cin>>op>>x>>y;
		if(op==1) B.update(dfn[x],dfn[x],y);
		if(op==2) B.update(dfn[x],dfn[x]+siz[x]-1,y);
		if(op==3) cout<<query(x,y)<<endl;
	}
	return 0;
}