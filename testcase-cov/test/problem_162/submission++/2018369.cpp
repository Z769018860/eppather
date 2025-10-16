#include <stdio.h>
#define N 998244352
void f(long long di,long long mi)
{
	long long result=1;
	while(mi>0)
	{
		if(mi%2!=0)
		{
			result=result*di%N;
		}
		mi=mi/2;
		di=di*di%N;
	}
	printf("%d ",result);
}
int main()
{
	long long x,n;scanf("%lld%lld",&x,&n);
	int i,j;
	int k;
	for(i=1;i<=n;i++)
	{
		scanf("%d",&k);
		f(x,k);
	}
	return 0;
}