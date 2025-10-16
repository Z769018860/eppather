#include <bits/stdc++.h>
using namespace std;
const int _ = 1e6 + 10;
const int mod = 998244353;
int n, a[_], b[_], ans, tmp = 1;
#define y ((x)&(-(x)))
inline void add(int x) {
    while (x <= n) {
        b[x]++;
        x += y;
    }
}
inline int sum(int x) {
    int ans = 0;
    while (x) {
        ans += b[x];
        (x ^= y);
    }
    return ans;
}
#undef y
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = n; i >= 1; i--) {
        ans = (ans + (long long) tmp * sum(a[i])) % mod;
        tmp = (long long) tmp * (n - i + 1) % mod;
        add(a[i]);
    }
    ans = (ans + 1) % mod;
    cout << ans << endl;
    return 0;
}