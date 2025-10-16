#include<iostream>
#include<cstdio>
#include<vector>
#define N 1000000
using namespace std;
int read()
{
	char c=0;
	int sum=0;
	while (c<'0'||c>'9') c=getchar();
	while ('0'<=c&&c<='9') sum=sum*10+c-'0',c=getchar();
	return sum;
}
int gcd(int a,int b)
{
	if (!b) return a;
	return gcd(b,a%b);
}
int sx,sy;
void exgcd(int a,int b)
{
	if (!b)
	{
		sx=1,sy=0;
		return;
	}
	int tx;
	exgcd(b,a%b),tx=sx,sx=sy,sy=tx-(a/b)*sy;
	return;
}
struct reads
{
	int num,data;
};
int n,m,q,res[N+1],lg[N+1],fa[N+1][21],op[N+1],X[N+1],Y[N+1],Z[N+1],A[N+1],B[N+1],rt[N+1],depth[N+1],sdepth[N+1];
bool used[N+1];
vector<reads>E[N+1];
void add(int x,int y,int z)
{
	E[x].push_back((reads){y,z}),E[y].push_back((reads){x,z});
	return;
}
int find(int x)
{
	if (rt[x]==x) return x;
	return rt[x]=find(rt[x]);
}
void unionn(int x,int y)
{
	rt[x]=y;
	return;
}
void dfs(int x)
{
	used[x]=1;
	for (int i=0;i<E[x].size();++i)
		if (!used[E[x][i].num])
			fa[E[x][i].num][0]=x,sdepth[E[x][i].num]=sdepth[x]+1,depth[E[x][i].num]=(depth[x]+E[x][i].data)%m,dfs(E[x][i].num);
	return;
}
int lca(int x,int y)
{
	if (sdepth[x]<sdepth[y]) swap(x,y);
	for (int i=lg[n];i>=0;--i)
		if (sdepth[fa[x][i]]>=sdepth[y])
			x=fa[x][i];
	if (x==y) return x;
	for (int i=lg[n];i>=0;--i)
		if (fa[x][i]!=fa[y][i])
			x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
int dis(int x,int y)
{
	long long d=(long long)(depth[x])+depth[y]-(depth[lca(x,y)]<<1);
	return (d%m+m)%m;
}
int main()
{
	int r,a,p,g;
	for (int i=2;i<=N;++i) lg[i]=lg[i>>1]+1;
	n=read(),m=read(),q=read();
	for (int i=1;i<=n;++i) rt[i]=i;
	for (int i=1;i<=q;++i)
	{
		op[i]=read();
		if (op[i]==1)
		{
			X[i]=read(),Y[i]=read(),Z[i]=read();
			if (find(X[i])!=find(Y[i])) unionn(find(X[i]),find(Y[i])),add(X[i],Y[i],Z[i]);
		}
		else X[i]=read(),Y[i]=read(),Z[i]=read(),A[i]=read(),B[i]=read();
	}
	for (int i=1;i<=n;++i)
		if (!used[i])
			sdepth[i]=1,dfs(i);
	for (int i=1;i<=lg[n];++i)
		for (int j=1;j<=n;++j)
			fa[j][i]=fa[fa[j][i-1]][i-1];
	for (int i=1;i<=n;++i) rt[i]=i,res[i]=m;
	for (int i=1;i<=q;++i)
	{
		if (op[i]==1)
		{
			if (find(X[i])==find(Y[i])) res[find(X[i])]=gcd(res[find(X[i])],dis(X[i],Y[i])+Z[i]);
			else res[find(Y[i])]=gcd(gcd(res[find(X[i])],res[find(Y[i])]),dis(X[i],Y[i])+Z[i]),unionn(find(X[i]),find(Y[i]));
		}
		else if (find(X[i])==find(Y[i]))
		{
			r=(dis(X[i],Y[i])+res[find(X[i])]-Z[i])%res[find(X[i])],g=gcd(A[i],res[find(X[i])]);
			if (r%g!=0) puts("0");
			else a=A[i]/g,r/=g,p=res[find(X[i])]/g,exgcd(a,p),sx=(1ll*sx*r%p+p)%p,printf("%d\n",(B[i]-1-sx+p)/p);
		}
		else puts("0");
	}
	return 0;
}
