

#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=3e5+10;
int const mod=998244353;
int n,rd[N],ans[N],dp[N];
unordered_map<int,int>mp[N];
struct node{int x,r,v,id;}a[N];
vector<int>b[N];
inline void dfs(int x,int sm,int la){
	if (dp[x]-mod>=sm || (mp[x].count(la) && mp[x][la]>=sm)) return;
	dp[x]=max(dp[x],sm),mp[x][la]=sm;for (auto v:b[x])
		dfs(v,sm+((a[v].v^a[la].v)+a[v].v*a[la].v)%mod,v),dfs(v,sm,la);
}
void solve(){
	cin>>n;
	for (int i=1;i<=n;++i) cin>>a[i].x;
	for (int i=1;i<=n;++i) cin>>a[i].r;
	for (int i=1;i<=n;++i) cin>>a[i].v,a[i].id=i;
	sort(a+1,a+n+1,[&](node &a,node &b){return a.x<b.x;});
	stack<int>s;
	for (int i=1;i<=n;++i){
		while (s.size() && a[s.top()].x+a[s.top()].r<a[i].x) s.pop();
		if (s.size()) b[s.top()].push_back(i),++rd[i];
		while (s.size() && a[s.top()].x+a[s.top()].r<=a[i].x+a[i].r) s.pop();
		s.push(i);
	}
	while (s.size()) s.pop();
	for (int i=n;i>=1;--i){
		while (s.size() && a[s.top()].x-a[s.top()].r>a[i].x) s.pop();
		if (s.size()) b[s.top()].push_back(i),++rd[i];
		while (s.size() && a[s.top()].x-a[s.top()].r>=a[i].x-a[i].r) s.pop();
		s.push(i);
	}
	for (int i=1;i<=n;++i)
		if (!rd[i]) dfs(i,0,i);
	for (int i=1;i<=n;++i) ans[a[i].id]=dp[i];
	for (int i=1;i<=n;++i) cout<<ans[i]<<'\n';
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int t=1;
	
	while (t--) solve();
	cerr<<"Running Time: "<<(double)clock()/CLOCKS_PER_SEC<<" s\n";
	return 0;
}