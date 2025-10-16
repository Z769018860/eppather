#include<bits/stdc++.h>
#define ci const int
#define ll long long
using namespace std;
ci mod=998244353,C=19190506,d=917504,N=(int)(1e12/d)+100;
ll qk(ll x,int y=mod-2){
	ll ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		x=x*x%mod,y>>=1;
	}
	return ans;
}
ci q=qk(C);
int fac[N],dfac[N],inv[N];
int Fac[d],Dfac[d];
ll Cc(ci n,ci m){
	if(n<m||m<0)return 0;
	return (ll)fac[n]*dfac[m]%mod*dfac[n-m]%mod;
}
ll Cq(ci n,ci m){
	if(n<m||m<0)return 0;
	return (ll)Fac[n]*Dfac[m]%mod*Dfac[n-m]%mod;
}
ll Lucas(ll n,ll m){
	if(n<d&&m<d)return Cq(n,m);
	return Cc(n/d,m/d)*Lucas(n%d,m%d)%mod;
}
int sum(ll l,ll r){
	return (__int128)(l+r)*(r-l+1)/2%(mod-1);
}
int main(){
	fac[0]=fac[1]=dfac[0]=dfac[1]=inv[1]=1;
	for(int i=2;i<N;++i)
		fac[i]=(ll)fac[i-1]*i%mod,
		inv[i]=(ll)(mod-mod/i)*inv[mod%i]%mod,
		dfac[i]=(ll)dfac[i-1]*inv[i]%mod;
	Fac[0]=1;
	for(int i=1;i<d;++i)Fac[i]=(qk(q,i)-1)*qk(q-1)%mod;
	for(int i=1;i<d;++i)Fac[i]=(ll)Fac[i-1]*Fac[i]%mod;
	for(int i=0;i<d;++i)Dfac[i]=qk(Fac[i]);
	int T;scanf("%d",&T);
	while(T--){
		ll n,m;scanf("%lld%lld",&n,&m);
		__int128 pw=(__int128)m*(m+1)/2%(mod-1);
		pw=(sum(n-m+1,n)-pw+mod-1)%(mod-1);
		printf("%lld\n",qk(C,(ll)pw)*Lucas(n,m)%mod);
	}
	return 0;
}