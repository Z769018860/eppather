#include<bits/stdc++.h>
using namespace std;
int n,m,u[1050000],v[1050000],w[1050000];
vector<int> ed[205000];
namespace heap {
    int sz,dist[1050000],ls[1050000],rs[1050000],val[1050000];
    int merge(int x,int y) {
        if (!x||!y) return x+y;
        if (w[val[x]]>w[val[y]]) swap(x,y);
        rs[x]=merge(rs[x],y);
        if (dist[ls[x]]<dist[rs[x]]) swap(ls[x],rs[x]);
        dist[x]=dist[rs[x]]+1;
        return x;
    }
    int newnode(int x) {
        sz++;
        dist[sz]=1;ls[sz]=rs[sz]=0;val[sz]=x;
        return sz;
    }
    int insert(int x,int y) {
        return merge(x,newnode(y));
    }
    int top(int x) {
        return val[x];
    }
    int pop(int x) {
        return merge(ls[x],rs[x]);
    }
}
int pq=0,f[1050000];
long long ans;
int main() {
    scanf("%d%d",&n,&m);
    for (int i=1;i<=m;i++) scanf("%d%d%d",&u[i],&v[i],&w[i]);
    for (int i=1;i<=m;i++) {
        ed[u[i]].push_back(i);
        ed[v[i]].push_back(i);
    }
    f[1]=1;
    for (auto cur:ed[1]) pq=heap::insert(pq,cur);
    for (int i=1;i<n;i++) {
        while (f[u[heap::top(pq)]]==f[v[heap::top(pq)]]) {
            pq=heap::pop(pq);
        }
        int tmp=heap::top(pq);
        pq=heap::pop(pq);
        ans+=w[tmp];
        if (f[u[tmp]]<f[v[tmp]]) swap(u[tmp],v[tmp]);
        f[v[tmp]]=1;
        for (auto cur:ed[v[tmp]]) if (!f[u[cur]+v[cur]-v[tmp]]) pq=heap::insert(pq,cur);
    }
    printf("%lld\n",ans);
    return 0;
}
