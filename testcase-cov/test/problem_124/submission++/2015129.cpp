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
const int N=1e7+10;
const LL mod=1e9+7;
LL n, k, prime[N], pr;
bool v[N];LL num[N];
LL qpow(LL a, LL b)
{
	LL res=1%mod;
	while (b)
	{
		if (b&1) res=res*a%mod;
		a=a*a%mod;b>>=1;
	}
	return res;
}

void init()
{
	num[1]=1;
	for (int i=1;i<=n;i++)
	{
		if (!v[i]) prime[++pr]=i, num[i]=qpow(i, k);
		for (int j=1;j<=pr&&i*prime[j]<=n;j++)
		{ 	
			v[i*prime[j]]=1;
			num[i*prime[j]]=num[i]*num[prime[j]]%mod;
			if (i%prime[j]==0) break;
		}
	}
}

int main()
{
	read(n), read(k);
	init();LL ans=0;
	for (int i=1;i<=n;i++) ans=(ans+1ll*(n/i)*num[i])%mod;
	printf("%lld", ans%mod);
	return 0;
}