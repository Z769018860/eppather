#include<bits/stdc++.h>
using namespace std;
int T,n,m,k;
typedef long long ll;
ll ans;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&n,&m,&k);
        ans = (ll)(m + 1) / 2 * (m / 2) * n + (ll)(n + 1) / 2 * (n / 2) * m;
        printf("%lld\n",ans);
    }
}