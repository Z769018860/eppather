#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<cassert>
#include<stack>
#include<queue>
#include<vector>
#include<map>
#include<cstdlib>
#include<set>
using namespace std;
#define ll long long
#define ull unsigned long long
#define int ll
int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0' || ch>'9')
	{
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9')
	{
		x=x*10+(ch-'0');
		ch=getchar();
	}
	return x*f;
}
const int MAXN=3e5+10;
int n,q;
int s[MAXN];
int a[MAXN],k;
signed main()
{
	
	
	n=read();
	int maxn=0;
	for(int i=1;i<=n;i++)
		s[i]=read(),maxn=max(maxn,s[i]);
	q=read();
	while(q--)
	{
		int maxn=-1e18,minn=1e18;
		a[0]=read(),a[1]=read(),k=read();
		if(a[0]==0 && a[1]==0)
		{
			printf("%lld %lld\n",s[1],s[1]);
			continue;
		}
		maxn=max(a[0],a[1]),minn=min(a[0],a[1]);
		int i=2;
		while(1)
		{
			a[i]=k*a[i-1]+a[i-2];
			if(a[i]>0 && a[i-1]>0 && a[i]>maxn)
				break;
			if(a[i]<0 && a[i-1]<0 && a[i]<minn)
				break;
			maxn=max(maxn,a[i]),minn=min(minn,a[i]);
			i++;
		}
		int pos1=-1,pos2=-1;
		int t=i;
		for(int i=1;i<=n;i++)
		{
			if(s[i]>t)
				break;
			if(pos1==-1 || a[s[i]]>a[pos1])
				pos1=s[i];
			if(pos2==-1 || a[s[i]]<a[pos2])
				pos2=s[i];
		}
		if(s[n]>t)
		{
			if(a[t]<0)
			{
				if(pos1==-1)
					pos1=s[1];
				pos2=s[n];
			}
			else
			{
				if(pos2==-1)
					pos2=s[1];
				pos1=s[n];
			}
		}
		printf("%lld %lld\n",pos1,pos2);
	}
	return 0;
}