#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int lowbit(int x)
{
	return x & -x;
}

static void add(long *c, int n, int i, long k)
{
	while (i <= n) {
		c[i] += k;
		i += lowbit(i);
	}
}

static long sum(long *c, int i)
{
	long result = 0;
	while (i) {
		result += c[i];
		i -= lowbit(i);
	}
	return result;
}

int main(void)
{
	int n, q;
	long *c;
	int op;
	long x, y;
	int i;

	scanf("%d %d", &n, &q);
	c = (long *)calloc(n + 1, sizeof(long));
	for (i = 1; i <= n; i++) {
		scanf("%ld", &x);
		add(c, n, i, x);
	}

	for (i = 1; i <= q; i++) {
		scanf("%d %ld %ld", &op, &x, &y);
		if (op == 1)
			add(c, n, x, y);
		else if (op == 2)
			printf("%ld\n", sum(c, y) - sum(c, x - 1));
	}

	return 0;
}