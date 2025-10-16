#include<bits/stdc++.h>
#define int long long
#define N 1000005
#define pb push_back
#define fi first
#define se second
#define pii pair<int,int>
#define mem(x) (memset(x,0,sizeof(x)))
using namespace std;
int id[N],le[N],cn,root[2][N],dfn[N],idx,n,K,dr[N],rt0[N],ln[N],cn2; vector<int>g[N];
int par[N],son[N],sz[N],top[N],ok[N][2],INF=(int)1e18;
int mul(int x,int y){
	if(!y||!x) return 0;
	if(x>INF/y) return INF+1;
	return x*y; }
struct node{
	int a[2][2];
	node(){memset(a,0,sizeof(a));}
	node(int p,int q,int r,int s){
		a[0][0]=p,a[0][1]=q,a[1][0]=r,a[1][1]=s;
	}friend node operator * (const node& x,const node& y){
		node c; for(int i=0;i<2;i++) for(int j=0;j<2;j++)
			for(int k=0;k<2;k++) c.a[i][j]=min(c.a[i][j]+mul(x.a[i][k],y.a[k][j]),INF+1);
		return c;}
}; struct SGT_light{
	int lc[N<<4],rc[N<<4],ml[N<<4];
	void build(int &rt,int l,int r){
		if(l>r) return; ml[rt=(++cn)]=1; if(l==r) return;
		int md=(l+r)>>1; build(lc[rt],l,md),build(rc[rt],md+1,r);	
	}void modf(int rt,int l,int r,int x,int d){
		if(l>r) return; if(l==r) return ml[rt]=d,void();
		int md=(l+r)>>1; if(x<=md) modf(lc[rt],l,md,x,d);
		else modf(rc[rt],md+1,r,x,d); ml[rt]=mul(ml[lc[rt]],ml[rc[rt]]);
	}int ask(int rt){if(!rt) return 1; return ml[rt];}
}; SGT_light T[2];

struct SGT_heavy{
	node T[N<<3]; int lc[N<<3],rc[N<<3];
	void build(int &rt,int l,int r){
		if(l>r) return; T[rt=(++cn2)]=node(1,0,0,1); if(l==r) return; 
		int md=(l+r)>>1; build(lc[rt],l,md),build(rc[rt],md+1,r);
	}void modf(int rt,int l,int r,int x,node d){
		if(l==r){T[rt]=d; return;} int md=(l+r)>>1;
		if(x<=md) modf(lc[rt],l,md,x,d); else modf(rc[rt],md+1,r,x,d);
		T[rt]=T[lc[rt]]*T[rc[rt]];
	}}tx;
int F(int x,int o){return tx.T[rt0[x]].a[0][o];}




void dfs1(int x,int fa){
	sz[x]=1,par[x]=fa,top[x]=x;
	int mxid=0; for(int &u:g[x])
		if(u!=fa){
			dfs1(u,x),sz[x]+=sz[u];
			if(sz[mxid]<sz[u]) mxid=u;
		}son[x]=mxid;
	for(int &u:g[x]) if(u!=fa&&u!=son[x]) id[u]=(++le[x]);
}node getF(int x){return node(T[1].ask(root[1][x])*ok[x][0],T[0].ask(root[0][x])*ok[x][1],T[1].ask(root[1][x])*ok[x][0],0);}
void dfs2(int x,int fa,int tp){
	top[x]=tp; if(son[x]) dfs2(son[x],x,tp);
	for(int &u:g[x]) if(u!=fa&&u!=son[x])
		dfs2(u,x,u); dfn[x]=(++ln[tp]);
}void dfs(int x,int fa){
	for(int &u:g[x]) if(u!=fa) dfs(u,x);
	tx.modf(rt0[top[x]],1,ln[top[x]],dfn[x],getF(x));
	if(par[x]&&x==top[x]){int f=par[x]; 
		T[0].modf(root[0][f],1,le[f],id[x],F(x,0));
		T[1].modf(root[1][f],1,le[f],id[x],min(F(x,0)+F(x,1),INF+1));
	}
}void chg(int x,int c1,int c2){
	ok[x][0]=c1,ok[x][1]=c2;
	tx.modf(rt0[top[x]],1,ln[top[x]],dfn[x],getF(x)),x=top[x];
	while(par[x]){int f=par[x];
		T[0].modf(root[0][f],1,le[f],id[x],F(x,0));
		T[1].modf(root[1][f],1,le[f],id[x],min(F(x,0)+F(x,1),INF+1));
		tx.modf(rt0[top[f]],1,ln[top[f]],dfn[f],getF(f)),x=top[f];}
}int qry(){return min(F(1,0)+F(1,1),INF+1);}
int po[N],sl,a[N]; signed main(){
	scanf("%lld%lld",&n,&K);
	for(int i=1;i<n;i++) scanf("%lld",&po[i]),po[i]++;
	for(int i=1,u;i<n;i++){
		scanf("%lld",&u),u++;
		g[u].pb(po[i]),g[po[i]].pb(u);
	}scanf("%lld",&sl); int sp=K;
	for(int i=1;i<=sl;i++) scanf("%lld",&a[i]),a[i]++;
	sort(a+1,a+sl+1); vector<int>vi; for(int i=1;i<=n;i++) ok[i][0]=ok[i][1]=1;
	for(int i=1;i<=sl;i++){
		ok[a[i]][0]=0,ok[a[i]][1]=1,vi.pb(a[i]);	
		for(int t=a[i-1]+1;t<a[i];t++) ok[t][0]=1,ok[t][1]=0;
	}dfs1(1,0),dfs2(1,0,1);
	for(int i=1;i<=n;i++){
		for(int o=0;o<2;o++) T[o].build(root[o][i],1,le[i]);
		if(i==top[i]) tx.build(rt0[i],1,ln[i]);	
	}dfs(1,0); for(int i=sl;~i;i--){
		if(qry()>K) break;
		else if(i){K-=(qry()-1);
			chg(a[i],1,0),vi.pop_back();
			if(i!=sl) for(int t=a[i]+1;t<=a[i+1];t++)
				chg(t,1,1);
		}}
	for(int i=1;i<=n&&K>0;i++) if(ok[i][0]&&ok[i][1]){
		K--,chg(i,0,1); if(qry()>K){vi.pb(i); continue;}
		K-=(qry()-1),chg(i,1,0);
	}if(K>0) return 0; for(int &u:vi) printf("%lld ",u-1); puts("");
	return 0;
}