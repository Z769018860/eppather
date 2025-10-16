#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <unordered_map>
#define int long long
using namespace std;
const int mod=998244353,inv6=166374059;
int n,m,q,sq,cnt,M,p[20],a[200010];
int pos[200010],x[200010],k[200010];
unordered_map<int,int>sum,mp;
void ins(int x){
    for(int i=1;i<=cnt;i++)while(x%p[i]==0)x/=p[i];
    for(int i=2;i*i<=x;i++){
        if(x%i==0){
            p[++cnt]=i;
            while(x%i==0)x/=i;
        }
    }
    if(x!=1)p[++cnt]=x;
}
void dfs(int x,int val){
    a[++a[0]]=val;
    for(int i=x;i<=cnt&&1ll*p[i]*val<=n;i++)dfs(i,val*p[i]);
}
int g1[200010],g2[200010];
int find(int x){
    return x<=sq?g1[x]:g2[n/x];
}
int s(int n){
    n%=mod;
    return 1ll*n*(n+1)%mod*(2*n+1)%mod*inv6%mod;
}
signed main(){
    scanf("%lld%lld%lld",&n,&m,&q);
    for(int i=1;i<=m;i++){
        scanf("%lld%lld",&pos[i],&x[i]);sum[pos[i]]=(sum[pos[i]]+x[i])%mod;
        ins(pos[i]);
    }
    for(int i=1;i<=q;i++)scanf("%lld",&k[i]),ins(k[i]);
    sort(p+1,p+cnt+1);
    dfs(1,1);
    sort(a+1,a+a[0]+1);
    sq=100000;
    int blo=n/(sq+1);
    for(int i=1;i<=sq;i++)g1[i]=s(i);
    for(int i=1;i<=blo;i++)g2[i]=s(n/i);
    for(int i=1;i<=cnt;i++){
        int t=1ll*p[i]*p[i]%mod,lim=blo/p[i];
        for(int j=1;j<=lim;j++)g2[j]=(g2[j]-t*g2[j*p[i]]%mod+mod)%mod;
        for(int j=lim+1;j<=blo;j++)g2[j]=(g2[j]-t*g1[n/(j*p[i])]%mod+mod)%mod;
        for(int j=sq;j>=1;j--)g1[j]=(g1[j]-t*g1[j/p[i]]%mod+mod)%mod;
    }
    for(int i=1;i<=cnt;i++){
        for(int j=1;j<=a[0];j++){
            if(a[j]%p[i]==0){
                sum[a[j]]=(sum[a[j]]+1ll*sum[a[j]/p[i]]*p[i])%mod;
            }
        }
    }
    for(int i=1;i<=a[0];i++)sum[a[i]]=1ll*sum[a[i]]*find(n/a[i])%mod;
    for(int i=1;i<=cnt;i++){
        for(int j=a[0];j>=1;j--){
            if(a[j]%p[i]==0){
                sum[a[j]/p[i]]=(sum[a[j]/p[i]]+1ll*sum[a[j]]*p[i])%mod;
            }
        }
    }
    for(int i=1;i<=q;i++)printf("%lld\n",sum[k[i]]);
    return 0;
}