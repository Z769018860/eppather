#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false), cin.tie(0);

    int T; cin >> T;
    while(T --) {
        long long n; cin >> n;
        cout << (n >= 4 ? "Yes" : "No") << '\n';
        cout << (n % 2 == 0 && n >= 4 ? "Yes" : "No") << '\n';
    }

    return 0;
}