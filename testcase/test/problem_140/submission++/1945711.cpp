#include <bits/stdc++.h>
using namespace std;

#define IOS ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define ios ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define qwq ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define QWQ ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define jump ;return 0;
#define space " "
using mainint=signed;using ll=long long;using ull=unsigned long long;using ld=long double;template<class T>void gmin(T &a,T b){if(a>b) a=b;}template<class T>void gmax(T &a,T b){if(a<b) a=b;}using pii=pair<int,int>;using pll=pair<ll,ll>;using pil=pair<int,ll>;using Pli=pair<ll,int>;const int INF=0x3f3f3f3f;const ll INFINF=0x3f3f3f3f3f3f3f3f;


struct edge{
	int u,v,w;
}e[10005];
int id[105],in[105],pre[105],used[105];
int zhuliu(int root,int n,int m){
	int ans=0;
	while(1){
		for(int i=1;i<=n;++i) in[i]=INF;
		for(int i=1;i<=m;++i){
			int u=e[i].u,v=e[i].v;
			if(e[i].w<in[v] && u!=v){
				in[v]=e[i].w;
				pre[v]=u;
			}
		}
		for(int i=1;i<=n;++i){
			if(i==root) continue;
			if(in[i]==INF) return -1;
		}
		int cnt=0;
		memset(id,0,sizeof(id));
		memset(used,0,sizeof(used));
		in[root]=0;
		for(int i=1;i<=n;++i){
			ans+=in[i];
			int j=i;
			while(used[j]!=i && id[j]==0 && j!=root){
				used[j]=i;
				j=pre[j];
			}
			if(j!=root && id[j]==0){
				cnt++;
				for(int k=pre[j];k!=j;k=pre[k]) id[k]=cnt;
				id[j]=cnt;
			}
		}
		if(cnt==0) break;
		for(int i=1;i<=n;++i)
			if(id[i]==0) id[i]=++cnt;
		for(int i=1;i<=m;++i){
			int u=e[i].u,v=e[i].v;
			e[i].u=id[u];e[i].v=id[v];
			if(id[u]!=id[v]) e[i].w-=in[v];
		}
		n=cnt;
		root=id[root];
	}
	return ans;
}
mainint main(){
	qwq
	int n,m,root;
	cin>>n>>m>>root;
	for(int i=1;i<=m;++i){
		cin>>e[i].u>>e[i].v>>e[i].w;
		if(e[i].u==e[i].v) e[i].w=INF;
	}
	cout<<(zhuliu(root,n,m));
}