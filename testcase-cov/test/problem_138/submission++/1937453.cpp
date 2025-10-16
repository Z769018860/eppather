
#include<iostream>
#include<cstring>
using namespace std;
namespace lly
{
    constexpr int N=15;using ll=long long;constexpr ll mod=1e9+7;
    inline ll qpow(ll a,ll b){ll ret=1;a%=mod;for(;b;a=a*a%mod,b>>=1) if(b&1) ret=ret*a%mod;return ret;}
    ll fac[N],ifac[N];
    inline void init(const int n)
    {
        fac[0]=ifac[0]=1;
        for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
        ifac[n]=qpow(fac[n],mod-2);
        for(int i=n-1;i>0;i--) ifac[i]=ifac[i+1]*(i+1)%mod;
    }
    inline ll binom(ll n,ll m){return fac[n]*ifac[m]%mod*ifac[n-m]%mod;}
    struct dat{ll f[N][N],u,r;};dat t0,tou,tor;int d1,d2;
    inline dat operator+(const dat&x,const dat&y)
    {
        dat res;ll p1=1,p2=1;res.u=x.u+y.u;res.r=x.r+y.r;memcpy(res.f,x.f,sizeof(res.f));
        for(int dx=0;dx<=d1;dx++)
            for(int dy=0;dy<=d2;dy++)
                for(int i=(p1=1,dx);i>=0;i--,p1=p1*(x.r%mod)%mod)
                    for(int j=(p2=1,dy);j>=0;j--,p2=p2*(x.u%mod)%mod)
                        res.f[dx][dy]=(res.f[dx][dy]+y.f[i][j]*p1%mod*p2%mod*binom(dx,i)%mod*binom(dy,j)%mod)%mod;
        return res;
    }
    inline dat operator*(dat a,ll b){dat res=t0;for(;b;a=a+a,b>>=1)if(b&1) res=res+a;return res;}
    inline dat ugcd(ll a,ll b,ll c,ll n,const dat&tu,const dat&tr)
    {
        b%=c;if(a>=c) return ugcd(a%c,b,c,n,tu,tu*(a/c)+tr);
        ll m=(a*n+b)/c;if(!m) return tr*n;
        return tr*((c-b-1)/a)+tu+ugcd(c,c-b-1,a,m-1,tr,tu)+tr*(n-(m*c-b-1)/a);
    }
    inline void solve()
    {
        ll a,b,c,n;cin>>n>>a>>b>>c>>d1>>d2;init(max(d1,d2));
        memset(t0.f,0,sizeof(t0.f));memset(tou.f,0,sizeof(tou.f));memset(tor.f,0,sizeof(tor.f));
        tou.u=1;tor.r=1;for(int i=0;i<=d1;i++) tor.f[i][0]=1;
        ll ans=(tou*(b/c)+ugcd(a,b,c,n,tou,tor)).f[d1][d2];if(d1==0) ans=(ans+qpow(b/c,d2))%mod;
        cout<<ans<<"\n";
    }
    inline void work()
    {
        ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
        int T;cin>>T;while(T--) solve();
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