#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N=2e2+7,M=5e3+7;
constexpr ll inf=0x3f3f3f3f3f3f3f3f;
struct edge{
	int to,cap,nxt;
}e[M<<1];
int head[N],ecnt,dis[N];
int temp[N];
void add_edge(int u,int v,int w){
	e[ecnt]={v,w,head[u]},head[u]=ecnt++;
	e[ecnt]={u,0,head[v]},head[v]=ecnt++;
}
bool bfs(int s,int t){
	memset(dis,-1,sizeof(dis));
	queue<int>q;
	q.emplace(s);
	dis[s]=0;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i!=-1;i=e[i].nxt){
			int v=e[i].to;
			if(e[i].cap&&dis[v]==-1)
				dis[v]=dis[u]+1,q.emplace(v);
		}
	}
	return dis[t]!=-1;
}
ll dfs(int u,int t,ll lim){
	if(!lim)
		return 0;
	if(u==t)
		return lim;
	ll flow=0;
	for(int &i=head[u];i!=-1;i=e[i].nxt){
		if(!e[i].cap||dis[e[i].to]!=dis[u]+1)continue;
		ll delta=dfs(e[i].to,t,min<ll>(lim-flow,e[i].cap));
		flow+=delta;
		e[i].cap-=delta,e[i^1].cap+=delta;
		if(flow==lim)
			return flow;
	}
	return flow;
}
ll flow(int s,int t){
	ll res=0;
	memcpy(temp,head,sizeof(head));
	while(bfs(s,t)){
		res+=dfs(s,t,inf);
		memcpy(head,temp,sizeof(temp));
	}
	return res;
}
int main(){
	memset(head,-1,sizeof(head));
	cin.tie(nullptr)->sync_with_stdio(false);
	int n,m,s,t;
	cin>>n>>m>>s>>t;
	for(int i=1,u,v,w;i<=m;i++)
		cin>>u>>v>>w,add_edge(u,v,w);
	cout<<flow(s,t)<<'\n';
	return 0;
}