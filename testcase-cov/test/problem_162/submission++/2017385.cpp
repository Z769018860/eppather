#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=998244352;
const int S=31596;
ll a[32000],b[32000];
int main()
{
    ll x; int n; scanf("%lld%d",&x,&n);
    a[0]=1,b[0]=1;
    for(int i=1;i<=S;i++)
        a[i]=a[i-1]*x%mod;
    for(int i=1;i<=S;i++)
        b[i]=b[i-1]*a[S]%mod;
    for(int i=1;i<=n;i++){
        ll aa; scanf("%lld",&aa);
        printf("%lld ",a[aa%S]*b[aa/S]%mod);
    }
}