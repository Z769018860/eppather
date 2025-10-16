
#include<bits/stdc++.h>
typedef long long ll;
#define pii pair<int,int>
#define fi first
#define se second
#define vec vector
#define eb emplace_back
using namespace std;
const int maxn=5e5+5;
int opt[maxn];
int a[maxn],b[maxn];
int w[2*maxn],mat[2*maxn];
pii ed[2*maxn];
bool dir[2*maxn];
map<pii,int> id;
int read(){
    int x=0,y=1;
    char ch=getchar();
    while(ch<48||ch>57){if(ch==45)y=-1;ch=getchar();}
    while(ch>=48&&ch<=57)x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    return x*y;
}
vec<pii> e[maxn];
int tag,vis[maxn];
int rt,dep[maxn];
void dfs1(int x,int faid){
	vis[x]=tag;
	for(auto p:e[x]){
		int y=p.fi,id=p.se;
		if(id==mat[faid])continue;
		if(vis[y]==tag){rt=x;continue;}
		dep[y]=dep[x]+1;dfs1(y,id);
	}
	return ;
}
vec<int> C,P,Pt,cir;
void dfs2(int x,int faid){
	vis[x]=tag;Pt.eb(x);
	for(auto p:e[x]){
		int y=p.fi,id=p.se;
		if(id==mat[faid])continue;
		P.eb(id);
		if(vis[y]==tag){if(dep[y]<=dep[x])C=P,cir=Pt;P.pop_back();continue;}
		dep[y]=dep[x]+1;dfs2(y,id);
		P.pop_back();
	}
	Pt.pop_back();
	return ;
}
int f[maxn],siz[maxn],bl[maxn];
int dfsnum,dfn[maxn],rdfn[maxn];
void dfs3(int x,int fa){
	bl[x]=rt;f[x]=fa;dfn[x]=++dfsnum;rdfn[dfsnum]=x;siz[x]=1;opt[x]=2;
	for(auto p:e[x])if(p.fi!=fa)dfs3(p.fi,x),siz[x]+=siz[p.fi];
	return ;
}
int val1[2*maxn],val2[2*maxn];
int mx[4*maxn],laz[4*maxn];
void pushup(int k){mx[k]=max(mx[k<<1],mx[k<<1|1]);return ;}
void add_laz(int k,int v){mx[k]+=v,laz[k]+=v;return ;}
void pushdown(int k){
	if(laz[k]==0)return ;
	add_laz(k<<1,laz[k]),add_laz(k<<1|1,laz[k]);
	laz[k]=0;
	return ;
}
void modify(int k,int l,int r,int x,int y,int v){
	if(l>r)return ;
	if(l>=x&&r<=y){add_laz(k,v);return ;}
	int mid=l+((r-l)>>1);
	pushdown(k);
	if(x<=mid)modify(k<<1,l,mid,x,y,v);
	if(y>mid)modify(k<<1|1,mid+1,r,x,y,v);
	pushup(k);
	return ;
}
int query(int k,int l,int r,int x,int y){
	if(l>=x&&r<=y)return mx[k];
	int mid=l+((r-l)>>1);
	pushdown(k);
	if(y<=mid)return query(k<<1,l,mid,x,y);
	if(x>mid)return query(k<<1|1,mid+1,r,x,y);
	return max(query(k<<1,l,mid,x,y),query(k<<1|1,mid+1,r,x,y));
}
int main(){
    int n1,n2,op,tot=0;
	n1=read(),n2=read(),op=read();
	for(int i=1;i<=n1;i++)a[i]=read();
	for(int i=1;i<=n1;i++)b[i]=read();
	for(int i=1;i<=n1;i++){
		int u=(a[i]+b[i])%n2+1,v=(a[i]-b[i]+n2)%n2+1;
		if(u>v)swap(u,v);
		ed[++tot]=pii(v,u),w[tot]=read(),id[pii(v,u)]=tot,e[v].eb(pii(u,tot)),mat[tot]=tot;
		if(u!=v){
			ed[++tot]=pii(u,v),w[tot]=read(),id[pii(u,v)]=tot,e[u].eb(pii(v,tot));
			mat[tot]=tot-1,mat[tot-1]=tot;
		}
	}
	int res=0;
	for(int i=1;i<=n2;i++){
		if(vis[i])continue;
		rt=0;tag++;dfs1(i,0);
		if(!rt){rt=i;dfs3(i,0);continue;}
		tag++;dfs2(rt,0);
		for(auto x:cir)opt[x]=1;
		int w1=0,w2=0;
		for(int c=0;c<C.size();c++){
			int id1=C[c],id2=mat[C[c]];
			w1+=w[id1],w2+=w[id2];dir[id1]=0,dir[id2]=1;
			if(id1==id2)w1-=w[id1];
		}
		val1[tag]=w1,val2[tag]=w2;
		res+=max(w1,w2);
	}
	for(int i=1;i<=tot;i++){
		int u=ed[i].fi,v=ed[i].se;
		if(opt[u]==2&&opt[v]==2)continue;
		if(opt[u]==1&&opt[v]==1)continue;
		if(dep[u]<dep[v])res+=w[i];
	}
	int N=dfsnum;
	for(int i=1;i<=dfsnum;i++){
		int x=rdfn[i],y=f[x];
		if(!y)continue;
		int w1=w[id[pii(x,y)]],w2=w[id[pii(y,x)]];
		modify(1,1,N,dfn[bl[x]],dfn[bl[x]]+siz[bl[x]]-1,w2);
		modify(1,1,N,i,i+siz[x]-1,w1-w2);
	}
	for(int i=1;i<=dfsnum;){
		int x=rdfn[i];
		res+=query(1,1,N,i,i+siz[x]-1);
		i+=siz[x];
	}
	printf("%d\n",res);
	int q=read();
	while(q--){
		int x,v;
		x=read(),v=read();
		if(op)x-=res,v-=res;
		v-=w[x];
		int a=ed[x].fi,b=ed[x].se;
		if(opt[a]==2&&opt[b]==2){
			int L=dfn[bl[a]],R=L+siz[bl[a]]-1;
			res-=query(1,1,N,L,R);
			if(dep[a]>dep[b])modify(1,1,N,dfn[a],dfn[a]+siz[a]-1,v);
			else modify(1,1,N,L,dfn[b]-1,v),modify(1,1,N,dfn[b]+siz[b],R,v);
			res+=query(1,1,N,L,R);
		}
		else if(opt[a]==1&&opt[b]==1){
			res-=max(val1[vis[a]],val2[vis[a]]);
			if(dir[x]==0)val1[vis[a]]+=v;else val2[vis[a]]+=v;
			res+=max(val1[vis[a]],val2[vis[a]]);
		}
		else if(dep[a]<dep[b])res+=v;
		w[x]+=v;
		printf("%d\n",res);
	}
    return 0;
}
