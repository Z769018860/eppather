#include<bits/stdc++.h>
using namespace std;
const int mo=998244353;
#define int long long
long long n,m,k,f[2200001],vis[22],iv[1001],ivv[1001];
long long ans[2200001][22];
inline void OR(long long *f,int x=1){
for (int i=0;i<n;++i) for (int j=0;j<(1<<n);++j) if (j>>i&1) f[j]=(f[j]+x*f[j^(1<<i)]+mo)%mo;
}
inline void OR(int x=1){
for (int i=0;i<n;++i) for (int j=0;j<(1<<n);++j) if (j>>i&1) for (int num=0;num<=n;++num) ans[j][num]=(ans[j][num]+x*ans[j^(1<<i)][num]+mo)%mo;
}
inline long long ksm(long long x,long long y){if (mo==1) return 0; long long ans=1;for (int i=0;(y>>i);++i){if (y>>i&1) ans=ans*x%mo; x=x*x%mo;}return ans;}
inline long long invv(long long x){return ksm(x,mo-2);}

inline void INV(long long *f){
long long g[22]; memset(g,0,sizeof(g));
g[0]=invv(f[0]);
for (int i=1;i<=n;++i){
for (int j=0;j<i;++j) g[i]=(g[i]-g[j]*f[i-j])%mo;
g[i]=(g[i]*g[0]%mo+mo)%mo;
}
for (int i=0;i<=n;++i) f[i]=g[i];
}

inline void LN(long long *f){
long long g[22]; memset(g,0,sizeof(g)); assert(f[0]==1);
for (int i=0;i<n;++i){
long long na=iv[i+1]; g[i+1]=(i+1)*f[i+1]%mo;
for (int j=0;j<i;++j) g[i+1]=(g[i+1]-(j+1)*g[j+1]%mo*f[i-j])%mo;
g[i+1]=(g[i+1]*na)%mo;
}
for (int i=0;i<=n;++i) f[i]=g[i];
}

inline void EXP(long long *f){
long long g[22]; memset(g,0,sizeof(g)); assert(f[0]==0);
g[0]=1;
for (int i=0;i<n;++i){for (int j=0;j<=i;++j) g[i+1]=(g[i+1]+g[j]*f[i-j+1]%mo*(i-j+1))%mo; g[i+1]=g[i+1]*iv[i+1]%mo;}
for (int i=0;i<=n;++i) f[i]=g[i];
}

inline void trans(long long *f){
long long A[22],g[22],val=f[0];
memset(A,0,sizeof(A)); memset(g,0,sizeof(g));
for (int i=0;i<n;++i) A[i]=(i+1)*f[i+1]%mo;
int tmp=0;
while (tmp<=n && !f[tmp]) ++tmp;
if (tmp>n){f[0]=1; return;}
if (tmp) for (int i=tmp;i<=n;++i) f[i-tmp]=f[i],f[i]=0;
long long na=f[0],nv=invv(na);
for (int i=0;i<=n;++i) f[i]=f[i]*nv%mo;
LN(f); for (int i=0;i<=n;++i) f[i]=f[i]*k%mo; EXP(f);
na=ksm(na,k);
for (int i=0;i<=n;++i) f[i]=f[i]*na%mo;
if (tmp){for (int i=n;i>=0;--i){if (i+tmp*k<=n) f[i+tmp*k]=f[i]; f[i]=0;}}
for (int i=0;i<=n;++i) f[i]=f[i]*ivv[k]%mo;
na=1;
for (int i=0;i<=k;++i) g[0]=(g[0]+na*ivv[i])%mo,na=na*val%mo;
for (int i=0;i<n;++i){for (int j=0;j<=i;++j) g[i+1]=(g[i+1]+A[i-j]*(g[j]-f[j]))%mo; g[i+1]=g[i+1]*iv[i+1]%mo;}
for (int i=0;i<=n;++i) f[i]=g[i];
}


signed main(){
ios::sync_with_stdio(false); cin.tie(0);
ivv[0]=1;
for (int i=1;i<=100;++i) iv[i]=invv(i),ivv[i]=iv[i]*ivv[i-1]%mo;

cin>>n>>m>>k;

for (int i=1;i<=m;++i){int x; cin>>x; ++ans[x][__builtin_popcount(x)];}

OR();
for (int i=0;i<(1<<n);++i) trans(ans[i]);
OR(mo-1);
cout<<(ans[(1<<n)-1][n]%mo+mo)%mo;
return 0;
}