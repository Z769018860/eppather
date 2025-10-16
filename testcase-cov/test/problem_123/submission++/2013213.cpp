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
const int N=5e5+10;
int n, m, f[N];
struct edge{int x, y, c;}a[N];
bool cmp(edge n1, edge n2) {return n1.c<n2.c;}
int findfa(int x) {return f[x]=(f[x]==x)?x:findfa(f[x]);}

int main()
{
	read(n), read(m);
	int cnt=0;LL ans=0;
	for (int i=1;i<=n;i++) f[i]=i;
	for (int i=1;i<=m;i++)
	{
		int x, y, c;
		read(x), read(y), read(c);
		a[i]={x, y, c};
	}
	sort(a+1, a+m+1, cmp);
	for (int i=1;i<=m;i++)
	{
		int x=a[i].x, y=a[i].y;
		int tx=findfa(x), ty=findfa(y);
		if (tx==ty) continue;
		f[ty]=tx;ans+=a[i].c;
		if (++cnt==n-1) break;
	}
	printf("%lld", ans);
	return 0;
}