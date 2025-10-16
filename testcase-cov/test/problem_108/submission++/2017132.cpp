#include <bits/stdc++.h>
using namespace std;
const int _ = 3e5 + 10;
const int p = 998244353;
const int g = 114514;
inline int qpow(int a, int b) {
    int s = 1;
    while (b) {
        if (b & 1) s = (long long) s * a % p;
        a = (long long) a * a % p;
        (b >>= 1);
    }
    return s;
}
int rev[_];
inline void init(int s) {
    int n = (1 << s);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < s; j++) {
            if (i & (1 << j)) {
                (rev[i] |= (1 << (s - j - 1)));
            }
        }
    }
}
inline void ntt(int* a, int s, bool f) {
    int n = (1 << s);
    for (int i = 0; i < n; i++) {
        if (i < rev[i]) {
            swap(a[i], a[rev[i]]);
        }
    }
    for (int k = 0; k < s; k++) {
        int mul = qpow(g, ((p - 1) >> (k + 1)));
        int step = (1 << (k + 1));
        for (int d = 0; d < n; d += step) {
            int prod = 1;
            for (int i = 0, j = (1 << k); j < step; i++, j++) {
                int tmp = (long long) a[j+d] * prod % p;
                a[j+d] = (a[i+d] + p - tmp) % p;
                a[i+d] = (a[i+d] + tmp) % p;
                prod = (long long) prod * mul % p;
            }
        }
    }
    if (f) {
        reverse(a+1, a+n);
        int tmp = qpow(n, p - 2);
        for (int i = 0; i < n; i++) {
            a[i] = (long long) a[i] * tmp % p;
        }
    }
}
int n, m, a[_], b[_], c[_];
int main() {
    cin >> n >> m;
    for (int i = 0; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i <= m; i++) {
        cin >> b[i];
    }
    int k = __lg(n + m) + 1;
    init(k);
    ntt(a, k, false);
    ntt(b, k, false);
    for (int i = 0; i < (1 << k); i++) {
        c[i] = (long long) a[i] * b[i] % p;
    }
    ntt(c, k, true);
    for (int i = 0; i <= n + m; i++) {
        cout << c[i];
        if (i != n + m) cout << ' ';
    }
    cout << endl;
}