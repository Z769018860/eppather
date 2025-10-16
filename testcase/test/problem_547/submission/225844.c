#include<stdio.h>
#include<string.h>
typedef long long  ll;
#define  mod 65537
ll m,n;
ll f[6005],g[6005],tp[6005];
void mul(ll *a,ll *b)
{
	for(int i=0;i<=2*m;i++) tp[i]=0;
	for(int i=0;i<m;i++)
    for(int j=0;j<m;j++)
	 tp[i+j]=(tp[i+j]+a[i]*b[j])%mod;
	for(int i=2*m-2;i>=m;i--)
	{
		for(int j=0;j<m;j++)
			tp[i-m+j]=(tp[i-m+j]+tp[i])%mod;
		tp[i]=0;
	}
	for(int i=0;i<m;i++) a[i]=tp[i];
}
void ksm1()
{
	while(n)
	{
		if(n&1)mul(g,f);
		mul(f,f);
		n>>=1;
	}
}
void f1()
{
	f[1]=1; g[0]=1;
	ksm1();
	ll s=1,ans=0;
	for(int i=0;i<m;i++) ans=(ans+s*g[i])%mod,s=s*2%mod;
	printf("%lld\n",(ans%mod+mod)%mod);
}
ll fac[65538],inv[65538];

ll C(ll n,ll m)
{
	if(m>n) return 0;
	if(n>=mod) return C(n/mod,m/mod)*C(n%mod,m%mod)%mod;
	else return fac[n]*inv[m]*inv[n-m]%mod;
}
ll ksm2(ll x,ll k)
{
	ll s=1;
	while(k)
	{
		if(k&1) s=s*x%mod;
		x=x*x%mod;
		k>>=1;
	}
	return s;
}
ll calc(ll n1)
{
	ll ans=0,pw2=ksm2(2,n1),iv=ksm2(ksm2(2,m+1),mod-2);
	int lim=n1/(m+1);
	for(int i=0;i<=lim;++i)
	{
		if(i&1) ans-=pw2*C(n1-i*m,i);
		else ans+=pw2*C(n1-i*m,i);
		pw2=pw2*iv%mod;
	}
	return (ans%mod+mod)%mod;
}
void f2()
{
	fac[0]=inv[0]=1;
	for(int i=1;i<mod;i++) fac[i]=fac[i-1]*i%mod;
	inv[mod-1]=ksm2(fac[mod-1],mod-2);
	for(int i=mod-2;i>=1;i--) inv[i]=inv[i+1]*(i+1)%mod;
	printf("%lld\n",(calc(n+1)-calc(n)+mod)%mod);
}
int main()
{
	scanf("%lld%lld",&n,&m);
	if(m==1) {printf("1\n");return 0;}
	if(m<=3000) f1();
	else f2();
	return 0;
}