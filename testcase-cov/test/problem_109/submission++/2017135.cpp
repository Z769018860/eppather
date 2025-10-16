#include <bits/stdc++.h>
using namespace std;
const int _ = 4e6 + 10;
int n, m, f[_], ans;
int find(int x) {
    if (x == f[x]) return x;
    return f[x] = find(f[x]);
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        f[i] = i;
    }
    while (m--) {
        int o, u, v;
        cin >> o >> u >> v;
        switch (o) {
            case 0: {
                f[find(u)] = find(v);
                break;
            }
            case 1: {
                ans = ((ans << 1) | (find(u) == find(v))) % 998244353;
            }
        }
    }
    cout << ans << endl;
}