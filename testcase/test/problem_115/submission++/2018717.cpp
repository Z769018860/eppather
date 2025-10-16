#include<map>
#include<queue>
#include<cmath>
#include<vector>
#include<complex>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<unordered_map>
using namespace std;

char buf[1<<20], *p1=buf, *p2=buf;
#define getchar() (p1==p2&&(p2=buf+fread(p1=buf, 1, 1<<20, stdin), p1==p2)?EOF:*p1++)
template <typename T>
void read(T &x)
{
	x=0;int f=1;char c=getchar();
	while (!isdigit(c)) f=(c=='-')?-1:1, c=getchar();
	while (isdigit(c)) x=(x<<1)+(x<<3)+c-'0', c=getchar();
	x*=f;
}

typedef long long LL;
const int N=210, M=2e4+10, inf=0x3f3f3f3f;
int n, m, st, ed, to[N], low[M], h[N], now[N];
struct edge{int x, y, c, pre;}a[M<<3];int alen=1, last[N];
void ins(int x, int y, int c)
{
	alen++;a[alen]={x, y, c, last[x]};last[x]=alen;
	alen++;a[alen]={y, x, 0, last[y]};last[y]=alen;
}

bool bfs()
{
	queue<int> Q;Q.push(st);
	memset(h, 0x3f, sizeof h);h[st]=0;
	while (!Q.empty())
	{
		int x=Q.front();Q.pop();
		for (int k=last[x];k;k=a[k].pre)
		{
			int y=a[k].y;
			if (a[k].c&&h[y]>h[x]+1) h[y]=h[x]+1, Q.push(y);
		}	
	}
	return h[ed]!=inf;
}

int dinic(int x, int flow)
{
	if (x==ed) return flow;
	int sx=0, sy;
	for (int &k=now[x];k;k=a[k].pre)
	{
		int y=a[k].y;
		if (a[k].c&&h[y]==h[x]+1)
		{
			sy=dinic(y, min(a[k].c, flow-sx));
			a[k].c-=sy, a[k^1].c+=sy, sx+=sy;
			if (sx==flow) return sx;
		}
	}
	if (!sx) h[x]=-1;
	now[x]=last[x];
	return sx;
}

int main()
{
	read(n), read(m);
	st=n+1, ed=n+2;
	for (int i=1;i<=m;i++) 
	{
		int x, y, u, v;
		read(x), read(y), read(u), read(v);
		low[i]=u, ins(x, y, v-u);
		to[x]-=u, to[y]+=u;
	}
	int sum=0, ans=0;
	for (int i=1;i<=n;i++)
	{
		if (to[i]<0) ins(i, ed, -to[i]);
		if (to[i]>0) ins(st, i, to[i]), sum+=to[i];
	}
	memcpy(now, last, sizeof now);
	while (bfs()) ans+=dinic(st, 2e9);
	if (ans==sum) 
	{
		puts("YES");
		for (int i=1;i<=m;i++) printf("%d\n", low[i]+a[(i<<1)+1].c);
	}
	else printf("NO");
	return 0;
}