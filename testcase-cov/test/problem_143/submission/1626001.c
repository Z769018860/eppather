#include<stdio.h>
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
ll k[9]={2,3,5,7,11,13,17,37,24251};
ll mul(ll a,ll b,ll p)
{
    ull c=(ull)a*b-(ull)((ld)a/p*b+0.5L)*p;
    if(c<p)
        return c;
    return c+p;
}
ll quick(ll a,ll n,ll p)
{
    ll ans=1;
    while(n>0)
    {
        if(n&1)
            ans=mul(ans,a,p);
        n>>=1;
        a=mul(a,a,p);
    }
    return ans;
}
int mile(ll x,ll a)
{
    ll d=x-1,r=0;
    while(!(d&1))
    {
        d>>=1;r++;
    }
    ll t=quick(a,d,x);
    if(t==1) return 1;
    for(int i=0;i<r;i++)
    {
        if(t==x-1) return 1;
        t=mul(t,t,x);
    }
    return 0;
}
int prime(ll x)
{
    if(x<=3)  return x>1;
    if(!(x&1)) return 0;
    for(int i=0;i<9;i++)
    {
        if(x==k[i]) return 1;
        if(x%k[i]==0) return 0;
        if(!mile(x,k[i])) return 0;
    }
    return 1;
}
int main(void)
{
    ll x;
    while(~scanf("%lld",&x))
    {
        if(prime(x))
            printf("Y\n");
        else
            printf("N\n");
    }
    return 0;
}
