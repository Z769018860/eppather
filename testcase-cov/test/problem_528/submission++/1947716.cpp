#include<bits/stdc++.h>
using namespace std;
#define ll long long
int const N=1e7+10;
int const mod=998244353;
ll n,m;int prime[N],sm[N],mu[N];
bool vis[N];
inline void init(){
    mu[1]=1;
    for (int i=2;i<N;++i){
        if (!vis[i]) prime[++prime[0]]=i,mu[i]=-1;
        for (int j=1;j<=prime[0] && i*prime[j]<N;++j){
            vis[i*prime[j]]=1;
            if (i%prime[j]==0) break;
            mu[i*prime[j]]=-mu[i];
        }
    }
    for (int i=1;i<N;++i) sm[i]=sm[i-1]+mu[i];
}
inline int sum(ll x){
    x=sqrt(x);
    return sm[x];
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n>>m,init();
    if (n>m) swap(n,m);
    int ans=0;
    for (ll l=1,r=0;l<=n;l=r+1){
        r=min(n/(n/l),m/(m/l));
        ans+=1ll*((n/l)%mod)*((m/l)%mod)%mod*(sum(r)+mod-sum(l-1))%mod,ans%=mod;
    }
    return cout<<ans<<'\n',0;
}