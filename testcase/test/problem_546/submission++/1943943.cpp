#include <bits/stdc++.h>
using namespace std;

const int d[4][2] = {
    0, 1, 0, -1, 1, 0, -1, 0
};
const int maxk = 100005;
int n, m, k, S, T, p[2][maxk];

inline int gi()
{
    char c = getchar();
    while (c < '0' || c > '9') c = getchar();
    int sum = 0;
    while ('0' <= c && c <= '9') sum = sum * 10 + c - 48, c = getchar();
    return sum;
}

namespace segt
{
    int tot[2], ch[2][maxk * 10][2], val[2][maxk * 10], root[2];

    #define mid ((l + r) >> 1)

    void Set(int d, int x, int y, int v, int &s, int l, int r)
    {
        if (!s) s = ++tot[d];
        if (x <= l && r <= y) {
            val[d][s] = v; return;
        }
        if (x <= mid) Set(d, x, y, v, ch[d][s][0], l, mid);
        if (mid + 1 <= y) Set(d, x, y, v, ch[d][s][1], mid + 1, r);
    }

    void Set(int d, int x, int y, int v)
    {
        Set(d, x, y, v, root[d], 1, 1e9);
    }

    int query(int d, int x, int s = 1, int l = 1, int r = 1e9)
    {
        if (l <= x && x <= r && val[d][s]) return val[d][s];
        if (x <= mid) return query(d, x, ch[d][s][0], l, mid);
        else return query(d, x, ch[d][s][1], mid + 1, r);
    }
}

int x[2][maxk], cnt[2];
void prepare1(int d)
{
    memcpy(x[d], p[d], sizeof(int) * (k + 1));
    sort(x[d] + 1, x[d] + k + 1);
    int &M = cnt[d], N;
    N = unique(x[d] + 1, x[d] + k + 1) - x[d] - 1;
    if (x[d][1] > 1) segt::Set(d, 1, x[d][1] - 1, ++M);
    for (int i = 1; i <= N; ++i) {
        ++M; segt::Set(d, x[d][i], x[d][i], M);
        if (x[d][i] < x[d][i + 1] - 1) segt::Set(d, x[d][i] + 1, x[d][i + 1] - 1, ++M);
    }
    if (d == 0 && x[d][N] < n) segt::Set(d, x[d][N] + 1, n, ++M);
    if (d == 1 && x[d][N] < m) segt::Set(d, x[d][N] + 1, m, ++M);
}

struct block {
    int l, r, Id;
};
vector<block> t[2][maxk * 2];

struct node {
    int p, Id;
};
vector<node> q[2][maxk * 2];

int _d, tot;
inline bool cmp(const int &a, const int &b)
{
    return p[_d][a] != p[_d][b] ? p[_d][a] < p[_d][b] : p[_d ^ 1][a] < p[_d ^ 1][b];
}

int Id[maxk];
void prepare2(int d)
{
    for (int i = 1; i <= k; ++i) Id[i] = i;
    _d = d; sort(Id + 1, Id + k + 1, cmp);
    for (int i = 1, j = 1, now, x = 0, y, ly; i <= cnt[d]; ++i) {
        now = 0;
        if (j <= k) x = segt::query(d, p[d][Id[j]]), y = segt::query(d ^ 1, p[d ^ 1][Id[j]]);
        if (x != i) {t[d][i].push_back((block){1, cnt[d ^ 1], ++tot}), q[d ^ 1][1].push_back((node){i, tot}); continue;}
        while(x == i && j <= k) {
            if (y > now + 1) t[d][i].push_back((block){now + 1, y - 1, ++tot}), q[d ^ 1][now + 1].push_back((node){i, tot});
            q[d][i].push_back((node){y, 0});
            now = y; ++j; ly = y;
            if (j > k) break;
            x = segt::query(d, p[d][Id[j]]);
            y = segt::query(d ^ 1, p[d ^ 1][Id[j]]);
        }
        if (ly < cnt[d ^ 1]) t[d][i].push_back((block){ly + 1, cnt[d ^ 1], ++tot}), q[d ^ 1][ly + 1].push_back((node){i, tot});
    }
}

struct edge {
    int to, next, w;
}e[maxk * 180];
int h[maxk * 80], Tot;

inline void add(int u, int v, int w)
{
    if (!u || !v) return;
    e[++Tot] = (edge) {v, h[u], w}; h[u] = Tot;
}

namespace pret
{

    int root[2][maxk * 5], Time[2], tot[2], ch[2][maxk * 60][2], val[2][maxk * 60];

    #define mid ((l + r) >> 1)

    void Set(int d, int &s, int l, int r, int p, int v)
    {
        ++tot[d];
        ch[d][tot[d]][0] = ch[d][s][0]; ch[d][tot[d]][1] = ch[d][s][1];
        s = tot[d];
        if (l == r) {
            val[d][s] = v; return;
        }
        if (p <= mid) Set(d, ch[d][s][0], l, mid, p, v);
        else Set(d, ch[d][s][1], mid + 1, r, p, v);
    }

    inline void Set(int p, int v, int d)
    {
        ++Time[d]; root[d][Time[d]] = root[d][Time[d] - 1];
        Set(d, root[d][Time[d]], 1, cnt[d ^ 1], p, v);
    }   

