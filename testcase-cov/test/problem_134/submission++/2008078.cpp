#include<bits/stdc++.h>
using namespace std;
const int N = 5e3+5;
typedef long long ll;
int n,m;
ll tr[N][N];
inline ll read()
{
    ll x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
ll lowbit(int x) 
{
	return x&-x;
}
void add(int x,int y,int val)
{
	for(int i=x;i<=n;i+=lowbit(i))
	{
		for(int j=y;j<=m;j+=lowbit(j))
		{
			tr[i][j]+=val;
		}
	}
}
ll sum(int x,int y)
{
	ll ans=0;
	for(int i=x;i;i-=lowbit(i))
	{
		for(int j=y;j;j-=lowbit(j))
		{
			ans+=tr[i][j];
		}
	}
	return ans;
}
int main()
{
	cin.tie(0);cout.tie(0);
	n=read();m=read();
	ll ord;
	while(~scanf("%lld",&ord))
	{
		if(ord==1)
		{
			ll x,y,xx,yy,v; 
			x=read();y=read();
			xx=read();yy=read();
			v=read();
			add(x,y,v);
			add(xx+1,yy+1,v);
			add(x,yy+1,-v);
			add(xx+1,y,-v);
		}
		else
		{
			ll x,y;
			x=read();y=read(); 
			cout<<sum(x,y)<<'\n';
		}
	}
	return 0;
}