#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
const int N = 1e3 + 10;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    cout << (n * n + 1) / 2 << endl;

    for (int i = 1; i <= n; i += 2) {
        for (int j = 1; j <= n; j += 2) {
            int k = (i / 2 + j / 2) % ((n + 1) / 2) + 1;
            cout << i << ' ' << j << ' ' << k << endl;
        }
    }

    for (int i = 2; i <= n; i += 2) {
        for (int j = 2; j <= n; j += 2) {
            int k = (i / 2 + j / 2) % (n / 2) + (n + 1) / 2 + 1;
            cout << i << ' ' << j << ' ' << k << endl;
        }
    }

    return 0;
}