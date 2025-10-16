

#include<bits/stdc++.h>
using namespace std;
#define int long long
#define rep(i,j,k) for (int i=j;i<=k;++i)
#define per(i,j,k) for (int i=j;i>=k;--i)
int const N=1e4+5;
int n,m,r,mi[N],id[N],top[N],fa[N];
struct edge{int u,v,w;}e[N];
inline int zhuliu(int n,int m,int r){
    int ans=0;
    while (1){
        memset(mi,0x3f,sizeof(int)*(n+1));
        memset(id,0,sizeof(int)*(n+1));
        memset(fa,0,sizeof(int)*(n+1));
        memset(top,0,sizeof(int)*(n+1));
        rep(i,1,m){
            int u=e[i].u,v=e[i].v,w=e[i].w;
            if (mi[v]>w) mi[v]=w,fa[v]=u;
        }
        int cnt=0;
        rep(i,1,n){
            if (i==r) continue;
            if (!fa[i]) return -1;
            ans+=mi[i];
        }
        rep(i,1,n){
            if (i==r) continue;
            if (top[i]) continue;
            int u=i;
            for (;!top[u] && u!=r;u=fa[u]) top[u]=i;
            if (top[u]==i){
                ++cnt;
                for (;!id[u];u=fa[u]) id[u]=cnt;
            }
        }
        if (!cnt) return ans;
        rep(i,1,n)
            if (!id[i]) id[i]=++cnt;
        int gt=0;
        rep(i,1,m){
            int u=e[i].u,v=e[i].v,w=e[i].w;
            if (id[u]==id[v]) continue;
            e[++gt]=(edge){id[u],id[v],w-mi[v]};
        }
        n=cnt,m=gt,r=id[r];
    }
}
void solve(){
    cin>>n>>m>>r;
    rep(i,1,m) cin>>e[i].u>>e[i].v>>e[i].w;
    cout<<zhuliu(n,m,r)<<'\n';
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int t=1;
    
    while (t--) solve();
    return 0;
}