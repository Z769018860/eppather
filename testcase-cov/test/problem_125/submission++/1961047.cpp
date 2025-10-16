#include <bits/stdc++.h>
using namespace std;

#define int long long
const int P = 998244353;

signed main() {
    int n, res = 0;
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++) {
        int t = n / i;
        res = (res + t * (2 * i * i + 3 * i + 5)) % P;
    }
    return !printf("%lld\n", res);
}