#include<bits/stdc++.h>
using namespace std;

constexpr unsigned maxn=1<<18,mod=998244353;
typedef unsigned long long ull;

namespace poly
{
constexpr unsigned G=3;
unsigned r[maxn],w[maxn];
ull qpow(ull p,unsigned q)
{
	ull r=1;
	while(q)
	{
		if(q&1) r=r*p%mod;
		p=p*p%mod;
		q/=2;
	}
	return r;
}
void ntt(vector<unsigned>&a,unsigned n,int tp)
{
	unsigned i,j,k,len=1<<n;
	a.resize(len);
	for(i=1;i<len;i++)
	{
		r[i]=r[i>>1]>>1|(i&1)<<(n-1);
		if(r[i]>i) swap(a[i],a[r[i]]);
	}
	for(i=1;i<len;i*=2)
	{
		ull pw=qpow(tp?(mod+1)/G:G,(mod-1)/i/2);
		w[0]=1;
		for(j=1;j<i;j++) w[j]=w[j-1]*pw%mod;
		for(j=0;j<len;j+=i*2)
		{
			for(k=0;k<i;k++)
			{
				unsigned &x=a[j+k],&y=a[j+k+i],b=1ull*w[k]*y%mod;
				y=x-b;
				if(y>>31) y+=mod;
				x+=b;
				if(x>=mod) x-=mod;
			}
		}
	}
	if(tp)
	{
		ull inv=qpow(len,mod-2);
		for(auto&it:a) it=it*inv%mod;
	}
}
vector<unsigned> mul(vector<unsigned>a,vector<unsigned>b)
{
	unsigned len=a.size()+b.size()-2,n=len?__lg(len)+1:0,i;
	ntt(a,n,0);
	ntt(b,n,0);
	for(i=0;i<a.size();i++) a[i]=1ull*a[i]*b[i]%mod;
	ntt(a,n,1);
	a.resize(len+1);
	return a;
}
}

char s[maxn];
unsigned dp[maxn],f[maxn],fi[maxn],cnt[maxn];

void dfs(int l,int r)
{
	if(l==r) return;
	int mid=(l+r)/2,i;
	static vector<unsigned>a,b;
	dfs(l,mid);
	a.resize(mid-l+1);
	for(i=l;i<=mid;i++) a[i-l]=s[i]!='<'?(cnt[i]?mod-dp[i]:dp[i]):0;
	b.resize(r-l);
	for(i=1;i<=r-l;i++) b[i-1]=fi[i];
	a=poly::mul(a,b);
	for(i=mid+1;i<=r;i++)
	{
		if(cnt[i-1])
		{
			dp[i]-=a[i-l-1];
			if(dp[i]>>31) dp[i]+=mod;
		}
		else
		{
			dp[i]+=a[i-l-1];
			if(dp[i]>=mod) dp[i]-=mod;
		}
	}
	dfs(mid+1,r);
}

int main()
{
	int i,n;
	scanf("%s",s+1);
	n=strlen(s+1)+1;
	f[0]=1;
	for(i=1;i<=n;i++)
	{
		cnt[i]=cnt[i-1]^(s[i]=='>');
		f[i]=1ull*f[i-1]*i%mod;
	}
	fi[n]=poly::qpow(f[n],mod-2);
	for(i=n;i>=1;i--) fi[i-1]=1ull*i*fi[i]%mod;
	dp[0]=1;
	dfs(0,n);
	printf("%llu\n",1ull*dp[n]*f[n]%mod);
	return 0;
}
