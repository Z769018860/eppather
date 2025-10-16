#include <bits/stdc++.h>

using namespace std;

int main() {
    int T;
    cin >> T;

    while (T--) {
        int n, k;
        cin >> n >> k;

        for (int i = 1, x, y, z; i <= k; i++)
            cin >> x >> y >> z;

        cout << (((n ^ k) & 1) ? "YES" : "NO") << endl;
    }

    return 0;
}
