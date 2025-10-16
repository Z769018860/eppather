#include<stdlib.h>
#include<math.h>
#include<stdio.h>
#include <string.h>
long long t[1000001];
long long t0[1000001];
long long t1[1000001];
long long n, q;
long long lowbit(long long x) {
	return x & -x;
}
int main()
{
	
	long long c, m, d, x;
	long long i, j, I;
	long long ans1, ans2;
	scanf("%lld %lld", &n, &q);
	for (i = 1; i <= n; i++)
	{
		scanf("%lld", t + i);
		t0[i] = t[i] - t[i - 1];
		t1[i] = t0[i];
	}
	for (i = 1; i <= n; i++)
	{
		if (i + lowbit(i) <= n)
			t1[i + lowbit(i)] += t1[i];
	}
	for (i = 1; i <= q; i++)
	{
		scanf("%lld", &c);
		if (c == 1)
		{
			scanf("%lld %lld %lld", &m, &d, &x);
			d = d + 1;
			while (m <= n)
			{
				t1[m] += x;
				m += lowbit(m);
			}while (d <= n)
			{
				t1[d] -= x;
				d += lowbit(d);
			}
		}
		else if (c == 2)
		{
			scanf("%lld", &m);
			ans1 = 0;
			while (m > 0)
			{
				ans1 += t1[m];
				m -= lowbit(m);
			}
			printf("%lld\n", ans1);
		}
	}
	return 0;
}