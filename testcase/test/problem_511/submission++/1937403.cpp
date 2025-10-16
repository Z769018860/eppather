#include <bits/stdc++.h>

template <typename Type>
Type read() {
    bool f = 0;
    char ch;
    while (!isdigit(ch = getchar())) f = ch == '-';
    Type x = ch ^ '0';
    while (isdigit(ch = getchar())) x = (x << 3) + (x << 1) + (ch ^ '0');
    return f ? -x : x;
}

template <typename Type>
Type &read(Type &x) { return x = read<Type>(); }

template <typename Type, typename... Args>
auto &read(Type &x, Args&... args) { return read(x), read(args...); }

constexpr uint64_t UINT64_X1F = 0x1f1f1f1f1f1f1f1f;
constexpr int UINT64_X1F_HIGHBIT = std::__lg(UINT64_X1F);

struct Num {
    uint64_t x;
    Num(uint64_t x = 0) : x(x) {}
    friend Num operator+(Num a, Num b) { return std::min(a.x + b.x, UINT64_X1F); }
    friend Num &operator+=(Num &a, Num b) { return a = a + b; }
    friend Num operator*(Num a, Num b) {
        if (std::__lg(a.x + 1) + std::__lg(b.x + 1) > UINT64_X1F_HIGHBIT) return UINT64_X1F;
        return std::min(a.x * b.x, UINT64_X1F);
    }
};


constexpr int N = 1000005;
constexpr int M = 1 << std::__lg(N) + 2;

struct Sub {
    Num f0, f1;
    Sub() {}
    Sub(Num f0, Num f1) : f0(f0), f1(f1) {}
    friend Sub operator+(Sub a, Sub b) { return Sub(a.f0 + b.f0, a.f1 + b.f1); }
    friend Sub &operator+=(Sub &a, Sub b) { return a = a + b; }
};

struct Cluster {
    Num f00, f01, f10, f11;
    Cluster() {}
    Cluster(Num f00, Num f01, Num f10, Num f11) : f00(f00), f01(f01), f10(f10), f11(f11) {}
    friend Sub operator*(Sub a, Cluster b) {
        return Sub(
            a.f0 * b.f00 + a.f1 * b.f10,
            a.f0 * b.f01 + a.f1 * b.f11
        );
    }
    friend Cluster operator*(Cluster a, Cluster b) {
        return Cluster(
            a.f00 * b.f00 + a.f01 * b.f10,
            a.f00 * b.f01 + a.f01 * b.f11,
            a.f10 * b.f00 + a.f11 * b.f10,
            a.f10 * b.f01 + a.f11 * b.f11
        );
    }
};

struct SetMul {
    uint64_t num0;
    std::multiset<uint64_t> set;
    Num solve() {
        if (num0) return 0;
        if (set.size() > UINT64_X1F_HIGHBIT) return UINT64_X1F;
        Num ans = 1;
        for (auto x : set) ans = ans * x;
        return ans;
    }
    void add(Num x) {
        if (x.x == 0) return ++num0, void(0);
        if (x.x == 1) return;
        set.insert(x.x);
    }
    void rem(Num x) {
        if (x.x == 0) return --num0, void(0);
        if (x.x == 1) return;
        set.erase(set.find(x.x));
    }
};

int n;
int ex[N], ey[N];
int fa[N], size[N], dep[N], dfn[N], son[N], top[N], inn[N];

int now[N];
int enable0[N], enable1[N];

uint64_t k;

SetMul s0[N], s1[N];

Sub ftop[N];

Cluster seg[M];

std::vector<int> to[N];

void dfs1(int u, int f) {
    fa[u] = f;
    size[u] = 1;
    for (auto v : to[u]) if (v != fa[u]) {
        dep[v] = dep[u] + 1;
        dfs1(v, u);
        if (size[v] > size[son[u]]) son[u] = v;
        size[u] += size[v];
    }
}

void dfs2(int u, int t) {
    static int dfn_cnt = 0;
    dfn[u] = ++dfn_cnt;
    top[u] = t;
    inn[t] = u;
    if (son[u]) dfs2(son[u], t);
    for (auto v : to[u]) if (v != fa[u] && v != son[u]) dfs2(v, v);
}

void seg_update(int pos, Cluster val) {
    int u = 1, l = 1, r = n;
    while (l < r) {
        int mid = l + r >> 1;
        if (pos <= mid) {
            u = u << 1;
            r = mid;
        } else {
            u = u << 1 | 1;
            l = mid + 1;
        }
    }
    seg[u] = val;
    while (u >>= 1) seg[u] = seg[u << 1 | 1] * seg[u << 1];
}

