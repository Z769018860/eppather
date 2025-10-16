#include <bits/stdc++.h>
using namespace std;
long long b[100];
int main() {
    int n;
    cin >> n;
    while (n--) {
        long long x;
        cin >> x;
        for (long long i = 60LL; i >= 0LL; i--) {
            if (!(x & (1LL << i))) continue;
            if (b[i]) {
                (x ^= b[i]);
            } else {
                b[i] = x;
                break;
            }
        }
    }
    long long ans = 0LL;
    for (long long i = 60LL; i >= 0LL; i--) {
        if (b[i]) {
            if (!(ans & (1LL << i))) {
                (ans ^= b[i]);
            }
        }
    }
    cout << ans << endl;
    return 0;
}