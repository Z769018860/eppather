#include <bits/stdc++.h>

using namespace std;
const int N = 2100;
long long s1[N][N], s2[N][N], s3[N][N], s4[N][N];
int n, m;

int lowbit(int x)
{
	return x & (-x);
}

void updata(int x, int y, long long z)
{
	for (int i = x; i <= n; i += lowbit(i))
	{
		for (int j = y; j <= n; j += lowbit(j))
		{
			s1[i][j] += z;
			s2[i][j] += x * z;
			s3[i][j] += y * z;
			s4[i][j] += x * y * z;
		}
	}
}

long long sum(int x, int y)
{
	long long res = 0;
	for (int i = x; i > 0; i -= lowbit(i))
	{
		for (int j = y; j > 0; j -= lowbit(j))
		{
			res += (x + 1) * (y + 1) * s1[i][j] - (y + 1) * s2[i][j] - (x + 1) * s3[i][j] + s4[i][j];
		}
	}
	return res;
}

int main()
{
	while (scanf("%d %d", &n, &m) == 2)
	{
		memset(s1, 0, sizeof(s1));
		memset(s2, 0, sizeof(s2));
		memset(s3, 0, sizeof(s3));
		memset(s4, 0, sizeof(s4));
		int k;
		while (scanf("%d", &k) == 1)
		{
			if (k == 1)
			{
				int a, b, c, d;
				long long x;
				scanf("%d %d %d %d %lld", &a, &b, &c, &d, &x);
				updata(a, b, x);
				updata(c + 1, b, -x);
				updata(a, d + 1, -x);
				updata(c + 1, d + 1, x);
			}
			else
			{
				int x1, y1, x2, y2;
				scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
				printf("%lld\n", sum(x2, y2) - sum(x1 - 1, y2) - sum(x2, y1 - 1) + sum(x1 - 1, y1 - 1));
			}
		}
	}
	return 0;
}