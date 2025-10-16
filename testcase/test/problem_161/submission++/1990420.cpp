#include<bits/stdc++.h>
#define N 5000010
typedef long long LL;
using namespace std;
LL p=1e9+7;
LL d=998244353;
LL a[N];
LL s[N];
LL sv[N];
LL inv[N];
LL b[N];
LL qmi(LL m, LL k)
{
    LL res = 1%p, t = m;
    while(k)
    {
        if(k&1) res = res * t % p;
        t = t * t % p;
        k >>= 1;
    }
    return res;
}
int main(){
    int n;
    scanf("%d",&n);
    s[0]=1;
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&a[i]);
        s[i]=a[i]*s[i-1]%p;
    }
    sv[n]= qmi(s[n],p-2);
    for(int i=n-1;i>=1;i--)
    {
        sv[i]=sv[i+1]*a[i+1]%p;
    }
    for(int i=1;i<=n;i++)
    {
       inv[i] = (sv[i]*s[i-1]+p)%p;
    }
    b[0]=1;
    for(int i=1;i<=n;i++)
    {
        b[i]=b[i-1]*d%p;
    }
    LL res=0;
    for(int i=1;i<=n;i++)
    {
        res=res+(inv[i]*b[n-i])%p;
        res=res%p;
    }
    printf("%lld\n",res);
    return 0;
}

