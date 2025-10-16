#include <iostream>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <set>
#include <map>
using namespace std;
typedef long long int ll;
const int N=1e6+9,INF=1e9;
const double eps=1e-5;
typedef pair <int,int> PII;
inline int read()
{
    int x=0,f=1;char c=getchar();
    while(c<'0' || c>'9') {if(c=='-') f=-1;c=getchar();}
    while(c>='0' && c<='9') {x=x*10+c-48,c=getchar();}
    return x*f;
}
inline ll readll()
{
    ll x=0,f=1;char c=getchar();
    while(c<'0' || c>'9') {if(c=='-') f=-1;c=getchar();}
    while(c>='0' && c<='9') {x=x*10+c-48,c=getchar();}
    return x*f;
}
struct node{
    int to,nxt;
} edge[N];
int n,tot,head[N],d[N],in[N],cnt,ans[N];
vector <int> g[N];
queue <int> q;
priority_queue <int,vector<int>,greater<int>> Q;
void addedge(int u,int v)
{
    edge[++tot].to=v,edge[tot].nxt=head[u],head[u]=tot;
}
void add(int x,int y)
{
    if(x==y) return;
    g[x].push_back(y),in[y]++;
}
int main()
{
    
    #ifdef FILEIO
        freopen("in.in","r",stdin);
        freopen("out.out","w",stdout);
    #endif
    n=read();
    if(n%2==1)
    {
        puts("-1");
        return 0;
    }
    for(int i=1;i<n;i++)
    {
        int u=read(),v=read();
        addedge(u,v),addedge(v,u);
        d[u]++,d[v]++;
    }
    for(int i=1;i<=n;i++)
        if(d[i]==1) q.push(i);
    while(q.empty()==false)
    {
        int u=q.front(),tmp=-1;
        q.pop();
        for(int i=head[u];i;i=edge[i].nxt)
        {
            int v=edge[i].to;
            if(d[v]>0) tmp=v,d[v]=0;
        }
        if(tmp==-1) continue;
        for(int i=head[u];i;i=edge[i].nxt)
        {
            int v=edge[i].to;
            add(tmp,v);
        }
        for(int i=head[tmp];i;i=edge[i].nxt)
        {
            int v=edge[i].to;
            add(u,v),d[v]--;
            if(d[v]==1) q.push(v);
        }
        ++cnt;
    }
    if(cnt!=n/2)
    {
        puts("-1");
        return 0;
    }
    for(int i=1;i<=n;i++)
        if(in[i]==0) Q.push(i);
    cnt=0;
    while(Q.empty()==false)
    {
        int u=Q.top();
        Q.pop();
        ans[++cnt]=u;
        for(int i=0;i<g[u].size();i++)
        {
            int v=g[u][i];
            in[v]--;
            if(in[v]==0) Q.push(v);
        }
    }
    if(cnt!=n)
    {
        puts("-1");
        return 0;
    }
    for(int i=1;i<=cnt;i++) cout<<ans[i]<<" ";
    cerr<<endl<<1e3*clock()/CLOCKS_PER_SEC<<"ms";
    return 0;
}