#include <bits/stdc++.h>

using namespace std;

const int maxn = 355;

int n, tot;

bool vis[maxn][maxn];

int read()
{
	int res = 0, ch = getchar();
	for (; !isdigit(ch); ch = getchar())
		;
	for (; isdigit(ch); ch = getchar())
		res = (res << 3) + (res << 1) + (ch & 15);
	return res; 
}

int cn3(int n)
{
	return n * (n - 1) * (n - 2) / 3 / 2;
}

int main()
{
	n = read();
	while (n)
	{
		int m = 3;
		while (cn3(m + 1) <= n)
			++m;
		n -= cn3(m);
		for (int i = tot + 1; i <= tot + m; ++i)
		{
			for (int j = i + 1; j <= tot + m; ++j)
			{
				for (int k = j + 1; k <= tot + m; ++k)
					vis[i][j] = vis[j][k] = vis[i][k] = 1;
			}
		}
		tot += m;
	}
	printf("%d\n", tot);
	for (int i = 1; i <= tot; ++i)
	{
		for (int j = i + 1; j <= tot; ++j)
			printf("%d%c", vis[i][j], " \n"[j == tot]);
	}
	return 0;
}