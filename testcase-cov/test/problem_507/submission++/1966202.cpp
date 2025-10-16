#include<bits/stdc++.h>
#define ll long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=1e6;
const ll inf=1e18;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,m,c[Maxn+5],h[Maxn+5]; ll w[Maxn+5];
ll f[Maxn+5],g[Maxn+5],sum[Maxn+5];

int main()
{
    

    n=read(),m=read();
    For(i,1,n) c[i]=read();
    For(i,1,n) h[i]=read(),sum[i]=sum[i-1]+h[i];
    For(i,1,n) f[i]=g[i]=inf;
    For(i,1,m) w[i]=inf;
    ll mn=0,ans=sum[n]; For(i,1,n)
    {
        g[i]=w[c[i]],f[i]=mn+sum[i-1],w[c[i]]=min(w[c[i]],f[i]);
        mn=min(mn,g[i]-sum[i]),ans=min(ans,g[i]+sum[n]-sum[i]);
    }
    cout<<sum[n]-ans<<endl;
    return 0;
}