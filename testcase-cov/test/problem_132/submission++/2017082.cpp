#include <bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr int N = 1e6 + 5;
int n, q;
ll a[N], b[N];
ll temp[N];
int x, y, op;
ll z;

int lowbit(int x)
{
    return x & (-x);
}

void modify(int p, ll k)
{
    for (int i = p; i <= n; i += lowbit(i))
    {
        a[i] += k;
        b[i] += k * p;
    }
}

ll query(int p)
{
    ll res = 0;
    for (int i = p; i; i -= lowbit(i))
        res += a[i] * (p + 1) - b[i];
    return res;
}

ll ask(int l, int r)
{
    return query(r) - query(l - 1);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) cin >> temp[i];
    for (int i = 1; i <= n; ++i) modify(i, temp[i] - temp[i - 1]);
    while (q--)
    {
        cin >> op;
        if (op == 1)
        {
            cin >> x >> y >> z;
            modify(x, z);
            modify(y + 1, -z);
        }
        else if (op == 2)
        {
            cin >> x >> y;
            ll ans = ask(x, y);
            cout << ans << "\n";
        }
    }
    return 0;
}