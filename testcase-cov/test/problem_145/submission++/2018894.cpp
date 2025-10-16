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
	void init(int m){n=m;}
	void update(int x,ll v){for(;x<=n;x+=lowbit(x))c[x]+=v;}
	ll query(int x){
		ll res=0;
		for(;x;x^=lowbit(x))res+=c[x];
		return res;
	}
}bit1,bit2;
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
	for(int i=g.h[now],nxt;i;i=g.nxt[i])if((nxt=g.v[i])!=fa)dfs(nxt,now);
	r[now]=tot;
}
void update(int x,ll y){bit1.update(x,y),bit2.update(x,1ll*(x-1)*y);}
inline ll query(int x){
	return 1ll*x*bit1.query(x)-bit2.query(x);
}
signed main(){
	cin>>n>>m>>rt;
	FOR(i,1,n)cin>>a[i];
	FOR(i,1,n-1){
		int u,v;cin>>u>>v;
		g.add_edge(u,v),g.add_edge(v,u);
	}
	dfs(rt,0);
	bit1.init(n),bit2.init(n);
	FOR(i,1,n)update(l[i],a[i]-a[dfn[l[i]-1]]);
	while(m--){
		int opt,a,x;
		cin>>opt>>a;
		if(opt<2){
			cin>>x;
			update(l[a],x),update(r[a]+1,-x);
		}else cout<<(query(r[a])-query(l[a]-1))<<endl;
	}
	return 0;
}