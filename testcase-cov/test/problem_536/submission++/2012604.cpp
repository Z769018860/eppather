#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,s,t,dis[100005],now[100005],k,c,tot,ans[100005],num[100005];
struct ss{
	int v,w,fx;
};
vector<ss>q[100005];
bool bfs(){
	memset(dis,0,sizeof(dis));
	queue<int>que;que.push(s);dis[s]=1;
	now[s]=0;
	while(que.size()){
		int x=que.front();que.pop();
		for(int i=0;i<q[x].size();i++){
			int v=q[x][i].v,w=q[x][i].w;
			if(!dis[v]&&w){
				dis[v]=dis[x]+1;now[v]=0;
				que.push(v);
				if(v==t)return 1;
			}
		}
	}
	return 0;
}
int dfs(int x,int flow){
	if(x==t)return flow;
	int res=flow;
	for(int i=0;i<q[x].size()&&res;i++){
		int v=q[x][i].v;
		now[x]=i;
		if(dis[v]==dis[x]+1&&q[x][i].w){
			int k=dfs(v,min(res,q[x][i].w));
			if(!k)dis[v]=0;
			q[x][i].w-=k;
			q[v][q[x][i].fx].w+=k;
			res-=k;
		}
	}
	return flow-res;
}
int dinic(){
	int maxn=0;
	while(bfs()){
		maxn+=dfs(s,1e18);
	}	
	return maxn;
}
void add(int u,int v,int w){
	q[u].push_back(ss{v,w,q[v].size()});
	q[v].push_back(ss{u,0,q[u].size()-1});
}
signed main(){
	scanf("%lld%lld",&k,&c);tot=k+c;
	scanf("%lld",&n);
	s=++tot,t=++tot;
	for(int i=1;i<=n;i++){
		int w1,w2;scanf("%lld%lld",&w1,&w2);tot++;
		num[tot]=i;
		add(s,tot,1);add(tot,w1,1);add(tot,w2+k,1);
	}
	scanf("%lld",&m);
	for(int i=1;i<=m;i++){
		int w1,w2;scanf("%lld%lld",&w1,&w2);tot++;
		add(w1,tot,1);add(w2+k,tot,1);add(tot,t,1);
	}
	dinic();
	for(int i=0;i<q[s].size();i++){
		int v=q[s][i].v;
		if(!q[s][i].w&&!dis[v])ans[num[v]]=1;
	}
	for(int i=1;i<=n;i++)printf("%lld\n",ans[i]);
}