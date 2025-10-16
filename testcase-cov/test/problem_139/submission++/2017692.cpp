#include <bits/stdc++.h>
using namespace std;
const int _ = 1e5 + 10;
const int __ = 2e5 + 10;
const int ___ = 4e5 + 10;
int n, m, arr[_], e, hd[_], nx[__], to[__];
inline void add(int u, int v) {
    e++;
    nx[e] = hd[u];
    to[e] = v;
    hd[u] = e;
}
int fa[_], siz[_], dep[_], son[_];
void dfs1(int x) {
    siz[x] = 1;
    for (int i = hd[x]; i; i = nx[i]) {
        int y = to[i];
        if (y == fa[x]) continue;
        fa[y] = x;
        dep[y] = dep[x] + 1;
        dfs1(y);
        siz[x] += siz[y];
        if (siz[y] > siz[son[x]]) {
            son[x] = y;
        }
    }
}
int cnt, dfn[_], rev[_], rdfn[_], tp[_];
void dfs2(int x) {
    dfn[x] = ++cnt;
    rev[cnt] = x;
    if (son[x]) {
        tp[son[x]] = tp[x];
        dfs2(son[x]);
    }
    for (int i = hd[x]; i; i = nx[i]) {
        int y = to[i];
        if (y == fa[x] || y == son[x]) continue;
        tp[y] = y;
        dfs2(y);
    }
    rdfn[x] = cnt;
}
#define M (((L)+(R))>>1)
#define ls ((p)<<1)
#define rs (((p)<<1)|1)
long long sum[___], tag[___];
inline void mmodify(int p, long long k, int L, int R) {
    sum[p] += k * (R - L + 1);
    tag[p] += k;
}
inline void pushdown(int p, int L, int R) {
    mmodify(ls, tag[p], L, M);
    mmodify(rs, tag[p], M+1, R);
    tag[p] = 0;
}
inline void pushup(int p) {
    sum[p] = sum[ls] + sum[rs];
}
void build(int p, int L, int R) {
    tag[p] = 0LL;
    if (L == R) {
        sum[p] = arr[rev[L]];
    } else {
        build(ls, L, M);
        build(rs, M+1, R);
        pushup(p);
    }
}
void modify(int p, int k, int l, int r, int L, int R) {
    if (l == L && r == R) {
        mmodify(p, k, L, R);
    } else {
        pushdown(p, L, R);
        if (r <= M) {
            modify(ls, k, l, r, L, M);
        } else if (l > M) {
            modify(rs, k, l, r, M+1, R);
        } else {
            modify(ls, k, l, M, L, M);
            modify(rs, k, M+1, r, M+1, R);
        }
        pushup(p);
    }
}
long long query(int p, int l, int r, int L, int R) {
    if (l == L && r == R) {
        return sum[p];
    } else {
        pushdown(p, L, R);
        if (r <= M) {
            return query(ls, l, r, L, M);
        } else if (l > M) {
            return query(rs, l, r, M+1, R);
        } else {
            return query(ls, l, M, L, M) + query(rs, M+1, r, M+1, R);
        }
    }
}
#undef rs
#undef ls
#undef M
inline void add_chain(int u, int v, long long k) {
    while (tp[u] != tp[v]) {
        if (dep[tp[u]] < dep[tp[v]]) swap(u, v);
        modify(1, k, dfn[tp[u]], dfn[u], 1, n);
        u = fa[tp[u]];
    }
    if (dep[u] < dep[v]) swap(u, v);
    modify(1, k, dfn[v], dfn[u], 1, n);
}
inline long long sum_chain(int u, int v) {
    long long ans = 0LL;
    while (tp[u] != tp[v]) {
        if (dep[tp[u]] < dep[tp[v]]) swap(u, v);
        ans += query(1, dfn[tp[u]], dfn[u], 1, n);
        u = fa[tp[u]];
    }
    if (dep[u] < dep[v]) swap(u, v);
    ans += query(1, dfn[v], dfn[u], 1, n);
    return ans;
}
inline void add_subtree(int u, int rt, long long k) {
    if (u == rt) {
        modify(1, k, 1, n, 1, n);
    } else if (dfn[rt] > dfn[u] && dfn[rt] <= rdfn[u]) {
        int v = rt;
        while (tp[u] != tp[fa[v]]) {
            v = tp[fa[v]];
        }
        if (fa[v] != u) {
            v = rev[dfn[u] + 1];
        }
        if (dfn[v] != 1) modify(1, k, 1, dfn[v] - 1, 1, n);
        if (rdfn[v] != n) modify(1, k, rdfn[v] + 1, n, 1, n);
    } else {
        modify(1, k, dfn[u], rdfn[u], 1, n);
    }
}
inline long long sum_subtree(int u, int rt) {
    if (u == rt) {
        return query(1, 1, n, 1, n);
    } else if (dfn[rt] > dfn[u] && dfn[rt] <= rdfn[u]) {
        int v = rt;
        while (tp[u] != tp[fa[v]]) {
            v = tp[fa[v]];
        }
        if (fa[v] != u) {
            v = rev[dfn[u] + 1];
        }
        long long ans = 0LL;
        if (dfn[v] != 1) ans += query(1, 1, dfn[v] - 1, 1, n);
        if (rdfn[v] != n) ans += query(1, rdfn[v] + 1, n, 1, n);
        return ans;
    } else {
        return query(1, dfn[u], rdfn[u], 1, n);
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    for (int i = 2; i <= n; i++) {
        int f;
        cin >> f;
        add(f, i);
    }
    dep[1] = 1;
    dfs1(1);
    tp[1] = 1;
    dfs2(1);
    build(1, 1, n);
    cin >> m;
    int rt = 1;
    while (m--) {
        int o;
        cin >> o;
        switch (o) {
            case 1: {
                int u;
                cin >> u;
                rt = u;
                break;
            }
            case 2: {
                int u, v, k;
                cin >> u >> v >> k;
                add_chain(u, v, k);
                break;
            }
            case 3: {
                int u, k;
                cin >> u >> k;
                add_subtree(u, rt, k);
                break;
            }
            case 4: {
                int u, v;
                cin >> u >> v;
                cout << sum_chain(u, v) << '\n';
                break;
            }
            case 5: {
                int u;
                cin >> u;
                cout << sum_subtree(u, rt) << '\n';
                break;
            }
        }
    }
    cout << flush;
    return 0;
}