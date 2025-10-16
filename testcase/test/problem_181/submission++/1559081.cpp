
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=30;
ll t,n,m,md,cnt,p[N],c[N],q[N];
vector <int> qzj[N];
ll qpow (ll a,ll b,ll p) {ll res=1;while (b) {if (b&1) res=(res*a)%p;a=(a*a)%p,b>>=1;}return res;}
void exgcd (ll a,ll b,ll &x,ll &y) {
	if (b==0) {x=1,y=0;return;}
	exgcd(b,a%b,x,y);ll t=x;x=y;y=t-(a/b)*y;
}
ll g (ll n,ll p) {ll res=0;while (n) {res+=n/p;n/=p;}return res;}
ll f (ll n,ll k) {
	if (!n) {return 1;}
	ll cir=qzj[k][q[k]],res=qzj[k][n%q[k]];
	return f(n/p[k],k)*res%q[k]*qpow(cir,n/q[k],q[k])%q[k];
}
ll calc (ll n,ll m,ll k) {
	ll pw=g(n,p[k])-g(m,p[k])-g(n-m,p[k]);if (pw>=c[k]) return 0;
	ll res=1;for (int i=1;i<=pw;i++) {res*=p[k];}
	ll x=0,y=0,a=f(n,k),b=f(m,k),c=f(n-m,k);
	exgcd(b,q[k],x,y);b=(x%q[k]+q[k])%q[k];
	exgcd(c,q[k],x,y);c=(x%q[k]+q[k])%q[k];return res*a%q[k]*b%q[k]*c%q[k];
}
int main () {
	scanf("%lld%lld",&t,&md);
	for (int i=2;i<=md;i++) if (md%i==0) {p[++cnt]=i;q[cnt]=1;while (md%i==0) md/=i,q[cnt]*=i,c[cnt]++;}
	for (int i=1;i<=cnt;i++) {
		qzj[i].push_back(1);ll nw=1;
		for (int j=1;j<=q[i];j++) {if (j%p[i]) nw=(nw*j)%q[i];qzj[i].push_back(nw);}
	}
	for (int ii=1;ii<=t;ii++) {
		scanf("%lld%lld",&n,&m);
		ll nw=1,ans=0;for (int i=1;i<=cnt;i++) {
			ll r=calc(n,m,i),a=0,b=0;exgcd(nw,q[i],a,b);
			ans+=nw*(a%q[i])%(nw*q[i])*(r-ans)%(nw*q[i]);nw*=q[i];ans%=nw;
		}
		printf("%lld\n",(ans+nw)%nw);
	}
	return 0;
}