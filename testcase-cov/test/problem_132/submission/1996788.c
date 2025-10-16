#include<stdlib.h>
#include<math.h>
#include<stdio.h>
#include <string.h>
long long t[1000001];
long long t0[1000001];
long long t1[1000001];
long long t1i[1000001];
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
		t1i[i] = t0[i] * i;
	}
	for (i = 1; i <= n; i++)
	{
		if (i + lowbit(i) <= n)
		{
			t1[i + lowbit(i)] += t1[i];
			t1i[i + lowbit(i)] += t1i[i];
		}
	}
	for (i = 1; i <= q; i++)
	{
		scanf("%lld", &c);
		if (c == 1)
		{
			int M;
			scanf("%lld %lld %lld", &m, &d, &x);
			d = d + 1;
			M = m;
			while (m <= n)
			{
				t1[m] += x;
				t1i[m] += x * M;
				m += lowbit(m);
			}M = d;
			while (d <= n)
			{
				t1[d] -= x;
				t1i[d] -= x * M;
				d += lowbit(d);
			}
		}
		else if (c == 2)
		{
			int M, D;
			ans1 = 0;
			ans2 = 0;
			scanf("%lld %lld", &m, &d);
			m = m - 1;
			M = m; D = d;
			
			while (m > 0)
			{
				ans1 += t1[m];
				m -= lowbit(m);
			}
			ans1 *= (M + 1);
			while (M > 0)
			{
				ans1 -= t1i[M];
				M -= lowbit(M);
			}
			while (d > 0)
			{
				ans2 += t1[d];
				d -= lowbit(d);
			}
			ans2 *= (D + 1);
			while (D > 0)
			{
				ans2 -= t1i[D];
				D -= lowbit(D);
			}
			printf("%lld\n", ans2-ans1);
		}
	}
	return 0;
}