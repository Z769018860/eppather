#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int a[55], b[55], f[105], g[105];
int pw[55][3005];

int main()
{
	int t, i, j, k, n, p, c, d;
	ll m, v;
	scanf("%d%d", &n, &p);
	for(i = 0; i <= n; i++)
		scanf("%d", a + i);
	pw[0][0] = 1;
	for(i = 1; i < p; i++)
	{
		for(j = 0; j <= (i - 1) * n; j++)
			for(k = 0; k <= n; k++)
				pw[i][j + k] += pw[i - 1][j] * a[k];
		for(j = 0; j <= i * n; j++)
			pw[i][j] %= p;
	}
	scanf("%d", &t);
	while(t--)
	{
		scanf("%lld%lld", &m, &v);
		for(i = 1; i <= 2 * n; i++)
			f[i] = 0;
		f[0] = 1;
		while(m || v)
		{
			for(i = 0; i <= 2 * n; i++)
				g[i] = 0;
			for(i = 0; i <= 2 * n; i++)
			{
				c = (v - i % p + p) % p;
				d = m % p;
				for(j = 0; j <= n; j++)
					g[(i + c) / p + j] += f[i] * pw[d][c + j * p];
			}
			for(i = 0; i <= 2 * n; i++)
				f[i] = g[i] % p;
			m /= p;
			v /= p;
		}
		printf("%d\n", f[0]);
	}
	return 0;
}