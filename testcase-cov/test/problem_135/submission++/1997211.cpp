#include <bits/stdc++.h>
using namespace std;
int n, m;
const int N = 2049;
int lowbit(int x) {
    return x & (-x);
}
#define ll long long
ll t1[N][N], t2[N][N], t3[N][N], t4[N][N];
void add(ll x, ll y, ll z) {
    for (int X = x; X <= n; X += lowbit(X))
        for (int Y = y; Y <= m; Y += lowbit(Y)) {
            t1[X][Y] += z;
            t2[X][Y] += z * x;
            t3[X][Y] += z * y;
            t4[X][Y] += z * x * y;
        }
}

void range_add(ll xa, ll ya, ll xb, ll yb, ll z) {
    add(xa, ya, z);
    add(xa, yb + 1, -z);
    add(xb + 1, ya, -z);
    add(xb + 1, yb + 1, z);
}

ll ask(ll x, ll y) {
    ll res = 0;

    for (int i = x; i; i -= lowbit(i))
        for (int j = y; j; j -= lowbit(j))
            res += (x + 1) * (y + 1) * t1[i][j] - (y + 1) * t2[i][j] -
                   (x + 1) * t3[i][j] + t4[i][j];

    return res;
}

ll range_ask(ll xa, ll ya, ll xb, ll yb) {
    return ask(xb, yb) - ask(xb, ya - 1) - ask(xa - 1, yb) + ask(xa - 1, ya - 1);
}
signed main() {
    ios::sync_with_stdio(false);
    char c;
    cin >> n >> m;
    int aa, bb, cc, dd, val;

    while (cin >> c) {
        cin >> aa >> bb >> cc >> dd;

        if (c == '1') {
            cin >> val;
            range_add(aa, bb, cc, dd, val);
        }

        if (c == '2') {
            cout << range_ask(aa, bb, cc, dd) << endl;
        }
    }

    return 0;
}