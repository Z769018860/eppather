#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e6+5;
const int mod=998244353;
ll n,fac[maxn];
ll a[maxn],sum,ans,li[maxn];
ll ch(ll a,ll b){return a*b%mod;}
ll ad(ll a,ll b){return ((a+b)%mod+mod)%mod;}
void init()
{
    fac[0]=fac[1]=1;
    for(int i=2;i<=n;i++)fac[i]=ch(i,fac[i-1]);
}
struct tree{
    ll c[maxn];
    ll lb(ll x){return x&-x;}
    void upd(ll x,ll v)
    {
        for(;x<=n;x+=lb(x)) c[x]+=v;
    }
    ll qry(ll x)
    {
        ll res=0;
        for(;x;x-=lb(x)) res+=c[x];
        return res;
    }
}T;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    init();
    for(int i=1;i<=n;i++) T.upd(i,1);
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        ans=ad(ans,ch(T.qry(a[i])-1,fac[n-i]));
        T.upd(a[i],-1);
    }
    cout<<ans+1;
    return 0;
}