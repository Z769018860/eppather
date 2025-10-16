#include <bits/stdc++.h>

#ifndef _STKLIB_FENWICK_HPP
# define _STKLIB_FENWICK_HPP

# include <functional>
# include <vector>

namespace StK {

template <class Type, class PlusOper = std::plus<Type>, class Sequence = std::vector<Type> >
class Fenwick {

   protected:
    size_t size;
    Sequence data;

   public:
    template <class... Args>
      Fenwick(size_t size, Args... args)
      : size(size), data(size + 1, Type(args...)) {}

    Fenwick &add(size_t i, Type v) { while (i <= size) data[i] = PlusOper()(data[i], v), i += i & -i; return *this; }

    Type sum(size_t i) { Type ans(data.front()); while (i) ans = PlusOper()(ans, data[i]), i &= i - 1; return ans; }

};

} 

#endif

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int n, m, R;
    std::cin >> n >> m >> R;
    --R;

    std::vector<int64_t> val(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> val[i];
    }

    std::vector<std::vector<int>> to(n);
    for (int i = 1; i < n; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        to[u].push_back(v);
        to[v].push_back(u);
    }

    const int C = std::__lg(n) + 1;
    int dfn_cnt = 0;
    std::vector<int> dep(n), dfn(n), dfn_end(n);
    std::vector<std::vector<int>> anc(C, std::vector<int>(n));
    {
        auto _F_dfs = [&](auto self, int u) -> void {
            for (int i = 1; i < C; ++i) {
                anc[i][u] = anc[i - 1][anc[i - 1][u]];
            }
            dfn[u] = ++dfn_cnt;
            for (auto v : to[u]) {
                to[v].erase(std::find(to[v].begin(), to[v].end(), u));
                dep[v] = dep[u] + 1;
                anc[0][v] = u;
                val[u] -= val[v];
                self(self, v);
            }
            dfn_end[u] = dfn_cnt;
        };
        anc[0][R] = R;
        _F_dfs(_F_dfs, R);
    }

    StK::Fenwick<int64_t> fen1(n), fen2(n);
    auto add_uptag = [&](int u, int64_t V) {
        fen1.add(dfn[u], V);
        fen2.add(dfn[u], V * dep[u]);
    };
    auto query_sub1 = [&](int l, int r) { return fen1.sum(r) - fen1.sum(l - 1); };
    auto query_sub2 = [&](int l, int r) { return fen2.sum(r) - fen2.sum(l - 1); };

    for (int i = 0; i < n; ++i) {
        add_uptag(i, val[i]);
    }

    auto lca = [&](int u, int v) {
        if (dep[u] < dep[v]) {
            std::swap(u, v);
        }
        for (int d = dep[u] - dep[v]; d; d &= d - 1) {
            u = anc[__builtin_ctz(d)][u];
        }
        if (u == v) {
            return u;
        }
        for (int i = std::__lg(dep[u]); i >= 0; --i) {
            if (anc[i][u] != anc[i][v]) {
                u = anc[i][u];
                v = anc[i][v];
            }
        }
        return anc[0][u];
    };

    for (int qi = 0; qi < m; ++qi) {
        int op;
        std::cin >> op;
        if (op == 1) {
            int a, b, x;
            std::cin >> a >> b >> x;
            --a, --b;
            int c = lca(a, b);
            add_uptag(a, x);
            add_uptag(b, x);
            add_uptag(c, -x);
            if (c != R) {
                add_uptag(anc[0][c], -x);
            }
        } else if (op == 2) {
            int u;
            std::cin >> u;
            --u;
            std::cout << query_sub1(dfn[u], dfn_end[u]) << '\n';
        } else {
            int u;
            std::cin >> u;
            --u;
            std::cout << query_sub2(dfn[u], dfn_end[u]) - (dep[u] - 1) * query_sub1(dfn[u], dfn_end[u]) << '\n';
        }
    }

    return 0;
}
