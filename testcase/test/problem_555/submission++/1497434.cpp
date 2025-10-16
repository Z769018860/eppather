
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline","fast-math","unroll-loops","no-stack-protector")
#pragma GCC diagnostic error "-fwhole-program"
#pragma GCC diagnostic error "-fcse-skip-blocks"
#pragma GCC diagnostic error "-funsafe-loop-optimizations"
#include <bits/stdc++.h>
#define INF 1000000000
#define LINF 1000000000000000000
#define MOD 1000000007
#define mod 998244353
#define F first
#define S second
#define ll long long
#define N 12010
using namespace std;
ll fact[N],inv[N],inv_fac[N];
ll ksm(ll x,ll y)
{
	ll ret=1;
	while(y>0)
	{
		if(y&1)
		{
			ret=(ret*x)%mod;
		}
		x=(x*x)%mod;
		y>>=1;
	}
	return ret;
}
struct Ntt{
	ll n,m,rev[N],resnum,lim,mxbit;
	void NTT(ll* a,ll flag)
	{
		ll i,j,k,l;
		for(i=0;i<lim;i++)
		{
			if(rev[i]<i)
			{
				swap(a[i],a[rev[i]]);
			}
		}
		for(l=2;l<=lim;l<<=1)
		{
			i=l>>1;
			ll gn=ksm(3,(mod-1)/l);
			for(j=0;j<lim;j+=l)
			{
				ll g=1;
				for(k=0;k<i;++k)
				{
					ll x=(a[i+j+k]*g)%mod;
					a[i+j+k]=(a[j+k]+mod-x)%mod;
					a[j+k]=(a[j+k]+x)%mod;
					g=(g*gn)%mod;
				}
			}
		}
		if(flag==-1)
		{
			reverse(a+1,a+lim);
			ll inv=ksm(lim,mod-2);
			for(i=0;i<lim;i++)
			{
				a[i]=(a[i]*inv)%mod;
			}
		}
		return;
	}
	ll a1[N],a2[N];
	vector<ll> do_ntt(vector<ll> v1,vector<ll> v2)
	{
		ll i;
		vector<ll> ret;
		n=v1.size(),m=v2.size();
		resnum=n+m-1;
		for(lim=1,mxbit=0;lim<n+m;lim<<=1,mxbit++);
		--mxbit;
		for(i=0;i<lim;++i)
		{
			a1[i]=a2[i]=0;
		}
		for(i=0;i<n;++i)
		{
			a1[i]=v1[i];
		}
		for(i=0;i<m;++i)
		{
			a2[i]=v2[i];
		}
		rev[0]=0;
		for(i=1;i<lim;++i)
		{
			rev[i]=(rev[i>>1]>>1)|((i&1)<<mxbit);
		}
		NTT(a1,1);
		NTT(a2,1);
		for(i=0;i<lim;++i)
		{
			a1[i]=(a1[i]*a2[i])%mod;
		}
		NTT(a1,-1);
		for(i=0;i<resnum;++i)
		{
			ret.push_back(a1[i]);
		}
		return ret;
	}
}ntt;
ll C(ll x,ll y){return (x<y||x<0||y<0)?0:(fact[x]*((inv_fac[y]*inv_fac[x-y])%mod))%mod;}
ll a,b,n,m,d,k,pwa[N],pwb[N],dp[N];
pair<ll,ll> plc[N];
vector<ll> pwf[62],sumf[62];
vector<ll> padd(vector<ll> x,vector<ll> y)
{
	ll i;
	if(x.size()<y.size())
	{
		swap(x,y);
	}
	for(i=0;i<y.size();i++)
	{
		x[i]=(x[i]+y[i])%mod;
	}
	return x;
}
vector<ll> getmod(vector<ll> v)
{
	ll i;
	vector<ll> ret(d,0);
	for(i=0;i<v.size();i++)
	{
		ret[i%d]=(ret[i%d]+v[i])%mod;
	}
	return ret;
}
ll calc(ll x,ll y)
{
	ll ret=(ksm(a,y)*ksm(b,x))%mod,i;
	for(i=1;i<=x;i++)
	{
		ret=(ret*((y+i)%mod))%mod;
	}
	ret=(ret*inv_fac[x])%mod;
	return ret;
}
ll solve(ll pre,ll req,ll tot)
{
	ll i;
	if(tot<pre)
	{
		return 0;
	}
	tot=(tot-pre)/d+1;
	vector<ll> a,b={0};
	for(i=0;i<=pre;i++)
	{
		a.push_back((C(pre,i)*((pwa[i]*pwb[pre-i])%mod))%mod);
	}
	a=getmod(a);
	for(i=0;i<=60;i++)
	{
		if((tot>>i)&1)
		{
			b=ntt.do_ntt(b,pwf[i]);
			b=getmod(b);
			b=padd(b,sumf[i]);
		}
	}
	a=ntt.do_ntt(a,b);
	a=getmod(a);
	return a[req];
}
int main(){
	ll i,j;
	cin>>a>>b>>n>>d>>m>>k;
	pwa[0]=pwb[0]=fact[0]=inv_fac[0]=inv[1]=inv_fac[1]=fact[1]=1;
	pwa[1]=a,pwb[1]=b;
	for(i=2;i<N;i++)
	{
		pwa[i]=(pwa[i-1]*a)%mod;
		pwb[i]=(pwb[i-1]*b)%mod;
		fact[i]=(fact[i-1]*i)%mod;
		inv[i]=(inv[mod%i]*(mod-mod/i))%mod;
		inv_fac[i]=(inv_fac[i-1]*inv[i])%mod;
	}
	for(i=0;i<k;i++)
	{
		cin>>plc[i].F>>plc[i].S;
	}
	sumf[0]={1};
	for(i=0;i<=d;i++)
	{
		pwf[0].push_back((C(d,i)*((pwa[i]*pwb[d-i])%mod))%mod);
	}
	pwf[0]=getmod(pwf[0]);
	for(i=1;i<=60;i++)
	{
		pwf[i]=ntt.do_ntt(pwf[i-1],pwf[i-1]);
		sumf[i]=padd(ntt.do_ntt(sumf[i-1],pwf[i-1]),sumf[i-1]);
		pwf[i]=getmod(pwf[i]);
		sumf[i]=getmod(sumf[i]);
	}
	sort(plc,plc+k);
	ll ans=solve(0,0,n);
	for(i=0;i<k;i++)
	{
		dp[i]=(mod-calc(plc[i].F,plc[i].S))%mod;
		for(j=0;j<i;j++)
		{
			if(plc[i].F>=plc[j].F&&plc[i].S>=plc[j].S)
			{
				dp[i]=(dp[i]+mod-((dp[j]*calc(plc[i].F-plc[j].F,plc[i].S-plc[j].S))%mod))%mod;
			}
		}
		if(plc[i].F+plc[i].S<=n)
		{
			ans=(ans+dp[i]*solve((d-(plc[i].F%d)+d-(plc[i].S%d))%d,(d-(plc[i].S%d))%d,n-plc[i].F-plc[i].S))%mod;
		}
	}
	cout<<ans<<endl;
	return 0;
}