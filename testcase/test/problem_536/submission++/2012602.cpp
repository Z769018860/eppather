#include<bits/stdc++.h>

using namespace std;
int n,m,s,t,dis[100005],k,c,tot,ans[40005],num[60005];
struct ss{
	int v,nxt,w;
}q[1000005];
int head[1000005],cnt=1;
inline int read(){
   int s=0, w=1;
   char ch = getchar();
   while (ch < '0' || ch > '9') {if (ch == '-') w = -1; ch = getchar();}
   while (ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
   return s * w;
}

inline void put(int x){
   if(!x)putchar('0');
   if(x<0)putchar('-'),x=-x;
   int num(0);char c[66];
   while(x)c[++ num]=x%10+48,x/=10;
   while(num)putchar(c[num --]);
   return (void)(putchar('\n'));
}
bool bfs()
{
	for(int i=0;i<=tot;i++)	dis[i] = 0;
	queue<int>qq; qq.push( s );
	dis[s] = 1;
	while( !qq.empty() )
	{
		int u = qq.front(); qq.pop();
		for(int i=head[u];i;i=q[i].nxt )
		{
			int v = q[i].v;
			if( dis[v]==0&&q[i].w )
			{
				dis[v] = dis[u]+1;
				if( v==t )	return true;
				qq.push( v );
			}
		}
	}
	return false;
}
int dfs(int u,int flow)
{
	if( u==t )	return flow;
	int res = flow;
	for(int i=head[u];i&&res;i=q[i].nxt )
	{
		int v = q[i].v;
		if( q[i].w&&dis[v]==dis[u]+1 )
		{
			int temp = dfs(v,min(res,q[i].w));
			if( temp==0 )	dis[v] = 0;
			res-=temp;
			q[i].w-=temp, q[i^1].w+=temp;
		}
	}
	return flow-res;
}
int dinic(){
	int maxn=0;
	while(bfs()){
		maxn+=dfs(s,1e9);
	}	
	return maxn;
}
void add(int u,int v,int w){
	q[++cnt]=ss{v,head[u],w};head[u]=cnt;
	q[++cnt]=ss{u,head[v],0};head[v]=cnt;
}
signed main(){
	k=read(),c=read();tot=k+c;
	n=read();
	s=++tot,t=++tot;
	for(int i=1;i<=n;i++){
		int w1,w2;w1=read(),w2=read();tot++;
		num[tot]=i;
		add(s,tot,1);add(tot,w1,1);add(tot,w2+k,1);
	}
	m=read();
	for(int i=1;i<=m;i++){
		int w1,w2;w1=read(),w2=read();tot++;
		add(w1,tot,1);add(w2+k,tot,1);add(tot,t,1);
	}
	dinic();
	for(int i=head[s];i;i=q[i].nxt){
		int v=q[i].v;
		if(!q[i].w&&!dis[v])ans[num[v]]=1;
	}
	for(int i=1;i<=n;i++)put(ans[i]);
}