#include<bits/stdc++.h>
using namespace std;
#define li long long
li a[1001000];
int main(){
    li n=0,i,j,k,kk;
    scanf("%lld",&k);
    a[++n]=1;
    while(k%2==0)a[++n]=2,k/=2;
    a[++n]=3;
    for(li i=(1ll<<60)-1,w=0;i>1;i/=2)
      while(k%i==0&&i!=63){j=i;while(j)a[++n]=w,j/=2;w^=1;k/=i;}
    if(k>1){puts("qnq");return 0;}
    printf("%d\n",n);
    for(i=1;i<=n;i++)printf("%d ",a[i]);
    return 0;
}