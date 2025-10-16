#include<bits/stdc++.h>
using i64=long long;
using std::cin;
using std::cout;
constexpr int maxk=10,maxn=105,maxm=505,inf=0x3f3f3f3f;
int dp[1<<maxk][maxn];
struct Edge{
	int nxt,to,w;
}G[maxm<<1];
int h[maxn],et;
void adde(int u,int v,int w){
	G[++et]={h[u],v,w},h[u]=et;
}
void solve(){
	int n,m,k;
	cin>>n>>m>>k;
	for(int i=0,u,v,w;i<m;++i){
		cin>>u>>v>>w,adde(u,v,w),adde(v,u,w);
	}
	memset(dp,inf,sizeof(dp));
	for(int i=0,x;i<k;++i){
		cin>>x,dp[1<<i][x]=0;
	}
	int S=1<<k,ans=inf;
	{
		using pack=std::pair<int,int>;
		std::priority_queue<pack,std::vector<pack>,std::greater<pack> > pq;
		for(int s=0;s<S;++s){
			for(int t=s&(s-1);t>(s^t);--t&=s){
				for(int u=1;u<=n;++u){
					dp[s][u]=std::min(dp[s][u],dp[t][u]+dp[s^t][u]);		
				}
			}
			for(int u=1;u<=n;++u){
				pq.emplace(dp[s][u],u);
			}
			while(!pq.empty()){
				auto [w,u]=pq.top();
				pq.pop();
				if(w==dp[s][u]){
					for(int i=h[u];i;i=G[i].nxt){
						int to=G[i].to;
						if(dp[s][to]>w+G[i].w){
							pq.emplace(dp[s][to]=w+G[i].w,to);
						}
					}
				}
			}
		}
	}
	for(int u=1;u<=n;++u){
		ans=std::min(ans,dp[S-1][u]);
	}
	cout<<ans;
}
int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	solve();
	return 0;
}