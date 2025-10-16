#include<bits/stdc++.h>
#define ll long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=1e4;

inline ll read()
{
    ll x=0,f=1;
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

int T,n; ll a[Maxn+5],pr[Maxn+5],m;
inline int isPrime(int x)
{for(int i=2;i*i<=x;++i) if(x%i==0) return 0; return 1;}
inline int Check(int id,ll mid)
{
    ll res=0;
    for(ll i=pr[id];;)
    {
        res+=mid/i;
        if(res>=a[id]) return 1;
        if(i>mid/pr[id]) break; i*=pr[id];
    } return (res>=a[id]);
}
inline void Solve()
{
    n=read(); ll l=1,r=1,mx=1;
    For(i,1,n) a[i]=read(),mx=max(mx,a[i]*pr[i]);
    For(i,1,n)
    {
        r=mx; while(l<r)
        {
            ll mid=(l+r)/2;
            if(Check(i,mid)) r=mid; else l=mid+1;
        }
    } printf("%lld\n",l);
}

int main()
{
    

    For(i,2,Maxn) if(isPrime(i)) pr[++m]=i;
    T=read(); while(T--) Solve();
    return 0;
}