#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int k;
    std::cin >> k;

    int n = k + 1;
    std::vector<int> a(n);
    a[0] = n - 1;
    a[1] = 0;
    for (int i = 2; i < n; ++i) {
        a[i] = a[i - 2] + (i % 2 == 0 ? -1 : 1);
    }

    std::cout << n << "\n";
    for (int i = 0; i < n; ++i) {
        std::cout << a[n - 1 - i] + 1 << " \n"[i == n - 1];
    }

    return 0;
}
