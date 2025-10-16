#include <bits/stdc++.h>
using namespace std;
const int _ = 1e5 + 10;
int n, k, a[_], b[_];
long double c[_];
inline long double f(long double x) {
    for (int i = 1; i <= n; i++) {
        c[i] = x * b[i] - a[i];
    }
    nth_element(c+1, c+k+1, c+n+1);
    long double ans = 0.0L;
    for (int i = 1; i <= k; i++) {
        ans += c[i];
    }
    return ans;
}
int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    long double L = 0.0L;
    long double R = 1.0L;
    while (R - L > 1e-10L) {
        long double M = ((L + R) / 2.0L);
        if (f(M) > 0) {
            R = M;
        } else {
            L = M;
        }
    }
    cout << fixed << setprecision(10) << ((L + R) / 2.0L) << endl;
}