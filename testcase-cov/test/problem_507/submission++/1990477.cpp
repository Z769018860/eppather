#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int maxn=1e6+100;
ll n,k,sum[maxn],v[maxn];
ll dp[maxn],head[maxn],d;
ll last[maxn];
int main()
{
    scanf("%lld%lld",&n,&k);
    for(int i=1; i<=n; i++)
    {
        scanf("%lld",&v[i]);
        head[i]=last[v[i]];
        last[v[i]]=i;
    }
    for(int i=1; i<=n; i++)
    {
        scanf("%lld",&d);
        sum[i]=sum[i-1]+d;
    }
    for(int i=1; i<=n; i++)
    {
        dp[i]=dp[i-1];
        if(head[i])
            dp[i]=max(dp[i],max(dp[head[i]-1]+sum[i]-sum[head[i]-1],dp[head[i]]+sum[i]-sum[head[i]]));
    }
    printf("%lld\n",dp[n]);
    return 0;
}