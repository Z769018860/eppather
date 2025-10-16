#include<bits/stdc++.h>
using namespace std;
int n,k,bn,num;
unsigned int r[89449],g[89449],s[89449],phi[89449],phi1[89449],ans;
unsigned int qpow(unsigned int a,int b,unsigned int ans=1){for(;b;b>>=1)b&1&&(ans*=a),a*=a;return ans;}
int id(int x){return x<=bn?x:num-n/x+1;}
int main(){
  cin>>n>>k,bn=sqrt(n);
  for(int l=1;l<=n;l=r[num]+1)r[++num]=n/(n/l),g[num]=r[num]-1,phi1[num]=(r[num]+2)*(r[num]-1)/2;
  for(int j=2;j<=bn;j++)if(g[j]!=g[j-1])for(int i=num;r[i]>=j*j;i--)g[i]-=g[id(r[i]/j)]-g[j-1],phi1[i]-=j*(phi1[id(r[i]/j)]-phi1[j-1]);
  for(int i=1;i<=num;i++)phi[i]=phi1[i]-=g[i];
  for(int j=bn;j>=2;j--){
    if(g[j]==g[j-1])continue;
    unsigned int pk=qpow(j,k);
    for(int i=num;r[i]>=j*j;i--){
      long long p=j;
      for(int e=1;p*j<=r[i];e++,p*=j)s[i]+=s[id(r[i]/p)]+pk*(g[id(r[i]/p)]-g[j-1]),phi[i]+=(p-p/j)*(phi[id(r[i]/p)]-phi1[j])+(p*j-p);
    }
  }
  for(int i=1;i<=num;i++)ans+=(2*phi[id(n/r[i])]+1)*(s[i]+g[i]-s[i-1]-g[i-1]);
  return cout<<ans<<'\n',0;
}