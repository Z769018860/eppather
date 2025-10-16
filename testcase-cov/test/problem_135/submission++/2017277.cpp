#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define el "\n"

constexpr int N = 5000;
ll t1[N][N], t2[N][N], t3[N][N], t4[N][N];
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
        {
            t1[i][j] += k;
            t2[i][j] += k * x;
            t3[i][j] += k * y;
            t4[i][j] += k * x * y;
        }
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
            res += (x + 1) * (y + 1) * t1[i][j] - (y + 1) * t2[i][j] - (x + 1) * t3[i][j] + t4[i][j];
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
            cin >> a >> b >> c >> d >> k;
            update(a, b, c, d, k);
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