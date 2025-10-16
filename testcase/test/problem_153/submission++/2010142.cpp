#include<bits/stdc++.h>
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define dwn(i,x,y) for(int i=x;i>=y;i--)
#define ll long long
using namespace std;
template<typename T>inline void qr(T &x){
    x=0;int f=0;char s=getchar();
    while(!isdigit(s))f|=s=='-',s=getchar();
    while(isdigit(s))x=x*10+s-48,s=getchar();
    x=f?-x:x;
}
int cc=0,buf[31];
template<typename T>inline void qw(T x){
    if(x<0)putchar('-'),x=-x;
    do{buf[++cc]=int(x%10);x/=10;}while(x);
    while(cc)putchar(buf[cc--]+'0');
}
const int N=(1<<22)+10,mod=998244353;
int n,m,k,f[N],sum[N],g[N];
int fc[N],ifc[N];
int power(int a,int b){
    int ret=1;
    while(b){
        if(b&1)ret=1ll*ret*a%mod;
        a=1ll*a*a%mod;b>>=1;
    }
    return ret;
}
int C(int x,int y){
    if(x<0||y<0||x<y)return 0;
    return 1ll*fc[x]*ifc[y]%mod*ifc[x-y]%mod;
}
void solve(){
    qr(n),qr(m),qr(k);
    int t=(1<<n)-1;
    rep(i,1,m){
        int x;qr(x);
        x^=t;
        f[x]++;
    }
    rep(i,0,n-1)
        rep(j,0,(1<<n)-1-(1<<i))
            if(!(j>>i&1))
                f[j]+=f[j+(1<<i)];
    fc[0]=1;
    rep(i,1,m)fc[i]=1ll*fc[i-1]*i%mod;
    ifc[m]=power(fc[m],mod-2);
    dwn(i,m-1,0)ifc[i]=1ll*ifc[i+1]*(i+1)%mod;
    int ans=0;
    g[0]=1;
    rep(i,1,m){
        rep(j,0,min(i,k))g[i]=(g[i]+C(i,j))%mod;
    }
    rep(i,0,(1<<n)-1){
        if(i)sum[i]=sum[i-(i&-i)]+1;
        if(sum[i]&1){
            ans=(ans-g[f[i]]+mod)%mod;
        }
        else{
            ans=(ans+g[f[i]])%mod;
        }
    }
    qw(ans);
}
int main(){
    int tt;tt=1;
    while(tt--)solve();
    return 0;
}