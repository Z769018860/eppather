#include<bits/stdc++.h>
using namespace std;
const int N = 5e3+5;
typedef long long ll;
int n,m;
ll a[N][N],b[N][N],c[N][N],d[N][N];
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
void add(ll x, ll y, ll v) 
{
    for(int i=x;i<=n;i+=lowbit(i))
	{
        for(int j=y;j<=m;j+=lowbit(j))
		{
            a[i][j]+=v;
            b[i][j]+=(x-1)*v;
            c[i][j]+=(y-1)*v;
            d[i][j]+=(x-1)*(y-1)*v;
        }
    }
}
ll sum(ll x,ll y)
{
    ll ans=0;
    for(int i=x;i;i-=lowbit(i))
	{
        for(int j=y;j;j-=lowbit(j))
		{
            ans+=x*y*a[i][j]-y*b[i][j]-x*c[i][j]+d[i][j];
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
			ll x,y,xx,yy; 
			x=read();y=read();
			xx=read();yy=read();
			cout<<sum(xx,yy)-sum(xx,y-1)-sum(x-1,yy)+sum(x-1,y-1)<<'\n';
		}
	}
	return 0;
}