#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

const ll inf = 0x3f3f3f3f;
const ll linf = 0x3f3f3f3f3f3f3f3f;
const ll mod = 1e9 + 7;
const ll N = 3e5 + 10;

#define int long long

int n, m, q;
struct Edge {
    int x, y, l;
} e[N];

bool cmp(Edge a, Edge b) {
    return a.l < b.l;
}

vector<int> edge[N];
int cnt;
int num[N];

int par[N];

int findp(int x) {
    if (x == par[x]) return x;
    return par[x] = findp(par[x]);
}

void unite(int x, int y, int l) {
    x = findp(x);
    y = findp(y);
    if (x == y) return;
    par[x] = par[y] = ++cnt;
    par[cnt] = cnt;
    num[cnt] = l;
    edge[x].push_back(cnt);
    edge[y].push_back(cnt);
    edge[cnt].push_back(x);
    edge[cnt].push_back(y);
}

int A, B, C, P;

inline int rnd() { return A = (A * B + C) % P; }

const int LogN = 26;
int st[N], ed[N], id[N], deep[N];
int poi[N][LogN];
int Id;
int lg[N];

void dfs(int x, int par, int depth) {
    st[x] = ++Id;
    id[Id] = x;
    deep[Id] = depth;
    poi[Id][0] = Id;
    for(auto y:edge[x]) {
        if(y == par) continue;
        dfs(y, x, depth + 1);
        Id++;
        id[Id] = x;
        deep[Id] = depth;
        poi[Id][0] = Id;
    }

}

int query(int u, int v) {
    int l = st[u], r = st[v];
    if(l > r) swap(l, r);
    int t = lg[r - l + 1];
    int p = deep[poi[l][t]] < deep[poi[r - (1 << t) + 1][t]] ? poi[l][t]:poi[r - (1 << t) + 1][t];

    return num[id[p]];
}

void solve() {
    lg[0] = -1;
    for(int i = 1; i < N; ++i) lg[i] = lg[i >> 1] + 1;
    cin >> n >> m;
    cnt = n;
    for (int i = 1; i <= n; ++i) par[i] = i;
    for (int i = 1; i <= m; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        e[i] = {a, b, w};
    }
    sort(e + 1, e + m + 1, cmp);
    for (int i = 1; i <= m; ++i) {
        int x, y, l;
        x = e[i].x, y = e[i].y, l = e[i].l;
        x = findp(x);
        y = findp(y);
        if (x == y) continue;
        unite(x, y, l);
    }






    dfs(cnt, 0, 1);
    for(int i = 1; i < LogN; ++i) {
        for(int j = 1; j <= Id && j + (1 << i) - 1 <= Id; ++j) {
            poi[j][i] = deep[poi[j][i - 1]] < deep[poi[j + (1 << (i - 1))][i - 1]] ? poi[j][i - 1]:poi[j + (1 << (i - 1))][i - 1];
        }
    }





    cin >> q;
    cin >> A >> B >> C >> P;
    int ans = 0;
    for (int i = 1; i <= q; ++i) {
        int u, v;
        u = rnd() % n + 1, v = rnd() % n + 1;
        if(u ^ v) {
            ans = (ans + query(u, v)) % mod;
        }
    }
    cout << ans;
}

signed main() {






        solve();
    return 0;
}