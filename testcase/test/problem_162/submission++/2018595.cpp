#include <bits/stdc++.h>
using namespace std;
const int mod = 998244352;
int a[100010], b[100010];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int x;
    cin >> x;
    a[0] = 1;
    for (int i = 1; i <= 100000; i++) {
        a[i] = (long long) a[i-1] * x % mod;
    }
    int y = a[100000];
    b[0] = 1;
    for (int i = 1; i <= 100000; i++) {
        b[i] = (long long) b[i-1] * y % mod;
    }
    int n;
    cin >> n;
    while (n--) {
        int t;
        cin >> t;
        cout << (long long) b[t / 100000] * a[t % 100000] % mod;
        if (n) cout << ' ';
    }
    cout << endl;
    return 0;
}