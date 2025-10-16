#include<bits/stdc++.h>
using namespace std;
const int MOD=998244353;
void add(int &x,int y){ x+=y; if(x>=MOD) x-=MOD; if(x<0) x+=MOD; }
int ad(int x,int y){ x+=y; if(x>=MOD) x-=MOD; if(x<0) x+=MOD; return x; }
int power(int x,int y){
    int ans=1;
    for(;y;y>>=1,x=1ll*x*x%MOD) if(y&1) ans=1ll*ans*x%MOD;
    return ans;
}
int n,m,k,jc,invk,inv[25],ans;
int u[1<<21][25],f[1<<21][25],g[25],h[25];
void fwt(int f[1<<21][25],int type){
    for(int mid=1;mid<(1<<n);mid<<=1)
        for(int i=0;i<(1<<n);i+=mid<<1)
            for(int j=0;j<mid;++j)
                for(int k=0;k<=n;++k) add(f[i|j|mid][k],type*f[i|j][k]);
}
int main(){
    
    scanf("%d%d%d",&n,&m,&k);
    jc=1; for(int i=1;i<=k;++i) jc=1ll*jc*i%MOD; invk=power(jc,MOD-2);
    for(int i=1;i<=n+1;++i) inv[i]=power(i,MOD-2);
    for(int i=0,s;i<m;++i) scanf("%d",&s),++u[s][__builtin_popcount(s)];
    fwt(u,1);
    for(int s=0;s<(1<<n);++s){
        int sp=-1,tp=-1;
        for(int i=0;i<=n;++i){
            g[i]=u[s][i],h[i]=0;
            if(sp==-1&&g[i]) sp=i;
        }
        tp=sp*k;
        if(sp!=-1&&tp<=n){
            h[tp]=power(g[sp],k);
            for(int i=0;tp+i+1<=n;++i){
                for(int j=0;j<=i;++j){
                    add(h[i+1+tp],1ll*k*h[j+tp]%MOD*g[i-j+1+sp]%MOD*(i-j+1)%MOD);
                    if(j<i) add(h[i+1+tp],-1ll*h[j+1+tp]*(j+1)%MOD*g[i-j+sp]%MOD);
                }
                h[i+1+tp]=1ll*h[i+1+tp]*power(1ll*g[sp]*(i+1)%MOD,MOD-2)%MOD;
            }
        }
        int t=1; f[s][0]=1;
        for(int i=1;i<=k;++i) t=1ll*t*g[0]%MOD*inv[i]%MOD,add(f[s][0],t);
        for(int i=0;i<n;++i){
            for(int j=0;j<=i;++j) add(f[s][i+1],1ll*g[j+1]*(j+1)%MOD*ad(f[s][i-j],-1ll*h[i-j]*invk%MOD)%MOD);
            f[s][i+1]=1ll*f[s][i+1]*inv[i+1]%MOD;
        }
    }
    fwt(f,-1),printf("%d",f[(1<<n)-1][n]);

    return 0;
}