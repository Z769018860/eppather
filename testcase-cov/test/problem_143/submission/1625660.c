#include<stdio.h>
typedef long long ll;
ll quick(ll a,ll n,ll p)
{
    ll ans=1;
    while(n>0)
    {
        if(n&1)
            ans=(__int128)ans*a%p;
        n>>=1;
        a=(__int128)a*a%p;
    }
    return ans;
}
int prime(ll x)
{
    if(x<=3)  return x>1;
    if(!(x&1)) return 0;
    ll k[7]={2,325,9375,28178,450775,9780504,1795265022},d=x-1,r=0;
    while(!(d&1))
    {
        d>>=1;r++;
    }
    for(int i=0;i<7;i++)
    {
        ll a=k[i];
        ll t=quick(a,d,x);
        if(t<=1||t==x-1)
            continue;
        for(int i=0;i<r;i++)
        {
            t=(__int128)t*t%x;
            if(t==x-1&&i!=r-1)
            {
                t=1;
                break;
            }
            if(t==1) return 0;
        }
        if(t!=1)  return 0;
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