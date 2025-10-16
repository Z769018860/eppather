#include<stdio.h>

long long bit[1000010],d[1000010];

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
		scanf("%lld",&d[i]);
			updata(i,d[i]-d[i-1],n) ;
		
	}
	
	for(i = 1;i<=q;i++)
	{
		scanf("%lld",&a);
		if(a == 1)
		{
			scanf("%lld %lld %lld",&a,&b,&c);
			updata(a,c,n);
			updata(b+1,-c,n);
		}
			
		else if(a == 2)
		{
			scanf("%lld",&a);
			printf("%lld\n",sum1(a));
		}
		
	}
    return 0;
}