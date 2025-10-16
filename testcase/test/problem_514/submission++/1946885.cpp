

#include<bits/stdc++.h>
using namespace std;
int const N=1e4+10;
int n,m,a[N],b[N],ans[N];
void solve(){
	cin>>n>>m;
	for (int i=1;i<=n;++i) cin>>a[i],b[i]=b[i-1]+a[i];
	memset(ans,-0x3f,sizeof(ans));
	for (int l=1;l<=n;++l)
		for (int i=l;i<=n;++i)
			ans[l]=max(ans[l],b[i]-b[i-l]);
	for (int i=n;i>=1;--i) ans[i]=max(ans[i],ans[i+1]);
	while (m--){
		int x;cin>>x;
		cout<<ans[x]<<'\n';
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