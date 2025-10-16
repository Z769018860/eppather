#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N=2e5+5;
const int inf=0x3f3f3f3f;

inline int read(){
	int f=1,x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+ch-48;
		ch=getchar();
	}
	return f*x;
}

int n,m,k;
struct edge{
	int u,v,w;
}e[N];
bool cmp(edge A,edge B){
	return A.w<B.w;
}
int f[N];
int find(int x){
	if(x==f[x])return x;
	return f[x]=find(f[x]);
}
int cnt,val[N],lg[N];
vector <int> G[N];
int up[N][15],dep[N];
void Dfs(int x,int fa){
	up[x][0]=fa,dep[x]=dep[fa]+1;
	for(int i=1;i<=lg[dep[x]];i++)up[x][i]=up[up[x][i-1]][i-1];
	for(int i=0;i<G[x].size();i++){
		int y=G[x][i];
		if(y==fa)continue;
		Dfs(y,x);
	}
}
int lca(int u,int v){
	if(dep[u]>dep[v])swap(u,v);
	for(int i=lg[dep[v]];i>=0;i--){
		if(dep[up[v][i]]>=dep[u])v=up[v][i];
	}
	if(u==v)return val[u];
	for(int i=lg[dep[v]];i>=0;i--){
		if(up[u][i]!=up[v][i]){
			u=up[u][i];
			v=up[v][i];
		}
	}
	if(up[u][0]==0)return -1;
	return val[up[u][0]];
}
signed main(){
	n=read(),m=read(),k=read();
	for(int i=1;i<=2*n;i++){
		f[i]=i;
		lg[i]=lg[i-1];
		if(i==(1<<lg[i-1]))lg[i]++;
	}
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		e[i]=edge{u,v,w};
	}
	int tmp=0;
	sort(e+1,e+m+1,cmp);
	cnt=n;
	for(int i=1;i<=m;i++){
		int u=e[i].u,v=e[i].v,w=e[i].w;
		int fu=find(u),fv=find(v);
		if(fu!=fv){
			f[fu]=f[fv]=++cnt;
			G[fu].push_back(cnt),G[fv].push_back(cnt);
			G[cnt].push_back(fu),G[cnt].push_back(fv);
			val[cnt]=e[i].w;
			tmp++;
		}
		if(tmp==n-1)break;
	}
	Dfs(find(1),0);
	while(k--){
		int u=read(),v=read();
		printf("%lld\n",lca(u,v));
	}
	return 0;
}