#include <bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr int N = 4500;
ll t[N][N];
int n, m;
int op, a, b, c, d;
ll k;

int lowbit(int x)
{
    return x & (-x);
}

void modify(int x, int y, ll k)
{
    for (int i = x; i <= n; i += lowbit(i))
        for (int j = y; j <= m; j += lowbit(j))
            t[i][j] += k;
}

ll query(int x, int y)
{
    ll res = 0;
    for (int i = x; i; i -= lowbit(i))
        for (int j = y; j; j -= lowbit(j))
            res += t[i][j];
    return res;
}

ll ask(int a, int b, int c, int d)
{
    return query(c, d) - query(c, b - 1) - query(a - 1, d) + query(a - 1, b - 1);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m;
    while (cin >> op)
    {
        if (op == 1)
        {
            cin >> a >> b >> k;
            modify(a, b, k);
        }
        else if (op == 2)
        {
            cin >> a >> b >> c >> d;
            ll ans = ask(a, b, c, d);
            cout << ans << "\n";
        }
    }
    return 0;
}