#include<stdio.h>
#include<iostream>
using namespace std;
long long fun(long long a,long long b,long long c)
{
	long long num=1;
	while(b)
	{
		if(b&1)
		{
			num=num*a%c;
		}
		b >>= 1;
		a=a*a%c;
	}
	return num;
}
int aaa[5000005];
int main()
{
	int m; 
	int n;
	scanf("%d%d",&m, &n);
	for(int i = 0; i < n; i ++)
	{
		scanf("%lld", &aaa[i]);
	}
	for(int i = 0; i < n; i ++)
	{
		printf("%lld ",fun(m, aaa[i], 998244352));
	}
	return 0;
}