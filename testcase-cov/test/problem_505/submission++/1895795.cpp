#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int N=605;
const int inf=0x3f3f3f3f;
int n,m,s,t,ans,last[N],cur[N],cnt,dis[N];
struct data{int x,y,w,r;}c[N],pts[N];
struct edge{int to,next,c;}e[N*N*2];
queue<int> que;
int read(){int x=0,f=1;char ch=getchar();while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
void clear(){memset(last,0,sizeof(last));cnt=1;}
bool check(int i,int j){if ((pts[i].x-c[j].x)*(pts[i].x-c[j].x)+(pts[i].y-c[j].y)*(pts[i].y-c[j].y)<=c[j].r*c[j].r) return 1;else return 0;}
void addedge(int u,int v,int c){e[++cnt].to=v;e[cnt].c=c;e[cnt].next=last[u];last[u]=cnt;e[++cnt].to=u;e[cnt].c=0;e[cnt].next=last[v];last[v]=cnt;}
bool bfs(){
    for (int i=s;i<=t;i++) dis[i]=0;
    while (!que.empty()) que.pop();
    que.push(s);dis[s]=1;
    while (!que.empty()){
        int u=que.front();que.pop();
        for (int i=last[u];i;i=e[i].next)
            if (e[i].c&&!dis[e[i].to]){
                dis[e[i].to]=dis[u]+1;
                if (e[i].to==t) return 1;
                que.push(e[i].to);
            }
    }
    return 0;
}
int dfs(int x,int maxf){
    if (x==t||!maxf) return maxf;
    int ret=0;
    for (int &i=cur[x];i;i=e[i].next)
        if (e[i].c&&dis[e[i].to]==dis[x]+1){
            int f=dfs(e[i].to,min(e[i].c,maxf-ret));
            e[i].c-=f;e[i^1].c+=f;ret+=f;
            if (maxf==ret) break;
        }
    return ret;
}
void dinic()
{
    ans=0;
    while (bfs())
    {
        for (int i=s;i<=t;i++) cur[i]=last[i];
        ans+=dfs(s,inf);
    }
}

int main()
{
    int T=read();
    while (T--)
    {
        clear();
        n=read();m=read();
        for (int i=1;i<=n;i++) c[i].x=read(),c[i].y=read(),c[i].w=read(),c[i].r=read();
        for (int i=1;i<=m;i++)
        {
            pts[i].x=read();pts[i].y=read();pts[i].w=read();
            if (check(i,1)) c[1].w+=pts[i].w,i--,m--;
            else
            {
                int flag=0;
                for (int j=2;j<=n;j++)
                    if (check(i,j))
                    {
                        flag=1;break;
                    }
                if (!flag) i--,m--;
            }
        }
        s=0;t=n+m+1;
        int flag=0;
        for (int i=2;i<=n;i++)
        {
            if (c[i].w>c[1].w)
            {
                puts("qaq");flag=1;
                break;
            }
            addedge(s,i,c[1].w-c[i].w);
        }
        if (flag) continue;
        int tot=0;
        for (int i=1;i<=m;i++) addedge(i+n,t,pts[i].w),tot+=pts[i].w;
        for (int i=2;i<=n;i++)
            for (int j=1;j<=m;j++)
                if (check(j,i)) addedge(i,j+n,inf);
        dinic();
        if (ans==tot) puts("ZQC! ZQC!");
        else puts("qaq");
    }
    return 0;
}