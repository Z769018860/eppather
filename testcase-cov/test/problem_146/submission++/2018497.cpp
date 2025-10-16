#include<cstdio>
#define it register int
#define il inline
const int N=8000005;
typedef long long ll;
int h[N],nxt[N],adj[N],opt,l[N],r[N],s[N],id[N],root,u,v,k,d[N],n,m,fa[N],top[N],w[N],son[N],t,cnt,lc;
ll ans,ww[N],c1[N],c2[N];
namespace io {
    const int SIZE = (1 << 21) + 1;
    char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55];
    int f, qr;
#define gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
    inline void flush () {
        fwrite (obuf, 1, oS - obuf, stdout);
        oS = obuf;
    }
    inline void putc (char x) {
        *oS ++ = x;
        if (oS == oT) flush ();
    }
    template<class T>
    inline void getc(T &x)
    {
        for(c=gc();!((c>='a'&&c<='z')||(c>='A'&&c<='Z'));c=gc());
        x=c;
    }
    template <class I>
    inline void fr (I &x) {
        for (f = 1, c = gc(); c < '0' || c > '9'; c = gc()) if (c == '-') f = -1;
        for (x = 0; c <= '9' && c >= '0'; c = gc()) x = x * 10 + (c & 15);
        x *= f;
    }
    template <class I>
    inline void print (I x) {
        if (!x) putc ('0');
        if (x < 0) putc ('-'), x = -x;
        while (x) qu[++ qr] = x % 10 + '0',  x /= 10;
        while (qr) putc (qu[qr --]);
    }
    struct Flusher_ {
        ~Flusher_() {
            flush();
        }
    } io_flusher_;
}
using io :: fr;
using io :: putc;
using io :: print;
using io :: getc;
il void Add(){
    nxt[++t]=h[u],h[u]=t,adj[t]=v,nxt[++t]=h[v],h[v]=t,adj[t]=u;
}
il void DFS(it x){
    s[x]=1,d[x]=d[fa[x]]+1,l[x]=++cnt,ww[x]=w[x];
    for(it i=h[x];i;i=nxt[i])
        if(adj[i]!=fa[x]){
            fa[adj[i]]=x,DFS(adj[i]),s[x]+=s[adj[i]],ww[x]+=ww[adj[i]];
            if(s[adj[i]]>s[son[x]])
                son[x]=adj[i];
        }
    r[x]=cnt;
}
il void dfs(it x){
    if(!top[x]) top[x]=x;
    if(!son[x]) return;
    top[son[x]]=top[x],dfs(son[x]);
    for(it i=h[x];i;i=nxt[i])
        if(adj[i]!=fa[x]&&adj[i]!=son[x]) dfs(adj[i]);
}
il void sp(int &p,int &q){
    p+=q,q=p-q,p-=q;
}
il void lca(){
    it p=u,q=v;
    while(top[p]!=top[q]){
        if(d[top[p]]<d[top[q]]) sp(p,q);
        p=fa[top[p]];
    }
    lc=d[p]<d[q]?p:q;
}
il ll cal(ll *t,it x){
    ll now=0;
    while(x) now+=t[x],x-=(x&-x);
    return now;
}
il void add(ll *t,it x,ll num){
    while(x<=n) t[x]+=num,x+=(x&-x);
}
il ll q(ll *t,it l,it r){
    return cal(t,r)-cal(t,l-1);
}
il void ins(it x){
    add(c1,l[x],k),add(c2,l[x],1ll*k*d[x]);
}
il void del(it x){
    add(c1,l[x],-k),add(c2,l[x],-1ll*k*d[x]);
}
int main(){
    fr(n),fr(m),fr(root);
    for(it i=1;i<=n;++i) fr(w[i]);
    for(it i=1;i<n;++i) fr(u),fr(v),Add();
    DFS(root),dfs(root);
    while(m--){
        fr(opt),fr(u);
        if(opt==1){
            fr(v),fr(k),lca();
            ins(u),ins(v),del(lc);
            if(fa[lc]) del(fa[lc]);
        }
        if(opt==2) printf("%lld\n",q(c1,l[u],r[u])+w[u]);
        if(opt==3) printf("%lld\n",q(c2,l[u],r[u])+1ll*q(c1,l[u],r[u])*(1-d[u])+ww[u]);
    }
    return 0;
}