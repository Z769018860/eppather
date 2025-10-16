#include<bits/stdc++.h>
using namespace std;
using ll=long long;
constexpr ll mod=998244353;
ll presum(__int128 n,int t){
	if(t==0)return n%mod;
	if(t==1)return n*(n+1)/2%mod;
	if(t==2)return n*(n+1)/2*(2*n+1)/3%mod;
}
ll rangesum(int l,int r,int t){return mod+presum(r,t)-presum(l-1,t);}
int main(){
	int n;cin>>n;
	ll ans=0;
	for(int l=1,r;l<=n;l=r+1){
		r=n/(n/l);
		(ans+=n/l*(rangesum(l,r,0)*5+rangesum(l,r,1)*3+rangesum(l,r,2)*2))%=mod;
	}cout<<ans;
	return 0;
}