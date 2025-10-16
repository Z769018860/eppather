#include<bits/stdc++.h>
using namespace std;
constexpr int mod=1000000007;
int n,k,cnt,p[1000005],si[10000005];
bool on[10000005];
long long ans;
inline int omega(int x,int y){
    int ret=1;
    while(y){
        if(y&1) ret=1ll*ret*x%mod;
        x=1ll*x*x%mod,y>>=1;
    }
    return (ret+1)%mod;
}
int main(){
    scanf("%d%d",&n,&k);
    si[1]=1,on[1]=1;
    for(int i=1;i<=n;i++){
        if(!on[i]) p[++cnt]=i,si[i]=omega(i,k);
        for(int j=1;j<=cnt&&i*p[j]<=n;j++){
            on[i*p[j]]=1;
            si[i*p[j]]=1ll*si[i]*si[p[j]]%mod;
            if(i%p[j]==0){
                si[i*p[j]]=(1ll*(si[i]-si[i/p[j]])*(si[p[j]]-1)+si[i])%mod;
                break;
            }
        }
    }
    for(int i=1;i<=n;i++) ans+=si[i];
    ans=(ans%mod+mod)%mod;
    printf("%lld\n",ans);
    return 0;
}