#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10;
struct Edge{
    int next, to, w;
}e[maxn<<1];
struct node{
    int u, v, w;
}edge[maxn<<1];
bool cmp(node x, node y){ 
    return x.w < y.w; 
}
int n, m, k, cnt;
int head[maxn], dep[maxn], f[maxn][20], maxw[maxn][20], fa[maxn];
void add(int u, int v, int w){
    e[++cnt].next = head[u];
    e[cnt].to = v;
    e[cnt].w = w;
    head[u] = cnt;
}
int find(int x){ 
    return x==fa[x] ? fa[x] : fa[x]=find(fa[x]); 
}
void kruskal(){
    for(int i = 1; i <= n; i++) fa[i] = i;
    sort(edge + 1, edge + 1 + m, cmp);
    int times = 1;
    for (int i = 1; i <= m&&times <= n-1; i++) {
        int fx=find(edge[i].u), fy=find(edge[i].v);
        if(fx!=fy){
            fa[fx] = fy, times++;
            add(edge[i].u, edge[i].v, edge[i].w);
            add(edge[i].v, edge[i].u, edge[i].w);
        }  
    }
}
void dfs(int u, int fa) {
    dep[u] = dep[fa] + 1;
    for (int i = head[u]; i; i = e[i].next) {
        int v = e[i].to;
        if (v==fa) continue;
        f[v][0] = u, maxw[v][0] = e[i].w;
        dfs(v, u);
    }
}
int query(int x, int y) {
    if(dep[x]<dep[y]) swap(x, y);
    int t = (int)(log(dep[x]) / log(2)), res = 0;
    for (int i = t; i >= 0; i--) {
        if (dep[f[x][i]] >= dep[y]) {
            res = max(res, maxw[x][i]);
            x = f[x][i];
        }
        if(x==y) return res;
    }
    for (int i = t; i >= 0; i--) {
        if (f[x][i] && f[x][i] != f[y][i]) {
            res = max(res, max(maxw[x][i], maxw[y][i]));
            x = f[x][i];
            y = f[y][i];
        }
    }
    return max(res, max(maxw[x][0], maxw[y][0]));
}
int main(){
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 1; i <= m; i++)
        scanf("%d%d%d", &edge[i].u, &edge[i].v, &edge[i].w);
    kruskal();
    for(int i = 1; i <= n; i++){
        if (!dep[i]) dfs(i, 0);
    }
    for (int j = 1; (1 << j) <= n; j++){
        for (int i = 1; i <= n; i++){
            f[i][j] = f[f[i][j - 1]][j - 1];
            maxw[i][j] = max(maxw[i][j - 1], maxw[f[i][j - 1]][j - 1]);
        }
    }
    while(k--){
        int s, t;
        scanf("%d%d", &s, &t);
        if (find(s)!=find(t)) puts("-1");
        else printf("%d\n", query(s, t));
    }
    return 0;
}