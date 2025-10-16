#include <bits/stdc++.h>
using namespace std;
const int _ = 1e5 + 10;
int n, m, val[_], ls[_], rs[_], fa[_], hi[_];
bool del[_];
int find(int x) {
    if (x == fa[x]) return x;
    return fa[x] = find(fa[x]);
}
int merge(int x, int y) {
    if (!x || !y) return x + y;
    if (val[x] > val[y] || (val[x] == val[y] && x > y)) {
        swap(x, y);
    }
    if (hi[ls[x]] <= hi[rs[x]]) {
        ls[x] = merge(ls[x], y);
    } else {
        rs[x] = merge(rs[x], y);
    }
    hi[x] = min(hi[ls[x]], hi[rs[x]]) + 1;
    return x;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> val[i];
        ls[i] = rs[i] = 0;
        fa[i] = i;
        hi[i] = 1;
    }
    while (m--) {
        int o;
        cin >> o;
        switch (o) {
            case 1: {
                int x, y;
                cin >> x >> y;
                if (!del[x] && !del[y]) {
                    x = find(x);
                    y = find(y);
                    if (x != y) {
                        int tmp = merge(x, y);
                        fa[x] = tmp;
                        fa[y] = tmp;
                    }
                }
                break;
            }
            case 2: {
                int x;
                cin >> x;
                if (del[x]) {
                    cout << -1 << '\n';
                } else {
                    x = find(x);
                    cout << val[x] << '\n';
                    int a = ls[x];
                    int b = rs[x];
                    int tmp = merge(a, b);
                    fa[a] = tmp;
                    fa[b] = tmp;
                    fa[x] = tmp;
                    del[x] = true;
                }
                break;
            }
        }
    }
    cout << flush;
    return 0;
}