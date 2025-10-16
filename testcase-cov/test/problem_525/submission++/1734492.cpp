#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5, mod = 998244353;

template<typename T>bool chkmax(const T &_x, const T &_y) {
	return (_x < _y) ? (_x = _y, 1) : 0;
}
template<typename T>bool chkmin(const T &_x, const T &_y) {
	return (_x > _y) ? (_x = _y, 1) : 0;
}

int n, m;
signed main() {

	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	
	int k;
    cin >> k;

    if (k == 1) {
        cout << -1;
        return 0;
    }

    int phi = 1;

    for (int i = 2; i < k; ++i) {
        if (__gcd(i, k) == 1) {
            phi++;
        }
    }

    cout << (2 * phi + 2) << "\n";

    for (int i = 1; i <= phi + 2; ++i) {
        cout << 0 << " ";
    }



    cout << k - 1 << " ";

    for (int i = 1; i <= phi - 1; ++i) {
        std::cout << 0 << " ";
    }

    cout << 1 << "\n";
	return 0;
}