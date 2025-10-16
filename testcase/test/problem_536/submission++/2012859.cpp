#include<bits/stdc++.h>
using namespace std;
char *p1,*p2,buf[2000000];
#define nc() (p1==p2 && (p2=(p1=buf)+fread(buf,1,2000000,stdin),p1==p2)?EOF:*p1++)
inline int read()
{
    int x=0,f=1;
    char ch=nc();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')f=-1;
        ch=nc();
    }
    while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=nc();
    return x*f;
}
const int N=4000005,M=4000005;
int nodecnt;


int edgenum=1,head[M],to[M],nxt[M],v[M];
int s,t;
int addedge(int x,int y,int z)
{
	to[++edgenum]=y;
	v[edgenum]=z;
	nxt[edgenum]=head[x];
	head[x]=edgenum;
	swap(x,y);
	to[++edgenum]=y;
	v[edgenum]=0;
	nxt[edgenum]=head[x];
	head[x]=edgenum;
    return edgenum-1;
}
int dep[4000005];
queue<int>que;


int now[4000005];
bool bfs()
{
	for(int i=1;i<=nodecnt;i++)dep[i]=1e9;
	while(!que.empty())que.pop();
	que.push(s);
	now[s]=head[s];
	dep[s]=1;
	while(!que.empty())
	{
		int x=que.front();
		que.pop();
        int cnt=0;
		for(int i=head[x];i;i=nxt[i])
		{
            cnt++;
			int y=to[i];
			if(!v[i])continue;
			if(dep[y]==1e9)
			{
				que.push(y);
				dep[y]=dep[x]+1;
				now[y]=head[y];
				if(y==t)return true;
			}
		}
	}
	return false;
}
int dinic(int x,int flow)
{
	if(x==t)return flow;
	int rest=flow;
	for(int i=now[x];i&&rest;i=nxt[i])
	{
		now[x]=i;
		int y=to[i];
		if(!v[i])continue;
		if(dep[y]!=dep[x]+1)continue;
		int k=dinic(y,min(rest,v[i]));
		if(k==0)dep[y]=1e9;
		v[i]-=k;
		v[i^1]+=k;
		rest-=k;
	}
	return flow-rest;
}


int mpnum[100005],mpcol[100005];
int mpn[400005],mpm[400005];
int num,col;
int n,m;
int S,T;
int rnk[N];
int ans[400005];
int main()
{
    
    num=read();
    col=read();
    S=++nodecnt,T=++nodecnt;
    s=S,t=T;
    for(int i=1;i<=num;i++)mpnum[i]=++nodecnt;
    for(int i=1;i<=col;i++)mpcol[i]=++nodecnt;
    n=read();
    for(int x,y,i=1;i<=n;i++)
    {
        x=read(),y=read();
        mpn[i]=++nodecnt;
        rnk[addedge(S,mpn[i],1)]=i;
        addedge(mpn[i],mpcol[y],1);
        addedge(mpn[i],mpnum[x],1);
    }
    m=read();
    for(int x,y,i=1;i<=m;i++)
    {
        x=read(),y=read();
        mpm[i]=++nodecnt;
        addedge(mpm[i],T,1);
        addedge(mpcol[y],mpm[i],1);
        addedge(mpnum[x],mpm[i],1);
    }
	while(bfs())dinic(s,1e9);
    for(int i=head[S];i;i=nxt[i])
    {
        
        if(rnk[i]&&!v[i]&&dep[to[i]]==1e9)ans[rnk[i]]=1;
    }
    for(int i=1;i<=n;i++)printf("%d\n",ans[i]);
    return 0;
}