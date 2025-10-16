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
const int N=1e5+10, M=60;
int n, m, tot;
LL a[N], b[N], p[M];

void insert(LL x)
{
	for (int i=M;~i;i--)
	{
		if ((x>>i)&1) 
		{
			if (!p[i]) {p[i]=x;break;}
			x^=p[i];
		}
	}
}

int main()
{
	read(n);LL x;
	for (int i=1;i<=n;i++) read(x), insert(x);
	for (int i=0;i<M;i++)
		for (int j=i-1;~j;j--)
			if (p[i]&(1ll<<j)) p[i]^=p[j];
	for (int i=0;i<M;i++) if (p[i]) a[tot++]=p[i];
	read(m);
	for (int i=1;i<=m;i++) 
	{
		read(x);
		if (tot!=n) x--;
		if (x>=(1ll<<tot)) puts("-1");
		else 
		{
			LL ans=0;
			for (int i=0;i<tot;i++)
				if (x&(1ll<<i)) ans^=a[i];
			printf("%lld\n", ans);
		}
	}
	return 0;
}