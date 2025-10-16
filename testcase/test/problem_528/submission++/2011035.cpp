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
const int N=5e6+10,mod=998244353;
int cnt,p[N],mu[N];bool v[N];
void solve(){
    v[1]=1;
    int t=5e6;
    mu[1]=1;
    rep(i,2,t){
        if(!v[i])p[++cnt]=i,mu[i]=-1;
        for(int j=1;j<=cnt&&i*p[j]<=t;j++){
            v[i*p[j]]=1;
            if(i%p[j]==0){
                mu[i*p[j]]=0;
                break;
            }
            else mu[i*p[j]]=-mu[i];
        }
    }
    ll n,m;qr(n),qr(m);
    if(n>m)swap(n,m);
    int ans=0;
    for(int i=1;1ll*i*i<=n;i++){
        int p1=(n/(1ll*i*i))%mod;
        int p2=(m/(1ll*i*i))%mod;
        ans=(ans+1ll*mu[i]*p1*p2%mod+mod)%mod;
    }
    cout<<ans<<endl;
}
int main(){
    int tt;tt=1;
    while(tt--)solve();
    return 0;
}