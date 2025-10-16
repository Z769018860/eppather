#include<bits/stdc++.h>
using namespace std;
int main(){
  ios::sync_with_stdio(false);
  int n,k,w=0; string s; cin>>n>>k>>s;
  vector<int> a(max(n,k)+2),b(k+1);
  for(int i=n-1;~i;i--)
    s[i]=='*'?w++:a[w]++;
  for(int i=0;i<=n;i++)
    if(a[i])a[i+1]+=a[i]-1>>1,a[i]-=(a[i]-1|1)^1;
  for(int i=k-1;~i;n--,i--){
    while(~n&&!a[n])n--;
    if(n>=i)b[i]=1;
    else{
      for(int j=0;j<=n;j++)a[j+1]+=a[j]>>1;
      for(int j=0;j<=i;j++)b[j]=a[j]&=1;
      break;
    }
  }
  k--; while(k&&!b[k])k--;
  for(int i=k;~i;i--)cout<<b[i];
  cout<<endl;
  return 0;
}