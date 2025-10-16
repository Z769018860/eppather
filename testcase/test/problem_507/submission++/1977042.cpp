#include <bits/stdc++.h>
#ifdef LOCAL
#include "debug.h"
#endif
using namespace std;
typedef long long ll;
const ll N = 1e6 + 10, mn = -1e18;
ll n, k, ans, c[N], v[N], mx[N], s[N], dp[N];
inline void optimizeIO(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
}
int main(int argc, char const *argv[]) {
    optimizeIO(), cin >> n >> k;
    for (int i = 1; i <= k; i++) mx[i] = mn;
    for (int i = 1; i <= n; i++) cin >> c[i];
    for (int i = 1; i <= n; i++) {
        cin >> v[i], s[i] = s[i - 1] + v[i];
    }
    ll maxn = 0;
    for (int i = 1; i <= n; i++) {
        dp[i]    = max(dp[i], mx[c[i]] + s[i]);
        mx[c[i]] = max(mx[c[i]], maxn - s[i - 1]);
        maxn = max(maxn, dp[i]), ans = max(ans, dp[i]);
    }
    cout << ans << endl;
    return 0;
}
