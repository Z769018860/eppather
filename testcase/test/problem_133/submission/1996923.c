#include<stdlib.h>
#include<math.h>
#include<stdio.h>
#include <string.h>
#define int long long
long long n, m;
long long tree[10000][10000];
long long lowbit(long long x) {
	return x & -x;
                                                     }
void add(int x, int y, int val)
{
	while (x <= n)
	{
		int ty = y;
		while (ty <= m)
		{
			tree[x][ty] += val;
			ty += lowbit(ty);
		}
		x += lowbit(x);
	}
}long long query1(int x, int y)
{
	long long ans = 0;
	while (x >= 1)
	{
		int ty = y;
		while (ty >= 1)
		{
			ans += tree[x][ty];
			ty -= lowbit(ty);
		}
		x -= lowbit(x);
	}
	return ans;
}
long long query(int x0, int y0, int x1, int y1)
{
	return query1(x1, y1) + query1(x0 - 1, y0 - 1) - query1(x1, y0 - 1) - query1(x0 - 1, y1);
}signed main()
{
	long long i, j, x, y, a, b, c, d, k;
	scanf("%lld %lld", &n, &m);
	while (scanf("%lld", &x) != EOF)
	if (x == 1)
	{
		scanf("%lld %lld %lld", &x, &y, &k);
		add(x, y, k);
	}
	else {
		scanf("%lld %lld %lld %lld", &a, &b, &c, &d);
		long long num = query(a, b, c, d);
		printf("%lld\n", num);
	}
	return 0;
}