#pragma GCC optimize(3,"Ofast","inline")
#include <bits/stdc++.h>
using i64 = long long;

constexpr int N = 1e6 + 10, mod = 998244353;

signed main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    std::cin >> n;
    std::bitset<1000010> dp, f;
    dp[0] = 1;
    while (n -- ) {
        int l, r;
        std::cin >> l >> r;
        f = 0;
        for (int i = l; i <= r; i ++) f |= (dp << i * i); 
        dp = f;
    }
    std::cout << dp.count() << '\n';
    return 0;
}