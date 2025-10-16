#include<bits/stdc++.h>
using namespace std;
const int N=405,M=1.5e4+5,Inf=INT_MAX;
int n,m;
namespace Dinic{
	int s,t,Cnt=1,Cost;
	int h[N],dis[N],now[N];
	bool in[N];
	struct edge{int next,to,flow,val;}e[M*2];
	inline void qxx(int x,int y,int z,int c){e[++Cnt]=(edge){h[x],y,z,c},h[x]=Cnt,e[++Cnt]=(edge){h[y],x,0,-c},h[y]=Cnt;}
	inline bool spfa(){
		fill(dis+1,dis+n+1,Inf);
		for(int i=1;i<=n;++i)now[i]=h[i];
		queue<int>q;
		q.push(s),in[s]=true,dis[s]=0;
		while(!q.empty()){
			int x=q.front();q.pop();
			in[x]=false;
			for(int i=h[x];i;i=e[i].next){
				int y=e[i].to;
				if(!e[i].flow)continue;
				if(dis[x]+e[i].val<dis[y]){
					dis[y]=dis[x]+e[i].val;
					if(!in[y])q.push(y),in[y]=true;
				}
			}
		}
		return dis[t]!=Inf;
	}
	int dfs(int x,int flow){
		if(x==t||!flow)return flow;
		int Res=flow,i;
		in[x]=true;
		for(i=now[x];i;i=e[i].next){
			int y=e[i].to;
			if(in[y]||!e[i].flow||dis[x]+e[i].val!=dis[y])continue;
			int k=dfs(y,min(Res,e[i].flow));
			if(!k)dis[y]=-Inf;
			e[i].flow-=k,e[i^1].flow+=k,Res-=k,Cost+=k*e[i].val;
			if(!Res)break;
		}
		return in[x]=false,now[x]=i,flow-Res;
	}
	inline int Solve(){
		int Res=0;
		while(spfa())Res+=dfs(s,Inf);
		return Res;
	}
}
signed main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m,Dinic::s=1,Dinic::t=n;
	for(int i=1,x,y,z,c;i<=m;++i)cin>>x>>y>>z>>c,Dinic::qxx(x,y,z,c);
	cout<<Dinic::Solve()<<" "<<Dinic::Cost<<endl;
	return 0;
}