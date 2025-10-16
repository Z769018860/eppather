#include <cstdio>
#include <ctime>
#include <cctype>
#include <vector>
#define N 1000010
#define ll long long
using std::vector;
ll M;
std::vector<ll> f[N];
int top; ll P[N],K[N],PK[N],g[N];
ll mpow(ll x,ll y,ll p)
{
	ll ans=1;
	for(;y;y>>=1,x=x*x%p) if(y&1) ans=ans*x%p;
	return ans;
}
ll mp(ll x,ll y,ll p)
{
	if(x==1) return 1;
	else return y&1?x:1;
}
ll fact(ll n,ll p,ll k,ll pk,int i)
{
	if(!n) return 1;
	return mp(f[i][pk],n/pk,pk)*fact(n/p,p,k,pk,i)%pk*f[i][n%pk]%pk;
}
ll exgcd(ll x,ll y,ll &a,ll &b)
{
	if(!y) {a=1, b=0; return x;}
	ll rtn=exgcd(y,x%y,b,a);
	b-=(x/y)*a;
	return rtn;
}
ll inv(ll x,ll p)
{
	ll a,b; x%=p;
	if(exgcd(x,p,a,b)!=1) return -1;
	return (a+p)%p;
}
void init(ll p)
{
	M=p;
	for(ll i=2;i*i<=p;i++) if(!(p%i))
	{
		PK[top]=1, P[top]=i;
		while(!(p%i)) p/=i,K[top]++,PK[top]*=i;
		top++;
	}
	if(p>1) PK[top]=P[top]=p, K[top]=1, top++;
	
	for(int i=0;i<top;i++)
	{
		f[i].push_back(1);
		for(int j=1;j<=PK[i];j++)
			f[i].push_back((j%P[i]?j:1)*f[i].back()%PK[i]);
	}

	for(int i=0;i<top;i++) g[i]=(M/PK[i])*inv(M/PK[i],PK[i])%M;
}
ll exponent(ll n,ll p) {return n?exponent(n/p,p)+n/p:0;}
ll calc(ll n,ll m)
{
	ll ans=0;
	for(int i=0;i<top;i++)
	{
		ll e=exponent(n,P[i])-exponent(m,P[i])-exponent(n-m,P[i]);
		if(e<K[i])
		{
			ll num=fact(n,P[i],K[i],PK[i],i)*inv(fact(m,P[i],K[i],PK[i],i)*fact(n-m,P[i],K[i],PK[i],i),PK[i])%PK[i];
			num=num*mpow(P[i],e,PK[i])%PK[i];
			ans=(ans+num*g[i])%M;
		}
	}
	return ans;
}
ll read()
{
	ll x=0; char ch;
	for(ch=getchar();!isdigit(ch);ch=getchar())
		continue;
	for(;isdigit(ch);ch=getchar()) x=x*10+ch-'0';
	return x;
}
void write(ll x)
{
	if(x>=10) write(x/10);
	putchar(x%10+'0');
}
int main()
{
	#ifdef xkcdjerry
	freopen("544195584.in","r",stdin);
	freopen(".out","w",stdout);
	#endif
	int T=read(); init(read());
	#ifdef xkcdjerry
	fprintf(stderr,"%.2lf\n",clock()/(double)CLOCKS_PER_SEC);
	#endif
	while(T--)
	{
		ll n=read(),m=read();
		write(calc(n,m));
		putchar('\n');
	}
}