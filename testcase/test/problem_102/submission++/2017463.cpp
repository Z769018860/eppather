#include<bits/stdc++.h>
using namespace std;

#define rep(i,j,k) for(int i=(j);i<=(k);i++)
#define per(i,j,k) for(int i=(j);i>=(k);i--)
#define pb push_back
#define mp make_pair
#define fi first
#define se second
typedef vector<int> vi;
typedef pair<int,int> pi;

const int N=5005,M=50005,inf=INT_MAX;
struct flow{
	int n,m,S,T;
	int cur[N],dis[N]; bool vis[N];
	vector< array<int,4> > G[N];
	void link(int u,int v,int w,int c){
		int d0=G[u].size(),d1=G[v].size();
		G[u].pb({v,w,c,d1});
		G[v].pb({u,0,-c,d0});
	}
	bool spfa(){
		fill(dis+1,dis+n+1,inf);
		dis[S]=0,vis[S]=1;
		queue<int> Q;
		Q.push(S);
		while(!Q.empty()){
			int u=Q.front(); Q.pop();
			vis[u]=0;
			for(auto &ed:G[u]){
				int v=ed[0],w=ed[1],c=ed[2];
				if(w && dis[u]+c<dis[v]){
					dis[v]=dis[u]+c;
					if(!vis[v]){
						Q.push(v);
						vis[v]=1;
					}
				}
			}
		}
		return dis[T]<inf;
	}
	int dfs(int u,int rst){
		if(u==T){
			return rst;
		}
		vis[u]=1;
		int pre=rst;
		for(;cur[u]<(int)G[u].size(); cur[u]++){
			auto &ed=G[u][cur[u]];
			int v=ed[0],w=ed[1],c=ed[2],r=ed[3];
			if(dis[u]+c==dis[v] && w && !vis[v]){
				int f=dfs(v,min(rst,w));
				ed[1]-=f,G[v][r][1]+=f,rst-=f;
				if(!rst){
					break;
				}
			}
		}
		vis[u]=0;
		return pre-rst;
	}
	pi Dinic(){
		int flow=0,cost=0;
		while(spfa()){
			rep(i,1,n){
				cur[i]=0;
			}
			int f=dfs(S,inf);
			flow+=f,cost+=f*dis[T];
		}
		return mp(flow,cost);
	}
}F;
signed main(){
  	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  	
  	cin>>F.n>>F.m;
	F.S=1,F.T=F.n;
  	rep(i,1,F.m){
  		int u,v,w,c; cin>>u>>v>>w>>c;
  		F.link(u,v,w,c);
  	}
  	pi ans=F.Dinic();
  	cout<<ans.fi<<' '<<ans.se<<'\n';
  	
	return 0;
}