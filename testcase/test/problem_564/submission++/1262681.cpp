#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    int half = n / 2;
    vector<int> a(half);
    iota(a.begin(), a.end(), 0);
    if (n & 1) {
        vector<int> b(n - half);
        iota(b.begin(), b.end(), 0);
        cout << (n * n + 1) / 2 << "\n";
        for (int i = 0; i < half; i++) {
            for (int j = 0; j < half; j++) {
                cout << i + 1 << " " << j + 1 << " " << a[j] + 1 << "\n";
                a[j] = (a[j] + 1) % half;
            }
        }
        for (int i = 0; i < n - half; i++) {
            for (int j = 0; j < n - half; j++) {
                cout << i + n - half << " " << j + n - half << " " << b[j] + n - half << "\n";
                b[j] = (b[j] + 1) % (n - half);
            }
        }
    } else {
        cout << n * n / 2 << "\n";
        for (int i = 0; i < half; i++) {
            for (int j = 0; j < half; j++) {
                cout << i + 1 << " " << j + 1 << " " << a[j] + 1 << "\n";
                cout << i + half + 1 << " " << j + half + 1 << " " << a[j] + half + 1 << "\n";
                a[j] = (a[j] + 1) % half;
            }
        }
    }
    return 0;
}