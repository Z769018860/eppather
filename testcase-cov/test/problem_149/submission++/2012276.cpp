#include <bits/stdc++.h>
using namespace std;
int n, m;
int v[100010], c[100010];
double k[100010];
double eps = 1e-8;

double check(double x) {
    for (int i = 1; i <= n; i++) {
        k[i] = x * c[i] - v[i];
    }

    sort(k + 1, k + n + 1);
    double res = 0;

    for (int i = 1; i <= m; i++)
        res += k[i];

    return res;
}

signed main() {
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
        cin >> v[i];

    for (int i = 1; i <= n; i++)
        cin >> c[i];

    double l = 0, r = 1000000000000;
    double res = 0;

    while (r - l > eps) {
        double mid = (l + r) / 2;

        if (check(mid) > 0)
            r = mid;
        else {
            res = mid;
            l = mid;
        }
    }

    printf("%.6lf", res);
    return 0;
}