#include<bits/stdc++.h>
#define lowbit(x) (x&-x)
#define ls(p) (p<<1)
#define rs(p) (p<<1|1)
#define Swap(x,y) (x^=y,y^=x,x^=y)
#define MAXP (105)
#define MAXI (405)
#define MAXN (505)
#define MAXM (90005)
#define INF (10000000000000000ll)
#define Add(u,v,w) add(u,v,w),add(v,u,0)
#define ll long long
using namespace std;
void File()
{
    freopen("data.in","r",stdin);
    freopen("data.out","w",stdout);
}
template<typename type>
void read(type &x)
{
    bool f=0;char ch=0;x=0;
    while(ch<'0'||ch>'9'){f|=!(ch^'-');ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    x=f?-x:x;
}
template<typename type,typename... Args>
void read(type &x,Args &... args)
{
    read(x);
    read(args...);
}
int cnt=1;
int head[MAXN],to[MAXM<<1],nxt[MAXM<<1];
ll cap[MAXM<<1];
void add(int u,int v,ll w)
{
    nxt[++cnt]=head[u],head[u]=cnt;
    to[cnt]=v,cap[cnt]=w;
}
int n,m,s,t;
int dis[MAXN],cur[MAXN];
queue<int> q;
bool BFS()
{
    while(!q.empty()) q.pop();
    q.push(s);
    memset(dis,-1,sizeof(dis));
    dis[s]=0;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(int i=head[u];i;i=nxt[i])
        {
            int v=to[i];
            if((!(~dis[v]))&&cap[i])
            {
                dis[v]=dis[u]+1;
                q.push(v);
            }
        }
    }
    return ~dis[t];
}
ll dfs(int u,ll flow)
{
    if(!(u^t)) return flow;
    ll rst=flow;
    for(int &i=cur[u];i;i=nxt[i])
    {
        int v=to[i];
        if((!(dis[v]^(dis[u]+1)))&&cap[i]>0)
        {
            ll ret=dfs(v,min(rst,cap[i]));
            rst-=ret;
            cap[i]-=ret;
            cap[i^1]+=ret;
            if(!rst) break;
        }
    }
    return flow-rst;
}
ll Dinic()
{
    ll Flow=0;
    while(BFS())
    {
        for(int i=1;i<=n;i++)
            cur[i]=head[i];
        Flow+=dfs(s,INF);
    }
    return Flow;
}
bool et[MAXI];
int test,N,M,lim;
int px[MAXP],py[MAXP],pw[MAXP],pr[MAXP],ix[MAXI],iy[MAXI],iw[MAXI];
ll sumf;
ll dist(ll a,ll b,ll c,ll d){return (a-c)*(a-c)+(b-d)*(b-d);}
bool build()
{
    sumf=0,cnt=1;
    memset(head,0,sizeof(head));
    memset(et,0,sizeof(et));
    read(N,M);
    for(int i=1;i<=N;i++) read(px[i],py[i],pw[i],pr[i]);
    for(int i=1;i<=M;i++) read(ix[i],iy[i],iw[i]);
    lim=pw[1];
    for(int i=1;i<=M;i++)
    {
        if(dist(px[1],py[1],ix[i],iy[i])<=1ll*pr[1]*pr[1])
        {
            lim+=iw[i];
            et[i]=1;
        }
    }
    s=N+M,t=N+M+1,n=N+M+1;
    for(int i=1;i<=M;i++)
    {
        if(!et[i])
        {
            Add(i+N-1,t,iw[i]);
            for(int j=1;j<=N;j++)
            {
                if(dist(px[j],py[j],ix[i],iy[i])<=1ll*pr[j]*pr[j])
                {
                    sumf+=iw[i];
                    break;
                }
            }
        }
    }
    for(int i=2;i<=N;i++)
    {
        if(lim-pw[i]<0) return 0;
        Add(s,i,lim-pw[i]);
        for(int j=1;j<=M;j++)
            if(!et[j])
                if(dist(px[i],py[i],ix[j],iy[j])<=1ll*pr[i]*pr[i])
                    Add(i,j+N-1,INF);
    }
    return (Dinic()^sumf)?0:1;
}
int main()
{
    
    read(test);
    for(int tq=1;tq<=test;tq++) printf("%s\n",build()?"ZQC! ZQC!":"qaq");
}