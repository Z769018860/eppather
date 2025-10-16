#include <iostream>
using namespace std;
#define N 998244352
void f(long long base,long long power)
{
	long long result=1;
	while(power>0)
	{
		if(power%2==1) result=result*base%N;
		power/=2;
		base=base*base%N;
	}
	printf("%lld ",result);
}
int main()
{
	long long c,n;
	cin>>c>>n;
	long long m;
	for(long long i=1;i<=n;i++)
	{
		scanf("%lld",&m);
		f(c,m);
	}
	return 0;
}