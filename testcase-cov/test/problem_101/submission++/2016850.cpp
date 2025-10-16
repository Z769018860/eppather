#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e2+10;
const int M=5e3+10;
bool mem1;
int n,m,s,t,head[N],tot=1;
struct Edge {
    int to,nxt,w;
}eg[M<<1];
void Add(int x,int y,int w) {
    eg[++tot]={y,head[x],w}, head[x]=tot;
    eg[++tot]={x,head[y],0}, head[y]=tot;
}
int dis[N],vis[N],cur[N];
bool bfs() {
    memcpy(cur,head,sizeof(cur));
    memset(dis,0x3f,sizeof(dis));
    memset(vis,0,sizeof(vis));
    queue<int> q; 
    dis[s]=0, vis[s]=1, q.push(s);
    while(q.size()) {
        int x=q.front(); q.pop();
        vis[x]=0;
        for(int i=head[x];i;i=eg[i].nxt) {
            int y=eg[i].to;
            if(dis[y]>dis[x]+1&&eg[i].w) {
                dis[y]=dis[x]+1;
                if(!vis[y]) vis[y]=1, q.push(y);
            }
        }
    }
    return (dis[t]!=0x3f3f3f3f);
}
int dfs(int x,int f) {
    if(x==t||!f) return f;
    int use=0;
    for(int i=cur[x];i&&f;i=eg[i].nxt) {
        cur[x]=i;
        int y=eg[i].to;
        if(dis[y]!=dis[x]+1||!eg[i].w||vis[y]) continue;
        int c=dfs(y,min(f,eg[i].w));
        if(!c) {vis[y]=1; continue;}
        use+=c, eg[i].w-=c, eg[i^1].w+=c, f-=c;
    }
    return use;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m>>s>>t;
    for(int i=1,x,y,w;i<=m;i++) {
        cin>>x>>y>>w;
        Add(x,y,w);
    }
    ll ans=0;
    while(bfs()) ans+=dfs(s,INT_MAX);
    cout<<ans<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}