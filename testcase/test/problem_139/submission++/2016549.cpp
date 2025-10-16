#include<bits/stdc++.h>
using namespace std;
int n,fa[105000],rt,m,op,q,x,y,z;
int dep[105000],sz[105000],kson[105000],ktop[105000],dfnord[105000],dfncnt;
long long a[105000];
vector<int> son[105000],klst[105000];
void dfs(int x) {
    sz[x]=1;
    dep[x]=dep[fa[x]]+1;
    for (auto cur:son[x]) {
        dfs(cur);
        sz[x]+=sz[cur];
    }
    if (sz[x]==1) return;
    kson[x]=son[x][0];
    for (int j=1;j<son[x].size();j++) if (sz[son[x][j]]>sz[kson[x]]) kson[x]=son[x][j];
}
void dfs0(int x) {
    dfnord[x]=++dfncnt;
    if ((x==1)||(x!=kson[fa[x]])) ktop[x]=x;
    else ktop[x]=ktop[fa[x]];
    if (sz[x]==1) return;
    dfs0(kson[x]);
    for (auto cur:son[x]) if (cur!=kson[x]) dfs0(cur);
}
int lca(int u,int v) {
    while (ktop[u]!=ktop[v]) {
        if (dep[ktop[u]]<dep[ktop[v]]) v=fa[ktop[v]];
        else u=fa[ktop[u]];
    }
    if (dep[u]<dep[v]) return u;
    return v;
}
namespace seg {
    long long sgt[405000][2];
    void pushdown(int p,int s,int t) {
        if (s==t) {
            sgt[p][1]=0;
            return;
        }
        int mid=(s+t)/2;
        sgt[p*2][0]+=sgt[p][1]*(mid-s+1);
        sgt[p*2][1]+=sgt[p][1];
        sgt[p*2+1][0]+=sgt[p][1]*(t-mid);
        sgt[p*2+1][1]+=sgt[p][1];
        sgt[p][1]=0;
    }
    void update(int p,int s,int t,int l,int r,long long x) {
        if ((l<=s)&&(t<=r)) {
            sgt[p][0]+=x*(t-s+1);
            sgt[p][1]+=x;
            return;
        }
        pushdown(p,s,t);
        int mid=(s+t)/2;
        if (l<=mid) update(p*2,s,mid,l,r,x);
        if (r>mid) update(p*2+1,mid+1,t,l,r,x);
        sgt[p][0]=sgt[p*2][0]+sgt[p*2+1][0];
    }
    long long getsum(int p,int s,int t,int l,int r) {
        if ((l<=s)&&(t<=r)) return sgt[p][0];
        pushdown(p,s,t);
        int mid=(s+t)/2;
        if (r<=mid) return getsum(p*2,s,mid,l,r);
        if (l>mid) return getsum(p*2+1,mid+1,t,l,r);
        return getsum(p*2,s,mid,l,r)+getsum(p*2+1,mid+1,t,l,r);
    }
}
void update_path(int u,int v,long long x) {
    int w=lca(u,v);
    while (dep[u]>=dep[w]) {
        if (dep[ktop[u]]<=dep[w]) {
            seg::update(1,1,n,dfnord[w],dfnord[u],x);
            break;
        }
        seg::update(1,1,n,dfnord[ktop[u]],dfnord[u],x);
        u=fa[ktop[u]];
    }
    while (dep[v]>=dep[w]) {
        if (dep[ktop[v]]<=dep[w]) {
            seg::update(1,1,n,dfnord[w],dfnord[v],x);
            break;
        }
        seg::update(1,1,n,dfnord[ktop[v]],dfnord[v],x);
        v=fa[ktop[v]];
    }
    seg::update(1,1,n,dfnord[w],dfnord[w],-x);
}
long long query_path(int u,int v) {
    int w=lca(u,v);
    long long res=0;
    while (dep[u]>=dep[w]) {
        if (dep[ktop[u]]<=dep[w]) {
            res+=seg::getsum(1,1,n,dfnord[w],dfnord[u]);
            break;
        }
        res+=seg::getsum(1,1,n,dfnord[ktop[u]],dfnord[u]);
        u=fa[ktop[u]];
    }
    while (dep[v]>=dep[w]) {
        if (dep[ktop[v]]<=dep[w]) {
            res+=seg::getsum(1,1,n,dfnord[w],dfnord[v]);
            break;
        }
        res+=seg::getsum(1,1,n,dfnord[ktop[v]],dfnord[v]);
        v=fa[ktop[v]];
    }
    res-=seg::getsum(1,1,n,dfnord[w],dfnord[w]);
    return res;
}
void update_sub(int v,int u,long long x) {
    int w=lca(v,u);
    if (w==u) {
        if (u==v) {
            seg::update(1,1,n,1,n,x);
            return;
        }
        while (dep[v]>dep[u]) {
            if (dep[ktop[v]]<=dep[u]+1) {
                v=klst[ktop[v]][dep[u]-dep[ktop[v]]+1];
                break;
            }
            v=fa[ktop[v]];
        }
        seg::update(1,1,n,1,n,x);
        seg::update(1,1,n,dfnord[v],dfnord[v]+sz[v]-1,-x);
    } else seg::update(1,1,n,dfnord[u],dfnord[u]+sz[u]-1,x);
}
long long query_sub(int v,int u) {
    int w=lca(v,u);
    if (w==u) {
        if (u==v) return seg::getsum(1,1,n,1,n);
        while (dep[v]>dep[u]) {
            if (dep[ktop[v]]<=dep[u]+1) {
                v=klst[ktop[v]][dep[u]-dep[ktop[v]]+1];
                break;
            }
            v=fa[ktop[v]];
        }
        return seg::getsum(1,1,n,1,n)-seg::getsum(1,1,n,dfnord[v],dfnord[v]+sz[v]-1);
    }
    return seg::getsum(1,1,n,dfnord[u],dfnord[u]+sz[u]-1);
}
int main() {
    scanf("%d",&n);
    for (int i=1;i<=n;i++) scanf("%lld",&a[i]);
    for (int i=2;i<=n;i++) {
        scanf("%d",&fa[i]);
        son[fa[i]].push_back(i);
    }
    dfs(1);dfs0(1);rt=1;
    for (int i=1;i<=n;i++) {
        if (ktop[i]==i) {
            for (int j=i;j;j=kson[j]) klst[i].push_back(j);
        }
    }
    for (int i=1;i<=n;i++) seg::update(1,1,n,dfnord[i],dfnord[i],a[i]);
    scanf("%d",&q);
    while (q--) {
        scanf("%d",&op);
        if (op==1) {
            scanf("%d",&x);
            rt=x;
        }
        if (op==2) {
            scanf("%d%d%d",&x,&y,&z);
            update_path(x,y,z);
        }
        if (op==3) {
            scanf("%d%d",&x,&y);
            update_sub(rt,x,y);
        }
        if (op==4) {
            scanf("%d%d",&x,&y);
            printf("%lld\n",query_path(x,y));
        }
        if (op==5) {
            scanf("%d",&x);
            printf("%lld\n",query_sub(rt,x));
        }
    }
    return 0;
}
