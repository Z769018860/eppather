#include <bits/stdc++.h>
#include <ext/rope>
using namespace std;
using namespace __gnu_cxx;
const int N = 3e5 + 5;
rope<int>r[N];
int m, type, k, t, x, cnt;
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    r[0].push_back(0);
    cin >> m;

    while (m--) {
        cin >> type >> t >> k;

        if (type == 1) {
            r[++cnt] = r[t];
            cin >> x;
            r[cnt].insert(k, x);
        } else if (type == 2) {
            r[++cnt] = r[t];
            r[cnt].erase(k, 1);
        } else
            cout << r[t].at(k) << '\n';
    }
}