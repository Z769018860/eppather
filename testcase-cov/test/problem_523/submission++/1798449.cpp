#include <bits/stdc++.h>
#define lowbit(x) (x & -x)
#define eb emplace_back
#define pb push_back
#define mp make_pair
using namespace std;

typedef long long ll;
const int N = 5e5+5;
const int Mod = 998244353;

#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;

inline int read() {
    int x = 0; char c = getchar();
    while (c < '0' || c > '9') c = getchar();
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x;
}

int m, n, T, q, a[N], k[N], ans, lst, re[N * 2], cnt;
int E[N][2], v[N][2], tp[N];
bool vis[N];

vector<int> G[N];
pair<int, int> w[N];

int fa[N], e[N];

int fnd(int x) {
    if (x == fa[x]) return x;
    return fa[x] = fnd(fa[x]);
}

inline int mrg(int x, int y, int id) {
    x = fnd(x), y = fnd(y);
    if (x == y) e[x] = id;
    else {
        fa[x] = y;
        e[y] |= e[x];
    }
    return (x != y);
}

namespace Ring {
    int stk[N], top;
    bool fl;

    void dfs(int x, int fa, int ei) {
        vis[x] = 1;
        if (x == E[ei][1]) fl = 1;
        for (int id : G[x]) {
            int son = E[id / 2][id & 1];
            if (son == fa) continue;

            bool p = fl;
            if (!fl) stk[++top] = id;
            dfs(son, x, ei);
            if (!fl) top--;

            if (p == fl) tp[id / 2] = (id & 1) + 4;
        }
    }

    void init(int x) {
        e[x]--;
        stk[top = fl = 0] = 2 * e[x];
        dfs(E[e[x]][0], E[e[x]][0], e[x]);
        for (int i = 0; i <= top; i++) {
            int id = stk[i];
            tp[id / 2] = 2 + (id & 1);
            w[x].first += v[id / 2][id & 1];
            w[x].second += v[id / 2][!(id & 1)];
        }
    }
}

struct segT {
    struct node {
        int mx, ad;
    };
    vector<node> T;

    #define ls (p << 1)
    #define rs (p << 1 | 1)

    inline void push_up(int p) {
        T[p].mx = max(T[ls].mx, T[rs].mx) + T[p].ad;
    }

    void upd(int p, int l, int r, int gl, int gr, int k) {
        if (gl > gr) return;
        if (l >= gl && r <= gr) {
            T[p].mx += k, T[p].ad += k;
            return;
        }
        int mid = (l + r) >> 1;
        if (mid >= gl) upd(ls, l, mid, gl, gr, k);
        if (mid < gr) upd(rs, mid + 1, r, gl, gr, k);
        push_up(p);
    }

    #undef ls
    #undef rs
};

namespace Tree {
    int dfn[N], siz[N], tot;
    segT T[N];

    void dfs(int x, int fa) {
        vis[x] = 1;
        dfn[x] = ++tot;
        siz[x] = 1;
        for (int id : G[x]) {
            int son = E[id / 2][id & 1];
            if (son == fa) continue;
            dfs(son, x);
            siz[x] += siz[son];
            tp[id / 2] = id & 1;
        }
    }

    void init(int rt) {
        tot = 0;
        dfs(rt, -1);
        T[rt].T.resize(siz[rt] * 4);
    }

    void upd(int rt, int i, int j, int d) {
        ans -= T[rt].T[1].mx;

        int s = E[i][tp[i]];
        if (j == tp[i]) {
            T[rt].upd(1, 1, siz[rt], 1, dfn[s] - 1, d);
            T[rt].upd(1, 1, siz[rt], dfn[s] + siz[s], siz[rt], d);
        }
        else T[rt].upd(1, 1, siz[rt], dfn[s], dfn[s] + siz[s] - 1, d);

        ans += T[rt].T[1].mx;
    }
}

inline void upd(int i, int j, int g) {
    int rt = fnd(E[i][0]), d = g - v[i][j];
    if (tp[i] < 2) {
        Tree::upd(rt, i, j, d);
    } else if (tp[i] < 4) {
        ans -= max(w[rt].first, w[rt].second);
        (j == tp[i] - 2 ? w[rt].first : w[rt].second) += d;
        if (k[i] == 1) w[rt].second += d;
        ans += max(w[rt].first, w[rt].second);
    } else {
        if (j == tp[i] - 4) ans += d;
    }
    v[i][j] = g;
}

int main() {
    m = read(), n = read(), T = read();
    for (int i = 0; i < n; i++) fa[i] = i;
    for (int i = 0; i < m; i++) a[i] = read();
    for (int i = 0; i < m; i++) {
        int b = read();
        int &x = E[i][0] = (a[i] + b) % n;
        int &y = E[i][1] = (a[i] - b + n) % n;
        k[i] = 1 + (x != y);
        if (x > y) swap(x, y);
        if (mrg(x, y, i + 1)) {
            G[x].pb(2 * i + 1);
            G[y].pb(2 * i);
        }
    }

    for (int i = 0; i < n; i++) if (!vis[i]) {
        int f = fnd(i);
        if (e[f]) Ring::init(f);
        else Tree::init(f);
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < k[i]; j++) {
            re[++cnt] = 2 * i + j;
            upd(i, j, read());
        }

    cout << ans << '\n';

    q = read();
    while (q--) {
        int x = read() - ans * T, v = read() - ans * T;
        upd(re[x] / 2, re[x] & 1, v);
        cout << ans << '\n';
    }
    return 0;
}