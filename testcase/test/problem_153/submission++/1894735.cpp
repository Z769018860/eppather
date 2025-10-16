#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll mod=998244353;
const int N=(1<<22)+5,M=2e5+5;
int n,m,k,len;ll a[N];
ll mul[M],inv[M];
ll qpow(ll x,ll y)
{
    ll res=1;while(y){if(y&1ll) res=res*x%mod; x=x*x%mod,y>>=1;} return res;
}
inline ll C(int x,int y){return x<y?0:mul[x]*inv[y]%mod*inv[x-y]%mod;}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n>>m>>k;len=(1<<n);
    for(int i=1,v;i<=m;i++){cin>>v;a[v]++;}
    for(int i=1;i<len;i<<=1)
        for(int j=0;j<len;j+=2*i)
            for(int k=0;k<i;k++)
                a[i+j+k]+=a[j+k];
    mul[0]=1;
    for(int i=1;i<M;i++)
        mul[i]=mul[i-1]*i%mod;
    inv[M-1]=qpow(mul[M-1],mod-2);
    for(int i=M-2;i>=0;i--)
        inv[i]=inv[i+1]*(i+1ll)%mod;
    for(int i=0;i<len;i++)
    {
        ll sum=0;
        for(int j=1;j<=k;j++)
            sum+=C(a[i],j),sum%=mod;
        a[i]=sum;
    }
    for(int i=1;i<len;i<<=1)
        for(int j=0;j<len;j+=2*i)
            for(int k=0;k<i;k++)
                a[i+j+k]+=mod-a[j+k],a[i+j+k]%=mod;
    cout<<a[len-1];
    return 0;
}