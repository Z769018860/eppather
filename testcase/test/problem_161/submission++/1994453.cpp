#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=5e6+5;
ll n,a[N],sum[N],sv[N],ppow[N],ans,p,k;
inline int read() {
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9')
		x=x*10+ch-'0',ch=getchar();
	return x*f;
}
void exgcd(ll a,ll b,ll &x,ll &y) {
	if(b==0) {
		x=1,y=0;
		return ;
	}
	exgcd(b,a%b,y,x);
	y-=(a/b)*x;
}
int main() {
	n=read();p=1e9+7;
	ppow[0]=sum[0]=1;
	for(int i=1; i<=n; i++) {
		a[i]=read();
		sum[i]=sum[i-1]*a[i]%p;
		ppow[i]=ppow[i-1]*998244353%p;
	}
	ll x,y;
	exgcd(sum[n],p,x,y);
	sv[n+1]=(p+x%p)%p;	
	for(int i=n;i>=1;i--) {
		sv[i]=sv[i+1]*a[i]%p;
		ans=(ans+sv[i+1]*sum[i-1]%p*ppow[n-i]%p)%p;		
	}
	printf("%d",ans);
	return 0;
}