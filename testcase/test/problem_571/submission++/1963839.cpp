#include<bits/stdc++.h>
using namespace std;
int n,m,L,R;
#define pb push_back
struct SAT2{
	int hd[20100000],to[40100000],nxt[40100000],cn,N;
	int col[20010000],scc,dfn[20100000],low[20010000],sta[20010000],top;
	bool vis[20010000];
	inline void ad(int u,int v){to[++cn]=v,nxt[cn]=hd[u],hd[u]=cn;}
	inline void dfs(int x){
		dfn[x]=low[x]=++dfn[0],sta[++top]=x,vis[x]=1;
		for(int i=hd[x];i;i=nxt[i]){
			int v=to[i];
			if(!dfn[v])dfs(v),low[x]=min(low[x],low[v]);
			else if(vis[v])low[x]=min(low[x],dfn[v]);
		}
		if(dfn[x]==low[x]){
			col[x]=++scc,vis[x]=0;
			while(sta[top]!=x)vis[sta[top]]=0,col[sta[top]]=scc,top--;
			top--;
		}
	}
	inline void gen(){
		for(int i=1;i<=N;i++)if(!dfn[i])dfs(i);
	}
}T;
vector<int>g_[50100];
int st[101000];
int U[200100],V[201000],W[200100],m_,nn;
vector<int>g[100100];
int so[101000],ee;
void ad(int u,int v,int w){
	m_++;U[m_]=u,V[m_]=v,W[m_]=w;
	g[v].pb(m_),g[u].pb(m_);
}
int build(int l,int r){
	if(l==r)return so[l];
	int on=++n,mid=(l+r)>>1,ls=build(l,mid),rs=build(mid+1,r);
	ad(on,ls,l==mid),ad(on,rs,mid+1==r);
	return on;
}
void dfs(int x,int f){
	ee=0;
	for(int v:g_[x])if(v!=f)so[++ee]=v;
	if(!ee)return;
	int rt=build(1,ee);
	ad(x,rt,ee==1);
	for(int v:g_[x])if(v!=f)dfs(v,x);
}
int S,sz[101000],rt,mx;
bool vis[200100];
void dfs2(int x,int f){
	sz[x]=1;
	for(int i:g[x]){
		int v=x^U[i]^V[i];if(v==f||vis[i])continue;
		dfs2(v,x),sz[x]+=sz[v];int me=max(sz[v],S-sz[v]);
		if(mx>me)mx=me,rt=i;
	}
}
int d[201000];
vector<int>vc;
void dfs3(int x,int f){
	sz[x]=1;
	if(x<=n)vc.pb(x);
	for(int i:g[x]){
		int v=x^U[i]^V[i];if(v==f||vis[i])continue;
		d[v]=d[x]+W[i],dfs3(v,x),sz[x]+=sz[v];
	}
}
int oi[201000][2][2],le;
void sol(int e){
	if(!e)return;vis[e]=1;
	d[U[e]]=d[V[e]]=0,vc.clear(),dfs3(U[e],0);
	vector<int>uc=vc;vc.clear();dfs3(V[e],0);
	for(int step=0;step<2;step++){
		swap(uc,vc);
		int md=0;
		for(int x:vc)md=max(md,d[x]);
		if(vc.empty()||uc.empty())continue;
		for(int sp=0;sp<2;sp++){
			for(int i=0;i<=md;i++)for(int j=0;j<2;j++)for(int k=0;k<2;k++)oi[i][j][k]=++T.N;
			for(int x:vc)for(int o=0;o<2;o++)for(int i=0;i<2;i++){
				if(!sp)T.ad(oi[d[x]][i][o],x+o*n);
				else T.ad(x+(!o)*n,oi[d[x]][i][o]);
			}
			for(int i=1;i<=md;i++)if(i%le)
				for(int o=0;o<2;o++){
					if(!sp)T.ad(oi[i-1][0][o],oi[i][0][o]),T.ad(oi[i][1][o],oi[i-1][1][o]);
					else T.ad(oi[i][0][o],oi[i-1][0][o]),T.ad(oi[i-1][1][o],oi[i][1][o]);
				}
			for(int u:uc)if(st[u]){
				int l=L-W[e]-d[u],r=R-W[e]-d[u];
				l=max(l,0),r=min(r,md);
				if(l>r)continue;
				if(l==0){
					for(int i=0;i<2;i++)for(int j=0;j<2;j++)if(((st[u]>>(i*2+j))&1)){
						if(!sp)T.ad(u+i*n,oi[r][1][j]);
						else T.ad(oi[r][1][j],u+(!i)*n);
					}
				}
				else{
					for(int i=0;i<2;i++)for(int j=0;j<2;j++)if(((st[u]>>(i*2+j))&1)){
						if(!sp)T.ad(u+i*n,oi[l][0][j]);
						else T.ad(oi[l][0][j],u+(!i)*n);
					}
					if(l/le<r/le){
						for(int i=0;i<2;i++)for(int j=0;j<2;j++)if(((st[u]>>(i*2+j))&1)){
							if(!sp)T.ad(u+i*n,oi[r][1][j]);
							else T.ad(oi[r][1][j],u+(!i)*n);
						}
					}
				}
			}
		}
	}
	S=sz[U[e]],mx=S+1,rt=0,dfs2(U[e],0),sol(rt);
	S=sz[V[e]],mx=S+1,rt=0,dfs2(V[e],0),sol(rt);
}
int main(){
	scanf("%d%d%d%d",&n,&m,&L,&R);le=R-L+1;
	nn=n;
	for(int i=1,u,v;i<n;i++)scanf("%d%d",&u,&v),g_[u].pb(v),g_[v].pb(u);
	for(int i=1,x,z;i<=m;i++)scanf("%d%d",&x,&z),st[x]|=(1<<z);
	dfs(1,0);S=n,mx=S+1;
	dfs2(1,0);
	T.N=n*2,n=nn,sol(rt);T.gen();
	bool fl=1;
	for(int i=1;i<=n;i++)fl&=(T.col[i]!=T.col[i+n]);
	puts(fl?"YES":"NO");
	return 0;
}