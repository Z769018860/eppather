#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=5e5,inf=1e9;

struct Node{int frm,to,nxt; int w;} Edge[Maxn*2+5];
int tot=1,Head[Maxn+5],cur[Maxn+5];
inline void Addedge(int x,int y,int k)
{
    Edge[++tot]=Node{x,y,Head[x],k},Head[x]=tot;
    Edge[++tot]=Node{y,x,Head[y],0ll},Head[y]=tot;
}

int n1,n2,m1,m2,s,t,tmp;
int id1[Maxn+5],id2[Maxn+5];
int vis[Maxn+5],dis[Maxn+5],maxf;

inline int bfs()
{
    queue<int> q; For(i,1,tmp) dis[i]=vis[i]=0,cur[i]=Head[i];
    dis[s]=0,vis[s]=1,q.push(s);
    while(!q.empty())
    {
        int x=q.front(); q.pop();
        for(int i=Head[x];i;i=Edge[i].nxt)
        {
            int y=Edge[i].to; if(Edge[i].w && !vis[y])
                dis[y]=dis[x]+1,vis[y]=1,q.push(y);
        }
    } return vis[t];
}
inline int dfs(int x,int flow)
{
    if(!flow || x==t) {maxf+=flow; return flow;}
    int used=0,res=0;
    for(int i=cur[x];i && used<flow;i=Edge[i].nxt)
    {
        int y=Edge[i].to; cur[x]=i;
        if(dis[y]==dis[x]+1 && Edge[i].w)
            if(res=dfs(y,min(flow-used,Edge[i].w)))
                used+=res,Edge[i].w-=res,Edge[i^1].w+=res;
    } return used;
}
inline void dfs(int x)
{
    vis[x]=1;
    for(int i=Head[x];i;i=Edge[i].nxt) if(Edge[i].w)
    {
        int y=Edge[i].to; if(y==s || y==t) continue;
        if(!vis[y]) dfs(y);
    }
}

int main()
{
    

    cin>>m1>>m2>>n1; s=1,t=2,tmp=2;
    For(i,1,m1) id1[i]=++tmp;
    For(i,1,m2) id2[i]=++tmp;
    For(i,1,n1)
    {
        Addedge(s,++tmp,1); int x,y; cin>>x>>y;
        Addedge(tmp,id1[x],1),Addedge(tmp,id2[y],1);
    } cin>>n2;
    For(i,1,n2)
    {
        Addedge(++tmp,t,1); int x,y; cin>>x>>y;
        Addedge(id1[x],tmp,1),Addedge(id2[y],tmp,1);
    }
    while(bfs()) dfs(s,inf);
    memset(vis,0,sizeof(vis));
    for(int i=Head[s];i;i=Edge[i].nxt) if(Edge[i].w)
        {int y=Edge[i].to; if(vis[y]) continue; dfs(y);}
    vector<int> ans;
    for(int i=Head[s];i;i=Edge[i].nxt)
    {
        if(vis[Edge[i].to]) ans.push_back(1);
        else ans.push_back(0);
    }
    reverse(ans.begin(),ans.end());
    for(auto i:ans) printf("%d\n",i^1);
    return 0;
}