#include <cstdio>
#define N 200010
#define M 2000010
int head[N];
struct edge {int v,c,nxt;}e[M]; int cur=2;
void ins(int u,int v,int w)
{
	e[cur]={v,w,head[u]}; head[u]=cur++;
	e[cur]={u,0,head[v]}; head[v]=cur++;
}
int dis[N];
bool bfs(int S,int T)
{
	static int q[N]; int tail=0;
	for(int i=1;i<=T;i++) dis[i]=-1;
	dis[q[tail++]=S]=0;
	for(int i=0;i!=tail;i++)
	{
		for(int x=q[i],j=head[x];j;j=e[j].nxt) if(e[j].c&&dis[e[j].v]==-1)
		{
			dis[q[tail++]=e[j].v]=dis[x]+1;
		}
	}
	return dis[T]!=-1;
}
int dfs(int S,int T,int flow)
{
	if(S==T||!flow) return flow;
	int ans=0;
	for(int i=head[S];i;i=e[i].nxt) if(dis[e[i].v]==dis[S]+1)
	{
		int t=dfs(e[i].v,T,e[i].c<flow?e[i].c:flow);
		e[i].c-=t, e[i^1].c+=t, flow-=t, ans+=t;
	}
	if(!ans) dis[S]=-1;
	return ans;
}
int ans=0;
int n,m; char last[N],s[N];
int S,T;
int calc(int x,int y) {return (x-1)*m+y;}
int main()
{
	scanf("%d%d",&n,&m);
	S=calc(n,m)+1,T=calc(n,m)+2;
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s+1);
		for(int j=1;j<=m;j++)
		{
			if(s[j]=='1') ins(S,calc(i,j),1);
			if(s[j]=='2') ans++;
			if(s[j]=='3') ins(calc(i,j),T,1);

			if(s[j]=='1'&&s[j-1]=='3') ins(calc(i,j),calc(i,j-1),1);
			if(s[j]=='3'&&s[j-1]=='1') ins(calc(i,j-1),calc(i,j),1);

			if(s[j]=='1'&&last[j]=='3') ins(calc(i,j),calc(i-1,j),1);
			if(s[j]=='3'&&last[j]=='1') ins(calc(i-1,j),calc(i,j),1);
		}
		for(int j=1;j<=m;j++) last[j]=s[j];
	}
	while(bfs(S,T)) ans+=dfs(S,T,0x3f3f3f3f);
	printf("%d",ans);
}