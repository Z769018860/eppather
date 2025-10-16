#include <bits/stdc++.h>
using namespace std;
const int _ = 1e6 + 10;
int n, q, a, o, l, r, x;
struct bit {
    #define y ((x)&(-(x)))
    long long arr[_];
    inline void add(int x, long long k) {
        while (x <= n) {
            arr[x] += k;
            x += y;
        }
    }
    inline long long sum(int x) {
        long long ans = 0LL;
        while (x) {
            ans += arr[x];
            x -= y;
        }
        return ans;
    }
    #undef y
} s, sx;
inline void add(int l, int r, long long k) {
    s.add(l, k);
    s.add(r+1, -k);
    sx.add(l, l*k);
    sx.add(r+1, -(r+1)*k);
}
inline long long sum(int l, int r) {
    return (r+1) * s.sum(r) - sx.sum(r) - l * s.sum(l-1) + sx.sum(l-1);
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a;
        add(i, i, a);
    }
    while (q--) {
        cin >> o;
        switch (o) {
            case 1: {
                cin >> l >> r >> x;
                add(l, r, x);
                break;
            }
            case 2: {
                cin >> l >> r;
                cout << sum(l, r) << '\n';
                break;
            }
        }
    }
    cout << flush;
    return 0;
}