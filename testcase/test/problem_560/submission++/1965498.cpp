#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, k;
    std::cin >> n >> k;

    std::string s;
    std::cin >> s;

    std::vector<int> a;
    int cur = 0;
    for (int i = n - 1; i >= 0; --i) {
        if (s[i] == '+') {
            cur += 1;
        }
        if (s[i] == '*') {
            int x = (cur - 1) / 2;
            a.push_back(cur - 2 * x);
            cur = x;
        }
    }
    while (cur) {
        int x = (cur - 1) / 2;
        a.push_back(cur - 2 * x);
        cur = x;
    }

    a.push_back(0);
    const int m = int(a.size());

    int r = m - 1, cnt = 0;
    while (r >= 0) {
        while (r >= 0 && a[r] == 0) {
            --r;
        }
        if (r < 0) {
            break;
        }
        if (cnt + r + 2 <= k) {
            for (int i = 0; i <= r; ++i) {
                a[i + 1] += a[i] / 2;
                a[i] %= 2;
            }
            if (cnt) {
                while (cnt + r + 2 < k) {
                    std::cout << 0;
                    ++cnt;
                }
            }
            for (int i = r + 1; i >= 0; --i) {
                if (a[i] || cnt) {
                    std::cout << a[i];
                    ++cnt;
                }
            }
            break;
        }
        std::cout << std::min(a[r], 1);
        ++cnt;
        --r;
    }
    if (cnt == 0) {
        std::cout << 0;
    }
    std::cout << "\n";

    return 0;
}
