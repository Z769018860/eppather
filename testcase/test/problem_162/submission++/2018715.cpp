#include<stdio.h>
const int N=1e7;
long long a[N];
long long pow(long long x,long long n)
{
	long long res=1;
	while(n)
	{
			if(n&1)
		{
			res=(res*x)%998244352;
		}
			n=n>>1;
			x=(x*x)%998244352;
	}
	return res;
}
int main()
{
	long long m,n;
	scanf("%lld%lld",&m,&n);
	for(int i=0;i<n;i++)
	{
		scanf("%lld",&a[i]);
	}
	for(int i=0;i<n;i++)
	{
		printf("%lld ",pow(m,a[i])%998244352);
	}
	return 0;
 } 