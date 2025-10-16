#include<bits/stdc++.h>
#define ll long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=1e3,Maxm=1e4,Maxk=1.2e6;
const ll inf=1e18;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

struct Node{int to,nxt,w,cst;} Edge[Maxm*2+5];
int tot=1,Head[Maxn+5],cur[Maxn+5];
inline void Addedge(int x,int y,int z,int w)
{
    Edge[++tot]=(Node){y,Head[x],z,w},Head[x]=tot;
    Edge[++tot]=(Node){x,Head[y],0,-w},Head[y]=tot;
}

int n,m,K,s,t,h1[35],h2[35],h3[35]; ll maxf,minc;
ll dis[Maxn+5]; int vis[Maxn+5];
queue<int> q;

inline int bfs()
{
    For(i,1,t) dis[i]=inf,vis[i]=0,cur[i]=Head[i];
    dis[s]=0,vis[s]=1,q.push(s);
    while(!q.empty())
    {
        int x=q.front(); q.pop(),vis[x]=0;
        for(int i=Head[x];i;i=Edge[i].nxt)
        {
            int y=Edge[i].to;
            if(Edge[i].w && dis[x]+Edge[i].cst<dis[y])
            {
                dis[y]=dis[x]+Edge[i].cst;
                if(!vis[y]) vis[y]=1,q.push(y);
            }
        }
    }
    return (dis[t]<inf);
}
inline int dfs(int x,int flow)
{
    if(vis[x]) return 0;
    if(x==t || !flow) {maxf+=flow; return flow;}
    int used=0,res=0; vis[x]=1;
    for(int i=cur[x];i && used<flow;i=Edge[i].nxt)
    {
        int y=Edge[i].to; cur[x]=i;
        if(Edge[i].w && dis[y]==dis[x]+Edge[i].cst)
            if(res=dfs(y,min(Edge[i].w,flow-used)))
            {
                used+=res,Edge[i].w-=res,Edge[i^1].w+=res;
                minc+=1ll*res*Edge[i].cst;
            }
    }
    vis[x]=0; return used;
}
inline void Init()
{
    static int A[Maxk+5],B[Maxk+5];
    n=read(); For(i,1,n) A[i]=read(); sort(A+1,A+n+1);
    m=read(); For(i,1,m) B[i]=read(); sort(B+1,B+m+1);
    K=read();
    For(i,1,n) h1[__builtin_ctz(A[i])]++;
    For(i,1,m) h2[__builtin_ctz(B[i])]++;
    for(int l=1,r,it1=0,it2=0;l<=n;l=r+1)
    {
        for(r=l;r<n && A[r+1]==A[l];++r);
        while(it1<m && B[it1+1]<A[l]) it1++;
        while(it2<m && B[it2+1]<=A[l]) it2++;
        if(B[it2]==A[l]) h3[__builtin_ctz(A[l])]+=min(it2-it1,r-l+1);
    }
}

int main()
{
    
    

    Init();
    s=31*3+1; int t1=s+1; t=t1+1;
    For(i,0,30)
    {
        Addedge(s,i+1,h1[i],0),Addedge(i+1,t,n+5,(1<<i));
        Addedge(i+1,31*2+i+1,h3[i],0);
    }
    For(i,1,30) Addedge(i+1,31+i,n+5,0);
    For(i,0,30) Addedge(31+i+1,31*2+i+1,h2[i],(1<<i));
    For(i,0,29) Addedge(31+i+2,31+i+1,n+5,0);
    For(i,0,30) Addedge(31*2+i+1,t1,h2[i],0);
    Addedge(t1,t,K,0);
    while(bfs()) dfs(s,int(1e9));
    cout<<minc<<endl;
    return 0;
}