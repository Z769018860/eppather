#include<stdio.h>

long long bit[1000010];

long long lowbit(long long x)
{
	return (x&(-x));
}
void updata(long long i,long long v,long long n)
{
	for(i;i<=n;i+=lowbit(i))
		{
			bit[i] += v; 
		} 
}

long long sum1(long long n)
{
	long long i,ans = 0;
	for(i=n;i>0;i-=lowbit(i))
		{
			ans += bit[i]; 
		} 
	return ans;
}
long long sum2(long long l,long long r)
{
	return sum1(r) - sum1(l-1);
}
 main()
{
	
	
	long long n,q,i,j,v,a,b,c;
	scanf("%lld %lld",&n,&q);

	for(i = 1;i<=n;i++)
	{
		scanf("%lld",&v);
		updata(i,v,n) ;
		
	}
	
	for(i = 1;i<=q;i++)
	{
		scanf("%lld %lld %lld",&a,&b,&c);
		if(a == 1)
			updata(b,c,n);
		else if(a == 2)
			printf("%lld\n",sum2(b,c));
	}
    return 0;
}