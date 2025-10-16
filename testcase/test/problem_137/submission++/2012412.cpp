#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
using std::cin;using std::cout;
constexpr int N=140005,M=100005,L=280005,mod=1e9+7;
int n,m,fa[N],val[N],tot,dfn[N],cnt,deep[N],id[L][20],lg2[L],q,a,b,c,p,u,v,ans;
struct A{int a,b,w;}d[M];
std::vector<int>edge[N];
inline int rnd(){return a=(a*b%p+c)%p;}
inline int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
inline void down(int u){
	dfn[u]=++cnt;id[cnt][0]=u;
	for(int i:edge[u]){
		deep[i]=deep[u]+1;
		down(i);
		id[++cnt][0]=u;
	}
}
inline int query(int x,int y){
	int t=lg2[y-x+1];
	if(deep[id[x][t]]<deep[id[y-(1<<t)+1][t]]) return id[x][t];
	return id[y-(1<<t)+1][t];
}
signed main(){


	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	cin>>n>>m;for(int i=1;i<2*n;++i) fa[i]=i;tot=n;
	for(int i=1;i<=m;++i) cin>>d[i].a>>d[i].b>>d[i].w;
	std::sort(d+1,d+m+1,[](A a,A b){return a.w<b.w;});
	for(int i=1;i<=m;++i){
		int fu=find(d[i].a),fv=find(d[i].b);
		if(fu!=fv){
			val[++tot]=d[i].w;
			fa[fu]=fa[fv]=tot;
			edge[tot].push_back(fu);
			edge[tot].push_back(fv);
		}
	}
	deep[tot]=1;down(tot);
	for(int i=2;i<=cnt;++i) lg2[i]=lg2[i>>1]+1;
	for(int i=1;i<=19;++i)
		for(int j=1;j+(1<<i)-1<=cnt;++j)
			if(deep[id[j][i-1]]<deep[id[j+(1<<(i-1))][i-1]]) id[j][i]=id[j][i-1];
			else id[j][i]=id[j+(1<<(i-1))][i-1];
	cin>>q>>a>>b>>c>>p;
	for(int i=1;i<=q;++i){
		u=rnd()%n+1;v=rnd()%n+1;
		ans=(ans+val[query(std::min(dfn[u],dfn[v]),std::max(dfn[u],dfn[v]))])%mod;
	}
	cout<<ans;
	return 0;
}