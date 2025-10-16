#include <bits/stdc++.h>

using i64 = long long;

template <typename Info, typename Tag>
struct LazySegmentTree {
    int n;
    std::vector<Info> s;
    std::vector<Tag> t;

    LazySegmentTree() = default;
    LazySegmentTree(int n_, const Info &v = Info{}) {
        init(n_, v);
    }
    template <typename T>
    LazySegmentTree(const std::vector<T> &v) {
        init(v);
    }
    void init(int n_, const Info &v = Info{}) {
        init(std::vector<Info>(n_, v));
    }
    template <typename T>
    void init(const std::vector<T> &v) {
        n = int(v.size());
        s.assign(4 << std::__lg(n), Info{});
        t.assign(4 << std::__lg(n), Tag{});
        auto build = [&](auto self, int u, int l, int r) -> void {
            if (r - l == 1) {
                s[u] = v[l];
                return;
            }
            int m = (l + r) / 2;
            self(self, u << 1, l, m);
            self(self, u << 1 | 1, m, r);
            pull(u);
        };
        build(build, 1, 0, n);
    }

    void pull(int u) {
        s[u] = s[u << 1] + s[u << 1 | 1];
    }
    void apply(int u, const Tag &v) {
        s[u].apply(v);
        t[u].apply(v);
    }
    void push(int u) {
        apply(u << 1, t[u]);
        apply(u << 1 | 1, t[u]);
        t[u] = Tag{};
    }

    void modify(int u, int l, int r, int p, const Info &v) {
        if (r - l == 1) {
            s[u] = v;
            return;
        }
        int m = (l + r) / 2;
        push(u);
        if (p < m) {
            modify(u << 1, l, m, p, v);
        } else {
            modify(u << 1 | 1, m, r, p, v);
        }
        pull(u);
    }
    void modify(int p, const Info &v) {
        modify(1, 0, n, p, v);
    }

    Info query(int u, int l, int r, int p) {
        if (r - l == 1) {
            return s[u];
        }
        int m = (l + r) / 2;
        push(u);
        if (p < m) {
            return query(u << 1, l, m, p);
        } else {
            return query(u << 1 | 1, m, r, p);
        }
    }
    Info query(int p) {
        return query(1, 0, n, p);
    }

    Info rangeQuery(int u, int l, int r, int ql, int qr) {
        if (qr <= l || r <= ql) {
            return Info{};
        }
        if (ql <= l && r <= qr) {
            return s[u];
        }
        int m = (l + r) / 2;
        push(u);
        return rangeQuery(u << 1, l, m, ql, qr) + rangeQuery(u << 1 | 1, m, r, ql, qr);
    }
    Info rangeQuery(int ql, int qr) {
        return rangeQuery(1, 0, n, ql, qr);
    }

    void rangeApply(int u, int l, int r, int ql, int qr, const Tag &v) {
        if (qr <= l || r <= ql) {
            return;
        }
        if (ql <= l && r <= qr) {
            apply(u, v);
            return;
        }
        int m = (l + r) / 2;
        push(u);
        rangeApply(u << 1, l, m, ql, qr, v);
        rangeApply(u << 1 | 1, m, r, ql, qr, v);
        pull(u);
    }
    void rangeApply(int ql, int qr, const Tag &v) {
        rangeApply(1, 0, n, ql, qr, v);
    }
};

struct Tag {
    int v = 0;
    void apply(const Tag &b) {
        v = std::max(v, b.v);
    }
};

struct Info {
    std::pair<int, int> v{2e9, -1};
    void apply(const Tag &b) {
        v.first = std::max(v.first, b.v);
    }
};
Info operator+(const Info &a, const Info &b) {
    return Info{std::min(a.v, b.v)};
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    std::cin >> n;

    LazySegmentTree<Info, Tag> seg(n);
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        seg.modify(i, Info{{x, i}});
    }

    int q;
    std::cin >> q;

    while (q--) {
        int op;
        std::cin >> op;
        if (op == 1) {
            int l, r, x;
            std::cin >> l >> r >> x;
            --l;
            seg.rangeApply(l, r, Tag{x});
        }
        if (op == 2) {
            int l, r, x, k;
            std::cin >> l >> r >> x >> k;
            --l;
            if (r - l < k) {
                std::cout << "-1\n";
                continue;
            }

            std::priority_queue<std::tuple<std::pair<int, int>, int, int>> h;
            auto push = [&](int l, int r) {
                if (l >= r) {
                    return;
                }
                auto v = seg.rangeQuery(l, r).v;
                v.first *= -1;
                h.emplace(v, l, r);
            };
            push(l, r);
            std::vector<int> ans;
            while (k--) {
                auto [v, l, r] = h.top();
                h.pop();
                ans.push_back(-v.first);
                push(l, v.second);
                push(v.second + 1, r);
            }
            if (ans.back() >= x) {
                std::cout << "-1\n";
            } else {
                for (int i = 0; i < int(ans.size()); ++i) {
                    std::cout << ans[i] << " \n"[i == int(ans.size()) - 1];
                }
            }
        }
    }

    return 0;
}
