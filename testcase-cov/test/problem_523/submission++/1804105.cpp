#include <bits/stdc++.h>

using namespace std;

const int maxn=1e6; 

int m,n,T; 
int a[maxn+5],b[maxn+5],U[maxn+5],V[maxn+5],W[maxn+5]; 
int ecnt; 
vector<pair<int,int>> g[maxn+5]; 
int vis[maxn+5],flg[maxn+5],bel[maxn+5],rev[maxn+5]; 
long long sumh[maxn+5][2],sumt[maxn+5];
int dfn[maxn+5],low[maxn+5],dcnt,dpre[maxn+5]; 
int blocnt,sta[maxn+5],top; 
int hashuan[maxn+5],rt[maxn+5],ish[maxn+5]; 

void dfs(int u,int preid) {
    vis[u]=1; 
    dfn[u]=++dcnt; dpre[dcnt]=u; 
    for (auto x:g[u]) {
        int v=x.first,id=x.second;
        bel[id]=blocnt; 
        if (v==u) {
            flg[id]=0;
            
            hashuan[blocnt]=1; 
            ish[u]=1;
        } else if (preid!=-1 && id==rev[preid]) {
            continue ; 
        } else if (vis[v]) {
            if (dfn[v]>dfn[u]) continue ; 
            for (int j=top;j>=1;j--) {
                int id=sta[j]; 
                flg[id]=0;
                flg[rev[id]]=1;
                ish[U[id]]=ish[V[id]]=1;
                if (U[id]==v) break ; 
                
                
            }
            hashuan[blocnt]=1; 
            flg[id]=0;
            flg[rev[id]]=1;
            
            
        } else {
            sta[++top]=id;
            dfs(v,id);
            top--;
        }
    }
    low[u]=dcnt; 
}

void dfs2(int u,int pre) {
    for (auto x:g[u]) {
        int v=x.first,id=x.second; 
        if (v==pre || ish[v]) continue ; 
        flg[id]=2,flg[rev[id]]=4;
        dfs2(v,u); 
    }
}

struct Seg {
    long long mx[maxn*4+5],tag[maxn*4+5];
    void seta(int p,long long d) {
        tag[p]+=d; 
        mx[p]+=d; 
    }
    void upd(int p) {
        mx[p]=max(mx[p+p],mx[p+p+1]); 
    }
    void push(int p) {
        if (tag[p]==0) return ;
        seta(p+p,tag[p]); 
        seta(p+p+1,tag[p]);
        tag[p]=0;
    }
    void modify(int p,int l,int r,int ql,int qr,long long d) {
        if (l==ql&&r==qr) {
            seta(p,d);
            return ; 
        }
        push(p); 
        int mid=(l+r)>>1;
        if (qr<=mid) modify(p+p,l,mid,ql,qr,d);
        else if (mid<ql) modify(p+p+1,mid+1,r,ql,qr,d);
        else modify(p+p,l,mid,ql,mid,d),modify(p+p+1,mid+1,r,mid+1,qr,d);
        upd(p); 
    }
    long long query(int p,int l,int r,int ql,int qr) {
        if (l==ql&&r==qr) return mx[p];
        push(p); 
        int mid=(l+r)>>1;
        if (qr<=mid) return query(p+p,l,mid,ql,qr);
        else if (mid<ql) return query(p+p+1,mid+1,r,ql,qr);
        else return max(query(p+p,l,mid,ql,mid),query(p+p+1,mid+1,r,mid+1,qr)); 
    }
} seg; 

long long ans; 
long long eachans[maxn+5]; 

void modify(int id,int w) {
    long long prew=W[id];
    W[id]=w;
    int b=bel[id];  
    ans-=eachans[b]; 
    if (flg[id]==0) {
        sumh[b][0]-=prew;
        sumh[b][0]+=w; 
        eachans[b]=max(sumh[b][0],sumh[b][1])+sumt[b]; 
        ans+=eachans[b]; 
    } else if (flg[id]==1) {
        sumh[b][1]-=prew;
        sumh[b][1]+=w; 
        eachans[b]=max(sumh[b][0],sumh[b][1])+sumt[b]; 
        ans+=eachans[b]; 
    } else if (flg[id]==2) {
        sumt[b]-=prew;
        sumt[b]+=w; 
        eachans[b]=max(sumh[b][0],sumh[b][1])+sumt[b]; 
        ans+=eachans[b]; 
    } else if (flg[id]==3) {
        int u=U[id],v=V[id]; 
        int lp=dfn[rt[b]],rp=low[rt[b]]; 
        if (dfn[u]<=dfn[v]) {
            if (lp<dfn[v]) seg.modify(1,1,n,lp,dfn[v]-1,w-prew); 
            if (low[v]<rp) seg.modify(1,1,n,low[v]+1,rp,w-prew); 
        } else {
            seg.modify(1,1,n,dfn[u],low[u],w-prew); 
        }
        eachans[b]=seg.query(1,1,n,lp,rp);
        ans+=eachans[b]; 
    }
    else ans+=eachans[b]; 
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>m>>n>>T; 
    for (int i=0;i<m;i++) cin>>a[i];
    for (int i=0;i<m;i++) {
        cin>>b[i];
        int u=(a[i]+b[i])%n;
        int v=(a[i]-b[i]+n)%n; 
        if (u>v) swap(u,v); 
        if (u==v) {
            ecnt++; 
            U[ecnt]=u,V[ecnt]=v;
            g[u].emplace_back(v,ecnt); 
            g[v].emplace_back(u,ecnt);
            rev[ecnt]=0;  
        } else {
            ecnt++;
            U[ecnt]=v,V[ecnt]=u;
            g[v].emplace_back(u,ecnt); 
            ecnt++;
            U[ecnt]=u,V[ecnt]=v; 
            g[u].emplace_back(v,ecnt); 
            rev[ecnt]=ecnt-1;
            rev[ecnt-1]=ecnt; 
        }
    }
    for (int i=1;i<=ecnt;i++) {
        flg[i]=-1; 
    }
    for (int i=0;i<n;i++) {
        if (!vis[i]) {
            ++blocnt; 
            rt[blocnt]=i;
            top=0; 
            dfs(i,-1);
        }
    }
    for (int i=0;i<n;i++) {
        if (ish[i]) dfs2(i,-1); 
    }
    for (int i=1;i<=ecnt;i++) {
        if (flg[i]==-1) {
            flg[i]=3; 
        }
        int w; 
        cin>>w; 
        modify(i,w); 
    }
    int q;
    cin>>q;
    long long lstans=ans; 
    cout<<lstans<<'\n'; 
    for (int i=1;i<=q;i++) {
        int x,v;
        cin>>x>>v;
        x=x-lstans*T,v=v-lstans*T; 
        modify(x,v);
        cout<<(lstans=ans)<<'\n'; 
    }
    return 0; 
}