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
mt19937 rd(time(0));
struct Treap {
    int ls[N],rs[N],val[N],rk[N],sz[N];
    int rt,tot;
    void update(int x) { return sz[x]=sz[ls[x]]+sz[rs[x]]+1, void(); }
    int newnode(int v) { return tot++, val[tot]=v, rk[tot]=rd(), sz[tot]=1, tot; }
    PII splitv(int id,int v) {
        if(!id) return {0,0};
        if(val[id]<=v) {
            PII res=splitv(rs[id],v);
            rs[id]=res.first, update(id);
            return {id,res.second};
        }
        else {
            PII res=splitv(ls[id],v);
            ls[id]=res.second, update(id);
            return {res.first,id};
        }
    }
    int merge(int x,int y) {
        if(!x||!y) return x+y;
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
    void insert(int v) {
        PII res=splitv(rt,v);
        rt=merge(res.first,newnode(v),res.second);
    }
    void del(int v) {
        PII res1=splitv(rt,v-1), res2=splitv(res1.second,v);
        res2.first=merge(ls[res2.first],rs[res2.first]);
        rt=merge(res1.first,res2.first,res2.second);
    }
    int qrk(int v) {
        PII res=splitv(rt,v-1);
        int ans=sz[res.first]+1;
        rt=merge(res.first,res.second);
        return ans;
    }
    int qkth(int v) {
        int id=rt;
        while(1) {
            if(sz[ls[id]]+1==v) return val[id];
            if(sz[ls[id]]>=v) id=ls[id];
            else v-=sz[ls[id]]+1, id=rs[id];
        }
    }
    int qpre(int x) { return qkth(qrk(x)-1); }
    int qsub(int x) { return qkth(qrk(x+1)); }
}t;
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int T; cin>>T;
    while(T--) {
        int op,x;
        cin>>op>>x;
        if(op==1) t.insert(x);
        if(op==2) t.del(x);
        if(op==3) cout<<t.qrk(x)<<endl;
        if(op==4) cout<<t.qkth(x)<<endl;
        if(op==5) cout<<t.qpre(x)<<endl;
        if(op==6) cout<<t.qsub(x)<<endl;
    }

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}