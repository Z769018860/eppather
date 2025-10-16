
#include<iostream>
using namespace std;
namespace lly
{
    constexpr int N=(1<<22)+5;using ll=long long;constexpr ll mod=998244353;
    inline ll qpow(ll a,ll b)
    {
        ll ret=1;a%=mod;
        for(;b;a=a*a%mod,b>>=1) if(b&1) ret=ret*a%mod;
        return ret;
    }
    ll fac[N],ifac[N];
    inline void init(const int n)
    {
        fac[0]=ifac[0]=1;
        for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
        ifac[n]=qpow(fac[n],mod-2);
        for(int i=n-1;i>0;i--) ifac[i]=ifac[i+1]*(i+1)%mod;
    }
    inline ll binom(ll n,ll m){return (n<0||m<0||n<m)?0:fac[n]*ifac[m]%mod*ifac[n-m]%mod;}
    inline void FWT(ll *f,int n,int op)
    {
        for(int i=1;i<n;i<<=1)
            for(int j=0;j<n;j+=i<<1)
                for(int k=0;k<i;k++)
                    f[i+j+k]=(f[i+j+k]+op*f[j+k]+mod)%mod;
    }
    ll f[N];
    inline void work()
    {
        ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
        int n,t,m;cin>>n>>t>>m;ll x;init(t);
        for(int i=1;i<=t;i++) cin>>x,f[x]++;
        FWT(f,1<<n,1);
        for(int i=0;i<(1<<n);i++) 
        {
            x=f[i];f[i]=0;
            for(int j=1;j<=m;j++) f[i]=(f[i]+binom(x,j))%mod;
        }
        FWT(f,1<<n,-1);
        cout<<f[(1<<n)-1]<<"\n";
    }
}
int main()
{
    #ifdef llydebug
    freopen(".in","r",stdin);
    #endif
    lly::work();
    return 0;
}