    struct Edge {
        int u, v, type;
    };
    vector<Edge> E;

    void query(int d, int s, int l, int r, int x, int y, int u)
    {
        if (x <= l && r <= y) {
            if (l == r) E.push_back((Edge) {u, val[d][s], 2});
            else E.push_back((Edge) {u, s, d});
            return;
        }
        if (x <= mid) query(d, ch[d][s][0], l, mid, x, y, u);
        if (y >= mid + 1) query(d, ch[d][s][1], mid + 1, r, x, y, u);
    }

    inline void query(int l, int r, int u, int d)
    {
        query(d, root[d][Time[d]], 1, cnt[d ^ 1], l, r, u);
    }

    #define leaf(d, x) (!ch[d][x][0] && !ch[d][x][1])
    inline void addedge(int base)
    {
        for (Edge v : E)
            add(v.u, v.type == 2 ? v.v : v.type == 0 ? v.v + base : v.v + base + tot[0], 1);
        for (int i = 1; i <= tot[0]; ++i)
            add(i + base, leaf(0, ch[0][i][0]) ? val[0][ch[0][i][0]] : ch[0][i][0] + base, 0),
            add(i + base, leaf(0, ch[0][i][1]) ? val[0][ch[0][i][1]] : ch[0][i][1] + base, 0);
        for (int i = 1; i <= tot[1]; ++i)
            add(i + base + tot[0], leaf(1, ch[1][i][0]) ? val[1][ch[1][i][0]] : ch[1][i][0] + base + tot[0], 0),
            add(i + base + tot[0], leaf(1, ch[1][i][1]) ? val[1][ch[1][i][1]] : ch[1][i][1] + base + tot[0], 0);
    }
}

void prepare3(int d)
{
    for (int i = 1; i <= cnt[d]; ++i) {
        for (node v : q[d][i]) pret::Set(v.p, v.Id, d);
        for (block v : t[d][i]) pret::query(v.l, v.r, v.Id, d);
    }
}

#define mid ((l + r) >> 1)
int find(int x[], int d)
{
    int l = 0, r = t[d][x[d]].size() - 1;
    while (l < r) {
        if (t[d][x[d]][mid].r < x[d ^ 1]) l = mid + 1;
        else if (t[d][x[d]][mid].l > x[d ^ 1]) r = mid - 1;
        else return t[d][x[d]][mid].Id;
    }
    return t[d][x[d]][l].Id;
}

bool vis[maxk * 80];
int dis[maxk * 80], que[2][maxk * 40], r[2];

void bfs(int s[], int tot)
{
    memset(dis, -1, sizeof(dis));
    for (int i = 1; i <= tot; ++i) que[0][++r[0]] = s[i], vis[s[i]] = true, dis[s[i]] = 0;
    int now = 1;
    do {
        now ^= 1; r[now ^ 1] = 0;
        for (int u, j = 1; j <= r[now]; ++j) {
            u = que[now][j];
            for (int v, i = h[u]; v = e[i].to, i; i = e[i].next)
                if (!e[i].w && !vis[v]) {
                    vis[v] = true; que[now][++r[now]] = v;
                    dis[v] = dis[u];
                }
        }
        for (int u, j = 1; j <= r[now]; ++j) {
            u = que[now][j];
            for (int v, i = h[u]; v = e[i].to, i; i = e[i].next)
                if (e[i].w && !vis[v]) {
                    vis[v] = true; que[now ^ 1][++r[now ^ 1]] = v;
                    dis[v] = dis[u] + 1;
                }
        }
    } while (r[now ^ 1]);
}

set<pair<int, int> > Cnt;

int main()
{
    n = gi(); m = gi(); k = gi(); int Q = gi();
    for (int i = 1; i <= k; ++i) scanf("%d%d", &p[0][i], &p[1][i]), Cnt.insert(make_pair(p[0][i], p[1][i]));
    S = gi(); T = gi();
    ++k; p[0][k] = S; p[1][k] = T;

    prepare1(0);
    prepare1(1);

    prepare2(0);
    prepare2(1);

    prepare3(0);
    prepare3(1);

    int x[2], t[10] = {0}, Tot = 0;

    for (int i = 0; i < 4; ++i) 
        if (1 <= S + d[i][0] && S + d[i][0] <= n && 1 <= T + d[i][1] && T + d[i][1] <= m && !Cnt.count(make_pair(S + d[i][0], T + d[i][1]))) { 
            x[0] = segt::query(0, S + d[i][0]); x[1] = segt::query(1, T + d[i][1]);
            if (!d[i][0]) t[++Tot] = find(x, 0);
            else t[++Tot] = find(x, 1);
        }

    pret::addedge(tot);
    bfs(t, Tot);

    S = segt::query(0, S); T = segt::query(1, T);
    for (int i = 1; i <= Q; ++i) {
        x[0] = segt::query(0, gi()); x[1] = segt::query(1, gi());
        if (x[0] == S && x[1] == T) puts("0");
        else printf("%d\n", min(dis[find(x, 0)], dis[find(x, 1)]));
    }

    return 0;
}