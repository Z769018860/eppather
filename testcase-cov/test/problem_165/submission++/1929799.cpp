#include<bits/stdc++.h>
#define maxn 3010
#define mod 998244353
#define ll long long int
using namespace std;
ll power(ll a,ll b,ll c){
	ll p=1;
	while(b){
		if(b&1) p=p*a%c;
		a=a*a%c, b>>=1ll;
	}
	return p;
}
int n=0;
ll w[maxn];
struct U{ll x,y;}A[maxn];
void insert(){
	w[++n]=1;
	scanf("%lld%lld",&A[n].x,&A[n].y);
	ll inv=0;
	for(int i=1;i<n;i++){
		inv=power(A[i].x-A[n].x,mod-2,mod);
		w[i]=w[i]*inv%mod;
		inv=power(A[n].x-A[i].x,mod-2,mod);
		w[n]=w[n]*inv%mod;
	}
	w[n]=w[n]*A[n].y%mod;
	return;
}
ll f(ll x){
	if(n==1) return A[n].y;
	ll s=0,M=1;
	for(int i=1;i<=n;i++){
		if(A[i].x==x) return A[i].y;
		M=M*(x-A[i].x)%mod;
	}
	for(int i=1;i<=n;i++){
		s=(s+M*w[i]%mod*power(x-A[i].x,mod-2,mod))%mod;
	}
	return (s%mod+mod)%mod;
}
int main(){
	int op,k,t;
	scanf("%d",&t);
	while(t--){
		scanf("%d",&op);
		if(op==1){
			insert();
		}
		else if(op==2){
			scanf("%d",&k);
			printf("%lld\n",f(1ll*k));
		}
	}
    return 0;
}