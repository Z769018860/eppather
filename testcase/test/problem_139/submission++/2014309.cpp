#include <bits/stdc++.h>

using LL = long long;
using ull = unsigned long long;
using Pair = std::pair<int, int>;

struct Seg {
    std::vector<LL> sum, tag;
    std::vector<int> len;
    int n;

    Seg(int n) : n(n), sum(n << 2), tag(n << 2), len(n << 2) {}

    void pushup(int x) {
        sum[x] = sum[x << 1] + sum[x << 1 | 1];
    }

    void change(int x, LL v) {
        sum[x] += v * len[x];
        tag[x] += v;
    }

    void pushdown(int x) {
        if (tag[x]) {
            change(x << 1, tag[x]);
            change(x << 1 | 1, tag[x]);
            tag[x] = 0;
        }
    }

    void modify(int x, int l, int r, const int &L, const int &R, const LL &v) {
        if (L <= l && r <= R) {
            change(x, v);
            return;
        }
        pushdown(x);
        int mid = (l + r) >> 1;
        if (L <= mid)modify(x << 1, l, mid, L, R, v);
        if (R > mid)modify(x << 1 | 1, mid + 1, r, L, R, v);
        pushup(x);
    }

    LL query(int x, int l, int r, const int &L, const int &R) {
        if (L <= l && r <= R)return sum[x];
        pushdown(x);
        int mid = (l + r) >> 1;
        LL res = 0;
        if (L <= mid)res = query(x << 1, l, mid, L, R);
        if (R > mid)res += query(x << 1 | 1, mid + 1, r, L, R);
        return res;
    }

    void build(int x, int l, int r, const auto &a, const auto &rnk) {
        len[x] = r - l + 1;
        if (l == r) {
            sum[x] = a[rnk[l]];
            return;
        }
        int mid = (l + r) >> 1;
        build(x << 1, l, mid, a, rnk);
        build(x << 1 | 1, mid + 1, r, a, rnk);
        pushup(x);
    }
};

struct Tree {
    int n;
    std::vector<std::vector<int>> G;
    std::vector<int> dep, fa, sz, son, dfn, low, top, rnk, a;
    Seg tr;
    int idx, rt;

    Tree(int n) : n(n), tr(n), a(n + 1), G(n + 1), dep(n + 1), fa(n + 1), sz(n + 1), son(n + 1), dfn(n + 1), low(n + 1),
                  top(n + 1), rnk(n + 1), idx(0), rt(1) {
        for (int i = 1; i <= n; i++) {
            std::cin >> a[i];
        }
        for (int i = 2; i <= n; i++) {
            int f;
            std::cin >> f;
            G[f].push_back(i);
            fa[i] = f;
        }
        dfs_son(1, 0);
        dfs_top(1, 1);
        tr.build(1, 1, n, a, rnk);
    }

    void dfs_son(int x, int fax) {
        sz[x] = 1;
        for (const auto &tox: G[x]) {
            if (tox == fax)continue;
            dep[tox] = dep[x] + 1;
            dfs_son(tox, x);
            sz[x] += sz[tox];
            if (sz[tox] > sz[son[x]])son[x] = tox;
        }
    }

    void dfs_top(int x, int topx) {
        top[x] = topx;
        dfn[x] = ++idx;
        rnk[idx] = x;
        if (son[x])dfs_top(son[x], topx);
        for (const auto &tox: G[x]) {
            if (tox == fa[x] || tox == son[x])continue;
            dfs_top(tox, tox);
        }
        low[x] = idx;
    }

    void modify_chain(int x, int y, LL v) {
        while (top[x] != top[y]) {
            if (dep[top[x]] < dep[top[y]])std::swap(x, y);
            tr.modify(1, 1, n, dfn[top[x]], dfn[x], v);
            x = fa[top[x]];
        }
        if (dep[x] > dep[y])std::swap(x, y);
        tr.modify(1, 1, n, dfn[x], dfn[y], v);
    }

    LL query_chain(int x, int y) {
        LL res = 0;
        while (top[x] != top[y]) {
            if (dep[top[x]] < dep[top[y]])std::swap(x, y);
            res += tr.query(1, 1, n, dfn[top[x]], dfn[x]);
            x = fa[top[x]];
        }
        if (dep[x] > dep[y])std::swap(x, y);
        res += tr.query(1, 1, n, dfn[x], dfn[y]);
        return res;
    }

    void change_rt(int x) {
        rt = x;
    }

    void modify_subtree(int x, LL v) {
        if (x == rt) {
            tr.modify(1, 1, n, 1, n, v);
            return;
        }
        if (dfn[rt] >= dfn[son[x]] && dfn[rt] <= low[son[x]]) {
            tr.modify(1, 1, n, 1, n, v);
            tr.modify(1, 1, n, dfn[son[x]], low[son[x]], -v);
            return;
        }
        if (dfn[rt] >= dfn[x] && dfn[rt] <= low[x]) {
            int y = top[rt];
            while (fa[y] != x)y = top[fa[y]];
            tr.modify(1, 1, n, 1, n, v);
            tr.modify(1, 1, n, dfn[y], low[y], -v);
            return;
        }
        tr.modify(1, 1, n, dfn[x], low[x], v);
    }

    LL query_subtree(int x) {
        if (x == rt)return tr.query(1, 1, n, 1, n);
        if (dfn[rt] >= dfn[son[x]] && dfn[rt] <= low[son[x]]) {
            return tr.query(1, 1, n, 1, n) - tr.query(1, 1, n, dfn[son[x]], low[son[x]]);
        }
        if (dfn[rt] >= dfn[x] && dfn[rt] <= low[x]) {
            int y = top[rt];
            while (fa[y] != x)y = top[fa[y]];
            return tr.query(1, 1, n, 1, n) - tr.query(1, 1, n, dfn[y], low[y]);
        }
        return tr.query(1, 1, n, dfn[x], low[x]);
    }
};

void solve(const int &Case) {
    int n;
    std::cin >> n;
    Tree tree(n);
    int q;
    std::cin >> q;
    while (q--) {
        int op;
        std::cin >> op;
        if (op == 1) {
            int x;
            std::cin >> x;
            tree.change_rt(x);
        }
        else if (op == 2) {
            int x, y;
            LL v;
            std::cin >> x >> y >> v;
            tree.modify_chain(x, y, v);
        }
        else if (op == 3) {
            int x;
            LL v;
            std::cin >> x >> v;
            tree.modify_subtree(x, v);
        }
        else if (op == 4) {
            int x, y;
            std::cin >> x >> y;
            std::cout << tree.query_chain(x, y) << '\n';
        }
        else {
            int x;
            std::cin >> x;
            std::cout << tree.query_subtree(x) << '\n';
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int T = 1;

    for (int Case = 1; Case <= T; Case++)solve(Case);
    return 0;
}