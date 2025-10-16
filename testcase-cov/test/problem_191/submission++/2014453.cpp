#include <bits/stdc++.h>

using namespace std;

#define int long long 

constexpr int MAXN=1e5+10;

vector<int> g[MAXN], g2[MAXN];
struct E {
    int u, v;
} e[MAXN<<2]; int n, m, deg[MAXN], cnt[MAXN];

signed main(){
    cin>>n>>m;
    for (int i=1,u,v; i<=m; ++i) {
        cin>>u>>v; 
        g[u].push_back(v); g[v].push_back(u);
        deg[u]++; deg[v]++;
        e[i]={u,v};
    }
    for (int i=1; i<=m; ++i) {
        auto [u,v]=e[i];
        if ((deg[u]<deg[v]) || (deg[u]==deg[v]&&u<v))
            swap(u,v);
        g2[u].push_back(v);
    }
    int ans=0;
    for (int u=1; u<=n; ++u) {
        for (auto v: g2[u])
        for (auto w: g[v])
        if (deg[u]>deg[w] || (deg[u]==deg[w]&&u>w))
                ans+=cnt[w]++;
        for (auto v: g2[u])
        for (auto w: g[v])
        if (deg[u]>deg[w] || (deg[u]==deg[w]&&u>w))
                cnt[w]=0;
    }
    cout<<ans;
}