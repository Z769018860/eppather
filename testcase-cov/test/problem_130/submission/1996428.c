#include<stdlib.h>
#include<math.h>
#include<stdio.h>
#include <string.h>
int a[1000001];
long long t[1000001];
long long lowbit(long long x) {
	return x & -x;
}
int main()
{
	long long n, q;
	long long c, m, d;
	long long i, j;
	long long ans1,ans2;
	scanf("%lld %lld", &n, &q);
	for (i = 1; i <= n; i++)
	{
		scanf("%lld", t + i);
	}for (i = 1; i <= n ; i++)
	{
		if (i + lowbit(i) <= n)
		t[i + lowbit(i)] += t[i];
	}
	for (i = 1; i <= q; i++)
	{
		scanf("%lld %lld %lld", &c, &m, &d);
		if (c == 1)
		{
			while (m <=n )
			{
				t[m] += d;
				m += lowbit(m);
			}
		}
		else if (c == 2)
		{
			ans1 = 0;
			ans2 = 0;
			while (d > 0)
			{
				ans1 += t[d];
				d -= lowbit(d);
			}m -= 1;
			while (m > 0)
			{
				ans2 += t[m];
				m-= lowbit(m);
			}
			printf("%lld\n", ans1 - ans2);
		}
	}
	return 0;
}