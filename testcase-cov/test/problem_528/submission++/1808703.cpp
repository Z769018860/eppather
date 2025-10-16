#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const ll maxn=4e6+5;
const ll mod=998244353;
ll P;
ll pri[maxn],mu[maxn],p[maxn],cnt;
void init(){
	mu[1]=1;
	for(ll i=2;i<=P;++i){
		if(!p[i]) pri[++cnt]=i,mu[i]=-1;
		for(ll j=1;j<=cnt&&pri[j]*i<=P;++j){
			p[pri[j]*i]=1;
			if(i%pri[j]==0){
				mu[pri[j]*i]=0;
				break;
			}
			else mu[pri[j]*i]=-mu[i];
		}
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	ll n,m;cin>>n>>m;
	if(n<m) swap(n,m);P=sqrt(n+0.5);init();
	ll ans=0;
	for(ll i=1;1ll*i*i<=n;++i){
		if(!mu[i]) continue;
		ll x=i*i;
		ans=(ll)(ans+mu[i]*(1ll*(n/x)%mod*((m/x)%mod))%mod+mod)%mod;
	}
	cout<<ans<<'\n';
	return 0;
}