#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=1e6+50;

int n,k,a[Maxn+5],ans[Maxn+5]; char s[Maxn+5];

int main()
{
    

    scanf("%d%d%s",&n,&k,s+1);
    for(int i=n,j=0;i>=1;--i) {if(s[i]=='*') j++; else a[j]++;}
    n+=30; For(i,0,n) {int k=(a[i]-1)/2; a[i]-=k*2,a[i+1]+=k;}
    int p=k-1;
    while(n>=0)
    {
        while(n>=0 && !a[n]) n--;
        if(n<0) break;
        if(n>=p) ans[p--]=1;
        else
        {
            For(i,0,p-1) if(a[i]>=2) a[i]-=2,a[i+1]++;
            For(i,0,p) ans[i]=a[i];
            break;
        }
        n--;
    } p=k-1; while(p>=0 && !ans[p]) p--;
    if(p<0) puts("0");
    else {Rof(i,p,0) putchar(ans[i]+'0'); putchar('\n');}
    return 0;
}