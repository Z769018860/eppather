#include<iostream>
#include<cstring>
#include<algorithm>
#include<map>
#include<vector>
#include<queue>
#include<cmath>
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
const int N=3e6+10;
LL n, p, inv[N];

int main()
{
	read(n), read(p);
	inv[1]=1;printf("1\n");
	for (int i=2;i<=n;i++)
		inv[i]=(p-p/i)*inv[p%i]%p, printf("%lld\n", inv[i]);
	return 0;
}