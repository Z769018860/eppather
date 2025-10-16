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
const int N=1e5+10;
int n, m;LL p[N], a[N];

void insert(LL x)
{
	for (int i=51;i;i--)
	{
		if (x>>i&1) 
		{
			if (!p[i]) {p[i]=x;break;}
			x^=p[i];
		}
	}
}

int main()
{
	read(n);LL ans=0;
	for (int i=1;i<=n;i++) read(a[i]), insert(a[i]);
	for (int i=51;i;i--) ans=max(ans, ans^p[i]);
	printf("%lld", ans);
	return 0;
}