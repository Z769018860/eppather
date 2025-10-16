#include<bits/stdc++.h>
#define pb push_back
#define fi first
#define se second
#define inf 0x3f3f3f3f3f3f3f3f
using namespace std;
vector<pair<long long,int>>f,g;
int n,m,Q;
int work(int x,int y){
	int t=31-__builtin_clz(x&y);
	if(t==-1)return x|y;
	return x|y|((1<<(t+1))-1);
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	f.pb({0,0});
	for(int i=1;i<=n;i++){
		int x,y;cin>>x>>y;
		g.clear();
		for(auto e:f){
			g.pb(e);
			g.pb({e.fi+x,work(e.se,y)});
		}
		sort(g.begin(),g.end());
		f.clear(),f.pb({0,0});
		for(auto e:g){
			if(e.se>f.back().se)f.pb(e);
		}
	}
	cin>>Q;
	while(Q--){
		long long res=inf;
		int x;
		cin>>x;
		for(auto e:f) if(e.se>=x)res=min(res,e.fi);
		cout<<(res==inf?-1:res)<<"\n";
	}
}