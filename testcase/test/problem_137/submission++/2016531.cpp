#include<iostream>
#include<string.h>
#include<vector>
#include<algorithm>
using std::cin; using std::cout; using std::vector;
const int maxn = 70000 + 5;
const int mod = 1000000007;

int lg[4 * maxn];
void get_lg(){
    lg[1] = 0;
    for(int j = 2; j < 4 * maxn; j++) lg[j] = lg[j >> 1] + 1;
}
int A, B, C, P;
inline int rnd(){ return A = (A * B + C ) % P; }

struct edge{
    int x, y, w;
    edge(int f, int t, int d): x(f), y(t), w(d){}
    edge(){}
    bool operator<(const edge &rhs)const{
        return w < rhs.w;
    }
};
vector<edge> edges; int n, m;
vector<int> tree[2 * maxn]; int w[2 * maxn];
int fa[2 * maxn];
int euler[4 * maxn], pos[2 * maxn], tot, dfn;
int st[4 * maxn][20];

int pa(int x){
    return x == fa[x] ? x : fa[x] = pa(fa[x]);
}
void kruskal(){
    std::sort(edges.begin(), edges.end());
    for(int k = 0; k <= 2 * n; k++) fa[k] = k;
    for(int k = 0; k <= 2 * n; k++) tree[k].clear();
    int cnt = 0; tot = n;
    for(const edge &e : edges){
        int fx = pa(e.x), fy = pa(e.y);
        if(fx == fy) continue;
        fa[fx] = fa[fy] = ++tot; w[tot] = e.w;
        tree[tot].push_back(fx); tree[fx].push_back(tot);
        tree[tot].push_back(fy); tree[fy].push_back(tot);
        cnt++; if(cnt == n - 1) break;
    }
}
void dfs(int u, int p){
    euler[++dfn] = u; pos[u] = dfn;
    for(const int &v : tree[u])
        if(v != p){
            dfs(v, u);
            euler[++dfn] = u;
        }
}
void get_st(){
    for(int j = 1; j <= dfn; j++) st[j][0] = euler[j];
    for(int k = 1; (1 << k) <= dfn; k++){
        int s = 1 << (k - 1);
        for(int j = 1; j + s - 1 <= dfn; j++)
            if(pos[st[j][k - 1]] < pos[st[j + s][k - 1]])
                st[j][k] = st[j][k - 1];
            else st[j][k] = st[j + s][k - 1];
    }
}
int lca(int x, int y){
    int l = pos[x], r = pos[y];
    if(l > r) std::swap(l, r);
    int k = lg[r - l + 1];
    int anc = 0;
    if(pos[st[l][k]] < pos[st[r - (1 << k) + 1][k]])
        anc = st[l][k];
    else anc = st[r - (1 << k) + 1][k];
    return w[anc];    
}
int main(){
    std::ios_base::sync_with_stdio(false);

    get_lg();
    cin >> n >> m; int x, y, w, q;
    for(int k = 0; k < m; k++){
        cin >> x >> y >> w;
        edges.push_back(edge(x, y, w));
    }
    kruskal();
    dfs(tot, 0);
    get_st();
    cin >> q; int ans = 0;
    cin >> A >> B >> C >> P;
    while(q--){
        int u = rnd() % n + 1, v = rnd() % n + 1;
        int res = lca(u, v);
        ans = (ans + res) % mod;
    }
    cout << ans << '\n';
    return 0;
}