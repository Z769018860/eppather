#include<bits/stdc++.h>
using namespace std;

#define int long long

const int N=5e5+1e3+7;

int n,m,r,st[N],ed[N],dc,top[N],dep[N],sz[N],son[N],fa[N],a[N];

struct BIT {
    int a[N], b[N];
    inline void _Add(int x, int y) {
        for (int i = x; i <= n; i += i & -i) {
            a[i] += y;
            b[i] += y * (x - 1);
        }
    }
    inline int _Ask(int x) {
        int t0 = 0, t1 = 0;
        for (int i = x; i; i -= i & -i) t0 += a[i], t1 += b[i];
        return x * t0 - t1;
    }
    inline void Add(int x, int y, int z) {
        _Add(x, z); _Add(y + 1, -z);
    }
    inline int Ask(int x, int y) {
        return _Ask(y) - _Ask(x - 1);
    }
}T;

vector<int> g[N];

int rev[N];

void dfs1(int x) {
    sz[x]=1;
    for(auto v:g[x]) {
        if(v==fa[x])
            continue;
        dep[v]=dep[x]+1;
        fa[v]=x;
        dfs1(v);
        sz[x]+=sz[v];
        if(sz[v]>sz[son[x]])
            son[x]=v;
    }
}

void dfs2(int x) {
    st[x]=ed[x]=++dc,rev[dc]=x;
    T.Add(dc,dc,a[x]);
    if(!son[x])
        return;
    top[son[x]]=top[x];
    dfs2(son[x]);
    for(auto v:g[x]) {
        if(v==fa[x]||v==son[x])
            continue;
        top[v]=v;
        dfs2(v);
    }
    ed[x]=dc;
}

void change(int x,int y,int v) {
    while(top[x]!=top[y]) {
        if(dep[top[x]]<dep[top[y]])
            swap(x,y);
        T.Add(st[top[x]],st[x],v);
        x=fa[top[x]];
    }
    dep[x]<dep[y]?T.Add(st[x],st[y],v):T.Add(st[y],st[x],v);
}

int qry(int x,int y) {
    int ret=0;
    while(top[x]!=top[y]) {
        if(dep[top[x]]<dep[top[y]])
            swap(x,y);
        ret+=T.Ask(st[top[x]],st[x]);
        x=fa[top[x]];
    }
    ret+=dep[x]<dep[y]?T.Ask(st[x],st[y]):T.Ask(st[y],st[x]);
    return ret;
}

int getp(int x,int y) {
    int last;
    while(top[y]!=top[x])
        last=top[y],y=fa[top[y]];
    if(y!=x) return rev[st[x]+1];
    else return last;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    for(int i=2;i<=n;i++)
    {
        int u;
        cin>>u;
        g[u].push_back(i);
    }
    r=1;
    dfs1(1);
    top[1]=1;
    dfs2(1);
    cin>>m;
    while(m--)
    {
        int op;
        cin>>op;
        if(op==1)
            cin>>r;
        else if(op==2)
        {
            int u,v,w;
            cin>>u>>v>>w;
            change(u,v,w);
        }
        else if(op==3)
        {
            int u,v;
            cin>>u>>v;
            if(u==r)
                T.Add(1,n,v);
            else if(st[u]<=st[r]&&st[r]<=ed[u]) {
                int p=getp(u,r);
                T.Add(1,n,v);
                T.Add(st[p],ed[p],-v);
            } else {
                T.Add(st[u],ed[u],v);
            }
        }
        else if(op==4)
        {
            int u,v;
            cin>>u>>v;
            cout<<qry(u,v)<<"\n";
        }
        else
        {
            int u;
            cin>>u;
            int ans=0;
            if(u==r)
                ans=T.Ask(1,n);
            else if(st[u]<=st[r]&&st[r]<=ed[u]) {
                int p=getp(u,r);
                ans+=T.Ask(1,n);
                ans-=T.Ask(st[p],ed[p]);
            } else {
                ans=T.Ask(st[u],ed[u]);
            }
            cout<<ans<<"\n";
        }
    }
}