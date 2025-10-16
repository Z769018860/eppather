#include <cstdio>
#include <utility>
#include <random>
#include <chrono>

inline constexpr int log2(int x) { return 31 - __builtin_clz(x); }

const int Q = 3e5 + 16;

std::mt19937 rnd(0);

struct node
{
    int val, wt, size;
    node *l, *r;

    node() {}

    node(int val) : val(val), wt(rnd()), size(1), l(nullptr), r(nullptr) {}
    node(node *l, int val, int wt, node *r) : val(val), wt(wt), l(l), r(r),
        size(1 + (l ? l -> size : 0) + (r ? r -> size : 0)) {}
}
t[3 * Q * log2(Q)]; int tcnt;

template <typename... Ts>
node *newnode(Ts... xs)
{
    t[tcnt] = node(xs...);
    return &t[tcnt++];
}

inline int size(node *u) { return u ? u -> size : 0; }

node *merge(node *u, node *v)
{
    if (u == nullptr) return v;
    if (v == nullptr) return u;

    if (u -> wt < v -> wt)
        return newnode(u -> l, u -> val, u -> wt, merge(u -> r, v));
    else
        return newnode(merge(u, v -> l), v -> val, v -> wt, v -> r);
}

std::pair<node*, node*> split(node *u, int k)
{
    if (u == nullptr) return std::make_pair(nullptr, nullptr);

    int lsz = size(u -> l);
    if (k <= lsz)
    {
        auto [v, w] = split(u -> l, k);
        return std::make_pair(v, newnode(w, u -> val, u -> wt, u -> r));
    }
    else
    {
        auto [v, w] = split(u -> r, k - lsz - 1);
        return std::make_pair(newnode(u -> l, u -> val, u -> wt, v), w);
    }
}

int query(node *u, int k)
{
    if (u == nullptr) return -1;

    int lsz = size(u -> l);
    if (k <= lsz) return query(u -> l, k);
    else if (k == lsz + 1) return u -> val;
    else return query(u -> r, k - lsz - 1);
}

node *ver[Q]; int vcnt;

int main()
{
    int q; scanf("%d", &q);
    
    ver[0] = nullptr;
    vcnt = 1;
    while (q--)
    {
        int op, t, k; scanf("%d %d %d", &op, &t, &k);
        if (op == 1)
        {
            int x; scanf("%d", &x);
            auto [u, w] = split(ver[t], k - 1);
            node *v = newnode(x);
            ver[vcnt++] = merge(merge(u, v), w);
        }
        else if (op == 2)
        {
            auto [u, u2] = split(ver[t], k - 1);
            auto [v, w] = split(u2, 1);
            ver[vcnt++] = merge(u, w);
        }
        else if (op == 3)
        {
            printf("%d\n", query(ver[t], k));
        }
    }
}
