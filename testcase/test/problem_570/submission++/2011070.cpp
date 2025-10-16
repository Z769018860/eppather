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
const int N=(1<<22)+10,mod=1e9+7;
int n,m,k,f[N],sum[N];
int power(int a,int b){
    int ret=1;
    while(b){
        if(b&1)ret=1ll*ret*a%mod;
        a=1ll*a*a%mod;b>>=1;
    }
    return ret;
}
void solve(){
    qr(n),qr(m),qr(k);
    int t=(1<<n)-1;
    rep(i,1,m){
        int x;qr(x);
        f[x]++;
    }
    rep(i,0,n-1)
        rep(j,0,(1<<n)-1-(1<<i))
            if(!(j>>i&1))
                f[j]+=f[j+(1<<i)];
    int ans=0;
    rep(i,1,(1<<n)-1){
        if(i)sum[i]=sum[i-(i&-i)]+1;
        if(sum[i]&1){
            ans=(ans+power(f[i],k))%mod;
        }
        else{
            ans=(ans-power(f[i],k)+mod)%mod;
        }
    }
    qw(ans);
}
int main(){
    int tt;tt=1;
    while(tt--)solve();
    return 0;
}