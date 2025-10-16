#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=1e5,Maxk=1e6,inf=1e9;
const int dx[4]={0,1,0,-1},dy[4]={1,0,-1,0};

int n,m,ans; string ch[Maxn+5];
vector<int> id[Maxn+5];

struct Node{int frm,to,nxt,w;} Edge[Maxk*2+5];
struct Graph
{
    int s,t,vis[Maxk+5],dis[Maxk+5],maxf;
    int tot=1,Head[Maxk+5],cur[Maxk+5];
    inline void Addedge(int x,int y,int k)
    {
        Edge[++tot]=Node{x,y,Head[x],k},Head[x]=tot;
        Edge[++tot]=Node{y,x,Head[y],0ll},Head[y]=tot;
    }
    inline int bfs()
    {
        queue<int> q; For(i,1,t) dis[i]=vis[i]=0,cur[i]=Head[i];
        dis[s]=0,vis[s]=1,q.push(s);
        while(!q.empty())
        {
            int x=q.front(); q.pop();
            for(int i=Head[x];i;i=Edge[i].nxt)
            {
                int y=Edge[i].to;
                if(Edge[i].w && !vis[y])
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
    inline void Build()
    {
        s=n*m+1,t=n*m+2;
        For(i,1,n) For(j,1,m) if(ch[i][j]=='1' || ch[i][j]=='3')
        {
            if(i+j&1) Addedge(s,id[i][j],1);
            else Addedge(id[i][j],t,1);
            if(i+j&1)
            {
                For(k,0,3)
                {
                    int i1=i+dx[k],j1=j+dy[k];
                    if(i1<1 || i1>n || j1<1 || j1>m) continue;
                    if(ch[i1][j1]=='2' || ch[i1][j1]=='*') continue;
                    if(ch[i1][j1]==ch[i][j]) continue;
                    Addedge(id[i][j],id[i1][j1],1);
                }
            }
        }
        while(bfs()) dfs(s,inf); ans+=maxf;
    }
} G;

int main()
{
    
    
    cin>>n>>m; For(i,1,n) cin>>ch[i],ch[i]=' '+ch[i];
    For(i,0,n+1) id[i].resize(m+2);
    int tmp=0; For(i,1,n) For(j,1,m) id[i][j]=++tmp;
    For(i,1,n) For(j,1,m) if(ch[i][j]=='2') ans++;
    G.Build(),cout<<ans<<endl;
    return 0;
}