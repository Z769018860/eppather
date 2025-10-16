#include<bits/stdc++.h>
#define endl '\n'
using namespace std;

#define int long long

const int mod=998244353;
int qpow(int a,int b){
    int ans=1;
    while(b){
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
int inv_2,inv_6;
int pre(int x){
    return (2*x*(x+1)%mod*(2*x+1)%mod*inv_6%mod+3*x*(x+1)%mod*inv_2%mod+5*x)%mod;
}


void solve(){
    inv_2=qpow(2,mod-2),inv_6=qpow(6,mod-2);
    int n,ans=0;
    cin>>n;
    for(int l=1,r;l<=n;l=r+1){
        r=n/(n/l);
        ans+=(pre(r)-pre(l-1))%mod*(n/l)%mod;
        ans%=mod;
    }
    ans=(ans+mod)%mod;
    cout<<ans<<endl;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T=1;
   
    while(T--){
        solve();
    }
}