Cluster seg_query(int u, int l, int r, int L, int R) {
    if (l >= L && r <= R) return seg[u];
    int mid = l + r >> 1;
    if (R <= mid) return seg_query(u << 1, l, mid, L, R);
    if (L > mid) return seg_query(u << 1 | 1, mid + 1, r, L, R);
    return seg_query(u << 1 | 1, mid + 1, r, L, R) * seg_query(u << 1, l, mid, L, R);
}

Cluster seg_query(int L, int R) { return seg_query(1, 1, n, L, R); }

void update_light(int u) {
    Num t0 = enable0[u] ? s1[u].solve() : 0;
    Num t1 = enable1[u] ? s0[u].solve() : 0;
    seg_update(dfn[u], Cluster(t0, t1, t0, 0));
}

void rem_top(int u) {
    s0[fa[u]].rem(ftop[u].f0);
    s1[fa[u]].rem(ftop[u].f0 + ftop[u].f1);
}

void add_top(int u) {
    s0[fa[u]].add(ftop[u].f0);
    s1[fa[u]].add(ftop[u].f0 + ftop[u].f1);
}

void update_top(int u) { ftop[u] = Sub(1, 0) * seg_query(dfn[u], dfn[inn[u]]); }

void dfs3(int u) {
    for (auto v : to[u]) if (v != fa[u]) dfs3(v);
    update_light(u);
    if (top[u] == u) {
        update_top(u);
        if (fa[u]) add_top(u);
    }
}

void updateS(int u) {
    while (fa[top[u]]) {
        update_light(u);
        u = top[u];
        rem_top(u);
        update_top(u);
        add_top(u);
        u = fa[u];
    }
    update_light(u);
    u = top[u];
    update_top(u);
}

int dis[N];
uint64_t dfs(int u) {
    if (u == n + 1) return 1;
    uint64_t ans = 0;
    if (enable0[u]) {
        ans += dfs(u + 1);
    }
    if (!dis[u] && enable1[u]) {
        for (auto v : to[u]) ++dis[v];
        ans += dfs(u + 1);
        for (auto v : to[u]) --dis[v];
    }
    return ans;
}

uint64_t force_ans() { return dfs(1); }

uint64_t get_ans() {
    
    
    
    
    
    return (ftop[1].f0 + ftop[1].f1).x;
}

bool dec() {
    int p = n;
    while (p > 0 && !now[p]) now[p] = 1, enable0[p] = 0, enable1[p] = 1, --p;
    if (p == 0) return false;
    now[p] = 0, enable0[p] = 1, enable1[p] = 0;
    
    
    return true;
}

int main() {
    
    

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    read(n, k);
    for (int i = 1; i < n; ++i) ex[i] = read<int>() + 1;
    for (int i = 1; i < n; ++i) ey[i] = read<int>() + 1;
    for (int i = 1; i < n; ++i) {
        to[ex[i]].push_back(ey[i]);
        to[ey[i]].push_back(ex[i]);
    }

    {
        int q = read<int>();
        while (q--) now[read<int>() + 1] = 1;
    }

    {
        int i = n;
        while (i > 0 && now[i] == 0) --i;
        for (++i; i <= n; ++i) {
            bool flag = true;
            for (auto v : to[i]) flag &= !now[v];
            now[i] = flag;
            k -= flag;
            if (k == 0) {
                for (int i = 1; i <= n; ++i) if (now[i]) std::cout << i - 1 << ' ';
                std::cout << '\n';
                return 0;
            }
        }
    }

    for (int i = 1; i <= n; ++i) (now[i] ? enable1 : enable0)[i] = 1;

    
    
    
    

    
        
    
    

    
        
    

    dfs1(1, 0);
    dfs2(1, 1);
    dfs3(1);

    get_ans();

    int pos = -1;
    for (int i = n; i >= 1; --i) {
        if (!now[i]) {
            enable1[i] = 1;
            updateS(i);
        } else {
            enable0[i] = 1;
            enable1[i] = 0;
            updateS(i);
            uint64_t now_ans = get_ans();
            if (k + 1 <= now_ans) {
                pos = i;
                break;
            }
            k -= now_ans - 1;
            now[i] = 0;
            enable1[i] = 1;
            updateS(i);
        }
    }

    
    if (pos == -1) return std::cout << '\n', 0;

    now[pos] = 0;
    for (int i = pos + 1; i <= n; ++i) {
        enable0[i] = 0;
        updateS(i);
        uint64_t now_ans = get_ans();
        if (k <= now_ans) {
            now[i] = 1;
            if (k == 1) {
                while (i < n) now[++i] = 0;
                break;
            }
            --k;
        } else {
            now[i] = 0;
            k -= now_ans;
            enable0[i] = 1;
            enable1[i] = 0;
            updateS(i);
        }
    }

    for (int i = 1; i <= n; ++i) if (now[i]) std::cout << i - 1 << ' ';
    std::cout << '\n';

    return 0;
}
