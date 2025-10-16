#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+10;
const int inf = 1e9;
int n1,n2,s,t,id,m,c; 
int ans[maxn],num[maxn],dis[maxn];
struct edge{
	int to,nxt,flow;
}d[maxn]; int head[maxn],cnt=1;
void add(int u,int v,int flow)
{
	d[++cnt] = (edge){v,head[u],flow},head[u]=cnt;
	d[++cnt] = (edge){u,head[v],0},head[v] = cnt;
}
bool bfs(int u,int t)
{
	for(int i=0;i<=id;i++)	dis[i] = 0;
	queue<int>q; q.push( s );
	dis[s] = 1;
	while( !q.empty() )
	{
		int u = q.front(); q.pop();
		for(int i=head[u];i;i=d[i].nxt )
		{
			int v = d[i].to;
			if( dis[v]==0&&d[i].flow )
			{
				dis[v] = dis[u]+1;
				if( v==t )	return true;
				q.push( v );
			}
		}
	}
	return false;
}
int dinic(int u,int flow)
{
	if( u==t )	return flow;
	int res = flow;
	for(int i=head[u];i&&res;i=d[i].nxt )
	{
		int v = d[i].to;
		if( d[i].flow&&dis[v]==dis[u]+1 )
		{
			int temp = dinic(v,min(res,d[i].flow));
			if( temp==0 )	dis[v] = 0;
			res-=temp;
			d[i].flow-=temp, d[i^1].flow+=temp;
		}
	}
	return flow-res;
}
int MAXFLOW(int u,int t)
{
	int ans = 0;
	while( bfs(s,t) )	ans += dinic(s,inf);
	return ans;	
} 
int main()
{
	cin >> m >> c;
	id = m+c;
	s = ++id, t = ++id;
	cin >> n1;
	for(int i=1;i<=n1;i++)
	{
		int x,y; cin >> x >> y;
		add( s,++id,1 );
		add( id,x,1 );
		add( id,m+y,1 );
		num[ id ] = i; 
	}
	cin >> n2;
	for(int i=1;i<=n2;i++)
	{
		int x,y; cin >> x >> y;
		add( x, ++id, 1 );
		add( y+m,id,1 );
		add( id,t,1 );
	}
	MAXFLOW(s,t);
	for(int i=head[s];i;i=d[i].nxt )
	{
		if( !d[i].flow&&dis[d[i].to]==0 )
			
			ans[num[d[i].to]] = 1; 
	}
	for(int i=1;i<=n1;i++)
		cout << ans[i] << "\n";
}