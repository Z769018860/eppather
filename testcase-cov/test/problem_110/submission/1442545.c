#include<stdio.h> 
#define ll long long
ll pp(ll a,ll b,ll p)
{
	ll r=1;
	while(b)
	{
		if(b%2==1)
			r=(r*a)%p;
		a=(a*a)%p;
		b=b/2;
	}
	return r;
}
int main()
{
	ll n,p;
	scanf("%lld %lld",&n,&p);
	for(int i=1;i<=n;i++)
		printf("%lld\n",pp(i,p-2,p));
	return 0; 
} 