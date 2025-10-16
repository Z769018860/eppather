#include<bits/stdc++.h>
#define ll long long
using namespace std;
#define Tp template<typename T>
#define Ts template<typename T,typename... _T>
char buf[1<<20],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=buf+fread(p1=buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
Tp inline void read(T& x){
    x=0;char c=getchar();bool f=0;
    for(;c<48||c>57;c=getchar())c=='-'&&(f=1);
    for(;c>47&&c<58;c=getchar())x=(x<<1)+(x<<3)+(c^48);
    f&&(x=-x);
}
Ts inline void read(T& x,_T&... y){read(x),read(y...);}
const ll N=5e6+5,P=1e9+7;
const ll p=998244353;
ll a[N],inv[N],sv[N];
ll qpow(ll a,ll b){
	ll ans=1;
	for(;b;b>>=1){
		if(b&1)ans=ans*a%P;
		a=a*a%P;
	}
	return ans;
}
int main(){
	ll n;read(n);sv[0]=1;
	for(ll i=1;i<=n;i++){
		read(a[i]);
		sv[i]=sv[i-1]*a[i]%P;
	}
	inv[n]=qpow(sv[n],P-2);
	for(ll i=n-1;i>=1;i--){
		inv[i]=inv[i+1]*a[i+1]%P;
	}
	ll ans=0,res=1;
	for(ll i=n;i>=1;i--){
		ll x=inv[i]*sv[i-1]%P;
		ans=(ans+x*res%P)%P;
		res=res*p%P;
	}
	printf("%lld",ans);
	return 0;
}