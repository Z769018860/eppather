#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 L;
mt19937_64 rnd(time(0));
ll ksm(ll x,ll k,ll mod){
	ll res=1;
	for(;k;k>>=1,x=(L)x*x%mod)
		if(k&1) res=(L)res*x%mod;
	return res;
}
bool MR(ll n){
	if(n<3) return n==2;
	ll u=n-1; int t=0;
	while(u&1^1) u>>=1,++t;
	for(int i=0;i<10;++i){
		ll b=rnd()%(n-2)+2;
		ll v=ksm(b,u,n); int s=0;
		if(v==1) continue;
		for(;s<t;++s){
			if(v==n-1) break;
			v=(L)v*v%n;
		}
		if(s==t) return 0;
	}
	return 1;
}
int main(){
	ll x;
	while(scanf("%lld",&x)!=EOF)
		puts(MR(x)?"Y":"N");
	return 0;
}
