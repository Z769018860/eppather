#include <bits/stdc++.h>
const int MAXN=1e6+10, mod=1e9+7;
using namespace std;
 
inline int read() {
    char c=getchar();
    int x=0, f=1;
    while (c<'0' || c>'9') {
        if(c=='-')    f=-1;
        c=getchar();
    }
    while (c>='0' && c<='9')  x=x*10+c-'0', c=getchar();
    return x*f;
}
 
int N,M,fa[MAXN],tot,val[MAXN],id[MAXN][21],num,dfn[MAXN],dep[MAXN],lg2[MAXN];
 
struct Edge {
    int u, v, w;
    bool operator<(const Edge &rhs) const { return w < rhs.w; }
} E[MAXN];
 
vector<int> v[MAXN];
 
int find(int x) {return fa[x]==x?fa[x]:fa[x]=find(fa[x]);}
 
void Kruskal() 
{
    for (int i=1; i<=2*N; i++)  fa[i]=i;
    tot = N;
    for(int i=1; i<=M; i++) {
        int x = find(E[i].u), y = find(E[i].v);
        if(x==y)    continue;
        val[++tot] = E[i].w;
        v[tot].push_back(x);
        v[tot].push_back(y);
        v[x].push_back(tot);
        v[y].push_back(tot);
        fa[x] = tot;
        fa[y] = tot;
    }
}
 
void dfs(int x, int fa) 
{
    dfn[x] = ++num;
    dep[x] = dep[fa]+1;
    id[num][0] = x;
    for (int i=0, to; i<v[x].size(); i++) {
        if((to=v[x][i])==fa)    continue;
        dfs(to, x);
        id[++num][0] = x;
    }
}
 
void RMQ() {
    for(int i=2; i<=num; i++)  lg2[i] = lg2[i>>1] + 1;
    for(int j=1; j<=20; j++)
        for(int i=1; i+(1<<j)-1<=num; i++) {
            int r = i+(1<<(j-1));
            id[i][j] = (dep[id[i][j-1]] < dep[id[r][j-1]]) ? id[i][j-1] : id[r][j-1];
        }
}
 
int A, B, C, P;
inline int rnd() { return A = (A*B+C) % P; }
 
int LCA(int x, int y) {
    x = dfn[x];
    y = dfn[y];
    if (x > y)
        swap(x, y);
    int k = lg2[y - x + 1];
    return dep[id[x][k]] < dep[id[y - (1 << k) + 1][k]] ? id[x][k] : id[y - (1 << k) + 1][k];
}
 
int main() {
    N = read();
    M = read();
    for (int i = 1; i <= M; i++) {
        int x = read(), y = read(), z = read();
        E[i] = (Edge){ x, y, z };
    }
    sort(E + 1, E + M + 1);
    Kruskal();
    dfs(tot, 0);
    RMQ();
    int ans = 0, Q = read();
    A = read();    B = read();
    C = read();    P = read();
    while (Q--) {
        int u = rnd() % N + 1, v = rnd() % N + 1;
        (ans += val[LCA(u, v)]) %= mod;
    }
    printf("%d", ans);
    return 0;
}