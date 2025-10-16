#include <bits/stdc++.h>
using namespace std;
const int _ = 2333;
int n, m;
struct bit {
    long long arr[_][_];
    inline void add(int x, int y, long long k) {
        for (int i = x; i <= n; i += ((i) & (-i))) {
            for (int j = y; j <= m; j += ((j) & (-j))) {
                arr[i][j] += k;
            }
        }
    }
    inline long long sum(int x, int y) {
        long long ans = 0LL;
        for (int i = x; i; i -= ((i) & (-i))) {
            for (int j = y; j; j -= ((j) & (-j))) {
                ans += arr[i][j];
            }
        }
        return ans;
    }
} s, sx, sy, sxy;
inline void add(int u, int d, int l, int r, long long k) {
    s.add(u, l, k);
    sx.add(u, l, u * k);
    sy.add(u, l, l * k);
    sxy.add(u, l, u * l * k);
    s.add(u, r+1, -k);
    sx.add(u, r+1, -u * k);
    sy.add(u, r+1, -(r+1) * k);
    sxy.add(u, r+1, -u * (r+1) * k);
    s.add(d+1, l, -k);
    sx.add(d+1, l, -(d+1) * k);
    sy.add(d+1, l, -l * k);
    sxy.add(d+1, l, -(d+1) * l * k);
    s.add(d+1, r+1, k);
    sx.add(d+1, r+1, (d+1) * k);
    sy.add(d+1, r+1, (r+1) * k);
    sxy.add(d+1, r+1, (d+1) * (r+1) * k);
}
inline long long sum(int u, int d, int l, int r) {
    return (d+1) * (r+1) * s.sum(d, r) - (r+1) * sx.sum(d, r) - (d+1) * sy.sum(d, r) + sxy.sum(d, r) - (d+1) * l * s.sum(d, l-1) + l * sx.sum(d, l-1) + (d+1) * sy.sum(d, l-1) - sxy.sum(d, l-1) - u * (r+1) * s.sum(u-1, r) + (r+1) * sx.sum(u-1, r) + u * sy.sum(u-1, r) - sxy.sum(u-1, r) + u * l * s.sum(u-1, l-1) - l * sx.sum(u-1, l-1) - u * sy.sum(u-1, l-1) + sxy.sum(u-1, l-1);
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    int o;
    while (cin >> o) {
        switch (o) {
            case 1: {
                int a, b, c, d, x;
                cin >> a >> b >> c >> d >> x;
                add(a, c, b, d, x);
                break;
            }
            case 2: {
                int a, b, c, d;
                cin >> a >> b >> c >> d;
                cout << sum(a, c, b, d) << '\n';
                break;
            }
        }
    }
    cout << flush;
}