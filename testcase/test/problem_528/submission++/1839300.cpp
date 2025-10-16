#include<bits/stdc++.h>
#define int long long
const int mod=998244353;
using namespace std;
int n,m,miu[4000000],prim[4000000],N;
bool b[4000000];
signed main(){
  miu[1]=1;
  int MAX=sqrt(1e13);
  for(int i=2;i<=MAX;++i){
    if(!b[i])prim[++N]=i,miu[i]=-1;
    for(int j=1;j<=N&&prim[j]*i<=MAX;++j){
      b[prim[j]*i]=1;
      if(i%prim[j]==0)break;
      miu[prim[j]*i]=-miu[i];
    }
  }
  for(int i=2;i<=MAX;++i)miu[i]+=miu[i-1];
  scanf("%lld%lld",&n,&m);
  if(n>m)swap(n,m);
  int i=1,j=0;
  MAX=sqrt(n);
  int ans=0;
  for(;i<=MAX;){
    j=min(n/(n/(i*i)),(m/(m/(i*i))));
    j=sqrt(j);
    ans=(ans+1ll*((n/(i*i))%mod)*((m/(i*i))%mod)%mod*(miu[j]-miu[i-1])%mod)%mod;
    i=j+1;
  }
  cout<<(ans+mod)%mod;
}