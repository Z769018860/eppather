#pragma G++ optimize(2)
#pragma GCC optimize(2)
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
#include<cmath>
#define GET getchar()
#define lc (x<<1)
#define rc (x<<1|1)
using namespace std;
typedef long long ll;

namespace FastIO{
	const int L=(1<<20);
	char buf[L],*S,*T;
	#ifdef ONLINE_JUDGE
	inline char getchar(){
		if(S==T){T=(S=buf)+fread(buf,1,L,stdin);if(S==T)return EOF;}
		return *S++;
	}
	#endif
	inline int read(){
		int s=0,f=1;char t=GET;
		while('0'>t||t>'9'){if(t=='-')f=-1;t=GET;}
		while('0'<=t&&t<='9'){s=(s<<1)+(s<<3)+t-'0';t=GET;}
		return s*f;
	}
}
using FastIO::read;

const int N=1000005;
int n,m,Lx[N],Rx[N],val[N],seq[N],tot,Root;
int fa[N][21],Log[N],d[N],siz[N];

struct TArray{
	#define lowbit(x) (x&(-x))
	ll sm[N];
	void add(int x,ll d){
		for(int i=x;i<=n;i+=lowbit(i))
			sm[i]+=d;
	}
	ll sum(int x){
		ll ans=0;
		for(int i=x;i>0;i-=lowbit(i))
			ans+=sm[i];
		return ans;
	}
	ll sum(int l,int r){
		return sum(r)-sum(l-1);
	}
}wd,w;

struct line{
	int Nxt,to;
}l[N*2];
int h[N],cnt;

inline void Link(int u,int v){
	l[++cnt]=(line){h[u],v};h[u]=cnt;
	l[++cnt]=(line){h[v],u};h[v]=cnt;
}

void Dfs(int u,int f){
	siz[u]=1;fa[u][0]=f;d[u]=d[f]+1;
	for(int i=1;i<=20;i++){
		fa[u][i]=fa[fa[u][i-1]][i-1];
	}
	seq[Lx[u]=++tot]=val[u];
	for(int i=h[u],v;i;i=l[i].Nxt){
		v=l[i].to;
		if(v!=f){
			Dfs(v,u);
			siz[u]+=siz[v];
		}
	}
	Rx[u]=tot;
}

int LCA(int x,int y){
	if(d[x]<d[y])swap(x,y);
	for(int i=Log[d[x]];i>=0;i--)
		if(d[fa[x][i]]>=d[y])x=fa[x][i];
	if(x==y)return x;
	for(int i=Log[d[x]];i>=0;i--)
		if(fa[x][i]!=fa[y][i]){
			x=fa[x][i];
			y=fa[y][i];
		}
	return fa[x][0];
}

void Add(int x,int delta){
	
	wd.add(Lx[x],(ll)delta*d[x]);
	w.add(Lx[x],delta);
}

void Add(int a,int b,int delta){
	int g=LCA(a,b);
	Add(a,delta); 
	Add(b,delta); 
	Add(g,-delta);
	if(fa[g][0])Add(fa[g][0],-delta);
}

ll s(int u){
	return w.sum(Lx[u],Rx[u]);
}

ll ss(int u){
	return wd.sum(Lx[u],Rx[u])+(-d[u]+1)*w.sum(Lx[u],Rx[u]);
}

int main(){
	n=read();m=read();Root=read();
	for(int i=2;i<=n;i++)Log[i]=Log[i>>1]+1;
	for(int i=1;i<=n;i++)val[i]=read();
	for(int i=1,x,y;i<n;i++){
		x=read();y=read();
		Link(x,y);
	}
	Dfs(Root,0);
	for(int i=1;i<=n;i++)Add(i,i,val[i]);
	
	for(int i=1,opt;i<=m;i++){
		opt=read();
		if(opt==1){
			int x=read(),y=read(),d=read();
			Add(x,y,d);
		}else if(opt==2){
			int x=read();
			cout<<s(x)<<'\n';
		}else{
			int x=read();
			cout<<ss(x)<<'\n';
		}
	}
	return 0;
}