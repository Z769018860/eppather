#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=(1<<22),Mod=1e9+7;

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
inline int Pow(int x,int y)
{
    int res=1;
    while(y)
    {
        if(y&1) res=1ll*res*x%Mod;
        x=1ll*x*x%Mod,y>>=1;
    }
    return res;
}

int n,m,K,lim,f[Maxn+5];

int main()
{
    

    n=read(),m=read(),K=read(),lim=(1<<n)-1;
    For(i,1,m) {int x=read(); f[x]++;}
    For(i,0,n-1) For(j,0,lim) if(j&(1<<i))
        f[j^(1<<i)]+=f[j];
    int ans=0;
    For(i,0,lim)
    {
        int res=Pow(f[i],K);
        if(__builtin_popcount(i)&1) ans=(ans-res+Mod)%Mod;
        else ans=(ans+res)%Mod;
    }
    ans=(Pow(m,K)-ans+Mod)%Mod;
    cout<<ans<<endl;
    return 0;
}