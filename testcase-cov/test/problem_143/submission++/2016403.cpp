#include<bits/stdc++.h>
using namespace std;
#define ll long long
int pri[]={2,3,5,7,11,13,17,19,23,29,31,37};
ll Pow(ll a,ll b,ll mod){
	ll rec=1;
	for(;b;b>>=1,a=(__int128)a*a%mod)
		if(b&1)rec=(__int128)rec*a%mod;
	return rec;
}
bool chk(ll n){
	if(n<3||n%2==0)return n==2;
	ll a=n-1,b=0;
	while(a%2==0)a/=2,b++;
	for(int i=0,s;i<12;i++){
		ll w=Pow(pri[i],a,n);
		if(w<=1)continue;
		for(s=0;s<b;s++){
			if(w==n-1)break;
			w=(__int128)w*w%n;
		}if(s==b)return 0;
	}return 1;
}
int main(){for(ll n;scanf("%lld",&n)!=EOF;)puts(chk(n)?"Y":"N");}