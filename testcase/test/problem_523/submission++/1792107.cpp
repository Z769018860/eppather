#include <bits/stdc++.h>
#define rep(i, l, r) for(int i = (l); i <= (r); i++)
#define per(i, r, l) for(int i = (r); i >= (l); i--)
#define mem(a, b) memset(a, b, sizeof a)
#define For(i, l, r) for(int i = (l), i##e = (r); i < i##e; i++)
#define pb push_back
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
#define SZ(x) int((x).size())

using namespace std;
using ll = long long;

template<class T> inline T& cmin(T& a, const T& b) { if(b < a) a = b; return a; }
template<class T> inline T& cmax(T& a, const T& b) { if(a < b) a = b; return a; }
template<class... Args> void print(Args&&... args) {
#ifdef local
    ((cout << args << ' '), ...);
#endif
}
template<class... Args> void println(Args&&... args) {
#ifdef local
    print(args...), cout << endl;
#endif
}
int read() {
    char ch;
    do ch = cin.get(); while(ch < 48);
    int res = 0;
    do res = res * 10 + ch - 48, ch = cin.get(); while(ch >= 48);
    return res;
}

const int N = 5e5 + 8;

int m, n, a[N], b[N], id[N * 2], ans;
int A[N], B[N], C[N * 2], fa[N], no[N * 2], type[N * 2];
vector<pair<int, int>> G[N];
int cc, dfc, cyc, sum[N][3], dl[N], dr[N];
struct {
    vector<array<int, 2>> c;
    void init(int n) {
        int m = 1;
        while(m <= n + 1) m <<= 1;
        c.resize(m * 2);
    }
    void pu(int o) {
        c[o][0] = max(c[o * 2][0], c[o * 2 + 1][0]) + c[o][1];
    }
    void add(int l, int r, int v) {
        int m = SZ(c) >> 1;
        for(l += m - 1, r += m + 1; l ^ r ^ 1; pu(l >>= 1), pu(r >>= 1)) {
            if(~l & 1) c[l + 1][0] += v, c[l + 1][1] += v;
            if(r & 1) c[r - 1][0] += v, c[r - 1][1] += v;
        }
        while(l >>= 1) pu(l);
    }
} s[N];

int find(int x) { return fa[x] < 0 ? x : fa[x] = find(fa[x]); }
inline bool merge(int u, int v) {
    u = find(u), v = find(v);
    if(u == v) return 1;
    if(fa[u] > fa[v]) swap(u, v);
    fa[u] += fa[v], fa[v] = u;
    return 0;
}
bool dfs1(int u, int ban) {
    dl[u] = 1;
    bool res = 0;
    for(auto [v, i] : G[u]) {
        no[i] = cc;
        if(i == ban || i != ban + 1 && !dl[v] && (type[i ^ 1] = -1, dfs1(v, ban)))
            type[i] = 1, type[i ^ 1] = 2, res = 1;
    }
    return res;
}
void dfs2(int u) {
    dl[u] = ++dfc;
    for(auto [v, i] : G[u]) {
        no[i] = cc;
        if(!dl[v]) type[i] = v, type[i ^ 1] = -v, dfs2(v);
    }
    dr[u] = dfc;
}
void modify(int i, int v) {
    int c = no[i];
    if(c > cyc) {
        ans -= sum[c][0] + s[c].c[1][0];
        int x = abs(type[i]);
        if(type[i] >= 0) {
            s[c].add(dl[x], dr[x], C[i] - v);
            sum[c][0] += v - C[i];
        } else s[c].add(dl[x], dr[x], v - C[i]);
        ans += sum[c][0] + s[c].c[1][0];
    } else if(type[i] >= 0) {
        ans -= sum[c][0] + max(sum[c][1], sum[c][2]);
        sum[c][type[i]] += v - C[i];
        ans += sum[c][0] + max(sum[c][1], sum[c][2]);
    }
    C[i] = v;
}
int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T, q;
    cin >> m >> n >> T;
    For(i, 0, m) a[i] = read();
    For(i, 0, m) b[i] = read();
    int eid = 0;
    For(i, 0, m) {
        int u = a[i] - b[i], v = a[i] + b[i];
        if(u < 0) u += n;
        if(v >= n) v -= n;
        if(u > v) swap(u, v);
        A[i] = u, B[i] = v;
        G[v].eb(u, i * 2), id[++eid] = i * 2;
        if(u != v) G[u].eb(v, i * 2 + 1), id[++eid] = i * 2 + 1;
    }
    mem(fa, -1);
    For(i, 0, m) if(merge(A[i], B[i])) ++cc, ++cyc, dfs1(A[i], i * 2);
    For(i, 0, n) if(!dl[i]) ++cc, dfs2(i), s[cc].init(dfc), dfc = 0;
    rep(i, 1, eid) modify(id[i], read());
    cout << ans << '\n';
    cin >> q;
    while(q--) {
        int i = read() - T * ans;
        modify(id[i], read() - T * ans);
        cout << ans << '\n';
    }
}