#include <iostream>
#include <vector>
#include <numeric>
int ans = 1;
int solve(int a, int p, int k) {
    std::vector<int> power(k + 1);
    power[0] = 1;
    for (int i = 1; i <= k; ++i)
        power[i] = power[i - 1] * p;
    int res = 1;
    for (int i = 0; 1ll * i * a < k; ++i) {
        int phi = power[k - i * a] / p * (p - 1);
        int x = phi / std::gcd(phi, a);
        if (p == 2 && a % 2 == 0 && x % 2 == 0)
            x /= 2;
        res += x;
    }
    return res;
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int a, q, n;
    std::cin >> a >> q >> n;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            int k = 0;
            while (n % i == 0) {
                n /= i;
                ++k;
            }
            ans *= solve(a, i, k);
        }
    }
    if (n > 1)
        ans *= solve(a, n, 1);
    std::cout << ans << "\n";
    return 0;
}