

#include<bits/stdc++.h>
using namespace std;
int const N=3e5+10;
int n,m,ans=INT_MAX,ct,la[N];
set<int>s[N];map<int,int>gp;
void solve(){
	cin>>n>>m;
	for (int i=1;i<=n;++i){
		int x;cin>>x;
		if (!gp[x]) gp[x]=++ct;
		x=gp[x];
		s[x].insert(i);
		if (la[x]) ans=min(ans,i-la[x]);
		la[x]=i;
	}
	while (m--){
		int x,y;cin>>x>>y;
		if (!gp[x]) gp[x]=++ct;
		if (!gp[y]) gp[y]=++ct;
		x=gp[x],y=gp[y];
		if (!s[x].size() || (x==y)){cout<<ans<<'\n';continue;}
		if (s[x].size()>s[y].size()) swap(s[x],s[y]);
		for (auto i:s[x]){
			auto it=s[y].lower_bound(i);
			if (it!=s[y].end()) ans=min(ans,(*it)-i);
			if (it==s[y].begin()) continue;
			--it,ans=min(ans,i-(*it));
		}
		for (auto i:s[x]) s[y].insert(i);
		s[x].clear(),cout<<ans<<'\n';
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int t=1;
	
	while (t--) solve();
	cerr<<"Running Time: "<<(double)clock()/CLOCKS_PER_SEC<<" s\n";
	return 0;
}