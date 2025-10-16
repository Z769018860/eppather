#include <bits/stdc++.h>

using i64 = long long;
int n, w[100005];

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> w[i];
    std::sort(w + 1, w + n + 1);
    i64 ans = 0;
    int cur;
    for (cur = 1; cur + 2 <= n;) 
        ans += 1ll * (w[cur + 2] - w[cur]) * (w[cur + 2] - w[cur]), cur += 2;
    for (int nxt = (n - (n & 1)); nxt > 0; nxt = cur - 2) 
        ans += 1ll * (w[cur] - w[nxt]) * (w[cur] - w[nxt]), cur = nxt;
    ans += 1ll * (w[cur] - w[1]) * (w[cur] - w[1]);
    std::cout << ans << '\n';
}