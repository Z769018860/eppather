#include <bits/stdc++.h>
using namespace std;
const int _ = 1145141;
const int p = 1e9 + 9;
long long n, f[_], g[_], h[_];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (long long i = 0; i < (1 << n); i++) {
        cin >> f[i];
    }
    for (long long i = 0; i < (1 << n); i++) {
        cin >> g[i];
    }
    for (long long i = 0; i < (1 << n); i++) {
        __int128 tmp = 0;
        for (long long j = i; j; j = ((j - 1) & i)) {
            tmp += f[j] * g[i^j];
        }
        tmp += f[0] * g[i];
        h[i] = tmp % p;
    }
    for (long long i = 0; i < (1 << n); i++) {
        cout << h[i];
        if (i != ((1 << n) - 1)) {
            cout << ' ';
        }
    }
    cout << endl;
    return 0;
}