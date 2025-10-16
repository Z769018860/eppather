#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long LL;
const int N=2510;
const int M=20010;
const int base=131;
const int mod=998244353;
int n,m;
int x[M],y[M],c[M],len;
LL a[M],b[N][N],f[N*2][N];
vector<LL>ans;
LL qmi(LL x,LL k){
    LL res=1;
    while(k){if(k&1)res=res*x%mod;x=x*x%mod;k>>=1;}
    return res;
}
void Berlekamp_Massey(){
    LL w=0,sum=0;
    vector<LL>last;
    for(int i=1;i<=2*n+1;i++){
        LL res=0;for(int j=0;j<(int)ans.size();j++) res=(res+a[i-j-1]*ans[j])%mod;
        if((a[i]-res)%mod==0) continue;
        if(!w){
            w=i;sum=(a[i]-res+mod)%mod;
            for(int j=i;j;j--) ans.push_back(0);
            continue;
        }
        vector<LL>t=ans;
        LL tm=(a[i]-res)*qmi(sum,mod-2)%mod;
        while(ans.size()<last.size()+i-w) ans.push_back(0);
        ans[i-w-1]=(ans[i-w-1]+tm)%mod;
        for(int j=0;j<(int)last.size();j++) ans[i-w+j]=(ans[i-w+j]-tm*last[j])%mod;
        if(t.size()-i<last.size()-w) last=t,w=i,sum=(a[i]-res+mod)%mod;
    }
    return;
}
int main(){ 
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            scanf("%lld",&b[i][j]);
            if(b[i][j]) x[++len]=i,y[len]=j,c[len]=b[i][j];
        }
        scanf("%lld",&f[1][i]);
    }
    for(int i=2;i<=2*n+1;i++)
        for(int j=1;j<=len;j++)
            f[i][x[j]]=(f[i][x[j]]+f[i-1][y[j]]*c[j])%mod;
    for(int i=1;i<=2*n+1;i++)
        for(int j=1;j<=n;j++)
            a[i]=(a[i]*base+f[i][j])%mod;
    
    Berlekamp_Massey();
    int l=ans.size();
    
    for(int i=1;i<=n;i++){
        LL sum=f[l][i];
        for(int j=0;j<l-1;j++) sum=(sum-ans[j]*f[l-j-1][i]%mod+mod)%mod;
        LL Ans=(sum*qmi(ans[l-1],mod-2)%mod+mod)%mod;
        printf("%lld ",Ans);
    }
    return 0;
}