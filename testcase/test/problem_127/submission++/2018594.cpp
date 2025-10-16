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
const int N=1.2e3+10, M=1.2e5+10, inf=0x3f3f3f3f;
int n, m, st, ed, h[N], cur[N], gap[N<<1];LL e[N];bool v[N];
struct cmp{bool operator()(const int &A, const int &B){return h[A]<h[B];}};
struct edge{int y;LL c;int other;};vector<edge> a[N];
void ins(int x, int y, LL c)
{
	a[x].push_back({y, c, (int)a[y].size()});
	a[y].push_back({x, 0, (int)a[x].size()-1});
}

bool bfs()
{
	queue<int> Q;Q.push(ed);
	memset(h, 0x3f, sizeof h);h[ed]=0;
	while (!Q.empty())
	{
		int x=Q.front();Q.pop();
		for (auto k:a[x])
		{
			int y=k.y;
			if (a[y][k.other].c&&h[y]>h[x]+1)
				h[y]=h[x]+1, Q.push(y);
		}
	}
	return h[st]!=inf;
}

priority_queue<int, vector<int>, cmp> q;
void push(int x)
{
	for (int &i=cur[x];i<(int)a[x].size();i++)
	{
		auto &k=a[x][i];int y=k.y;
		if (k.c&&h[y]+1==h[x])
		{
			LL sx=min(e[x], k.c);
			k.c-=sx, a[y][k.other].c+=sx;
			e[x]-=sx, e[y]+=sx;
			if (y!=st&&y!=ed&&!v[y]&&h[y]<inf) q.push(y), v[y]=1;
			if (!e[x]) return ;
		}
	}
	cur[x]=0;
}

void relabel(int x)
{
	h[x]=inf;
	for (auto k:a[x]) if (k.c&&h[k.y]+1<h[x]) h[x]=h[k.y]+1;
}

LL hlpp()
{
	if (!bfs()) return 0;
	h[st]=n, memset(gap, 0, sizeof gap);
	for (int i=1;i<=n;i++) if (h[i]<inf) ++gap[h[i]];
	for (auto &k:a[st])
	{
		int y=k.y;LL sx=k.c;
		if (k.c&&h[y]<inf)
		{
			k.c-=sx, a[y][k.other].c+=sx;
			e[st]-=sx, e[y]+=sx;
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
				for (int i=1;i<=n;i++) if (i!=st&&i!=ed&&h[i]>h[x]&&h[i]<n+1) h[i]=n+1;
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
		int x, y;LL c;
		read(x), read(y), read(c);
		ins(x, y, c);
	}
	printf("%lld", hlpp());
	return 0;
}
