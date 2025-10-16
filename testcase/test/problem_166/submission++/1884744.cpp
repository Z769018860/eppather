#pragma GCC optimize(2)
#include<cstdio>
#include<vector>
#include<algorithm>
#define ll long long
#define maxn 200005
using namespace std;
typedef vector<ll> poly;
const int M=200000;
const ll mod=998244353,inv2=499122177,g=3;
int n,m;
ll f[maxn],frac[maxn],r[maxn];
poly a,b;
void ready()
{
	frac[0]=1;
	for(int i=1;i<=M;++i)
	frac[i]=frac[i-1]*i%mod;
}
void presize(int n,int &l,int &m)
{
	l=0;m=1;
	while(m<n)
	{
		m<<=1;
		l++;
	}
	for(int i=0;i<m;++i)
	r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
}
ll mul(ll x,ll y)
{
	ll ret=1;
	while(y)
	{
		if(y&1)
		ret=(ret*x)%mod;
		x=(x*x)%mod;
		y>>=1;
	}
	return ret;
}
ll getinv(ll x)
{
	return mul(x,mod-2);
}
void ntt(poly &c,int lim,int flag)
{
	c.resize(lim);
	for(int i=0;i<lim;++i)
	{
		if(i<r[i])
		swap(c[i],c[r[i]]);
	}
	for(int mid=1;mid<lim;mid<<=1)
	{
		ll wn=mul(g,(mod-1)/(mid<<1));
		for(int r=mid<<1,j=0;j<lim;j+=r)
		{
			ll w=1;
			for(int k=0;k<mid;++k,w=(w*wn)%mod)
			{
				ll x=c[j+k],y=w*c[j+mid+k]%mod;
				c[j+k]=(x+y)%mod;
				c[j+mid+k]=((x-y)%mod+mod)%mod;
			}
		}
	}
	if(flag==1)return;
	ll inv=mul(lim,mod-2);
	reverse(c.begin()+1,c.end());
	for(int i=0;i<lim;++i)
	c[i]=(c[i]*inv)%mod;
}
void Mul(int n,poly &a,poly &b)
{
	int l,m;
	presize(n,l,m);
	ntt(a,m,1);
	ntt(b,m,1);
	for(int i=0;i<m;++i)
	a[i]=a[i]*b[i]%mod;
	ntt(a,m,-1);
}
void Lagrange(int n,int m)
{
	for(int i=0;i<=n;++i)
	{
		ll ret=frac[i]*frac[n-i]%mod;
		if((n-i)&1)
		ret=mod-ret;
		ll val=f[i]*getinv(ret)%mod;
		a.push_back(val);
	}
	for(int i=n+1;i<=(n<<1);++i)
	a.push_back(0);
	for(int i=0;i<=(n<<1);++i)
	{
		ll val=getinv(m-n+i);
		b.push_back(val);
	}
	Mul((n<<1)+10,a,b);
	ll val=1;
	for(int i=0;i<=n;++i)
	val=val*(m-i)%mod;
	for(int i=n;i<=(n<<1);++i)
	{
		a[i]=a[i]*val%mod;
		printf("%lld ",a[i]);
		ll del=m-2*n+i,ret=m+i+1-n;
		val=val*getinv(del)%mod*ret%mod;
	}
}
int main()
{
	ready();
	scanf("%d%d",&n,&m);
	for(int i=0;i<=n;++i)
	scanf("%lld",&f[i]);
	Lagrange(n,m);
	return 0;
}