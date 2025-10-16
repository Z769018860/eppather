#include<bits/stdc++.h>
#pragma GCC optimize(3)
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#pragma GCC optimize(2)
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