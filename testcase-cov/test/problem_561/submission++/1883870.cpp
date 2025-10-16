#include<bits/stdc++.h>

#define int long long 
using namespace std;
const long long mod=998244353;
int n,m,q;
int k[200100];
int prime[200100],cnt;
int s[200100],fb[200100],scnt,fcnt;
map<int,int>b,f,ans,g;
void dfs(int now,int id)
{
	s[++scnt]=now;
	if(id==cnt+1) return ;
	for(int i=id;i<=cnt;i++)
	{
		for(int j=1,p=prime[i];now*p<=n;j++,p=p*prime[i])
		{
			dfs(now*p,i+1);
		}
	}
	return ;
}
int fpow(int a,int b)
{
	int sum=1;
	for(;b;b>>=1)
	{
		if(b&1) sum=sum*a%mod;
		a=a*a%mod;
	}
	return sum;
}
signed main()
{
    cin>>n>>m>>q;
	for(int i=1;i<=m;i++)
	{
		int p,x;
		cin>>p>>x;
		if(b.find(p)==b.end())
		{
			int t=p;
			for(int j=1;j<=cnt;j++)
			{
				while(t%prime[j]==0) t/=prime[j];
			}
			for(int j=2;j*j<=n&&t!=1;j++)
			{
				if(t%j==0)
				{
					prime[++cnt]=j;
					while(t%j==0) t/=j;
				}
			}
			if(t!=1) prime[++cnt]=t;
		}
		b[p]=(b[p]+x)%mod;
	}
	for(int i=1;i<=q;i++)
	{
		cin>>k[i];
		int t=k[i];
		for(int j=1;j<=cnt;j++)
		{
			while(t%prime[j]==0) t/=prime[j];
		}
		for(int j=2;j*j<=n&&t!=1;j++)
		{
			if(t%j==0)
			{
				prime[++cnt]=j;
				while(t%j==0) t/=j;
			}
		}
		if(t!=1) prime[++cnt]=t;
	}
	dfs(1,1);
	
	
	map<int,int>::iterator it=b.begin();
	for(;it!=b.end();it++)
	{
		it->second=it->second*fpow(it->first,mod-2)%mod;
	}
	sort(s+1,s+1+scnt);
	for(int l=1,r;l<=n;l=r+1)
	{
		r=n/(n/l);
		fb[++fcnt]=n/l;
	}
	
	
	
	
	
	
	
	
	sort(fb+1,fb+1+fcnt);
	for(int i=1;i<=fcnt;i++)
	{
		int t=fb[i];
		f[t]=t*(t+1)%mod*(2*t+1)%mod*fpow(6,mod-2)%mod;
	}
	for(int i=1;i<=cnt;i++)
	{
		for(int j=fcnt;j>=1;j--)
		{
			int t=fb[j];
			f[t]=((f[t]-f[t/prime[i]]*prime[i]%mod*prime[i]%mod)%mod+mod)%mod;
		}
	}
	for(int i=1;i<=scnt;i++)
	{
		g[s[i]]=b[s[i]];
	}
	for(int i=1;i<=cnt;i++)
	{
		for(int j=1;j<=scnt;j++)
		{
			int t=s[j];
			if(t%prime[i]==0)
			{
				g[t]=(g[t]+g[t/prime[i]])%mod;
			}
		}
	}
	for(int i=1;i<=scnt;i++)
	{
		int t=s[i];
		ans[t]=t*t%mod*f[n/t]%mod*g[t]%mod;
	}
	for(int i=1;i<=cnt;i++)
	{
		for(int j=scnt;j>=1;j--)
		{
			int t=s[j];
			if(t*prime[i]<=n) ans[t]=(ans[t]+ans[t*prime[i]])%mod;
		}
	}
	for(int i=1;i<=q;i++)
	{
		cout<<ans[k[i]]*fpow(k[i],mod-2)%mod<<endl;
	}
	fclose(stdin);
	fclose(stdout);
    return 0;
}