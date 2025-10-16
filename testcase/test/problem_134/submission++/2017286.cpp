#include <bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr int N = 5000;
ll t[N][N];
int n, m;
int a, b, c, d, op;
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

void update(int a, int b, int c, int d, ll k)
{
    modify(a, b, k);
    modify(a, d + 1, -k);
    modify(c + 1, b, -k);
    modify(c + 1, d + 1, k);
}

ll query(int x, int y)
{
    ll res = 0;
    for (int i = x; i; i -= lowbit(i))
        for (int j = y; j; j -= lowbit(j))
            res += t[i][j];
    return res;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m;
    while (cin >> op)
    {
        if (op == 1)
        {
            cin >> a >> b >> c >> d >> k;
            update(a, b, c, d, k);
        }
        else if (op == 2)
        {
            cin >> a >> b;
            ll ans = query(a, b);
            cout << ans << "\n";
        }
    }
    return 0;
}