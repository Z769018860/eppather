#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1<<21,mod=998244353;
int n;
ll f[N][22];
void add(ll &x,ll y){
    x+=y;
    if(x>=mod)x-=mod;
}
void fwt(int op){
    for(ll j=1;j<(1<<n);j<<=1){
        for(ll i=0;i<(1<<n);i+=(j<<1)){
            for(ll k=0;k<j;k++)for(int d=1;d<=n;d++){
                if(op==1)add(f[i+k+j][d],f[i+k][d]);
                else add(f[i+k+j][d],mod-f[i+k][d]);
            }
        }
    }
}
ll g[22],h[22],ans[22];
int c[N];
ll inv[30],fac[30];
ll Pw(ll x,int cnt){
    ll ans=1;
    while(cnt){
        if(cnt&1)ans=ans*x%mod;
        x=x*x%mod;
        cnt>>=1;
    }
    return ans;
}
void get(int K){
    int bit=-1;
    for(int i=0;i<=n;i++)h[i]=0;
    for(int i=0;i<=n;i++)if(g[i]){
        bit=i;
        break;
    }
    if(-1==bit||bit*K>n)return;
    for(int i=0;i<=n-bit;i++)g[i]=g[i+bit];
    for(int i=n-bit+1;i<=n;i++)g[i]=0;
    h[0]=Pw(g[0],K);ll invv=Pw(g[0],mod-2);
    for(int i=1;i<=n-bit;i++){
        for(int j=0;j<i;j++)add(h[i],g[j+1]*(j+1)%mod*h[i-1-j]%mod);
        h[i]=h[i]*K%mod;
        for(int j=0;j<i-1;j++)add(h[i],mod-h[j+1]*(j+1)%mod*g[i-1-j]%mod);
        h[i]=h[i]*inv[i]%mod*invv%mod;
    }
    for(int i=n;i>=bit*K;i--)h[i]=h[i-bit*K];
    for(int i=0;i<bit*K;i++)h[i]=0;
}
inline int read(){
    int x=0;char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    return x;
}
int main(){
    int m,K;n=read(),m=read(),K=read();
    inv[1]=fac[1]=1;
    for(int i=2;i<=n+1;i++)inv[i]=inv[mod%i]*(mod-mod/i)%mod,fac[i]=fac[i-1]*inv[i]%mod;
    for(int i=1;i<(1<<n);i++)c[i]=c[i>>1]+(i&1);
    for(int i=0;i<m;i++){
        int x=read();
        f[x][c[x]]++;
    }
    fwt(1);
    for(int I=1;I<(1<<n);I++){
        for(int i=0;i<=n;i++)g[i]=f[I][i];
        get(K);
        for(int i=0;i<=n;i++)g[i]=f[I][i];
        f[I][0]=1;
        
        
        for(int i=1;i<=n;i++){
            f[I][i]=0;
            for(int j=0;j<i;j++)add(f[I][i],g[j+1]*(j+1)%mod*(f[I][i-j-1]+mod-h[i-j-1]*fac[K]%mod)%mod);
            
            f[I][i]=f[I][i]*inv[i]%mod;
            
        }
    }
    fwt(-1);
    printf("%lld",f[(1<<n)-1][n]);
    return 0;
}