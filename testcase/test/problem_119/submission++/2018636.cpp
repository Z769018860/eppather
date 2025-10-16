#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
using namespace std;
#define N 2510
#define M 6210
int n,m,s,t;
int head[M*2],to[M*2],ver[M*2],wei[M*2],tot;
int dist[N],v[N];
void add(int x,int y,int z)
{
	ver[++tot] = y;
	to[tot] = head[x];
	head[x] = tot;
	wei[tot] = z;
}
void djstl(int s,int t)
{
	memset(dist,0x3f3f3f3f,sizeof(dist));
	dist[s] = 0;
	for (int i=1;i<n;i++)
		{
		int x = 0;
		for (int j=1;j<=n;j++)
			{
			if (!v[j] and (x==0 or dist[j]<dist[x])) x = j;
			}
		v[x] = 1;
		for (int j = head[x];j;j = to[j])
			{
			int y = ver[j];
			dist[y] =min(dist[y],dist[x]+wei[j]);
			}
		}
	cout<<dist[t];
}
int main()
{
	cin>>n>>m>>s>>t;
	for (int i=1;i<=m;i++)
		{
		int u,v,w;
		cin>>u>>v>>w;
		add(u,v,w);
		add(v,u,w);
		}
	djstl(s,t);
}