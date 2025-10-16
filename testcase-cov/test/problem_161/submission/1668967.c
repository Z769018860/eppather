#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
long long b[5000010];
long long a[5000010];
long long s[5000010];
long long inv[5000010];
long long invs[5000010];
long long y[30];
int main()
{
	long long x,n,i,j,p,z;
	int p_2[30]={1,0,1,0,0,0,0,0,0,1,0,1,0,0,1,1,0,1,0,1,1,0,0,1,1,1,0,1,1,1};
	scanf("%lld",&n);
	p=1e9+7;
	b[n]=1;
	for(i=n-1;i>=1;i--)
	{
		b[i]=(b[i+1]*998244353)%p;
	}
	for(s[0]=1,x=0,i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		s[i]=(s[i-1]*a[i])%p;
	}
	for(z=s[n],y[0]=s[n],j=1;j<=29;j++)
	{
		y[j]=(y[j-1]*y[j-1])%p;
		if(p_2[j]==1)
		{
			z=(z*y[j])%p;
		}
	}
	invs[n]=z;
	for(i=n-1;i>=1;i--)
	{
		invs[i]=(invs[i+1]*a[i+1])%p;
	}
	for(i=1;i<=n;i++)
	{
		inv[i]=(invs[i]*s[i-1])%p;
	}
	for(x=0,i=1;i<=n;i++)
	{
		x=(x+(b[i]*inv[i])%p)%p;
	}
	printf("%lld\n",x);
	return 0;
}