#include<cstdio>
#include<algorithm>
#include<queue>
#include<iostream>
#define F(i,l,r) for(int i=(l),i##end=(r);i<=i##end;++i)
using namespace std;
const int M=4e6+5,N=1e5+5,inf=2e9,dir[4][2]={-1,0,1,0,0,-1,0,1};
int n,m,s,t,tot=1,ans,vet[M],nxt[M],val[M],head[N],dis[N],now[N];
template<typename T>inline void readmain(T &n){T sum=0,x=1;char ch=getchar();while (ch<'0'||ch>'9'){if (ch=='-')x=-1;ch=getchar();}while (ch>='0'&&ch<='9'){sum=sum*10+ch-'0';ch=getchar();}n=sum*x;}
template<typename T>inline T& read(T &x){readmain(x);return x;}
template<typename T,typename ...Tr>inline void read(T &x,Tr&... r){readmain(x);read(r...);}
template<typename T>inline void write(T x){if (x<0){putchar('-');x=-x;}if (x>9)write(x/10);putchar(x%10+'0');return;}
template<typename T>inline void writesc(T x){write(x);putchar(' ');}
template<typename T>inline void writeln(T x){write(x);putchar('\n');}
queue<int>q;
inline void add(int u,int v,int w){vet[++tot]=v;nxt[tot]=head[u];val[tot]=w;head[u]=tot;}
inline void print(int x)
{
	if (x==0)printf("s s ");else
	if (x==t)printf("t t ");else
	{
	int y=(x-1)%n+1;
	writesc((x-y)/n+1);
	writesc(y);
	}
}
inline void addline(int u,int v,int w)
{
	add(u,v,w);add(v,u,0);
	
}
inline bool bfs(int s,int t)
{
	F(i,0,t)now[i]=head[i],dis[i]=-1;
	while (q.size())q.pop();
	q.push(s);dis[s]=1;
	while (q.size())
	{
		int u=q.front();q.pop();
		for (int i=head[u];i;i=nxt[i])
		{
			int v=vet[i];
			if (val[i]>0&&dis[v]==-1)
			{
				dis[v]=dis[u]+1;
				if (v==t)return 1;
				q.push(v);
			}
		}
	}
	return 0;
}
inline int dfs(int u,int mn)
{
	if (!mn||u==t)return mn;
	int res=0;
	for (int i=now[u];i;i=nxt[i])
	{
		int v=vet[i];now[u]=i;
		if (dis[v]==dis[u]+1)
		{
			int s=dfs(v,min(mn-res,val[i]));
			if(s==0)continue;
			val[i]-=s;val[i^1]+=s;
			res+=s;if (mn==res)break;
		}
	}
	return res;
}
inline int dinic(){int res=0;while (bfs(s,t))res+=dfs(s,inf);return res;}
inline int id(int x,int y){return (x-1)*m+y;}
main()
{
	read(n,m);t=n*m+1;char a[n+1][m+1];int b[n+1][m+1];
	F(i,1,n)F(j,1,m)cin>>a[i][j],b[i][j]=(i+j)&1,ans+=(a[i][j]=='2');
	F(i,1,n)F(j,1,m)if (!b[i][j])addline(s,id(i,j),1);else addline(id(i,j),t,1);
	F(i,1,n)F(j,1,m)if (!b[i][j]&&a[i][j]!='*'&&a[i][j]!='2')
	{
		F(k,0,3)
		{
			int nh=i+dir[k][0];
			int nl=j+dir[k][1];
			if (nh<1||nl<1||nh>n||nl>m||a[nh][nl]=='*'||a[nh][nl]=='2'||a[nh][nl]==a[i][j])continue;
			addline(id(i,j),id(nh,nl),1);
		}
	}
	writeln(dinic()+ans);
	return 0;
}
