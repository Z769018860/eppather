#include <bits/stdc++.h>
using namespace std;

int n, np, p, a[60], f[300][13010], num1[70], num2[70], dp[70][13010];

inline void add1(int &x, int y) {
    x += y;

    if (x >= p)
        x -= p;
}

inline void add2(int &x, int y) {
    x += y;

    if (x < 0)
        x += p;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> np;
    p = np;

    for (int i = 0; i <= n; i++)
        cin >> a[i];

    f[0][0] = 1;

    for (int i = 0; i < p; i++) {
        for (int j = 0; j <= n * p; j++)
            if (f[i][j]) {
                for (int k = 0; k <= n && j + k <= n * p; k++) {
                    f[i + 1][j + k] += f[i][j] * a[k];
                }
            }

        for (int j = 0; j <= n * p; j++)
            f[i + 1][j] %= p;
    }

    int t;
    cin >> t;

    while (t--) {
        long long m, k;
        cin >> m >> k;
        int len1 = 60, len2 = 60;

        for (int i = 0; i <= 60; i++) {
            num1[i] = m % p;
            m /= p;

            if (m == 0) {
                len1 = min(len1, i);
            }
        }

        for (int i = 0; i <= 60; i++) {
            num2[i] = k % p;
            k /= p;

            if (k == 0) {
                len2 = min(len2, i);
            }
        }

        int len = max(len1, len2);

        for (int i = 0; i <= len + 1; i++) {
            for (int j = 0; j <= n; j++)
                dp[i][j] = 0;
        }

        dp[0][0] = 1;

        for (int i = 0; i <= len; i++) {
            for (int j = 0; j <= n; j++)
                if (dp[i][j]) {
                    for (int k = 0; k <= n; k++) {
                        int cur = k * p + num2[i] - j;

                        if (cur >= 0 && cur <= n * p) {
                            dp[i + 1][k] += dp[i][j] * f[num1[i]][cur];
                        }
                    }
                }

            for (int k = 0; k <= n; k++)
                dp[i + 1][k] %= p;
        }

        cout << dp[len + 1][0] % np << '\n';
    }

    return 0;
}