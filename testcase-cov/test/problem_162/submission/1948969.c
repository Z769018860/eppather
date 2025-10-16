#include<stdio.h>
long long result(long long x, long long a, long long p)
{
	long long ans=1;
	while (a > 0)
	{
		if (a % 2 == 1)
		{
			ans = ans * x % p;
		}
		x = x * x % p;
		a = a / 2;
	}
	return ans;
}
int main()
{
	int x, n;
	int ai;
	int p = 998244352;
	scanf("%d%d", &x, &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &ai);
		printf("%d ", result(x, ai, p));
	}
	return 0;
}
