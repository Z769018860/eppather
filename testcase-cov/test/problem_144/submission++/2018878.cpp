#include<bits/stdc++.h>
#define ll long long
#define RCL(a,b,c,d) memset((a),(b),sizeof(c)*(d))
#define FOR(i,a,b) for(register int i=(a);i<=(b);++i)
#define DOR(i,a,b) for(register int i=(a);i>=(b);--i)
#define main Main();signed main(){ios::sync_with_stdio(0);cin.tie(0);return Main();}signed Main
using namespace std;
const int N=1e6+10;
int n,m,rt;
int a[N];
int dfn[N],l[N],r[N],tot;
struct Binary_Indexed_Trees{
#define lowbit(a) ((a)&(-a))
	ll c[N],n;
	void init(int m){n=m,build();}
	void build(){
		FOR(i,1,n)c[i]=a[dfn[i]];
		FOR(i,1,n)if(i+lowbit(i)<=n)c[i+lowbit(i)]+=c[i];
	}
	void update(int x,int v){for(;x<=n;x+=lowbit(x))c[x]+=v;}
	ll query(int x){
		ll res=0;
		for(;x;x^=lowbit(x))res+=c[x];
		return res;
	}
}bit;
struct CFS{
	int tot,v[N<<1],nxt[N<<1],h[N];
	void init(int n){
		tot=0,RCL(h,0,int,n+5);
	}
	void add_edge(int U,int V){
		v[++tot]=V,nxt[tot]=h[U],h[U]=tot;
	}
}g;
void dfs(int now,int fa){
	dfn[++tot]=now,l[now]=tot;
	for(int i=g.h[now],nxt;i;i=g.nxt[i])if((nxt=g.v[i])!=fa)
		dfs(nxt,now);
	r[now]=tot;
}
signed main(){
	cin>>n>>m>>rt;
	FOR(i,1,n)cin>>a[i];
	FOR(i,1,n-1){
		int u,v;cin>>u>>v;
		g.add_edge(u,v),g.add_edge(v,u);
	}
	dfs(rt,0);
	bit.init(n);
	while(m--){
		int opt,a,x;
		cin>>opt>>a;
		if(opt<2){
			cin>>x;
			bit.update(l[a],x);
		}else cout<<(bit.query(r[a])-bit.query(l[a]-1))<<endl;
	}
	return 0;
}