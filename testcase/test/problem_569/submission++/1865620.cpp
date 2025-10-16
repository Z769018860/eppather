#include<bits/stdc++.h>
#define pb push_back
#define MP make_pair
#define pii pair<int,int>
#define pil pair<int,ll>
#define pli pair<ll,int>
#define fi first
#define se second
using namespace std;
typedef long long ll;
template<typename T>void readmain(T &x){
    bool neg=false;unsigned int c=getchar();
    for(;(c^48)>9;c=getchar())if(c=='-')neg=true;
    for(x=0;(c^48)<10;c=getchar())x=(x<<3)+(x<<1)+(c^48);
    if(neg)x=-x;
}
template<typename T>T& read(T &x){readmain(x);return x;}
template<typename T,typename ...Tr>void read(T &x,Tr&... r){readmain(x);read(r...);}
constexpr int N=100005,inf=1e9;
int n,m,ans,s,t,MAXN,tot;
vector<int> id[N];
string a[N];
namespace MAXF{
	constexpr int N=100005,M=300005;
	int edgenum=1,head[N],cur[N],Next[M*2],vet[M*2],dis[N];
	int flw[M*2],inf=1e9;
	queue<int> q;
	void add(int u,int v,int w){
		edgenum++;
		Next[edgenum]=head[u];
		vet[edgenum]=v;
		flw[edgenum]=w;
		head[u]=edgenum;
	}
	void ADD(int u,int v,int w){add(u,v,w);add(v,u,0);}
	bool bfs(int s,int t){
		for(int i=1;i<=MAXN;i++)cur[i]=head[i],dis[i]=-1;
		while(!q.empty())q.pop();
		q.push(s);dis[s]=1;
		while(!q.empty()){
			int u=q.front();
			q.pop();
			for(int e=head[u];e;e=Next[e]){
				int v=vet[e];
				if(flw[e]>0&&dis[v]==-1){
					dis[v]=dis[u]+1;
					if(v==t)return 1;
					q.push(v);
				}
			}
		}
		return 0;
	}
	int dfs(int u,int t,int flow){
		if(!flow||u==t)return flow;
		int used=0;
		for(int e=cur[u];e;e=Next[e]){
			int v=vet[e];cur[u]=e;
			if(dis[v]==dis[u]+1){
				int tmp=dfs(v,t,min(flow-used,flw[e]));
				if(tmp==0)continue;
				flw[e]-=tmp;flw[e^1]+=tmp;
				used+=tmp;
				if(flow==used)break;
			}
		}
		return used;
	}
	int dinic(int s,int t){int FLOW=0;while(bfs(s,t))FLOW+=dfs(s,t,inf);return FLOW;}
}
using MAXF::ADD;
int main(){
	read(n,m);
	for(int i=1;i<=n;i++){
		cin>>a[i];a[i]='$'+a[i];
		id[i].resize(m+3);
		for(int j=1;j<=m;j++)id[i][j]=++tot,ans+=(a[i][j]=='2');
	}
	s=++tot,MAXN=t=++tot;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]=='*')continue;
			if((i+j)&1)ADD(s,id[i][j],1);
			else ADD(id[i][j],t,1);
			if(a[i][j]=='2')continue; 
			if(i<n&&a[i+1][j]!='*'&&a[i+1][j]!='2'&&a[i][j]!=a[i+1][j]){
				int u=id[i][j],v=id[i+1][j];
				if(!((i+j)&1))swap(u,v);
				ADD(u,v,1);
			}
			if(j<m&&a[i][j+1]!='*'&&a[i][j+1]!='2'&&a[i][j]!=a[i][j+1]){
				int u=id[i][j],v=id[i][j+1];
				if(!((i+j)&1))swap(u,v);
				ADD(u,v,1);
			}
		}
	}
	printf("%d\n",MAXF::dinic(s,t)+ans);
    return 0;
}