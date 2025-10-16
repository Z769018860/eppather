#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=1e9+7;
const int N=5000005;
ll read(){
	ll x=0,f=1;
	char c=getchar();
	while(c>'9'||c<'0'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
ll qfst(ll a,ll b){
	ll res=1,t=a;
	while(b){
		if(b&1==1){
			res=(res*t)%mod;
		}
		t=(t*t)%mod;
		b=b>>1;
	}
	return res;
}
ll x,y;
ll exgcd(ll a,ll b,ll &x,ll &y){
	if(b==0){
		x=1;
		y=0;
		return a;
	}
	int d=exgcd(b,a%b,y,x);
	y=y-(a/b)*x;
	return d; 
}
ll premult[N];
ll a[N];
ll qs[N];
ll ans[N]; 
ll f[N];
int main(){
	
	int n;
	cin>>n;
	premult[0]=1;
	f[0]=1;
	f[1]=998244353;
	for(int i=2;i<=n;i++){
		f[i]=(f[i-1]*998244353)%mod;
	}
	for(int i=1;i<=n;i++){
		a[i]=read();
		premult[i]=(premult[i-1]*a[i])%mod;
	}
	ll d=exgcd(premult[n],mod,x,y);
	
	while(x<0){
		x=(x+mod/d)%mod;
	}
	x=x%(mod/d);

	qs[n]=x; 
	for(int i=n-1;i>=1;i--){
		qs[i]=(qs[i+1]*a[i+1])%mod;

	}

	for(int i=1;i<=n;i++){
		ans[i]=(premult[i-1]*qs[i])%mod;

	}
	ll anss=0;
	for(int i=1;i<=n;i++){
		anss=(anss+(ans[i]*f[n-i])%mod)%mod; 
	}
	cout<<anss;
	
	return 0;
}