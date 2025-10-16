#include<queue>
#include<cmath>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
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
const int N=1.2e3+10, M=1.2e5+10, inf=0x3f3f3f3f;
int n, m, st, ed, h[N], gap[N<<1], cur[N];LL e[N];bool v[N];
struct cmp{bool operator ()(int A, int B)const{return h[A]<h[B];}};
struct edge{int x, y;int c;int pre;}a[M<<1];int alen=1, last[N];
void ins(int x, int y, int c)
{
	alen++;a[alen]={x, y, c, last[x]};last[x]=alen;
	alen++;a[alen]={y, x, 0, last[y]};last[y]=alen;
}

bool bfs()
{
	queue<int> Q;Q.push(ed);
	memset(h, 0x3f, sizeof h);h[ed]=0;
	while (!Q.empty())
	{
		int x=Q.front();Q.pop();
		for (int k=last[x];k;k=a[k].pre)
		{
			int y=a[k].y;
			if (a[k^1].c&&h[y]>h[x]+1) 
				h[y]=h[x]+1, Q.push(y);
		}
	}
	return h[st]!=inf;
}

priority_queue<int, vector<int>, cmp> q;
void push(int x)
{
	for (int k=cur[x];k;k=a[k].pre)
	{
		int y=a[k].y;cur[x]=k;
		if (a[k].c&&h[y]+1==h[x]&&h[y]<inf)
		{
			LL sx=min(e[x], (LL)a[k].c);
			a[k].c-=sx, a[k^1].c+=sx, e[x]-=sx, e[y]+=sx;
			if (y!=st&&y!=ed&&!v[y]) q.push(y), v[y]=1;
			if (!e[x]) return ;
		}
	}
	cur[x]=last[x]; 
}

void relabel(int x)
{
	h[x]=inf;
	for (int k=last[x];k;k=a[k].pre)
	{
		int y=a[k].y;
		if (a[k].c&&h[y]+1<h[x]) h[x]=h[y]+1;
	}
}

int hlpp()
{
	if (!bfs()) return 0;
	memcpy(cur, last, sizeof cur);
	h[st]=n, memset(gap, 0, sizeof gap);
	for (int i=1;i<=n;i++) if (h[i]<inf) ++gap[h[i]];
	for (int k=last[st];k;k=a[k].pre)
	{
		int y=a[k].y;LL sx=a[k].c;
		if (a[k].c&&h[y]<inf)
		{
			a[k].c-=sx, a[k^1].c+=sx, e[st]-=sx, e[y]+=sx;
			if (y!=st&&y!=ed&&!v[y]) q.push(y), v[y]=1;
		}
	}
	while (!q.empty())
	{
		int x=q.top();q.pop();
		v[x]=0, push(x);
		if (e[x])
		{
			if (!--gap[h[x]])
				for (int i=1;i<=n;i++) 
					if (i!=st&&i!=ed&&h[i]>h[x]&&h[i]<n+1) h[i]=n+1;
			relabel(x), ++gap[h[x]];
			q.push(x), v[x]=1;
		}
	}
	return e[ed];
}

int main()
{
	read(n), read(m), read(st), read(ed);
	for (int i=1;i<=m;i++)
	{
		int x, y, c;
		read(x), read(y), read(c);
		ins(x, y, c);
	}
	printf("%d", hlpp());
	return 0;
}