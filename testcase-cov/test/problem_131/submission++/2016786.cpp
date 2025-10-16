#include <bits/stdc++.h>

using ll = long long;
constexpr int N = 1e6 + 5;
int n, q;
ll a[N];
ll temp[N];

int lowbit(int x)
{
    return x & (-x);
}

void modify(int p, ll x)
{
    for (int i = p; i <= n; i += lowbit(i)) a[i] += x;
}

ll query(int p)
{
    ll ret = 0;
    for (int i = p; i; i -= lowbit(i)) ret += a[i];
    return ret;
}

ll ask(int l, int r)
{
    return query(r) - query(l - 1);
}

int main()
{
    std::ios::sync_with_stdio(false); std::cin.tie(nullptr);
    std::cin >> n >> q;
    for (int i = 1; i <= n; ++i) std::cin >> temp[i];
    for (int i = 1; i <= n; ++i)
    {
        ll ad = temp[i] - temp[i - 1];
        modify(i, ad);
    }
    int op, x, y;
    ll t;
    while (q--)
    {
        std::cin >> op;
        if (op == 1)
        {
            std::cin >> x >> y >> t;
            modify(x, t);
            modify(y + 1, -t);
        }
        else if (op == 2)
        {
            std::cin >> x;
            ll ans = query(x);
            std::cout << ans << "\n";
        }
    }
    return 0;
}