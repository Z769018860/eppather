#include<bits/stdc++.h>
using namespace std;
template<typename T>inline void read(T &x){
	x=0;
	char ch=getchar();
	bool flag=0;
	while(ch>'9'||ch<'0') flag=flag||ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	x=flag?-x:x;
}
template<typename T,typename ...Args>inline void read(T &x,Args &...args){
	read(x),read(args...);
}
template<typename T>inline void prt(T x){
	if(x>9) prt(x/10);
	putchar(x%10+'0');
}
template<typename T>inline void put(T x){
	if(x<0) putchar('-'),x=-x;
	prt(x);
}
template<typename T>inline void put(char ch,T x){
	put(x),putchar(ch);
}
template<typename T,typename ...Args>inline void put(char ch,T x,Args ...args){
	put(ch,x),put(ch,args...);
}
#define N 200005
int n,m,L,R;
namespace Graph{
	#define M 40000005
	struct edge{
		int v,nxt;
	}e[M<<1];
	int head[M],cnt;
	inline void add(int u,int v){
		e[++cnt]=(edge){v,head[u]},head[u]=cnt;
	}
	int dfn[M],low[M],sta[M],vis[M],col[M],idx,tp,k,num;
	inline void tarjan(int x){
		dfn[x]=low[x]=++idx,sta[++tp]=x,vis[x]=1;
		for(int i=head[x];i;i=e[i].nxt){
			int v=e[i].v;
			if(!dfn[v]) tarjan(v),low[x]=min(low[x],low[v]);
			else if(vis[v]) low[x]=min(low[x],dfn[v]);
		}
		if(dfn[x]==low[x]){
			int v;num++;
			do v=sta[tp--],vis[v]=0,col[v]=num;
			while(v!=x);
		}
	}
	inline void solve(){
		for(int i=1;i<=k;i++)
			if(!dfn[i]) tarjan(i);
		for(int i=1;i<=n;i++)
			if(col[i]==col[i+n]) return puts("NO"),void();
		puts("YES");
	}
}
struct edge{
	int v,nxt,w;
}e[N<<1];
int head[N],cnt=1,num,stat[N],B;
inline void add(int u,int v,int w){
	e[++cnt]=(edge){v,head[u],w},head[u]=cnt;
	e[++cnt]=(edge){u,head[v],w},head[v]=cnt;
}
vector<int> g[N];

