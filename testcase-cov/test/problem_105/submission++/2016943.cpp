#include<bits/stdc++.h>
using namespace std;
namespace treap {
    int ls[105000],rs[105000],sz[105000],wgt[105000],tag[105000];
    void pushdown(int x) {
        if (!x||!tag[x]) return;
        swap(ls[x],rs[x]);
        if (ls[x]) tag[ls[x]]^=1;
        if (rs[x]) tag[rs[x]]^=1;
        tag[x]=0;
    }
    int merge(int x,int y) {
        pushdown(x);pushdown(y);
        if (!x||!y) return x+y;
        if (wgt[x]<wgt[y]) {
            rs[x]=merge(rs[x],y);
            sz[x]=1+sz[ls[x]]+sz[rs[x]];
            return x;
        }
        ls[y]=merge(x,ls[y]);
        sz[y]=1+sz[ls[y]]+sz[rs[y]];
        return y;
    }
    void split(int x,int d,int &u,int &v) {
        pushdown(x);
        if (!d) {
            u=0;v=x;
            return;
        }
        if (sz[x]==d) {
            u=x;v=0;
            return;
        }
        if (sz[ls[x]]<d) {
            split(rs[x],d-sz[ls[x]]-1,u,v);
            rs[x]=u;
            u=x;
            sz[u]-=sz[v];
            return;
        }
        split(ls[x],d,u,v);
        ls[x]=v;
        v=x;
        sz[v]-=sz[u];
    }
    void dbg(int x) {
        if (!x) return;
        cout<<x<<' '<<ls[x]<<' '<<rs[x]<<' '<<sz[x]<<' '<<wgt[x]<<' '<<tag[x]<<endl;
        dbg(ls[x]);
        dbg(rs[x]);
    }
    void dfs(int x) {
        pushdown(x);
        if (!x) return;
        dfs(ls[x]);
        printf("%d ",x);
        dfs(rs[x]);
    }
}
using treap::dbg;
int rt,n,m,l[105000],r[105000],ord[105000],sd,u,v,w;
int main() {
    scanf("%d%d",&n,&m);
    sd=n+m;
    for (int i=1;i<=m;i++) {
        scanf("%d%d",&l[i],&r[i]);
        sd^=(l[i]+r[i]+i);
    }
    mt19937 rnd(sd);
    for (int i=1;i<=n;i++) ord[i]=i;
    shuffle(ord+1,ord+1+n,rnd);
    for (int i=1;i<=n;i++) {
        treap::sz[i]=1;treap::wgt[i]=ord[i];
    }
    rt=1;
    for (int i=2;i<=n;i++) rt=treap::merge(rt,i);
    for (int i=1;i<=m;i++) {
        treap::split(rt,l[i]-1,u,v);
        treap::split(v,r[i]-l[i]+1,v,w);
        
        treap::tag[v]^=1;
        rt=treap::merge(treap::merge(u,v),w);
        
    }
    treap::dfs(rt);
    printf("\n");
    return 0;
}
