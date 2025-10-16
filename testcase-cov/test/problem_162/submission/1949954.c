#include<stdio.h>
#define ll long long
ll p=998244352;
ll f(ll a,ll b){
	ll r=1;
	while(b>0){
		if(b%2==1){
			r=r*a%p;
		}
		b/=2;
		a=a*a%p;
	}
	return r;
}
int main(){
	ll x,n,a;
	scanf("%lld%lld",&x,&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a);
		printf("%lld ",f(x,a));
	}
	return 0;
}
