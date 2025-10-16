#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
bool mem1;
mt19937 rd(20080618);
struct Treap {
    int ls[N],rs[N],val[N],rk[N],sz[N],lz[N];
    int rt,tot;
    int st[N],top;
    void update(int x) { return sz[x]=sz[ls[x]]+sz[rs[x]]+1, void(); }
    void dfs(int x) {
        if(ls[x]) dfs(ls[x]);
        if(rs[x]) dfs(rs[x]);
        update(x);
    }
    void build(int n) {
        for(int i=1;i<=n;i++) {
            val[i]=i, rk[i]=rd();
            int p=0;
            while(top&&rk[st[top]]>rk[i]) p=st[top--];
            ls[i]=p;
            if(top) rs[st[top]]=i;
            st[++top]=i;
        }
        rt=st[1];
        dfs(rt);
    }
    void pushdown(int id) { 
        if(!lz[id]) return;
        swap(ls[id],rs[id]);
        lz[id]=0, lz[ls[id]]^=1, lz[rs[id]]^=1;
    }
    PII splitrk(int id,int v) {
        if(!id) return {0,0};
        pushdown(id);
        if(sz[ls[id]]>=v) {
            PII res=splitrk(ls[id],v);
            ls[id]=res.second, update(id);
            return {res.first,id};
        }
        else if(sz[ls[id]]+1==v) {
            int p=rs[id];
            rs[id]=0, update(id);
            return {id,p};
        }
        else {
            PII res=splitrk(rs[id],v-sz[ls[id]]-1);
            rs[id]=res.first, update(id);
            return {id,res.second};
        }
    }
    int merge(int x,int y) {
        if(!x||!y) return x+y;
        pushdown(x), pushdown(y);
        if(rk[x]<rk[y]) {
            rs[x]=merge(rs[x],y), update(x);
            return x;
        }
        else {
            ls[y]=merge(x,ls[y]), update(y);
            return y;
        }
    }
    int merge(int x,int y,int z) { return merge(merge(x,y),z); }
    void reverse(int l,int r) {
        PII res1=splitrk(rt,l-1), res2=splitrk(res1.second,r-l+1);
        lz[res2.first]^=1;
        rt=merge(res1.first,res2.first,res2.second);
    }
    void print(int id) {
        pushdown(id);
        if(ls[id]) print(ls[id]);
        cout<<val[id]<<" ";
        if(rs[id]) print(rs[id]);
    }
}t;
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int n,m;
    cin>>n>>m;
    t.build(n);
    for(int i=1,l,r;i<=m;i++) cin>>l>>r, t.reverse(l,r);
    t.print(t.rt), cout<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}