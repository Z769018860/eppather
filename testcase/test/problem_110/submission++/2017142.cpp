#include <bits/stdc++.h>
using namespace std;
int n, p, a[3000010];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> p;
    cout << 1;
    a[1] = 1;
    for (int i = 2; i <= n; i++) {
        a[i] = p - (long long) (p / i) * a[p % i] % p;
        cout << '\n' << a[i];
    }
    cout << endl;
    return 0;
}