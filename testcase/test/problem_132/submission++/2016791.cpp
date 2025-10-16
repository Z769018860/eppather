#include <bits/stdc++.h>

#define el "\n"
#define ls p*2
#define rs p*2+1

using ll = long long;

constexpr int N = 1e6 + 5;
struct segment
{
    int l, r;
    ll val, tag;
};
segment t[N * 4];
ll a[N];
int n, q, op;
int x, y;
ll z;

void pushup(int p)
{
    t[p].val = t[ls].val + t[rs].val;
}

void pushdown(int p)
{
    t[ls].val += t[p].tag * (t[ls].r - t[ls].l + 1);
    t[rs].val += t[p].tag * (t[rs].r - t[rs].l + 1);
    t[ls].tag += t[p].tag;
    t[rs].tag += t[p].tag;
    t[p].tag = 0;
}

void build(int p, int l, int r)
{
    t[p].l = l;
    t[p].r = r;
    if (l == r)
    {
        t[p].val = a[l];
        return;
    }
    int mid = (l + r) / 2;
    build(ls, l, mid);
    build(rs, mid + 1, r);
    pushup(p);
}

void modify(int p, int l, int r, ll z)
{
    if (l <= t[p].l && r >= t[p].r)
    {
        t[p].val += z * (t[p].r - t[p].l + 1);
        t[p].tag += z;
        return;
    }
    pushdown(p);
    int mid = (t[p].r + t[p].l) / 2;
    if (l <= mid) modify(ls, l, r, z);
    if (r > mid) modify(rs, l, r, z);
    pushup(p);
}

ll query(int p, int l, int r)
{
    if (l <= t[p].l && r >= t[p].r) return t[p].val;
    pushdown(p);
    int mid = (t[p].l + t[p].r) / 2;
    ll ans = 0;
    if (l <= mid) ans += query(ls, l, r);
    if (r > mid) ans += query(rs, l, r);
    return ans;
}

int main()
{
    std::ios::sync_with_stdio(false); std::cin.tie(nullptr);
    std::cin >> n >> q;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    build(1, 1, n);
    while (q--)
    {
        std::cin >> op;
        if (op == 1)
        {
            std::cin >> x >> y >> z;
            modify(1, x, y, z);
        }
        else if (op == 2)
        {
            std::cin >> x >> y;
            ll ans = query(1, x, y);
            std::cout << ans << el;
        }
    }
    return 0;
}