#include <bits/stdc++.h>

#define int long long 

using namespace std;

const int N=1e3+7;

const int mod=1e9+7;

int a[N][N],b[N][N];

int c[N][N],m,n,p;

signed main(void) 

{

scanf("%lld%lld%lld",&n,&p,&m); 

for(int i=1;i<=n;i++)

for(int j=1;j<=p;j++)

  scanf("%lld",a[i]+j);
for(int i=1;i<=p;i++)

for(int j=1;j<=m;j++)

  scanf("%lld",b[i]+j);
for(int i=1;i<=n;i++)

for(int j=1;j<=m;j++)

  for(int k=1;k<=p;k++)	{

    c[i][j]+=a[i][k]*b[k][j]%mod;  

    c[i][j]+=mod;c[i][j]%=mod;  

  }
for(int i=1;i<=n;i++) {

for(int j=1;j<=m;j++)

  printf("%lld ",c[i][j]);   

putchar(10);    
}

return 0;

}