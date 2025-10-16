#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<vector>
const long long mod=998244353;
int w[1<<21|1],p,q;
long long Pow(long long a,long long b)
{
	long long s=1;
	for(a%=mod;b;a=a*a%mod,b>>=1)
		if(b&1)
			s=s*a%mod;
	return s;
}
void init()
{
	w[0]=1;
	for(int t=0;t<20;t++)
	{
		long long f=w[1<<t]=Pow(114514,mod-1>>t+2);
		for(int x=1<<t;x<1<<t+1;x++)
			w[x]=f*w[x-(1<<t)]%mod;
	}
	return;
}
std::vector<int>a[20],b[20];
void ntt(std::vector<int>&a,int n)
{
	a.resize(1<<n);
	for(int h=1<<n-1;h;h>>=1)
		for(int j=0,i=0;j<1<<n;j+=h<<1,i++)
			for(int k=j;k<j+h;k++)
			{
				int u(a[k]),v(1ll*w[i]*a[k+h]%mod);
				a[k]=u+v>=mod?u+v-mod:u+v,a[k+h]=u-v<0?u-v+mod:u-v;
			}
	return;
}
void intt(std::vector<int>&a,int n)
{
	a.resize(1<<n);
	for(int h=1;h<1<<n;h<<=1)
		for(int j=0,i=0;j<1<<n;j+=h<<1,i++)
			for(int k=j;k<j+h;k++)
			{
				int u(a[k]),v(a[k+h]);
				a[k]=u+v>=mod?u+v-mod:u+v,a[k+h]=1ll*(u-v<0?u-v+mod:u-v)*w[i]%mod;
			}
	std::reverse(std::next(a.begin()),a.end());
	long long r(mod-(mod-1>>n));
	for(int i=0;i<1<<n;i++)
		a[i]=a[i]*r%mod;
	return;
}
void push(std::vector<int>&a)
{
	for(int i=0;i<a.size();i++)
		if(a[i]>=q)
		{
			if(i==a.size()-1)
				a.emplace_back(a[i]/q);
			else
				a[i+1]+=a[i]/q;
			a[i]%=q;
		}
	while(a.size()>1&&!a.back())
		a.pop_back();
	return;
}
char s[100001];
int main()
{
	init();
	scanf("%d%d%s",&p,&q,s),a[0].emplace_back(p),push(a[0]);
	for(int i=1;i<20;i++)
	{
		int q=1;
		for(;1<<q<a[i-1].size()<<1;q++);
		a[i]=a[i-1],ntt(a[i],q);
		for(int j=0;j<1<<q;j++)
			a[i][j]=1ll*a[i][j]*a[i][j]%mod;
		intt(a[i],q),push(a[i]);
	}
	int ls=strlen(s);
	for(int i=1;i<=ls;i++)
	{
		std::vector<int>v;
		v.emplace_back(s[ls-i]<='9'?s[ls-i]^'0':s[ls-i]<='Z'?(s[ls-i]^'A'-1)+9:(s[ls-i]^'a'-1)+35),push(v);
		int j=0;
		for(;1<<j<(i&-i);j++)
		{
			int q=1;
			for(;1<<q<a[j].size()+v.size();q++);
			std::vector<int>z=a[j];
			ntt(z,q),ntt(v,q);
			for(int k=0;k<1<<q;k++)
				v[k]=1ll*z[k]*v[k]%mod;
			intt(v,q),push(v);
			if(v.size()<b[j].size())
				v.resize(b[j].size());
			for(int k=0;k<b[j].size();k++)
				v[k]+=b[j][k];
			push(v);
		}
		b[j]=v;
	}
	std::vector<int>v;
	for(int i=0;i<20;i++)
		if(ls&1<<i)
		{
			if(!v.empty())
			{
				int q=1;
				for(;1<<q<a[i].size()+v.size();q++);
				std::vector<int>z=a[i];
				ntt(z,q),ntt(v,q);
				for(int k=0;k<1<<q;k++)
					v[k]=1ll*z[k]*v[k]%mod;
				intt(v,q),push(v);
			}
			if(v.size()<b[i].size())
				v.resize(b[i].size());
			for(int k=0;k<b[i].size();k++)
				v[k]+=b[i][k];
			push(v);
		}
	for(int i=v.size()-1;~i;i--)
		printf("%c",v[i]["0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"]);
	return 0;
}