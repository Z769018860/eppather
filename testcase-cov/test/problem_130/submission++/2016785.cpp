#include <bits/stdc++.h>

using ll = long long;
constexpr int N = 1e6 + 5;
int n, q;
ll a[N];

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
    ll p;
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> p;
        modify(i, p);
    }
    int op, x, y;
    ll t;
    while (q--)
    {
        std::cin >> op;
        if (op == 1)
        {
            std::cin >> x >> t;
            modify(x, t);
        }
        else if (op == 2)
        {
            std::cin >> x >> y;
            ll ans = ask(x, y);
            std::cout << ans << "\n";
        }
    }
    return 0;
}