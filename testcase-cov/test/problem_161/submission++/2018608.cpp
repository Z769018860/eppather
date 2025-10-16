#include <bits/stdc++.h>
using namespace std;
const int _ = 5e6 + 10;
const int mod = 1e9 + 7;
inline int qpow(int a, int b) {
    int s = 1;
    while (b) {
        if (b & 1) s = (long long) s * a % mod;
        a = (long long) a * a % mod;
        (b >>= 1);
    }
    return s;
}
int n, a[_], f[_], g[_], b[_];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    f[0] = 1;
    for (int i = 1; i <= n; i++) {
        f[i] = (long long) f[i-1] * a[i] % mod;
    }
    g[n] = qpow(f[n], mod - 2);
    for (int i = n-1; i >= 0; i--) {
        g[i] = (long long) g[i+1] * a[i+1] % mod;
    }
    for (int i = 1; i <= n; i++) {
        b[i] = (long long) f[i-1] * g[i] % mod;
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = (998244353LL * ans + b[i]) % mod;
    }
    cout << ans << endl;
    return 0;
}