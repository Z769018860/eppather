#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7;
int quick_pow(int a,int b){
    if(b==0)
        return 1ll;
    if(b==1)
        return a%mod;
    int sum=quick_pow(a,b/2);
    sum*=sum,sum%=mod;
    if(b%2)
        sum*=a,sum%=mod;
    return sum;
}
int n,m,k,a[1000005],ans;
int cnt[1<<22],sum[1<<22];
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m>>k;
    for(int i=1; i<=m; i++){
        cin>>a[i];
        cnt[a[i]]++;
    }
    sum[0]=0;
    for(int i=1; i<(1<<n); i++)
        sum[i]=sum[i/2]+(i&1);
    for(int i=0; i<n; i++)
        for(int j=1; j<(1<<n); j++)
            if(j&(1<<i))
                cnt[j-(1<<i)]+=cnt[j];
    for(int i=1; i<(1<<n); i++){
        if(sum[i]%2)
            ans+=quick_pow(cnt[i],k);
        else
            ans-=quick_pow(cnt[i],k);
        ans=(ans%mod+mod)%mod;
    }
    cout<<ans;
    return 0;
}
