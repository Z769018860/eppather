#include<bits/stdc++.h>
#pragma GCC optimize ("Ofast")
using namespace std;
const int N=1e5+5,M=6e6+5;
int n,m,l,r,dep[N],cnt,tot=1,num,lim,s[M],dfn[M],low[M],sz[N],mx=1e9,rt,rtt[2],head[N],sum,id[M],ls[M],rs[M],p[N<<2][2][2];
bool v[N][5],vis[M];
vector<int>g[M],d[N],q;
struct o{
    int ne,to,dis;
}e[N<<1];
inline void ad(int x,int y,int k){
    e[++tot].ne=head[x];
    head[x]=tot;
    e[tot].to=y;
    e[tot].dis=k;
}
inline void add(int x,int y,int k){
    ad(x,y,k),ad(y,x,k);
}
inline void rebuild(int x,int fa){
    int lst=0;
    for(int to:g[x]){
        if(to==fa)continue;
        if(!lst)add(x,to,1),lst=x;
        else add(++cnt,to,1),add(lst,cnt,0),lst=cnt;
        rebuild(to,x);
    }
    g[x].clear();g[x].shrink_to_fit();
}
inline void dfs(int x,int fa){
    sz[x]=1;
    if(x<=n&&(n<=1000||v[x][4]))lim=max(lim,dep[x]),d[dep[x]].push_back(x),q.push_back(x);
    for(int i=head[x];i;i=e[i].ne){
        int to=e[i].to;
        if(to==fa||vis[i])continue;
        dep[to]=dep[x]+e[i].dis;
        dfs(to,x),sz[x]+=sz[to];
    }
}
inline void find(int x,int fa){
    for(int i=head[x];i;i=e[i].ne){
        int to=e[i].to;
        if(to==fa||vis[i])continue;
        if(max(sz[to],sum-sz[to])<mx)mx=max(sz[to],sum-sz[to]),rt=i;
        find(to,x);
    }
}
inline void build(int &x,int l,int r){
    x=++num;
    for(int i=0;i<2;i++)for(int j=0;j<2;j++)p[x][i][j]=++cnt;
    if(l==r){
        for(int to:d[l]){
            for(int i=0;i<2;i++){
                int y=to+i*n;
                for(int j=0;j<2;j++){
                    if(!j)g[p[x][i][j]].push_back(y);
                    else g[y].push_back(p[x][i][j]);
                }
            }
        }
        d[l].clear();d[l].shrink_to_fit();
        return;
    }
    int mid=(l+r)>>1;
    build(ls[x],l,mid),build(rs[x],mid+1,r);
    for(int i=0;i<2;i++){
        g[p[x][i][0]].push_back(p[ls[x]][i][0]),g[p[x][i][0]].push_back(p[rs[x]][i][0]);
        g[p[ls[x]][i][1]].push_back(p[x][i][1]),g[p[rs[x]][i][1]].push_back(p[x][i][1]);
    }
}
inline void link(int x,int l,int r,int ql,int qr,int k){
    if(l>qr||r<ql||ql>qr)return;
    if(l>=ql&&r<=qr){
        if(v[k][0])g[k+n].push_back(p[x][1][0]),g[p[x][0][1]].push_back(k);
        if(v[k][1])g[k+n].push_back(p[x][0][0]),g[p[x][1][1]].push_back(k);
        if(v[k][2])g[k].push_back(p[x][1][0]),g[p[x][0][1]].push_back(k+n);
        if(v[k][3])g[k].push_back(p[x][0][0]),g[p[x][1][1]].push_back(k+n);
        return;
    }
    int mid=(l+r)>>1;
    link(ls[x],l,mid,ql,qr,k),link(rs[x],mid+1,r,ql,qr,k);
}
inline void cal(int i){
    vis[i]=vis[i^1]=1;
    int x=e[i].to,y=e[i^1].to,k=e[i].dis;
    dep[x]=dep[y]=rtt[1]=rtt[0]=0;
    vector<int>q1,q2;
    lim=0;
    dfs(x,0);swap(q1,q);int l0=lim;
    num=0;
    build(rtt[0],0,l0);
    lim=0;
    dfs(y,0);swap(q2,q);int l1=lim;
    build(rtt[1],0,l1);
    for(int u:q1)link(rtt[1],0,l1,max(0,l-dep[u]-k),min(l1,r-dep[u]-k),u);
    for(int u:q2)link(rtt[0],0,l0,max(0,l-dep[u]-k),min(l0,r-dep[u]-k),u);
    if(sz[x]>1){
        mx=1e9,rt=0,sum=sz[x];
        find(x,0);
        cal(rt);
    }
    if(sz[y]>1){
        mx=1e9,rt=0,sum=sz[y];
        find(y,0);
        cal(rt);
    }
}
inline void tarjan(int x){
    s[++num]=x,dfn[x]=low[x]=++cnt,vis[x]=1;
    for(int to:g[x]){
        if(!dfn[to]){
            tarjan(to);
            low[x]=min(low[x],low[to]);
        }else if(vis[to])low[x]=min(low[x],dfn[to]);
    }
    if(low[x]==dfn[x]){
        sum++;
        while(s[num+1]!=x){
            vis[s[num]]=0,id[s[num]]=sum,num--;
        }
    }
}
namespace FAST_READ{
    const int MAX_BUF=1<<20;
    char buf[MAX_BUF+10],*p1=buf,*p2=buf;
    #define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,MAX_BUF,stdin),p1==p2)?EOF:*p1++)
    int rd(){
        int x=0;bool f=0;char ch=gc();
        while(ch<'0'||ch>'9')f|=ch=='-',ch=gc();
        while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=gc();
        return f?-x:x;
    }
}
using FAST_READ::rd;
signed main(){
    
    
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    n=rd(),m=rd(),l=rd(),r=rd();
    for(int i=1;i<n;i++){
        int x=rd(),y=rd();g[x].push_back(y),g[y].push_back(x);
    }
    while(m--){
        int x=rd(),op=rd();
        v[x][op]=v[x][4]=1;
    }
    cnt=n;
    rebuild(1,0);
    cnt=n+n;
    dfs(1,0);rt=0,mx=1e9,sum=n;find(1,0);
    for(int i=0;i<=lim;i++)d[i].clear(); 
    q.clear();cal(rt);
    for(int i=1;i<=tot;i++)vis[i]=0;
    int now=cnt;cnt=tot=num=sum=0;
    for(int i=1;i<=n;i++)if(!dfn[i])tarjan(i);
    for(int i=1;i<=n;i++){
        if(id[i]==id[i+n]){
            cout<<"NO";return 0;
        }
    }
    cout<<"YES";
    return 0;
}
