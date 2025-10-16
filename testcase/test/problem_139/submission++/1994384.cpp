#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
    int x=0;char s=getchar();
    bool f=true;
    for(;s<'0'||'9'<s;s=getchar()) if(s=='-') f=false;
    for(;'0'<=s&&s<='9';s=getchar()) x=(x<<1)+(x<<3)+(s^48);
    return f?x:~x+1;
}
#define read read()
void write1(int x){
    if(x>9) write1(x/10);
    putchar(x%10+48);
}
void write(int x){
    if(x<0) putchar('-'),x=~x+1;
    write1(x);
}
const int N=1e5+10;
int a[N],ch[N],depth[N],size[N],fa[N],son[N],dfn[N],top[N];
int n,m,tot;
namespace EDGE{
    struct node{
        int to,next;
    }edge[N<<1];
    int head[N],cnt;
    inline void add(int u,int v){
        edge[++cnt]={v,head[u]};
        head[u]=cnt;
    }
}using namespace EDGE;
namespace ST{
    struct SegmentTree{
        int l,r,sum,lazy;
        #define l(x) tree[x].l
        #define r(x) tree[x].r
        #define sum(x) tree[x].sum
        #define lazy(x) tree[x].lazy
        #define pushup(x) sum(x)=(sum(x<<1)+sum(x<<1|1))
    }tree[N<<2];
    inline void pushdown(int x){
        if(lazy(x)){
            lazy(x<<1)+=lazy(x);
            lazy(x<<1|1)+=lazy(x);
            sum(x<<1)+=(r(x<<1)-l(x<<1)+1)*lazy(x);
            sum(x<<1|1)+=(r(x<<1|1)-l(x<<1|1)+1)*lazy(x);
            lazy(x)=0;
        }
    }
    void build(int k,int l,int r){
        l(k)=l,r(k)=r;
        if(l==r){sum(k)=a[l];return;}
        int mid=(l+r)>>1;
        build(k<<1,l,mid);
        build(k<<1|1,mid+1,r);
        pushup(k);
    }
    void update(int k,int l,int r,int total){
        if(l<=l(k)&&r(k)<=r){
            sum(k)+=(r(k)-l(k)+1)*total;
            lazy(k)+=total;
            return;
        }
        pushdown(k);
        int mid=(l(k)+r(k))>>1;
        if(l<=mid) update(k<<1,l,r,total);
        if(r>mid) update(k<<1|1,l,r,total);
        pushup(k);
    }
    int query(int k,int l,int r){
        if(l<=l(k)&&r(k)<=r) return sum(k);
        pushdown(k);
        int mid=(l(k)+r(k))>>1,res=0;
        if(l<=mid) res+=query(k<<1,l,r);
        if(r>mid) res+=query(k<<1|1,l,r);
        return res;
    }
}using namespace ST;
void dfs1(int x){
    size[x]=1;
    for(int i=head[x];i;i=edge[i].next){
        int y=edge[i].to;
        if(y==fa[x]) continue;
        fa[y]=x; depth[y]=depth[x]+1;
        dfs1(y);
        size[x]+=size[y];
        if(size[y]>size[son[x]]) son[x]=y;
    }
}
void dfs2(int x,int t){
    a[++tot]=ch[x];
    dfn[x]=tot;
    top[x]=t;
    if(son[x]) dfs2(son[x],t);
    for(int i=head[x];i;i=edge[i].next){
        int y=edge[i].to;
        if(y==son[x]||y==fa[x]) continue;
        dfs2(y,y);
    }
}
inline void call1(int x,int y,int z){
    int fx=top[x],fy=top[y];
    while(fx!=fy){
        if(depth[fx]<depth[fy])
            swap(fx,fy),swap(x,y);
        update(1,dfn[fx],dfn[x],z);
        x=fa[fx];
        fx=top[x];
    }
    if(depth[x]>depth[y]) swap(x,y);
    update(1,dfn[x],dfn[y],z);
}
inline int call2(int x,int y){
    int fx=top[x],fy=top[y],res=0;
    while(fx!=fy){
        if(depth[fx]<depth[fy])
            swap(fx,fy),swap(x,y);
        res+=query(1,dfn[fx],dfn[x]);
        x=fa[fx];fx=top[x];
    }
    if(depth[x]>depth[y]) swap(x,y);
    res+=query(1,dfn[x],dfn[y]);
    return res;
}
inline int get_son(int x,int y){
    int fx=top[x],fy=top[y];
    while(fx!=fy){
        if(depth[fx]<depth[fy]) 
            swap(x,y),swap(fx,fy);
        if(fa[fx]==y) return fx;
        x=fa[fx];
        fx=top[x];
    }
    if(depth[x]>depth[y]) swap(x,y);
    return son[x];
}
signed main(){
    #ifndef ONLINE_JUDGE
        freopen("in.in","r",stdin);
        freopen("out.out","w",stdout);
    #endif
    n=read;
    for(int i=1;i<=n;++i) ch[i]=read;
    for(int i=2;i<=n;++i){
        int y=read;
        add(i,y);add(y,i);
    }
    dfs1(1);dfs2(1,1);build(1,1,tot);
    int m=read,root=1;
    while(m--){
        int op=read;
        if(op==1) root=read;
        else if(op==2){
            int u=read,v=read,k=read;
            call1(u,v,k);
        }
        else if(op==4){
            int u=read,v=read;
            write(call2(u,v));puts(" ");
        }
        else if(op==3){
            int x=read,k=read;
            if(x==root) update(1,1,n,k);
            else if(dfn[x]>dfn[root]||dfn[x]+size[x]-1<dfn[root])
                update(1,dfn[x],dfn[x]+size[x]-1,k);
            else{
                int y=get_son(x,root);
                if(dfn[y]+size[y]-1==n) update(1,1,dfn[y]-1,k);
                else{
                    update(1,1,dfn[y]-1,k);
                    update(1,dfn[y]+size[y],n,k);
                }
            }
        }
        else if(op==5){
            int x=read,ans=0;
            if(x==root) ans=query(1,1,tot);
            else if(dfn[x]>dfn[root]||dfn[x]+size[x]-1<dfn[root])
                ans=query(1,dfn[x],dfn[x]+size[x]-1);
            else{
                int y=get_son(x,root);
                if(dfn[y]+size[y]-1==n) ans=query(1,1,dfn[y]-1);
                else{
                    ans+=query(1,1,dfn[y]-1);
                    ans+=query(1,dfn[y]+size[y],tot);
                }
            }
            write(ans);puts(" ");
        }
    }
}