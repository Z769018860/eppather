#include<bits/stdc++.h>
using namespace std;
int n,k,bn,bn1,prime[44727],prime1[1587406],cnt,cnt1,num,r[89449];
unsigned int pk[44727],fk[1587406],f[89449],g[89449],s[89449],ans;
bool vis[44727],vis1[1587406];
unsigned int qpow(unsigned int a,int b,unsigned int ans=1){
  for(;b;b>>=1)b&1&&(ans*=a),a*=a;
  return ans;
}
int prime_init(int n,int prime[],bool a[],int cnt=0){
  for(int i=2;i<=n;i++)a[i]=1;
  for(int i=2;i<=n;i++){
    if(a[i])prime[++cnt]=i;
    for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
      a[i*prime[j]]=0;
      if(i%prime[j]==0)break;
    }
  }
  return cnt;
}
int f_init(int n,int prime[],unsigned int f[],bool a[],int cnt=0){
  f[1]=0;
  for(int i=2;i<=n;i++)a[i]=1;
  for(int i=2;i<=n;i++){
    if(a[i])prime[++cnt]=i,f[i]=1;
    for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
      a[i*prime[j]]=0,f[i*prime[j]]=a[i]?pk[j]:f[i];
      if(i%prime[j]==0)break;
    }
  }
  return cnt;
}
int id(long long x){
  return x<=bn?x:num-n/x+1;
}
int main(){
  cin>>n>>k,bn=sqrt(n),bn1=pow(n,2.0/3),cnt=prime_init(bn,prime,vis);
  for(int i=1;i<=cnt;i++)pk[i]=qpow(prime[i],k);
  for(long long l=1;l<=n;l=r[num]+1)r[++num]=n/(n/l),g[num]=r[num]-1;
  for(int i=1,t;i<=cnt;i++){
    t=prime[i]*prime[i];
    for(int j=num;r[j]>=t;j--)g[j]-=g[id(r[j]/prime[i])]-i+1;
  }
  for(int j=cnt,t;j>=1;j--){
    t=prime[j]*prime[j];
    for(int i=num;r[i]>=t;i--){
      long long p=prime[j];
      for(int e=1;p*prime[j]<=r[i];e++,p*=prime[j]){
        s[i]+=s[id(r[i]/p)]+pk[j]*(g[id(r[i]/p)]-j+1);
      }
    }
  }
  cnt1=f_init(bn1,prime1,fk,vis1);
  for(int i=cnt1;i>=1;i--)for(int j=bn1/prime1[i];j>=1;j--)fk[prime1[i]*j]-=fk[j];
  for(int i=1;i<=bn1;i++)fk[i]+=fk[i-1];
  for(int i=1;i<=num;i++){
    if(r[i]<=bn1)f[i]=fk[r[i]];
    else{
      f[i]=s[i]+g[i];
      for(int l1=2,r1;l1<=r[i];l1=r1+1)r1=r[i]/(r[i]/l1),f[i]-=(r1-l1+1)*f[id(r[i]/l1)];
    }
  }
  for(int i=1;i<=num;i++)ans+=1ll*(n/r[i])*(n/r[i])*(f[i]-f[i-1]);
  return cout<<ans<<'\n',0;
}