#ifdef DEBUG
int dis[8000][8000];
inline void debug(int x,int fa,int r,int d){
	dis[r][x]=d;
	for(auto v:g[x]) 
		if(v!=fa) debug(v,x,r,d+1);
}
inline void check(int x,int fa,int r,int d){
	if(x<=n) cerr<<"now = "<<x<<' '<<r<<' '<<d<<' '<<dis[x][r]<<endl,assert(dis[x][r]==d);
	for(int i=head[x];i;i=e[i].nxt){
		int v=e[i].v;
		if(v==fa) continue;
		check(v,x,r,d+e[i].w);
	}
}
#endif
inline void dfs1(int x,int fa){
	int lst=0;
	for(auto v:g[x]){
		if(v==fa) continue;
		if(!lst) add(x,v,1),lst=x;
		else add(lst,++num,0),add(num,v,1),lst=num;
		dfs1(v,x);
	}
}
int siz[N],maxs,sum,id,idx;
bool vis[N];
inline void get_siz(int x,int fa){
	siz[x]=1;
	for(int i=head[x];i;i=e[i].nxt){
		int v=e[i].v;
		if(v==fa||vis[i>>1]) continue;
		get_siz(v,x),siz[x]+=siz[v];
	}
}
inline void get_wc(int x,int fa){
	for(int i=head[x];i;i=e[i].nxt){
		int v=e[i].v;
		if(v==fa||vis[i>>1]) continue;
		get_wc(v,x);
		if(max(siz[v],sum-siz[v])<maxs) maxs=max(siz[v],sum-siz[v]),id=i>>1;
	}
}
vector<int> tmp[2][N];
inline void get_dist(int x,int fa,int d,int id){
	if(x<=n) tmp[id][d].emplace_back(x);
	for(int i=head[x];i;i=e[i].nxt){
		int v=e[i].v;
		if(v==fa||vis[i>>1]) continue;
		get_dist(v,x,d+e[i].w,id);
	}
}
int ind0[N],ind1[N],oud0[N],oud1[N];
int preind0[N],preind1[N],preoud0[N],preoud1[N];
int sufind0[N],sufind1[N],sufoud0[N],sufoud1[N];
inline void insert(int a,int lena,int b,int lenb,int w){
	for(int i=0;i<=lenb;i++){
		ind0[i]=++idx,ind1[i]=++idx,oud0[i]=++idx,oud1[i]=++idx;
		for(auto x:tmp[b][i]){
			Graph::add(x,ind0[i]);
			Graph::add(x+n,ind1[i]);
			Graph::add(oud0[i],x);
			Graph::add(oud1[i],x+n);
		} 
	}
	for(int i=0;i<=lenb;i+=B){
		int l=i,r=min(lenb,i+B-1);
		for(int j=l;j<=r;j++){
			preind0[j]=++idx;
			preind1[j]=++idx;
			preoud0[j]=++idx;
			preoud1[j]=++idx;
			if(j!=l){
				Graph::add(preind0[j-1],preind0[j]);
				Graph::add(preind1[j-1],preind1[j]);
				Graph::add(preoud0[j],preoud0[j-1]);
				Graph::add(preoud1[j],preoud1[j-1]);
			}
			Graph::add(ind0[j],preind0[j]);
			Graph::add(ind1[j],preind1[j]);
			Graph::add(preoud0[j],oud0[j]);
			Graph::add(preoud1[j],oud1[j]);
		}
		for(int j=r;j>=l;j--){
			sufind0[j]=++idx;
			sufind1[j]=++idx;
			sufoud0[j]=++idx;
			sufoud1[j]=++idx;
			if(j!=r){
				Graph::add(sufind0[j+1],sufind0[j]);
				Graph::add(sufind1[j+1],sufind1[j]);
				Graph::add(sufoud0[j],sufoud0[j+1]);
				Graph::add(sufoud1[j],sufoud1[j+1]);
			}
			Graph::add(ind0[j],sufind0[j]);
			Graph::add(ind1[j],sufind1[j]);
			Graph::add(sufoud0[j],oud0[j]);
			Graph::add(sufoud1[j],oud1[j]);
		}
	}
	for(int i=0;i<=lena;i++){
		for(auto x:tmp[a][i]){
			if(!stat[x]) continue;
			int l=L-i-w,r=min(lenb,R-i-w);
			if(r<0||l>lenb) continue;
			if(stat[x]>>0&1){
				if(l>=0) Graph::add(x,sufoud0[l]);
				if(l<0||r/B!=l/B) Graph::add(x,preoud0[r]);
				if(l>=0) Graph::add(sufind1[l],x+n);
				if(l<0||r/B!=l/B) Graph::add(preind1[r],x+n);
			}
			if(stat[x]>>1&1){
				if(l>=0) Graph::add(x,sufoud1[l]);
				if(l<0||r/B!=l/B) Graph::add(x,preoud1[r]);
				if(l>=0) Graph::add(sufind0[l],x+n);
				if(l<0||r/B!=l/B) Graph::add(preind0[r],x+n);
			}
			if(stat[x]>>2&1){
				if(l>=0) Graph::add(x+n,sufoud0[l]);
				if(l<0||r/B!=l/B) Graph::add(x+n,preoud0[r]);
				if(l>=0) Graph::add(sufind1[l],x);
				if(l<0||r/B!=l/B) Graph::add(preind1[r],x);
			}
			if(stat[x]>>3&1){
				if(l>=0) Graph::add(x+n,sufoud1[l]);
				if(l<0||r/B!=l/B) Graph::add(x+n,preoud1[r]);
				if(l>=0) Graph::add(sufind0[l],x);
				if(l<0||r/B!=l/B) Graph::add(preind0[r],x);
			}
		}
	}
}
inline void devide(int x){
	get_siz(x,0),maxs=0x3f3f3f3f,sum=siz[x],id=0;
	if(siz[x]==1) return;
	get_wc(x,0),vis[id]=1;
	int a=e[id<<1].v,b=e[id<<1|1].v;
	get_dist(a,0,0,0),get_dist(b,0,0,1);
	int lena=0,lenb=0;
	for(;tmp[0][lena+1].size();lena++);
	for(;tmp[1][lenb+1].size();lenb++);
	insert(0,lena,1,lenb,e[id<<1].w),insert(1,lenb,0,lena,e[id<<1].w);
	for(int i=0;i<=sum;i++) tmp[0][i].clear(),tmp[1][i].clear();
	devide(a),devide(b);
}
int main(){
	read(n,m,L,R),num=n,idx=n<<1,B=R-L+1;
	for(int i=1,u,v;i<n;i++)
		read(u,v),g[u].emplace_back(v),g[v].emplace_back(u);
	for(int i=1,op,x;i<=m;i++) read(x,op),stat[x]|=1<<op;
	#ifdef DEBUG
	for(int i=1;i<=n;i++) debug(i,0,i,0);
	#endif
	dfs1(1,0);
	#ifdef DEBUG
	for(int i=1;i<=n;i++) check(i,0,i,0);
	#endif
	devide(1),Graph::k=idx,Graph::solve();
	return 0;
}