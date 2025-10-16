#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int N = 1e6 + 5;
LL c[N], v[N], sum[N], dp[N];
LL flag[N], maxx[N];
LL inf=9223372036854775807;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int n,k;
    cin >> n >> k;
    for(int i = 1; i <= n; i++) cin >> c[i];
    for(int i = 1; i <= n; i++){
        cin >> v[i];
        sum[i] = sum[i - 1] + v[i];
    }
    for(int i=1;i<=k;i++) maxx[i]=-inf;
    for(int i=1;i<=n;i++){
        dp[i]=dp[i-1];
        if(flag[c[i]])
            dp[i]=max(dp[i],maxx[c[i]]+sum[i]);
        maxx[c[i]]=max(maxx[c[i]],dp[i-1]-sum[i-1]);
        flag[c[i]]=1;
        
        
        
    }
    cout<<dp[n];
}